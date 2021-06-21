#include <atmel_start.h>
#include <stdio.h>

#include "globals.h"
#include "LCDBus.h"
#include "LCD.h"
#include "splash.h"

/** GLOBAL SETTINGS ***********************************************************/

bool localEcho = true;
bool breakEnable = false;
bool lineFeed = true;
bool autoWrap = true;
int lineFeedNewLine = 1;

//This device is for gamers because all the characters are white by default.
uint16_t defaultForegroundColor = 0xFFFF;
uint16_t defaultBackgroundColor = 0x0000;

char compileTime[] =  __TIMESTAMP__;
char versionLabel[] = "Beach Taco Bell";


/** LOCAL PROTOTYPES **********************************************************/
void setupBoard(void);



int main(void)
{
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();
	
	
	int count = 0;
	
	printf("hi\n");
	InitLCD();
	//splashScreen();

	/* Replace with your application code */
	while (1) {
		//printf("%i",count);
		//count++;
		splashScreen();
	}
}
