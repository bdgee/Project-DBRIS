import time
from pymata4 import pymata4

def distance(data):
	print(data[2])

#board = Arduino('/dev/ttyACM0')
board = pymata4.Pymata4()

trig = 11
echo = 12
board.set_pin_mode_sonar(trig, echo, distance)

while True: 
	time.sleep(.5)
	board.sonar_read(trig)