#include "config_usart.h"

void configure_console(void)
{
	struct usart_config config_usart;
	usart_get_config_defaults(&config_usart);

	config_usart.baudrate    = SERCOMBAUD;
	config_usart.mux_setting = SERCOMMUX;
	config_usart.pinmux_pad0 = SERCOMPAD0;
	config_usart.pinmux_pad1 = SERCOMPAD1;
	config_usart.pinmux_pad2 = SERCOMPAD2;
	config_usart.pinmux_pad3 = SERCOMPAD3;

	while (usart_init(&usart_instance,	 SERCOMMODULE, &config_usart) != STATUS_OK) { }

	stdio_serial_init(&usart_instance, SERCOMMODULE, &config_usart);
	usart_enable(&usart_instance);
}

void serialRead(uint16_t *const buffer){
	
	if (usart_read_wait(&usart_instance, buffer) == STATUS_OK) {
	}


}