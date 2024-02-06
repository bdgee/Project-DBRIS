#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
from std_msgs.msg import *
import serial
import time

class ArdNode(Node):

    def __init__(self):
        super().__init__("ard_node")
        self.get_logger().info("ard_node has been started")

        #Subscribers
        self.dir_sub_ = self.create_subscription(Float64MultiArray, "robot_dir", self.sub_robot_dir, 10)

        #Publishers
        self.motor_pos_pub_ = self.create_publisher(Float64MultiArray, "motor_pos", 10)
        self.servo_pos_pub_ = self.create_publisher(Float64, "servo_pos", 10)
        self.sensor_dist_pub_ = self.create_publisher(Float64, "sensor_dist", 10)
        

        self.timer_ = self.create_timer(1.0/5.0, self.pub_motor_pos)
    
    def pub_motor_pos(self):
        msg = Float64MultiArray()

        #Get the motor position
        msg.data = [0.0, 0.0]
        self.motor_pos_pub_.publish(msg)
    
    def pub_servo_pos(self):
        msg = Float64()
        msg = 1.0
        self.servo_pos_pub_.publish(msg)
    
    def pub_sensor_dist(self):
        msg = Float64()
        msg = 1.0
        self.sensor_dist_pub_.publish(msg)

    def sub_robot_dir(self, msg:Float64MultiArray):
        self.get_logger().info(str(msg))


def main (args = None):
    rclpy.init(args = args)
    node = ArdNode()
    rclpy.spin(node)
    rclpy.shutdown()