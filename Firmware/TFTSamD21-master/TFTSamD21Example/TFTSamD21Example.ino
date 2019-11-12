
/*

M0(Zero)    TFT
5v          VCC
GND         GND
3.3         RD
5v          LEDA    
D0          DB8
D1          DB9
D2          DB10
D3          DB11
D4          DB12
D5          DB13
D6          DB14
D7          DB15

RS          A5
WR          A4
CS          A3
REST        A2

*/

#include "Arduino.h"
#include "character_map.h"
#include "arcena_22pt.h"
#define RS A5
#define WR A4
#define CS A3
#define RS_T A2


#define XSIZE 239
#define YSIZE 319
#define LEFT 0

#define RIGHT 9999
#define CENTER 9998

#define PORTRAIT 0
#define LANDSCAPE 1

#define fontbyte(x) pgm_read_byte(&cfont.font[x])
#define swap(type, i, j) {type t = i; i = j; j = t;}
void setFont(const unsigned char* f, const unsigned int (*d)[3], byte c);
void prnt(char *st, int x, int y);
struct currentFont
{
  uint8_t* font;
  uint8_t x_size;
  uint8_t y_size;
  uint8_t offset;
  uint8_t numchars;
};

struct charInfo {

  int width;
  int offset;

};


struct fontSet {

  const unsigned char* font; // your font array
  const unsigned int (*descriptors)[3]; // your font info
  byte num_of_chars; // number of characters in your font set
  byte rows;

};


charInfo ci;
fontSet fi;
currentFont cfont;
int current_x;
int current_y;

byte fcolorr, fcolorg, fcolorb;
byte bcolorr, bcolorg, bcolorb;
byte orient;
const unsigned char* cMap;

void setup() {
  orient = LANDSCAPE;
  Serial.begin(9600);

  for (int i = 0; i < 8; i++) {

    pinMode(i, OUTPUT); // D0 - D7

  }

  pinMode(RS, OUTPUT);
  pinMode(WR, OUTPUT);
  pinMode(CS, OUTPUT);
  pinMode(RS_T, OUTPUT);

  initTft();
  setBackColor(0, 0, 0);
  clrScr();

  setFont(arcena_22ptBitmaps, arcena_22ptDescriptors, 95);
  setCharMap(charMap); // standard 95 ascii characters
  setColor(255, 255, 17);
  prnt("Hello SAMD21!", 0 , 0);
}

void loop() {


}

void initTft() {

  setBit(RS_T);


  clearBit(RS_T);


  setBit(RS_T);

  clearBit(CS);
  setTFTProperties();

}

void writeComData(byte com, word data) {

  writeCom(com);
  writeData(data >> 8, data );

}

void writeData(byte vh, byte vl) {

  setBit(RS);
  writeBus(vh, vl);

}

void writeCom(byte com) {

  clearBit(RS);
  writeBus(0x00, com);

}
void writeBus(byte hv, byte lv) {

  writeToTFT(hv);
  pulseBitLow(WR);
  writeToTFT(lv);
  pulseBitLow(WR);


}

void writeToTFT(byte vl) {

  for (int i = 0; i < 8; i++) {
    byte bt = ((vl >> i)  & 0x01);
    digitalWrite(i, bt);

  }
}

void setBit(byte pin) {
  digitalWrite(pin, HIGH);
}

void clearBit(byte pin) {
  digitalWrite(pin, LOW);
}

void pulseBitLow(byte pin) {

  clearBit(pin);
  //delay(5);
  setBit(pin);
}

void setColor(byte r, byte g, byte b)
{
  fcolorr = r;
  fcolorg = g;
  fcolorb = b;
}

void setBackColor(byte r, byte g, byte b)
{
  bcolorr = r;
  bcolorg = g;
  bcolorb = b;
}

void setFont(const unsigned char* f, const unsigned int (*d)[3], byte c) {

  fi.font = f;
  fi.descriptors = d;
  fi.num_of_chars = c;
  fi.rows = (int)pgm_read_word(&(fi.descriptors[0][1])); // get height for characters

}

void setPixel(byte r, byte g, byte b)
{
  writeData(((r & 248) | g >> 5), ((g & 28) << 3 | b >> 3));
}

void clrScr()
{

  long i;

  clearBit(CS);

  clrXY();

  setBit(RS);
  long pixels = 76800;
  for (i = 0; i < pixels; i++)
  {

    writeBus(0, 0);

  }

  setBit(CS);

}

