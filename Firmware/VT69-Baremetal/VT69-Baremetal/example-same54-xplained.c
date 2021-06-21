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

#include <assert.h>
#include <stdint.h>
#include "sam_clocks.h"

/*
 * We have numerous options for clock source on this board.
 * The 12 MHz crystal on XOSC1 is preferable. However, we can also
 * use the DFLL48M.
 *
 * Ultimately, we expect DPLL#0 to generate a 120 MHz clock using
 * any working clock as its reference.
 */

#if 1
#define	SAME54_DPLL_SOURCE	SAM_DPLL_REFCLK_XOSC1	/* 12 MHz Crystal */
#else
#define	SAME54_DPLL_SOURCE	SAM_DPLL_REFCLK_GCLK	/* Open-loop DFLL48M */
#endif

#define	FREQ_MHZ(f)		((f) * 1000u * 1000u)

/* F_CPU would normally be defined in the Makefile, but just in case... */
#ifndef F_CPU
#define	F_CPU	FREQ_MHZ(120)
#endif

static void
same54_init_clocks(void)
{
	unsigned int dpll_freq, clk;

	if (SAME54_DPLL_SOURCE == SAM_DPLL_REFCLK_XOSC0 ||
	    SAME54_DPLL_SOURCE == SAM_DPLL_REFCLK_XOSC1) {
		sam_xosc_id_t xosc;
		unsigned int xosc_good;

		/* FDPLL is locked to a 12 MHz external crystal */
		if (SAME54_DPLL_SOURCE == SAM_DPLL_REFCLK_XOSC0)
			xosc = SAM_XOSC_ID_0;
		else
			xosc = SAM_XOSC_ID_1;

		/* Start the 12 MHz crystal on XOSC1. */
		xosc_good = sam_xosc_config(xosc,
		    SAM_XOSC_TYPE_CRYSTAL, SAM_XOSC_AUTO_LOOP_OFF,
		    FREQ_MHZ(12));

		assert(xosc_good > 0);
		(void) xosc_good;
	} else
	if (SAME54_DPLL_SOURCE == SAM_DPLL_REFCLK_GCLK) {
		unsigned int gen;

		/* FDPLL is locked to DFLL48 */

		/* Allocate a clock generator for DFLL48. */
		gen = sam_gclk_gen_alloc(SAM_GCLK_GEN_TYPE_NORMAL);
		assert(gen > 0);

		/*
		 * GCLK is used undivided by the DPLL, so we must configure the
		 * generator to divide it down to a legal value. Anything under
		 * 3.2 MHz is acceptable. Dividing by 24 gives a nice even
		 * multiple, and a 2 MHz output clock.
		 */
		clk = sam_gclk_gen_config(gen, SAM_GCLK_GEN_SRC_DFLL,
		    SAM_GCLK_GEN_DIVSEL_DIRECT,
		    sam_dfll48m_frequency / FREQ_MHZ(2), 0);
		assert(clk >= 32768u);
		assert(clk <= 3200000u);
		(void) clk;

		/*
		 * Enable the DPLL#0 peripheral channel clock, sourced from the
		 * generator allocated above.
		 */
		clk = sam_gclk_periph_chan_enable(OSCCTRL_GCLK_ID_FDPLL0,
		    gen);
		assert(clk > 0);
		(void) clk;
	}

	/* Start up DPLL#0, slaved to the selected clock source. */
	dpll_freq = sam_dpll_config(SAM_DPLL_ID_0, SAME54_DPLL_SOURCE, F_CPU);
	assert(dpll_freq > 0);
	(void) dpll_freq;

	/*
	 * Switch GCLK_MAIN over to DPLL#0's undivided output, CPUDIV=1.
	 * This configures Flash wait states and SystemCoreClock.
	 */
	clk = sam_gclk0_mainck_config(SAM_GCLK_GEN_SRC_DPLL0, 1,
	    SAM_GCLK_GEN_DIVSEL_DIRECT, 0, 0);
	assert(clk > 0);
	(void) clk;

	/* Now running at 120 MHz. */
}

static void
same54_init_console(void)
{
	unsigned int gen, sercom_clock;

	/* Enable the APB clock for the console SERCOM. */
	sam_periph_clock_enable(ID_SERCOM2);

	/*
	 * We will use a GCLK to divide DPLL#0 to provide a suitable
	 * input clock for the USART. For common baudrates <= 115200, the
	 * ideal USART clock is 1843200, resulting in a GCLK divisor of 65
	 * with 120 MHz DPLL output. This gives an actuak clock frequency
	 * of 1846154, which is well within tolerance.
	 */

	/* Allocate a clock generator. */
	gen = sam_gclk_gen_alloc(SAME5X_GCLK_GEN_TYPE_NORMAL);
	assert(gen > 0);

	/* Derive the required clock frequency from DPLL#0. */
	sercom_clock = sam_gclk_gen_config(gen, SAM_GCLK_GEN_SRC_DPLL0,
	    SAM_GCLK_GEN_DIVSEL_DIRECT,
	    sam_dpll_frequencies[0] / 1843200u, 0);
	assert(sercom_clock > 0);

	/* The SERCOM's clock source is the configured clock generator. */
	(void) sam_gclk_periph_chan_enable(SERCOM2_GCLK_ID_CORE, gen);

	/*
	 * Example call to initialise the SERCOM, making sure to pass
	 * its clock frequency.
	 */
	sam_sercom_usart_init(ID_SERCOM2, sercom_clock);
}

void
platform_init(void)
{

	same54_init_clocks();
	same54_init_console();
}
