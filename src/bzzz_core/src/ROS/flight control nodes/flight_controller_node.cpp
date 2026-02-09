#include <chrono>
#include <memory>
#include <Eigen/Dense> // Crucial for LQR and EKF matrix math

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
        pwm_pub_ = this->create_publisher<std_msgs::msg::Float32MultiArray>("/bzzz/MotorCommands", 10);
        
        imu_sub_ = this->create_subscription<sensor_msgs::msg::Imu>(
            "/bzzz/imu", rclcpp::SensorDataQoS(), std::bind(&FlightControllerNode::imu_callback, this, _1));
            
        baro_sub_ = this->create_subscription<bzzz_msgs::msg::PressureData>(
            "/bzzz/pressure", 10, std::bind(&FlightControllerNode::baro_callback, this, _1));
            
        tof_sub_ = this->create_subscription<bzzz_msgs::msg::RangeData>(
            "/bzzz/range", 10, std::bind(&FlightControllerNode::tof_callback, this, _1));
            
        // TODO: subscribe to RC setpoint

        X_ekf_ = Vector4f::Zero(); //
        P_ekf_ = Matrix4f::Identity(); 
        
        K_attitude_ = MatrixXf(3, 6);
        K_attitude_ << 1.0, 0.0, 0.0, 0.1, 0.0, 0.0,
                       0.0, 1.0, 0.0, 0.0, 0.1, 0.0,
                       0.0, 0.0, 1.0, 0.0, 0.0, 0.1;

        K_altitude_ = MatrixXf(1, 2);
        K_altitude_ << 2.0, 0.5;

        mixer_ = MatrixXf(4, 4); 
        mixer_ << 1.0, -1.0,  1.0,  1.0, 
                  1.0,  1.0, -1.0,  1.0,
                  1.0,  1.0,  1.0, -1.0,
                  1.0, -1.0, -1.0, -1.0; 
    }

private:
    Vector4f X_ekf_; 
    Matrix4f P_ekf_;
    float latest_baro_alt_ = 0.0;
    float latest_tof_alt_ = -1.0;
    bool new_baro_data_ = false;

    void imu_callback(const sensor_msgs::msg::Imu::SharedPtr msg)
    {
        // TODO: Pass msg->angular_velocity and msg->linear_acceleration into a Madgwick class
        Vector4f q_est(1.0, 0.0, 0.0, 0.0);
        Vector3f rates(msg->angular_velocity.x, msg->angular_velocity.y, msg->angular_velocity.z);

        float dt = 0.005;
        float a_z = msg->linear_acceleration.z - 9.81; 
        
        X_ekf_(0) += X_ekf_(1) * dt + 0.5 * a_z * dt * dt;
        X_ekf_(1) += a_z * dt;
        
        // TODO: Update P_ekf_ covariance matrix

        if (new_baro_data_) {
            float y = latest_baro_alt_ - X_ekf_(0);
            // TODO: Calculate Kalman Gain (K) using Jacobian (H) and update X_ekf_ and P_ekf_
            new_baro_data_ = false;
        }

        Vector3f attitude_error(0.0, 0.0, 0.0);
        Vector3f rate_error(0.0, 0.0, 0.0);
        
        VectorXf state_vector(6);
        state_vector << attitude_error, rate_error;
        
        Vector3f torques = K_attitude_ * state_vector;

        float z_ref = 5.0;
        float z_dot_ref = 0.0;
        Vector2f alt_error(z_ref - X_ekf_(0), z_dot_ref - X_ekf_(1));
        
        float base_thrust = K_altitude_ * alt_error; 
        
        float mass = 1.0; // kg
        float total_thrust = (base_thrust + (mass * 9.81));

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

    void tof_callback(const bzzz_msgs::msg::RangeData::SharedPtr msg)
    {
        latest_tof_alt_ = msg->distance;
    }

    rclcpp::Publisher<std_msgs::msg::Float32MultiArray>::SharedPtr pwm_pub_;
    rclcpp::Subscription<sensor_msgs::msg::Imu>::SharedPtr imu_sub_;
    rclcpp::Subscription<bzzz_msgs::msg::PressureData>::SharedPtr baro_sub_;
    rclcpp::Subscription<bzzz_msgs::msg::RangeData>::SharedPtr tof_sub_;
};

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<FlightControllerNode>());
    rclcpp::shutdown();
    return 0;
}