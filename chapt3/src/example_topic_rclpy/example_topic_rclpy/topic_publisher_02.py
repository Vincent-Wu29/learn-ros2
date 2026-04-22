#!usr/bin/env python3
import rclpy
from rclpy.node import Node
from std_msgs.msg import String

class TopicPublisher02(Node):
    def __init__(self, name):
        super().__init__(name)
        self.get_logger().info(f"大家好，我是{name}")
        self.command_publisher_ = self.create_publisher(String, "command", 10)
        self.timer_ = self.create_timer(0.5, self.timer_callback)

    def timer_callback(self):
        msg = String()
        msg.data = "backup"
        self.command_publisher_.publish(msg)
        self.get_logger().info(f"发布命令：{msg.data}")


def main(args=None):
    rclpy.init(args=args)
    node = TopicPublisher02("topic_publisher_02")
    rclpy.spin(node)
    rclpy.shutdown()