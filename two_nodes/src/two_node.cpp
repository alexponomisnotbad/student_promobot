#include <memory>
#include "/home/alex/ros2_ws/src/two_nodes/hpp/two_node.hpp"

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<TwoNode>());
  rclcpp::shutdown();
  return 0;
}

