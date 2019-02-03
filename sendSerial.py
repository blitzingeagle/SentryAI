import serial
import argparse

parser = argparse.ArgumentParser()
parser.add_argument("--command", type=char, default=b'c')
args = parser.parse_args()

ser = Serial.serial("/dev/ttyUSB1", 9600)
ser.write(args.command)
