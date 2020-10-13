/*
 * keyboard.c
 *
 * Created: 6/29/2020 3:39:42 PM
 *  Author: bench
 */ 

#include <asf.h>
#include "globals.h"
#include "console.h"
#include "keyboard.h"
#include "LCD.h"
#include "LCDBus.h"
#include "fonts.h"

bool capsLock = false;
bool scrollLock = false;
bool cursorBlinkState = true;

char unsigned scanCodeBuffer[20] = {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};

char unsigned keyDownBuffer[20] = {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};
	
int scanCodes[70] = {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
		0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
		0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
		0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
		0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
		0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};
						
uint8_t cursorBuffer[200] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};


unsigned char consoleDisplay[80][24];

#define NUM_ROW 10
#define NUM_COL 7

static uint32_t kb_row[] = { KB_ROW0, KB_ROW1, KB_ROW2, KB_ROW3, KB_ROW4, KB_ROW5, KB_ROW6, KB_ROW7, KB_ROW8, KB_ROW9 };
static uint32_t kb_col[] = { KB_COL0, KB_COL1, KB_COL2, KB_COL3, KB_COL4, KB_COL5, KB_COL6 };
static int kb_row_index[] = {  2,  3,  4,  5,  6,  7, 10, 11, 12, 13 };
static int kb_col_index[] = { 16, 17, 18, 19, 20, 21, 27 };	

void drawBlank(void)
{
	if(cursorBlinkState == true)
		drawChar(0x20);
}

