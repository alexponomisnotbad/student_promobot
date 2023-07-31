#include <chrono>
#include <functional>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "std_msgs/msg/integer.hpp"


class MinimalPublisher : public rclcpp::Node
{
  public:
    MinimalPublisher()
    : Node("minimal_publisher"), _ncount(0)
    {
       using std::placeholders::_1;
       using namespace std::chrono_literals;
       _psubscription = this->create_subscription<std_msgs::msg::Integer>(
  "topic", 10, std::bind(&MinimalPublisher::topic_callback, this, std::placeholders::_1));
       _ppublisher = this->create_publisher<std_msgs::msg::String>("topic", 10);
       _ptimer = this->create_wall_timer(
       500ms, std::bind(&MinimalPublisher::timer_callback, this));
      
    }

  private:
    void timer_callback()
    {
      if (_last_data_received == 555) 
      {
         auto message = std_msgs::msg::String();
         message.data = "Hello, I am alive!" + std::to_string(_ncount++);
         RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", message.data.c_str());
        _ppublisher->publish(message);
      }
    }
    void topic_callback(const std_msgs::msg::Integer::SharedPtr msg) const
    {
      _last_data_received = msg->data;
      RCLCPP_INFO(this->get_logger(), "I heard: '%d'", msg->data);
    }
  private:
    rclcpp::TimerBase::SharedPtr _ptimer;
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr _ppublisher;
    rclcpp::Subscription<std_msgs::msg::Integer>::SharedPtr _psubscription;
    size_t _ncount;
};

