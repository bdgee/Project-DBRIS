import time
from pyfirmata import *
from pymata4 import pymata4

def distance(data):
	print(data[2])

if __name__ == '__main__':
	#board = Arduino('/dev/ttyACM0')
	board = pymata4.Pymata4()
	print("Success")

	trig = 3
	echo = 2
	board.set_pin_mode_sonar(trig, echo, distance)
