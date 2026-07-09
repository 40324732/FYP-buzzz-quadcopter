#include <chrono>
#include <memory>
#include <cmath>
#include <Eigen/Dense>

#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/imu.hpp"
#include "std_msgs/msg/float32_multi_array.hpp"
#include "bzzz_msgs/msg/target_thrust.hpp"

using std::placeholders::_1;
using namespace Eigen;

class AttitudeControllerNode : public rclcpp::Node
{
public:
    AttitudeControllerNode() : Node("attitude_controller_node")
    {
        pwm_pub_ = this->create_publisher<std_msgs::msg::Float32MultiArray>("/bzzz/actuator_pwm", 10);
        
        imu_sub_ = this->create_subscription<sensor_msgs::msg::Imu>(
            "/bzzz/imu", rclcpp::SensorDataQoS(), std::bind(&AttitudeControllerNode::imu_callback, this, _1));
            
        thrust_sub_ = this->create_subscription<bzzz_msgs::msg::TargetThrust>(
            "/bzzz/target_thrust", 10, std::bind(&AttitudeControllerNode::thrust_callback, this, _1));

        q_est_ << 1.0, 0.0, 0.0, 0.0; 

        K_attitude_ = MatrixXf(3, 6);
        K_attitude_ << 5.0, 0.0, 0.0, 0.5, 0.0, 0.0,
                       0.0, 5.0, 0.0, 0.0, 0.5, 0.0,
                       0.0, 0.0, 8.0, 0.0, 0.0, 0.8;

        mixer_ = MatrixXf(4, 4); 
        mixer_ << 1.0, -1.0,  1.0,  1.0, 
                  1.0,  1.0, -1.0,  1.0,
                  1.0,  1.0,  1.0, -1.0,
                  1.0, -1.0, -1.0, -1.0; 
    }

private:
    Vector4f q_est_; 
    
    float latest_force_z_ = 0.0f;
    float latest_bat_a_ = 1.0f;
    float latest_bat_b_ = 0.0f;

    void thrust_callback(const bzzz_msgs::msg::TargetThrust::SharedPtr msg)
    {
        latest_force_z_ = msg->force_z;
        latest_bat_a_ = msg->battery_a;
        latest_bat_b_ = msg->battery_b;
    }

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

        Vector4f q_ref(1.0f, 0.0f, 0.0f, 0.0f);
        
        Vector3f q_err_vec(
            q_ref(0)*(-q_est_(1)) + q_ref(1)*q_est_(0) + q_ref(2)*(-q_est_(3)) - q_ref(3)*(-q_est_(2)),
            q_ref(0)*(-q_est_(2)) - q_ref(1)*(-q_est_(3)) + q_ref(2)*q_est_(0) + q_ref(3)*(-q_est_(1)),
            q_ref(0)*(-q_est_(3)) + q_ref(1)*(-q_est_(2)) - q_ref(2)*(-q_est_(1)) + q_ref(3)*q_est_(0)
        );

        VectorXf state_vector(6);
        state_vector << (2.0f * q_err_vec), gyro;
        
        Vector3f torques = K_attitude_ * state_vector; 

        Vector4f control_efforts;
        control_efforts << latest_force_z_, torques(0), torques(1), torques(2);
        
        Vector4f raw_forces = mixer_ * control_efforts; 
        
        std_msgs::msg::Float32MultiArray pwm_msg;
        for(int i=0; i<4; i++) {
            float pwm = (raw_forces(i) - latest_bat_b_) / latest_bat_a_;
            
            pwm = std::max(1000.0f, std::min(2000.0f, pwm));
            pwm_msg.data.push_back(pwm);
        }

        pwm_pub_->publish(pwm_msg);
    }

    rclcpp::Publisher<std_msgs::msg::Float32MultiArray>::SharedPtr pwm_pub_;
    rclcpp::Subscription<sensor_msgs::msg::Imu>::SharedPtr imu_sub_;
    rclcpp::Subscription<bzzz_msgs::msg::TargetThrust>::SharedPtr thrust_sub_;
    MatrixXf K_attitude_, mixer_;
};

int main(int argc, char * argv[]) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<AttitudeControllerNode>());
    rclcpp::shutdown();
    return 0;
}