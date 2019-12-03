/*
 * Electrical setup: LCD data pins are a 16-bit bus from PB00 to PB15 
 * 
 * LCD uses 8080-series interface, with 19 wires, 16 of which are the data bus
 * the CSX (active low) enables the parallel interface, WRX is the parallel data write
 * RDX is the parallel data read.
 * 
 * Graphics chip controller reads the data on the rising edge of the wrx signal.
 * The D/CX is the data, command flag. When D/CX = 1 bits are display RAM data or
 * command paramaters. When D/CX = 0, the bits are commands.
 * 
 * The interface is set with the IM0 through IM3 pins. Functions below:
 * 
 *                  | D/CX  | RDX | WRX | Function
 *                  | 0       1     R   | Write 16-bit command
 * 16 bit parallel  | 1       1     R   | Write 16-bit display data or parameter
 *                  | 1       R     1   | Read 16-bit display data
 *                  | 1       R     1   | Read 16-bit parameter or status               
 */ 
 #include "sam.h"

//Define LCD control pins
 #define LCD_RS PORT_PA08   //  Read strobe, signal to read data when RS is low
 #define LCD_WR PORT_PA09   //  Write strobe, signal to write data when WRX is low, falling edge
 #define LCD_CS PORT_PA13   //  Chip Select LOW ENABLE
 #define LCD_DC PORT_PA15   //  Display data/command selection , '0'=command, '1'=data
 #define LCD_RST PORT_PA03  //  Reset pin, idk, does stuff
 #define LCD_BUS 0x0000FFFF //  pins PB00 to PB15


int disp_x_size = 479;  //Define x size of display, 480, zero indexed
int disp_y_size = 799;  //Define y size of display, 800, zero indexed

byte fch, fcl;
word color;


void setup() 
{

  SystemInit(); //Initalize SAM system


  //Configure LCD control pins as output
  REG_PORT_DIRSET0 = LCD_WR;
  REG_PORT_DIRSET0 = LCD_DC;
  REG_PORT_DIRSET0 = LCD_RS;  
  REG_PORT_DIRSET0 = LCD_RST;
  REG_PORT_DIRSET0 = LCD_CS;
  REG_PORT_DIRSET1 = LCD_BUS; // direction set to output PB00-PB15


  //REG_PORT_OUTCLR0 = LCD_CS;
  //REG_PORT_OUTSET0 = LCD_RS;
/*
  REG_PORT_OUTSET0 = LCD_CS;
  REG_PORT_OUTSET0 = LCD_RST;
  REG_PORT_OUTSET0 = LCD_WR;
  REG_PORT_OUTSET0 = LCD_DC;
  REG_PORT_OUTSET0 = LCD_RS;
  */
  delay(100);

  initLCD();    //Initalize the LCD

  clrScr();


}

void loop() 
{

  clrScr();


  RedScr();

  
}

// Writes one-byte command
void LCD_Write_Command(uint8_t command)
{
  //Set D/CX to 0 as we are moving a command
  REG_PORT_OUTCLR0 = LCD_DC;
  //Prepend with 0x00
  LCD_Write_Bus(0x00,command);
}

// Writes two-byte command
void LCD_Write_Command(uint8_t commandHigh, uint8_t commandLow)
{
  //Set D/CX to 0 as we are moving a command
  REG_PORT_OUTCLR0 = LCD_DC;
  LCD_Write_Bus(commandHigh, commandLow);
}

// Writes two-byte data as we are moving data
void LCD_Write_Data(uint8_t dataHigh, uint8_t dataLow)
{
  //Set D/CX to 1 as moving data
  REG_PORT_OUTSET0 = LCD_DC;
  LCD_Write_Bus(dataHigh, dataLow);  
}

// Writes one-byte data
void LCD_Write_Data(uint8_t data)
{
  //Set D/CX to 1 as we are moving data
  REG_PORT_OUTSET0 = LCD_DC;
  //Prepend with 0x00
  LCD_Write_Bus(0x00,data);
}

void pulse_WR_Low()
{
  REG_PORT_OUTSET0 = LCD_WR;
  REG_PORT_OUTCLR0 = LCD_WR;
}

/*  LCD_Write_Bus
 *  For the NT35510 in 8080-series 16-bit mode
 *  data is written on the falling edge of the WR pin
 *  (datasheet page 25). To do this we set PB00..PB15
 *  to the data we want to send
 */
void LCD_Write_Bus(uint8_t bitHigh, uint8_t bitLow)
{ 

  uint16_t data = (bitHigh << 8) | (bitLow & 0xFF);
  
  REG_PORT_DIRSET1 = LCD_BUS;  //Set PB00 - PB15 as output
  REG_PORT_OUTCLR1 = LCD_BUS;  //clear bits
  
  // Write data to PB00..PB15
  REG_PORT_OUTSET1 = data;       //set PB00..PB15 to data

  pulse_WR_Low();

  //set LCD bus back to 0
  REG_PORT_OUTCLR1 = LCD_BUS;
  
}

