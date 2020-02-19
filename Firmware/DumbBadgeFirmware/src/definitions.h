/*
 * Copyright (C) 2018 Microchip Technology Inc. and its subsidiaries
 *
 * File:            definitions.h
 * Project:         dfll48m-initialization
 * Date:            June 30, 2018
 * Compiler:        arm-gcc v6.3.1
 * 
 * Project-wide constants
 *
 * Hardware Configuration: SAMD21 Xplained PRO (ATSAMD21J18A) 
 *
 */


#ifndef DEFINITIONS_H_
#define DEFINITIONS_H_


// Constants for Clock Generators
#define GENERIC_CLOCK_GENERATOR_MAIN      (0u)
#define GENERIC_CLOCK_GENERATOR_XOSC32K   (1u)
#define GENERIC_CLOCK_GENERATOR_OSCULP32K (2u) /* Initialized at reset for WDT */
#define GENERIC_CLOCK_GENERATOR_OSC8M     (3u)
// Constants for Clock multiplexers
#define GENERIC_CLOCK_MULTIPLEXER_DFLL48M (0u)

// Constants for DFLL48M
#define MAIN_CLK_FREQ (24000000u)
#define EXT_32K_CLK_FREQ (32768u)

#endif /* DEFINITIONS_H_ */