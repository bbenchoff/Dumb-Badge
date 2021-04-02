/*
 * LCD.c
 *
 * Created: 6/29/2020 1:46:11 PM
 *  Author: bench
 */ 
#include <asf.h>
#include "globals.h"
#include "LCDBus.h"
#include "LCD.h"

uint16_t display_X_size = 479;
uint16_t display_Y_size = 799;

uint16_t fore_Color_High, fore_Color_Low;
uint16_t back_Color_High, back_Color_Low;

void setColorRGB(uint8_t r, uint8_t g, uint8_t b)
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

void fillRect(int x1, int y1, int x2, int y2)
{
	
	int temp = 0;
	
	if (x1>x2)
	{
		temp = x1;
		x1 = x2;
		x2 = temp;
	}
	if (y1>y2)
	{
		temp = x1;
		x1 = x2;
		x2 = temp;
	}
	
	REG_PORT_OUTCLR1 = LCD_CS;
	setXY(x1, y1, x2, y2);
	REG_PORT_OUTSET1 = LCD_DC;
	LCD_Fast_Fill(fore_Color_High, fore_Color_Low,
	(((long)(x2-x1)+1)*((long)(y2-y1)+1)));
	REG_PORT_OUTSET1 = LCD_CS;
}

void fillRectBackColor(int x1, int y1, int x2, int y2)
{
	int temp = 0;
	
	if (x1>x2)
	{
		temp = x1;
		x1 = x2;
		x2 = temp;
	}
	if (y1>y2)
	{
		temp = x1;
		x1 = x2;
		x2 = temp;
	}
	
	REG_PORT_OUTCLR1 = LCD_CS;
	setXY(x1, y1, x2, y2);
	REG_PORT_OUTSET1 = LCD_DC;
	LCD_Fast_Fill(back_Color_High, back_Color_Low,
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

void setXY(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
	
	//printf("setxy:\t%i\t%i\t%i\t%i\t\n\r",x1,y1,x2,y2);
	
	/*
	SwapUint16(x1, y1);
	SwapUint16(x2, y2);
	y1=display_Y_size-y1;
	y2=display_Y_size-y2;
	SwapUint16(y1, y2);
	*/
	
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

void setPixel(uint16_t color)
{
	//it sets it to a 16-bit color.
	//LCD_Write_DATA16((color<<8),(color&0xFF)); 
	LCD_Write_DATA16((color>>8),(color&0xFF));
}

void drawPixel(uint16_t x, uint16_t y)
{
	REG_PORT_OUTCLR1 = LCD_CS;
	setXY(x,y,x,y);
	setPixel((fore_Color_High<<8)|fore_Color_Low);
	REG_PORT_OUTSET1 = LCD_CS;
}

/*
void setDrawDirection(void)
{
	//Following sets the MADCTL register for correct interfacing
	//of the GRAM re:fonts. Information found on page 146 and
	//page 76 of NT35510 datasheet.
	//We will only be using characters from here on out, so
	//leave this as is, do not reinitialize.
	REG_PORT_OUTCLR1 = LCD_CS;
	REG_PORT_OUTCLR1 = LCD_DC;
	LCD_Write_COM16(0x36, 0x00);
	REG_PORT_OUTSET1 = LCD_DC;
	LCD_Write_DATA8(0x80);
	REG_PORT_OUTSET1 = LCD_CS;
}
*/
void clearScreen(void)
{
	setColorRGB(0,0,0);
	fillRect(0,0,display_Y_size,display_X_size);
}
