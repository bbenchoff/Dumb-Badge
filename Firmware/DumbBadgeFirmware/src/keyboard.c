/*
 * keyboard.c
 *
 * Created: 6/29/2020 3:39:42 PM
 *  Author: bench
 */ 

#include <asf.h>
#include <stdint.h>
#include <stdbool.h> 


#include "globals.h"
#include "console.h"
#include "keyboard.h"
#include "LCD.h"
#include "LCDBus.h"
#include "settings.h"
#include "ouroboros.h"
#include "parser.h"

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
						
unsigned char consoleDisplay[80][24];

#define NUM_ROW 10
#define NUM_COL 7

static uint32_t kb_row[] = { KB_ROW0, KB_ROW1, KB_ROW2, KB_ROW3, KB_ROW4, KB_ROW5, KB_ROW6, KB_ROW7, KB_ROW8, KB_ROW9 };
static uint32_t kb_col[] = { KB_COL0, KB_COL1, KB_COL2, KB_COL3, KB_COL4, KB_COL5, KB_COL6 };
static int kb_row_index[] = {  2,  3,  4,  5,  6,  7, 10, 11, 12, 13 };
static int kb_col_index[] = { 16, 17, 18, 19, 20, 21, 27 };
	
cbuf_handle_t ouroboros;


