/*
 * Copyright (c) 2020 Steve Woodford and Maverick Embedded Technologies Ltd.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef SAM_CLOCKS_H
#define SAM_CLOCKS_H

#include <stdbool.h>

/*
 * The SAMD5X/E5X range of SoCs from Microchip have a very flexible
 * clock heirarchy.
 *
 * Unfortunately, with this flexibility comes a significant level of
 * complexity; sufficient to confuse and confound even seasoned software
 * engineers.
 *
 * Microchip's "Start" web-based configurator can be used to spit out
 * some canned initialisation code according to its WYSIWYG clock editor,
 * but it's brittle at runtime and pays no heed to min/max clock
 * frequencies in the data sheet.
 *
 * So here I present a simple API to cover the vast majority of clock
 * configurations for these devices. One of the key benefits of this API
 * over "Start" is that the configuration is not fixed at compile-time;
 * you are free to reconfigure the clocks at runtime in whatever manner
 * you choose.
 *
 * The API incorporates a plethora of sanity checking to ensure it is
 * being used correctly and that clock routing/frequencies do not exceed
 * the capabilities of the device. For debug builds (NDEBUG is *not*
 * defined), the API makes heavy use of the 'assert()' library call to
 * force execution to halt, making it easy to track down the problem
 * in a debugger. In release builds (NDEBUG *is* defined), the API
 * still validates input parameters and will return an error status
 * if things are not as they should be. However, this release behaviour
 * can be removed entirely should you wish to live fast and loose.
 * Just #define SAM_CLOCKS_FAST_AND_LOOSE_ASSERT_FOR_RELEASE when
 * compiling for release. Your code will be smaller, but you'd better
 * be very sure it can never fail...
 *
 * That said, it's no panacea. There are some missing features:
 *
 *	- Clock failure detection at runtime,
 *	- 'Run in Standby' configuration (the code sets all clocks to
 *	   always run in standby),
 *	- 'On Demand' is not used,
 *	- Clock register "Write locking" is not handled,
 *	- DPLL filters are not used.
 *
 * Adding the missing features is left as an exercise for the reader.
 */

/*
 * ============================================================================
 * Global Data
 * ============================================================================
 */
/*
 * The following global variables are exported by the API. They reflect the
 * current frequency of all configured clock sources in the system.
 *
 * A value of zero indicates an unconfigured source.
 *
 * These variables are for reference purposes only; consumers of this API must
 * not modify them.
 */
#ifndef SAM_CONST
#define	SAM_CONST	const
#endif
extern SAM_CONST unsigned int sam_dfll48m_frequency;
extern SAM_CONST unsigned int sam_xosc32k_frequency;
extern SAM_CONST unsigned int sam_xosc_frequencies[/* 0 - 1 */];
extern SAM_CONST unsigned int sam_dpll_frequencies[/* 0 - 1 */];
extern SAM_CONST unsigned int sam_gclk_frequencies[/* 0 - 11 */];


/*
 * ============================================================================
 * XOSCn Configuration API
 * ============================================================================
 */
/*
 * This is the 'xosc' parameter to sam_xosc_config(), identifying the
 * target XOSC instance.
 */
typedef enum sam_xosc_id {
	SAM_XOSC_ID_0 = 0,
	SAM_XOSC_ID_1 = 1
} sam_xosc_id_t;

/*
 * Identify the type of oscillator connected to the input of XOSCn. Options
 * are crystal or TTL.
 * This is used as the 'type' parameter for sam_xosc_config();
 */
typedef enum sam_xosc_type {
	SAM_XOSC_TYPE_TTL,
	SAM_XOSC_TYPE_CRYSTAL
} sam_xosc_type_t;

/*
 * Configure automatic loop gain settings for an XOSCn device.
 * This is the 'auto_loop' parameter for sam_xosc_config(), and
 * is valid only when XOSCn is connected to an external crystal.
 */
typedef enum sam_xosc_auto_loop {
	SAM_XOSC_AUTO_LOOP_OFF,
	SAM_XOSC_AUTO_LOOP_LOW,
	SAM_XOSC_AUTO_LOOP_HIGH
} sam_xosc_auto_loop_t;

/*
 * Initialise an external oscillator, identified by the 'xosc' and
 * 'type' parameters.
 * For crystals, the automatic loop gain setting is configure using the
 * 'auto_loop' parameter. The frequency of the crystal/TTL input is
 * specified by the 'frequency' parameter.
 *
 * The function will return 'frequency' on success, or zero on failure,
 * (such as failing to become ready within a reasonable time period).
 *
 * Invalid input parameters will be asserted in debug builds, otherwise
 * zero will be returned.
 */
