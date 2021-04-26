import serial

ser = serial.Serial('COM1')
ser.baudrate = 9600


for x in range(30,38):
    for y in range(40,48):
        background = str(y)
        foreground = str(x)
        
        ser.write(b'\x1B')
        ser.write(b'[')
        ser.write(foreground.encode())
        ser.write(b'm')

        ser.write(b'\x1B')
        ser.write(b'[')
        ser.write(background.encode())
        ser.write(b'm')
        
        ser.write(b'test')
        


    if (x-1) % 2 == 0:
         ser.write(b'\n')

ser.write(b'\n')
