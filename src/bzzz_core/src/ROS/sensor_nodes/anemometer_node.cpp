#include <chrono>
#include <memory>
#include <string>
#include <vector>
#include <thread>
#include <mutex>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <sstream>
#include <algorithm>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float32_multi_array.hpp"

using namespace std::chrono_literals;

class AnemometerNode : public rclcpp::Node
{
public:
    AnemometerNode() : Node("anemometer_node"), keep_going_(true), cursor_(0), window_length_(3)
    {
        publisher_ = this->create_publisher<std_msgs::msg::Float32MultiArray>("/bzzz/wind_data", 10);

        values_cache_.resize(7, std::vector<float>(window_length_, 0.0f));

        background_thread_ = std::thread(&AnemometerNode::read_serial_background, this, "/dev/ttyS0", B115200);

        timer_ = this->create_wall_timer(
            100ms, std::bind(&AnemometerNode::timer_callback, this));
    }

    ~AnemometerNode()
    {
        keep_going_ = false;
        if (background_thread_.joinable()) {
            background_thread_.join();
        }
    }

private:
    void read_serial_background(const std::string& port, speed_t baud)
    {
        int fd = open(port.c_str(), O_RDWR | O_NOCTTY | O_NDELAY);
        if (fd == -1) {
            RCLCPP_ERROR(this->get_logger(), "Unable to open serial port %s", port.c_str());
            return;
        }

        struct termios options;
        tcgetattr(fd, &options);
        cfsetispeed(&options, baud);
        cfsetospeed(&options, baud);
        options.c_cflag |= (CLOCAL | CREAD);
        options.c_cflag &= ~PARENB;
        options.c_cflag &= ~CSTOPB;
        options.c_cflag &= ~CSIZE;
        options.c_cflag |= CS8;
        options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG); // Raw input
        tcsetattr(fd, TCSANOW, &options);

        char buffer[256];
        std::string line = "";

        while (keep_going_) {
            int n = read(fd, buffer, sizeof(buffer) - 1);
            if (n > 0) {
                buffer[n] = '\0';
                line += buffer;

                size_t pos;
                while ((pos = line.find('\n')) != std::string::npos) {
                    std::string sentence = line.substr(0, pos);
                    line.erase(0, pos + 1);

                    parse_and_store(sentence);
                }
            } else {
                std::this_thread::sleep_for(10ms); // Prevent 100% CPU usage
            }
        }
        close(fd);
    }

    void parse_and_store(const std::string& sentence)
    {
        std::istringstream iss(sentence);
        std::vector<float> readings;
        float value;
        
        while (iss >> value) {
            readings.push_back(value);
        }

        if (readings.size() == 7) {
            std::lock_guard<std::mutex> lock(data_mutex_);
            for (int i = 0; i < 7; ++i) {
                values_cache_[i][cursor_] = readings[i];
            }
            cursor_ = (cursor_ + 1) % window_length_;
        }
    }

    float get_median(std::vector<float> window)
    {
        std::sort(window.begin(), window.end());
        int n = window.size();
        if (n % 2 == 0) {
            return (window[n / 2 - 1] + window[n / 2]) / 2.0f;
        } else {
            return window[n / 2];
        }
    }

    void timer_callback()
    {
        auto message = std_msgs::msg::Float32MultiArray();
        
        std::lock_guard<std::mutex> lock(data_mutex_);
        
        for (int i = 0; i < 7; ++i) {
            float median_val = get_median(values_cache_[i]);
            message.data.push_back(median_val);
        }

        publisher_->publish(message);
    }

    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<std_msgs::msg::Float32MultiArray>::SharedPtr publisher_;
    
    std::thread background_thread_;
    std::mutex data_mutex_;
    bool keep_going_;
    
    int cursor_;
    int window_length_;
    std::vector<std::vector<float>> values_cache_; 
};

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<AnemometerNode>());
    rclcpp::shutdown();
    return 0;
}