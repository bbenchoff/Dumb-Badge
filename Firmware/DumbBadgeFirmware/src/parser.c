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

static const char csiEscCodes[] = "@ABCDEFGHJKLMPXacdefghlmnqrsu`";
static const char DECIDreturn[] = {0x1B,0x5B,0x3F,0x36,0x63};

uint8_t parserBuffer[10];
int paramBuffer[4];

uint8_t DECSCX = 0;
uint8_t DECSCY = 0;

bool textBold;
bool textUnderscore;
bool textBlink;
bool textReverseVideo;

uint16_t textForeground = 0xFFFF;
uint16_t textBackground = 0x0000;


void parseChar(uint8_t character)
{
		
	parserState state = currentState;
	
	switch(state)
	{
		case stateGround:
			groundState(character);
			break;
		
		case stateESC:
			escState(character);
			break;
		
		case stateESCinter:
			escIntState(character);
			break;
		
		case stateCSIentry:
			CSIentryState(character);
			break;
		
		case stateCSIparam:
			CSIparamState(character);
			break;
		
		case stateCSIignore:
			CSIignoreState(character);
			break;
	}
	
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
		
		
		//set reverse video
		if(textReverseVideo == true)  //If this is reverse Text
		{
			SetBit(consoleSGR[xCharPos][yCharPos],7);
		}
		else
		{
			ClearBit(consoleSGR[xCharPos][yCharPos],7);
		}
		
		//set bold
		if(textBold == true)
		{
			SetBit(consoleSGR[xCharPos][yCharPos],1);
		}
		else
		{
			ClearBit(consoleSGR[xCharPos][yCharPos],1);
		}
		
		//set underscore
		if(textUnderscore == true)
		{
			SetBit(consoleSGR[xCharPos][yCharPos],4);
		}
		else
		{
			ClearBit(consoleSGR[xCharPos][yCharPos],4);
		}
		
		//set blink
		if(textBlink == true)
		{
			SetBit(consoleSGR[xCharPos][yCharPos],5);
		}
		else
		{
			ClearBit(consoleSGR[xCharPos][yCharPos],5);
		}
		
		consoleColors[xCharPos][yCharPos] = (textForeground << 16) | textBackground;
		
		//this line _actually prints the character_
		drawChar(consoleDisplay[xCharPos][yCharPos]);

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
	else if(character == 0x48)		//ESC + H - (HTS) - 
	{
		HTS(); ///not supported now
	}
	else if(character == 0x4D)		//ESC + M - (RI)
	{
		RI();
	}
	else if(character == 0x59)		//ESC + Z (DECID)
	{
		//This returns ESC [ ? 6 c, which is apparently a VT102
		printf("%s",DECIDreturn);
		currentState = stateGround;
	}
	else if(character == 0x63)		//ESC + c - (RIS)
	{
		RIS();
	}
	else if(character == 0x3E)		//ESC >
	{
		//set DECPNM set numeric keypad mode
		currentState = stateGround;
	}
	else if(character == 0x3D)		//ESC =
	{
		//set DECPAM set application keypad mode
		currentState = stateGround;
	}
	else if(character == 0x5D)		//ESC ]
	{
		/*
		this is OSC Operating System Command
		and this is a fucking mess look at Linux man page
		for console_codes I don't know if I have to
		implement this god I hope not
		*/
		currentState = stateGround;
	}
	//# 0x23, % 0x25, ( 0x28, ) 0x29, ] 0x5D
	//I'm doing it this way because fuck it
	else if(character == 0x23 || character == 0x25 || character == 0x28 ||
		character == 0x29 || character == 0x5D)
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
	
	//"@ABCDEFGHJKLMPXacdefghlmnqrsu`";
	if(character == 0x40)		//ESC [ @ ICH insert indicated # of blank chars
	{
		//ICH insert indicated # of blank chars
		ICH();
	}
	else if(character == 0x41)	//ESC [ A	Cursor Up
	{
		CUU();
	}
	else if(character == 0x61)	//ESC [ a HPR
	{
		CUF();
	}
	else if(character == 0x42)	//ESC [ B	Cursor Down
	{
		CUD();
	}
	else if(character == 0x43)	//ESC [ C	Cursor Forward
	{
		CUF();
	}
	else if(character == 0x63)	//ESC [ c DA
	{
		//This returns ESC [ ? 6 c, which is apparently a VT102
		printf("%s",DECIDreturn);
		currentState = stateGround;
	}
	else if(character == 0x44)	//ESC [ D	Cursor Backward
	{
		CUB();
	}
	else if(character == 0x64)	//ESC [ d	VPA
	{
		//moves cursor to the indicated row, current column
		
	}
	else if(character == 0x45)	//ESC [ E	Cursor Next Line
	{
		CNL();
	}
	else if(character == 0x65)	//ESC [ e VPR
	{
		//moves cursor down the indicated number of rows
		CUD();
	}
	else if(character == 0x46)	//ESC [ F	Cursor Preceding Line
	{
		CPL();
	}
	else if(character == 0x66)	//ESC [ f HVP
	{
		//move cursor to indicated row, column.
		CUP();
	}
	else if(character == 0x47)	//ESC [ G	Cursor Horizontal Absolute
	{
		CHA();
	}
	else if(character == 0x67)	//ESC [ g TBC
	{
		//clear tab stop at current position
		currentState = stateGround;
	}
	else if(character == 0x48)	//ESC [ H	Cursor Position
	{
		CUP();
	}
	else if(character == 0x68)	//ESC [ h Set Mode
	{
		//TO DO HOLY SHIT THIS IS A BIG ONE
		SM();
		currentState = stateGround;
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
	else if(character == 0x4C)	//ESC [ L 
	{
		//insert indicated # of blank lines
		//IL()
		currentState = stateGround;
	}
	else if(character == 0x6C)	//ESC [ l	Reset mode
	{
		RM();
		currentState = stateGround;
	}
	else if(character == 0x4D)	//ESC [ M
	{
		//DL
		//Delet indicated number of lines
		currentState = stateGround;
	}
	else if(character == 0x6D)	//ESC [ m	Select Graphic Rendition
	{
		SGR();
	}
	else if(character == 0x6E)	//ESC [ n Device Status Report
	{
		DSR();
	}
	else if(character == 0x50)	//ESC [ P	Delete Character
	{
		DCH();
	}
	else if(character == 0x51)	//ESC [ Q	Select Edit Extent Mode
	{
		SEM();
	}
	else if(character == 0x71)	//ESC [ q	Set Keyboard LEDs
	{
		//<Blink>
		currentState = stateGround;
	}
	else if(character == 0x72)	//ESC [ r	DECSTBM
	{
		/*
		Set top and bottom margins for scroll region
		*/
		DECSTBM();

	}
	else if(character == 0x73)	//ESC [ s	Save Cursor Position
	{
		SC();
	}
	else if(character == 0x75)	//ESC [ u	Restore Cursor Position
	{
		RC();
	}
	else if(character == 0x58)	//ESC [ X
	{
		//Erases indicated number of characters on the current line
		currentState = stateGround;
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
	else if(character == 0x60)	//ESC [ ` HPA
	{
		//move cursor to indicated column in current row
		currentState = stateGround;
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
	else if(character == 0x3F)	//Question '?'; this is a param
	{
		currentState = stateCSIparam;
		CSIparamState(character);
	}
	else if(character == 0x1B)		//ESC, send back to stateESC
	{
		currentState = stateESC;
		
	}
	else if(character == 0x3A)
	{
		currentState = stateCSIignore;
	}
	else
	{
		currentState = stateGround;
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
	else if(character == 0x3F)					//character is '?', this is used for DECCKM
	{											//and basically everything with 'h' as
		enqueueParser('?');						//the terminating character
	}
	else if(isValidCSIEscapeCode(character))		//character matches a supported escape code
	{											
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
		currentState = stateESC;
	}
	else if(character >= 0x40 && character <= 0x7E)
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
	
	//# 0x23, % 0x25, ( 0x28, ) 0x29, ] 0x5D
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
			else
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
			else if(character == 0x42) //B
			{
				//Select default latin-1 mapping
			}
			else if(character == 0x30) //0
			{
				//select VT100 graphics mapping
			}
			else if(character == 0x55) //U
			{
				//select null mapping -- strait to character rom
			}
			else if(character == 0x4B) //K
			{
				//select user mapping
			}
			else
			{
				//do nothing
			}
			break;
		case '%':		//Start sequence selecting character set
			if(character == 0x40) //@
			{
				//Select Latin-1 character set
			}
			else if(character == 0x47) //G
			{
				//select UTF-8 character set
			}
			else if(character == 0x38) //8
			{
				
			}
			else
			{
				
			}
			break;
		case ')':		//Start sequence defining G1 character set
			if(character == 0x42) //B
			{
				//Select default latin-1 mapping
			}
			else if(character == 0x30) //0
			{
				//select VT100 graphics mapping
			}
			else if(character == 0x55) //U
			{
				//select null mapping -- strait to character rom
			}
			else if(character == 0x4B) //K
			{
				//select user mapping
			}
			else
			{
				//do nothing
			}
			break;
	}
	stateEnterBuffer = 0x00;
	currentState = stateGround;
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
	/*
	The RI control moves the active position upward in the display by one 
	line. If the active position is already at the top margin, the display 
	will scroll downward by one line. If the display scrolls, a blank line 
	with all attributes off will appear at the top margin.
	
	If the active position is below the top margin when this control is 
	executed the active position will not move beyond the top margin. If 
	the active position is above the top margin (as the result of absolute 
	cursor positioning) it will still move upward by one line and no 
	scrolling will occur. in this case the active position will not move 
	beyond the first line of the display.
	*/
	char tempCharacter;

	if(yCharPos == topMargin)
	{
		//We have to scroll down because ANSI X3.64-1979 is not a VT-100.
		//so we're writing a scroll down function for console.c
	
		scrollDown(topMargin);
	}
	else
	{
		if(yCharPos > 0)
		{
			drawChar(consoleDisplay[xCharPos][yCharPos]);
			yCharPos--;
			tempCharacter = consoleDisplay[xCharPos][yCharPos];
			drawChar(tempCharacter);
		}
	}
	
	blinkCursor();
	currentState = stateGround;
}

void RIS()
{
	//soft reset of system with ESC + c 
	//this might be sloppy, could replace this with an overflowing WDT
	//but this seems to work so /shrug
	NVIC_SystemReset();
}

void HTS()
{
	//set tab stop at current column, unsupported now
	currentState = stateGround;
}

/************************************************************************/
/*    CSI mnemonic functions                                            */
/************************************************************************/
void CUU() // Cursor Up*
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

void CUD() //Cursor Down *
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

void CUF() //Cursor Forward *
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

void CUB() //Cursor Backward *
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

void CNL() //Cursor Next Line *
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

void CPL() //Cursor Preceding Line *
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

void CHA() //Cursor Horizontal Absolute *
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
		
		if(parameter >= 80) //clamp it to column 79
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

void CUP() //Cursor Position *
{
	unsigned char tempCharacter;
	uint8_t xTemp = 0;
	uint8_t yTemp = 0;
	
	yTemp = dequeueParam();
	xTemp = dequeueParam();
	
	//need to decrement, because display is indexed at 0,0.
	if(yTemp > 0)
		yTemp = yTemp - 1;
		
	if(xTemp > 0)
		xTemp = xTemp - 1;
	
	drawChar(consoleDisplay[xCharPos][yCharPos]);
	
	if(originMode == DISPLACED)
	{
		//this sets the cursor relative to the origin of the current
		//scrolling region.
		if((topMargin + yTemp) <= bottomMargin)
			yCharPos = topMargin + yTemp;
		else
			yCharPos = bottomMargin;
			
		xCharPos = xTemp;
	}
	else
	{
		//This sets the cursor relative to 0,0
		
		if(yTemp <= 24)
			yCharPos = yTemp;
		else
			yCharPos = 24;
			
		if(xTemp <= 80)
			xCharPos = xTemp;
		else
			xCharPos = 80; 
	}

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

void ED() //Edit In Display *
{
	uint8_t parameter;
	
	uint8_t xTemp = xCharPos;
	uint8_t yTemp = yCharPos;
	
	cursorBlinkState = false;  //need to turn the blinking off; ugly kludge
	
	if(isEmptyParam())
	{
		parameter = 2;
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
				consoleSGR[xCharPos][yCharPos] = 0x00;
				consoleColors[xCharPos][yCharPos] = 0xFFFF0000;
				drawChar(0x00);
			}
			//second step, erase the rest of the lines
			for(int j = yTemp+1 ; j < 24 ; j++)
			{
				for(int i = 0 ; i < 80 ; i++)
				{
					xCharPos = i;
					yCharPos = j;
					consoleSGR[xCharPos][yCharPos] = 0x00;
					consoleColors[xCharPos][yCharPos] = 0xFFFF0000;
					drawChar(0x00);
				}
			}
		break;
		
		case 1:			//Erases from beginning of display to cursor
			//first step, erase beginning of current line
			for(int i = 0 ;  i <= xTemp ;  i++)
			{
				xCharPos = i;
				consoleSGR[xCharPos][yCharPos] = 0x00;
				consoleColors[xCharPos][yCharPos] = 0xFFFF0000;
				drawChar(0x00);
			}
			//second step, erase previous lines
			for(int j = 0 ; j < yTemp ; j++)
			{
				for(int i = 0 ; i < 80 ; i++)
				{
					xCharPos = i;
					yCharPos = j;
					consoleSGR[xCharPos][yCharPos] = 0x00;
					consoleColors[xCharPos][yCharPos] = 0xFFFF0000;
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
					consoleSGR[xCharPos][yCharPos] = 0x00;
					consoleColors[xCharPos][yCharPos] = 0xFFFF0000;
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

void EL() //Edit In Line *
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
			for(int i = xTemp ;  i <= 79 ;  i++)
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

void SGR() //Select Graphic Rendition *
{
	
	uint16_t eightBitColor[256] = 
	{
		0x0000,0x8000,0x0400,0x8400,0x0010,0x8010,0x0410,0xC618,0x8410,0xF800,
		0x07E0,0xFFE0,0x001F,0xF81F,0x07FF,0xFFFF,0x0000,0x000B,0x0010,0x0015,
		0x001A,0x001F,0x02E0,0x02EB,0x001D,0x02F5,0x02FA,0x02FF,0x0420,0x042B,
		0x0430,0x0435,0x043A,0x043F,0x0560,0x056B,0x0570,0x0575,0x057A,0x057F,
		0x06A0,0x06AB,0x06B0,0x06B5,0x06BA,0x06BF,0x07E0,0x07EB,0x07F0,0x07F5,
		0x07FA,0x07FF,0x5800,0x580B,0x5810,0x5815,0x581A,0x581F,0x5AE0,0x5AEB,
		0x5AF0,0x5AF5,0x5AFA,0x5AFF,0x5C20,0x5C2B,0x5C30,0x5C35,0x5C3A,0x5C3F,
		0x5D60,0x5D6B,0x5D70,0x5D75,0x5D7A,0x5D7F,0x5EA0,0x5EAB,0x5EB0,0x5EB5,
		0x5EBA,0x5EBF,0x5FE0,0x5FEB,0x5FF0,0x5FF5,0x5FFA,0x5FFF,0x8000,0x800B,
		0x8010,0x8015,0x801A,0x801F,0x82E0,0x82EB,0x82F0,0x82F5,0x82FA,0x82FF,
		0x8420,0x842B,0x8430,0x8435,0x843A,0x843F,0x8560,0x856B,0x8570,0x8575,
		0x857A,0x857F,0x86A0,0x86AB,0x86B0,0x86B5,0x86BA,0x86BF,0x87E0,0x87EB,
		0x87F0,0x87F5,0x87FA,0x87FF,0xA800,0xA80B,0xA810,0xA815,0xA81A,0xA81F,
		0xAAE0,0xAAEB,0xAAF0,0xAAF5,0xAAFA,0xAAFF,0xAC20,0xAC2B,0xAC30,0x0566,
		0xAC3A,0xAC3F,0xAD60,0xAD6B,0xAD70,0xAD75,0xAD7A,0xAD7F,0xAEA0,0xAEAB,
		0xAEB0,0xAEB5,0xAEBA,0xAEBF,0xAFE0,0xAFEB,0xAFF0,0xAFF5,0xAFFA,0xAFFF,
		0xD000,0xD00B,0xD010,0xD015,0xD01A,0xD01F,0xD2E0,0xD2EB,0xD2F0,0xD2F5,
		0xD2FA,0xD2FF,0xD420,0xD42B,0xD430,0xD435,0xD43A,0xD43F,0xD560,0xD56B,
		0xD570,0xD575,0xD57A,0xD57F,0xD6A0,0xD6AB,0xD6B0,0xD6B5,0xD6BA,0xD6BF,
		0xD7E0,0xD7EB,0xD7F0,0xD7F5,0xD7FA,0xD7FF,0xF800,0xF80B,0xF810,0xF815,
		0xF81A,0xF81F,0xFAE0,0xFAEB,0xFAF0,0xFAF5,0xFAFA,0xFAFF,0xFC20,0xFC2B,
		0xFC30,0xFC35,0xFC3A,0xFC3F,0xFD60,0xFD6B,0xFD70,0xFD75,0xFD7A,0xFD7F,
		0xFEA0,0xFEAB,0xFEB0,0xFEB5,0xFEBA,0xFEBF,0xFFE0,0xFFEB,0xFFF0,0xFFF5,
		0xFFFA,0xFFFF,0x0841,0x1082,0x18E3,0x2124,0x3186,0x39C7,0x4228,0x4A69,
		0x5ACB,0x630C,0x632C,0x73AE,0x8410,0x8C51,0x94B2,0x9CF3,0xAD55,0xB596,
		0xBDF7,0xC638,0xD69A,0xDEDB,0xE73C,0xEF7D
	};
	
	uint8_t parameter;	
	cursorBlinkState = false;  //need to turn the blinking off; ugly kludge
	uint8_t r = 0;
	uint8_t g = 0;
	uint8_t b = 0;	
	
	if(isEmptyParam())
	{
		parameter = 0;
		
		textBold = false;
		textUnderscore = false;
		textBlink = false;
		textReverseVideo = false;

		textForeground = defaultForegroundColor;
		textBackground = defaultBackgroundColor;
							
	}
	else
	{
		while(!isEmptyParam())
		{
			parameter = dequeueParam();
			switch(parameter)
			{
				case 0:		// all attributes off
				
					textBold = false;
					textUnderscore = false;
					textBlink = false;
					textReverseVideo = false;

					textForeground = defaultForegroundColor;
					textBackground = defaultBackgroundColor;
					break;
				
				case 1:		// bold on
					textBold = true;
					break;
									
				case 4:		// set underscore
					textUnderscore = true;
					break;
					
				case 5:		//set blink
					textBlink = true;
					break;
					
				case 7:		//set reverse video on
					textReverseVideo = true;
					break;
					
				case 21:	//set underline
					textUnderscore = true;
					break;
					
				case 22:	//bold off
					textBold = false;
					break;
					
				case 24:	//underline off
					textUnderscore = false;
					break;
					
				case 25:	//blink off
					textBlink = false;
					break;
					
				case 27:	//reverse video off
					textReverseVideo = false;
					break;
					
				case 30:	//black foreground
					textForeground = BLACK;
					break;
					
				case 31:	//red foreground
					textForeground = RED;
					break;
					
				case 32:	//green foreground
					textForeground = GREEN;
					break;
					
				case 33:	//brown foreground
					textForeground = BROWN;
					break;
					
				case 34:	//blue foreground
					textForeground = BLUE;
					break;
					
				case 35:	//magenta foreground
					textForeground = MAGENTA;
					break;
					
				case 36:	//cyan foreground
					textForeground = CYAN;
					break;
					
				case 37:	//white
					textForeground = WHITE;
					break;
					
				case 38:	//256/24-bit foreground color
					parameter = dequeueParam();
					if(parameter == 5)	//256 color
					{
						parameter = dequeueParam();
						textForeground = eightBitColor[parameter];
					}
					if(parameter == 2) //RGB color, 3 parameter r/g/b
					{
						r = dequeueParam();
						g = dequeueParam();
						b = dequeueParam();
						
						textForeground = ((r & 0xf8) << 8) | ((g & 0xfc) << 3) | (b >> 3);
					}
					break;
					
				case 39:	//default foreground color (white)
					textForeground = defaultForegroundColor;
					break;
					
				case 40:	//set black background
					textBackground = BLACK;
					break;
				
				case 41:	//set red background
					textBackground = RED;
					break;
					
				case 42:	//green background
					textBackground = GREEN;
					break;
					
				case 43:	//brown background
					textBackground = BROWN;
					break;
					
				case 44:	//blue background
					textBackground = BLUE;
					break;
					
				case 45:	//magenta background
					textBackground = MAGENTA;
					break;
					
				case 46:	//cyan background
					textBackground = CYAN;
					break;
					
				case 47:	//white background
					textBackground = WHITE;
					break;
					
				case 48:	//256/24-bit background color
					parameter = dequeueParam();
					if(parameter == 5)	//256 color
					{
						parameter = dequeueParam();
						textBackground = eightBitColor[parameter];
					}
					if(parameter == 2) //RGB color, 3 parameter r/g/b
					{
						r = dequeueParam();
						g = dequeueParam();
						b = dequeueParam();
						
						textBackground = ((r & 0xf8) << 8) | ((g & 0xfc) << 3) | (b >> 3);				
					}
					break;
					
				case 49:	//default background color (black)
					textBackground = defaultBackgroundColor;
					break;
					
				case 2:		// set half-bright
					textForeground &= 0x7BEF;	// what the fuck?
					textBackground &= 0x7BEF;
					break;
				
			}
		}	
	}
	
	blinkCursor();
	currentState = stateGround;
}


void DCH() //Delete Character
{
	currentState = stateGround;
}
void SEM() //Select Edit Extent Mode
{
	currentState = stateGround;
}
void CTC() //Cursor Tabulation Control
{
	currentState = stateGround;
}
void ECH() //Erase Character
{
	currentState = stateGround;
}
void CBT() //Cursor Backwards Tab
{
	currentState = stateGround;
}
void ICH(void) //Insert indicated # of blank chars
{
	currentState = stateGround;
}
void DSR(void) 
{
	/* DEVICE STATUS REPORT
	
	The Status Report provides the host with operating status of many features
	including Operating status, keyboard language, user-defined keys, and even
	the amount of memory assigned to macro definitions. Most of these are unused
	by Linux console_codes; the only ones supported by Linux are DSR-CPR, or
	cursor position report, and DSR-OS, or operating status.
	
	See the following page for information on unsupported DSRs.
	https://vt100.net/docs/vt510-rm/DSR.html
	
	This state is entered in two ways:
	
	ANSI format:	ESC [ ps n
	DEC format:		ESC [ ? ps n
	
	where ps is a parameter
	
	The following paramaters are supported:
	
	5	Device status report; answer is ESC [ 0 n (terminal OK)
	6	Cursor position report; Answer is ESC [ y ; x R, where x,y is the cursor
	
	This function will support both ANSI and DEC formats
	*/
	unsigned char tempCharacter;
		
	uint8_t xTemp = xCharPos;
	uint8_t yTemp = yCharPos;
	
	char DSROSResponse[] = {0x1b, 0x5b, 0x30, 0x6e};
	
	char stringResponse[10];
	char tempbuffer[5];
		
	cursorBlinkState = false;  //need to turn the blinking off; ugly kludge
		
	tempCharacter = dequeueParser();
	
	if(!isEmptyParam()) //We are in DEC format
	{
		tempCharacter = dequeueParam();  //this now contains either a 5 or 6
	}
	
	switch(tempCharacter){
		case 5:		//this is a DSR, we send Terminal OKAY
			printf("%s",DSROSResponse);
		break;
		
		case 6:		//This is CPR
			strcat(stringResponse,"\x1B");
			strcat(stringResponse,"\x5B");
			strcat(stringResponse,itoa(yTemp,tempbuffer,10));
			strcat(stringResponse,";");
			strcat(stringResponse,itoa(xTemp,tempbuffer,10));
			strcat(stringResponse,"R");
		
			printf("%s",stringResponse);
		break;
	}
	
	stringResponse[0] = '\0';
	tempbuffer[0] = '\0';
		
	blinkCursor();
	xCharPos = xTemp;
	yCharPos = yTemp;
	currentState = stateGround;
}

void DECSTBM(void)
{
	/*
	Set top and bottom margins for scroll region.
	
	DESSTBM control sets the values of the top and bottom margins of the
	scrolling region. The first parameter sets the value of the top margin,
	and the second parameter sets the value of the bottom margin. The default
	settings if either or both parameters are omitted are the boundaries of
	the logical display page; one for the top marting and 24 for the bottom.
	
	Notes: Execution of this control causes the active portion to be set to
	the page origin obeying Origin Mode (DECOM): first column of the first line
	if origin mode is in the reset (absolute) state, top and left margins if
	the origin mode is in the set (displaced) state.
	
	If value specified for the top margin is equal to or greater than the
	value specified for the bottom margin, this control will be ignored.
	
	If the value specified for the bottom margin is greater than the the
	number of lines in the logical display page, this control will be ignored.
	*/
	
	
	cursorBlinkState = false;  //need to turn the blinking off; ugly kludge
	uint8_t topParameter = 0;
	uint8_t bottomParameter = 0;
	uint8_t tempCharacter;
	
	if(isEmptyParam())
	{
		//do nothing, fall through.		
	}
	else
	{
		while(!isEmptyParam())
		{
			topParameter = dequeueParam();
			bottomParameter = dequeueParam();
			
			if(topParameter == 0)
				topParameter = 1;
				
			if(bottomParameter == 0)
				bottomParameter = 24;
			
			if((topParameter < bottomParameter) && (bottomParameter <= 24))
			{
				topMargin = topParameter-1;
				bottomMargin = bottomParameter;
				
				if(originMode == ABSOLUTE)
				{
					drawChar(consoleDisplay[xCharPos][yCharPos]);
					xCharPos = 0;
					yCharPos = 0;
					tempCharacter = consoleDisplay[xCharPos][yCharPos];
					drawChar(tempCharacter);
				}
				else
				{
					drawChar(consoleDisplay[xCharPos][yCharPos]);
					xCharPos = topMargin;
					yCharPos = 0;
					tempCharacter = consoleDisplay[xCharPos][yCharPos];
					drawChar(tempCharacter);					
				}
				
			}
		}
	}
	
	blinkCursor();
	currentState = stateGround;
}

void SM(void)
{
	cursorBlinkState = false;

	uint8_t temp;
	
	if(isEmptyParam())
	{
		//do nothing, fall through.
	}
	else
	{
		temp = dequeueParam();
		
		if((temp == 4) || (temp == 20))  // is ECMA-48 code
		{
			if(temp == 4)
			{
				//DECIM (default off): Set Insert Mode.
			}
			if(temp == 20)
			{
				//	LF/NL (default off): Automatically follow echo 
				//of LF, VT, or FF with CR.
			}
			
		}
		if(temp == (uint8_t)'?')
		{
			temp = dequeueParam();
			
			switch(temp)
			{
				case 1:
					//	DECCKM (default off): When set, the cursor keys send an ESC 0 prefix,
					//rather than ESC [.
					
					break;
					
				case 5:
					//DECSCNM (defualt off): Set reverse video mode.
					//unimplemented, because it's not used.

					break;
				
				case 6:
					//DECOM (defualt ABSOLUTE): When set, cursor addressing
					//is relative to the upper left corner of the scrolling 
					//region.
					originMode = DISPLACED;
					break;
					
				case 7:			
					//DECAWM (default on): Set autowrap on. In this mode, a 
					//graphic character emitted after column 80 forces a 
					//wrap to the beginning of the following line.
					
					break;
					
				case 8:			
					//DECARM (default on): Set keyboard autorepeat on.
				
					break;
					
				case 25:		
					//DECTECM (default on): Make cursor visible
				
					break;
			}
		}
	}
	blinkCursor();
	currentState = stateGround;
}

void RM(void)
{
	cursorBlinkState = false;

	uint8_t temp;
	
	if(isEmptyParam())
	{
		//do nothing, fall through.
	}
	else
	{
		temp = dequeueParam();
		
		if((temp == 4) || (temp == 20))  // is ECMA-48 code
		{
			if(temp == 4)
			{
				//DECIM (default off): Set Insert Mode.
			}
			if(temp == 20)
			{
				//	LF/NL (default off): Automatically follow echo
				//of LF, VT, or FF with CR.
			}
			
		}
		if(temp == (uint8_t)'?')
		{
			temp = dequeueParam();
			
			switch(temp)
			{
				case 1:
				//	DECCKM (default off): When set, the cursor keys send an ESC 0 prefix,
				//rather than ESC [.
				
				break;
				
				case 5:
				//DECSCNM (defualt off): Set reverse video mode.

				break;
				
				case 6:
				//DECOM (defualt ABSOLUTE): When set, cursor addressing
				//is relative to the upper left corner of the scrolling
				//region.
				originMode = ABSOLUTE;
				break;
				
				case 7:
				//DECAWM (default on): Set autowrap on. In this mode, a
				//graphic character emitted after column 80 forces a
				//wrap to the beginning of the following line.
				
				break;
				
				case 8:
				//DECARM (default on): Set keyboard autorepeat on.
				
				break;
				
				case 25:
				//DECTECM (default on): Make cursor visible
				
				break;
			}
		}
	}
	blinkCursor();
	currentState = stateGround;
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
	/*
	what data structures for tabs are most performant and is is big-o of 
	number of column or big-o of number of tabs shut the fuck up
	*/
	
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
