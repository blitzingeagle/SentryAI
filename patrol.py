import serial
import subprocess
import random
import argparse
import time

parser = argparse.ArgumentParser()
parser.add_argument("--serial", type=str, default="/dev/ttyUSB1")
args = parser.parse_args()

ser = Serial.serial(args.serial, 9600)
    
while True:
    action = random.randint(1, 5)
    if action == 1:
        ser.write(b'w')
    elif action == 2:
        ser.write(b's')
    elif action == 3:
        ser.write(b'a')   
    elif action == 4:
        ser.write(b'd')
    time.sleep(3)
    ser.write(b'x')
    time.sleep(1)
    if action == 1 or action == 3:
        ser.write(b't')
    elif action == 2 or action == 4:
        ser.write(b'y')
    time.sleep(5)





