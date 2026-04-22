#!usr/bin/env python3
from urllib import request

import rclpy
from rclpy.node import Node
from example_interfaces.srv import AddTwoInts

class ServiceClient02(Node):
    def __init__(self, name):
        super().__init__(name)
        self.get_logger().info(f"节点启动：{name}")
        self.client_ = self.create_client(AddTwoInts, "add_two_ints_srv")

    def result_callback(self, result_future):
        response = result_future.result()
        self.get_logger().info(f"返回结果：{response.sum}")


    def send_request(self, a, b):
        self.get_logger().info(f"计算：{a}+{b}")

        while not self.client_.wait_for_service(1):
            if not rclpy.ok():
                self.get_logger().error("等待服务启动中发生中断...")
            self.get_logger().info("等待服务启动中")

        request = AddTwoInts.Request()
        request.a = a
        request.b = b

        self.client_.call_async(request).add_done_callback(self.result_callback)


def main(args=None):
    rclpy.init(args=args)
    node = ServiceClient02("service_server_02")
    node.send_request(3, 4)
    rclpy.spin(node)
    rclpy.shutdown()