void printKeyboardBuffer(void)
{
	bool shifted = false;
	
	unsigned char noCase[] =	  
		{0xFF,0xFF,0xFF,0xFF,0xFF,	//Col0, Row0-4
		0x37,0x75,0x67,0x6A,0x2C,	//Col0, Row5-9
		0x31,0x71,0xFF,0xFF,0xFF,	//Col1, Row0-4
		0x38,0x69,0x68,0x6B,0xFF,	//Col1, Row5-9
		0x32,0x77,0xFF,0x7A,0xFF,	//Col2, Row0-4
		0x39,0x30,0x6F,0x6C,0x2E,	//Col2, Row5-9
		0x33,0x65,0x61,0x78,0xFF,	//Col3, Row0-4
		0xFF,0x2D,0x70,0x3B,0x2F,	//Col3, Row5-9
		0x34,0x72,0x73,0x63,0x20,	//Col4, Row0-4
		0xFF,0x3D,0x5B,0x27,0xFF,	//Col4, Row5-9
		0x35,0x74,0x64,0x76,0x6E,	//Col5, Row0-4
		0xFF,0x27,0x5D,0xFF,0x5C,	//Col5, Row5-9
		0x36,0x79,0x66,0x62,0x6D,	//Col6, Row0-4
		0xFF,0xFF,0xFF,0xFF,0xFF};	//Col6, Row5-9
	
	unsigned char shiftCase[] = 
		{0xFF,0xFF,0xFF,0xFF,0xFF,	//Col0, Row0-4
		0x26,0x55,0x47,0x4A,0x3C,	//Col0, Row5-9
		0x21,0x51,0xFF,0xFF,0xFF,	//Col1, Row0-4
		0x2A,0x49,0x48,0x4B,0xFF,	//Col1, Row5-9
		0x40,0x57,0xFF,0x5A,0xFF,	//Col2, Row0-4
		0x28,0x29,0x4F,0x4C,0x3E,	//Col2, Row5-9
		0x23,0x45,0x41,0x58,0xFF,	//Col3, Row0-4
		0xFF,0x5F,0x50,0x3A,0x3F,	//Col3, Row5-9
		0x24,0x52,0x53,0x43,0x20,	//Col4, Row0-4
		0xFF,0x2B,0x7B,0x22,0xFF,	//Col4, Row5-9
		0x25,0x54,0x44,0x56,0x4E,	//Col5, Row0-4
		0xFF,0x7E,0x7D,0xFF,0x7C,	//Col5, Row5-9
		0x5E,0x59,0x46,0x42,0x4D,	//Col6, Row0-4
		0xFF,0xFF,0xFF,0xFF,0xFF};	//Col6, Row0-4


	//Check if Shift key is present
	for(int i=0; i<20; i++)
	{
		if((scanCodeBuffer[i] == 13) | (scanCodeBuffer[i] == 49))
			shifted = true;
	}
	
	for(int i=0; i<20; i++)
	{

		//if a key is not in the keydown buffer, continue
		if(!keyDown(scanCodeBuffer[i]))
		{
			
			//add the scancode to the keycode buffer
			keyDownBuffer[i] = scanCodeBuffer[i];
			
			//The actual scancode handling goes here
			if(scanCodeBuffer[i] == 0xFF)
			{
				//do nothing, blank key
			}
			
			//Arrow key handling
			else if(scanCodeBuffer[i] == 35) //left
			{
				if(xCharPos > 0) 
				{
					
					cursorBlinkState = true;
					//blinkCursor();
					xCharPos--;
				}
			}
			else if(scanCodeBuffer[i] == 45)	//down
			{
				if(yCharPos < 24)
				{
					cursorBlinkState = true;
					//blinkCursor();
					yCharPos++;
				}
			}
			else if(scanCodeBuffer[i] == 55)	//up
			{
				if(yCharPos > 0)
				{
					cursorBlinkState = true;
					//blinkCursor();
					yCharPos--;
				}
			}
			else if(scanCodeBuffer[i] == 65)	//right
			{
				if(xCharPos < 79)
				{
					cursorBlinkState = true;
					//blinkCursor();
					xCharPos++;
				}
			}
			
			else if((scanCodeBuffer[i] == 49) | (scanCodeBuffer[i] == 13))
			{
				//SHIFT - do nothing
			}
			else if(scanCodeBuffer[i] == 58) //Return
			{
				if(yCharPos == 23)
				{
					
					newLine();
					xCharPos = 0;
				}
				else
				{
					
					yCharPos++;
					xCharPos = 0;
				}
			}
			else if(scanCodeBuffer[i] == 69) //Line
			{
				
				if(yCharPos == 23)
				{
					newLine();
				}
				else
				{
					yCharPos++;
				}
			}
			else if(scanCodeBuffer[i] == 66) //Backspace
			{
				drawChar(0x20);
				xCharPos--;
				drawChar(consoleDisplay[xCharPos][yCharPos]);
				readCursor(xCharPos,yCharPos);
				
			}
			else
			{
				if(shifted)
				{
					consoleDisplay[xCharPos][yCharPos] = shiftCase[scanCodeBuffer[i]];
					drawChar(shiftCase[scanCodeBuffer[i]]);
					xCharPos++;
					drawChar(consoleDisplay[xCharPos][yCharPos]);
					
					
					if(xCharPos > 79)
					{
						//readCursor(xCharPos++,yCharPos);
						xCharPos--;
						//drawCursorBuffer();
						//clearCursorBuffer();	
					}
					//cursorBlinkState = true;
					blinkCursor();
				}
				else
				{
					consoleDisplay[xCharPos][yCharPos] = noCase[scanCodeBuffer[i]];
					drawChar(noCase[scanCodeBuffer[i]]);
					xCharPos++;
					drawChar(consoleDisplay[xCharPos][yCharPos]);
					
					
					
					if(xCharPos > 79)
					{

						//readCursor(xCharPos++,yCharPos);
						xCharPos--;
						//drawCursorBuffer();
						//clearCursorBuffer();	
					}
					//cursorBlinkState = true;
					blinkCursor();

				}
			}
		}
	}
	
	//Reset the buffer.
	for(int i = 0 ; i < 20 ; i++)
	{
		scanCodeBuffer[i] = 0xFF;
	}
	
}

