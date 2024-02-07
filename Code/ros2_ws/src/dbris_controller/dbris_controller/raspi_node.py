#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
from std_msgs.msg import *

class RaspiNode(Node):

    def __init__(self):
        super().__init__("raspi_node") 
        self.get_logger().info("raspi_node has been started")

        #Publishers
        self.dir_pub_ = self.create_publisher(String, "robot_dir", 10)
        self.timer_ = self.create_timer(1.0/5.0, self.pub_robot_dir)
        
        #Subscribers
        self.motor_pos_sub = self.create_subscription(Float64MultiArray, "motor_pos", self.sub_motor_pos, 10)
        self.servo_pos_sub = self.create_subscription(Float64, "servo_pos", self.sub_servo_pos, 10)
        self.ultra_dist_sub = self.create_subscription(Float64, "ultra_dist", self.sub_ultra_dist, 10)
        self.accel_sub = self.create_subscription(Float64MultiArray, "accel", self.sub_accel, 10)
        self.gyro_sub = self.create_subscription(Float64MultiArray, "gyro", self.sub_gyro, 10)

    #Publisher method
    def pub_robot_dir (self):
        msg = String()
        msg.data = "Bruh"
        self.dir_pub_.publish(msg)

    #Subscriber Methods
    def sub_motor_pos (self, msg:Float64MultiArray):
        self.get_logger().info(str(msg))
    
    def sub_servo_pos (self, msg:Float64):
        pass
    
    def sub_ultra_dist (self, msg:Float64):
        pass
    
    def sub_accel (self, msg:Float64MultiArray):
        pass

    def sub_gyro (self, msg:Float64MultiArray):
        pass

def main (args = None):
    rclpy.init(args = args)
    node = RaspiNode()
    rclpy.spin(node)
    rclpy.shutdown()