/***************************************************
//Web: http://www.buydisplay.com
EastRising Technology Co.,LTD
Examples for ER-TFTM040-1(480x800 Pixels)with Resistive Touch Panel
Software SPI,8080 16-bit Interface 5V Power Supply

This program is a demo of how to use most of the functions
of the library with a supported display modules.

Tested and worked with:
Arduino Mega 2560,Arduino Due
Works with Arduino 1.6.0 IDE 
****************************************************/

#include <UTFT.h>
#include <UTouch.h>

// Standard Arduino Mega/Due shield            : <display model>,38,39,40,41
UTFT myGLCD(NT35510_16,7,38,9,10);  //(byte model, int RS, int WR, int CS, int RST, int SER)

UTouch  myTouch( 2, 6, 3, 4, 5);      //RTP: byte tclk, byte tcs, byte din, byte dout, byte irq

extern uint8_t SmallFont[];

void setup()
{

  myGLCD.InitLCD();

  myGLCD.clrScr();

  myTouch.InitTouch();
  myTouch.setPrecision(PREC_MEDIUM);
    myGLCD.setFont(SmallFont);
}

void loop()
{
  long x, y;
         myGLCD.setColor(255, 0, 0);
          myGLCD.print("* www.buydiplay.com  Resistive touchscreen test.Please touch the screen!", CENTER, 10);   
  while (myTouch.dataAvailable() == true)
  {
    myTouch.read();
    x = myTouch.getX();
    y = myTouch.getY();
   // if ((x!=-1) and (y!=-1))
    {
      myGLCD.drawPixel (x, y);
    }
  }
}

