#include <memory>
#include "/home/alex/ros2_ws/src/two_nodes/hpp/one_node.hpp"

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  auto message = std_msgs::msg::String();
  message.data = "Hello, I am alive! 0";
  RCLCPP_INFO(logger, "Publishing: '%s'", message.data.c_str());
  rclcpp::spin(std::make_shared<cpp_pubsub::MinimalPublisher>());
  rclcpp::shutdown();
  return 0;
}
