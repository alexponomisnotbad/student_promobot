#include <iostream>
#include <chrono>
#include <thread>
#include <functional>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

const uint16_t c_timeout_ms = 2;
class MinimalPublisher : public rclcpp::Node
{
public:

  MinimalPublisher()
  : Node("minimal_publisher")
  {
    using namespace std::chrono_literals;
    _ptimer = this->create_wall_timer(
    std::chrono::seconds(c_timeout_ms) , std::bind(&MinimalPublisher:: timer_callback, this));
  }
  private:
    void timer_callback()
    {
      auto message = std_msgs::msg::String();
      message.data = "Hello, I am alive! ";
      RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", message.data.c_str());
      std::this_thread::sleep_for(std::chrono::seconds(c_timeout_ms));
    }
  private:
    rclcpp::TimerBase::SharedPtr _ptimer;
};
int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalPublisher>());
  rclcpp::shutdown();
    return 0;
}
