/*
 * parser.c
 *
 * Created: 11/19/2020 4:47:05 PM
 *  Author: bench
 *
 */ 

#include <stdint.h>
#include <stdio.h>


#include "globals.h"
#include "parserState.h"

#include "LCDBus.h"
#include "LCD.h"
#include "keyboard.h"
#include "console.h"
#include "splash.h"
#include "uart.h"
#include "ouroboros.h"
#include "settings.h"
#include "parser.h"

uint8_t DECSCX = 0;
uint8_t DECSCY = 0;

void parseChar(uint8_t character)
{
	
	parserState state = currentState;
	
	switch(state)
	{
		case stateGround:
		{
			groundState(character);
		}
		break;
		
		case stateESC:
		{
			escState(character);
		}
		break;
		
		case stateESCinter:
		{
			escIntState(character);
		}
		break;
		
		case stateCSIentry:
		{
			CSIentryState(character);
		}
		break;
		
		case stateCSIparam:
		{
			
		}
		break;
		
		case stateCSIinter:
		{
			
		}
		break;
		
		case stateCSIignore:
		{
			
		}
		break;
	}
	
}

void escState(uint8_t character)
{
	char tempCharacter;
	int xTemp = 0;
	
	if(character == 0x44)		//ESC + D - (IND) - 
	{
		//Moves cursor down one line in column
		//performs newline() if row = 24
		if(yCharPos < 23)
		{
			drawChar(consoleDisplay[xCharPos][yCharPos]);
			yCharPos++;
			tempCharacter = consoleDisplay[xCharPos][yCharPos];
			drawChar(tempCharacter);
			blinkCursor();
		}
		else
		{	
			xTemp = xCharPos;
			drawChar(consoleDisplay[xCharPos][yCharPos]);
			newLine();
			drawChar(0x00);
			xCharPos = xTemp;
			blinkCursor();
		}
		
		currentState = stateGround;	
			
	}
	else if(character == 0x45)		//ESC + E - (NEL) -
	{
		//new line, moves down one line and to the
		//first column (CR,LF) scrolls if row = 24
		if(yCharPos < 23)
		{
			drawChar(consoleDisplay[xCharPos][yCharPos]);
			yCharPos++;
			xCharPos = 0;
			tempCharacter = consoleDisplay[xCharPos][yCharPos];
			drawChar(tempCharacter);
			blinkCursor();

		}
		else
		{
			drawChar(consoleDisplay[xCharPos][yCharPos]);
			newLine();
			drawChar(0x00);
			xCharPos = 0;
			blinkCursor();
		}	
		
		currentState = stateGround;	
		
	}
	else if(character == 0x37)		//ESC + 7 - (DECSC) -
	{
		//Save cursor position
		DECSCX = xCharPos;
		DECSCY = yCharPos;
		currentState = stateGround;
	} 
	else if(character == 0x38)		//ESC + 8 - (DECRC) -
	{
		//Restore cursor to saved position
		drawChar(consoleDisplay[xCharPos][yCharPos]);
		xCharPos = DECSCX;
		yCharPos = DECSCY;
		tempCharacter = consoleDisplay[xCharPos][yCharPos];
		drawChar(tempCharacter);
		blinkCursor();
		currentState = stateGround;
	}
	else if(character == 0x23 || character == 0x28)
	{
		stateEnterBuffer = character;
		currentState = stateESCinter;
	}
	else if(character == 0x5B)
	{
		currentState = stateCSIentry;
	}
	else
	{
		currentState = stateGround;
	}
}

void CSIentryState(uint8_t character)
{
	
}

