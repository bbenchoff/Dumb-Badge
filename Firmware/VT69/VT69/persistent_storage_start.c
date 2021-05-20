/*
 * Code generated from Atmel Start.
 *
 * This file will be overwritten when reconfiguring your Atmel Start project.
 * Please copy examples or other code you want to keep to a separate file or main.c
 * to avoid loosing it when reconfiguring.
 */
#include "atmel_start.h"
#include "nv.h"
#include "string.h"
#include "nv_storage.h"

/**
 * \brief Initialize Persistent Storage
 */
void persistent_storage_init(void)
{
	nv_init(&FLASH_0);
	nv_storage_init();
}

/**
 * \brief Persistent storage example
 *
 * IMPORTANT! Be careful running this example. It makes assumption that storage
 * area provided in Persistent storage configuration is reserved in the linker
 * script. If it is not reserved, flash content may get corrupted.
 */
void persistent_storage_example(void)
{
	// store, read and eraze one item
	uint8_t data[10];

	memset(data, 0xa5, 10);
	nv_storage_write(1, 0, data, 10);
	memset(data, 0x00, 10);
	nv_storage_read(1, 0, data, 10);
	nv_storage_delete(1);
}