void setXY(word x1, word y1, word x2, word y2)
{
/*
  swap(x1, y1);
  swap(x2, y2)
  y1=disp_y_size-y1;
  y2=disp_y_size-y2;
  swap(y1, y2)
*/

  LCD_Write_Command(0x2a,0x00); //
  LCD_Write_Data(x1>>8);        //  This section sets the row and column address
  LCD_Write_Command(0x2a,0x01); //  to define area of frame memory MPU can access.
  LCD_Write_Data(x1);           //  Information on layout of frame memory
  LCD_Write_Command(0x2a,0x02); //  is given on pp 75-77 of NT35510 datasheed
  LCD_Write_Data(x2>>8);        //
  LCD_Write_Command(0x2a,0x03); //  Effectively, we are setting a 1 x 1 pixel area of the displa
  LCD_Write_Data(x2);           //


  LCD_Write_Command(0x2b,0x00); 
  LCD_Write_Data(y1>>8);
  LCD_Write_Command(0x2b,0x01); 
  LCD_Write_Data(y1);
  LCD_Write_Command(0x2b,0x02); 
  LCD_Write_Data(y2>>8);
  LCD_Write_Command(0x2b,0x03); 
  LCD_Write_Data(y2);

  LCD_Write_Command(0x2c,0x00); //  Memory write, transfers data from MPU interface to frame memory // datasheet page 139

}

void setColor(byte r, byte g, byte b)
{
  fch=((r&248)|g>>5);
  fcl=((g&28)<<3|b>>3);
}

void setColor(word color)
{
  fch=byte(color>>8);
  fcl=byte(color & 0xFF);
}

/*
 * setPixel(word color)
 * 
 */
void setPixel(word color)
{
  LCD_Write_Data((color>>8),(color&0xFF));  /// 565 RGB 
}

/*
 * drawPixel(int x, int y)
 * draws a pixel of color specified
 * in setPixel at XY location
 */

void drawPixel(int x, int y)
{


  setXY(x,y,x,y);

  setPixel((fch<<8)|fcl);
  

   
  clrXY();
}

void clrXY()
{
  setXY(0,0,disp_x_size,disp_y_size);
}

void clrScr()
{


  clrXY();

  fastFill(0,0,((disp_x_size+1)*(disp_y_size+1)));
  
}

void RedScr()
{

  clrXY();

  fastFill(0xFF,0x00,((disp_x_size+1)*(disp_y_size+1)));
  
}

void fastFill(uint8_t bitHigh, uint8_t bitLow, long pix)
{
  long blocks;

  uint16_t data = (bitHigh << 8) | (bitLow & 0xFF);

  REG_PORT_DIRSET1 = LCD_BUS;  //Set PB00 - PB15 as output
  REG_PORT_OUTCLR1 = LCD_BUS;  //clear bits
  
  // Write data to PB00..PB15
  REG_PORT_OUTSET1 = data;       //set PB00..PB15 to data

  blocks = pix/16;

  //
  //Keep the bus at the desired color, and pulse WR low
  //for every pixel. This is broken up into blocks of 16
  //(for some reason).
  //
  for(int i = 0; i<blocks; i++)
  {
    pulse_WR_Low();   //1
    pulse_WR_Low();   //2
    pulse_WR_Low();   //3
    pulse_WR_Low();   //4
    pulse_WR_Low();   //5
    pulse_WR_Low();   //6
    pulse_WR_Low();   //7
    pulse_WR_Low();   //8
    pulse_WR_Low();   //9
    pulse_WR_Low();   //10
    pulse_WR_Low();   //11
    pulse_WR_Low();   //12
    pulse_WR_Low();   //13
    pulse_WR_Low();   //14
    pulse_WR_Low();   //15
    pulse_WR_Low();   //16
  }

  //after that's done, clean up the remaining parts that isn't % 16
  if ((pix % 16) != 0)
    for(int i=0 ; i<(pix%16)+1 ; i++)
    {
      pulse_WR_Low();   //
    }

  //set the LCD bus back to 0
  REG_PORT_OUTCLR0 = LCD_BUS;
  
}

/*
 * initLCD()
 * 
 * YOU LOOK AT THIS AND
 * TELL ME THERE'S A GOD
 */
