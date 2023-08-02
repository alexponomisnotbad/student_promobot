#include <chrono>
#include <functional>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "std_msgs/msg/int32.hpp"
using std::placeholders::_1;

class MinimalPublisher : public rclcpp::Node
{
  public:
    MinimalPublisher()
    : Node("minimal_publisher"), _ncount(1)
    {
       using namespace std::chrono_literals;
       _psubscription = this->create_subscription<std_msgs::msg::Int32>(
  "topic", 10, std::bind(&MinimalPublisher::topic_callback, this, std::placeholders::_1));
      
    }

  private:
    void topic_callback(const std_msgs::msg::Int32::SharedPtr msg) const
    {
    auto _last_data_received  = std_msgs::msg::Int32();
      _last_data_received = msg->data;
      if (_last_data_received == (0 + _ncount++)) 
      { 
         RCLCPP_INFO(this->get_logger(), "I heard: '%d'", msg->data);
         auto message = std_msgs::msg::String();
         message.data = "Hello, I am alive!" + std::to_string(_ncount++);
         RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", message.data.c_str());
      }
    }
  private:
    rclcpp::Subscription<std_msgs::msg::Int32>::SharedPtr _psubscription;
    size_t _ncount;
};

