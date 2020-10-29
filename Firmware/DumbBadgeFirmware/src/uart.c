/*
 * uart.c
 *
 * Created: 10/16/2020 3:18:32 PM
 *  Author: bench
 */ 

#include <asf.h>
#include <string.h>

#include "globals.h"

#include "LCDBus.h"
#include "LCD.h"
#include "keyboard.h"
#include "console.h"
#include "splash.h"
#include "uart.h"
#include "ouroboros.h"

char rx_buf;
char tempCharacter;
uint8_t characterFromRingBuffer;

cbuf_handle_t cbuf;	

void parseRXBuffer(void)
{
		//circular_buf_get(cbuf, &characterFromRingBuffer);
		
			if(characterFromRingBuffer == 0x0D)  //Carriage Return  //this returns to xcharpos = 0
			{
				if(yCharPos == 23)
				{
					drawChar(consoleDisplay[xCharPos][yCharPos]);
					xCharPos = 0;
					drawChar(0x00);
					blinkCursor();
				}
				else
				{
					drawChar(consoleDisplay[xCharPos][yCharPos]);
					xCharPos = 0;
					drawChar(consoleDisplay[xCharPos][yCharPos]);
					blinkCursor();
				}
			}
			else if(characterFromRingBuffer == 0x0A)	//Line Feed
			{
				if(yCharPos == 23)
				{
					drawChar(consoleDisplay[xCharPos][yCharPos]);
					newLine();
					drawChar(0x00);
					blinkCursor();
				}
				else
				{
					drawChar(consoleDisplay[xCharPos][yCharPos]);
					yCharPos++;
					drawChar(consoleDisplay[xCharPos][yCharPos]);
					blinkCursor();
				}
			}
			else if(characterFromRingBuffer == 0x08)  //Backspace
			{
				drawChar(consoleDisplay[xCharPos][yCharPos]);
				xCharPos--;
				tempCharacter = consoleDisplay[xCharPos][yCharPos];
				drawChar(tempCharacter);
				blinkCursor();
			}
			else if(characterFromRingBuffer != 0x00)
			{
				//this line places the key to be printed into the console buffer
				consoleDisplay[xCharPos][yCharPos] = rx_buf;
				
				//this line _actually prints the character_
				drawChar(characterFromRingBuffer);

				//move the cursor one postition forward
				xCharPos++;

				//draw the character again, for some reason, idk.
				drawChar(consoleDisplay[xCharPos][yCharPos]);
				
				if(xCharPos > 79)		//END OF LINE
				{
					xCharPos--;
				}
			}
}

void clearRXBuffer(void)
{

	rx_buf = 0x00;

}
