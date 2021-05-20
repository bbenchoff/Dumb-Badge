/**************************This is 80 width line*******************************/
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


/** LOCAL PROTOTYPES **********************************************************/
void setupBoard(void);


int main(void)
{
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();

	printf("Serial OK 9600 8N1\n\r");
	setupBoard();
	
	/* Replace with your application code */
	while (1) {
	
		setupBoard();
	}
}

void setupBoard(void)
{
	//uint16_t adcResult;
	//uint16_t megaHurtz = (uint16_t)CONF_GCLK_EIC_FREQUENCY;
	
	/* Initializes MCU, drivers and middleware */
	//atmel_start_init();
	
	
	
	
	/*configure_adc();
	adc_start_conversion(&adc_instance);
	do {
	// Wait for conversion to be done and read out result 
	} while (adc_read(&adc_instance, &adcResult) == STATUS_BUSY);
	*/
	
	//srand((adcResult ^ megaHurtz));
	
	//delay_init();
	
	//conf_systick();

	//configure_usart_USB();
	
	/*
	The Pi is connected to a different SERCOM in the SAMD51 version;
	The Pi is now connected to SERCOM2, with PAD0 (PI_TX) on pin 46,
	and PAD1 (PI_RX) on pin 47.
	
	Also, this gives us the ability to bridge UARTs. THIS IS COOL
	
	*/
	//configure_usart();
	//configure_usart_callbacks();
	//system_interrupt_enable_global();
	
	//I have no idea why I need to call this; it's in the callback and it
	//doesn't work without this line here. Remove this at your own peril.
	//usart_read_buffer_job(&usart_instance, (uint8_t*)&rx_buf, 1);
	

	
	InitLCD();
	splashScreen();
			
	//conf_systick();

	//xCharPos=0;
	//yCharPos=0;
	//drawChar(0xFF);
}
