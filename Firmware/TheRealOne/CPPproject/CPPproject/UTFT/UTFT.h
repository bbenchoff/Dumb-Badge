/*
  UTFT.h - Arduino/chipKit library support for Color TFT LCD Boards
  Copyright (C)2010-2014 Henning Karlsen. All right reserved
  
  This library is the continuation of my ITDB02_Graph, ITDB02_Graph16
  and RGB_GLCD libraries for Arduino and chipKit. As the number of 
  supported display modules and controllers started to increase I felt 
  it was time to make a single, universal library as it will be much 
  easier to maintain in the future.

  Basic functionality of this library was origianlly based on the 
  demo-code provided by ITead studio (for the ITDB02 modules) and 
  NKC Electronics (for the RGB GLCD module/shield).

  This library supports a number of 8bit, 16bit and serial graphic 
  displays, and will work with both Arduino and chipKit boards. For a 
  full list of tested display modules and controllers, see the 
  document UTFT_Supported_display_modules_&_controllers.pdf.

  When using 8bit and 16bit display modules there are some 
  requirements you must adhere to. These requirements can be found 
  in the document UTFT_Requirements.pdf.
  There are no special requirements when using serial displays.

  You can always find the latest version of the library at 
  http://electronics.henningkarlsen.com/
  http://www.buydisplay.com
  If you make any modifications or improvements to the code, I would 
  appreciate that you share the code with me so that I might include 
  it in the next release. I can be contacted through 
  http://electronics.henningkarlsen.com/contact.php.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the CC BY-NC-SA 3.0 license.
  Please see the included documents for further information.

  Commercial use of this library requires you to buy a license that
  will allow commercial use. This includes using the library,
  modified or not, as a tool to sell products.

  The license applies to all part of the library including the 
  examples and tools supplied with the library.

  //----------------------------------------------------------------------
//EASTRISING TECHNOLOGY CO,.LTD.//
// Ver   	: 2.0            Date:Jan-26-2015 
// Create    	: JAVEN LIU
*/

#ifndef UTFT_h
#define UTFT_h

#define UTFT_VERSION	279

#define LEFT 0
#define RIGHT 9999
#define CENTER 9998

#define PORTRAIT 0
#define LANDSCAPE 1

#define HX8347A			0
#define ILI9327			1
#define SSD1289			2
#define ILI9325C		3
#define ILI9325D_8		4
#define ILI9325D_16		5
#define HX8340B_8		6
#define HX8340B_S		7
#define HX8352A			8
#define ST7735			9
#define PCF8833			10
#define S1D19122		11
#define SSD1963_480		12
#define SSD1963_800		13
#define S6D1121_8		14
#define S6D1121_16		15
#define	SSD1289LATCHED	16
//#define NOT_IN_USE	17
//#define NOT_IN_USE	18
#define SSD1289_8		19
#define	SSD1963_800ALT	20
#define ILI9481			21
#define ILI9325D_16ALT	22
#define S6D0164			23
#define ST7735S			24
#define ILI9341_S5P		25
#define ILI9341_S4P		26
#define R61581			27
#define ILI9486			28
#define CPLD			29
#define HX8353C			30
#define ST7735_ALT		31
#define ILI9341_8		32
#define ILI9341_16		33
#define ILI9488_16		34
#define ILI9342_16		35
#define ILI9342_S5P		36
#define ILI9342_S4P		37
#define ILI9163_S5P		38
#define ST7735S_S5P_80160		39
#define NT35510_16		40


#define TFTM040_1_16		40  // NT35510	(16bit)

#define SERIAL_4PIN		4
#define SERIAL_5PIN		5
#define LATCHED_16		17

#define NOTINUSE		255

//*********************************
// COLORS
//*********************************
// VGA color palette
#define VGA_BLACK		0x0000
#define VGA_WHITE		0xFFFF
#define VGA_RED			0xF800
#define VGA_GREEN		0x0400
#define VGA_BLUE		0x001F
#define VGA_SILVER		0xC618
#define VGA_GRAY		0x8410
#define VGA_MAROON		0x8000
#define VGA_YELLOW		0xFFE0
#define VGA_OLIVE		0x8400
#define VGA_LIME		0x07E0
#define VGA_AQUA		0x07FF
#define VGA_TEAL		0x0410
#define VGA_NAVY		0x0010
#define VGA_FUCHSIA		0xF81F
#define VGA_PURPLE		0x8010
#define VGA_TRANSPARENT	0xFFFFFFFF

