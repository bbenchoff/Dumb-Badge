/**************************This is 80 width line*******************************/

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
*/
#include <asf.h>
#include "config_usart.h"

/** MACROS ********************************************************************/
#define LCD_Reset	PORT_PB30
#define LCD_CS		PORT_PB22
#define LCD_WR		PORT_PB17
#define LCD_DC		PORT_PB23
#define LCD_RD		PORT_PB16


#define SwapUint16(x , y) { uint16_t temp = x; x = y; y = temp; }

/** VARIABLES *****************************************************************/

uint16_t fore_Color_High, fore_Color_Low, back_Color_High, back_Color_Low;

uint16_t display_X_size = 479;
uint16_t display_Y_size = 799;


/*
/	Fix this serial number thing because it doesn't work.
/	I think you need pointers.
*/
static uint16_t chip_Serial_Number = (0x0080A00C ^ 0x0080A040 ^ 
									0x0080A044 ^ 0x0080A048);

/** LOCAL PROTOTYPES **********************************************************/

void InitLCD(void);
void LCD_Write_Bus(char VH, char VL);
void LCD_Write_COM16(char VH, char VL);
void LCD_Write_COM8(char VL);
void LCD_Write_DATA16(char VH, char VL);
void LCD_Write_DATA8(char VL);

void setColorRGB(uint8_t r, uint8_t g, uint8_t b);
void setColorHex(uint16_t color);
void setBackColorRGB(unsigned char r, unsigned char g, unsigned char b);
void setBackColorHex(uint16_t color);

