from picamera import PiCamera
import time

camera = PiCamera()
time.sleep(2)

camera.capture('/home/bdgee/Project-DBRIS/Code/img.jpg')
print("Done")