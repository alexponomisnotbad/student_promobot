#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "std_msgs/msg/int32.hpp"
using std::placeholders::_1;

class MinimalSubscriber : public rclcpp::Node
{
  public:
    MinimalSubscriber()
    : Node("minimal_subscriber"), _ncount(0)
    { 
      using namespace std::chrono_literals;
      _psubscription = this->create_subscription<std_msgs::msg::String>(
      "topic", 10, std::bind(&MinimalSubscriber::topic_callback, this, _1));
    }
  private:
    void topic_callback(const std_msgs::msg::String::SharedPtr msg) const
  {
    auto last_message  = std_msgs::msg::String();
    last_message = msg->data
    if (last_message == ("Hello, I am alive!" + std::to_string(_ncount++)))
    {
      RCLCPP_INFO(this->get_logger(), "Received message: '%s'", msg->data.c_str());
      auto message = std_msgs::msg::Int32();
      message.data = 0 + _ncount++;
      RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", message.data.c_str());
    }
  }

  private:
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr _psubscription;
    size_t _ncount;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalSubscriber>());
  rclcpp::shutdown();
  return 0;
}

