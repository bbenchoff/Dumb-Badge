/**************************This is 80 width line*******************************/
#include <asf.h>
#include <string.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <assert.h>


#include "settings.h"
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
#include "parserState.h"


//#include "config_usart.h"
#include "conf_clocks.h"

/** VARIABLES *****************************************************************/

//Version Label
char compileTime[] =  __TIMESTAMP__;
char versionLabel[] = "Beach Taco Bell";

#define UART_BUFFER_SIZE 10

uint16_t ul_tickcount=0;
bool funcLock = false;
uint8_t rx_buf;

parserState currentState = stateGround;


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

void usart_read_callback(struct usart_module *const usart_module);
void configure_usart(void);
void configure_usart_callbacks(void);

void setupBoard(void);
//void configure_usart_USB(void);
void configure_adc(void);
void conf_systick(void);

//struct usart_module usart_USB;
struct adc_module adc_instance;
struct usart_module usart_instance;
cbuf_handle_t ouroboros;
//struct Settings settings;


/** STUFF BEGINS HERE *********************************************************/
int main (void)
{
	setupBoard();

	//initalize the settings	
	//settings.localEcho=false;

	//initalize the ring buffer for uart
	uint8_t * buffer  = malloc(UART_BUFFER_SIZE * sizeof(uint8_t));
	ouroboros = ring_init(buffer, UART_BUFFER_SIZE);
	


	while(1)
	{			
		__WFI();
		
		if((ul_tickcount % (UINT16_MAX/4) == 0) && (funcLock == false))
		{
			funcLock = true;

			blinkCursor();
			
			funcLock = false;
			
		}
		
		if((ul_tickcount % 200 == 0) && (funcLock == false))
		{
			funcLock = true;

			readKeyboard();
			
			printKeyboardBuffer();

			parseRXBuffer();
			funcLock = false;
		}
		
	
	}
}

/**************************INTERRUPT STUFF****************************/

void SysTick_Handler(void)
{
	ul_tickcount++;
}

void conf_systick(void)
{
	//system_core_clk=48Mhz / 1000=48kHz systic clk if 48Mhz  is used
	SysTick_Config(SystemCoreClock/1000);
	system_interrupt_enable(SYSTEM_INTERRUPT_SYSTICK);
}

void usart_read_callback(struct usart_module *const usart_module)
{

	// Read one character from the UART.
	//We can only use this function because it's non-blocking
	//and we can only read one character because reading > 1 means
	//it doesn't complete until _all_ characters are read.
	
	usart_read_buffer_job(&usart_instance, (uint8_t*)&rx_buf, 1);
	
	//stuff that ONE CHARACTER into the circular FIFO buffer
	ring_put(ouroboros, rx_buf);
}


/**************************SERCOM STUFF*******************************/


void configure_usart(void)
{
	struct usart_config config_usart;
	usart_get_config_defaults(&config_usart);

	config_usart.baudrate    = 9600;
	config_usart.mux_setting = USART_RX_1_TX_0_XCK_1;
	config_usart.pinmux_pad0 = PINMUX_PA08D_SERCOM2_PAD0;
	config_usart.pinmux_pad1 = PINMUX_PA09D_SERCOM2_PAD1;
	config_usart.pinmux_pad2 = PINMUX_UNUSED;
	config_usart.pinmux_pad3 = PINMUX_UNUSED;
	
	/*
	The SamD51 version will be using CTS and RTS flow control;
	see this for more information:
	
	https://www.avrfreaks.net/forum/no-asf-samd21-sercom-usart-rxc-interrupt-not-triggering
	
	RTS on PAD2 and CTS on PAD3
	
	*/
	
	while (usart_init(&usart_instance, SERCOM2, &config_usart) != STATUS_OK) {
	}
	stdio_serial_init(&usart_instance, SERCOM2, &config_usart);
	usart_enable(&usart_instance);
}

void configure_usart_callbacks(void)
{
	usart_register_callback(&usart_instance,usart_read_callback, USART_CALLBACK_BUFFER_RECEIVED);
	usart_enable_callback(&usart_instance, USART_CALLBACK_BUFFER_RECEIVED);
}




/*
void configure_usart_USB(void)
{
	struct usart_config config_usart_USB;
	usart_get_config_defaults(&config_usart_USB);

		config_usart_USB.baudrate    = 9600;
		config_usart_USB.mux_setting = EDBG_CDC_SERCOM_MUX_SETTING;
		config_usart_USB.pinmux_pad0 = EDBG_CDC_SERCOM_PINMUX_PAD0;
		config_usart_USB.pinmux_pad1 = EDBG_CDC_SERCOM_PINMUX_PAD1;
		config_usart_USB.pinmux_pad2 = EDBG_CDC_SERCOM_PINMUX_PAD2;
		config_usart_USB.pinmux_pad3 = EDBG_CDC_SERCOM_PINMUX_PAD3;
		while (usart_init(&usart_USB,
		EDBG_CDC_MODULE, &config_usart_USB) != STATUS_OK) {
		}

	usart_enable(&usart_USB);
}
*/

void configure_adc(void)
{
	struct adc_config config_adc;
	adc_get_config_defaults(&config_adc);
	config_adc.clock_source = GCLK_GENERATOR_1;
	config_adc.clock_prescaler = ADC_CLOCK_PRESCALER_DIV16;
	config_adc.reference = ADC_REFERENCE_INT1V;
	config_adc.positive_input = ADC_POSITIVE_INPUT_TEMP;
	config_adc.negative_input = ADC_NEGATIVE_INPUT_GND;
	adc_init(&adc_instance, ADC, &config_adc);
	adc_enable(&adc_instance);
}


void setupBoard(void)
{
	uint16_t adcResult;
	uint16_t megaHurtz = (uint16_t)system_gclk_gen_get_hz(0);
	

	system_init();
	
	configure_adc();
	adc_start_conversion(&adc_instance);
	do {
	/* Wait for conversion to be done and read out result */
	} while (adc_read(&adc_instance, &adcResult) == STATUS_BUSY);
	
	
	srand((adcResult ^ megaHurtz));
	
	delay_init();
	
	conf_systick();

	//configure_usart_USB();
	
	/*
	The Pi is connected to a different SERCOM in the SAMD51 version;
	The Pi is now connected to SERCOM2, with PAD0 (PI_TX) on pin 46,
	and PAD1 (PI_RX) on pin 47.
	
	Also, this gives us the ability to bridge UARTs. THIS IS COOL
	
	*/
	configure_usart();
	configure_usart_callbacks();
	system_interrupt_enable_global();
	
	//I have no idea why I need to call this; it's in the callback and it
	//doesn't work without this line here. Remove this at your own peril.
	usart_read_buffer_job(&usart_instance, (uint8_t*)&rx_buf, 1);
	


	printf("\n\rSerial OK 9600 8N1\n\r");

	
	InitLCD();
	splashScreen();
			
	conf_systick();

	xCharPos=0;
	yCharPos=0;
	drawChar(0xFF);
}
