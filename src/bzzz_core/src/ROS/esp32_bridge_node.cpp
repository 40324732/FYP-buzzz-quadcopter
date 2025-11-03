#include "rclcpp/rclcpp.hpp"
#include "bzzz_msgs/msg/motor_commands.hpp"
#include "bzzz_msgs/msg/sensor_suite.hpp"

#include <fcntl.h>   
#include <termios.h> 
#include <unistd.h>  
#include <cstring>   


#pragma pack(push, 1)
struct SerialTxPacket {
  uint8_t header[2] = {0xAA, 0xBB};
  float thrust;
  float roll;
  float pitch;
  float yaw_rate;
  uint8_t footer = 0xFF;
};
#pragma pack(pop)

class Esp32BridgeNode : public rclcpp::Node
{
public:
  Esp32BridgeNode() : Node("esp32_bridge_node")
  {
    serial_fd_ = open("/dev/ttyUSB0", O_RDWR | O_NOCTTY | O_NDELAY);
    
    if (serial_fd_ < 0) {
      RCLCPP_ERROR(this->get_logger(), "Failed to open serial port! Are you plugged in?");
    } else {
      configure_serial_port();
      RCLCPP_INFO(this->get_logger(), "Serial port opened successfully at 115200 baud.");
    }

    motor_sub_ = this->create_subscription<bzzz_msgs::msg::MotorCommands>(
      "motor_commands", 10, std::bind(&Esp32BridgeNode::motor_callback, this, std::placeholders::_1));

    sensor_pub_ = this->create_publisher<bzzz_msgs::msg::SensorSuite>("sensor_suite", 10);
  }

  ~Esp32BridgeNode() {
    if (serial_fd_ >= 0) close(serial_fd_);
  }

private:
  int serial_fd_;

  void configure_serial_port()
  {
    struct termios tty;
    tcgetattr(serial_fd_, &tty);

    cfsetispeed(&tty, B115200);
    cfsetospeed(&tty, B115200);

    tty.c_cflag &= ~PARENB; 
    tty.c_cflag &= ~CSTOPB; 
    tty.c_cflag &= ~CSIZE;  
    tty.c_cflag |= CS8;     
    
    tty.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG); 
    tty.c_oflag &= ~OPOST;

    tcsetattr(serial_fd_, TCSANOW, &tty);
  }

  void motor_callback(const bzzz_msgs::msg::MotorCommands::SharedPtr msg)
  {
    if (serial_fd_ < 0) return;

    SerialTxPacket pkt;
    pkt.thrust = msg->thrust;
    pkt.roll = msg->roll;
    pkt.pitch = msg->pitch;
    pkt.yaw_rate = msg->yaw_rate;

    int packet_size = sizeof(SerialTxPacket);

    int bytes_written = write(serial_fd_, &pkt, packet_size);

    if (bytes_written > 0) {
      RCLCPP_INFO(this->get_logger(), "Sent %d bytes to ESP32.", bytes_written);
    }
  }

  rclcpp::Subscription<bzzz_msgs::msg::MotorCommands>::SharedPtr motor_sub_;
  rclcpp::Publisher<bzzz_msgs::msg::SensorSuite>::SharedPtr sensor_pub_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<Esp32BridgeNode>());
  rclcpp::shutdown();
  return 0;
}