#if defined(__AVR__)
	#include "Arduino.h"
	#include "hardware/avr/HW_AVR_defines.h"
#elif defined(__PIC32MX__)
	#include "WProgram.h"
	#include "hardware/pic32/HW_PIC32_defines.h"
#elif defined(__arm__)
	//#include "Arduino.h"
	#include "hardware/arm/HW_ARM_defines.h"
#endif

struct _current_font
{
	uint8_t* font;
	uint8_t x_size;
	uint8_t y_size;
	uint8_t offset;
	uint8_t numchars;
};

class UTFT
{
	public:
		UTFT();
		UTFT(int model, int RS, int WR, int CS, int RST, int SER=0);
		void	InitLCD(int orientation=LANDSCAPE);
		void	clrScr();
		void	drawPixel(int x, int y);
		void	drawLine(int x1, int y1, int x2, int y2);
		void	fillScr(int r, int g, int b);
		void	fillScr(uint8_t color);
		void	drawRect(int x1, int y1, int x2, int y2);
		void	drawRoundRect(int x1, int y1, int x2, int y2);
		void	fillRect(int x1, int y1, int x2, int y2);
		void	fillRoundRect(int x1, int y1, int x2, int y2);
		void	drawCircle(int x, int y, int radius);
		void	fillCircle(int x, int y, int radius);
		void	setColor(int r, int g, int b);
		void	setColor(uint8_t color);
		word	getColor();
		void	setBackColor(int r, int g, int b);
		void	setBackColor(uint32_t color);
		word	getBackColor();
		void	print(char *st, int x, int y, int deg=0);
		void	print(String st, int x, int y, int deg=0);
		void	printNumI(long num, int x, int y, int length=0, char filler=' ');
		void	printNumF(double num, int dec, int x, int y, char divider='.', int length=0, char filler=' ');
		void	setFont(uint8_t* font);
		uint8_t* getFont();
		uint8_t	getFontXsize();
		uint8_t	getFontYsize();
		void	drawBitmap(int x, int y, int sx, int sy, bitmapdatatype data, int scale=1);
		void	drawBitmap(int x, int y, int sx, int sy, bitmapdatatype data, int deg, int rox, int roy);
		void	lcdOff();
		void	lcdOn();
		void	setContrast(char c);
		int		getDisplayXSize();
		int		getDisplayYSize();
		void	setBrightness(int br);
		void	setDisplayPage(int page);
		void	setWritePage(int page);

/*
	The functions and variables below should not normally be used.
	They have been left publicly available for use in add-on libraries
	that might need access to the lower level functions of UTFT.

	Please note that these functions and variables are not documented
	and I do not provide support on how to use them.
*/
		uint8_t			fch, fcl, bch, bcl;
		uint8_t			orient;
		long			disp_x_size, disp_y_size;
		uint8_t			display_model, display_transfer_mode, display_serial_mode;
		regtype			*P_RS, *P_WR, *P_CS, *P_RST, *P_SDA, *P_SCL, *P_ALE;
		regsize			B_RS, B_WR, B_CS, B_RST, B_SDA, B_SCL, B_ALE;
		uint8_t			__p1, __p2, __p3, __p4, __p5;
		_current_font	cfont;
		boolean			_transparent;

		void LCD_Writ_Bus(char VH,char VL, byte mode);
		void LCD_Write_COM(char VL);
		void LCD_Write_COM(char VH,char VL);
		void LCD_Write_DATA(char VH,char VL);
		void LCD_Write_DATA(char VL);
		void LCD_Write_COM_DATA(char com1,int dat1);
		void _hw_special_init();
		void setPixel(uint16_t color);
		void drawHLine(int x, int y, int l);
		void drawVLine(int x, int y, int l);
		void printChar(int c, int x, int y);
		void setXY(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
		void clrXY();
		void rotateChar(int c, int x, int y, int pos, int deg);
		void _set_direction_registers(int mode);
		void _fast_fill_16(int ch, int cl, long pix);
		void _fast_fill_8(int ch, long pix);
		void _convert_float(char *buf, double num, int width, int prec);
};

#endif