extern unsigned int
sam_xosc_config(sam_xosc_id_t xosc, sam_xosc_type_t type,
		sam_xosc_auto_loop_t auto_loop, unsigned int freq);


/*
 * ============================================================================
 * XOSC32K Configuration API
 * ============================================================================
 */
/*
 * Identifies the type of input to the XOSC32K oscillator.
 * This is the 'type' parameter for sam_xosc32k_config().
 */
typedef enum sam_xosc32k_type {
	SAM_XOSC32K_TYPE_TTL,
	SAM_XOSC32K_TYPE_CRYSTAL,
	SAM_XOSC32K_TYPE_CRYSTAL_HS
} sam_xosc32k_type_t;

/*
 * Initialise the external 32 KHz oscillator, with the type of oscillator
 * identified by the 'type' parameter. If 'en1k' is non-zero, XOSC32K's
 * 1 KHz RTC output will be enabled. If 'en32k' is non-zero, XOSC32K's
 * 32 KHz RTC output will be enabled. At least one of these *must* be
 * non-zero.
 *
 * The function will return zero if the oscillator failed to start.
 * Otherwise it will return 32768 if 'en32k' is non-zero. If 'en32k'
 * is zero, it will return 1024.
 *
 * Invalid input parameters will be asserted in debug builds, otherwise
 * zero will be returned.
 */
extern unsigned int
sam_xosc32k_config(sam_xosc32k_type_t type, int en32k, int en1k);


/*
 * ============================================================================
 * DFLL48M Configuration API
 * ============================================================================
 */
/*
 * Identifies the source clock to which the DFLL48M should be phase-locked.
 * This is the 'type' parameter for sam_dfll48_lock().
 */
typedef enum sam_dfll48_lock_source {
	SAM_DFLL48_LOCK_OPEN_LOOP,
	SAM_DFLL48_LOCK_GCLK,
	SAM_DFLL48_LOCK_USB_SOF
} sam_dfll48_lock_source_t;

/*
 * Attempt to phase-lock the DFLL48M oscillator with another clock source.
 * Two options are available, a pre-configured clock generator, or USB
 * Start of Frame (SOF). In either case, you must call this function *after*
 * enabling the reference clock. For SAM_DFLL48_LOCK_GCLK, you are also
 * responsible for ensuring the generator's output frequency is within the
 * legal range for DFLL48M.
 * The default 'Open Loop' mode can be restored by calling the function with
 * 'lock_source' set to SAM_DFLL48_LOCK_OPEN_LOOP.
 *
 * The function will return the DFLL48M's actual output frequency on success,
 * or zero if the DFLL48M failed to lock.
 *
 * Note: The actual output frequency depends on the frequency of the reference
 *       clock to which it is phase-locked. If the reference clock is not
 *       an exact multiple of 48 MHz, then the actual output will be slightly
 *       under 48 MHz.
 *
 * If 'wait_for_lock' is true, the function will busy-wait for lock to be
 * achieved, subject to a 30 mS timeout.
 *
 * Invalid input parameters and/or out of range reference clock frequency
 * will be asserted in debug builds, otherwise zero will be returned.
 */
extern unsigned int
sam_dfll48_lock(sam_dfll48_lock_source_t lock_source, bool wait_for_lock);


/*
 * ============================================================================
 * DPLLn Configuration API
 * ============================================================================
 */
/*
 * This is the 'id' parameter to sam_dpll_config(), identifying the
 * target DPLL.
 */
typedef enum sam_dpll_id {
	SAM_DPLL_ID_0 = 0,
	SAM_DPLL_ID_1 = 1
} sam_dpll_id_t;

/*
 * Identifies the source of the DPLLn reference clock.
 * This is the 'refclk' parameter to sam_dpll_config();
 */
typedef enum sam_dpll_refclk {
	SAM_DPLL_REFCLK_XOSC0,
	SAM_DPLL_REFCLK_XOSC1,
	SAM_DPLL_REFCLK_GCLK,
	SAM_DPLL_REFCLK_XOSC32
} sam_dpll_refclk_t;

/*
 * Configure the specified DPLL 'id' to use the input 'refclk' to generate
 * the desired 'output_freq' frequency. The function will attempt to configure
 * the DPLL so that the actual output frequency is as close as possible to the
 * desired value, without exceeding it.
 *
 * Note that the caller is responsible for configuring the reference clock
 * before calling this function.
 * 
 * The function will return zero if the DPLL failed to lock to the reference
 * clock. Otherwise it will return the actual output frequency.
 *
 * Invalid input parameters and/or out of range reference clock frequency
 * will be asserted in debug builds, otherwise zero will be returned.
 */
extern unsigned int
sam_dpll_config(sam_dpll_id_t id, sam_dpll_refclk_t refclk,
		unsigned int output_freq);


