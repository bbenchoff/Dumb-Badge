/*
 * splash.c
 *
 * Created: 6/29/2020 5:40:19 PM
 *  Author: bench
 */ 

#include <asf.h>
#include <string.h>

#include "globals.h"
#include "splash.h"
#include "LCD.h"
#include "console.h"


/***********drawKare ** It's the boot graphic*************************/
//	drawKare(int emotion) is the boot animation displayed on startup
//	this displays an 'emotion':
//	emotion = 0:	a 'happy terminal'; normal mode
//	emotion = 1:	a lowercase pi, for using an SBC as the
//					endpoint of the serial (non USB) serial port.
//	emotion = 2:	the 'sad terminal'; idk, macs had a 'sad mac'.
//
//	yes, this is full of magic numbers but this will be the only
//	graphic in the entire project. Please note this is the most
//	space efficient way to do this; a 40x31 bitmap is 930 bytes,
//	whereas	this is (104*2)+28+20, or 256 bytes.
/*********************************************************************/
void drawKare(int emotion)
{
	uint16_t body[104] = {10,10,20,20,20,0,380,10,380,10,390,20,0,
		20,10,290,390,20,400,290,10,290,20,300,380,290,390,300,20,
		300,380,310,0,30,50,40,0,50,50,60,80,30,280,40,70,40,80,190,
		80,190,280,200,280,40,290,190,0,70,50,80,0,90,50,100,0,110,
		50,120,0,130,50,140,0,150,50,160,0,170,50,180,0,190,50,200,
		300,200,370,210,30,220,370,230,30,240,370,250,30,260,370,
		270,90,280,300,290};
	
	uint8_t happyTerm[28] = {180,80,190,130,170,130,190,140,140,
		60,150,100,210,60,220,100,130,150,140,160,140,160,220,170,
	220,150,230,160};
	
	uint8_t rPiBeret[20] = {120,60,240,80,110,70,120,90,150,
	60,170,170,200,60,220,160,210,160,230,170};

	int offsetGraphicX = 300;
	int offsetGraphicY = 150;
	int iSv = 2;				//an inverse scale factor

	
	
	for(int i = 0; i < 104; i = i+4)
	{
		fillRect(((body[i]/iSv)+(offsetGraphicX)),
		((body[i+1]/iSv)+(offsetGraphicY)),
		((body[i+2]/iSv)+(offsetGraphicX)),
		((body[i+3]/iSv)+(offsetGraphicY)));
	}
	switch(emotion)
	{
		case 0: //happy term
		for(int i = 0; i < 28; i = i+4)
		{
			fillRect(((happyTerm[i]/iSv)+(offsetGraphicX)),
			((happyTerm[i+1]/iSv)+(offsetGraphicY)),
			((happyTerm[i+2]/iSv)+(offsetGraphicX)),
			((happyTerm[i+3]/iSv)+(offsetGraphicY)));
		}
		break;
		case 1: //pi face
		for(int i = 0; i < 20; i = i+4)
		{
			fillRect((
			(rPiBeret[i]/iSv)+(offsetGraphicX)),
			((rPiBeret[i+1]/iSv)+(offsetGraphicY)),
			((rPiBeret[i+2]/iSv)+(offsetGraphicX)),
			((rPiBeret[i+3]/iSv)+(offsetGraphicY)));
		}
		break;
		case 2:
		//make a sad terminal thing go here
		break;
	}
}

void splashScreen(void)
{
	static const char *splashText[32];
	splashText[0] = "Trans rights are human rights";//
	splashText[1] = "13^5 + 16^5 = 17^5";//
	splashText[2] = "Reticulating Splines";//
	splashText[3] = "violence.works";//
	splashText[4] = "Tabs!";//
	splashText[5] = "Kill Billionaires (and Trillionaire)";//
	splashText[6] = "Interest in technology is not a personality";//
	splashText[7] = "10 PRINT CHR$(205.5+RND(1)); : GOTO 10";//
	splashText[8] = "No gods. No masters. No external libraries.";//
	splashText[9] = "Kill Nazis";//
	splashText[10] = "Tiananmen Square 1989";//
	splashText[11] = "America was founded on slavery";
	splashText[12] = "There is only capital and labor";//
	splashText[13] = "Encourage _symmetric_ class warfare";//
	splashText[14] = "$CURRENT_MEME";//
	splashText[15] = "A Nice TTY";//
	splashText[16] = "Unix epoch minus 0xFF days";//
	splashText[17] = "i  = 0x5f3759df - ( i >> 1 );";//
	splashText[18] = "ACAB";//
	splashText[19] = "Defcon's canceled.";//
	splashText[20] = "Ratsnest: Nothing To Do!";//
	splashText[21] = "It has 69 keys.";//
	splashText[22] = "Because VT-420 was already taken";//
	splashText[23] = "Compression algorithm based on BBP (1997)";//
	splashText[24] = "The source of the Mississippi river is in Pennsylvania.";
	splashText[25] = "Offensive hardware";//
	splashText[26] = "Follow World Pog Federation    @WorldPog";//
	splashText[27] = "Dummy thicc client";//
	splashText[28] = "A Nice TTY. An OK Computer.";//
	splashText[29] = "Ceci n'est pas une Cyberdeck (because it's not a Pelican Case)";//
	splashText[30] = "Solidarity is not a new framework";//
	splashText[31] = "Breadboarding Is Not A Crime";//
	splashText[32] = "Off by one errors are common";
	
	const char *textPhrase = splashText[((rand()%32))];
	char bootString[40];
	const uint32_t megaHurtz = system_gclk_gen_get_hz(0);
	itoa(megaHurtz,bootString,10);
	//strcpy(bootString, " Hz");

	
	clearScreen();
	setColorRGB(255,255,255);
	
	REG_PORT_DIRTGL1 = PORT_PB31;
	PORT->Group[1].PINCFG[31].bit.PULLEN = 1;
	PORT->Group[1].PINCFG[31].bit.INEN = 1;
	if((PORT->Group[1].IN.reg & PORT_PB31) != 0)
	{
		//This is the 'pi' graphic; put some codes
		//here to handle setting up the uarts.
		drawKare(1);
	}
	else
	drawKare(0); //The normal graphic
	

	
	xCharPos = 40 - (strlen(textPhrase)/2);
	yCharPos = 16;
	
	writeString(textPhrase);
	
	yCharPos = 17;
	xCharPos = 40 - (strlen(bootString)/2);
	writeString(bootString);
	delay_ms(2000);
	clearScreen();
	
	setColorRGB(0,255,0);
	setBackColorRGB(0,0,0);
	
	//Setting the xChar and yChar position has to come
	//after splashScreen() and InitLCD();
	xCharPos = 0;
	yCharPos = 0;
	

}