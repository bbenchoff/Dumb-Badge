#include <atmel_start.h>
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>


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

char versionLabel[] = "Beach Taco Bell";
char compileTime[] = __TIMESTAMP__;


int main(void)
{
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();
	InitLCD();

	printf("hi");
	 int count = 0;

	/* Replace with your application code */
	while (1) {
		printf("%i",count);
		count++;
		splashScreen();
	}
}
