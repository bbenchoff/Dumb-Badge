import serial
import sys
import curses

stdscr = curses.initscr()

file = open(sys.argv[2],"rb")

ser = serial.Serial(sys.argv[1])
stdscr.clear()

stdscr.addstr(sys.argv[2])
stdscr.addstr(" Open ")
stdscr.addstr(ser.name)
stdscr.refresh()


byte=file.read(1)

while byte:

    c = byte
    stdscr.addstr(1,0, "Next Byte: ")
    stdscr.addstr(c)
    stdscr.addstr("  ")
    stdscr.addstr(2,0, "Press any key to transmit, Q to quit")
    stdscr.refresh()

    c = stdscr.getch()
                  
    if c == ord('Q'):
        break
    else:
        ser.write(byte)
        byte=file.read(1)
    
ser.close()
file.close()

