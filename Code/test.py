import time
from pyfirmata import *

if __name__ == '__main__':
	board = Arduino('/dev/ttyACM0')
	print("Success")

	echo = board.get_pin('d:7:o')

	while True:
		print(echo.ping())