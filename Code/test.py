import time
import pyfirmata

if __name__ == '__main__':
	board = pyfirmata.Arduino('/dev/ttyACM0')
	print("Success")

	echo = board.get_pin('d:11:i')
	trig = board.get_pin('d:12:o')
	LED = board.get_pin('d:13:o')
	
	

	while True:
		board.digital[13].write(1)
		time.sleep(1)
		board.digital[13].write(0)
		time.sleep(1)
