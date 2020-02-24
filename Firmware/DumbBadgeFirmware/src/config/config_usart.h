#include <asf.h>
uint8_t read_buffer;

#define SERCOMBAUD		9600
/* Uncomment to use SERCOM 2 config settings! */

#define SERCOM2USART

#define SERCOMMODULE	        SERCOM2
#define SERCOMMUX		USART_RX_1_TX_0_XCK_1
#define SERCOMPAD0		PINMUX_PA08D_SERCOM2_PAD0
#define SERCOMPAD1		PINMUX_PA09D_SERCOM2_PAD1
#define SERCOMPAD2		PINMUX_UNUSED
#define SERCOMPAD3		PINMUX_UNUSED


struct usart_module usart_instance;

void configure_console(void);
void serialRead(uint16_t *const buffer);