void readKeyboard(void)
{
	/*
	The getScanCode writes ints to scanCodeBuffer. These are the scancode,
	with the key column being the decade, and the key row being the ones digit.
	For example, the 'A' key is scan code 32, because it's on column 3, row 2.
	
	Keyboard read is done by first setting the columns as output, low. Then,
	each column is set high, and each key row is read. If it's high, that goes
	into the buffer. Next, rows and columns are swapped; all rows
	are set as output, and the columns are read one at a time. If it's high,
	that keycode goes into the buffer.
	
	No, you can't just do the columns without doing the rows; there is
	keyboard ghosting if you do.
	
	For each keypress, scanCodeIndex is incremented. this is used as a counter
	to keep track of how many keys are pressed.
	*/
	
	int scanCodeIndex = 0;
	int i, j;
	

	//Reset ScanCodes[]
	for(i = 0 ; i < 70 ; i++)
	{
		scanCodes[i] = 0xFF;
	}
	
	
	//Set strong drive on column
	PORT->Group[0].WRCONFIG.bit.DRVSTR = 1;
	
	//Set all columns as output, low
	for (i = 0; i < NUM_COL; i++) {
		REG_PORT_DIRSET0 = kb_col[i];
		REG_PORT_OUTCLR0 = kb_col[i];
	}
	
	//set rows to input, pullup enabled
	for (i = 0; i < NUM_ROW; i++) {
		REG_PORT_DIRCLR0 = kb_row[i];
		PORT->Group[0].PINCFG[kb_row_index[i]].bit.PULLEN = 1;
		PORT->Group[0].PINCFG[kb_row_index[i]].bit.INEN = 1;
	}
			
	//Step through columns, if high, save that column.
	for (i = 0; i < NUM_COL; i++) {
		REG_PORT_OUTSET0 = kb_col[i];
		for (j = 0; j < NUM_ROW; j++) {	
			if((PORT->Group[0].IN.reg & kb_row[j]) != 0) {
				scanCodes[scanCodeIndex] = (i * NUM_ROW) + j;
				scanCodeIndex++;
			}
		}
		REG_PORT_OUTCLR0 = kb_col[i];
	}
	
	//Set all rows as output, low
	for (i = 0; i < NUM_ROW; i++) {
		REG_PORT_DIRSET0 = kb_row[i];
		REG_PORT_OUTCLR0 = kb_row[i];
	}
			
	//set columns to input, pullup enabled
	for (i = 0; i < NUM_COL; i++) {
		REG_PORT_DIRCLR0 = kb_col[i];
		PORT->Group[0].PINCFG[kb_col_index[i]].bit.PULLEN = 1;
		PORT->Group[0].PINCFG[kb_col_index[i]].bit.INEN = 1;
	}

	for (i = 0; i < NUM_ROW; i++) {
		REG_PORT_OUTSET0 = kb_row[i];
		for (j = 0; j < NUM_COL; j++) {
			if((PORT->Group[0].IN.reg & kb_col[j]) != 0)
			{
				scanCodes[scanCodeIndex] = (j * NUM_ROW) + i;
				scanCodeIndex++;
			}
		}
		REG_PORT_OUTCLR0 = kb_row[i];
	}
	
	//Send the scancodes to scancodebuffer, this is what 
	//printkeyboardbuffer actually reads
	for(i = 0 ; i < scanCodeIndex ; i++)
	{
		scanCodeBuffer[i] = scanCodes[i];	
	}
	
	//Remove a key if it is in the keyDownBuffer and
	//not in scanCodes[]. There are only 70 keys,
	//so we can go through all of those individually.
	for(i = 0; i < 70; i++)
	{
		if(keyDown(i) && !scanCodesContains(i))
		{
			removeFromKeyDown(i);
		}
	}
}

bool scanCodesContains(int scanCode)
{
	for(int i = 0 ; i < 70 ; i++)
	{
		if(scanCodes[i] == scanCode)
		{
			return true;
		}
	}
	return false;
}

bool bufferContains(int scanCode)
{
	for(int i = 0 ; i < 20 ; i++)
	{
		if(scanCodeBuffer[i] == scanCode)
		{
			return true;
		}
	}
	return false;
}

bool keyDown(int scancode)
{
	for(int i = 0 ; i < 20 ; i++)
	{
		if(keyDownBuffer[i] == scancode)
		{
			return true;
		}	
	}
	return false;
}

void removeFromKeyDown(int scancode)
{
	for(int i = 0 ; i < 20 ; i++)
	{
		if(keyDownBuffer[i] == scancode)
		{
			keyDownBuffer[i] = 0xFF;
		}
	}
}

void clearCursorBuffer(void)
{
	for(uint16_t i = 0 ; i < 200 ; i++)
	{
		cursorBuffer[i] = 0x00;
	}
}

void drawCursorBuffer(void)
{
	
	setXY(xCharPos*10,yCharPos*20,(xCharPos*10)+9,(yCharPos*20)+19);
	REG_PORT_OUTCLR1 = LCD_CS;
	for(uint16_t i = 0 ; i < 200 ; i++)
	{
		if((cursorBuffer[i] == 0xFF))
		{
			setPixel((fore_Color_High<<8)|fore_Color_Low);
		}
		else
		{
			setPixel((back_Color_High<<8)|back_Color_Low);
		}
	}
	REG_PORT_OUTSET1 = LCD_CS;
}

