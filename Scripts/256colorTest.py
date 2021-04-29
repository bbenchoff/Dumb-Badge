import serial

ser = serial.Serial('COM1')
ser.baudrate = 9600


for x in range(0,256):
    background = str(x)

    ser.write(b'\x1B')
    ser.write(b'[48;5;')
    ser.write(background.encode())
    ser.write(b'm')
        
    ser.write(b'test')
        

    if x % 20 == 0:
         ser.write(b'\n')

ser.write(b'testing half color\n')

for x in range(0,256):
    background = str(x)

    ser.write(b'\x1B')
    ser.write(b'[2m')
    ser.write(b'\x1B')
    ser.write(b'[38;5;')
    ser.write(background.encode())
    ser.write(b'm')
        
    ser.write(b'test')
        

    if x % 20 == 0:
         ser.write(b'\n')

ser.write(b'\n')