/*
 * ============================================================================
 * Clock Generator (GCLK) Configuration API
 * ============================================================================
 */
/*
 * This enumeration identifies a clock generator's input clock source.
 */
typedef enum sam_gclk_gen_src {
	SAM_GCLK_GEN_SRC_XOSC0 = 0,
	SAM_GCLK_GEN_SRC_XOSC1,
	SAM_GCLK_GEN_SRC_GCLKIN,
	SAM_GCLK_GEN_SRC_GCLKGEN1,
	SAM_GCLK_GEN_SRC_OSCULP32K,
	SAM_GCLK_GEN_SRC_XOSC32K,
	SAM_GCLK_GEN_SRC_DFLL,
	SAM_GCLK_GEN_SRC_DPLL0,
	SAM_GCLK_GEN_SRC_DPLL1
} sam_gclk_gen_src_t;

/*
 * This enumeration specifies how to interpret the 'div' parameter of
 * the sam_gclk_gen_config() and sam_gclk0_mainck_config() functions.
 *
 * For SAM_GCLK_GEN_DIVSEL_DIRECT, the generator output clock frequency
 * equals the source clock frequency divided by 'div'. If 'div' is 0 or 1,
 * the output clock is undivided.
 *
 * For SAM_GCLK_GEN_DIVSEL_POWER_OF_TWO, the generator output clock
 * frequency equals the source clock frequency divided by 2^('div'+1).
 */
typedef enum sam_gclk_gen_divsel {
	SAM_GCLK_GEN_DIVSEL_DIRECT,
	SAM_GCLK_GEN_DIVSEL_POWER_OF_TWO
} sam_gclk_gen_divsel_t;

/*
 * This enumeration is passed to sam_gclk_gen_alloc() to identify the
 * speed of clock generator to allocate. Generators come in two speed
 * flavours based on their maximum output clock frequency; 100 or 200 MHz.
 */
typedef enum sam_gclk_gen_type {
	SAM_GCLK_GEN_TYPE_NORMAL,	/* Max 100 MHz output. */
	SAM_GCLK_GEN_TYPE_FAST	/* Max 200 MHz output. */
} sam_gclk_gen_type_t;

/*
 * Allocate the first unused clock generator of the specified type.
 *
 * If there are no clock generators available, the function returns zero.
 * Otherwise it returns the GCLK's number, which can be passed to other
 * functions which accept a clock generator number.
 *
 * Note: GCLK0 cannot be allocated in this way.
 * Note: Generators are allocated top-down. That is, higher numbered
 *       GCLKs are allocated before lower numbered.
 * Note: Calling this function does *not* reserve or enable the allocated
 *       generator. You must call sam_gclk_gen_config() to do that.
 *
 * Invalid input parameters and/or no free generators of the specified
 * type will be asserted in debug builds, otherwise zero will be returned.
 */
extern unsigned int
sam_gclk_gen_alloc(sam_gclk_gen_type_t type);

/*
 * The opposite of the above function. The specified generator is disabled.
 *
 * Note: It is not possible to disable GCLK0.
 * Note: It is the caller's responsibility to ensure the generator is not
 *       referenced by any peripheral channels.
 *
 * The function returns '0' on success.
 *
 * Invalid input parameters will be asserted in debug builds, otherwise -1
 * will be returned.
 */
extern int
sam_gclk_gen_free(unsigned int gen);

/*
 * Configure and enable the specified generator with the supplied source
 * clock and divider.
 *
 * The target GCLK generator is specified by 'gen'. The generator's
 * source clock is specified by 'src'. The interpretation of the 'div'
 * parameter is governed by the 'divsel' parameter. See the definition
 * of sam_gclk_gen_divsel_t for details. The final parameter, 'xin_freq'
 * is only used for SAM_GCLK_GEN_SRC_GCLKIN. It specifies the frequency
 * of the external input clock.
 *
 * Note: GCLK0 cannot be configured using this function.
 * Note: The input clock must be enabled and running before calling this
 *       function, except for 'src' == SAM_GCLK_GEN_SRC_GCLKIN.
 * Note: For 'src' == SAM_GCLK_GEN_SRC_GCLKIN, the caller is responsible
 *       for configuring the appropriate GPIO input pin, and 'xin_freq'
 *       must not exceed 50 MHz.
 * Note: For GCLK1, all 16-bits of 'div' are significant. For all other
 *       clock generators, only the low 8-bits are significant.
 * Note: For 'divsel' == SAM_GCLK_GEN_DIVSEL_DIRECT, the function will
 *       set the GENCTRL.IDC bit for values of 'div' which are not a
 *       multiple of two. As per the data sheet, this ensures the output
 *       clock maintains a 50/50 duty cycle for uneven division factors.
 *
 * The function returns the output clock frequency of the generator, or
 * zero on failure (debug builds will assert() rather than return zero).
 *
 * Invalid input parameters, disabled clock source, or out of range clock
 * frequencies will be asserted in debug builds, otherwise zero will be
 * returned.
 */
