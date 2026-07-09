#include <chrono>
#include <memory>
#include <fstream>
#include <string>
#include <iomanip>
#include <ctime>

#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/imu.hpp"
#include "geometry_msgs/msg/pose_stamped.hpp"
#include "std_msgs/msg/float32_multi_array.hpp"
#include "bzzz_msgs/msg/pressure_data.hpp"
#include "bzzz_msgs/msg/range_data.hpp"

using std::placeholders::_1;
using namespace std::chrono_literals;

class DataLoggerNode : public rclcpp::Node
{
public:
    DataLoggerNode() : Node("data_logger_node")
    {
        imu_sub_ = this->create_subscription<sensor_msgs::msg::Imu>(
            "/bzzz/imu", 10, std::bind(&DataLoggerNode::imu_callback, this, _1));
            
        baro_sub_ = this->create_subscription<bzzz_msgs::msg::PressureData>(
            "/bzzz/pressure", 10, std::bind(&DataLoggerNode::baro_callback, this, _1));
            
        tof_sub_ = this->create_subscription<bzzz_msgs::msg::RangeData>(
            "/bzzz/range", 10, std::bind(&DataLoggerNode::tof_callback, this, _1));
            
        rc_sub_ = this->create_subscription<geometry_msgs::msg::PoseStamped>(
            "/bzzz/rc_setpoint", 10, std::bind(&DataLoggerNode::rc_callback, this, _1));
            
        pwm_sub_ = this->create_subscription<std_msgs::msg::Float32MultiArray>(
            "/bzzz/actuator_pwm", 10, std::bind(&DataLoggerNode::pwm_callback, this, _1));

        auto t = std::time(nullptr);
        auto tm = *std::localtime(&t);
        std::ostringstream oss;
        oss << "/home/ubuntu/bzzz_flight_log_" << std::put_time(&tm, "%Y-%m-%d_%H-%M-%S") << ".csv";
        
        log_file_.open(oss.str());
        if (!log_file_.is_open()) {
            RCLCPP_ERROR(this->get_logger(), "Failed to open log file: %s", oss.str().c_str());
        } else {
            log_file_ << "Timestamp,"
                      << "AccX,AccY,AccZ,"
                      << "GyroX,GyroY,GyroZ,"
                      << "BaroAlt,ToFDist,"
                      << "TargetAlt,"
                      << "PWM1,PWM2,PWM3,PWM4\n";
            RCLCPP_INFO(this->get_logger(), "Logging data to: %s", oss.str().c_str());
        }

        timer_ = this->create_wall_timer(
            20ms, std::bind(&DataLoggerNode::timer_callback, this));
    }

    ~DataLoggerNode()
    {
        if (log_file_.is_open()) {
            log_file_.close();
            RCLCPP_INFO(this->get_logger(), "Log file saved and closed successfully.");
        }
    }

private:
    float acc_[3] = {0.0f, 0.0f, 0.0f};
    float gyro_[3] = {0.0f, 0.0f, 0.0f};
    float baro_alt_ = 0.0f;
    float tof_dist_ = -1.0f;
    float target_alt_ = 0.0f;
    float pwm_[4] = {1000.0f, 1000.0f, 1000.0f, 1000.0f};

    void imu_callback(const sensor_msgs::msg::Imu::SharedPtr msg) {
        acc_[0] = msg->linear_acceleration.x;
        acc_[1] = msg->linear_acceleration.y;
        acc_[2] = msg->linear_acceleration.z;
        gyro_[0] = msg->angular_velocity.x;
        gyro_[1] = msg->angular_velocity.y;
        gyro_[2] = msg->angular_velocity.z;
    }

    void baro_callback(const bzzz_msgs::msg::PressureData::SharedPtr msg) {
        baro_alt_ = msg->relative_altitude;
    }

    void tof_callback(const bzzz_msgs::msg::RangeData::SharedPtr msg) {
        tof_dist_ = msg->distance;
    }

    void rc_callback(const geometry_msgs::msg::PoseStamped::SharedPtr msg) {
        target_alt_ = msg->pose.position.z;
    }

    void pwm_callback(const std_msgs::msg::Float32MultiArray::SharedPtr msg) {
        if (msg->data.size() >= 4) {
            for (int i = 0; i < 4; i++) {
                pwm_[i] = msg->data[i];
            }
        }
    }

    void timer_callback()
    {
        if (!log_file_.is_open()) return;

        auto now = std::chrono::system_clock::now();
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;
        auto timer = std::chrono::system_clock::to_time_t(now);
        std::tm bt = *std::localtime(&timer);

        log_file_ << std::put_time(&bt, "%H:%M:%S") << '.' << std::setfill('0') << std::setw(3) << ms.count() << ","
                  << acc_[0] << "," << acc_[1] << "," << acc_[2] << ","
                  << gyro_[0] << "," << gyro_[1] << "," << gyro_[2] << ","
                  << baro_alt_ << ","
                  << tof_dist_ << ","
                  << target_alt_ << ","
                  << pwm_[0] << "," << pwm_[1] << "," << pwm_[2] << "," << pwm_[3] << "\n";
    }

    std::ofstream log_file_;
    rclcpp::TimerBase::SharedPtr timer_;
    
    rclcpp::Subscription<sensor_msgs::msg::Imu>::SharedPtr imu_sub_;
    rclcpp::Subscription<bzzz_msgs::msg::PressureData>::SharedPtr baro_sub_;
    rclcpp::Subscription<bzzz_msgs::msg::RangeData>::SharedPtr tof_sub_;
    rclcpp::Subscription<geometry_msgs::msg::PoseStamped>::SharedPtr rc_sub_;
    rclcpp::Subscription<std_msgs::msg::Float32MultiArray>::SharedPtr pwm_sub_;
};

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<DataLoggerNode>());
    rclcpp::shutdown();
    return 0;
}