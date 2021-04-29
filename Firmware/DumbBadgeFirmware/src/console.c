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
#include "parser.h"
#include "settings.h"

uint16_t xCharPos = 0;
uint16_t yCharPos = 0;

unsigned char consoleDisplay[80][24];
uint32_t consoleColors[80][24];
uint8_t consoleSGR[80][24];



void drawChar(uint8_t character)
{
	uint16_t x = xCharPos;
	uint16_t y = yCharPos;
	
	uint16_t tempForeground;
	uint16_t tempBackground;
	
	uint32_t tempColor = consoleColors[x][y];
	
	tempForeground = (tempColor >> 16);
	tempBackground = consoleColors[x][y] & 0xFFFF;
	
	consoleDisplay[x][y] = character;
	
	uint8_t displayFont[10][20];
	uint8_t tempFontStorage[200];
	uint8_t k = 0;
	
	REG_PORT_OUTCLR1 = LCD_CS;
	setXY(x*10,y*20,x*10+9,y*20+19);
	
	//reformat the character into a 10x20 array:
	//first transmute it into tempFontStorage
	for(uint16_t i=0; i <= 24; i++)
	{
		for(int j=0;j<8;j++)
		{
			if((CodePage437[character][i]&(1<<(7-j)))!=0)
			{
				tempFontStorage[k] = 0xFF;
			}
			else
			{
				tempFontStorage[k] = 0x00;
			}
			k++;
		}
	}
	k = 0;
	//now reform into displayFont
	for(uint8_t i = 0; i <= 9 ; i++)
	{
		for(uint8_t j = 0; j <= 19 ; j++)
		{
			if(tempFontStorage[k] == 0xFF)
			{
				displayFont[i][j] = 0xFF;	
			}
			else
			{
				displayFont[i][j] = 0x00;
			}
			k++;
		}
	}
	
	//process displayFont if it is bold, first bit of consoleSGR
	if(BitVal(consoleSGR[xCharPos][yCharPos],1) == 1)
	{
		for(uint8_t i = 10; i >= 1 ; i--)
		{
			for(uint8_t j = 0; j <= 19 ; j++)
			{
				if(displayFont[i-1][j] == 0xFF)
				{
					displayFont[i][j] = 0xFF;
				}
			}
		}
	}
	
	//process displayfont if underscore, fourth bit of consoleSGR
	if(BitVal(consoleSGR[xCharPos][yCharPos],4) == 1)
	{
		for(int i = 0 ; i <= 9 ; i++)
		{
			displayFont[9][i] = 0xFF;
		}
	}
	
	//Process inverse video, compare 7th bit of consoleSGR
	if(BitVal(consoleSGR[xCharPos][yCharPos],7) == 0)
	{
		for(uint8_t i = 0; i <= 9 ; i++)
		{
			for(uint8_t j = 0; j <= 19 ; j++)
			{
				if(displayFont[i][j] == 0xFF)
				{
					setPixel(tempForeground);
				}
				else
				{
					setPixel(tempBackground);
				}
			}
		}
	}
	else
	{
		for(uint8_t i = 0; i <= 9 ; i++)
		{
			for(uint8_t j = 0; j <= 19 ; j++)
			{
				if(displayFont[i][j] != 0xFF)
				{
					setPixel(tempForeground);
				}
				else
				{
					setPixel(tempBackground);
				}
			}
		}		
	}
	
	REG_PORT_OUTSET1 = LCD_CS;
}

