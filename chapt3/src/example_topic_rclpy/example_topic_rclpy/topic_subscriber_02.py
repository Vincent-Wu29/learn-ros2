#!usr/bin/env python3
import rclpy
from rclpy.node import Node
from std_msgs.msg import String

class TopicSubscriber02(Node):
    def __init__(self, name):
        super().__init__(name)
        self.get_logger().info(f"大家好，我是{name}")
        self.command_subscriber_ = self.create_subscription(String, "command", self.command_callback, 10)

    def command_callback(self, msg):
        if (msg.data == "backup"):
            speed = -0.2
        self.get_logger().info(f"收到[{msg.data}]命令，发送速度{speed}")

def main(args=None):
    rclpy.init(args=args)
    node = TopicSubscriber02("topic_subscriber_02")
    rclpy.spin(node)
    rclpy.shutdown()