void escIntState(uint8_t character)
{
	/*
	ESC Intermediate is entered when an intermediate character arrives in an
	escape sequence; there are no paramaters, and the contro function is 
	determined by the intermediate and final characters.
	
	In effect, this state is for double-height lines, double width lines,
	different character sets, and so forth. the majority of VT100 ESC_INT
	escape codes leading in with '#' are not implemented. Codes leading in with
	'(' are implemented, because this will determine the character set (e.x.
	Code Page 347, katakana, ISO/IEC 8859-1).
	
	This state should probably just be part of the ESCAPE state, but whatever
	I'm writing it now.
	*/
		
	if(character == 0x1B)
	{
		currentState = stateGround;
	}
	
	switch(stateEnterBuffer)
	{
		case '#':
			if(character == 0x30) //'0'		
			{
				//do nothing
			}
			else if(character == 0x31) //'1'
			{
				//do nothing
			}
			else if(character == 0x32) //'2'
			{
				//do nothing
			}
			else if(character == 0x33) //'3'
			{
				//do nothing
				//should be double height line, top
			}
			else if(character == 0x34) //'4'
			{
				//do nothing
				//should be double height line, bottom
			}
			else if(character == 0x35) //'5'
			{
				//do nothing
				//should single width line
			}
			else if(character == 0x36) //'6'
			{
				//do nothing
				//should be double width line
			}
			else if(character == 0x37) //'7'
			{
				//do nothing
				//should bve make a hardcopy of screen, not imp
			}
			else if(character == 0x38) //'8'
			{
				//do nothing
				//alignment display, fill screen with 'E'
				//but this is an LCD, so fuck it
			}
			else if(character == 0x39) //'9'
			{
				//do nothing
			}
			break;
		case '(':
			if(character == 0x30) //'0'		
			{
				//Code Page 437
			}
			else if(character == 0x31) //'1'
			{
				//ISO/IEC8859-2
			}
			else if(character == 0x32) //'2'
			{
				//Katakana?
			}
			else if(character == 0x33) //'3'
			{
				//Windows-1252
			}
			else if(character == 0x34) //'4'
			{
				//do nothing
			}
			else if(character == 0x35) //'5'
			{
				//do nothing
			}
			else if(character == 0x36) //'6'
			{
				//do nothing
			}
			else if(character == 0x37) //'7'
			{
				//do nothing
			}
			else if(character == 0x38) //'8'
			{
				//do nothing
			}
			else if(character == 0x39) //'9'
			{
				//do nothing
			}
			break;
	}
	stateEnterBuffer = 0x00;
	currentState = stateGround;
	
}

