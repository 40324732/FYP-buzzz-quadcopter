#include <chrono>
#include <memory>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>

#include "rclcpp/rclcpp.hpp"
#include "bzzz_msgs/msg/range_data.hpp"

using namespace std::chrono_literals;

class ToFNode : public rclcpp::Node
{
public:
    ToFNode() : Node("tof_node"), file_i2c_(-1)
    {
        publisher_ = this->create_publisher<bzzz_msgs::msg::RangeData>("/bzzz/range", 10);

        if ((file_i2c_ = open("/dev/i2c-3", O_RDWR)) < 0) {
            RCLCPP_ERROR(this->get_logger(), "Failed to open the i2c bus");
            return;
        }
        if (ioctl(file_i2c_, I2C_SLAVE, 0x29) < 0) {
            RCLCPP_ERROR(this->get_logger(), "Failed to talk to VL53L0X");
            return;
        }

        write_register(0x88, 0x00);
        write_register(0x80, 0x01);
        write_register(0xFF, 0x01);
        write_register(0x00, 0x00);
        write_register(0x91, read_register(0x91) == 0x3C ? 0x3C : 0x00);
        write_register(0x00, 0x01);
        write_register(0xFF, 0x00);
        write_register(0x80, 0x00);

        write_register(0xFF, 0x01);
        write_register(0x4F, 0x00);
        write_register(0x4E, 0x2C);
        write_register(0xFF, 0x00);
        
        write_register(0x50, 0x01); 
        write_register(0x4F, 0x02); 
        
        write_register(0x00, 0x02); 

        RCLCPP_INFO(this->get_logger(), "VL53L0X Booted in 50Hz Continuous Mode.");

        timer_ = this->create_wall_timer(
            20ms, std::bind(&ToFNode::timer_callback, this));
    }

    ~ToFNode() { if (file_i2c_ >= 0) close(file_i2c_); }

private:
    void write_register(uint8_t reg, uint8_t value) {
        uint8_t buf[2] = {reg, value};
        write(file_i2c_, buf, 2);
    }

    uint8_t read_register(uint8_t reg) {
        write(file_i2c_, &reg, 1);
        uint8_t value;
        read(file_i2c_, &value, 1);
        return value;
    }

    void timer_callback()
    {
        auto message = bzzz_msgs::msg::RangeData();
        message.header.stamp = this->get_clock()->now();
        message.header.frame_id = "tof_link";

        uint8_t reg = 0x14;
        write(file_i2c_, &reg, 1);
        uint8_t data[12];
        if (read(file_i2c_, data, 12) == 12) {
            uint16_t distance_mm = (data[10] << 8) | data[11];
            
            if (distance_mm > 8000 || distance_mm == 20) { // 20 is often an error code on this sensor
                message.distance = -1.0f;
            } else {
                message.distance = (float)distance_mm / 1000.0f;
            }
        } else {
            message.distance = -1.0f;
        }

        publisher_->publish(message);
    }

    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<bzzz_msgs::msg::RangeData>::SharedPtr publisher_;
    int file_i2c_;
};

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<ToFNode>());
    rclcpp::shutdown();
    return 0;
}