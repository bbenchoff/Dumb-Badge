/*
 * Code generated from Atmel Start.
 *
 * This file will be overwritten when reconfiguring your Atmel Start project.
 * Please copy examples or other code you want to keep to a separate file
 * to avoid losing it when reconfiguring.
 */
#ifndef DRIVER_INIT_INCLUDED
#define DRIVER_INIT_INCLUDED

#include "atmel_start_pins.h"

#ifdef __cplusplus
extern "C" {
#endif

#include <hal_atomic.h>
#include <hal_delay.h>
#include <hal_gpio.h>
#include <hal_init.h>
#include <hal_io.h>
#include <hal_sleep.h>


#include <hal_ext_irq.h>

#include <hal_flash.h>

#include <hal_usart_sync.h>

#include <hal_usart_sync.h>

#include <hal_delay.h>

#include <hal_rand_sync.h>

#include "hal_usb_device.h"

#include <hal_wdt.h>

extern struct flash_descriptor FLASH_0;

extern struct usart_sync_descriptor USART_0;

extern struct usart_sync_descriptor USART_1;

extern struct rand_sync_desc RAND_0;

extern struct wdt_descriptor WDT_0;

void FLASH_0_init(void);
void FLASH_0_CLOCK_init(void);

void USART_0_PORT_init(void);
void USART_0_CLOCK_init(void);
void USART_0_init(void);

void USART_1_PORT_init(void);
void USART_1_CLOCK_init(void);
void USART_1_init(void);

void delay_driver_init(void);

void RAND_0_CLOCK_init(void);
void RAND_0_init(void);

void USB_0_CLOCK_init(void);
void USB_0_init(void);

void WDT_0_CLOCK_init(void);
void WDT_0_init(void);

/**
 * \brief Perform system initialization, initialize pins and clocks for
 * peripherals
 */
void system_init(void);

#ifdef __cplusplus
}
#endif
#endif // DRIVER_INIT_INCLUDED
