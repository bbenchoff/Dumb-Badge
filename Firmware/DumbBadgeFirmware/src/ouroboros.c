/*
 * ouroborous.c
 *
 * It's a ring buffer you uncultured swine
 *
 * Created: 10/27/2020 3:17:25 PM
 *  Author: bench
 */ 

#include <stdlib.h>
#include <stdint.h>

#include "ouroboros.h"

extern struct circular_buf_t {
	uint16_t * buffer;
	uint16_t head;
	uint16_t tail;
	uint16_t max; //of the buffer
	bool full;
};


static void advance_pointer(cbuf_handle_t cbuf)
{
	if(cbuf->full)
	{
		cbuf->tail = (cbuf->tail + 1) % cbuf->max;
	}

	cbuf->head = (cbuf->head + 1) % cbuf->max;

	// We mark full because we will advance tail on the next time around
	cbuf->full = (cbuf->head == cbuf->tail);
}

static void retreat_pointer(cbuf_handle_t cbuf)
{
	cbuf->full = false;
	cbuf->tail = (cbuf->tail + 1) % cbuf->max;
}

cbuf_handle_t ring_init(uint8_t* buffer, uint16_t size)
{
	cbuf_handle_t cbuf = malloc(sizeof(circular_buf_t));

	cbuf->buffer = buffer;
	cbuf->max = size;
	ring_reset(cbuf);
	
	return cbuf;
}

void ring_reset(cbuf_handle_t cbuf)
{
	cbuf->head = 0;
	cbuf->tail = 0;
	cbuf->full = false;
}

void ring_put(cbuf_handle_t cbuf, uint8_t data)
{
	cbuf->buffer[cbuf->head] = data;

	advance_pointer(cbuf);
}

int ring_get(cbuf_handle_t cbuf, uint8_t * data)
{
	int r = -1;

	if(!ring_empty(cbuf))
	{
		*data = cbuf->buffer[cbuf->tail];
		retreat_pointer(cbuf);

		r = 0;
	}

	return r;
}

bool ring_empty(cbuf_handle_t cbuf)
{
	return (!cbuf->full && (cbuf->head == cbuf->tail));
}

bool ring_full(cbuf_handle_t cbuf)
{
	return cbuf->full;
}
