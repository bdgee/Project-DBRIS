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
        self.dir_sub_ = self.create_subscription(String, "robot_dir", self.sub_robot_dir, 10)

        #Publishers
        self.motor_pos_pub_ = self.create_publisher(Float64MultiArray, "motor_pos", 10)
        self.servo_pos_pub_ = self.create_publisher(Float64, "servo_pos", 10)
        self.ultra_dist_pub_ = self.create_publisher(Float64, "ultra_dist", 10)
        self.accel_pub_ = self.create_publisher(Float64MultiArray, "accel", 10)
        self.gyro_pub_ = self.create_publisher(Float64MultiArray, "gyro", 10)
        

        self.timer_ = self.create_timer(1.0/5.0, self.pub_all)
    
    #Publisher method
    def pub_all(self):
        #Replace with serial monitor code later

        #Motor position
        motor_pos = Float64MultiArray()
        motor_pos.data = [0.0, 0.0]
        self.motor_pos_pub_.publish(motor_pos)

        #Servo
        servo_pos = Float64()
        servo_pos.data = 0.0
        self.servo_pos_pub_.publish(servo_pos)

        #Ultrasonic Sensor
        ultra_dist = Float64()
        ultra_dist.data = 1.0
        self.ultra_dist_pub_.publish(ultra_dist)

        #Accelerometer
        accel = Float64MultiArray()
        accel.data = [0.0, 0.0, 0.0]
        self.accel_pub_.publish(accel)

        #Gyroscope 
        gyro = Float64MultiArray()
        gyro.data = [0.0, 0.0, 0.0]
        self.gyro_pub_.publish(gyro)


    #Subscriber functions
    def sub_robot_dir(self, msg:String):
        self.get_logger().info(str(msg))


def main (args = None):
    rclpy.init(args = args)
    node = ArdNode()
    rclpy.spin(node)
    rclpy.shutdown()