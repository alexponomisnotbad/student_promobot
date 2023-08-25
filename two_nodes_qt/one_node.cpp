#include "rclcpp.hpp"
#include "std_msgs/msg/string.hpp"


int main(int argc, char **argv)
{
    rclcpp::init(argc, argv, "one_node");
    rclcpp::NodeHandle nh;

    rclcpp::Publisher chatter_pub = nh.advertise<std_msgs::String>("chatter", 1000);

    rclcpp::Rate loop_rate(10);
    while (ros::ok())
    {
        std_msgs::String msg;
        msg.data = "hello world";

        chatter_pub.publish(msg);

        rclcpp::spinOnce();

        loop_rate.sleep();
    }

    return 0;
}
