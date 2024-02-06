#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
from std_msgs.msg import *

class RaspiNode(Node):

    def __init__(self):
        super().__init__("raspi_node") 
        self.get_logger().info("raspi_node has been started")

        #Publishers
        self.dir_pub_ = self.create_publisher(Float64MultiArray, "robot_dir", 10)
        self.timer_ = self.create_timer(1.0/5.0, self.pub_robot_dir)
        
        #Subscribers
        self.motor_pos_sub = self.create_subscription(Float64MultiArray, "motor_pos", self.sub_motor_pos, 10)
        

    def pub_robot_dir (self):
        msg = Float64MultiArray()
        msg.data = [1.0, 1.0]
        self.dir_pub_.publish(msg)

    def sub_motor_pos (self, msg:Float64MultiArray):
        self.get_logger().info(str(msg))

def main (args = None):
    rclpy.init(args = args)
    node = RaspiNode()
    rclpy.spin(node)
    rclpy.shutdown()