void initLCD() 
{
  /* 
   *  Power supply on
   *  Hardware reset
   *  Wait 5ms or more
   *  SET SPLOUT 11100h // sleep out command
   *  Wait 5ms or more
   *  SET DSPON (2900h) // Display on command
   *  
   */

   
  REG_PORT_OUTSET0 = LCD_RST; //Reset = 1
  delay(5);
  REG_PORT_OUTCLR0 = LCD_RST; //Reset = 0
  delay(15);
  REG_PORT_OUTSET0 = LCD_RST; //Reset = 1
  delay(15);

  REG_PORT_OUTCLR0 = LCD_CS;

  LCD_Write_Command(0xF0,0x00);LCD_Write_Data(0x55);

  // Up until this line works. 
  
  LCD_Write_Command(0xF0,0x01);LCD_Write_Data(0xAA);
  LCD_Write_Command(0xF0,0x02);LCD_Write_Data(0x52);
  LCD_Write_Command(0xF0,0x03);LCD_Write_Data(0x08);
  LCD_Write_Command(0xF0,0x04);LCD_Write_Data(0x01);
  
  //#AVDD Set AVDD 5.2V
  LCD_Write_Command(0xB0,0x00);LCD_Write_Data(0x0D);
  LCD_Write_Command(0xB0,0x01);LCD_Write_Data(0x0D);
  LCD_Write_Command(0xB0,0x02);LCD_Write_Data(0x0D);
  
  //#AVDD ratio
  LCD_Write_Command(0xB6,0x00);LCD_Write_Data(0x34);
  LCD_Write_Command(0xB6,0x01);LCD_Write_Data(0x34);
  LCD_Write_Command(0xB6,0x02);LCD_Write_Data(0x34);
   
  //#AVEE  -5.2V
  LCD_Write_Command(0xB1,0x00);LCD_Write_Data(0x0D);
  LCD_Write_Command(0xB1,0x01);LCD_Write_Data(0x0D);
  LCD_Write_Command(0xB1,0x02);LCD_Write_Data(0x0D);
  
  //#AVEE ratio
  LCD_Write_Command(0xB7,0x00);LCD_Write_Data(0x34);
  LCD_Write_Command(0xB7,0x01);LCD_Write_Data(0x34);
  LCD_Write_Command(0xB7,0x02);LCD_Write_Data(0x34);
  
  //#VCL  -2.5V
  LCD_Write_Command(0xB2,0x00);LCD_Write_Data(0x00);
  LCD_Write_Command(0xB2,0x01);LCD_Write_Data(0x00);
  LCD_Write_Command(0xB2,0x02);LCD_Write_Data(0x00);
  
  //#VCL ratio
  LCD_Write_Command(0xB8,0x00);LCD_Write_Data(0x24);
  LCD_Write_Command(0xB8,0x01);LCD_Write_Data(0x24);
  LCD_Write_Command(0xB8,0x02);LCD_Write_Data(0x24); 
  
  //#VGH  15V
  LCD_Write_Command(0xBF,0x00);LCD_Write_Data(0x01);
  LCD_Write_Command(0xB3,0x00);LCD_Write_Data(0x0F);
  LCD_Write_Command(0xB3,0x01);LCD_Write_Data(0x0F);
  LCD_Write_Command(0xB3,0x02);LCD_Write_Data(0x0F);
  
  //#VGH  ratio
  LCD_Write_Command(0xB9,0x00);LCD_Write_Data(0x34);
  LCD_Write_Command(0xB9,0x01);LCD_Write_Data(0x34);
  LCD_Write_Command(0xB9,0x02);LCD_Write_Data(0x34); 
  
  //#VGL_REG  -10V
  LCD_Write_Command(0xB5,0x00);LCD_Write_Data(0x08);
  LCD_Write_Command(0xB5,0x00);LCD_Write_Data(0x08);
  LCD_Write_Command(0xB5,0x01);LCD_Write_Data(0x08);
  LCD_Write_Command(0xC2,0x00);LCD_Write_Data(0x03);
  
  //#VGLX  ratio
  LCD_Write_Command(0xBA,0x00);LCD_Write_Data(0x24);
  LCD_Write_Command(0xBA,0x01);LCD_Write_Data(0x24);
  LCD_Write_Command(0xBA,0x02);LCD_Write_Data(0x24);
  
  //#VGMP/VGSP 4.5V/0V
  LCD_Write_Command(0xBC,0x00);LCD_Write_Data(0x00);
  LCD_Write_Command(0xBC,0x01);LCD_Write_Data(0x78);
  LCD_Write_Command(0xBC,0x02);LCD_Write_Data(0x00);
  
  //#VGMN/VGSN -4.5V/0V
  LCD_Write_Command(0xBD,0x00);LCD_Write_Data(0x00);
  LCD_Write_Command(0xBD,0x01);LCD_Write_Data(0x78);
  LCD_Write_Command(0xBD,0x02);LCD_Write_Data(0x00);
  
  //#VCOM  -1.325V
  LCD_Write_Command(0xBE,0x00);LCD_Write_Data(0x00);
  LCD_Write_Command(0xBE,0x01);LCD_Write_Data(0x89);//69
  
   //Gamma Setting   
  LCD_Write_Command(0xD1,0x00);LCD_Write_Data(0x00);
  LCD_Write_Command(0xD1,0x01);LCD_Write_Data(0x2D);
  LCD_Write_Command(0xD1,0x02);LCD_Write_Data(0x00);
  LCD_Write_Command(0xD1,0x03);LCD_Write_Data(0x2E);
  LCD_Write_Command(0xD1,0x04);LCD_Write_Data(0x00); 
  LCD_Write_Command(0xD1,0x05);LCD_Write_Data(0x32);
  LCD_Write_Command(0xD1,0x06);LCD_Write_Data(0x00);
  LCD_Write_Command(0xD1,0x07);LCD_Write_Data(0x44);
  LCD_Write_Command(0xD1,0x08);LCD_Write_Data(0x00);
  LCD_Write_Command(0xD1,0x09);LCD_Write_Data(0x53);
  LCD_Write_Command(0xD1,0x0A);LCD_Write_Data(0x00);
  LCD_Write_Command(0xD1,0x0B);LCD_Write_Data(0x88);
  LCD_Write_Command(0xD1,0x0C);LCD_Write_Data(0x00);
  LCD_Write_Command(0xD1,0x0D);LCD_Write_Data(0xB6);
  LCD_Write_Command(0xD1,0x0E);LCD_Write_Data(0x00);
  LCD_Write_Command(0xD1,0x0F);LCD_Write_Data(0xF3);  //
  LCD_Write_Command(0xD1,0x10);LCD_Write_Data(0x01);
  LCD_Write_Command(0xD1,0x11);LCD_Write_Data(0x22);
  LCD_Write_Command(0xD1,0x12);LCD_Write_Data(0x01);
  LCD_Write_Command(0xD1,0x13);LCD_Write_Data(0x64);
  LCD_Write_Command(0xD1,0x14);LCD_Write_Data(0x01);
  LCD_Write_Command(0xD1,0x15);LCD_Write_Data(0x92);
  LCD_Write_Command(0xD1,0x16);LCD_Write_Data(0x01);
  LCD_Write_Command(0xD1,0x17);LCD_Write_Data(0xD4);
  LCD_Write_Command(0xD1,0x18);LCD_Write_Data(0x02);  
  LCD_Write_Command(0xD1,0x19);LCD_Write_Data(0x07);
  LCD_Write_Command(0xD1,0x1A);LCD_Write_Data(0x02);
  LCD_Write_Command(0xD1,0x1B);LCD_Write_Data(0x08);
  LCD_Write_Command(0xD1,0x1C);LCD_Write_Data(0x02);
  LCD_Write_Command(0xD1,0x1D);LCD_Write_Data(0x34);
  LCD_Write_Command(0xD1,0x1E);LCD_Write_Data(0x02);
  LCD_Write_Command(0xD1,0x1F);LCD_Write_Data(0x5F); //
  LCD_Write_Command(0xD1,0x20);LCD_Write_Data(0x02);
  LCD_Write_Command(0xD1,0x21);LCD_Write_Data(0x78);
  LCD_Write_Command(0xD1,0x22);LCD_Write_Data(0x02);
  LCD_Write_Command(0xD1,0x23);LCD_Write_Data(0x94);
  LCD_Write_Command(0xD1,0x24);LCD_Write_Data(0x02);
  LCD_Write_Command(0xD1,0x25);LCD_Write_Data(0xA6);
  LCD_Write_Command(0xD1,0x26);LCD_Write_Data(0x02);
  LCD_Write_Command(0xD1,0x27);LCD_Write_Data(0xBB);
  LCD_Write_Command(0xD1,0x28);LCD_Write_Data(0x02); 
  LCD_Write_Command(0xD1,0x29);LCD_Write_Data(0xCA);
  LCD_Write_Command(0xD1,0x2A);LCD_Write_Data(0x02);
  LCD_Write_Command(0xD1,0x2B);LCD_Write_Data(0xDB);
  LCD_Write_Command(0xD1,0x2C);LCD_Write_Data(0x02);
  LCD_Write_Command(0xD1,0x2D);LCD_Write_Data(0xE8);
  LCD_Write_Command(0xD1,0x2E);LCD_Write_Data(0x02);
  LCD_Write_Command(0xD1,0x2F);LCD_Write_Data(0xF9); //
  LCD_Write_Command(0xD1,0x30);LCD_Write_Data(0x03); 
  LCD_Write_Command(0xD1,0x31);LCD_Write_Data(0x1F);
  LCD_Write_Command(0xD1,0x32);LCD_Write_Data(0x03);
  LCD_Write_Command(0xD1,0x33);LCD_Write_Data(0x7F);
       
  LCD_Write_Command(0xD2,0x00);LCD_Write_Data(0x00);
  LCD_Write_Command(0xD2,0x01);LCD_Write_Data(0x2D);
  LCD_Write_Command(0xD2,0x02);LCD_Write_Data(0x00);
  LCD_Write_Command(0xD2,0x03);LCD_Write_Data(0x2E);
  LCD_Write_Command(0xD2,0x04);LCD_Write_Data(0x00); 
  LCD_Write_Command(0xD2,0x05);LCD_Write_Data(0x32);
  LCD_Write_Command(0xD2,0x06);LCD_Write_Data(0x00);
  LCD_Write_Command(0xD2,0x07);LCD_Write_Data(0x44);
  LCD_Write_Command(0xD2,0x08);LCD_Write_Data(0x00);
  LCD_Write_Command(0xD2,0x09);LCD_Write_Data(0x53);
  LCD_Write_Command(0xD2,0x0A);LCD_Write_Data(0x00);
  LCD_Write_Command(0xD2,0x0B);LCD_Write_Data(0x88);
  LCD_Write_Command(0xD2,0x0C);LCD_Write_Data(0x00);
  LCD_Write_Command(0xD2,0x0D);LCD_Write_Data(0xB6);
  LCD_Write_Command(0xD2,0x0E);LCD_Write_Data(0x00);
  LCD_Write_Command(0xD2,0x0F);LCD_Write_Data(0xF3);  //
  LCD_Write_Command(0xD2,0x10);LCD_Write_Data(0x01);
  LCD_Write_Command(0xD2,0x11);LCD_Write_Data(0x22);
  LCD_Write_Command(0xD2,0x12);LCD_Write_Data(0x01);
  LCD_Write_Command(0xD2,0x13);LCD_Write_Data(0x64);
  LCD_Write_Command(0xD2,0x14);LCD_Write_Data(0x01);
  LCD_Write_Command(0xD2,0x15);LCD_Write_Data(0x92);
  LCD_Write_Command(0xD2,0x16);LCD_Write_Data(0x01);
  LCD_Write_Command(0xD2,0x17);LCD_Write_Data(0xD4);
  LCD_Write_Command(0xD2,0x18);LCD_Write_Data(0x02);  
  LCD_Write_Command(0xD2,0x19);LCD_Write_Data(0x07);
  LCD_Write_Command(0xD2,0x1A);LCD_Write_Data(0x02);
  LCD_Write_Command(0xD2,0x1B);LCD_Write_Data(0x08);
  LCD_Write_Command(0xD2,0x1C);LCD_Write_Data(0x02);
  LCD_Write_Command(0xD2,0x1D);LCD_Write_Data(0x34);
  LCD_Write_Command(0xD2,0x1E);LCD_Write_Data(0x02);
  LCD_Write_Command(0xD2,0x1F);LCD_Write_Data(0x5F); //
  LCD_Write_Command(0xD2,0x20);LCD_Write_Data(0x02);
  LCD_Write_Command(0xD2,0x21);LCD_Write_Data(0x78);
  LCD_Write_Command(0xD2,0x22);LCD_Write_Data(0x02);
  LCD_Write_Command(0xD2,0x23);LCD_Write_Data(0x94);
  LCD_Write_Command(0xD2,0x24);LCD_Write_Data(0x02);
  LCD_Write_Command(0xD2,0x25);LCD_Write_Data(0xA6);
  LCD_Write_Command(0xD2,0x26);LCD_Write_Data(0x02);
  LCD_Write_Command(0xD2,0x27);LCD_Write_Data(0xBB);
  LCD_Write_Command(0xD2,0x28);LCD_Write_Data(0x02); 
  LCD_Write_Command(0xD2,0x29);LCD_Write_Data(0xCA);
  LCD_Write_Command(0xD2,0x2A);LCD_Write_Data(0x02);
  LCD_Write_Command(0xD2,0x2B);LCD_Write_Data(0xDB);
  LCD_Write_Command(0xD2,0x2C);LCD_Write_Data(0x02);
  LCD_Write_Command(0xD2,0x2D);LCD_Write_Data(0xE8);
  LCD_Write_Command(0xD2,0x2E);LCD_Write_Data(0x02);
  LCD_Write_Command(0xD2,0x2F);LCD_Write_Data(0xF9); //
  LCD_Write_Command(0xD2,0x30);LCD_Write_Data(0x03); 
  LCD_Write_Command(0xD2,0x31);LCD_Write_Data(0x1F);
  LCD_Write_Command(0xD2,0x32);LCD_Write_Data(0x03);
  LCD_Write_Command(0xD2,0x33);LCD_Write_Data(0x7F);
     
  LCD_Write_Command(0xD3,0x00);LCD_Write_Data(0x00);
  LCD_Write_Command(0xD3,0x01);LCD_Write_Data(0x2D);
  LCD_Write_Command(0xD3,0x02);LCD_Write_Data(0x00);
  LCD_Write_Command(0xD3,0x03);LCD_Write_Data(0x2E);
  LCD_Write_Command(0xD3,0x04);LCD_Write_Data(0x00); 
  LCD_Write_Command(0xD3,0x05);LCD_Write_Data(0x32);
  LCD_Write_Command(0xD3,0x06);LCD_Write_Data(0x00);
  LCD_Write_Command(0xD3,0x07);LCD_Write_Data(0x44);
  LCD_Write_Command(0xD3,0x08);LCD_Write_Data(0x00);
  LCD_Write_Command(0xD3,0x09);LCD_Write_Data(0x53);
  LCD_Write_Command(0xD3,0x0A);LCD_Write_Data(0x00);
  LCD_Write_Command(0xD3,0x0B);LCD_Write_Data(0x88);
  LCD_Write_Command(0xD3,0x0C);LCD_Write_Data(0x00);
  LCD_Write_Command(0xD3,0x0D);LCD_Write_Data(0xB6);
  LCD_Write_Command(0xD3,0x0E);LCD_Write_Data(0x00);
  LCD_Write_Command(0xD3,0x0F);LCD_Write_Data(0xF3);  //
  LCD_Write_Command(0xD3,0x10);LCD_Write_Data(0x01);
  LCD_Write_Command(0xD3,0x11);LCD_Write_Data(0x22);
  LCD_Write_Command(0xD3,0x12);LCD_Write_Data(0x01);
  LCD_Write_Command(0xD3,0x13);LCD_Write_Data(0x64);
  LCD_Write_Command(0xD3,0x14);LCD_Write_Data(0x01);
  LCD_Write_Command(0xD3,0x15);LCD_Write_Data(0x92);
  LCD_Write_Command(0xD3,0x16);LCD_Write_Data(0x01);
  LCD_Write_Command(0xD3,0x17);LCD_Write_Data(0xD4);
  LCD_Write_Command(0xD3,0x18);LCD_Write_Data(0x02);  
  LCD_Write_Command(0xD3,0x19);LCD_Write_Data(0x07);
  LCD_Write_Command(0xD3,0x1A);LCD_Write_Data(0x02);
  LCD_Write_Command(0xD3,0x1B);LCD_Write_Data(0x08);
  LCD_Write_Command(0xD3,0x1C);LCD_Write_Data(0x02);
  LCD_Write_Command(0xD3,0x1D);LCD_Write_Data(0x34);
  LCD_Write_Command(0xD3,0x1E);LCD_Write_Data(0x02);
  LCD_Write_Command(0xD3,0x1F);LCD_Write_Data(0x5F); //
  LCD_Write_Command(0xD3,0x20);LCD_Write_Data(0x02);
  LCD_Write_Command(0xD3,0x21);LCD_Write_Data(0x78);
  LCD_Write_Command(0xD3,0x22);LCD_Write_Data(0x02);
  LCD_Write_Command(0xD3,0x23);LCD_Write_Data(0x94);
  LCD_Write_Command(0xD3,0x24);LCD_Write_Data(0x02);
  LCD_Write_Command(0xD3,0x25);LCD_Write_Data(0xA6);
  LCD_Write_Command(0xD3,0x26);LCD_Write_Data(0x02);
  LCD_Write_Command(0xD3,0x27);LCD_Write_Data(0xBB);
  LCD_Write_Command(0xD3,0x28);LCD_Write_Data(0x02); 
  LCD_Write_Command(0xD3,0x29);LCD_Write_Data(0xCA);
  LCD_Write_Command(0xD3,0x2A);LCD_Write_Data(0x02);
  LCD_Write_Command(0xD3,0x2B);LCD_Write_Data(0xDB);
  LCD_Write_Command(0xD3,0x2C);LCD_Write_Data(0x02);
  LCD_Write_Command(0xD3,0x2D);LCD_Write_Data(0xE8);
  LCD_Write_Command(0xD3,0x2E);LCD_Write_Data(0x02);
  LCD_Write_Command(0xD3,0x2F);LCD_Write_Data(0xF9); //
  LCD_Write_Command(0xD3,0x30);LCD_Write_Data(0x03); 
  LCD_Write_Command(0xD3,0x31);LCD_Write_Data(0x1F);
  LCD_Write_Command(0xD3,0x32);LCD_Write_Data(0x03);
  LCD_Write_Command(0xD3,0x33);LCD_Write_Data(0x7F);
     
  LCD_Write_Command(0xD4,0x00);LCD_Write_Data(0x00);
  LCD_Write_Command(0xD4,0x01);LCD_Write_Data(0x2D);
  LCD_Write_Command(0xD4,0x02);LCD_Write_Data(0x00);
  LCD_Write_Command(0xD4,0x03);LCD_Write_Data(0x2E);
  LCD_Write_Command(0xD4,0x04);LCD_Write_Data(0x00); 
  LCD_Write_Command(0xD4,0x05);LCD_Write_Data(0x32);
  LCD_Write_Command(0xD4,0x06);LCD_Write_Data(0x00);
  LCD_Write_Command(0xD4,0x07);LCD_Write_Data(0x44);
  LCD_Write_Command(0xD4,0x08);LCD_Write_Data(0x00);
  LCD_Write_Command(0xD4,0x09);LCD_Write_Data(0x53);
  LCD_Write_Command(0xD4,0x0A);LCD_Write_Data(0x00);
  LCD_Write_Command(0xD4,0x0B);LCD_Write_Data(0x88);
  LCD_Write_Command(0xD4,0x0C);LCD_Write_Data(0x00);
  LCD_Write_Command(0xD4,0x0D);LCD_Write_Data(0xB6);
  LCD_Write_Command(0xD4,0x0E);LCD_Write_Data(0x00);
  LCD_Write_Command(0xD4,0x0F);LCD_Write_Data(0xF3);  //
  LCD_Write_Command(0xD4,0x10);LCD_Write_Data(0x01);
  LCD_Write_Command(0xD4,0x11);LCD_Write_Data(0x22);
  LCD_Write_Command(0xD4,0x12);LCD_Write_Data(0x01);
  LCD_Write_Command(0xD4,0x13);LCD_Write_Data(0x64);
  LCD_Write_Command(0xD4,0x14);LCD_Write_Data(0x01);
  LCD_Write_Command(0xD4,0x15);LCD_Write_Data(0x92);
  LCD_Write_Command(0xD4,0x16);LCD_Write_Data(0x01);
  LCD_Write_Command(0xD4,0x17);LCD_Write_Data(0xD4);
  LCD_Write_Command(0xD4,0x18);LCD_Write_Data(0x02);  
  LCD_Write_Command(0xD4,0x19);LCD_Write_Data(0x07);
  LCD_Write_Command(0xD4,0x1A);LCD_Write_Data(0x02);
  LCD_Write_Command(0xD4,0x1B);LCD_Write_Data(0x08);
  LCD_Write_Command(0xD4,0x1C);LCD_Write_Data(0x02);
  LCD_Write_Command(0xD4,0x1D);LCD_Write_Data(0x34);
  LCD_Write_Command(0xD4,0x1E);LCD_Write_Data(0x02);
  LCD_Write_Command(0xD4,0x1F);LCD_Write_Data(0x5F); //
  LCD_Write_Command(0xD4,0x20);LCD_Write_Data(0x02);
  LCD_Write_Command(0xD4,0x21);LCD_Write_Data(0x78);
  LCD_Write_Command(0xD4,0x22);LCD_Write_Data(0x02);
  LCD_Write_Command(0xD4,0x23);LCD_Write_Data(0x94);
  LCD_Write_Command(0xD4,0x24);LCD_Write_Data(0x02);
  LCD_Write_Command(0xD4,0x25);LCD_Write_Data(0xA6);
  LCD_Write_Command(0xD4,0x26);LCD_Write_Data(0x02);
  LCD_Write_Command(0xD4,0x27);LCD_Write_Data(0xBB);
  LCD_Write_Command(0xD4,0x28);LCD_Write_Data(0x02); 
  LCD_Write_Command(0xD4,0x29);LCD_Write_Data(0xCA);
  LCD_Write_Command(0xD4,0x2A);LCD_Write_Data(0x02);
  LCD_Write_Command(0xD4,0x2B);LCD_Write_Data(0xDB);
  LCD_Write_Command(0xD4,0x2C);LCD_Write_Data(0x02);
  LCD_Write_Command(0xD4,0x2D);LCD_Write_Data(0xE8);
  LCD_Write_Command(0xD4,0x2E);LCD_Write_Data(0x02);
  LCD_Write_Command(0xD4,0x2F);LCD_Write_Data(0xF9); //
  LCD_Write_Command(0xD4,0x30);LCD_Write_Data(0x03); 
  LCD_Write_Command(0xD4,0x31);LCD_Write_Data(0x1F);
  LCD_Write_Command(0xD4,0x32);LCD_Write_Data(0x03);
  LCD_Write_Command(0xD4,0x33);LCD_Write_Data(0x7F);
     
  LCD_Write_Command(0xD5,0x00);LCD_Write_Data(0x00);
  LCD_Write_Command(0xD5,0x01);LCD_Write_Data(0x2D);
  LCD_Write_Command(0xD5,0x02);LCD_Write_Data(0x00);
  LCD_Write_Command(0xD5,0x03);LCD_Write_Data(0x2E);
  LCD_Write_Command(0xD5,0x04);LCD_Write_Data(0x00); 
  LCD_Write_Command(0xD5,0x05);LCD_Write_Data(0x32);
  LCD_Write_Command(0xD5,0x06);LCD_Write_Data(0x00);
  LCD_Write_Command(0xD5,0x07);LCD_Write_Data(0x44);
  LCD_Write_Command(0xD5,0x08);LCD_Write_Data(0x00);
  LCD_Write_Command(0xD5,0x09);LCD_Write_Data(0x53);
  LCD_Write_Command(0xD5,0x0A);LCD_Write_Data(0x00);
  LCD_Write_Command(0xD5,0x0B);LCD_Write_Data(0x88);
  LCD_Write_Command(0xD5,0x0C);LCD_Write_Data(0x00);
  LCD_Write_Command(0xD5,0x0D);LCD_Write_Data(0xB6);
  LCD_Write_Command(0xD5,0x0E);LCD_Write_Data(0x00);
  LCD_Write_Command(0xD5,0x0F);LCD_Write_Data(0xF3);  //
  LCD_Write_Command(0xD5,0x10);LCD_Write_Data(0x01);
  LCD_Write_Command(0xD5,0x11);LCD_Write_Data(0x22);
  LCD_Write_Command(0xD5,0x12);LCD_Write_Data(0x01);
  LCD_Write_Command(0xD5,0x13);LCD_Write_Data(0x64);
  LCD_Write_Command(0xD5,0x14);LCD_Write_Data(0x01);
  LCD_Write_Command(0xD5,0x15);LCD_Write_Data(0x92);
  LCD_Write_Command(0xD5,0x16);LCD_Write_Data(0x01);
  LCD_Write_Command(0xD5,0x17);LCD_Write_Data(0xD4);
  LCD_Write_Command(0xD5,0x18);LCD_Write_Data(0x02);  
  LCD_Write_Command(0xD5,0x19);LCD_Write_Data(0x07);
  LCD_Write_Command(0xD5,0x1A);LCD_Write_Data(0x02);
  LCD_Write_Command(0xD5,0x1B);LCD_Write_Data(0x08);
  LCD_Write_Command(0xD5,0x1C);LCD_Write_Data(0x02);
  LCD_Write_Command(0xD5,0x1D);LCD_Write_Data(0x34);
  LCD_Write_Command(0xD5,0x1E);LCD_Write_Data(0x02);
  LCD_Write_Command(0xD5,0x1F);LCD_Write_Data(0x5F); //
  LCD_Write_Command(0xD5,0x20);LCD_Write_Data(0x02);
  LCD_Write_Command(0xD5,0x21);LCD_Write_Data(0x78);
  LCD_Write_Command(0xD5,0x22);LCD_Write_Data(0x02);
  LCD_Write_Command(0xD5,0x23);LCD_Write_Data(0x94);
  LCD_Write_Command(0xD5,0x24);LCD_Write_Data(0x02);
  LCD_Write_Command(0xD5,0x25);LCD_Write_Data(0xA6);
  LCD_Write_Command(0xD5,0x26);LCD_Write_Data(0x02);
  LCD_Write_Command(0xD5,0x27);LCD_Write_Data(0xBB);
  LCD_Write_Command(0xD5,0x28);LCD_Write_Data(0x02); 
  LCD_Write_Command(0xD5,0x29);LCD_Write_Data(0xCA);
  LCD_Write_Command(0xD5,0x2A);LCD_Write_Data(0x02);
  LCD_Write_Command(0xD5,0x2B);LCD_Write_Data(0xDB);
  LCD_Write_Command(0xD5,0x2C);LCD_Write_Data(0x02);
  LCD_Write_Command(0xD5,0x2D);LCD_Write_Data(0xE8);
  LCD_Write_Command(0xD5,0x2E);LCD_Write_Data(0x02);
  LCD_Write_Command(0xD5,0x2F);LCD_Write_Data(0xF9); //
  LCD_Write_Command(0xD5,0x30);LCD_Write_Data(0x03); 
  LCD_Write_Command(0xD5,0x31);LCD_Write_Data(0x1F);
  LCD_Write_Command(0xD5,0x32);LCD_Write_Data(0x03);
  LCD_Write_Command(0xD5,0x33);LCD_Write_Data(0x7F);
     
  LCD_Write_Command(0xD6,0x00);LCD_Write_Data(0x00);
  LCD_Write_Command(0xD6,0x01);LCD_Write_Data(0x2D);
  LCD_Write_Command(0xD6,0x02);LCD_Write_Data(0x00);
  LCD_Write_Command(0xD6,0x03);LCD_Write_Data(0x2E);
  LCD_Write_Command(0xD6,0x04);LCD_Write_Data(0x00); 
  LCD_Write_Command(0xD6,0x05);LCD_Write_Data(0x32);
  LCD_Write_Command(0xD6,0x06);LCD_Write_Data(0x00);
  LCD_Write_Command(0xD6,0x07);LCD_Write_Data(0x44);
  LCD_Write_Command(0xD6,0x08);LCD_Write_Data(0x00);
  LCD_Write_Command(0xD6,0x09);LCD_Write_Data(0x53);
  LCD_Write_Command(0xD6,0x0A);LCD_Write_Data(0x00);
  LCD_Write_Command(0xD6,0x0B);LCD_Write_Data(0x88);
  LCD_Write_Command(0xD6,0x0C);LCD_Write_Data(0x00);
  LCD_Write_Command(0xD6,0x0D);LCD_Write_Data(0xB6);
  LCD_Write_Command(0xD6,0x0E);LCD_Write_Data(0x00);
  LCD_Write_Command(0xD6,0x0F);LCD_Write_Data(0xF3);  //
  LCD_Write_Command(0xD6,0x10);LCD_Write_Data(0x01);
  LCD_Write_Command(0xD6,0x11);LCD_Write_Data(0x22);
  LCD_Write_Command(0xD6,0x12);LCD_Write_Data(0x01);
  LCD_Write_Command(0xD6,0x13);LCD_Write_Data(0x64);
  LCD_Write_Command(0xD6,0x14);LCD_Write_Data(0x01);
  LCD_Write_Command(0xD6,0x15);LCD_Write_Data(0x92);
  LCD_Write_Command(0xD6,0x16);LCD_Write_Data(0x01);
  LCD_Write_Command(0xD6,0x17);LCD_Write_Data(0xD4);
  LCD_Write_Command(0xD6,0x18);LCD_Write_Data(0x02);  
  LCD_Write_Command(0xD6,0x19);LCD_Write_Data(0x07);
  LCD_Write_Command(0xD6,0x1A);LCD_Write_Data(0x02);
  LCD_Write_Command(0xD6,0x1B);LCD_Write_Data(0x08);
  LCD_Write_Command(0xD6,0x1C);LCD_Write_Data(0x02);
  LCD_Write_Command(0xD6,0x1D);LCD_Write_Data(0x34);
  LCD_Write_Command(0xD6,0x1E);LCD_Write_Data(0x02);
  LCD_Write_Command(0xD6,0x1F);LCD_Write_Data(0x5F); //
  LCD_Write_Command(0xD6,0x20);LCD_Write_Data(0x02);
  LCD_Write_Command(0xD6,0x21);LCD_Write_Data(0x78);
  LCD_Write_Command(0xD6,0x22);LCD_Write_Data(0x02);
  LCD_Write_Command(0xD6,0x23);LCD_Write_Data(0x94);
  LCD_Write_Command(0xD6,0x24);LCD_Write_Data(0x02);
  LCD_Write_Command(0xD6,0x25);LCD_Write_Data(0xA6);
  LCD_Write_Command(0xD6,0x26);LCD_Write_Data(0x02);
  LCD_Write_Command(0xD6,0x27);LCD_Write_Data(0xBB);
  LCD_Write_Command(0xD6,0x28);LCD_Write_Data(0x02); 
  LCD_Write_Command(0xD6,0x29);LCD_Write_Data(0xCA);
  LCD_Write_Command(0xD6,0x2A);LCD_Write_Data(0x02);
  LCD_Write_Command(0xD6,0x2B);LCD_Write_Data(0xDB);
  LCD_Write_Command(0xD6,0x2C);LCD_Write_Data(0x02);
  LCD_Write_Command(0xD6,0x2D);LCD_Write_Data(0xE8);
  LCD_Write_Command(0xD6,0x2E);LCD_Write_Data(0x02);
  LCD_Write_Command(0xD6,0x2F);LCD_Write_Data(0xF9); //
  LCD_Write_Command(0xD6,0x30);LCD_Write_Data(0x03); 
  LCD_Write_Command(0xD6,0x31);LCD_Write_Data(0x1F);
  LCD_Write_Command(0xD6,0x32);LCD_Write_Data(0x03);
  LCD_Write_Command(0xD6,0x33);LCD_Write_Data(0x7F);
   
  //#LV2 Page 0 enable
  LCD_Write_Command(0xF0,0x00);LCD_Write_Data(0x55);
  LCD_Write_Command(0xF0,0x01);LCD_Write_Data(0xAA);
  LCD_Write_Command(0xF0,0x02);LCD_Write_Data(0x52);
  LCD_Write_Command(0xF0,0x03);LCD_Write_Data(0x08);
  LCD_Write_Command(0xF0,0x04);LCD_Write_Data(0x00); 
  
  //#DISPLAY CONTROL
  LCD_Write_Command(0xB1,0x00);LCD_Write_Data(0xCC);
  LCD_Write_Command(0xB1,0x01);LCD_Write_Data(0x00); 
   
  //#SOURCE HOLD TIME
  LCD_Write_Command(0xB6,0x00);LCD_Write_Data(0x05);
  
  //Set Gate EQ     
  LCD_Write_Command(0xB7,0x00);LCD_Write_Data(0x70); 
  LCD_Write_Command(0xB7,0x01);LCD_Write_Data(0x70);
  
  //#Source EQ control (Mode 2)
  LCD_Write_Command(0xB8,0x00);LCD_Write_Data(0x01);
  LCD_Write_Command(0xB8,0x01);LCD_Write_Data(0x03);
  LCD_Write_Command(0xB8,0x02);LCD_Write_Data(0x03);
  LCD_Write_Command(0xB8,0x03);LCD_Write_Data(0x03);
  
  //#INVERSION MODE
  LCD_Write_Command(0xBC,0x00);LCD_Write_Data(0x02);
  LCD_Write_Command(0xBC,0x01);LCD_Write_Data(0x00);  
  LCD_Write_Command(0xBC,0x02);LCD_Write_Data(0x00); 
  
  //#Timing control
  LCD_Write_Command(0xC9,0x00);LCD_Write_Data(0xD0);   
  LCD_Write_Command(0xC9,0x01);LCD_Write_Data(0x02);
  LCD_Write_Command(0xC9,0x02);LCD_Write_Data(0x50);
  LCD_Write_Command(0xC9,0x03);LCD_Write_Data(0x50); 
  LCD_Write_Command(0xC9,0x04);LCD_Write_Data(0x50); 
  

  LCD_Write_Command(0x35,0x00);   LCD_Write_Data(0x00); 


  LCD_Write_Command(0x3A,0x00);   LCD_Write_Data(0x55); //Data format 16-Bits

  LCD_Write_Command(0x36,0x00);   LCD_Write_Data(0x00);   


  LCD_Write_Command(0x11,0x00);   //StartUp  
  
  delay(120);

  LCD_Write_Command(0x29,0x00);   //display On

  delay(100);

  
}
