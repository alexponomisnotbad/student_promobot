#include <memory>
#include <iostream>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "std_msgs/msg/int32.hpp"

static constexpr char * c_topic = "publisher";
static constexpr char * c_subtopic = "subscriber";
static const uint8_t c_queue_size = 10;
static const uint32_t c_test_data = 999;

class TwoNode : public rclcpp::Node
{
public:
  TwoNode()
  : Node("second_node")
  {
    _psubscription = this->create_subscription<std_msgs::msg::String>(
      c_topic, c_queue_size, std::bind(&TwoNode::topicCallback, this, std::placeholders::_1));
    _ppublisher = this->create_publisher<std_msgs::msg::Int32>(c_subtopic, c_queue_size);
  }

private:
  void topicCallback(const std_msgs::msg::String & msg) const
  {
    RCLCPP_INFO(this->get_logger(), "I heard: '%s'", msg.data.c_str());

    auto message = std_msgs::msg::Int32();
    message.data = c_test_data;
    RCLCPP_INFO(this->get_logger(), std::to_string(message.data).c_str());
    _ppublisher->publish(message);
  }

private:
  rclcpp::Subscription<std_msgs::msg::String>::SharedPtr _psubscription;
  rclcpp::Publisher<std_msgs::msg::Int32>::SharedPtr _ppublisher;
};
