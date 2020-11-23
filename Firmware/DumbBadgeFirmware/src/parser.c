/*
 * parser.c
 *
 * Created: 11/19/2020 4:47:05 PM
 *  Author: bench
 */ 

#include <stdint.h>


#include "globals.h"

#include "LCDBus.h"
#include "LCD.h"
#include "keyboard.h"
#include "console.h"
#include "splash.h"
#include "uart.h"
#include "ouroboros.h"
#include "settings.h"
#include "parser.h"

void parseChar(uint8_t character)
{
	
	char tempCharacter;
	

	if(character == 0x00)							//NUL 0x00 DO NOTHING
	{
		
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
		drawChar(consoleDisplay[xCharPos][yCharPos]);
		xCharPos--;
		tempCharacter = consoleDisplay[xCharPos][yCharPos];
		drawChar(tempCharacter);
		blinkCursor();
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
	else if(character == 0x0B)						//VT 0x0B Vertical Tab
	{
		
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
		///Real Shit Happens Here
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
