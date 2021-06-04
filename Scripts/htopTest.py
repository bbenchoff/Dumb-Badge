import serial
import sys
import curses
import time

stdscr = curses.initscr()

file = open("htopIntro.bin","rb")
file2 = open("htopend.bin","rb")

ser = serial.Serial("COM1")
stdscr.clear()

stdscr.addstr(ser.name)
stdscr.refresh()

byte=file.read(1)
byte2=file2.read(1)

while byte:

    c = byte
    stdscr.addstr(1,0, "Next Byte: ")
    stdscr.addstr(c)
    stdscr.addstr("  ")
    stdscr.addstr(2,0, "Press any key to transmit next byte, Q to quit")
    stdscr.refresh()
    ser.write(byte)
    byte=file.read(1)
    time.sleep(.025)

file.close()

while byte2:

    c = byte2
    stdscr.addstr(1,0, "Next Byte: ")
    stdscr.addstr(c)
    stdscr.addstr("  ")
    stdscr.addstr(2,0, "Press any key to transmit next byte, Q to quit")
    stdscr.refresh()
    
    c = stdscr.getch()
                  
    if c == ord('Q'):
        break
    else:
        ser.write(byte2)
        byte2=file2.read(1)
    
ser.close()
file2.close()

