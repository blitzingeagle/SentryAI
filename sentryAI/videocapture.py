from __future__ import print_function
from imutils.video import WebcamVideoStream
from tkinter import *
from PIL import Image
from PIL import ImageTk
import datetime
import imutils
import threading
import time
import cv2
import numpy as np

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


class Interface:

  def __init__(self, vs):
   self.vs = vs
   self.frame = None
   self.thread = None
   self.stopEvent = None
   
   self.window = Tk()
   self.window.title("SentryAI")
   self.panel = None

   self.stopEvent = threading.Event()
   self.thread = threading.Thread(target=self.videoLoop, args=())
   self.thread.start()
    
    
  def videoLoop(self):
  
    try:
    
      while not self.stopEvent.is_set():
        self.frame = self.vs.read()
        self.frame = imutils.resize(self.frame, width = 500)
        
        timestamp = datetime.datetime.now()
        ts = timestamp.strftime("%A %d %B %Y %I:%M:%S%p")
        cv2.putText(self.frame,ts, (10, self.frame.shape[0] - 10), cv2.FONT_HERSHEY_SIMPLEX, 0.35, (0, 0, 255), 1)

        image = cv2.cvtColor(self.frame, cv2.COLOR_BGR2RGB)
        image = Image.fromarray(image)
        image = ImageTk.PhotoImage(image)

        if self.panel is None:
          self.panel = Label(image=image)
          self.panel.image = image
          self.panel.pack(side="left", padx=10, pady=10)
		
        else:
          self.panel.configure(image=image)
          self.panel.image = image
			
    except RuntimeError as e:
      print("[INFO] caught a RuntimeError")

  def onClose(self):
    print("[INFO] closing...")
    self.stopEvent.set()
    self.vs.stop()
    self.root.quit()
    
	
if __name__=='__main__':		
  vs = VideoStream().start()
  time.sleep(2.0)
  
  ui = Interface(vs)
  ui.window.mainloop()
  cv2.destroyAllWindows()
  
