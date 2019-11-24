/***************************************************
// Web: http://www.buydisplay.com
EastRising Technology Co.,LTD
Examples for 480x800 TFT LCD Module with NT35510 Controller
5V Power Supply, TFT:8080-16BIT Parallel,Micro SD Card:Hardware SPI,4-Wire SPI
Micro SD Card (TF Card) Demonstration,
Note that the jumper on the adapter board is the hardware SPI 
Don't foget to copy images from bmp folder to your TF card and insert to SD card slot of shield.
****************************************************/
   
#include <Wire.h>  
#include <UTFT.h> 
#include <SPI.h> 
#include <SD.h> 
   
// TFT display and SD card will share the hardware SPI interface. 
// Hardware SPI pins are specific to the Arduino board type and 
// cannot be remapped to alternate pins.  
   
// Standard Arduino Mega/Due shield            : <display model>,38,39,40,41

// Standard Arduino Mega/Due shield            : <display model>,38,39,40,41
UTFT myGLCD(NT35510_16,7,38,9,10);  //(byte model, int RS, int WR, int CS, int RST, int SER)
  
#define SD_CS 8
int dispx, dispy;   

void setup(void) { 
  
  // Setup the LCD
  myGLCD.InitLCD();

  Serial.begin(9600); 
  
  myGLCD.setColor(255, 0, 0);
  myGLCD.fillRect(0, 0, 799, 479);  
  
  dispx=myGLCD.getDisplayXSize();
  dispy=myGLCD.getDisplayYSize();  
   
  Serial.print("Initializing SD card..."); 
  if (!SD.begin(SD_CS)) { 
    Serial.println("failed!"); 
  } 
  Serial.println("OK!"); 
   
     bmpDraw("BMP_1.bmp", 0, 0);
   delay(1000);
   bmpDraw("BMP_2.bmp", 0, 0); 
  delay(1000);
   bmpDraw("BMP_3.bmp", 0, 0); 
  delay(1000);
   bmpDraw("BMP_4.bmp", 0, 0);    
    delay(1000);
   bmpDraw("BMP_5.bmp", 0, 0);   
     delay(1000);
   bmpDraw("BMP_6.bmp", 0, 0); 
    delay(1000);
   bmpDraw("BMP_7.bmp", 0, 0);   
     delay(1000);
   bmpDraw("BMP_8.bmp", 0, 0);  
     delay(1000);
   bmpDraw("BMP_9.bmp", 0, 0);  
     delay(1000);
   bmpDraw("BMP_10.bmp", 0, 0);  
  delay(1000);
} 
   
void loop() { 
} 
   
// This function opens a Windows Bitmap (BMP) file and 
// displays it at the given coordinates.  It's sped up 
// by reading many pixels worth of data at a time 
// (rather than pixel by pixel).  Increasing the buffer 
// size takes more of the Arduino's precious RAM but 
// makes loading a little faster.  20 pixels seems a 
// good balance. 
   
#define BUFFPIXEL 20

