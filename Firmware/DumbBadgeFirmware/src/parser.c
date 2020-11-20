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

void parseChar(uint8_t character)
{
	
	char tempCharacter;
	
	
	if(character == 0x0D)  //Carriage Return  //this returns to xcharpos = 0
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
	else if(character == 0x0A)	//Line Feed
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
	else if(character == 0x08)  //Backspace
	{
		drawChar(consoleDisplay[xCharPos][yCharPos]);
		xCharPos--;
		tempCharacter = consoleDisplay[xCharPos][yCharPos];
		drawChar(tempCharacter);
		blinkCursor();
	}
	else if(character != 0x00)
	{
		//this line places the key to be printed into the console buffer
		consoleDisplay[xCharPos][yCharPos] = character;
		
		//this line _actually prints the character_
		drawChar(character);

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
