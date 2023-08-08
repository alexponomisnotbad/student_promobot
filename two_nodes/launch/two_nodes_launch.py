from launch import LaunchDescription
from launch_ros.actions import Node


def generate_launch_description():
    return LaunchDescription([
        Node(
            package='two_nodes',
            namespace='talker',
            executable='talker',
            name='one_node'
        ),
        Node(
            package='two_nodes',
            namespace='listener',
            executable='listener',
            name='two_node'
        )
    ])
