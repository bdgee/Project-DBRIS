import cv2
import time
cam = cv2.VideoCapture(0)

ret, frame = cam.read()
img_name = "test.png"
cv2.imwrite(img_name, frame)
cam.release()

cv2.destroyAllWindows()