void groundState(uint8_t character)
{
	char tempCharacter;

	if(character == 0x00)							//NUL 0x00 DO NOTHING
	{
		//always ignore
	}
	else if(character == 0x01)						//SOH 0x01 Start of Heading
	{
		
	}
	else if(character == 0x02)						//STX 0x02 Start of Text
	{
		
	}
	else if(character == 0x03)						//ETX 0x03 End of text
	{
		
	}
	else if(character == 0x04)						//EOT 0x04 End of Transmission
	{
		
	}
	else if(character == 0x05)						//ENQ 0x05 Enquiry
	{
		
	}
	else if(character == 0x06)						//ACK 0x06 Acknowledge
	{
		
	}
	else if(character == 0x07)						//BEL 0x07 Bell
	{
		//Beep
	}
	else if(character == 0x08)						//BS 0x08 Backspace
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
	else if(character == 0x09)						//TAB 0x09 Horizontal Tab
	{
		drawChar(consoleDisplay[xCharPos][yCharPos]);
		if(xCharPos <= 79)
		{
			xCharPos = nextTab(xCharPos);
		}
		drawChar(consoleDisplay[xCharPos][yCharPos]);
		blinkCursor();
	}
	else if(character == 0x0A)						//LF 0x0A Line Feed
	{
		if(yCharPos == 23)
		{
			drawChar(consoleDisplay[xCharPos][yCharPos]);
			newLine();
			//drawChar(consoleDisplay[xCharPos][yCharPos]);
			//drawChar(0x00);
			blinkCursor();
		}
		else
		{
			drawChar(consoleDisplay[xCharPos][yCharPos]);
			yCharPos++;
			drawChar(consoleDisplay[xCharPos][yCharPos]);
			blinkCursor();
		}
		if(lineFeed)
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
	}
	else if(character == 0x0B)						//VT 0x0B Vertical Tab
	{
		if(yCharPos == 23)
		{
			drawChar(consoleDisplay[xCharPos][yCharPos]);
			newLine();
			//drawChar(consoleDisplay[xCharPos][yCharPos]);
			
			//drawChar(0x00);
			blinkCursor();
		}
		else
		{
			drawChar(consoleDisplay[xCharPos][yCharPos]);
			yCharPos++;
			drawChar(consoleDisplay[xCharPos][yCharPos]);
			blinkCursor();
		}
		if(lineFeed)
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
	}
	else if(character == 0x0C)						//FF 0x0C Form Feed
	{
		
	}
	else if(character == 0x0D)						//CR 0x0D Carriage Return
	{
		if(yCharPos == 23)
		{
			drawChar(consoleDisplay[xCharPos][yCharPos]);
			xCharPos = 0;
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
	else if(character == 0x0E)						//SO 0x0E Shift Out
	{
		
	}
	else if(character == 0x0F)						//SI 0x0F Shift In
	{
		
	}
	else if(character == 0x10)						//DLE 0x10 Data Link Escape
	{
		
	}
	else if(character == 0x11)						//DC1 0x11 Data Control 1
	{
		
	}
	else if(character == 0x12)						//DC2 0x12 Data Control 2
	{
		
	}
	else if(character == 0x13)						//DC3 0x13 Data Control 3
	{
		
	}
	else if(character == 0x14)						//DC4 0x14 Data Control 4
	{
		
	}
	else if(character == 0x15)						//NAK 0x15 Negative Acknowledge
	{
		
	}
	else if(character == 0x16)						//SYN 0x16 Synchronous Idle
	{
		
	}
	else if(character == 0x17)						//ETB 0x17 End of Transmission Block
	{
		
	}
	else if(character == 0x18)						//CAN 0x18 Cancel
	{
		
	}
	else if(character == 0x19)						//EM 0x19 End of Medium
	{
		
	}
	else if(character == 0x1A)						//SUB 0x1A Substitution
	{
		
	}
	else if(character == 0x1B)						//ESC 0x1B Escape
	{
		currentState = stateESC;
	}
	else if(character == 0x1C)						//FS 0x1C File Separator
	{
		
	}
	else if(character == 0x1D)						//GS 0x1D Group Separator
	{
		
	}
	else if(character == 0x1E)						//RS 0x1E Record Separator
	{
		
	}
	else if(character == 0x1F)						//US 0x1F Unit Separator
	{
		
	}
	else if(character == 0x7F)						//DEL 0x7F Delete
	{
		///Ignored by terminal
	}
	else
	{
		//this line places the key to be printed into the console buffer
		consoleDisplay[xCharPos][yCharPos] = character;
		
		//this line _actually prints the character_
		drawChar(character);

		//move the cursor one position forward
		xCharPos++;

		//draw the character again, for some reason, idk.
		drawChar(consoleDisplay[xCharPos][yCharPos]);
		
		if(xCharPos > 79)		//END OF LINE
		{
			xCharPos--;
		}
	}
}

int nextTab(int a) 
{
	int tabArray[] =
		{
		 8 ,8 ,8 ,8 ,8 ,8 ,8 ,8 ,
		 16,16,16,16,16,16,16,16,
		 24,24,24,24,24,24,24,24,
		 32,32,32,32,32,32,32,32,
		 40,40,40,40,40,40,40,40,
		 48,48,48,48,48,48,48,48,
		 56,56,56,56,56,56,56,56,
		 64,64,64,64,64,64,64,64,
		 72,72,72,72,72,72,72,72,
		 79,79,79,79,79,79,79,79
		};
	
	return tabArray[a];
}
