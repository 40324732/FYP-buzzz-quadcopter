#include <chrono>
#include <memory>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include <cmath>

#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/imu.hpp"

using namespace std::chrono_literals;

class ImuNode : public rclcpp::Node
{
public:
    ImuNode() : Node("imu_node"), file_i2c_(-1)
    {
        publisher_ = this->create_publisher<sensor_msgs::msg::Imu>("/bzzz/imu", rclcpp::SensorDataQoS());

        if ((file_i2c_ = open("/dev/i2c-1", O_RDWR)) < 0) {
            RCLCPP_ERROR(this->get_logger(), "Failed to open i2c bus");
            return;
        }
        
        if (ioctl(file_i2c_, I2C_SLAVE, 0x69) < 0) {
            RCLCPP_ERROR(this->get_logger(), "Failed to talk to ICM-20948");
            return;
        }

        uint8_t wake_cmd[2] = {0x06, 0x01};
        write(file_i2c_, wake_cmd, 2);
        usleep(10000); // Wait 10ms for startup

        timer_ = this->create_wall_timer(
            5ms, std::bind(&ImuNode::timer_callback, this));
    }

    ~ImuNode() { if (file_i2c_ >= 0) close(file_i2c_); }

private:
    void timer_callback()
    {
        auto message = sensor_msgs::msg::Imu();
        message.header.stamp = this->get_clock()->now();
        message.header.frame_id = "imu_link";

        uint8_t reg = 0x2D;
        write(file_i2c_, &reg, 1);
        
        uint8_t data[14];
        if (read(file_i2c_, data, 14) != 14) {
            RCLCPP_WARN(this->get_logger(), "I2C read error");
            return;
        }

        float accel_scale = 9.81f / 16384.0f;
        message.linear_acceleration.x = (int16_t(data[0] << 8 | data[1])) * accel_scale;
        message.linear_acceleration.y = (int16_t(data[2] << 8 | data[3])) * accel_scale;
        message.linear_acceleration.z = (int16_t(data[4] << 8 | data[5])) * accel_scale;

        float gyro_scale = (M_PI / 180.0f) / 131.0f;
        message.angular_velocity.x = (int16_t(data[8] << 8 | data[9])) * gyro_scale;
        message.angular_velocity.y = (int16_t(data[10] << 8 | data[11])) * gyro_scale;
        message.angular_velocity.z = (int16_t(data[12] << 8 | data[13])) * gyro_scale;

        publisher_->publish(message);
    }

    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<sensor_msgs::msg::Imu>::SharedPtr publisher_;
    int file_i2c_;
};

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<ImuNode>());
    rclcpp::shutdown();
    return 0;
}