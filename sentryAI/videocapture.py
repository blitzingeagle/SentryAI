from imutils.video import WebcamVideoStream
import datetime
import imutils
import time
import cv2

class VideoStream:

  def __init__(self, src=0):
    self.stream = WebcamVideoStream(src=src)
 
  def start(self):
    return self.stream.start()

  def update(self):
    self.stream.update()

  def read(self):
    return self.stream.read()

  def stop(self):
    return self.stream.stop()

if __name__=='__main__':

  vs = VideoStream().start()
  time.sleep(2.0)

  while True:
    frame = vs.read()
    frame = imutils.resize(frame, width = 400)

    timestamp = datetime.datetime.now()
    ts = timestamp.strftime("%A %d %B %Y %I:%M:%S%p")
    cv2.putText(frame,ts, (10, frame.shape[0] - 10), cv2.FONT_HERSHEY_SIMPLEX, 0.35, (0, 0, 255), 1)

    cv2.imshow("Frame", frame)
    key = cv2.waitKey(1) & 0xFF

    if key == ord("q"):
      break

  cv2.destroyAllWindows()
  vs.stop()
  