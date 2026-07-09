#include <chrono>
#include <memory>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <cmath>

#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/pose_stamped.hpp"

using namespace std::chrono_literals;

class RcNode : public rclcpp::Node
{
public:
    RcNode() : Node("rc_node"), serial_fd_(-1)
    {
        publisher_ = this->create_publisher<geometry_msgs::msg::PoseStamped>("/bzzz/rc_setpoint", 10);

        const char *serial_port = "/dev/ttyAMA0";
        serial_fd_ = open(serial_port, O_RDWR | O_NOCTTY | O_NDELAY);
        
        if (serial_fd_ == -1) {
            RCLCPP_WARN(this->get_logger(), "Failed to open serial port. RC will run in mock mode.");
        } else {
            struct termios options;
            tcgetattr(serial_fd_, &options);
            cfsetispeed(&options, B100000);
            cfsetospeed(&options, B100000);
            options.c_cflag |= (CLOCAL | CREAD);
            options.c_cflag &= ~PARENB;
            options.c_cflag |= CSTOPB;
            options.c_cflag &= ~CSIZE;
            options.c_cflag |= CS8;
            tcsetattr(serial_fd_, TCSANOW, &options);
        }

        timer_ = this->create_wall_timer(
            10ms, std::bind(&RcNode::timer_callback, this));
    }

    ~RcNode() { if (serial_fd_ != -1) close(serial_fd_); }

private:
    void timer_callback()
    {
        auto message = geometry_msgs::msg::PoseStamped();
        message.header.stamp = this->get_clock()->now();
        message.header.frame_id = "world";

        float stick_roll = 0.0f;
        float stick_pitch = 0.0f;
        float stick_yaw = 0.0f;
        float stick_throttle = 0.5f;

        float max_angle = 30.0f * (M_PI / 180.0f);
        
        float ref_roll = stick_roll * max_angle;
        float ref_pitch = stick_pitch * max_angle;
        float ref_yaw = stick_yaw * max_angle;

        float cy = std::cos(ref_yaw * 0.5f);
        float sy = std::sin(ref_yaw * 0.5f);
        float cp = std::cos(ref_pitch * 0.5f);
        float sp = std::sin(ref_pitch * 0.5f);
        float cr = std::cos(ref_roll * 0.5f);
        float sr = std::sin(ref_roll * 0.5f);

        message.pose.orientation.w = cr * cp * cy + sr * sp * sy;
        message.pose.orientation.x = sr * cp * cy - cr * sp * sy;
        message.pose.orientation.y = cr * sp * cy + sr * cp * sy;
        message.pose.orientation.z = cr * cp * sy - sr * sp * cy;

        message.pose.position.z = stick_throttle * 10.0f; 

        publisher_->publish(message);
    }

    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<geometry_msgs::msg::PoseStamped>::SharedPtr publisher_;
    int serial_fd_;
};

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<RcNode>());
    rclcpp::shutdown();
    return 0;
}