void invertCursorBuffer(void)
{
	for(uint16_t i = 0 ; i < 200 ; i++)
	{
		if((cursorBuffer[i] == 0xFF))
		{
			cursorBuffer[i] = 0x00;
		}
		else
		{
			cursorBuffer[i] = 0xFF;
		}
	}	
}

void readCursor(uint16_t cursorLocationX, uint16_t cursorLocationY)
{
	/*
	//First, this reads the GRAM memory at the cursor location
	//x,y. This is saved in a buffer. When the cursor blinks,
	//it alternates either that buffer, or the *inverse* of that
	//buffer.
	
	
	uint16_t x = cursorLocationX;
	uint16_t y = cursorLocationY;
	char character = consoleDisplay[x][y];
	uint8_t k = 0;
	
	uint8_t tempCursor[200] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

	

	for(uint16_t i=0; i <= 24; i++)
	{
		for(uint16_t j=0 ; j<8 ; j++)
		{
			if((CodePage437[character][i]&(1<<(7-j)))!=0)
			{
				tempCursor[k] = 0xFF;
			}
			else
			{
				tempCursor[k] = 0x00;
			}
			k++;
		}
	}
	
	for(uint8_t pixel = 0; pixel < 200 ; pixel++)
	{
		cursorBuffer[pixel] = tempCursor[pixel];
	}
	
	xCharPos = cursorLocationX;
	yCharPos = cursorLocationY;


	uint16_t x = cursorLocationX;
	uint16_t y = cursorLocationY;
	
	//set PB07 to input
	REG_PORT_DIRCLR1 = PORT_PB07;
	PORT->Group[1].PINCFG[7].bit.INEN = 1;
	PORT->Group[1].PINCFG[7].bit.PULLEN = 1;
	
	
	//Per page 40 of datasheet (5.1.2.7, 16-bit
	//parallel interface for data ram read.
	REG_PORT_OUTCLR1 = LCD_CS;
	setXY(cursorLocationX*10,cursorLocationY*20,cursorLocationX*10+9,cursorLocationY*20+19);
	//printf("Read\t%i, %i, %i, %i\n\r",x*10,y*20,x*10+9,y*20+19);
	
	
	//Send'Memory read' command 0x2E00, no data bit
	LCD_Write_COM16(0x2E,0x00);
	REG_PORT_OUTSET1 = LCD_DC;

	//needs dummy write, per data sheet, page 40
	REG_PORT_OUTCLR1 = LCD_RD;
	REG_PORT_OUTSET1 = LCD_RD;
	
	for(uint8_t pixel = 0; pixel <= 200 ; pixel++)
	{
		REG_PORT_OUTCLR1 = LCD_RD;
		REG_PORT_OUTSET1 = LCD_RD;

		//get the pin state, stuff into array
		
		//This can be expanded with else if for the MSBs
		//of all the colors; see datasheet page 40.
		if((PORT->Group[1].IN.reg & PORT_PB07) != 0)
		{
			cursorBuffer[pixel] = 0xFF;
		}
		else
		{
			cursorBuffer[pixel] = 0x00;
		}

		//dummy read, because pixel data broken up
		//per datasheet page 40. Everything after
		//the dummy write is BLUE pixels. Do we ever
		//need blue? IDK.
		
		REG_PORT_OUTCLR1 = LCD_RD;
		REG_PORT_OUTSET1 = LCD_RD;
	}
	
	REG_PORT_OUTSET1 = LCD_DC;
	REG_PORT_DIRSET1 = PORT_PB07;
	*/
}

uint16_t sumCursorBuffer(void)
{
	uint16_t sum = 0;
	
	for(uint16_t i = 0 ; i < 200 ; i++)
	{
		if((cursorBuffer[i] == 0xFF))
			sum++;			
	}
	return sum;
}

void blinkCursor(void)
{
	uint16_t x = xCharPos;
	uint16_t y = yCharPos;
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
					
					setPixel((back_Color_High<<8)|back_Color_Low);
				}
				else
				{
					setPixel((fore_Color_High<<8)|fore_Color_Low);
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
					setPixel((fore_Color_High<<8)|fore_Color_Low);
				}
				else
				{
					setPixel((back_Color_High<<8)|back_Color_Low);
					
				}
			}
		}	
	}

	REG_PORT_OUTSET1 = LCD_CS;
	
	//invert cursorBlinkState
	cursorBlinkState = !cursorBlinkState;
	
}
