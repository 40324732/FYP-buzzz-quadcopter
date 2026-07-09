#include <chrono>
#include <memory>
#include <cmath>
#include <Eigen/Dense>

#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/imu.hpp"
#include "bzzz_msgs/msg/pressure_data.hpp"
#include "bzzz_msgs/msg/target_thrust.hpp"

using std::placeholders::_1;
using namespace Eigen;
using namespace std::chrono_literals;

class AltitudeControllerNode : public rclcpp::Node
{
public:
    AltitudeControllerNode() : Node("altitude_controller_node")
    {
        thrust_pub_ = this->create_publisher<bzzz_msgs::msg::TargetThrust>("/bzzz/target_thrust", 10);
        
        imu_sub_ = this->create_subscription<sensor_msgs::msg::Imu>(
            "/bzzz/imu", rclcpp::SensorDataQoS(), std::bind(&AltitudeControllerNode::imu_callback, this, _1));
            
        baro_sub_ = this->create_subscription<bzzz_msgs::msg::PressureData>(
            "/bzzz/pressure", 10, std::bind(&AltitudeControllerNode::baro_callback, this, _1));

        X_ekf_ << 0.0, 0.0, 1.0, 0.0;
        P_ekf_ = Matrix4f::Identity(); 
        Q_ekf_ = Matrix4f::Identity() * 0.001;
        R_ekf_ = 0.5;
        
        q_est_ << 1.0, 0.0, 0.0, 0.0; 

        K_altitude_ = MatrixXf(1, 2);
        K_altitude_ << 3.5, 1.2;

        timer_ = this->create_wall_timer(
            20ms, std::bind(&AltitudeControllerNode::timer_callback, this));
    }

private:
    Vector4f X_ekf_, q_est_; 
    Matrix4f P_ekf_, Q_ekf_;
    float R_ekf_;
    float latest_baro_alt_ = 0.0;
    bool new_baro_data_ = false;

    Vector3f latest_acc_ = Vector3f::Zero();
    Vector3f latest_gyro_ = Vector3f::Zero();

    void imu_callback(const sensor_msgs::msg::Imu::SharedPtr msg)
    {
        latest_acc_ << msg->linear_acceleration.x, msg->linear_acceleration.y, msg->linear_acceleration.z;
        latest_gyro_ << msg->angular_velocity.x, msg->angular_velocity.y, msg->angular_velocity.z;

        float dt = 0.005f; 
        float q1 = q_est_(0), q2 = q_est_(1), q3 = q_est_(2), q4 = q_est_(3);
        Vector3f acc = latest_acc_.normalized();
        
        Vector4f f(
            2.0f * (q2 * q4 - q1 * q3) - acc(0),
            2.0f * (q1 * q2 + q3 * q4) - acc(1),
            2.0f * (0.5f - q2 * q2 - q3 * q3) - acc(2),
            0.0f
        );
        Matrix<float, 4, 4> J;
        J << -2.0f*q3,  2.0f*q4, -2.0f*q1, 2.0f*q2,
              2.0f*q2,  2.0f*q1,  2.0f*q4, 2.0f*q3,
              0.0f,    -4.0f*q2, -4.0f*q3, 0.0f,
              0.0f,     0.0f,     0.0f,    0.0f;
              
        Vector4f step = J.transpose() * f;
        step.normalize();

        float beta = 0.1f;
        Vector4f q_dot(
            0.5f * (-q2 * latest_gyro_(0) - q3 * latest_gyro_(1) - q4 * latest_gyro_(2)) - beta * step(0),
            0.5f * ( q1 * latest_gyro_(0) + q3 * latest_gyro_(2) - q4 * latest_gyro_(1)) - beta * step(1),
            0.5f * ( q1 * latest_gyro_(1) - q2 * latest_gyro_(2) + q4 * latest_gyro_(0)) - beta * step(2),
            0.5f * ( q1 * latest_gyro_(2) + q2 * latest_gyro_(1) - q3 * latest_gyro_(0)) - beta * step(3)
        );

        q_est_ += q_dot * dt;
        q_est_.normalize();
    }

    void baro_callback(const bzzz_msgs::msg::PressureData::SharedPtr msg)
    {
        latest_baro_alt_ = msg->relative_altitude;
        new_baro_data_ = true; 
    }

    void timer_callback()
    {
        float dt = 0.02f;

        float a_z_global = 2.0f * (q_est_(1)*q_est_(3) - q_est_(0)*q_est_(2)) * latest_acc_(0) +
                           2.0f * (q_est_(2)*q_est_(3) + q_est_(0)*q_est_(1)) * latest_acc_(1) +
                           (q_est_(0)*q_est_(0) - q_est_(1)*q_est_(1) - q_est_(2)*q_est_(2) + q_est_(3)*q_est_(3)) * latest_acc_(2);
        
        float a_z_true = (a_z_global * 9.81f) - 9.81f; 
        
        X_ekf_(0) += X_ekf_(1) * dt + 0.5f * a_z_true * dt * dt;
        X_ekf_(1) += a_z_true * dt;
        
        Matrix4f F = Matrix4f::Identity();
        F(0, 1) = dt;
        P_ekf_ = F * P_ekf_ * F.transpose() + Q_ekf_;

        if (new_baro_data_) {
            float y = latest_baro_alt_ - X_ekf_(0); 
            Matrix<float, 1, 4> H;
            H << 1.0f, 0.0f, 0.0f, 0.0f; 
            
            float S = (H * P_ekf_ * H.transpose())(0,0) + R_ekf_;
            Vector4f K = P_ekf_ * H.transpose() * (1.0f / S); 
            
            X_ekf_ += K * y;
            P_ekf_ = (Matrix4f::Identity() - K * H) * P_ekf_;
            new_baro_data_ = false;
        }

        float z_ref = 2.0f;
        Vector2f alt_error(z_ref - X_ekf_(0), 0.0f - X_ekf_(1));
        
        float base_thrust = (K_altitude_ * alt_error)(0,0); 
        
        float cos_theta_cos_phi = (q_est_(0)*q_est_(0) - q_est_(1)*q_est_(1) - q_est_(2)*q_est_(2) + q_est_(3)*q_est_(3));
        cos_theta_cos_phi = std::max(0.1f, cos_theta_cos_phi); 
        
        float mass = 0.8f;
        float total_thrust = (base_thrust + (mass * 9.81f)) / cos_theta_cos_phi; 

        auto msg = bzzz_msgs::msg::TargetThrust();
        msg.header.stamp = this->get_clock()->now();
        msg.force_z = total_thrust;
        msg.battery_a = X_ekf_(2);
        msg.battery_b = X_ekf_(3);

        thrust_pub_->publish(msg);
    }

    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<bzzz_msgs::msg::TargetThrust>::SharedPtr thrust_pub_;
    rclcpp::Subscription<sensor_msgs::msg::Imu>::SharedPtr imu_sub_;
    rclcpp::Subscription<bzzz_msgs::msg::PressureData>::SharedPtr baro_sub_;
    MatrixXf K_altitude_;
};

int main(int argc, char * argv[]) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<AltitudeControllerNode>());
    rclcpp::shutdown();
    return 0;
}