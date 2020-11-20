/*
 * ouroborous.c
 *
 * It's a ring buffer you uncultured swine
 *
 * Created: 10/27/2020 3:19:30 PM
 *  Author: bench
 */ 

#ifndef OUROBOROS_H	
#define OUROBOROS_H	



typedef struct circular_buf_t circular_buf_t;

typedef circular_buf_t* cbuf_handle_t;

/// Pass in a storage buffer and size, returns a circular buffer handle
cbuf_handle_t ring_init(uint8_t* buffer, uint16_t size);

/// Reset the circular buffer to empty, head == tail.
void ring_reset(cbuf_handle_t cbuf);

/// Adds data if the buffer is full
void ring_put(cbuf_handle_t cbuf, uint8_t data);

/// Retrieve a value from the buffer
/// Returns 0 on success, -1 if the buffer is empty
int ring_get(cbuf_handle_t cbuf, uint8_t * data);

/// CHecks if the buffer is empty
/// Returns true if the buffer is empty
bool ring_empty(cbuf_handle_t cbuf);

/// Checks if the buffer is full
/// Returns true if the buffer is full
bool ring_full(cbuf_handle_t cbuf);

#endif //OUROBOROS_H