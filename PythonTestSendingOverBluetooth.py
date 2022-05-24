import serial
import time

testSerial = serial.Serial('/dev/rfcomm0', 9600)

print("Writing to testSerial")
testSerial.write('$'.encode())