extern unsigned int
sam_gclk_gen_config(unsigned int gen, sam_gclk_gen_src_t src,
		    sam_gclk_gen_divsel_t divsel, uint16_t div,
		    unsigned int xin_freq);

/*
 * Enable/disable the specified generator's external output.
 * The 'gen' parameter specifies the target clock generator. If 'oe' is
 * non-zero, the output will be enabled. Otherwise it will be disabled.
 * The 'oov' indicates the output-off-value, as per the data sheet.
 *
 * Note: It is not legal to call this function for a GCLK whose input
 *       clock source is SAM_GCLK_GEN_SRC_GCLKIN. This will be
 *       asserted in debug builds.
 * Note: It is the caller's responsibility to configure the generator
 *       before calling this function.
 *
 * The function returns '0' on success.
 *
 * Invalid input parameters and/or out of range output clock frequency
 * will be asserted in debug builds, otherwise -1 will be returned.
 */
extern int
sam_gclk_gen_xout(unsigned int gen, int oe, int oov);

/*
 * Configure GCLK0, and the MCLK's CPU divider.
 * This is the only funtion capable of configuring GCLK0.
 *
 * All parameters, bar one, are identical to the sam_gclk_gen_config()
 * function. The same constraints for sam_gclk_gen_config() also apply.
 *
 * The 'cpudiv' parameter is used to set the CPU core clock divider in the
 * Main Clock controller. This will normally be '1' for highest performance.
 *
 * The function will ensure Flash Wait States are configured correctly
 * for the final CPU core clock speed, whether the clock is faster or
 * slower than the current core clock.
 *
 * Before returning, the function sets the 'SystemCoreClock' global
 * variable to the CPU core's clock frequency. Due to 'cpudiv', this
 * may be lower than GCLK0's output frequency.
 *
 * On return, the function returns the output clock frequency of GCLK0.
 *
 * Invalid input parameters and/or out of range clock frequencies
 * will be asserted in debug builds, otherwise zero will be returned.
 */
extern unsigned int
sam_gclk0_mainck_config(sam_gclk_gen_src_t src, uint8_t cpudiv,
			sam_gclk_gen_divsel_t divsel, uint8_t div,
			unsigned int xin_freq);

/*
 * Enable the specified peripheral channel, with its clock source set
 * to the specified generator.
 *
 * See the data sheet (Section 14.8.4) for valid values for 'pchan'.
 *
 * Note: It is the caller's responsibility to ensure the specified
 *       clock generator is enabled and supplying a valid clock.
 * Note: You can use this function to change a peripheral channel's
 *       clock generator whilst it is already enabled.
 *
 * On success, the function returns the clock frequency of the selected
 * clock generator.
 *
 * Invalid input parameters, or disabled clock generator will be asserted
 * in debug builds, otherwise zero will be returned.
 */
extern unsigned int
sam_gclk_periph_chan_enable(unsigned int pchan, unsigned int gen);

/*
 * Disable the specified peripheral channel.
 *
 * The function returns '0' on success.
 *
 * An invalid input parameter will be asserted in debug builds, otherwise
 * -1 will be returned in release builds.
 */
extern int
sam_gclk_periph_chan_disable(unsigned int pchan);

/*
 * ============================================================================
 * Main Clock (MCLK) Configuration API
 * ============================================================================
 */
/*
 * These three functions query and modify the status of individual peripheral
 * AHB and/or APB bus clocks. Most peripherals will need to have their clock
 * enabled before they can be used. Some are enabled by default after reset.
 *
 * The 'id' parameter identifies the target peripheral, and is always one of
 * the 'ID_abcd' constants defined in the SoC-specific header file from
 * Microchip. For example, ID_SERCOM1, ID_GMAC, or ID_CAN0.
 *
 * The sam_periph_clock_status() returns the current state of the
 * peripheral's clock; 0 for disabled, and 1 for enabled. It will return -1
 * on release builds if the peripheral ID is invalid.
 *
 * The sam_periph_clock_enable() and sam_periph_clock_disable()
 * functions return 0 on success. They will return -1 on release builds if the
 * peripheral ID is invalid.
 *
 * On debug builds, an invalid peripheral ID will cause an assertion.
 */
extern int sam_periph_clock_status(unsigned int id);
extern int sam_periph_clock_enable(unsigned int id);
extern int sam_periph_clock_disable(unsigned int id);

extern void sam_clock_dump(void);

#endif /* SAM_CLOCKS_H */