void clrXY()
{
  if (orient == PORTRAIT)
    setXY(0, 0, XSIZE, YSIZE);
  else
    setXY(0, 0, YSIZE, XSIZE);
}

void setXY(word x1, word y1, word x2, word y2)
{
  int tmp;

  if (orient == LANDSCAPE)
  {
    swap(word, x1, y1);
    swap(word, x2, y2)
    y1 = YSIZE - y1;
    y2 = YSIZE - y2;
    swap(word, y1, y2)
  }

  writeComData(0x20, x1);
  writeComData(0x21, y1);
  writeComData(0x50, x1);
  writeComData(0x52, y1);
  writeComData(0x51, x2);
  writeComData(0x53, y2);
  writeCom(0x22);

}

void drawRect(int x1, int y1, int x2, int y2)
{
  int tmp;

  if (x1 > x2)
  {
    swap(int, x1, x2);
  }
  if (y1 > y2)
  {
    swap(int, y1, y2);
  }

  drawHLine(x1, y1, x2 - x1);
  drawHLine(x1, y2, x2 - x1);
  drawVLine(x1, y1, y2 - y1);
  drawVLine(x2, y1, y2 - y1);
}

void drawPixel(int x, int y)
{
  clearBit(CS);
  setXY(x, y, x, y);
  setPixel(fcolorr, fcolorg, fcolorb);
  setBit(CS);
  clrXY();
}

void drawCircle(int x, int y, int radius)
{
  int f = 1 - radius;
  int ddF_x = 1;
  int ddF_y = -2 * radius;
  int x1 = 0;
  int y1 = radius;
  char ch, cl;

  ch = ((fcolorr & 248) | fcolorg >> 5);
  cl = ((fcolorg & 28) << 3 | fcolorb >> 3);

  clearBit(CS);
  setXY(x, y + radius, x, y + radius);
  writeData(ch, cl);
  setXY(x, y - radius, x, y - radius);
  writeData(ch, cl);
  setXY(x + radius, y, x + radius, y);
  writeData(ch, cl);
  setXY(x - radius, y, x - radius, y);
  writeData(ch, cl);

  while (x1 < y1)
  {
    if (f >= 0)
    {
      y1--;
      ddF_y += 2;
      f += ddF_y;
    }
    x1++;
    ddF_x += 2;
    f += ddF_x;
    setXY(x + x1, y + y1, x + x1, y + y1);
    writeData(ch, cl);
    setXY(x - x1, y + y1, x - x1, y + y1);
    writeData(ch, cl);
    setXY(x + x1, y - y1, x + x1, y - y1);
    writeData(ch, cl);
    setXY(x - x1, y - y1, x - x1, y - y1);
    writeData(ch, cl);
    setXY(x + y1, y + x1, x + y1, y + x1);
    writeData(ch, cl);
    setXY(x - y1, y + x1, x - y1, y + x1);
    writeData(ch, cl);
    setXY(x + y1, y - x1, x + y1, y - x1);
    writeData(ch, cl);
    setXY(x - y1, y - x1, x - y1, y - x1);
    writeData(ch, cl);
  }
  setBit(CS);
  clrXY();
}

void drawRoundRect(int x1, int y1, int x2, int y2)
{
  int tmp;

  if (x1 > x2)
  {
    swap(int, x1, x2);
  }
  if (y1 > y2)
  {
    swap(int, y1, y2);
  }
  if ((x2 - x1) > 4 && (y2 - y1) > 4)
  {
    drawPixel(x1 + 1, y1 + 1);
    drawPixel(x2 - 1, y1 + 1);
    drawPixel(x1 + 1, y2 - 1);
    drawPixel(x2 - 1, y2 - 1);
    drawHLine(x1 + 2, y1, x2 - x1 - 4);
    drawHLine(x1 + 2, y2, x2 - x1 - 4);
    drawVLine(x1, y1 + 2, y2 - y1 - 4);
    drawVLine(x2, y1 + 2, y2 - y1 - 4);
  }
}

