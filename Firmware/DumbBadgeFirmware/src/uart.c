/*
 * uart.c
 *
 * Created: 10/16/2020 3:18:32 PM
 *  Author: bench
 */ 

#include <asf.h>
#include <string.h>

#include "globals.h"

#include "LCDBus.h"
#include "LCD.h"
#include "keyboard.h"
#include "console.h"
#include "splash.h"
#include "uart.h"
#include "ouroboros.h"
#include "parser.h"

//uint8_t rx_buf;
char tempCharacter;

cbuf_handle_t ouroboros;	

void parseRXBuffer(void)
{
		while(!ring_empty(ouroboros))
		{
			uint8_t characterFromRingBuffer;
			ring_get(ouroboros, &characterFromRingBuffer);
			parseChar(characterFromRingBuffer);
		
		}
		ring_reset(ouroboros);
}