void clrScr(void);
void clrXY(void);
void setXY(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
void setPixel(uint16_t color);
void drawPixel(int x, int y);



void fillRect(int x1, int y1, int x2, int y2);
void LCD_Fast_Fill(int ch, int cl, long pix);
void drawKare(int emotion);

void configure_usart_USB(void);

struct usart_module usart_USB;



/** STUFF BEGINS HERE *********************************************************/
int main (void)
{

	/* Pin Initialization, begin with pin cleared */
	REG_PORT_DIRSET1 = 0x0000ffff;		//LCD data bus, PB00 - PB15
	REG_PORT_DIRSET1 = LCD_Reset;
	REG_PORT_DIRSET1 = LCD_CS;
	REG_PORT_DIRSET1 = LCD_WR;
	REG_PORT_DIRSET1 = LCD_DC;
	REG_PORT_DIRSET1 = LCD_RD;
	
	REG_PORT_OUTCLR1 = 0x0000ffff;
	REG_PORT_OUTCLR1 = LCD_Reset;
	REG_PORT_OUTCLR1 = LCD_CS;
	REG_PORT_OUTCLR1 = LCD_WR;
	REG_PORT_OUTCLR1 = LCD_DC;
	REG_PORT_OUTCLR1 = LCD_RD;
	
	system_init();
	delay_init();
	//srand(chip_Serial_Number);
	configure_usart_USB();
	
	configure_console();
	
	printf("Hello World\n\r");
	
	InitLCD();
	clrScr();

	uint8_t red, green, blue;
	red = 0;
	green = 128;
	blue = 64;

	while (1) {
		
		if(red > 0 && blue == 0)
		{
			red--;
			green++;
		}
		if(green > 0 && red == 0)
		{
			green--;
			blue++;
		}
		if(blue > 0 && green == 0)
		{
			red++;
			blue--;
		}
		setColorRGB(red, green, blue);
		drawKare(0);
			
		printf("%i,   %i,   %i\n \r", (char) red, green, blue);

		usart_write_buffer_wait(&usart_USB, red, 3);
	
	}
}


/**************************SERCOM STUFF*******************************/
void configure_usart_USB(void)
{
	struct usart_config config_usart_USB;
	usart_get_config_defaults(&config_usart_USB);

		config_usart_USB.baudrate    = 9600;
		config_usart_USB.mux_setting = EDBG_CDC_SERCOM_MUX_SETTING;
		config_usart_USB.pinmux_pad0 = EDBG_CDC_SERCOM_PINMUX_PAD0;
		config_usart_USB.pinmux_pad1 = EDBG_CDC_SERCOM_PINMUX_PAD1;
		config_usart_USB.pinmux_pad2 = EDBG_CDC_SERCOM_PINMUX_PAD2;
		config_usart_USB.pinmux_pad3 = EDBG_CDC_SERCOM_PINMUX_PAD3;
		while (usart_init(&usart_USB,
		EDBG_CDC_MODULE, &config_usart_USB) != STATUS_OK) {
		}

	usart_enable(&usart_USB);
}



/**************************LCD STUFF**********************************/

void setPixel(uint16_t color)
{
	//Sets color to rrrrrggggggbbbbb
	LCD_Write_DATA16((color>>8),(color&0xFF)); 
}

void drawPixel(int x, int y)
{
	REG_PORT_OUTCLR1 = LCD_CS;
	setXY(x,y,x,y);
	setPixel((fore_Color_High<<8)|fore_Color_Low);
	REG_PORT_OUTSET1 = LCD_CS;
}



void fillRect(int x1, int y1, int x2, int y2)
{
	if (x1>x2)
		SwapUint16(x1, x2);
	if (y1>y2)
		SwapUint16(y1, y2);
	
	REG_PORT_OUTCLR1 = LCD_CS;
	setXY(x1, y1, x2, y2);
	REG_PORT_OUTSET1 = LCD_DC;
	LCD_Fast_Fill(fore_Color_High, fore_Color_Low, 
		(((long)(x2-x1)+1)*((long)(y2-y1)+1)));
	REG_PORT_OUTSET1 = LCD_CS;
}

void LCD_Fast_Fill(int ch, int cl, long pix)
{
	int blocks;

	REG_PORT_OUTCLR1 = 0x0000ffff;
	REG_PORT_OUTSET1 = (ch << 8) | cl;

	blocks = pix/16;
	for (int i=0; i<blocks; i++)
	{
		for (int j=0; j<16; j++)
		{
			REG_PORT_OUTCLR1 = LCD_WR;
			REG_PORT_OUTSET1 = LCD_WR;
		}
	}
	
	if ((pix % 16) != 0)
		for (int i=0; i<(pix % 16)+1; i++)
		{
			REG_PORT_OUTCLR1 = LCD_WR;
			REG_PORT_OUTSET1 = LCD_WR;
		}
}
	
void clrScr(void)
{
	REG_PORT_OUTCLR1 = LCD_CS;
	clrXY();
}

void clrXY(void)
{
	setXY(0,0,display_X_size,display_Y_size);
}

void setColorRGB(unsigned char r, unsigned char g, 
		unsigned char b)
{
	fore_Color_High = ((r&248)|g>>5);
	fore_Color_Low = ((g&28)<<3|b>>3);
}

void setColorHex(uint16_t color)
{
	fore_Color_High = (color >> 8);
	fore_Color_Low = (color & 0xFF);
}

void setBackColorRGB(unsigned char r, 
		unsigned char g, unsigned char b)
{
	back_Color_High = ((r&248)|g>>5);
	back_Color_Low = ((g&28)<<3|b>>3);
}

void setBackColorHex(uint16_t color)
{
	back_Color_High = (color >> 8);
	back_Color_Low = (color & 0xFF);
}


void setXY(uint16_t x1, uint16_t y1, 
		uint16_t x2, uint16_t y2)
{
		
	SwapUint16(x1, y1);
	SwapUint16(x2, y2);
	y1=display_Y_size-y1;
	y2=display_Y_size-y2;
	SwapUint16(y1, y2);
	
	LCD_Write_COM16(0x2a,0x00);
	LCD_Write_DATA8(x1>>8);
	LCD_Write_COM16(0x2a,0x01);
	LCD_Write_DATA8(x1);
	LCD_Write_COM16(0x2a,0x02);
	LCD_Write_DATA8(x2>>8);
	LCD_Write_COM16(0x2a,0x03);
	LCD_Write_DATA8(x2);

	LCD_Write_COM16(0x2b,0x00);
	LCD_Write_DATA8(y1>>8);
	LCD_Write_COM16(0x2b,0x01);
	LCD_Write_DATA8(y1);
	LCD_Write_COM16(0x2b,0x02);
	LCD_Write_DATA8(y2>>8);
	LCD_Write_COM16(0x2b,0x03);
	LCD_Write_DATA8(y2);

	LCD_Write_COM16(0x2c,0x00);
}


void LCD_Write_Bus(char VH, char VL)
{
	REG_PORT_OUTCLR1 = 0x0000ffff;
	REG_PORT_OUTSET1 = (VH << 8) | VL;
	REG_PORT_OUTCLR1 = LCD_WR;
	REG_PORT_OUTSET1 = LCD_WR;

}

void LCD_Write_COM16(char VH, char VL)
{
	REG_PORT_OUTCLR1 = LCD_DC;
	LCD_Write_Bus(VH,VL);
}

void LCD_Write_COM8(char VL)
{
	REG_PORT_OUTCLR1 = LCD_DC;
	LCD_Write_Bus(0x00, VL);
}

void LCD_Write_DATA16(char VH, char VL)
{
	REG_PORT_OUTSET1 = LCD_DC;
	LCD_Write_Bus(VH,VL);
}

void LCD_Write_DATA8(char VL)
{
	REG_PORT_OUTSET1 = LCD_DC;
	LCD_Write_Bus(0x00, VL);
}


/***********drawKare ** It's the boot graphic*************************/
//	drawKare(int emotion) is the boot animation displayed on startup
//	this displays an 'emotion':
//	emotion = 0:	a 'happy terminal'; normal mode
//	emotion = 1:	a lowercase pi, for using a Raspberry Pi as the 
//					endpoint of the serial (non USB) serial port.
//	emotion = 2:	the 'sad terminal'; idk, macs had a 'sad mac'.
//
//	yes, this is full of magic numbers but this will be the only
//	graphic in the entire project. Please note this is the most
//	space efficient way to do this; a 40x31 bitmap is 930 bytes, 
//	whereas	this is (104*2)+28+20, or 256 bytes.
/*********************************************************************/
void drawKare(int emotion)
{
	uint16_t body[104] = {10,10,20,20,20,0,380,10,380,10,390,20,0,
		20,10,290,390,20,400,290,10,290,20,300,380,290,390,300,20,
		300,380,310,0,30,50,40,0,50,50,60,80,30,280,40,70,40,80,190,
		80,190,280,200,280,40,290,190,0,70,50,80,0,90,50,100,0,110,
		50,120,0,130,50,140,0,150,50,160,0,170,50,180,0,190,50,200,
		300,200,370,210,30,220,370,230,30,240,370,250,30,260,370,
		270,90,280,300,290};
		
	//Yeah, these are uint8 arrays.		
	uint8_t happyTerm[28] = {180,80,190,130,170,130,190,140,140,
		60,150,100,210,60,220,100,130,150,140,160,140,160,220,170,
		220,150,230,160};
		
	uint8_t rPiBeret[20] = {120,60,240,80,110,70,120,90,150,
		60,170,170,200,60,220,160,210,160,230,170};

	int offsetGraphicX = 300;	
	int offsetGraphicY = 150;	
	int iSv = 2;				//an inverse scale factor

	setBackColorRGB(0,0,0);
		
	for(int i = 0; i < 104; i = i+4)
	{
		fillRect(((body[i]/iSv)+(offsetGraphicX)),
		((body[i+1]/iSv)+(offsetGraphicY)),
		((body[i+2]/iSv)+(offsetGraphicX)),
		((body[i+3]/iSv)+(offsetGraphicY)));
	}
	switch(emotion)
	{
			case 0:
				for(int i = 0; i < 28; i = i+4)
				{
					fillRect(((happyTerm[i]/iSv)+(offsetGraphicX)),
					((happyTerm[i+1]/iSv)+(offsetGraphicY)),
					((happyTerm[i+2]/iSv)+(offsetGraphicX)),
					((happyTerm[i+3]/iSv)+(offsetGraphicY)));
				}
				break;
			case 1:
				for(int i = 0; i < 20; i = i+4)
				{
					fillRect((
					(rPiBeret[i]/iSv)+(offsetGraphicX)),
					((rPiBeret[i+1]/iSv)+(offsetGraphicY)),
					((rPiBeret[i+2]/iSv)+(offsetGraphicX)),
					((rPiBeret[i+3]/iSv)+(offsetGraphicY)));
				}
				break;
			case 2:
				//make a sad terminal thing go here
				break;
	}
}

/**************************InitLCD()**********************************/
void InitLCD(void)
{
	/*
	InitLCD() sets the pinMode of all the LCD control pins (write,
	read, D/C, Chip Select, Reset) as output. Then follows data 
	sheet initialization:
	
	0)	for some fucking reason, pull PB16 high
		0a)	This is actually necessary for reasons
		I can not conceive of. Just leave it in there
		and by the way don't use PB16 for anything.
	1)	pull Reset high, delay 5ms
	2)	pull Reset low, delay 15ms
	3)	pull Reset high, delay 15ms
	4)	pull Chip Select low
	5)	Write initialization procedure for LCD
		5a) this includes 120ms delay after startup
			and 100ms delay after turning the display on
			(command 0x29..)
			resulting in total time to initialize display as 255ms
			(120+100+15+15+5). This does not include writing all
			black to the display.
		5b) I have changed this to a 5ms startup; seems to work.
	6) pull Chip Select high.
	7) finally, set the color of background and foreground,
		then blank the screen (fillRect(0,0,799,489))
	
	If you are reading this, I must impress something upon you: I
	don't have any idea how or why this works. The data sheet for
	the NT35510 LCD Driver IC is incomplete. This code comes from
	a vendor example using an 8051 micro.
		
	I know the data sheet is incomplete because the commands below
	are not listed. I have no idea what this section of code is or
	does; nor does anyone outside of the people who designed this
	chip.
	
	That said, this section of code does correctly initialize the
	LCD. If you have any desire to change or edit this code, may
	whatever god you believe in have mercy on your soul.
		
	The following code was refactored to be utterly incomprehensible
	and full of magic numbers on purpose. I suggest you do not screw
	with this, as there is no documentation at all.
	*/
		
static char belial[70] = {0xF0,0xF0,0xF0,0xF0,0xF0,0xB0,0xB0,
		0xB0,0xB6,0xB6,0xB6,0xB1,0xB1,0xB1,0xB7,0xB7,0xB7,0xB2,0xB2,
		0xB2,0xB8,0xB8,0xB8,0xBF,0xB3,0xB3,0xB3,0xB9,0xB9,0xB9,0xB5,
		0xB5,0xB5,0xC2,0xBA,0xBA,0xBA,0xBC,0xBC,0xBC,0xBD,0xBD,0xBD,
		0xBE,0xBE,0xF0,0xF0,0xF0,0xF0,0xF0,0xB1,0xB1,0xB6,0xB7,0xB7,
		0xB8,0xB8,0xB8,0xB8,0xBC,0xBC,0xBC,0xC9,0xC9,0xC9,0xC9,0xC9,
		0x35,0x3A,0x36};
		
static char mulciber[70] = {0x00,0x01,0x02,0x03,0x04,0x00,0x01,
		0x02,0x00,0x01,0x02,0x00,0x01,0x02,0x00,0x01,0x02,0x00,0x01,
		0x02,0x00,0x01,0x02,0x00,0x01,0x02,0x00,0x01,0x02,0x00,0x00,
		0x01,0x00,0x00,0x01,0x02,0x00,0x01,0x02,0x00,0x01,0x02,0x00,
		0x01,0x00,0x01,0x02,0x03,0x04,0x00,0x00,0x00,0x00,0x01,0x00,
		0x01,0x02,0x03,0x00,0x01,0x02,0x00,0x01,0x02,0x03,0x04,0x00,
		0x00,0x00};
				
static char lucifer[70] = {0x55,0xAA,0x52,0x08,0x01,0x0D,0x0D,0x0D,
		0x34,0x34,0x34,0x0D,0x0D,0x0D,0x34,0x34,0x34,0x00,0x00,0x00,
		0x24,0x24,0x24,0x01,0x0F,0x0F,0x0F,0x34,0x34,0x34,0x08,0x08,
		0x08,0x03,0x24,0x24,0x24,0x00,0x78,0x00,0x00,0x78,0x00,0x00,
		0x89,0x55,0xAA,0x52,0x08,0x00,0xCC,0x00,0x05,0x70,0x70,0x01,
		0x03,0x03,0x03,0x02,0x00,0x00,0xD0,0x02,0x50,0x50,0x50,0x00,
		0x55,0x00};
		
static unsigned char beelzebub[48] = {0x00,0x2D,0x00,0x2E,0x00,0x32,
		0x00,0x44,0x00,0x53,0x00,0x88,0x00,0xB6,0x00,0xF3,0x01,0x22,
		0x01,0x64,0x01,0x92,0x01,0xD4,0x02,0x07,0x02,0x08,0x02,0x34,
		0x02,0x5F,0x02,0x78,0x02,0x94,0x02,0xA6,0x02,0xBB,0x02,0xDB,
		0x02,0xF9,0x03,0x1F,0x03,0x7F};
		
	REG_PORT_DIRSET1 = 0x00010000;
	REG_PORT_OUTSET1 = PORT_PB16;
	
	REG_PORT_OUTSET1 = LCD_Reset;
	delay_ms(5);
	REG_PORT_OUTCLR1 = LCD_Reset;
	delay_ms(15);
	REG_PORT_OUTSET1 = LCD_Reset;
	REG_PORT_OUTCLR1 = LCD_CS;

	for(int i = 0; i < 70; i++)
	{
		LCD_Write_COM16(belial[i],mulciber[i]);
		LCD_Write_DATA8(lucifer[i]);
	}
	
	for(char k = 0xD1; k < 0xD6; k++)
		for(int l = 0; l < 48; l++)
		{
			LCD_Write_COM16(k,l);
			LCD_Write_DATA8(beelzebub[l]);
		}
		
  	LCD_Write_COM16(0x11,0x00);   //Start Up  
  	delay_ms(5);
  	LCD_Write_COM16(0x29,0x00);   //Display On  
   	delay_ms(5);
	REG_PORT_OUTSET1 = LCD_CS;
	
	setColorRGB(0,0,0);
	setBackColorRGB(0, 0, 0);
	fillRect(0,0,799,489);
}

