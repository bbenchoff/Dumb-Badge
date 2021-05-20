/*
 * Code generated from Atmel Start.
 *
 * This file will be overwritten when reconfiguring your Atmel Start project.
 * Please copy examples or other code you want to keep to a separate file or main.c
 * to avoid loosing it when reconfiguring.
 */
#ifndef _PERSISTENT_STORAGE_MAIN_H_INCLUDED
#define _PERSISTENT_STORAGE_MAIN_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#include <nv_storage.h>

/**
 * \brief Initialize Persistent Storage
 */
void persistent_storage_init(void);

/**
 * \brief Persistent storage example
 *
 * IMPORTANT! Be careful running this example. It makes assumption that storage
 * area provided in Persistent storage configuration is reserved in the linker
 * script. If it is not reserved, flash content may get corrupted.
 */
void persistent_storage_example(void);

#ifdef __cplusplus
}
#endif

#endif // _PERSISTENT_STORAGE_MAIN_H_INCLUDED
