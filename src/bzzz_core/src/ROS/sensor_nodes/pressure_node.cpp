#include <chrono>
#include <memory>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include <cmath>
#include <cstdint>

#include "rclcpp/rclcpp.hpp"
#include "bzzz_msgs/msg/pressure_data.hpp"

using namespace std::chrono_literals;

class PressureNode : public rclcpp::Node
{
public:
    PressureNode() : Node("pressure_node"), file_i2c_(-1)
    {
        publisher_ = this->create_publisher<bzzz_msgs::msg::PressureData>("/bzzz/pressure", 10);
        
        if ((file_i2c_ = open("/dev/i2c-1", O_RDWR)) < 0) {
            RCLCPP_ERROR(this->get_logger(), "Failed to open the i2c bus");
            return;
        }
        if (ioctl(file_i2c_, I2C_SLAVE, 0x77) < 0) {
            RCLCPP_ERROR(this->get_logger(), "Failed to talk to BMP180");
            return;
        }

        uint8_t reg = 0xAA;
        write(file_i2c_, &reg, 1);
        uint8_t cal_data[22];
        if (read(file_i2c_, cal_data, 22) != 22) {
            RCLCPP_ERROR(this->get_logger(), "Failed to read calibration data");
            return;
        }

        ac1_ = (int16_t)(cal_data[0] << 8 | cal_data[1]);
        ac2_ = (int16_t)(cal_data[2] << 8 | cal_data[3]);
        ac3_ = (int16_t)(cal_data[4] << 8 | cal_data[5]);
        ac4_ = (uint16_t)(cal_data[6] << 8 | cal_data[7]);
        ac5_ = (uint16_t)(cal_data[8] << 8 | cal_data[9]);
        ac6_ = (uint16_t)(cal_data[10] << 8 | cal_data[11]);
        b1_  = (int16_t)(cal_data[12] << 8 | cal_data[13]);
        b2_  = (int16_t)(cal_data[14] << 8 | cal_data[15]);
        mb_  = (int16_t)(cal_data[16] << 8 | cal_data[17]);
        mc_  = (int16_t)(cal_data[18] << 8 | cal_data[19]);
        md_  = (int16_t)(cal_data[20] << 8 | cal_data[21]);

        RCLCPP_INFO(this->get_logger(), "BMP180 Calibrated Successfully.");

        timer_ = this->create_wall_timer(
            50ms, std::bind(&PressureNode::timer_callback, this));
    }

    ~PressureNode() { if (file_i2c_ >= 0) close(file_i2c_); }

private:
    void timer_callback()
    {
        uint8_t temp_cmd[2] = {0xF4, 0x2E};
        write(file_i2c_, temp_cmd, 2);
        usleep(5000); 
        
        uint8_t reg_msb = 0xF6;
        write(file_i2c_, &reg_msb, 1);
        uint8_t temp_data[2];
        read(file_i2c_, temp_data, 2);
        int32_t ut = (temp_data[0] << 8) + temp_data[1];

        uint8_t pres_cmd[2] = {0xF4, 0x34 + (3 << 6)};
        write(file_i2c_, pres_cmd, 2);
        usleep(26000); 
        
        write(file_i2c_, &reg_msb, 1);
        uint8_t pres_data[3];
        read(file_i2c_, pres_data, 3);
        int32_t up = ((pres_data[0] << 16) + (pres_data[1] << 8) + pres_data[2]) >> (8 - 3);

        int32_t x1 = ((ut - ac6_) * ac5_) >> 15;
        int32_t x2 = (mc_ << 11) / (x1 + md_);
        int32_t b5 = x1 + x2;

        int32_t b6 = b5 - 4000;
        int32_t x1_p = (b2_ * (b6 * b6 >> 12)) >> 11;
        int32_t x2_p = (ac2_ * b6) >> 11;
        int32_t x3 = x1_p + x2_p;
        int32_t b3 = (((ac1_ * 4 + x3) << 3) + 2) >> 2;

        x1_p = (ac3_ * b6) >> 13;
        x2_p = (b1_ * (b6 * b6 >> 12)) >> 16;
        x3 = ((x1_p + x2_p) + 2) >> 2;
        uint32_t b4 = (ac4_ * (uint32_t)(x3 + 32768)) >> 15;
        uint32_t b7 = ((uint32_t)up - b3) * (50000 >> 3);

        int32_t p = (b7 < 0x80000000) ? (b7 * 2) / b4 : (b7 / b4) * 2;
        x1_p = (p >> 8) * (p >> 8);
        x1_p = (x1_p * 3038) >> 16;
        x2_p = (-7357 * p) >> 16;
        p = p + ((x1_p + x2_p + 3791) >> 4); // Final Pressure in Pascals

        auto message = bzzz_msgs::msg::PressureData();
        message.header.stamp = this->get_clock()->now();
        message.header.frame_id = "baro_link";
        
        float sea_level_pressure = 101325.0f; // Can be updated via param later
        float altitude = 44330.0f * (1.0f - std::pow((float)p / sea_level_pressure, 1.0f / 5.255f));

        message.pressure = (float)p;
        message.relative_altitude = altitude;

        publisher_->publish(message);
    }

    int16_t ac1_, ac2_, ac3_, b1_, b2_, mb_, mc_, md_;
    uint16_t ac4_, ac5_, ac6_;

    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<bzzz_msgs::msg::PressureData>::SharedPtr publisher_;
    int file_i2c_;
};

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<PressureNode>());
    rclcpp::shutdown();
    return 0;
}