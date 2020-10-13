/*
 * console.c
 *
 * Created: 6/29/2020 3:05:03 PM
 *  Author: bench
 */ 

#include <asf.h>
#include <string.h>

#include "LCDBus.h"
#include "LCD.h"
#include "console.h"
#include "fonts.h"
#include "globals.h"

uint16_t xCharPos = 0;
uint16_t yCharPos = 0;


void drawChar(uint8_t character)
{
	uint16_t x = xCharPos;
	uint16_t y = yCharPos;
	
	consoleDisplay[xCharPos][yCharPos] = character;
	
	REG_PORT_OUTCLR1 = LCD_CS;
	setXY(x*10,y*20,x*10+9,y*20+19);
	for(uint16_t i=0; i <= 24; i++)
	{
		for(int j=0;j<8;j++)
		{
			if((CodePage437[character][i]&(1<<(7-j)))!=0)
			{
				setPixel((fore_Color_High<<8)|fore_Color_Low);	
			}
			else
			{
				setPixel((back_Color_High<<8)|back_Color_Low);
			}

		}
	}
	REG_PORT_OUTSET1 = LCD_CS;

}

void newLine(void)
{
	/*The 'soft scroll' function moves all pixels on the display up
	20 pixels, or the height of one char. Algorithm is as follows:
	
	0) Set the GRAM window to a row one pixel high (setxy).
	example: (0,20,800,21). 
	
	1) Set PB07 as input. This is the data bit that will read
	the actual pixel data from GRAM.
	
	1a) We use PB07 because it represents the MSB of the green
		part of the pixel; this will always be 1 if the pixel
		is active, because the only colors we use are green,
		white, and amber.
		
	1b) Configuration of pin as input is on "SAMD21/SAMR21
		GPIO" Tutorial (Phillip Vallone), page 38.
		
	2) Read the pixel data into a 1D array (first as char[800],
	can be optimized with bit packing. This information is on 
	NT35510 datasheet, page 40.
	
	3) Set PB07 (and the rest of PB00..15) as output, set GRAM
	window and output contents of 1D array. Repeat this
	460 times, for each line in the display.
	*/
	
	uint8_t rowPixel[800];
		
	for(uint16_t row = 0 ; row < 460 ; row++)
	{
		//Per page 40 of datasheet (5.1.2.7, 16-bit
		//parallel interface for data ram read.
		REG_PORT_OUTCLR1 = LCD_CS;
		setXY(0, row+20, 799, row+20);
		//Send'Memory read' command 0x2E00, no data bit
		LCD_Write_COM16(0x2E,0x00);
		REG_PORT_OUTSET1 = LCD_DC;
		
		//needs dummy write, per data sheet, page 40
		REG_PORT_OUTCLR1 = LCD_RD;
		REG_PORT_OUTSET1 = LCD_RD;
		
		//set PB07 to input
		REG_PORT_DIRCLR1 = PORT_PB07;
		PORT->Group[1].PINCFG[7].bit.INEN = 1;
		PORT->Group[1].PINCFG[7].bit.PULLEN = 1;
		
		
		//Read pixel data into the display	
		for(uint16_t getpixel = 0 ; getpixel < 800 ; getpixel++)
		{
			REG_PORT_OUTCLR1 = LCD_RD;
			REG_PORT_OUTSET1 = LCD_RD;

			//get the pin state, stuff into array
			
			//This can be expanded with else if for the MSBs
			//of all the colors; see datasheet page 40.
			if((PORT->Group[1].IN.reg & PORT_PB07) != 0)
				rowPixel[getpixel] = 0xFF;
			else
				rowPixel[getpixel] = 0x00;
				
			//dummy read, because pixel data broken up
			//per datasheet page 40. Everything after
			//the dummy write is BLUE pixels. Do we ever
			//need blue? IDK.
			
			REG_PORT_OUTCLR1 = LCD_RD;
			REG_PORT_OUTSET1 = LCD_RD;
		}
		
		REG_PORT_OUTSET1 = LCD_DC;
		REG_PORT_DIRSET1 = 0x0000FFFF;
		
		//now, read out that line of the display
		setXY(0, row, 799, row);	
		
		for(uint16_t writepixel = 0 ; writepixel < 800 ; writepixel++)
		{
			if((rowPixel[writepixel] == 0xFF))
				setPixel((fore_Color_High<<8)|fore_Color_Low);
			else
				setPixel((back_Color_High<<8)|back_Color_Low);
		}
	}
	
	//finally, clear the last character line of the display
	//and fix the console text buffer
	fillRectBackColor(0, 460, 799, 480);

}

void writeString(char str[])
{
	int length = strlen(str);
	for(int i = 0; i < length; i++)
	{
		drawChar(str[i]);
		if(xCharPos <= 80)
		xCharPos++;
	}
}

void fillConsole(void)
{
	for(int i = 0 ; i < 80 ; i++)
	{
		for(int j = 0 ; j < 24 ; j++)
		{
			consoleDisplay[i][j] = 0x00;
		}
	}
}