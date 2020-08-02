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

bool capsLock = false;
bool scrollLock = false;
bool cursorBlinkState = true;

char scanCodeBuffer[20] = {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
						0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};

char keyDownBuffer[20] = {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
						0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};
						
uint8_t cursorBuffer[200];

int kb_col[] = {KB_COL0, KB_COL1, KB_COL2, KB_COL3, KB_COL4, KB_COL5, KB_COL6};

int kb_row[] = {KB_ROW0, KB_ROW1, KB_ROW2, KB_ROW3, KB_ROW4, KB_ROW5, KB_ROW6, KB_ROW7, KB_ROW8, KB_ROW9};

void drawBlank(void)
{
	if(cursorBlinkState == true)
		drawChar(0x20);
}

void printKeyboardBuffer(void)
{
	bool shifted = false;
	
	char noCase[] =	  {0xFF,0xFF,0xFF,0xFF,0xFF,	//Col0, Row0-4
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
	
	char shiftCase[] = {0xFF,0xFF,0xFF,0xFF,0xFF,	//Col0, Row0-4
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
				if(xCharPos > 0)  ///I think I need to decouple the reading the next cursor
				//and actually moving the thing.
				{
					
					drawCursorBuffer();
					moveCursor(xCharPos-1,yCharPos);
					
					//clearCursorBuffer();
				}
			}
			else if(scanCodeBuffer[i] == 45)	//down
			{
				if(yCharPos < 24)
				{
					
					drawCursorBuffer();
					moveCursor(xCharPos,yCharPos+1);
					
					//clearCursorBuffer();
				}
			}
			else if(scanCodeBuffer[i] == 55)	//up
			{
				if(yCharPos > 0)
				{
					
					drawCursorBuffer();
					moveCursor(xCharPos,yCharPos-1);
					
					//clearCursorBuffer();
				}
			}
			else if(scanCodeBuffer[i] == 65)	//right
			{
				if(xCharPos < 79)
				{
					
					drawCursorBuffer();
					moveCursor(xCharPos+1,yCharPos);
					
					//clearCursorBuffer();
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
					drawCursorBuffer();
					newLine();
					xCharPos = 0;
				}
				else
				{
					drawCursorBuffer();
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
				drawCursorBuffer();
				xCharPos--;
				drawChar(0x20);
				//drawCursorBuffer();
				clearCursorBuffer();
				moveCursor(xCharPos,yCharPos);
				
			}
			else
			{
				if(shifted)
				{
					drawChar(shiftCase[scanCodeBuffer[i]]);
					if(xCharPos < 79)
					{
						moveCursor(xCharPos++,yCharPos);
						xCharPos++;
						clearCursorBuffer();
					}
				}
				else
				{
					drawChar(noCase[scanCodeBuffer[i]]);
					//clearCursorBuffer();
					if(xCharPos < 79)
					{
						moveCursor(xCharPos++,yCharPos);
						xCharPos++;
						clearCursorBuffer();
					}
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
	
	all keys are added to the keyDownBuffer. This is to 
	
	Relevant information:
	------------------------------------------------------------------------
	KB_ROW0		PORT_PA02				KB_COL0		PORT_PA16
	KB_ROW1		PORT_PA03				KB_COL1		PORT_PA17
	KB_ROW2		PORT_PA04				KB_COL2		PORT_PA18
	KB_ROW3		PORT_PA05				KB_COL3		PORT_PA19
	KB_ROW4		PORT_PA06				KB_COL4		PORT_PA20
	KB_ROW5		PORT_PA07				KB_COL5		PORT_PA21
	KB_ROW6		PORT_PA10				KB_COL6		PORT_PA27
	KB_ROW7		PORT_PA11
	KB_ROW8		PORT_PA12
	KB_ROW9		PORT_PA13	*/
	
	int scanCodeIndex = 0;
	int scanCodes[70];
	
	//Set strong drive on column
	PORT->Group[0].WRCONFIG.bit.DRVSTR = 1;
	
	//Set all columns as output, low
	REG_PORT_DIRSET0 = KB_COL0;
	REG_PORT_DIRSET0 = KB_COL1;
	REG_PORT_DIRSET0 = KB_COL2;
	REG_PORT_DIRSET0 = KB_COL3;
	REG_PORT_DIRSET0 = KB_COL4;
	REG_PORT_DIRSET0 = KB_COL5;
	REG_PORT_DIRSET0 = KB_COL6;

	REG_PORT_OUTCLR0 = KB_COL0;
	REG_PORT_OUTCLR0 = KB_COL1;
	REG_PORT_OUTCLR0 = KB_COL2;
	REG_PORT_OUTCLR0 = KB_COL3;
	REG_PORT_OUTCLR0 = KB_COL4;
	REG_PORT_OUTCLR0 = KB_COL5;
	REG_PORT_OUTCLR0 = KB_COL6;
	
	//set rows to input, pullup enabled
	REG_PORT_DIRCLR0 = KB_ROW0;
	REG_PORT_DIRCLR0 = KB_ROW1;
	REG_PORT_DIRCLR0 = KB_ROW2;
	REG_PORT_DIRCLR0 = KB_ROW3;
	REG_PORT_DIRCLR0 = KB_ROW4;
	REG_PORT_DIRCLR0 = KB_ROW5;
	REG_PORT_DIRCLR0 = KB_ROW6;
	REG_PORT_DIRCLR0 = KB_ROW7;
	REG_PORT_DIRCLR0 = KB_ROW8;
	REG_PORT_DIRCLR0 = KB_ROW9;
	
	PORT->Group[0].PINCFG[02].bit.PULLEN = 1;
	PORT->Group[0].PINCFG[03].bit.PULLEN = 1;
	PORT->Group[0].PINCFG[04].bit.PULLEN = 1;
	PORT->Group[0].PINCFG[05].bit.PULLEN = 1;
	PORT->Group[0].PINCFG[06].bit.PULLEN = 1;
	PORT->Group[0].PINCFG[07].bit.PULLEN = 1;
	PORT->Group[0].PINCFG[10].bit.PULLEN = 1;
	PORT->Group[0].PINCFG[11].bit.PULLEN = 1;
	PORT->Group[0].PINCFG[12].bit.PULLEN = 1;
	PORT->Group[0].PINCFG[13].bit.PULLEN = 1;
	
	PORT->Group[0].PINCFG[02].bit.INEN = 1;
	PORT->Group[0].PINCFG[03].bit.INEN = 1;
	PORT->Group[0].PINCFG[04].bit.INEN = 1;
	PORT->Group[0].PINCFG[05].bit.INEN = 1;
	PORT->Group[0].PINCFG[06].bit.INEN = 1;
	PORT->Group[0].PINCFG[07].bit.INEN = 1;
	PORT->Group[0].PINCFG[10].bit.INEN = 1;
	PORT->Group[0].PINCFG[11].bit.INEN = 1;
	PORT->Group[0].PINCFG[12].bit.INEN = 1;
	PORT->Group[0].PINCFG[13].bit.INEN = 1;
	
	/*
	//We're going to loop through the columns, and inside the rows
	//if a key is high, set the scancode index to that thing.
	for(int i = 0 ; i <= 6 ; i++)
	{
		REG_PORT_OUTSET0 = kb_col[i];
		for(int j = 0 ; j <= 9 ; j++)
		{
			if((PORT->Group[0].IN.reg & kb_row[j]) != 0)
			scanCodes[scanCodeIndex] = ((i*10) + j);
			scanCodeIndex++;
		}	
		REG_PORT_OUTCLR0 = kb_col[i];
	}
	*/
	
	//Step through columns, if high, save that column.
	//This is column 0
	REG_PORT_OUTSET0 = KB_COL0;
	if((PORT->Group[0].IN.reg & KB_ROW0) != 0)
	{
		scanCodes[scanCodeIndex] = 0; scanCodeIndex++;
	}
	if((PORT->Group[0].IN.reg & KB_ROW1) != 0)
	{
		scanCodes[scanCodeIndex] = 1; scanCodeIndex++;
	}
	if((PORT->Group[0].IN.reg & KB_ROW2) != 0)
	{
		scanCodes[scanCodeIndex] = 2; scanCodeIndex++;
	}
	if((PORT->Group[0].IN.reg & KB_ROW3) != 0)
	{
		scanCodes[scanCodeIndex] = 3; scanCodeIndex++;
	}
	if((PORT->Group[0].IN.reg & KB_ROW4) != 0)
	{
		scanCodes[scanCodeIndex] = 4; scanCodeIndex++;
	}
	if((PORT->Group[0].IN.reg & KB_ROW5) != 0)
	{
		scanCodes[scanCodeIndex] = 5; scanCodeIndex++;
	}
	if((PORT->Group[0].IN.reg & KB_ROW6) != 0)
	{
		scanCodes[scanCodeIndex] = 6; scanCodeIndex++;
	}
	if((PORT->Group[0].IN.reg & KB_ROW7) != 0)
	{
		scanCodes[scanCodeIndex] = 7; scanCodeIndex++;
	}
	if((PORT->Group[0].IN.reg & KB_ROW8) != 0)
	{
		scanCodes[scanCodeIndex] = 8; scanCodeIndex++;
	}
	if((PORT->Group[0].IN.reg & KB_ROW9) != 0)
	{
		scanCodes[scanCodeIndex] = 9; scanCodeIndex++;
	}
	REG_PORT_OUTCLR0 = KB_COL0;
	
	//This is column 1
	REG_PORT_OUTSET0 = KB_COL1;
	if((PORT->Group[0].IN.reg & KB_ROW0) != 0)
	{
		scanCodes[scanCodeIndex] = 10; scanCodeIndex++;
	}
	if((PORT->Group[0].IN.reg & KB_ROW1) != 0)
	{
		scanCodes[scanCodeIndex] = 11; scanCodeIndex++;
	}
	if((PORT->Group[0].IN.reg & KB_ROW2) != 0)
	{
		scanCodes[scanCodeIndex] = 12; scanCodeIndex++;
	}
	if((PORT->Group[0].IN.reg & KB_ROW3) != 0)
	{
		scanCodes[scanCodeIndex] = 13; scanCodeIndex++;
	}
	if((PORT->Group[0].IN.reg & KB_ROW4) != 0)
	{
		scanCodes[scanCodeIndex] = 14; scanCodeIndex++;
	}
	if((PORT->Group[0].IN.reg & KB_ROW5) != 0)
	{
		scanCodes[scanCodeIndex] = 15; scanCodeIndex++;
	}
	if((PORT->Group[0].IN.reg & KB_ROW6) != 0)
	{
		scanCodes[scanCodeIndex] = 16; scanCodeIndex++;
	}
	if((PORT->Group[0].IN.reg & KB_ROW7) != 0)
	{
		scanCodes[scanCodeIndex] = 17; scanCodeIndex++;
	}
	if((PORT->Group[0].IN.reg & KB_ROW8) != 0)
	{
		scanCodes[scanCodeIndex] = 18; scanCodeIndex++;
	}
	if((PORT->Group[0].IN.reg & KB_ROW9) != 0)
	{
		scanCodes[scanCodeIndex] = 19; scanCodeIndex++;
	}
	REG_PORT_OUTCLR0 = KB_COL1;
	
	//This is column 2
	REG_PORT_OUTSET0 = KB_COL2;
	if((PORT->Group[0].IN.reg & KB_ROW0) != 0)
	{
		scanCodes[scanCodeIndex] = 20; scanCodeIndex++;
	}
	if((PORT->Group[0].IN.reg & KB_ROW1) != 0)
	{
		scanCodes[scanCodeIndex] = 21; scanCodeIndex++;
	}
	if((PORT->Group[0].IN.reg & KB_ROW2) != 0)
	{
		scanCodes[scanCodeIndex] = 22; scanCodeIndex++;
	}
	if((PORT->Group[0].IN.reg & KB_ROW3) != 0)
	{
		scanCodes[scanCodeIndex] = 23; scanCodeIndex++;
	}
	if((PORT->Group[0].IN.reg & KB_ROW4) != 0)
	{
		scanCodes[scanCodeIndex] = 24; scanCodeIndex++;
	}
	if((PORT->Group[0].IN.reg & KB_ROW5) != 0)
	{
		scanCodes[scanCodeIndex] = 25; scanCodeIndex++;
	}
	if((PORT->Group[0].IN.reg & KB_ROW6) != 0)
	{
		scanCodes[scanCodeIndex] = 26; scanCodeIndex++;
	}
	if((PORT->Group[0].IN.reg & KB_ROW7) != 0)
	{
		scanCodes[scanCodeIndex] = 27; scanCodeIndex++;
	}
	if((PORT->Group[0].IN.reg & KB_ROW8) != 0)
	{
		scanCodes[scanCodeIndex] = 28; scanCodeIndex++;
	}
	if((PORT->Group[0].IN.reg & KB_ROW9) != 0)
	{
		scanCodes[scanCodeIndex] = 29; scanCodeIndex++;
	}
	REG_PORT_OUTCLR0 = KB_COL2;
	
	//This is column 3
	REG_PORT_OUTSET0 = KB_COL3;
	if((PORT->Group[0].IN.reg & KB_ROW0) != 0)
	{
		scanCodes[scanCodeIndex] = 30; scanCodeIndex++;
	}
	if((PORT->Group[0].IN.reg & KB_ROW1) != 0)
	{
		scanCodes[scanCodeIndex] = 31; scanCodeIndex++;
	}
	if((PORT->Group[0].IN.reg & KB_ROW2) != 0)
	{
		scanCodes[scanCodeIndex] = 32; scanCodeIndex++;
	}
	if((PORT->Group[0].IN.reg & KB_ROW3) != 0)
	{
		scanCodes[scanCodeIndex] = 33; scanCodeIndex++;
	}
	if((PORT->Group[0].IN.reg & KB_ROW4) != 0)
	{
		scanCodes[scanCodeIndex] = 34; scanCodeIndex++;
	}
	if((PORT->Group[0].IN.reg & KB_ROW5) != 0)
	{
		scanCodes[scanCodeIndex] = 35; scanCodeIndex++;
	}
	if((PORT->Group[0].IN.reg & KB_ROW6) != 0)
	{
		scanCodes[scanCodeIndex] = 36; scanCodeIndex++;
	}
	if((PORT->Group[0].IN.reg & KB_ROW7) != 0)
	{
		scanCodes[scanCodeIndex] = 37; scanCodeIndex++;
	}
	if((PORT->Group[0].IN.reg & KB_ROW8) != 0)
	{
		scanCodes[scanCodeIndex] = 38; scanCodeIndex++;
	}
	if((PORT->Group[0].IN.reg & KB_ROW9) != 0)
	{
		scanCodes[scanCodeIndex] = 39; scanCodeIndex++;
	}
	REG_PORT_OUTCLR0 = KB_COL3;
	
	//This is column 4
	REG_PORT_OUTSET0 = KB_COL4;
	if((PORT->Group[0].IN.reg & KB_ROW0) != 0)
	{
		scanCodes[scanCodeIndex] = 40; scanCodeIndex++;
	}
	if((PORT->Group[0].IN.reg & KB_ROW1) != 0)
	{
		scanCodes[scanCodeIndex] = 41; scanCodeIndex++;
	}
	if((PORT->Group[0].IN.reg & KB_ROW2) != 0)
	{
		scanCodes[scanCodeIndex] = 42; scanCodeIndex++;
	}
	if((PORT->Group[0].IN.reg & KB_ROW3) != 0)
	{
		scanCodes[scanCodeIndex] = 43; scanCodeIndex++;
	}
	if((PORT->Group[0].IN.reg & KB_ROW4) != 0)
	{
		scanCodes[scanCodeIndex] = 44; scanCodeIndex++;
	}
	if((PORT->Group[0].IN.reg & KB_ROW5) != 0)
	{
		scanCodes[scanCodeIndex] = 45; scanCodeIndex++;
	}
	if((PORT->Group[0].IN.reg & KB_ROW6) != 0)
	{
		scanCodes[scanCodeIndex] = 46; scanCodeIndex++;
	}
	if((PORT->Group[0].IN.reg & KB_ROW7) != 0)
	{
		scanCodes[scanCodeIndex] = 47; scanCodeIndex++;
	}
	if((PORT->Group[0].IN.reg & KB_ROW8) != 0)
	{
		scanCodes[scanCodeIndex] = 48; scanCodeIndex++;
	}
	if((PORT->Group[0].IN.reg & KB_ROW9) != 0)
	{
		scanCodes[scanCodeIndex] = 49; scanCodeIndex++;
	}
	REG_PORT_OUTCLR0 = KB_COL4;
	
	//This is column 5
	REG_PORT_OUTSET0 = KB_COL5;
	if((PORT->Group[0].IN.reg & KB_ROW0) != 0)
	{
		scanCodes[scanCodeIndex] = 50; scanCodeIndex++;
	}
	if((PORT->Group[0].IN.reg & KB_ROW1) != 0)
	{
		scanCodes[scanCodeIndex] = 51; scanCodeIndex++;
	}
	if((PORT->Group[0].IN.reg & KB_ROW2) != 0)
	{
		scanCodes[scanCodeIndex] = 52; scanCodeIndex++;
	}
	if((PORT->Group[0].IN.reg & KB_ROW3) != 0)
	{
		scanCodes[scanCodeIndex] = 53; scanCodeIndex++;
	}
	if((PORT->Group[0].IN.reg & KB_ROW4) != 0)
	{
		scanCodes[scanCodeIndex] = 54; scanCodeIndex++;
	}
	if((PORT->Group[0].IN.reg & KB_ROW5) != 0)
	{
		scanCodes[scanCodeIndex] = 55; scanCodeIndex++;
	}
	if((PORT->Group[0].IN.reg & KB_ROW6) != 0)
	{
		scanCodes[scanCodeIndex] = 56; scanCodeIndex++;
	}
	if((PORT->Group[0].IN.reg & KB_ROW7) != 0)
	{
		scanCodes[scanCodeIndex] = 57; scanCodeIndex++;
	}
	if((PORT->Group[0].IN.reg & KB_ROW8) != 0)
	{
		scanCodes[scanCodeIndex] = 58; scanCodeIndex++;
	}
	if((PORT->Group[0].IN.reg & KB_ROW9) != 0)
	{
		scanCodes[scanCodeIndex] = 59; scanCodeIndex++;
	}
	REG_PORT_OUTCLR0 = KB_COL5;
	
	//This is column 6
	REG_PORT_OUTSET0 = KB_COL6;
	if((PORT->Group[0].IN.reg & KB_ROW0) != 0)
	{
		scanCodes[scanCodeIndex] = 60; scanCodeIndex++;
	}
	if((PORT->Group[0].IN.reg & KB_ROW1) != 0)
	{
		scanCodes[scanCodeIndex] = 61; scanCodeIndex++;
	}
	if((PORT->Group[0].IN.reg & KB_ROW2) != 0)
	{
		scanCodes[scanCodeIndex] = 62; scanCodeIndex++;
	}
	if((PORT->Group[0].IN.reg & KB_ROW3) != 0)
	{
		scanCodes[scanCodeIndex] = 63; scanCodeIndex++;
	}
	if((PORT->Group[0].IN.reg & KB_ROW4) != 0)
	{
		scanCodes[scanCodeIndex] = 64; scanCodeIndex++;
	}
	if((PORT->Group[0].IN.reg & KB_ROW5) != 0)
	{
		scanCodes[scanCodeIndex] = 65; scanCodeIndex++;
	}
	if((PORT->Group[0].IN.reg & KB_ROW6) != 0)
	{
		scanCodes[scanCodeIndex] = 66; scanCodeIndex++;
	}
	if((PORT->Group[0].IN.reg & KB_ROW7) != 0)
	{
		scanCodes[scanCodeIndex] = 67; scanCodeIndex++;
	}
	if((PORT->Group[0].IN.reg & KB_ROW8) != 0)
	{
		scanCodes[scanCodeIndex] = 68; scanCodeIndex++;
	}
	if((PORT->Group[0].IN.reg & KB_ROW9) != 0)
	{
		scanCodes[scanCodeIndex] = 69; scanCodeIndex++; //nice.
	}
	REG_PORT_OUTCLR0 = KB_COL6;
	
	/*Now we set all of the *ROWS* as outputs, starting low, and read the
	column pins. Stuff them into the array, just like before.
	*/
	
	//Set all rows as output, low
	REG_PORT_DIRSET0 = KB_ROW0;
	REG_PORT_DIRSET0 = KB_ROW1;
	REG_PORT_DIRSET0 = KB_ROW2;
	REG_PORT_DIRSET0 = KB_ROW3;
	REG_PORT_DIRSET0 = KB_ROW4;
	REG_PORT_DIRSET0 = KB_ROW5;
	REG_PORT_DIRSET0 = KB_ROW6;
	REG_PORT_DIRSET0 = KB_ROW7;
	REG_PORT_DIRSET0 = KB_ROW8;
	REG_PORT_DIRSET0 = KB_ROW9;
	
	REG_PORT_OUTCLR0 = KB_ROW0;
	REG_PORT_OUTCLR0 = KB_ROW1;
	REG_PORT_OUTCLR0 = KB_ROW2;
	REG_PORT_OUTCLR0 = KB_ROW3;
	REG_PORT_OUTCLR0 = KB_ROW4;
	REG_PORT_OUTCLR0 = KB_ROW5;
	REG_PORT_OUTCLR0 = KB_ROW6;
	REG_PORT_OUTCLR0 = KB_ROW7;
	REG_PORT_OUTCLR0 = KB_ROW8;
	REG_PORT_OUTCLR0 = KB_ROW9;
		
	//set columns to input, pullup enabled
	REG_PORT_DIRCLR0 = KB_COL0;
	REG_PORT_DIRCLR0 = KB_COL1;
	REG_PORT_DIRCLR0 = KB_COL2;
	REG_PORT_DIRCLR0 = KB_COL3;
	REG_PORT_DIRCLR0 = KB_COL4;
	REG_PORT_DIRCLR0 = KB_COL5;
	REG_PORT_DIRCLR0 = KB_COL6;
	
	PORT->Group[0].PINCFG[16].bit.PULLEN = 1;
	PORT->Group[0].PINCFG[17].bit.PULLEN = 1;
	PORT->Group[0].PINCFG[18].bit.PULLEN = 1;
	PORT->Group[0].PINCFG[19].bit.PULLEN = 1;
	PORT->Group[0].PINCFG[20].bit.PULLEN = 1;
	PORT->Group[0].PINCFG[21].bit.PULLEN = 1;
	PORT->Group[0].PINCFG[27].bit.PULLEN = 1;
	
	PORT->Group[0].PINCFG[16].bit.INEN = 1;
	PORT->Group[0].PINCFG[17].bit.INEN = 1;
	PORT->Group[0].PINCFG[18].bit.INEN = 1;
	PORT->Group[0].PINCFG[19].bit.INEN = 1;
	PORT->Group[0].PINCFG[20].bit.INEN = 1;
	PORT->Group[0].PINCFG[21].bit.INEN = 1;
	PORT->Group[0].PINCFG[27].bit.INEN = 1;
	
	/*
	
	//This is row 0
	REG_PORT_OUTSET0 = KB_ROW0;
	if((PORT->Group[0].IN.reg & KB_COL0) != 0)
	{
		scanCodes[scanCodeIndex] = 0; scanCodeIndex++;
	}
	if((PORT->Group[0].IN.reg & KB_COL1) != 0)
	{
		scanCodes[scanCodeIndex] = 10; scanCodeIndex++;
	}
	if((PORT->Group[0].IN.reg & KB_COL2) != 0)
	{
		scanCodes[scanCodeIndex] = 20; scanCodeIndex++;
	}
	if((PORT->Group[0].IN.reg & KB_COL3) != 0)
	{
		scanCodes[scanCodeIndex] = 30; scanCodeIndex++;
	}
	if((PORT->Group[0].IN.reg & KB_COL4) != 0)
	{
		scanCodes[scanCodeIndex] = 40; scanCodeIndex++;
	}
	if((PORT->Group[0].IN.reg & KB_COL5) != 0)
	{
		scanCodes[scanCodeIndex] = 50; scanCodeIndex++;
	}
	if((PORT->Group[0].IN.reg & KB_COL6) != 0)
	{
		scanCodes[scanCodeIndex] = 60; scanCodeIndex++;
	}
	REG_PORT_OUTCLR0 = KB_ROW0;
	
	//This is row 1
	REG_PORT_OUTSET0 = KB_ROW1;
	if((PORT->Group[0].IN.reg & KB_COL0) != 0)
	{
		scanCodes[scanCodeIndex] = 1; scanCodeIndex++;
	}
	if((PORT->Group[0].IN.reg & KB_COL1) != 0)
	{
		scanCodes[scanCodeIndex] = 11; scanCodeIndex++;
	}
	if((PORT->Group[0].IN.reg & KB_COL2) != 0)
	{
		scanCodes[scanCodeIndex] = 21; scanCodeIndex++;
	}
	if((PORT->Group[0].IN.reg & KB_COL3) != 0)
	{
		scanCodes[scanCodeIndex] = 31; scanCodeIndex++;
	}
	if((PORT->Group[0].IN.reg & KB_COL4) != 0)
	{
		scanCodes[scanCodeIndex] = 41; scanCodeIndex++;
	}
	if((PORT->Group[0].IN.reg & KB_COL5) != 0)
	{
		scanCodes[scanCodeIndex] = 51; scanCodeIndex++;
	}
	if((PORT->Group[0].IN.reg & KB_COL6) != 0)
	{
		scanCodes[scanCodeIndex] = 61; scanCodeIndex++;
	}
	REG_PORT_OUTCLR0 = KB_ROW1;
	
	//This is row 2
	REG_PORT_OUTSET0 = KB_ROW2;
	if((PORT->Group[0].IN.reg & KB_COL0) != 0)
	{
		scanCodes[scanCodeIndex] = 2; scanCodeIndex++;
	}
	if((PORT->Group[0].IN.reg & KB_COL1) != 0)
	{
		scanCodes[scanCodeIndex] = 12; scanCodeIndex++;
	}
	if((PORT->Group[0].IN.reg & KB_COL2) != 0)
	{
		scanCodes[scanCodeIndex] = 22; scanCodeIndex++;
	}
	if((PORT->Group[0].IN.reg & KB_COL3) != 0)
	{
		scanCodes[scanCodeIndex] = 32; scanCodeIndex++;
	}
	if((PORT->Group[0].IN.reg & KB_COL4) != 0)
	{
		scanCodes[scanCodeIndex] = 42; scanCodeIndex++;
	}
	if((PORT->Group[0].IN.reg & KB_COL5) != 0)
	{
		scanCodes[scanCodeIndex] = 52; scanCodeIndex++;
	}
	if((PORT->Group[0].IN.reg & KB_COL6) != 0)
	{
		scanCodes[scanCodeIndex] = 62; scanCodeIndex++;
	}
	REG_PORT_OUTCLR0 = KB_ROW2;
	
	//This is row 3
	REG_PORT_OUTSET0 = KB_ROW3;
	if((PORT->Group[0].IN.reg & KB_COL0) != 0)
	{
		scanCodes[scanCodeIndex] = 3; scanCodeIndex++;
	}
	if((PORT->Group[0].IN.reg & KB_COL1) != 0)
	{
		scanCodes[scanCodeIndex] = 13; scanCodeIndex++;
	}
	if((PORT->Group[0].IN.reg & KB_COL2) != 0)
	{
		scanCodes[scanCodeIndex] = 23; scanCodeIndex++;
	}
	if((PORT->Group[0].IN.reg & KB_COL3) != 0)
	{
		scanCodes[scanCodeIndex] = 33; scanCodeIndex++;
	}
	if((PORT->Group[0].IN.reg & KB_COL4) != 0)
	{
		scanCodes[scanCodeIndex] = 43; scanCodeIndex++;
	}
	if((PORT->Group[0].IN.reg & KB_COL5) != 0)
	{
		scanCodes[scanCodeIndex] = 53; scanCodeIndex++;
	}
	if((PORT->Group[0].IN.reg & KB_COL6) != 0)
	{
		scanCodes[scanCodeIndex] = 63; scanCodeIndex++;
	}
	REG_PORT_OUTCLR0 = KB_ROW3;
	
	//This is row 4
	REG_PORT_OUTSET0 = KB_ROW4;
	if((PORT->Group[0].IN.reg & KB_COL0) != 0)
	{
		scanCodes[scanCodeIndex] = 4; scanCodeIndex++;
	}
	if((PORT->Group[0].IN.reg & KB_COL1) != 0)
	{
		scanCodes[scanCodeIndex] = 14; scanCodeIndex++;
	}
	if((PORT->Group[0].IN.reg & KB_COL2) != 0)
	{
		scanCodes[scanCodeIndex] = 24; scanCodeIndex++;
	}
	if((PORT->Group[0].IN.reg & KB_COL3) != 0)
	{
		scanCodes[scanCodeIndex] = 34; scanCodeIndex++;
	}
	if((PORT->Group[0].IN.reg & KB_COL4) != 0)
	{
		scanCodes[scanCodeIndex] = 44; scanCodeIndex++;
	}
	if((PORT->Group[0].IN.reg & KB_COL5) != 0)
	{
		scanCodes[scanCodeIndex] = 54; scanCodeIndex++;
	}
	if((PORT->Group[0].IN.reg & KB_COL6) != 0)
	{
		scanCodes[scanCodeIndex] = 64; scanCodeIndex++;
	}
	REG_PORT_OUTCLR0 = KB_ROW4;
	
	//This is row 5
	REG_PORT_OUTSET0 = KB_ROW5;
	if((PORT->Group[0].IN.reg & KB_COL0) != 0)
	{
		scanCodes[scanCodeIndex] = 5; scanCodeIndex++;
	}
	if((PORT->Group[0].IN.reg & KB_COL1) != 0)
	{
		scanCodes[scanCodeIndex] = 15; scanCodeIndex++;
	}
	if((PORT->Group[0].IN.reg & KB_COL2) != 0)
	{
		scanCodes[scanCodeIndex] = 25; scanCodeIndex++;
	}
	if((PORT->Group[0].IN.reg & KB_COL3) != 0)
	{
		scanCodes[scanCodeIndex] = 35; scanCodeIndex++;
	}
	if((PORT->Group[0].IN.reg & KB_COL4) != 0)
	{
		scanCodes[scanCodeIndex] = 45; scanCodeIndex++;
	}
	if((PORT->Group[0].IN.reg & KB_COL5) != 0)
	{
		scanCodes[scanCodeIndex] = 55; scanCodeIndex++;
	}
	if((PORT->Group[0].IN.reg & KB_COL6) != 0)
	{
		scanCodes[scanCodeIndex] = 65; scanCodeIndex++;
	}
	REG_PORT_OUTCLR0 = KB_ROW5;
	
	//This is row 6
	REG_PORT_OUTSET0 = KB_ROW6;
	if((PORT->Group[0].IN.reg & KB_COL0) != 0)
	{
		scanCodes[scanCodeIndex] = 6; scanCodeIndex++;
	}
	if((PORT->Group[0].IN.reg & KB_COL1) != 0)
	{
		scanCodes[scanCodeIndex] = 16; scanCodeIndex++;
	}
	if((PORT->Group[0].IN.reg & KB_COL2) != 0)
	{
		scanCodes[scanCodeIndex] = 26; scanCodeIndex++;
	}
	if((PORT->Group[0].IN.reg & KB_COL3) != 0)
	{
		scanCodes[scanCodeIndex] = 36; scanCodeIndex++;
	}
	if((PORT->Group[0].IN.reg & KB_COL4) != 0)
	{
		scanCodes[scanCodeIndex] = 46; scanCodeIndex++;
	}
	if((PORT->Group[0].IN.reg & KB_COL5) != 0)
	{
		scanCodes[scanCodeIndex] = 56; scanCodeIndex++;
	}
	if((PORT->Group[0].IN.reg & KB_COL6) != 0)
	{
		scanCodes[scanCodeIndex] = 66; scanCodeIndex++;
	}
	REG_PORT_OUTCLR0 = KB_ROW6;
	
	//This is row 7
	REG_PORT_OUTSET0 = KB_ROW7;
	if((PORT->Group[0].IN.reg & KB_COL0) != 0)
	{
		scanCodes[scanCodeIndex] = 7; scanCodeIndex++;
	}
	if((PORT->Group[0].IN.reg & KB_COL1) != 0)
	{
		scanCodes[scanCodeIndex] = 17; scanCodeIndex++;
	}
	if((PORT->Group[0].IN.reg & KB_COL2) != 0)
	{
		scanCodes[scanCodeIndex] = 27; scanCodeIndex++;
	}
	if((PORT->Group[0].IN.reg & KB_COL3) != 0)
	{
		scanCodes[scanCodeIndex] = 37; scanCodeIndex++;
	}
	if((PORT->Group[0].IN.reg & KB_COL4) != 0)
	{
		scanCodes[scanCodeIndex] = 47; scanCodeIndex++;
	}
	if((PORT->Group[0].IN.reg & KB_COL5) != 0)
	{
		scanCodes[scanCodeIndex] = 57; scanCodeIndex++;
	}
	if((PORT->Group[0].IN.reg & KB_COL6) != 0)
	{
		scanCodes[scanCodeIndex] = 67; scanCodeIndex++;
	}
	REG_PORT_OUTCLR0 = KB_ROW7;
	
	//This is row 8
	REG_PORT_OUTSET0 = KB_ROW8;
	if((PORT->Group[0].IN.reg & KB_COL0) != 0)
	{
		scanCodes[scanCodeIndex] = 8; scanCodeIndex++;
	}
	if((PORT->Group[0].IN.reg & KB_COL1) != 0)
	{
		scanCodes[scanCodeIndex] = 18; scanCodeIndex++;
	}
	if((PORT->Group[0].IN.reg & KB_COL2) != 0)
	{
		scanCodes[scanCodeIndex] = 28; scanCodeIndex++;
	}
	if((PORT->Group[0].IN.reg & KB_COL3) != 0)
	{
		scanCodes[scanCodeIndex] = 38; scanCodeIndex++;
	}
	if((PORT->Group[0].IN.reg & KB_COL4) != 0)
	{
		scanCodes[scanCodeIndex] = 48; scanCodeIndex++;
	}
	if((PORT->Group[0].IN.reg & KB_COL5) != 0)
	{
		scanCodes[scanCodeIndex] = 58; scanCodeIndex++;
	}
	if((PORT->Group[0].IN.reg & KB_COL6) != 0)
	{
		scanCodes[scanCodeIndex] = 68; scanCodeIndex++;
	}
	REG_PORT_OUTCLR0 = KB_ROW8;

	//This is row 9
	REG_PORT_OUTSET0 = KB_ROW9;
	if((PORT->Group[0].IN.reg & KB_COL0) != 0)
	{
		scanCodes[scanCodeIndex] = 9; scanCodeIndex++;
	}

	if((PORT->Group[0].IN.reg & KB_COL1) != 0)
	{
		scanCodes[scanCodeIndex] = 19; scanCodeIndex++;
	}

	if((PORT->Group[0].IN.reg & KB_COL2) != 0)
	{
		scanCodes[scanCodeIndex] = 29; scanCodeIndex++;
	}
	if((PORT->Group[0].IN.reg & KB_COL3) != 0)
	{
		scanCodes[scanCodeIndex] = 39; scanCodeIndex++;
	}
	if((PORT->Group[0].IN.reg & KB_COL4) != 0)
	{
		scanCodes[scanCodeIndex] = 49; scanCodeIndex++;
	}
	if((PORT->Group[0].IN.reg & KB_COL5) != 0)
	{
		scanCodes[scanCodeIndex] = 59; scanCodeIndex++;
	}
	if((PORT->Group[0].IN.reg & KB_COL6) != 0)
	{
		scanCodes[scanCodeIndex] = 69; scanCodeIndex++;
	}
	REG_PORT_OUTCLR0 = KB_ROW9;
	

	

	*/

	
	for(int i = 0; i < scanCodeIndex; i++)
	{
		if(!bufferContains(scanCodes[i]))
		{
			
			scanCodeBuffer[i] = scanCodes[i];

		}
	}

}

bool bufferContains(int scanCode)
{
	for(int i = 0 ; i < 20 ; i++)
	{
		if(scanCodeBuffer[i] == scanCode)
		{
			return true;
		}
		else
		{
			return false;
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
		else
		{
			return false;
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

	setXY(abs(xCharPos-79)*10,yCharPos*20,abs(xCharPos-79)*10+9,yCharPos*20+19);
	
	for(uint16_t i = 0 ; i < 200 ; i++)
	{
		if((cursorBuffer[i] == 0xFF))
		setPixel((fore_Color_High<<8)|fore_Color_Low);
		else
		setPixel((back_Color_High<<8)|back_Color_Low);
	}
	

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

void moveCursor(uint8_t x, uint8_t y)
{
	//First, this reads the GRAM memory at the cursor location
	//x,y. This is saved in a buffer. When the cursor blinks,
	//it alternates either that buffer, or the *inverse* of that
	//buffer.
	
	//All this function does is read the GRAM and move the cursor.
	
	//set PB07 to input
	REG_PORT_DIRCLR1 = PORT_PB07;
	PORT->Group[1].PINCFG[7].bit.INEN = 1;
	PORT->Group[1].PINCFG[7].bit.PULLEN = 1;
	
	
	//Per page 40 of datasheet (5.1.2.7, 16-bit
	//parallel interface for data ram read.
	REG_PORT_OUTCLR1 = LCD_CS;
	setXY(abs(x-79)*10,y*20,abs(x-79)*10+9,y*20+19);
	
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
	REG_PORT_DIRSET1 = 0x0000FFFF;
	
	//The cursor data is in the cursorBuffer, so now we move
	//xCharPos and yCharPos
	xCharPos = x;
	yCharPos = y;
	
}

void blinkCursor(void)
{
	if(cursorBlinkState)
	{

		//Draw the *inverse* of cursorBuffer
		setXY(abs(xCharPos-79)*10,yCharPos*20,abs(xCharPos-79)*10+9,yCharPos*20+19);
		
		for(uint16_t i = 0 ; i < 200 ; i++)
		{
			if((cursorBuffer[i] != 0xFF))
			setPixel((fore_Color_High<<8)|fore_Color_Low);
			else
			setPixel((back_Color_High<<8)|back_Color_Low);
		}
		
		//finally set cursorBlinkState to false
		cursorBlinkState = !cursorBlinkState;
	}
	else
	{

		setXY(abs(xCharPos-79)*10,yCharPos*20,abs(xCharPos-79)*10+9,yCharPos*20+19);
		
		for(uint16_t i = 0 ; i < 200 ; i++)
		{
			if((cursorBuffer[i] == 0xFF))
			setPixel((fore_Color_High<<8)|fore_Color_Low);
			else
			setPixel((back_Color_High<<8)|back_Color_Low);
		}
		//set cursorBlinkState to true
		cursorBlinkState = !cursorBlinkState;
	}
}

