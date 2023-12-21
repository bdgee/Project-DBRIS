import time
from pyfirmata import *

if __name__ == '__main__':
	board = Arduino('/dev/ttyACM0')
	print("Success")

	with board:
		while True:
			print(board.analog[0].read())
			time.sleep(1)