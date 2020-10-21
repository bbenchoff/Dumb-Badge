/**************************This is 80 width line*******************************/
#include <asf.h>
#include <string.h>

#include "globals.h"

#include "LCDBus.h"
#include "LCD.h"
#include "keyboard.h"
#include "console.h"
#include "splash.h"
#include "uart.h"

//#include "config_usart.h"
#include "conf_clocks.h"

/** VARIABLES *****************************************************************/

uint16_t ul_tickcount=0;
bool funcLock = false;	

#define RX_LEN 10
char rx_buf;


void usart_read_callback(struct usart_module *const usart_module);
void configure_usart(void);
void configure_usart_callbacks(void);

/** LOCAL PROTOTYPES **********************************************************/


void setupBoard(void);

//void configure_usart_USB(void);
void configure_adc(void);

void conf_systick(void);

//struct usart_module usart_USB;
struct adc_module adc_instance;

struct usart_module usart_instance;



/** STUFF BEGINS HERE *********************************************************/
int main (void)
{
	setupBoard();
	
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
	char temp = 0x00;
	usart_read_buffer_job(&usart_instance, (uint8_t*)&rx_buf, 1);
	
	temp = rx_buf;

	drawChar(temp);
	xCharPos++;
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
	config_adc.positive_input = ADC_POSITIVE_INPUT_DAC;
	adc_init(&adc_instance, ADC, &config_adc);
	adc_enable(&adc_instance);
}



void setupBoard(void)
{
	uint16_t adcResult;

	system_init();
	
	configure_adc();
	adc_start_conversion(&adc_instance);
	do {
		/* Wait for conversion to be done and read out result */
	} while (adc_read(&adc_instance, &adcResult) == STATUS_BUSY);
	
	delay_init();
	srand(adcResult);
	//configure_usart_USB();

	//configure_console();
	//printf("Serial OK 9600 8N1\n\r");
	configure_usart();
	configure_usart_callbacks();
	system_interrupt_enable_global();
	printf("Serial OK 9600 8N1\n\r");
	usart_read_buffer_job(&usart_instance, (uint8_t*)&rx_buf, 1);
	
	InitLCD();
	splashScreen();
			
	conf_systick();

	xCharPos=0;
	yCharPos=0;
	drawChar(0xFF);
}
