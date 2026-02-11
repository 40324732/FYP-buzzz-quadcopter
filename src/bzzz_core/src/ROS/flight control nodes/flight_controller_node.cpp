#include <chrono>
#include <memory>
#include <cmath>
#include <Eigen/Dense>

#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/imu.hpp"
#include "geometry_msgs/msg/quaternion.hpp"
#include "std_msgs/msg/float32_multi_array.hpp"
#include "bzzz_msgs/msg/pressure_data.hpp"
#include "bzzz_msgs/msg/range_data.hpp"

using std::placeholders::_1;
using namespace Eigen;

class FlightControllerNode : public rclcpp::Node
{
public:
    FlightControllerNode() : Node("flight_controller_node")
    {
        pwm_pub_ = this->create_publisher<std_msgs::msg::Float32MultiArray>("/bzzz/actuator_pwm", 10);
        
        imu_sub_ = this->create_subscription<sensor_msgs::msg::Imu>(
            "/bzzz/imu", rclcpp::SensorDataQoS(), std::bind(&FlightControllerNode::imu_callback, this, _1));
            
        baro_sub_ = this->create_subscription<bzzz_msgs::msg::PressureData>(
            "/bzzz/pressure", 10, std::bind(&FlightControllerNode::baro_callback, this, _1));

        X_ekf_ << 0.0, 0.0, 1.0, 0.0;
        P_ekf_ = Matrix4f::Identity(); 
        Q_ekf_ = Matrix4f::Identity() * 0.001;
        R_ekf_ = 0.5;
        
        q_est_ << 1.0, 0.0, 0.0, 0.0;

        K_attitude_ = MatrixXf(3, 6);
        K_attitude_ << 5.0, 0.0, 0.0, 0.5, 0.0, 0.0,
                       0.0, 5.0, 0.0, 0.0, 0.5, 0.0,
                       0.0, 0.0, 8.0, 0.0, 0.0, 0.8;

        K_altitude_ = MatrixXf(1, 2);
        K_altitude_ << 3.5, 1.2;

        mixer_ = MatrixXf(4, 4); 
        mixer_ << 1.0, -1.0,  1.0,  1.0, 
                  1.0,  1.0, -1.0,  1.0,
                  1.0,  1.0,  1.0, -1.0,
                  1.0, -1.0, -1.0, -1.0; 
    }

private:
    Vector4f X_ekf_; 
    Matrix4f P_ekf_, Q_ekf_;
    float R_ekf_;
    float latest_baro_alt_ = 0.0;
    bool new_baro_data_ = false;

    Vector4f q_est_;

    void imu_callback(const sensor_msgs::msg::Imu::SharedPtr msg)
    {
        float dt = 0.005f;
        Vector3f acc(msg->linear_acceleration.x, msg->linear_acceleration.y, msg->linear_acceleration.z);
        Vector3f gyro(msg->angular_velocity.x, msg->angular_velocity.y, msg->angular_velocity.z);

        float q1 = q_est_(0), q2 = q_est_(1), q3 = q_est_(2), q4 = q_est_(3);
        acc.normalize();
        
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
            0.5f * (-q2 * gyro(0) - q3 * gyro(1) - q4 * gyro(2)) - beta * step(0),
            0.5f * ( q1 * gyro(0) + q3 * gyro(2) - q4 * gyro(1)) - beta * step(1),
            0.5f * ( q1 * gyro(1) - q2 * gyro(2) + q4 * gyro(0)) - beta * step(2),
            0.5f * ( q1 * gyro(2) + q2 * gyro(1) - q3 * gyro(0)) - beta * step(3)
        );

        q_est_ += q_dot * dt;
        q_est_.normalize();

        float a_z_global = 2.0f * (q_est_(1)*q_est_(3) - q_est_(0)*q_est_(2)) * acc(0) +
                           2.0f * (q_est_(2)*q_est_(3) + q_est_(0)*q_est_(1)) * acc(1) +
                           (q_est_(0)*q_est_(0) - q_est_(1)*q_est_(1) - q_est_(2)*q_est_(2) + q_est_(3)*q_est_(3)) * acc(2);
        
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
            
            float S = H * P_ekf_ * H.transpose() + R_ekf_;
            Vector4f K = P_ekf_ * H.transpose() * (1.0f / S);
            
            X_ekf_ += K * y;
            P_ekf_ = (Matrix4f::Identity() - K * H) * P_ekf_;
            new_baro_data_ = false;
        }

        Vector4f q_ref(1.0f, 0.0f, 0.0f, 0.0f);
        
        Vector3f q_err_vec(
            q_ref(0)*(-q_est_(1)) + q_ref(1)*q_est_(0) + q_ref(2)*(-q_est_(3)) - q_ref(3)*(-q_est_(2)),
            q_ref(0)*(-q_est_(2)) - q_ref(1)*(-q_est_(3)) + q_ref(2)*q_est_(0) + q_ref(3)*(-q_est_(1)),
            q_ref(0)*(-q_est_(3)) + q_ref(1)*(-q_est_(2)) - q_ref(2)*(-q_est_(1)) + q_ref(3)*q_est_(0)
        );

        VectorXf state_vector(6);
        state_vector << (2.0f * q_err_vec), gyro;
        
        Vector3f torques = K_attitude_ * state_vector; 

        float z_ref = 2.0f;
        Vector2f alt_error(z_ref - X_ekf_(0), 0.0f - X_ekf_(1));
        
        float base_thrust = (K_altitude_ * alt_error)(0,0); 
        
        float cos_theta_cos_phi = (q_est_(0)*q_est_(0) - q_est_(1)*q_est_(1) - q_est_(2)*q_est_(2) + q_est_(3)*q_est_(3));
        cos_theta_cos_phi = std::max(0.1f, cos_theta_cos_phi);
        
        float mass = 0.8f; // kg
        float total_thrust = (base_thrust + (mass * 9.81f)) / cos_theta_cos_phi; 

        Vector4f control_efforts;
        control_efforts << total_thrust, torques(0), torques(1), torques(2);
        
        Vector4f raw_forces = mixer_ * control_efforts; 
        
        float a_t = X_ekf_(2);
        float b_t = X_ekf_(3);
        
        std_msgs::msg::Float32MultiArray pwm_msg;
        for(int i=0; i<4; i++) {
            float pwm = (raw_forces(i) - b_t) / a_t;
            pwm = std::max(1000.0f, std::min(2000.0f, pwm));
            pwm_msg.data.push_back(pwm);
        }

        pwm_pub_->publish(pwm_msg);
    }

    void baro_callback(const bzzz_msgs::msg::PressureData::SharedPtr msg)
    {
        latest_baro_alt_ = msg->relative_altitude;
        new_baro_data_ = true; 
    }

    rclcpp::Publisher<std_msgs::msg::Float32MultiArray>::SharedPtr pwm_pub_;
    rclcpp::Subscription<sensor_msgs::msg::Imu>::SharedPtr imu_sub_;
    rclcpp::Subscription<bzzz_msgs::msg::PressureData>::SharedPtr baro_sub_;
    MatrixXf K_attitude_, K_altitude_, mixer_;
};

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<FlightControllerNode>());
    rclcpp::shutdown();
    return 0;
}