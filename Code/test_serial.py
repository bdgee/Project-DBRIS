import serial.tools.list_ports
import time

serialInst = serial.Serial()

# portVar = '/dev/tty/ACM0'
portVar = 'COM3'
serialInst = serial.Serial(portVar, 115200, timeout=1.0)
time.sleep(3)
serialInst.reset_input_buffer()
print("Serial OK")
n = 1

try:
    while True:
        time.sleep(.01)
        #Send message
        serialInst.write((str(n+1)+"\n").encode('utf-8'))
        while serialInst.in_waiting <= 0:
            time.sleep(.01)
        packet = serialInst.readline().decode('utf-8')
        n = int(packet)
        print(n)
except KeyboardInterrupt:
    print("Close Serial communication")
    serialInst.close()