void fillRect(int x1, int y1, int x2, int y2)
{
  int tmp;

  if (x1 > x2)
  {
    swap(int, x1, x2);
  }
  if (y1 > y2)
  {
    swap(int, y1, y2);
  }

  if (orient == PORTRAIT)
  {
    for (int i = 0; i < ((y2 - y1) / 2) + 1; i++)
    {
      drawHLine(x1, y1 + i, x2 - x1);
      drawHLine(x1, y2 - i, x2 - x1);
    }
  }
  else
  {
    for (int i = 0; i < ((x2 - x1) / 2) + 1; i++)
    {
      drawVLine(x1 + i, y1, y2 - y1);
      drawVLine(x2 - i, y1, y2 - y1);
    }
  }
}

void fillRoundRect(int x1, int y1, int x2, int y2)
{
  int tmp;

  if (x1 > x2)
  {
    swap(int, x1, x2);
  }
  if (y1 > y2)
  {
    swap(int, y1, y2);
  }

  if ((x2 - x1) > 4 && (y2 - y1) > 4)
  {
    for (int i = 0; i < ((y2 - y1) / 2) + 1; i++)
    {
      switch (i)
      {
        case 0:
          drawHLine(x1 + 2, y1 + i, x2 - x1 - 4);
          drawHLine(x1 + 2, y2 - i, x2 - x1 - 4);
          break;
        case 1:
          drawHLine(x1 + 1, y1 + i, x2 - x1 - 2);
          drawHLine(x1 + 1, y2 - i, x2 - x1 - 2);
          break;
        default:
          drawHLine(x1, y1 + i, x2 - x1);
          drawHLine(x1, y2 - i, x2 - x1);
      }
    }
  }
}

void fillCircle(int x, int y, int radius)
{
  clearBit(CS);
  for (int y1 = -radius; y1 <= radius; y1++)
    for (int x1 = -radius; x1 <= radius; x1++)
      if (x1 * x1 + y1 * y1 <= radius * radius)
      {
        setXY(x + x1, y + y1, x + x1, y + y1);
        writeData(((fcolorr & 248) | fcolorg >> 5), ((fcolorg & 28) << 3 | fcolorb >> 3));
      }
  setBit(CS);
  clrXY();
}

void drawLine(int x1, int y1, int x2, int y2)
{
  int tmp;
  double delta, tx, ty;
  double m, b, dx, dy;
  char ch, cl;

  ch = ((fcolorr & 248) | fcolorg >> 5);
  cl = ((fcolorg & 28) << 3 | fcolorb >> 3);

  if (((x2 - x1) < 0))
  {
    swap(int, x1, x2);
    swap(int, y1, y2);
  }
  if (((y2 - y1) < 0))
  {
    swap(int, x1, x2);
    swap(int, y1, y2);
  }

  if (y1 == y2)
  {
    if (x1 > x2)
    {
      swap(int, x1, x2);
    }
    drawHLine(x1, y1, x2 - x1);
  }
  else if (x1 == x2)
  {
    if (y1 > y2)
    {
      swap(int, y1, y2);
    }
    drawVLine(x1, y1, y2 - y1);
  }
  else if (abs(x2 - x1) > abs(y2 - y1))
  {
    clearBit(CS);
    delta = (double(y2 - y1) / double(x2 - x1));
    ty = double(y1);
    if (x1 > x2)
    {
      for (int i = x1; i >= x2; i--)
      {
        setXY(i, int(ty + 0.5), i, int(ty + 0.5));
        writeData(ch, cl);
        ty = ty - delta;
      }
    }
    else
    {
      for (int i = x1; i <= x2; i++)
      {
        setXY(i, int(ty + 0.5), i, int(ty + 0.5));
        writeData(ch, cl);
        ty = ty + delta;
      }
    }
    setBit(CS);
  }
  else
  {
    clearBit(CS);
    delta = (float(x2 - x1) / float(y2 - y1));
    tx = float(x1);
    if (y1 > y2)
    {
      for (int i = y2 + 1; i > y1; i--)
      {
        setXY(int(tx + 0.5), i, int(tx + 0.5), i);
        writeData(ch, cl);
        tx = tx + delta;
      }
    }
    else
    {
      for (int i = y1; i < y2 + 1; i++)
      {
        setXY(int(tx + 0.5), i, int(tx + 0.5), i);
        writeData(ch, cl);
        tx = tx + delta;
      }
    }
    setBit(CS);
  }
  clrXY();
}

