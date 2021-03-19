/*
 * parser.c
 *
 * Created: 11/19/2020 4:47:05 PM
 *  Author: bench
 *
 */ 

#include <stdint.h>
#include <stdio.h>

#include <stdlib.h>
#include <string.h>

#include <stddef.h>
#include <stdbool.h>
#include <assert.h>
#include <asf.h>


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
#include "overflow.h"

static const char csiEscCodes[] = "ABCDEFGHIJKmPQrsWXZ";

uint8_t parserBuffer[10];
int paramBuffer[4];

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
			CSIparamState(character);
		}
		break;
		
		case stateCSIignore:
		{
			CSIignoreState(character);
		}
		break;
	}
	
}

void escState(uint8_t character)
{
	if(character == 0x37)		//ESC + 7 - (DECSC) -
	{
		SC();
	}
	else if(character == 0x38)		//ESC + 8 - (DECRC) -
	{
		RC();
	}
	else if(character == 0x44)		//ESC + D - (IND) - 
	{
		IND();			
	}
	else if(character == 0x45)		//ESC + E - (NEL) -
	{
		NEL();
	}
	else if(character == 0x4D)		//ESC + M - (RI)
	{
		RI();
	}
	else if(character == 0x63)		//ESC + c - (RIS)
	{
		RIS();
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
	
	if(character == 0x41)		//ESC [ A	Cursor Up
	{
		CUU();
	}
	else if(character == 0x42)	//ESC [ B	Cursor Down
	{
		CUD();
	}
	else if(character == 0x43)	//ESC [ C	Cursor Forward
	{
		CUF();
	}
	else if(character == 0x44)	//ESC [ D	Cursor Backward
	{
		CUB();
	}
	else if(character == 0x45)	//ESC [ E	Cursor Next Line
	{
		CNL();
	}
	else if(character == 0x46)	//ESC [ F	Cursor Preceding Line
	{
		CPL();
	}
	else if(character == 0x47)	//ESC [ G	Cursor Horizontal Absolute
	{
		CHA();
	}
	else if(character == 0x48)	//ESC [ H	Cursor Position
	{
		CUP();
	}
	else if(character == 0x49)	//ESC [ I	Cursor Horizontal Tab
	{
		CHT();
	}
	else if(character == 0x4A)	//ESC [ J	Erase In Display
	{
		ED();
	}
	else if(character == 0x4B)	//ESC [ K	Erase In Line
	{
		EL();
	}
	else if(character == 0x6D)	//ESC [ m	Select Graphic Rendition
	{
		SGR();
	}
	else if(character == 0x50)	//ESC [ P	Delete Character
	{
		DCH();
	}
	else if(character == 0x51)	//ESC [ Q	Select Edit Extent Mode
	{
		SEM();
	}
	else if(character == 0x72)	//ESC [ r	Restore Cursor Position
	{
		RC();
	}
	else if(character == 0x73)	//ESC [ s	Save Cursor Position
	{
		SC();
	}
	else if(character == 0x57)	//ESC [ W	Cursor Tabulation Control
	{
		CTC();
	}
	else if(character == 0x58)	//ESC [ X	Erase Character
	{
		ECH();
	}
	else if(character == 0x5A)	//ESC [ Z	Cursor Backwards Tab
	{
		CBT();	
	}
	else if(character >= 0x30 && character <= 0x39) // if the character is a digit 0-9
	{
		currentState = stateCSIparam;
		CSIparamState(character);
	}
	else if(character == 0x3B)	//Semicolon ; parameter deliminator
	{
		currentState = stateCSIparam;
		CSIparamState(character);
	}
	else if(character == 0x1B)
	{
		currentState = stateGround;
		
	}
	else if(character == 0x3A)
	{
		currentState = stateCSIignore;
	}
	else
	{
		currentState = stateCSIignore;
	}

}

void CSIparamState(uint8_t character)
{
	/*alright this is where it gets real, bucko.
	
	An incoming character may be digit 0-9, characters
	{ABCDEFGHIJKmPQWXZ}, or character ';'.
	If not, we go to state GROUND.
	
	The parser enters the CSI state with an empty parambuffer
	and parserbuffer. When a parameter is added, it goes into the
	parserbuffer. parambuffer and parserbuffer are implemented as queues,
	having the type char for parserbuffer and the type int for parambuffer.
	
	if a ';' is received, the items in the parserbuffer are concatenated
	and atoi()'d, then stuffed into the parambuffer. incoming digits 0x30-39
	are then also added to the parserbuffer
	
	when a character used for an escape code is seen incoming, we jump to
	*that*, then deal with the concatenation and options of each individual
	escape code.
	
	This is probably way harder than it sounds in my head.*/
	
	if(character >= 0x30 && character <= 0x39)		//character is a digit, put it in the buffer
	{
		enqueueParser(character);
	}
	else if(character == 0x3B)					//character is ';', now we take items out of 
	{											//the parserbuffer and concatenate them into
		enqueueParser(';');						//parambuffer 			
	}
	else if(isValidCSIEscapeCode(character))		//character matches a supported escape code
	{												//here, "ABCDEFGHIJKmPQWXZ"
		queueTransmogrifier();											
		currentState = stateCSIentry;
		CSIentryState(character);
	}
	else
	{
		currentState = stateCSIignore;
	}
}

void CSIignoreState(uint8_t character)
{
	if(character == 0x1B)
	{
		currentState = stateGround;
	}
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
	clearQueues();									//parser and paramQueues cleared

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

/************************************************************************/
/*    ESC mnemonic functions                                            */
/************************************************************************/

void SC()
{
	//Save cursor position
	DECSCX = xCharPos;
	DECSCY = yCharPos;
	currentState = stateGround;
}

void RC()
{
	//Restore cursor to saved position
	
	char tempCharacter;
	
	drawChar(consoleDisplay[xCharPos][yCharPos]);
	xCharPos = DECSCX;
	yCharPos = DECSCY;
	tempCharacter = consoleDisplay[xCharPos][yCharPos];
	drawChar(tempCharacter);
	blinkCursor();
	currentState = stateGround;
}

void IND()
{
	//Moves cursor down one line in column
	//performs newline() if row = 24
	
	char tempCharacter;
	int xTemp = 0;
	
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

void NEL()
{
	//new line, moves down one line and to the
	//first column (CR,LF) scrolls if row = 24
	
	char tempCharacter;
	
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

void RI()
{
	//Reverse Index
	//Moves the cursor to the same horizontal position on the preceding line
	
	char tempCharacter;
	
	if(yCharPos == 0)
	{
		//do nothing, scrolling the screen 'reverse' is not mentioned in
		//ANSI X3.64-1979
	}
	else
	{
		drawChar(consoleDisplay[xCharPos][yCharPos]);
		yCharPos--;
		tempCharacter = consoleDisplay[xCharPos][yCharPos];
		drawChar(tempCharacter);
		blinkCursor();
	}
	currentState = stateGround;
}

void RIS()
{
	//soft reset of system with ESC + c 
	//this might be sloppy, could replace this with an overflowing WDT
	//but this seems to work so /shrug
	NVIC_SystemReset();
}

/************************************************************************/
/*    CSI mnemonic functions                                            */
/************************************************************************/
void CUU() // Cursor Up
{
	unsigned char tempCharacter;
	uint8_t parameter = 0;
	
	if(isEmptyParam())
	{
		parameter = 1;
	}
	else
	{
		parameter = dequeueParam();
		
		if(parameter == 0)
		{
			parameter = 1;
		}
	}
	
	if((yCharPos - parameter) >= 0 && (yCharPos - parameter) <= 24)
	{
		drawChar(consoleDisplay[xCharPos][yCharPos]);
		yCharPos = yCharPos - parameter;
		tempCharacter = consoleDisplay[xCharPos][yCharPos];
		drawChar(tempCharacter);
	}
	else
	{
		drawChar(consoleDisplay[xCharPos][yCharPos]);
		yCharPos = 0;
		tempCharacter = consoleDisplay[xCharPos][yCharPos];
		drawChar(tempCharacter);
	}
	
	blinkCursor();
	currentState = stateGround;
}
void CUD() //Cursor Down
{
	unsigned char tempCharacter;
	uint8_t parameter = 0;
	
	if(isEmptyParam())
	{
		parameter = 1;
	}
	else
	{
		parameter = dequeueParam();
		
		if(parameter == 0)
		{
			parameter = 1;
		}
	}
	if((yCharPos + parameter) <= 23)
	{
		drawChar(consoleDisplay[xCharPos][yCharPos]);
		yCharPos = yCharPos + parameter;
		tempCharacter = consoleDisplay[xCharPos][yCharPos];
		drawChar(tempCharacter);
	}
	else
	{
		drawChar(consoleDisplay[xCharPos][yCharPos]);
		yCharPos = 23;
		tempCharacter = consoleDisplay[xCharPos][yCharPos];
		drawChar(tempCharacter);
	}

	blinkCursor();
	currentState = stateGround;
}
void CUF() //Cursor Forward
{
	unsigned char tempCharacter;
	uint8_t parameter = 0;
	
	if(isEmptyParam())
	{
		parameter = 1;
	}
	else
	{
		parameter = dequeueParam();
		
		if(parameter == 0)
		{
			parameter = 1;
		}
	}
	
	if(xCharPos + parameter <= 79)
	{
		drawChar(consoleDisplay[xCharPos][yCharPos]);
		xCharPos = xCharPos + parameter;
		tempCharacter = consoleDisplay[xCharPos][yCharPos];
		drawChar(tempCharacter);
	}
	else
	{
		drawChar(consoleDisplay[xCharPos][yCharPos]);
		xCharPos = 79;
		tempCharacter = consoleDisplay[xCharPos][yCharPos];
		drawChar(tempCharacter);	
	}
	blinkCursor();
	currentState = stateGround;
}
void CUB() //Cursor Backward
{
	unsigned char tempCharacter;
	uint8_t parameter = 0;
	
	if(isEmptyParam())
	{
		parameter = 1;
	}
	else
	{
		parameter = dequeueParam();
		
		if(parameter == 0)
		{
			parameter = 1;
		}
	}
	
	if(xCharPos - parameter >= 0)
	{
		drawChar(consoleDisplay[xCharPos][yCharPos]);
		xCharPos = xCharPos - parameter;
		tempCharacter = consoleDisplay[xCharPos][yCharPos];
		drawChar(tempCharacter);
	}
	else
	{
		drawChar(consoleDisplay[xCharPos][yCharPos]);
		xCharPos = 0;
		tempCharacter = consoleDisplay[xCharPos][yCharPos];
		drawChar(tempCharacter);
	}
	blinkCursor();
	currentState = stateGround;
}
void CNL() //Cursor Next Line
{
	unsigned char tempCharacter;
	uint8_t parameter = 0;
	
	if(isEmptyParam())
	{
		parameter = 1;
	}
	else
	{
		parameter = dequeueParam();
		
		if(parameter == 0)
		{
			parameter = 1;
		}
	}
	
	xCharPos = 0;
	
	if((yCharPos + parameter) <= 23)
	{
		drawChar(consoleDisplay[xCharPos][yCharPos]);
		yCharPos = yCharPos + parameter;
		tempCharacter = consoleDisplay[xCharPos][yCharPos];
		drawChar(tempCharacter);
	}
	else
	{
		drawChar(consoleDisplay[xCharPos][yCharPos]);
		yCharPos = 23;
		tempCharacter = consoleDisplay[xCharPos][yCharPos];
		drawChar(tempCharacter);
	}

	blinkCursor();
	currentState = stateGround;	
}
void CPL() //Cursor Preceding Line
{
	unsigned char tempCharacter;
	uint8_t parameter = 0;
	
	if(isEmptyParam())
	{
		parameter = 1;
	}
	else
	{
		parameter = dequeueParam();
		
		if(parameter == 0)
		{
			parameter = 1;
		}
	}
	
	xCharPos = 0;
	
	if((yCharPos - parameter) >= 0 && (yCharPos - parameter) <= 24)
	{
		drawChar(consoleDisplay[xCharPos][yCharPos]);
		yCharPos = yCharPos - parameter;
		tempCharacter = consoleDisplay[xCharPos][yCharPos];
		drawChar(tempCharacter);
	}
	else
	{
		drawChar(consoleDisplay[xCharPos][yCharPos]);
		yCharPos = 0;
		tempCharacter = consoleDisplay[xCharPos][yCharPos];
		drawChar(tempCharacter);
	}
	
	blinkCursor();
	currentState = stateGround;
	
}
void CHA() //Cursor Horizontal Absolute
{
	unsigned char tempCharacter;
	uint8_t parameter = 0;
	
	if(isEmptyParam())
	{
		parameter = 1;
	}
	else
	{
		parameter = dequeueParam();
		
		if(parameter > 0)
		{
			parameter--;  //need to decrement, because display is indexed at 0,0.
		}
		
		if(parameter >= 80)
		{
			parameter = 79;
		}
	}
	
	drawChar(consoleDisplay[xCharPos][yCharPos]);
	xCharPos = parameter;
	tempCharacter = consoleDisplay[xCharPos][yCharPos];
	drawChar(tempCharacter);
	
	blinkCursor();
	currentState = stateGround;
}
void CUP() //Cursor Position
{
	unsigned char tempCharacter;
	uint8_t parameter = 0;
	uint8_t xTemp = 0;
	uint8_t yTemp = 0;
	
	if(isEmptyParam())
	{
		parameter = 0;
	}
	else
	{
		parameter = dequeueParam();
		
		if(parameter > 0)
		{
			parameter--;  //need to decrement, because display is indexed at 0,0.
		}
		
		if(parameter >= 80)
		{
			parameter = 79;
		}
	}
	
	xTemp = parameter;

	if(isEmptyParam())
	{
		parameter = 0;
	}
	else
	{
		parameter = dequeueParam();
		
		if(parameter > 0)
		{
			parameter--;  //need to decrement, because display is indexed at 0,0.
		}
		
		if(parameter >= 24)
		{
			parameter = 23;
		}
	}
	
	yTemp = parameter;
	
	drawChar(consoleDisplay[xCharPos][yCharPos]);
	xCharPos = xTemp;
	yCharPos = yTemp;
	tempCharacter = consoleDisplay[xCharPos][yCharPos];
	drawChar(tempCharacter);
	
	blinkCursor();
	currentState = stateGround;
}
void CHT() //Cursor Horizontal Tab
{
	//do this later
	currentState = stateGround;
}
void ED() //Edit In Display
{
	uint8_t parameter;
	
	uint8_t xTemp = xCharPos;
	uint8_t yTemp = yCharPos;
	
	cursorBlinkState = false;  //need to turn the blinking off; ugly kludge
	
	if(isEmptyParam())
	{
		parameter = 0;
	}
	else
	{
		parameter = dequeueParam();
	}
		
	switch(parameter)
	{
		case 0:			//Erases from cursor to end of display
			//first step, erase rest of current line
			for(int i = xTemp ;  i <= 78 ;  i++)
			{
				xCharPos = i;
				drawChar(0x00);
			}
			//second step, erase the rest of the lines
			for(int j = yTemp+1 ; j < 24 ; j++)
			{
				for(int i = 0 ; i < 80 ; i++)
				{
					xCharPos = i;
					yCharPos = j;
					drawChar(0x00);
				}
			}
		break;
		
		case 1:			//Erases from beginning of display to cursor
			//first step, erase beginning of current line
			for(int i = 0 ;  i <= xTemp ;  i++)
			{
				xCharPos = i;
				drawChar(0x00);
			}
			//second step, erase previous lines
			for(int j = 0 ; j < yTemp ; j++)
			{
				for(int i = 0 ; i < 80 ; i++)
				{
					xCharPos = i;
					yCharPos = j;
					drawChar(0x00);
				}
			}
		break;
		
		case 2:			//Erases entire display
			for(int j = 0 ; j < 24 ; j++)
			{
				for(int i = 0 ; i < 80 ; i++)
				{
					xCharPos = i;
					yCharPos = j;
					drawChar(0x00);
				}
			}
		break;
	}
	
	blinkCursor();
	xCharPos = xTemp;
	yCharPos = yTemp;
	drawChar(0x00);
	
	currentState = stateGround;	


}
void EL() //Edit In Line
{
	unsigned char tempCharacter;
	uint8_t parameter;
	
	uint8_t xTemp = xCharPos;
	uint8_t yTemp = yCharPos;
	
	cursorBlinkState = false;  //need to turn the blinking off; ugly kludge
	
	if(isEmptyParam())
	{
		parameter = 0;
	}
	else
	{
		parameter = dequeueParam();
	}
	
	tempCharacter = consoleDisplay[xCharPos][yCharPos];
	
	switch(parameter)
	{
		case 0:			//Erases from cursor to end of line
			for(int i = xTemp ;  i <= 78 ;  i++)
			{
				xCharPos = i;
				drawChar(0x00);
			}
		break;
		
		case 1:			//Erases from beginning of line to cursor
			for(int i = 0 ;  i <= xTemp+1 ;  i++)
			{
				xCharPos = i;
				drawChar(0x00);
			}
		break;
		
		case 2:			//Erases entire line containing cursor
			for(int i = 0 ;  i <= 78 ;  i++)
			{
				xCharPos = i;
				drawChar(0x00);
			}
		break;
	}
	
	blinkCursor();
	xCharPos = xTemp;
	yCharPos = yTemp;
	drawChar(tempCharacter);
	
	currentState = stateGround;	
}
void SGR() //Select Graphic Rendition
{
	
}
void DCH() //Delete Character
{
	
}
void SEM() //Select Edit Extent Mode
{
	
}
void CTC() //Cursor Tabulation Control
{
	
}
void ECH() //Erase Character
{
	
}
void CBT() //Cursor Backwards Tab
{
	
}

bool isValidCSIEscapeCode(uint8_t character)
{
	
	for(uint8_t i = 0; i <= sizeof(csiEscCodes)/sizeof(csiEscCodes[0]) ; i++)
	{
		if(character == csiEscCodes[i])
		{
			return true;	
		}
	}
	return false;
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
