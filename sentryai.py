from flask import Flask
from flask_assistant import Assistant, ask, tell, event
from picture import captureImage
import cv2
import time
import requests
import json
import os
import subprocess
import signal
import serial

state = "command"
curr_proc = 0

#start of flask app
app = Flask(__name__)
assist = Assistant(app, '/')
serial_address = "/dev/ttyUSB1"
# ser = Serial.serial(serial_address, 9600)

@assist.action("Default Welcome Intent")
def default():
    global state
    global curr_proc
    
    state = "command"
    if curr_proc != None:
        os.killpg(curr_proc.pid, signal.SIGTERM)
        curr_proc.terminate()
        curr_proc = None
    #ser.write(b'i') #initialize
    return ask("Hi, I am Sentry AI!")

@assist.action("patrolPerimeter")
def patrolPerimeter():
    global state
    global curr_proc
    global serial_address
    
    state = "auto perimeter"
    if curr_proc != None
        os.killpg(curr_proc.pid, signal.SIGTERM)
        curr_proc.terminate()
    py_args = ['python', 'patrolPerimeter.py', "--serial", serial_address]
    curr_proc = subprocess.Popen(proc_args, shell=False, preexec_fn=os.setsid)
    return tell("OK, I will now patrol the perimeter and report any unusual activites!")
	
@assist.action("patrol")
def patrol():
    global state
    global curr_proc
    global serial_address

    if state == "auto":
        return tell("Menz already patrolling the area, don't over work menz!")

    state = "auto"
    if curr_proc != None
        os.killpg(curr_proc.pid, signal.SIGTERM)
        curr_proc.terminate()
    py_args = ['python', 'patrolPerimeter.py', "--serial", serial_address]
    curr_proc = subprocess.Popen(proc_args, shell=False, preexec_fn=os.setsid)

    return tell("OK, I will now patrol around this location and report any unusual activities!")

@assist.action("comeBack")
def comeBack():
    global state
    global curr_proc
    global serial_address
    
    state = "command"
    if curr_proc != None
        os.killpg(curr_proc.pid, signal.SIGTERM)
        curr_proc.terminate()
    py_args = ['python', 'comeBack.py', "--serial", serial_address]
    curr_proc = subprocess.Popen(proc_args, shell=False, preexec_fn=os.setsid)
    return tell("Oh, hello there. I hope I've done a good job!")

@assist.action("backward")
def backward():
    global state
    
    state = "command"
    if curr_proc != None
        os.killpg(curr_proc.pid, signal.SIGTERM)
        curr_proc.terminate()
        curr_proc = None
    #ser.write(b's') #move backwards a bit
    return ask("Done")

@assist.action("forward")
def forward():
    global state
    
    state = "command"
    if curr_proc != None
        os.killpg(curr_proc.pid, signal.SIGTERM)
        curr_proc.terminate()
        curr_proc = None
    #ser.write(b'w') #move forwards a bit
    return ask("Yes.")

@assist.action("turnLeft")
def turnLeft():
    global state
    
    state = "command"
    if curr_proc != None
        os.killpg(curr_proc.pid, signal.SIGTERM)
        curr_proc.terminate()
        curr_proc = None
    #ser.write(b'a') #turn left 90 degrees
    return ask("Yes.")

@assist.action("turnRight")
def turnRight():
    global state
    
    state = "command"
    if curr_proc != None
        os.killpg(curr_proc.pid, signal.SIGTERM)
        curr_proc.terminate()
        curr_proc = None
    #ser.write(b'd') #turn right 90 degrees
    return ask("Yes.")

@assist.action("panRight")
def panRight():
    global state
    
    state = "command"
    if curr_proc != None
        os.killpg(curr_proc.pid, signal.SIGTERM)
        curr_proc.terminate()
        curr_proc = None
    #ser.write(b'e') #turn right 90 degrees
    return ask("Yes.")

@assist.action("panLeft")
def panLeft():
    global state
    
    state = "command"
    if curr_proc != None
        os.killpg(curr_proc.pid, signal.SIGTERM)
        curr_proc.terminate()
        curr_proc = None
    #ser.write(b'q') #turn right 90 degrees
    return ask("Yes.")

@assist.action("stop")
def stop():
    global state
    
    state = "command"
    if curr_proc != None
        os.killpg(curr_proc.pid, signal.SIGTERM)
        curr_proc.terminate()
        curr_proc = None
    #ser.write(b'x') #turn right 90 degrees
    return ask("OK.")

@assist.action("resetMe")
def resetMe():
    global state
    
    state = "command"
    if curr_proc != None
        os.killpg(curr_proc.pid, signal.SIGTERM)
        curr_proc.terminate()
        curr_proc = None
    #ser.write(b'i') #reset
    return tell("Done resetting")

@assist.action("whatsUp")
def whatsUp:
    global state
    
    if state == "command":
        return tell("I am currently awaiting further command!")
    return tell("I am currently patroling autonomously")

if __name__ == "__main__":
    py_args = ['python', 'videocapture.py', "--serial", serial_address]
    curr_proc = subprocess.Popen(proc_args, shell=False, preexec_fn=os.setsid)

    app.run(debug=True)