void drawHLine(int x, int y, int l)
{
  char ch, cl;

  ch = ((fcolorr & 248) | fcolorg >> 5);
  cl = ((fcolorg & 28) << 3 | fcolorb >> 3);

  clearBit(CS);
  setXY(x, y, x + l, y);
  for (int i = 0; i < l + 1; i++)
  {
    writeData(ch, cl);
  }
  setBit(CS);
  clrXY();
}


void drawVLine(int x, int y, int l)
{
  char ch, cl;

  ch = ((fcolorr & 248) | fcolorg >> 5);
  cl = ((fcolorg & 28) << 3 | fcolorb >> 3);

  clearBit(CS);
  setXY(x, y, x, y + l);
  for (int i = 0; i < l; i++)
  {
    writeData(ch, cl);
  }
  setBit(CS);
  clrXY();
}


void setCharMap(const unsigned char* cm) {
  cMap = cm;
}

byte getIndex(char c) {

  for (int i = 0; i < 96; i++) {

    if (c == (int)pgm_read_byte(&(cMap[i]))) {

      return i;
    }

  }

}

void prnt(char *st, int x, int y) {
  int stl, i;

  stl = strlen(st);

  current_x = x;
  current_y = y;

  for (i = 0; i < stl; i++) {

    prntChar(*st++, x, y);
    current_x = current_x + ci.width;
    current_y = y;



  }

}

void prntChar(char ch, int x, int y) {

  digitalWrite(CS, LOW);
  byte bitCt = 8;// default
  byte indx;

  indx = getIndex(ch); // get the index from the char map


  ci.width = (int)pgm_read_word(&(fi.descriptors[indx][0]));
  ci.offset = (int)pgm_read_word(&(fi.descriptors[indx][2]));

  if (ci.width < 9) {

    bitCt = 8;
  } else if (ci.width < 17) {
    bitCt = 16;
  } else if (ci.width < 25) {
    bitCt = 24;
  } else if (ci.width < 33) {
    bitCt = 32;
  } else if (ci.width < 41) {
    bitCt = 40;
  } else if (ci.width < 49) {
    bitCt = 48;
  } else if (ci.width < 57) {
    bitCt = 56;

  } else if (ci.width < 65) {
    bitCt = 64;
  }

  int nextIndx = 0;

  if (indx + 1 >= fi.num_of_chars) { // array size 95

    nextIndx = ci.offset + (int)pgm_read_word(&(fi.descriptors[1][2])) - (int)pgm_read_word(&(fi.descriptors[0][2]));

  } else {

    nextIndx = (int)pgm_read_word(&(fi.descriptors[indx + 1][2]));

  }

  for (int i = ci.offset; i < nextIndx; i = i + bitCt / 8) {

    uint16_t ch;


    if (bitCt  == 16) {

      if (orient == PORTRAIT) {

        setXY(current_x, y, current_x + ci.width, y);

        byte byte1 = (uint8_t)pgm_read_byte(&( fi.font[i] ));
        byte byte2 = (uint8_t)pgm_read_byte(&( fi.font[i + 1] ));

        ch = (byte2 << 8) + byte1 ;

        for (int ii = 0; ii < ci.width + 1; ii++) {

          if ((ch >> ii) % 2 != 0) {

            setPixel(fcolorr, fcolorg, fcolorb);


          } else {

            setPixel(bcolorr, bcolorg, bcolorb);

          }

        }

      } else {

        setXY(current_x, y, current_x + ci.width, y);

        byte byte1 = (uint8_t)pgm_read_byte(&( fi.font[i] ));
        byte byte2 = (uint8_t)pgm_read_byte(&( fi.font[i + 1] ));

        ch = (byte2 << 8) + byte1 ;

        for (int ii = ci.width; ii > -1; ii--) {

          if ((ch >> ii) % 2 != 0) {

            setPixel(fcolorr, fcolorg, fcolorb);


          } else {

            setPixel(bcolorr, bcolorg, bcolorb);

          }

        }

      }



    } else {

      if (orient == PORTRAIT) {

        setXY(current_x, y, current_x + ci.width, y);

        for (int r = 0; r < bitCt / 8; r++) {

          ch = (uint8_t)pgm_read_byte(&( fi.font[i + r] ));

          for (int ii = 8; ii > 0; ii--) {

            if ((ch & (1 << (7 - ii))) != 0) {

              setPixel(fcolorr, fcolorg, fcolorb);


            } else {

              setPixel(bcolorr, bcolorg, bcolorb);

            }

          }

        }

      } else {

        setXY(current_x, y, current_x + ci.width, y);

        for (int r = bitCt / 8 - 1; r > -1; r--) {

          ch = (uint8_t)pgm_read_byte(&( fi.font[i + r] ));

          for (int ii = 0; ii < 8; ii++) {

            if ((ch & (1 << (7 - ii))) != 0) {

              setPixel(fcolorr, fcolorg, fcolorb);


            } else {

              setPixel(bcolorr, bcolorg, bcolorb);

            }

          }

        }

      }



    }

    y++;
  }

  digitalWrite(CS, HIGH);
  clrXY();

}
void rtChar (byte c, int x, int y, int pos, int deg) {
  // not supported yet
}

