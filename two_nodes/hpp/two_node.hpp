#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "std_msgs/msg/integer.hpp"
using std::placeholders::_1;

class MinimalSubscriber : public rclcpp::Node
{
  public:
    MinimalSubscriber()
    : Node("minimal_subscriber")
    { 
      namespace std::chrono_literals;
      using std::placeholders::_1;
      _ppublisher = this->create_publisher<std_msgs::msg::Integer>("output_topic", 10);
      _psubscription = this->create_subscription<std_msgs::msg::String>(
      "topic", 10, std::bind(&MinimalSubscriber::topic_callback, this, _1));
    }
  private:
    void topic_callback(const std_msgs::msg::String::SharedPtr msg) const
  {
    RCLCPP_INFO(this->get_logger(), "Received message: '%s'", msg->data.c_str());
    if (msg->data == "Hello, I am alive!")
    {
      auto message = std_msgs::msg::Integer();
      message.data = 555;
      RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", message.data.c_str());
      _ppublisher->publish(message);
    }
  }

  private:
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr _psubscription;
    rclcpp::Publisher<std_msgs::msg::Int32>::SharedPtr _ppublisher;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalSubscriber>());
  rclcpp::shutdown();
  return 0;
}