/************************************************************************
	printKeyboardBuffer()
	
	This function will _only_ take keyboard input and convert that
	to either a single byte to send, or an escape code to send
	all depending on (bool localEcho) in settings.
	
*************************************************************************/
void printKeyboardBuffer(void)
{
	bool shifted = false;
	bool controled = false;
	
	unsigned char noCase[] =
		{0x1B,0x00,0x09,0x00,0x00,	//Col0, Row0-4  K_ESC, K_SETUP, K_TAB, K_NOSCL, K_RIGHTALT
		0x37,0x75,0x67,0x6A,0x2C,	//Col0, Row5-9  K_7, K_U, K_G, K_J, K_<
		0x31,0x71,0x00,0x00,0x00,	//Col1, Row0-4	K_1, K_Q, K_CAPS, K_LSHIFT, K_RIGHTMETA
		0x38,0x69,0x68,0x6B,0x00,	//Col1, Row5-9	K_8, K_I, K_H, K_K, NULL
		0x32,0x77,0x00,0x7A,0x00,	//Col2, Row0-4	K_2, K_W, K_CONTROL, K_Z, K_LEFTMETA
		0x39,0x30,0x6F,0x6C,0x2E,	//Col2, Row5-9	K_9, K_0, K_O, K_L, K_>
		0x33,0x65,0x61,0x78,0x00,	//Col3, Row0-4	K_3, K_E, K_A, K_X, K_LEFTALT
		0x00,0x2D,0x70,0x3B,0x2F,	//Col3, Row5-9	K_LEFT, K_USCORE, K_P, K_SEMI, K_?
		0x34,0x72,0x73,0x63,0x20,	//Col4, Row0-4	K_4, K_R, K_S, K_C, K_SPACE
		0x00,0x3D,0x5B,0x27,0x00,	//Col4, Row5-9	K_DOWN, K_PLUS, K_{, K_QUOTE, K_RSHIFT
		0x35,0x74,0x64,0x76,0x6E,	//Col5, Row0-4	K_5, K_T, K_D, K_V, K_N
		0x00,0x27,0x5D,0x0D,0x5C,	//Col5, Row5-9	K_UP, K_TILDE, K_}, K_RETURN, K_PIPE
		0x36,0x79,0x66,0x62,0x6D,	//Col6, Row0-4	K_6, K_Y, K_F, K_B, K_M
		0x00,0x08,0x00,0x7F,0x0A};	//Col6, Row5-9	K_RIGHT, K_BACK, K_BREAK, K_DEL, K_LINE
	
	unsigned char shiftCase[] =
		{0x1B,0x00,0x09,0x00,0x00,	//Col0, Row0-4	K_ESC, K_SETUP, K_TAB, K_NOSCL, K_RIGHTALT
		0x26,0x55,0x47,0x4A,0x3C,	//Col0, Row5-9	K_7, K_U, K_G, K_J, K_<
		0x21,0x51,0x00,0x00,0x00,	//Col1, Row0-4	K_1, K_Q, K_CAPS, K_LSHIFT, K_RIGHTMETA
		0x2A,0x49,0x48,0x4B,0x00,	//Col1, Row5-9	K_8, K_I, K_H, K_K, NULL
		0x40,0x57,0x00,0x5A,0x00,	//Col2, Row0-4	K_2, K_W, K_CONTROL, K_Z, K_LEFTMETA
		0x28,0x29,0x4F,0x4C,0x3E,	//Col2, Row5-9	K_9, K_0, K_O, K_L, K_>
		0x23,0x45,0x41,0x58,0x00,	//Col3, Row0-4	K_3, K_E, K_A, K_X, K_LEFTALT
		0x00,0x5F,0x50,0x3A,0x3F,	//Col3, Row5-9	K_LEFT, K_USCORE, K_P, K_SEMI, K_?
		0x24,0x52,0x53,0x43,0x20,	//Col4, Row0-4	K_4, K_R, K_S, K_C, K_SPACE
		0x00,0x2B,0x7B,0x22,0x00,	//Col4, Row5-9	K_DOWN, K_PLUS, K_{, K_QUOTE, K_RSHIFT
		0x25,0x54,0x44,0x56,0x4E,	//Col5, Row0-4	K_5, K_T, K_D, K_V, K_N
		0x00,0x7E,0x7D,0x0D,0x7C,	//Col5, Row5-9	K_UP, K_TILDE, K_}, K_RETURN, K_PIPE
		0x5E,0x59,0x46,0x42,0x4D,	//Col6, Row0-4	K_6, K_Y, K_F, K_B, K_M
		0x00,0x08,0x00,0x7F,0x0A};	//Col6, Row0-4	K_RIGHT, K_BACK, K_BREAK, K_DEL, K_LINE
		
	unsigned char capsLockCase[] =
		{0x1B,0x00,0x09,0x00,0x00,	//Col0, Row0-4  K_ESC, K_SETUP, K_TAB, K_NOSCL, K_RIGHTALT
		0x37,0x55,0x47,0x4A,0x2C,	//Col0, Row5-9  K_7, K_U, K_G, K_J, K_<
		0x31,0x51,0x00,0x00,0x00,	//Col1, Row0-4	K_1, K_Q, K_CAPS, K_LSHIFT, K_RIGHTMETA
		0x38,0x49,0x48,0x4B,0x00,	//Col1, Row5-9	K_8, K_I, K_H, K_K, NULL
		0x32,0x57,0x00,0x5A,0x00,	//Col2, Row0-4	K_2, K_W, K_CONTROL, K_Z, K_LEFTMETA
		0x39,0x30,0x4F,0x4C,0x2E,	//Col2, Row5-9	K_9, K_0, K_O, K_L, K_>
		0x33,0x45,0x41,0x58,0x00,	//Col3, Row0-4	K_3, K_E, K_A, K_X, K_LEFTALT
		0x00,0x2D,0x50,0x3B,0x2F,	//Col3, Row5-9	K_LEFT, K_USCORE, K_P, K_SEMI, K_?
		0x34,0x52,0x53,0x43,0x20,	//Col4, Row0-4	K_4, K_R, K_S, K_C, K_SPACE
		0x00,0x3D,0x5B,0x27,0x00,	//Col4, Row5-9	K_DOWN, K_PLUS, K_{, K_QUOTE, K_RSHIFT
		0x35,0x54,0x44,0x56,0x4E,	//Col5, Row0-4	K_5, K_T, K_D, K_V, K_N
		0x00,0x27,0x5D,0x0D,0x5C,	//Col5, Row5-9	K_UP, K_TILDE, K_}, K_RETURN, K_PIPE
		0x36,0x59,0x46,0x42,0x4D,	//Col6, Row0-4	K_6, K_Y, K_F, K_B, K_M
		0x00,0x08,0x00,0x7F,0x0A};	//Col6, Row5-9	K_RIGHT, K_BACK, K_BREAK, K_DEL, K_LINE
		
	unsigned char controlCase[] =
		{0x1B,0x00,0x09,0x00,0x00,	//Col0, Row0-4	K_ESC, K_SETUP, K_TAB, K_NOSCL, K_RIGHTALT
		0x00,0x15,0x07,0x0A,0x00,	//Col0, Row5-9	K_7, K_U, K_G, K_J, K_<
		0x00,0x11,0x00,0x00,0x00,	//Col1, Row0-4	K_1, K_Q, K_CAPS, K_LSHIFT, K_RIGHTMETA
		0x00,0x09,0x08,0x0B,0x00,	//Col1, Row5-9	K_8, K_I, K_H, K_K, --NULL--
		0x00,0x17,0x00,0x1A,0x00,	//Col2, Row0-4	K_2, K_W, K_CONTROL, K_Z, K_LEFTMETA
		0x00,0x00,0x0F,0x0A,0x00,	//Col2, Row5-9	K_9, K_0, K_O, K_L, K_>
		0x00,0x05,0x01,0x18,0x00,	//Col3, Row0-4	K_3, K_E, K_A, K_X, K_LEFTALT
		0x00,0x00,0x10,0x00,0x1F,	//Col3, Row5-9	K_LEFT, K_USCORE, K_P, K_SEMI, K_?
		0x00,0x12,0x13,0x03,0x00,	//Col4, Row0-4	K_4, K_R, K_S, K_C, K_SPACE
		0x00,0x00,0x1B,0x00,0x00,	//Col4, Row5-9	K_DOWN, K_PLUS, K_{, K_QUOTE, K_RSHIFT
		0x00,0x14,0x04,0x16,0x0E,	//Col5, Row0-4	K_5, K_T, K_D, K_V, K_N
		0x00,0x1E,0x1D,0x00,0x1C,	//Col5, Row5-9	K_UP, K_TILDE, K_}, K_RETURN, K_PIPE
		0x00,0x19,0x06,0x02,0x0D,	//Col6, Row0-4	K_6, K_Y, K_F, K_B, K_M
		0x00,0x08,0x00,0x00,0x0a,};	//Col6, Row0-4	K_RIGHT, K_BACK, K_BREAK, K_DEL, K_LINE


	//Check if Shift key or Control key is present
	for(int i=0; i<20; i++)
	{
		if((scanCodeBuffer[i] == 13) | (scanCodeBuffer[i] == 49))
		{
			shifted = true;
		}
		if(scanCodeBuffer[i] == 22)
		{
			controled = true;
		}
	}
	
	
	for(int i = 0 ; i < 20 ; i++)
	{
		if(!keyDown(scanCodeBuffer[i]))
		{
			keyDownBuffer[i] = scanCodeBuffer[i];
			
			if(scanCodeBuffer[i] == 0x00)  //do nothing
			{
				//do nothing
			}
			else if(scanCodeBuffer[i] == 0x01)	//setup button, do something weird here
			{
				//this will drop into the setup menu	
			}
			else if(scanCodeBuffer[i] == 67)		//Break key, set by break enable in settings
			{
				if(breakEnable)
				{
					ring_put(ouroboros, 0x00);
				}
				//if breakEnable false, do nothing. 
			}
			else if(scanCodeBuffer[i] == 12)			//caps lock
			{
				capsLock = !capsLock;
			}
			else if(scanCodeBuffer[i] == 3)			//scroll lock
			{
				scrollLock = !scrollLock;
			}
			else if(scanCodeBuffer[i] == 35) //left
			{
				ring_put(ouroboros, 0x1B);
				ring_put(ouroboros, 0x5B);
				ring_put(ouroboros, 0x44);
				if(localEcho)
					arrowKey(scanCodeBuffer[i]);
			}
			else if(scanCodeBuffer[i]  == 45)	//down
			{

				ring_put(ouroboros, 0x1B);
				ring_put(ouroboros, 0x5B);
				ring_put(ouroboros, 0x42);
				if(localEcho)
					arrowKey(scanCodeBuffer[i]);
			}
			else if(scanCodeBuffer[i]  == 55)	//up
			{
				ring_put(ouroboros, 0x1B);
				ring_put(ouroboros, 0x5B);
				ring_put(ouroboros, 0x41);
				if(localEcho)
					arrowKey(scanCodeBuffer[i]);
			}
			else if(scanCodeBuffer[i]  == 65)	//right
			{
				ring_put(ouroboros, 0x1B);
				ring_put(ouroboros, 0x5B);
				ring_put(ouroboros, 0x43);
				if(localEcho)
					arrowKey(scanCodeBuffer[i]);
			}
			else
			{
				if(controled)
				{
					ring_put(ouroboros, controlCase[scanCodeBuffer[i]]);
				}
				else if(capsLock)
				{
					ring_put(ouroboros, capsLockCase[scanCodeBuffer[i]]);
					if(localEcho)
						parseChar(capsLockCase[scanCodeBuffer[i]]);
				}
				else if(shifted)
				{
					ring_put(ouroboros, shiftCase[scanCodeBuffer[i]]);
					if(localEcho)
						parseChar(shiftCase[scanCodeBuffer[i]]);
				}
				else
				{
					ring_put(ouroboros, noCase[scanCodeBuffer[i]]);
					if(localEcho)
						parseChar(noCase[scanCodeBuffer[i]]);
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


	/*
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
					drawChar(consoleDisplay[xCharPos][yCharPos]);
					xCharPos--;
					tempCharacter = consoleDisplay[xCharPos][yCharPos];
					drawChar(tempCharacter);
					blinkCursor();
				}
			}
			else if(scanCodeBuffer[i] == 45)	//down
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
			else if(scanCodeBuffer[i] == 55)	//up
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
			else if(scanCodeBuffer[i] == 65)	//right
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
			
			else if((scanCodeBuffer[i] == 49) | (scanCodeBuffer[i] == 13))
			{
				//SHIFT - do nothing
			}
			else if(scanCodeBuffer[i] == 58) //Return
			{
				if(yCharPos == 23)
				{
					drawChar(consoleDisplay[xCharPos][yCharPos]);
					newLine();
					xCharPos = 0;
					drawChar(0x00);
					blinkCursor();
					printf("\r");
				}
				else
				{
					drawChar(consoleDisplay[xCharPos][yCharPos]);
					yCharPos++;
					xCharPos = 0;
					drawChar(consoleDisplay[xCharPos][yCharPos]);
					blinkCursor();
					printf("\r");
				}
			}
			else if(scanCodeBuffer[i] == 69) //Line
			{
				
				if(yCharPos == 23)
				{
					drawChar(consoleDisplay[xCharPos][yCharPos]);
					newLine();
					drawChar(0x00);
					blinkCursor();
					printf("\n");
				}
				else
				{
					drawChar(consoleDisplay[xCharPos][yCharPos]);
					yCharPos++;
					drawChar(consoleDisplay[xCharPos][yCharPos]);
					blinkCursor();
					printf("\n");
				}
			}
			else if(scanCodeBuffer[i] == 66) //Backspace
			{
				drawChar(consoleDisplay[xCharPos][yCharPos]);
				xCharPos--;
				tempCharacter = consoleDisplay[xCharPos][yCharPos];
				drawChar(tempCharacter);
				blinkCursor();
			}
			else
			{
				if(shifted)
				{
					//this line places the key to be printed into the console buffer
					consoleDisplay[xCharPos][yCharPos] = shiftCase[scanCodeBuffer[i]];
					printf("%c",consoleDisplay[xCharPos][yCharPos]);
					//this line _actually prints the character_
					drawChar(shiftCase[scanCodeBuffer[i]]);
					
					//move the cursor one postition forward
					xCharPos++;
					
					//draw the character again, for some reason, idk.
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
					printf("%c",consoleDisplay[xCharPos][yCharPos]);
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
	}*/
