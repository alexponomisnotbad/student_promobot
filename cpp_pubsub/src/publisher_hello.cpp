#include <iostream>
#include <chrono>
#include <thread>
#include <functional>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

int c_timeout_ms;
class MinimalPublisher : public rclcpp::Node
{
public:

  static const char* _topic = "topic"
  static const size_t _size = 10
  MinimalPublisher()
  : Node("minimal_publisher"), _ncount(0)
  {
    _ppublisher = this->create_publisher<std_msgs::msg::String>(_topic, _size);
    _ptimer = this->create_wall_timer(
    std::chrono::seconds(c_timeout_ms) , std::bind(&MinimalPublisher:: _timer_callback, this));
  }
  private:
    void timer_callback()
    {
      auto message = std_msgs::msg::String();
      message.data = "Hello, I am alive! ";
      RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", message.data.c_str());
      _ppublisher->publish(message);
      std::this_thread::sleep_for(std::chrono::seconds(c_timeout_ms));
    }
    rclcpp::TimerBase::SharedPtr _ptimer;
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr _ppublisher;
    size_t _ncount;
};
int main(int argc, char * argv[])
{
  c_timeout_ms = 2
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalPublisher>());
  rclcpp::shutdown();
    return 0;
}
