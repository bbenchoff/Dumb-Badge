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
#include <SPI.h>

// Standard Arduino Mega/Due shield            : <display model>,38,39,40,41
UTFT myGLCD(NT35510_16,7,38,9,10);  //(byte model, int RS, int WR, int CS, int RST, int SER)

UTouch  myTouch( 2, 6, 3, 4, 5);      //RTP: byte tclk, byte tcs, byte din, byte dout, byte irq


// Declare which fonts we will be using
extern uint8_t BigFont[];

int color = 0;
word colorlist[] = {VGA_WHITE, VGA_BLACK, VGA_RED, VGA_BLUE, VGA_GREEN, VGA_FUCHSIA, VGA_YELLOW, VGA_AQUA};
int  bsize = 4;

void drawColorMarkerAndBrushSize(int col)
{
  myGLCD.setColor(VGA_BLACK);
  myGLCD.fillRect(25, 0, 31, 239);
  myGLCD.fillRect(myGLCD.getDisplayXSize()-31, 161, myGLCD.getDisplayXSize()-1, 191);
  myGLCD.setColor(VGA_WHITE);
  myGLCD.drawPixel(25, (col*30)+15);
  for (int i=1; i<7; i++)
    myGLCD.drawLine(25+i, ((col*30)+15)-i, 25+i, ((col*30)+15)+i);
  
  if (color==1)
    myGLCD.setColor(VGA_WHITE);
  else
    myGLCD.setColor(colorlist[col]);
  if (bsize==1)
    myGLCD.drawPixel(myGLCD.getDisplayXSize()-15, 177);
  else
    myGLCD.fillCircle(myGLCD.getDisplayXSize()-15, 177, bsize);
    
  myGLCD.setColor(colorlist[col]);
}

void setup()
{ 

  myGLCD.InitLCD();

  myGLCD.clrScr();
  myGLCD.setFont(BigFont);

  myTouch.InitTouch();
  myTouch.setPrecision(PREC_EXTREME);
  
  myGLCD.setColor(VGA_WHITE);
  myGLCD.drawLine(32,0,32,myGLCD.getDisplayYSize()-1);
  myGLCD.drawLine(myGLCD.getDisplayXSize()-32,0,myGLCD.getDisplayXSize()-32,myGLCD.getDisplayYSize()-1);
  myGLCD.print("C", myGLCD.getDisplayXSize()-24, 8);
  myGLCD.print("L", myGLCD.getDisplayXSize()-24, 24);
  myGLCD.print("E", myGLCD.getDisplayXSize()-24, 40);
  myGLCD.print("A", myGLCD.getDisplayXSize()-24, 56);
  myGLCD.print("R", myGLCD.getDisplayXSize()-24, 72);
  myGLCD.print("+", myGLCD.getDisplayXSize()-24, 136);
  myGLCD.print("-", myGLCD.getDisplayXSize()-24, 200);
  myGLCD.fillRect(myGLCD.getDisplayXSize()-32,96,myGLCD.getDisplayXSize()-1,128);
  myGLCD.drawLine(myGLCD.getDisplayXSize()-32,160,myGLCD.getDisplayXSize()-1,160);
  myGLCD.drawLine(myGLCD.getDisplayXSize()-32,192,myGLCD.getDisplayXSize()-1,192);
  myGLCD.drawLine(myGLCD.getDisplayXSize()-32,224,myGLCD.getDisplayXSize()-1,224);
  for (int i=0; i<8; i++)
  {
    myGLCD.setColor(colorlist[i]);
    myGLCD.fillRect(0, (i*30), 24, (((i+1)*30)-1));
  }
  drawColorMarkerAndBrushSize(color);
}

void loop()
{
  long x, y;
  
  while (myTouch.dataAvailable() == true)
  {
    myTouch.read();
    x = myTouch.getX();
    y = myTouch.getY();
    if ((x!=-1) and (y!=-1))
    {
      if (x>(31+bsize) and (x<myGLCD.getDisplayXSize()-(31+bsize)))
      {
        if (bsize==1)
          myGLCD.drawPixel(x, y);
        else
          myGLCD.fillCircle(x, y, bsize);
      }
      else
      {
        if (x<(30+bsize))
        {
          if (y<240)
          {
            color = y / 30;
            drawColorMarkerAndBrushSize(color);
            while (myTouch.dataAvailable()) {};
            delay(50);
         }
        }
        else
        {
          if (y<96)
          {
            myGLCD.setColor(VGA_BLACK);
            myGLCD.fillRect(33, 0, myGLCD.getDisplayXSize()-33, myGLCD.getDisplayYSize()-1);
            myGLCD.setColor(colorlist[color]);
          }
          if ((y>128) and (y<160))
          {
            if (bsize<7)
            {
              bsize++;
              drawColorMarkerAndBrushSize(color);
              while (myTouch.dataAvailable()) {};
              delay(50);
            }
          }
          if ((y>160) and (y<192))
          {
              bsize=4;
              drawColorMarkerAndBrushSize(color);
              while (myTouch.dataAvailable()) {};
              delay(50);
          }
          if ((y>192) and (y<224))
          {
            if (bsize>1)
            {
              bsize--;
              drawColorMarkerAndBrushSize(color);
              while (myTouch.dataAvailable()) {};
              delay(50);
            }
          }
        }
      }
    }
  }
}

