import time
from pyfirmata import *

if __name__ == '__main__':
	board = Arduino('/dev/ttyACM0')
	print("Success")

	while True:
		print('pain')
		time.sleep(1)