void setTFTProperties() {

  writeComData(0xE5, 0x78F0);
  writeComData(0x01, 0x0100);
  writeComData(0x02, 0x0200); // set 1 line inversion
  writeComData(0x03, 0x1030); // set GRAM write direction and BGR=1.
  writeComData(0x04, 0x0000); // Resize register
  writeComData(0x08, 0x0207); // set the back porch and front porch
  writeComData(0x09, 0x0000); // set non-display area refresh cycle ISC[3:0]
  writeComData(0x0A, 0x0000); // FMARK function
  writeComData(0x0C, 0x0000); // RGB interface setting
  writeComData(0x0D, 0x0000); // Frame marker Position
  writeComData(0x0F, 0x0000); // RGB interface polarity
  //*************Power On sequence ****************//
  writeComData(0x10, 0x0000); // SAP, BT[3:0], AP, DSTB, SLP, STB
  writeComData(0x11, 0x0007); // DC1[2:0], DC0[2:0], VC[2:0]
  writeComData(0x12, 0x0000); // VREG1OUT voltage
  writeComData(0x13, 0x0000); // VDV[4:0] for VCOM amplitude
  writeComData(0x07, 0x0001);
  // delay(200); // Dis-charge capacitor power voltage
  writeComData(0x10, 0x1690); // SAP, BT[3:0], AP, DSTB, SLP, STB
  writeComData(0x11, 0x0227); // Set DC1[2:0], DC0[2:0], VC[2:0]
  // delay(50); // Delay 50ms
  writeComData(0x12, 0x000D); // 0012
  //  delay(50); // Delay 50ms
  writeComData(0x13, 0x1200); // VDV[4:0] for VCOM amplitude
  writeComData(0x29, 0x000A); // 04  VCM[5:0] for VCOMH
  writeComData(0x2B, 0x000D); // Set Frame Rate
  // delay(50); // Delay 50ms
  writeComData(0x20, 0x0000); // GRAM horizontal Address
  writeComData(0x21, 0x0000); // GRAM Vertical Address
  // ----------- Adjust the Gamma Curve ----------//
  writeComData(0x30, 0x0000);
  writeComData(0x31, 0x0404);
  writeComData(0x32, 0x0003);
  writeComData(0x35, 0x0405);
  writeComData(0x36, 0x0808);
  writeComData(0x37, 0x0407);
  writeComData(0x38, 0x0303);
  writeComData(0x39, 0x0707);
  writeComData(0x3C, 0x0504);
  writeComData(0x3D, 0x0808);
  //------------------ Set GRAM area ---------------//
  writeComData(0x50, 0x0000); // Horizontal GRAM Start Address
  writeComData(0x51, 0x00EF); // Horizontal GRAM End Address
  writeComData(0x52, 0x0000); // Vertical GRAM Start Address
  writeComData(0x53, 0x013F); // Vertical GRAM Start Address
  writeComData(0x60, 0xA700); // Gate Scan Line
  writeComData(0x61, 0x0001); // NDL,VLE, REV
  writeComData(0x6A, 0x0000); // set scrolling line
  //-------------- Partial Display Control ---------//
  writeComData(0x80, 0x0000);
  writeComData(0x81, 0x0000);
  writeComData(0x82, 0x0000);
  writeComData(0x83, 0x0000);
  writeComData(0x84, 0x0000);
  writeComData(0x85, 0x0000);
  //-------------- Panel Control -------------------//
  writeComData(0x90, 0x0010);
  writeComData(0x92, 0x0000);
  writeComData(0x07, 0x0133); // 262K color and display ON

  setBit(CS);

  setColor(255, 255, 255);
  setBackColor(0, 0, 0);
  cfont.font = 0;

}
