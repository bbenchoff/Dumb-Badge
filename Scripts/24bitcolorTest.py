import serial
import random


ser = serial.Serial('COM1')
ser.baudrate = 9600


for x in range(0,256):
    background = str(x)

    red = random.randint(0,255)
    green = random.randint(0,255)
    blue = random.randint(0,255)

    redByte = str(red)
    blueByte = str(blue)
    greenByte = str(blue)

    ser.write(b'\x1B')
    ser.write(b'[38;2;')
    ser.write(redByte.encode())
    ser.write(b';')
    ser.write(greenByte.encode())
    ser.write(b';')
    ser.write(blueByte.encode())
    ser.write(b'm')
        
    ser.write(b'test')
        

    if (x-1) % 20 == 0:
         ser.write(b'\n')

ser.write(b'\n')