void newLine(void)
{
	/*
	The original intention of this function was to move all the characters
	on the display up one line; originally, this was done with a 'software
	scroll' function, where the microcontroller reads GRAM data from the 
	display. THIS IS A NOVEL APPROACH FOR THE NT35510 DISPLAY DRIVER.
	
	Unfortunately, just because something is cool doesn't mean it's
	efficient. This function has been refactored to scroll to a new line
	the sane way -- by moving characters in consoleDisplay around, then
	redrawing the display. Empirical testing has shown this is the faster
	way to do it.
	
	Additionally, this method is more extensible in that character colors
	may be preserved with an additional array indexing foreground and
	background colors. This method is simply the better way to do it. But
	it's not the coolest.
	
	I have retained the 'GRAM scroll' function in a comment below; this
	may be of use if you ever want to make a giant Conway's Game of Life
	or some chomping bits or something.
	*/
	
	int tempCursorx = xCharPos;
	int tempCursory = yCharPos;
	
	cursorBlinkState = true;
	blinkCursor();
	
	//First, move the characters in consoleDisplay up one line
	//we do not care about the zeroth line. Do the same with
	//the consoleGraphics array
	for(int j = 1 ; j <= 24 ; j++)
	{
		for(int i = 0 ; i < 80 ; i++)
		{
			consoleDisplay[i][j-1] = consoleDisplay[i][j];
			consoleColors[i][j-1] = consoleColors[i][j];
			consoleSGR[i][j-1] = consoleSGR[i][j];
		}
	}
	
	//Initalize the new row as 0x20, 'space'
	for(int k = 0 ; k < 80 ; k ++)
	{
		consoleDisplay[k][23] = 0x20;
		consoleColors[k][23] = 0x0000;
		consoleSGR[k][23] = 0x00;
	}
	
	//Redraw the display
	for(int j = 0 ; j < 24 ; j++)
	{
		for(int i = 0 ; i < 80 ; i++)
		{
			xCharPos = i;
			yCharPos = j;
			drawChar(consoleDisplay[i][j]);
		}
	}
		
	xCharPos = tempCursorx;
	yCharPos = tempCursory;
	
/*The 'soft scroll' function moves all pixels on the display up
20 pixels, or the height of one char. Algorithm is as follows:
	
1) Set the GRAM window to a row one pixel high (setxy).
example: (0,20,800,21). 
	
2) Set PB07 as input. This is the data bit that will read
the actual pixel data from GRAM.
	
3) We use PB07 because it represents the MSB of the green
	part of the pixel; this will always be 1 if the pixel
	is active, because the only colors we use are green,
	white, and amber.
		
4) Configuration of pin as input
		
5) Read the pixel data into a 1D array (first as char[800],
can be optimized with bit packing. This information is on 
NT35510 datasheet, page 40.
	
6) Set PB07 (and the rest of PB00..15) as output, set GRAM
window and output contents of 1D array. Repeat this
460 times, for each line in the display.
*/
/*
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
	
//clear the last character line of the display
//and fix the console text buffer
fillRectBackColor(0, 460, 799, 480);
*/
	
}

void blinkCursor(void)
{
	uint16_t x = xCharPos;
	uint16_t y = yCharPos;
	
	uint16_t tempForeground;
	uint16_t tempBackground;
		
	uint32_t tempColor = consoleColors[x][y];
		
	tempForeground = tempColor >> 16;
	tempBackground = consoleColors[x][y] & 0xFFFF;
	
	unsigned char character = consoleDisplay[x][y];
	setXY(x*10,y*20,x*10+9,y*20+19);
	REG_PORT_OUTCLR1 = LCD_CS;
	if(cursorBlinkState)
	{
		for(uint16_t i=0; i <= 24; i++)
		{
			for(int j=0;j<8;j++)
			{
				if((CodePage437[character][i]&(1<<(7-j)))!=0)
				{
					
					setPixel(tempBackground);
				}
				else
				{
					setPixel(tempForeground);
				}
			}
		}
	}
	else
	{
		for(uint16_t i=0; i <= 24; i++)
		{
			for(int j=0;j<8;j++)
			{
				if((CodePage437[character][i]&(1<<(7-j)))!=0)
				{
					setPixel(tempForeground);
				}
				else
				{
					setPixel(tempBackground);
					
				}
			}
		}
	}

	REG_PORT_OUTSET1 = LCD_CS;
	
	//invert cursorBlinkState
	cursorBlinkState = !cursorBlinkState;
	
}

void writeString(const char str[])
{
	int length = strlen(str);
	for(int i = 0; i < length; i++)
	{
		drawChar(str[i]);
		if(xCharPos <= 80)
		xCharPos++;
	}
}

void nullifyConsole(void)
{
	for(int i = 0 ; i < 80 ; i++)
	{
		for(int j = 0 ; j < 24 ; j++)
		{
			consoleDisplay[i][j] = 0x00;
			consoleSGR[i][j] = 0x00;
			consoleColors[i][j] = 0xFFFF0000;
		}
	}	
}

void arrowKey(int scancode)
{
	unsigned char tempCharacter;
	//Arrow key handling
	if(scancode == 35) //left
	{
		if(xCharPos > 0)
		{
			drawChar(consoleDisplay[xCharPos][yCharPos]);
			xCharPos--;
			tempCharacter = consoleDisplay[xCharPos][yCharPos];
			drawChar(tempCharacter);
			blinkCursor();
		}
	}
	else if(scancode  == 45)	//down
	{
		if(yCharPos < 23)
		{
			drawChar(consoleDisplay[xCharPos][yCharPos]);
			yCharPos++;
			tempCharacter = consoleDisplay[xCharPos][yCharPos];
			drawChar(tempCharacter);
			blinkCursor();
		}
	}
	else if(scancode  == 55)	//up
	{
		if(yCharPos > 0)
		{
			drawChar(consoleDisplay[xCharPos][yCharPos]);
			yCharPos--;
			tempCharacter = consoleDisplay[xCharPos][yCharPos];
			drawChar(tempCharacter);
			blinkCursor();
		}
	}
	else if(scancode  == 65)	//right
	{
		if(xCharPos < 79)
		{
			drawChar(consoleDisplay[xCharPos][yCharPos]);
			xCharPos++;
			tempCharacter = consoleDisplay[xCharPos][yCharPos];
			drawChar(tempCharacter);
			blinkCursor();
		}
	}
}