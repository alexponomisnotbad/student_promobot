from launch import LaunchDescription
from launch_ros.actions import Node


def generate_launch_description():
    return LaunchDescription([
        Node(
            package="two_nodes",
            executable="talker",
            name="first_node",
            output="screen",
            emulate_tty=True,
            parameters=[
                {'/home/alex/ros2_ws/src/two_nodes/parameters/first_node.yaml'}
            ]
        ),
        Node(
            package="two_nodes",
            executable="talker",
            name="first_node",
            output="screen",
            emulate_tty=True,
            parameters=[
                {'/home/alex/ros2_ws/src/two_nodes/parameters/second_node.yaml'}
            ]
        )
    ])
