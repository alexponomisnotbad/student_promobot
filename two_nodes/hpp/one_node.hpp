#include <chrono>
#include <functional>
#include <memory>
#include <string>
#include <unistd.h>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "std_msgs/msg/int32.hpp"

static constexpr char * c_topic = "publisher";
static constexpr char * c_subtopic = "subscriber";
static constexpr char * c_timer_parameter = "timer_parameter";
static constexpr char * c_queue_parameter = "queue_parameter";


class OneNode : public rclcpp::Node
{
public:
  OneNode()
  : Node("first_node"), _ncount(0)
  {
    this->declare_parameter(c_timer_parameter, timer_interval_sec_prm);
    this->declare_parameter(c_queue_parameter, queue_size_prm);
    queue_size = this->get_parameter(c_queue_parameter).as_int();
    _ppublisher = this->create_publisher<std_msgs::msg::String>(c_topic, queue_size);
    _psubscription = this->create_subscription<std_msgs::msg::Int32>(
    c_subtopic, queue_size, std::bind(&OneNode::сallback, this, std::placeholders::_1));
    timer_interval_sec = this->get_parameter(c_timer_parameter).as_int();
    _ptimer = this->create_wall_timer(
      std::chrono::seconds(timer_interval_sec), std::bind(&OneNode::timerCallback, this));
  }

public:
const uint8_t queue_size_prm = 10;
const uint8_t timer_interval_sec_prm = 10;
uint8_t queue_size = 0;
uint8_t timer_interval_sec = 0;

private:
  void timerCallback()
  {
    auto message = std_msgs::msg::String();
    message.data = "Hello, I'm alive! " + std::to_string(_ncount++);
    RCLCPP_INFO(this->get_logger(), message.data.c_str());
    _ppublisher->publish(message);
  }
  void сallback(const std_msgs::msg::Int32 & msg) const
  {
    RCLCPP_INFO(this->get_logger(), "I heard: '%s'", std::to_string(msg.data).c_str());
  }

private:
  rclcpp::TimerBase::SharedPtr _ptimer;
  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr _ppublisher;
  rclcpp::Subscription<std_msgs::msg::Int32>::SharedPtr _psubscription;
  size_t _ncount;
};