void bmpDraw(char *filename, int x, int y) {
  File     bmpFile;
  int      bmpWidth, bmpHeight;   // W+H in pixels
  uint8_t  bmpDepth;              // Bit depth (currently must be 24)
  uint32_t bmpImageoffset;        // Start of image data in file
  uint32_t rowSize;               // Not always = bmpWidth; may have padding
  uint8_t  sdbuffer[3*BUFFPIXEL]; // pixel in buffer (R+G+B per pixel)
  uint16_t lcdbuffer[BUFFPIXEL];  // pixel out buffer (16-bit per pixel)
  uint8_t  buffidx = sizeof(sdbuffer); // Current position in sdbuffer
  boolean  goodBmp = false;       // Set to true on valid header parse
  boolean  flip    = true;        // BMP is stored bottom-to-top
  int      w, h, row, col;
  uint8_t  r, g, b;
  uint32_t pos = 0, startTime = millis();
  uint8_t  lcdidx = 0;
  boolean  first = true;

  if((x >= dispx) || (y >= dispy)) return;

  Serial.println();
  Serial.print(F("Loading image '"));
  Serial.print(filename);
  Serial.println('\'');

  // Open requested file on SD card
  if ((bmpFile = SD.open(filename)) == NULL) {
    Serial.println(F("File not found"));
    return;
  }

  // Parse BMP header
  if(read16(bmpFile) == 0x4D42) { // BMP signature
    Serial.println(F("File size: ")); 
    Serial.println(read32(bmpFile));
    (void)read32(bmpFile); // Read & ignore creator bytes
    bmpImageoffset = read32(bmpFile); // Start of image data
    Serial.print(F("Image Offset: ")); 
    Serial.println(bmpImageoffset, DEC);

    // Read DIB header
    Serial.print(F("Header size: ")); 
    Serial.println(read32(bmpFile));
    bmpWidth  = read32(bmpFile);
    bmpHeight = read32(bmpFile);

    if(read16(bmpFile) == 1) { // # planes -- must be '1'
      bmpDepth = read16(bmpFile); // bits per pixel
      Serial.print(F("Bit Depth: ")); 
      Serial.println(bmpDepth);
      if((bmpDepth == 24) && (read32(bmpFile) == 0)) { // 0 = uncompressed
        goodBmp = true; // Supported BMP format -- proceed!
        Serial.print(F("Image size: "));
        Serial.print(bmpWidth);
        Serial.print('x');
        Serial.println(bmpHeight);

        // BMP rows are padded (if needed) to 4-byte boundary
        rowSize = (bmpWidth * 3 + 3) & ~3;

        // If bmpHeight is negative, image is in top-down order.
        // This is not canon but has been observed in the wild.
        if(bmpHeight < 0) {
          bmpHeight = -bmpHeight;
          flip      = false;
        }

        // Crop area to be loaded
        w = bmpWidth;
        h = bmpHeight;
        if((x+w-1) >= dispx)  w = dispx  - x;
        if((y+h-1) >= dispy) h = dispy - y;

        // Set TFT address window to clipped image bounds

        for (row=0; row<h; row++) { // For each scanline...
          // Seek to start of scan line.  It might seem labor-
          // intensive to be doing this on every line, but this
          // method covers a lot of gritty details like cropping
          // and scanline padding.  Also, the seek only takes
          // place if the file position actually needs to change
          // (avoids a lot of cluster math in SD library).
          if(flip) // Bitmap is stored bottom-to-top order (normal BMP)
            pos = bmpImageoffset + (bmpHeight - 1 - row) * rowSize;
          else     // Bitmap is stored top-to-bottom
          pos = bmpImageoffset + row * rowSize;
          if(bmpFile.position() != pos) { // Need seek?
            bmpFile.seek(pos);
            buffidx = sizeof(sdbuffer); // Force buffer reload
          }

          for (col=0; col<w; col++) { // For each column...
            // Time to read more pixel data?
            if (buffidx >= sizeof(sdbuffer)) { // Indeed
              // Push LCD buffer to the display first
              if(lcdidx > 0) {
                myGLCD.setColor(lcdbuffer[lcdidx]);
                myGLCD.drawPixel(col, row);
                lcdidx = 0;
                first  = false;
              }

              bmpFile.read(sdbuffer, sizeof(sdbuffer));
              buffidx = 0; // Set index to beginning
            }

            // Convert pixel from BMP to TFT format
            b = sdbuffer[buffidx++];
            g = sdbuffer[buffidx++];
            r = sdbuffer[buffidx++];
            myGLCD.setColor(r,g,b);
            myGLCD.drawPixel(col, row);
          } // end pixel

        } // end scanline

        // Write any remaining data to LCD
        if(lcdidx > 0) {
           myGLCD.setColor(lcdbuffer[lcdidx]);
          myGLCD.drawPixel(col, row);
        } 

        Serial.print(F("Loaded in "));
        Serial.print(millis() - startTime);
        Serial.println(" ms");

      } // end goodBmp
    }
  }

  bmpFile.close();
  if(!goodBmp) Serial.println(F("BMP format not recognized."));

}

// These read 16- and 32-bit types from the SD card file.
// BMP data is stored little-endian, Arduino is little-endian too.
// May need to reverse subscript order if porting elsewhere.

uint16_t read16(File f) {
  uint16_t result;
  ((uint8_t *)&result)[0] = f.read(); // LSB
  ((uint8_t *)&result)[1] = f.read(); // MSB
  return result;
}

uint32_t read32(File f) {
  uint32_t result;
  ((uint8_t *)&result)[0] = f.read(); // LSB
  ((uint8_t *)&result)[1] = f.read();
  ((uint8_t *)&result)[2] = f.read();
  ((uint8_t *)&result)[3] = f.read(); // MSB
  return result;
}


