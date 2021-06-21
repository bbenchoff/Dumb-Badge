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
#include <stdio.h>
#include <unistd.h>

/* Pull in the appropriate Microchip SAM D5x/E5x header file. */
#include "sam.h"

#define	SAM_CONST	/* */
#include "sam_clocks.h"

/*
 * Development builds will validate fixed constraints using assert().
 * Release builds will force a return value of 0.
 *
 * However, if you define SAM_CLOCKS_FAST_AND_LOOSE_ASSERT_FOR_RELEASE
 * in a release build, then no error checking whatsoever is performed.
 * Use this option at your own risk!
 */
#ifdef	NDEBUG
#ifndef	SAM_CLOCKS_FAST_AND_LOOSE_ASSERT_FOR_RELEASE
#define	CLOCK_ASSERT(rv,x)	do { if (!(x)) return rv; } while (0)
#else
#define	CLOCK_ASSERT(rv,x)	do { /* Nothing */ } while (0)
#endif
#else
#define	CLOCK_ASSERT(rv,x)	do { assert(x); } while (0)
#endif

/* Convenience macro for specifying MHz frequencies. */
#define	FREQ_MHZ(x)		((unsigned int)(x) * 1000u * 1000u)

/* Limits for the DFLL48M */
#define	DFLL_REFCLK_MIN		732u
#define	DFLL_REFCLK_MAX		33000u
#define	DFLL_MUL_MAX		(OSCCTRL_DFLLMUL_MUL_Msk >> \
				 OSCCTRL_DFLLMUL_MUL_Pos)

/* Limits for DPLLn. */
#define	DPLL_REFCLK_MIN		32000u
#define	DPLL_REFCLK_MAX		3200000u
#define	DPLL_OUTCLK_MIN		FREQ_MHZ(96)
#define	DPLL_OUTCLK_MAX		FREQ_MHZ(200)
#define	DPLL_DIV_MAX		(OSCCTRL_DPLLCTRLB_DIV_Msk >> \
				 OSCCTRL_DPLLCTRLB_DIV_Pos)

/* DPLLn clock calculations. */
#define	DPLL_FCKR(ref,div)		((ref) / (((div) + 1u) * 2u))
#define	DPLL_LDR(ckr,of)		(((of) / (ckr)) - 1u)
#define	DPLL_LDRFRAC(ckr,of)		(((of) % (ckr)) / ((ckr) / 32u))
#define	DPLL_OUTPUT(ckr,ldr,ldrfrac)	((((ldr) + 1) * (ckr)) + \
					 ((ldrfrac) * ((ckr) / 32u)))

/* Convenience macro to determine the size of arrays. */
#define	ARRAY_SIZE(f)	(sizeof(f) / sizeof((f)[0]))

/* Keep track of all the clock frequencies we've configured. */
uint32_t SystemCoreClock = FREQ_MHZ(48);
unsigned int sam_dfll48m_frequency = FREQ_MHZ(48);
unsigned int sam_xosc32k_frequency;
unsigned int sam_xosc_frequencies[ARRAY_SIZE(OSCCTRL->XOSCCTRL)];
unsigned int sam_dpll_frequencies[ARRAY_SIZE(OSCCTRL->Dpll)];
unsigned int sam_gclk_frequencies[ARRAY_SIZE(GCLK->GENCTRL)] = {
	[0] = FREQ_MHZ(48),
	0,
};

static void
hw_cycle_delay(uint32_t cycles)
{

	if (cycles) {
		__asm __volatile(
			"1:     subs    %0, %0, #1      \n"
			"       bne.n   1b              \n"
			: "+l" (cycles) : "0"(cycles));
	}
}

unsigned int
sam_xosc_config(sam_xosc_id_t xosc, sam_xosc_type_t type,
    sam_xosc_auto_loop_t auto_loop, unsigned int frequency)
{
	uint32_t reg, rdy, iptat, imult;
	unsigned int timeout;

	CLOCK_ASSERT(0, xosc == SAM_XOSC_ID_0 || xosc == SAM_XOSC_ID_1);

	CLOCK_ASSERT(0, type == SAM_XOSC_TYPE_TTL ||
	    type == SAM_XOSC_TYPE_CRYSTAL);

	CLOCK_ASSERT(0, auto_loop == SAM_XOSC_AUTO_LOOP_OFF ||
	    auto_loop == SAM_XOSC_AUTO_LOOP_LOW ||
	    auto_loop == SAM_XOSC_AUTO_LOOP_HIGH);

	CLOCK_ASSERT(0, frequency <= FREQ_MHZ(48));
	CLOCK_ASSERT(0, frequency >= FREQ_MHZ(8));

	if (frequency == FREQ_MHZ(8)) {
		iptat = 2;
		imult = 3;
	} else
	if (frequency <= FREQ_MHZ(16)) {
		iptat = 3;
		imult = 4;
	} else
	if (frequency <= FREQ_MHZ(24)) {
		iptat = 3;
		imult = 5;
	} else {
		iptat = 3;
		imult = 6;
	}

	/* Configure and enable the required oscillator. */
	reg = OSCCTRL_XOSCCTRL_ENABLE | OSCCTRL_XOSCCTRL_RUNSTDBY |
	    OSCCTRL_XOSCCTRL_IPTAT(iptat) | OSCCTRL_XOSCCTRL_IMULT(imult) |
	    OSCCTRL_XOSCCTRL_STARTUP(8);

	if (type == SAM_XOSC_TYPE_CRYSTAL) {
		/* Crystal oscillator. */
		reg |= OSCCTRL_XOSCCTRL_XTALEN;

		if (auto_loop > SAM_XOSC_AUTO_LOOP_OFF) {
			reg |= OSCCTRL_XOSCCTRL_ENALC;
			if (auto_loop == SAM_XOSC_AUTO_LOOP_HIGH)
				reg |= OSCCTRL_XOSCCTRL_LOWBUFGAIN;
		}
	} else {
		CLOCK_ASSERT(0, auto_loop == SAM_XOSC_AUTO_LOOP_OFF);
	}

	OSCCTRL->XOSCCTRL[xosc].reg = reg;
	rdy = xosc ? OSCCTRL_STATUS_XOSCRDY1 : OSCCTRL_STATUS_XOSCRDY0;
	timeout = 100000;
	while (timeout-- && (OSCCTRL->STATUS.reg & rdy) == 0)
		hw_cycle_delay(50);

	if ((OSCCTRL->STATUS.reg & rdy) == 0) {
		OSCCTRL->XOSCCTRL[xosc].reg = 0;
		return 0;
	}

	sam_xosc_frequencies[xosc] = frequency;

	return frequency;
}

unsigned int
sam_xosc32k_config(sam_xosc32k_type_t type, int en32k, int en1k)
{
	unsigned int timeout;
	uint32_t reg, rdy;

	CLOCK_ASSERT(0, en1k || en32k);

	/* 32.768 KHz crystal attached to XIN32/XOUT32 */
	reg = OSC32KCTRL_XOSC32K_ENABLE | OSC32KCTRL_XOSC32K_RUNSTDBY |
	    OSC32KCTRL_XOSC32K_STARTUP(1);

	switch (type) {
	case SAM_XOSC32K_TYPE_TTL:
		break;
	case SAM_XOSC32K_TYPE_CRYSTAL:
		reg |= OSC32KCTRL_XOSC32K_XTALEN | OSC32KCTRL_XOSC32K_CGM_XT;
		break;
	case SAM_XOSC32K_TYPE_CRYSTAL_HS:
		reg |= OSC32KCTRL_XOSC32K_XTALEN | OSC32KCTRL_XOSC32K_CGM_HS;
		break;
	default:
		CLOCK_ASSERT(0, 0);
	}

	if (en1k)
		reg |= OSC32KCTRL_XOSC32K_EN1K;
	if (en32k)
		reg |= OSC32KCTRL_XOSC32K_EN32K;

	OSC32KCTRL->XOSC32K.reg = reg;
	rdy = OSC32KCTRL_STATUS_XOSC32KRDY;
	timeout = 100000;
	while (timeout-- && (OSC32KCTRL->STATUS.reg & rdy) == 0)
		hw_cycle_delay(50);

	if ((OSC32KCTRL->STATUS.reg & rdy) == 0) {
		OSC32KCTRL->XOSC32K.reg = 0;
		return 0;
	}

	if (en32k)
		sam_xosc32k_frequency = 32768u;

	return en32k ? 32768u : 1024u;
}

static void
gclk_source_freq(sam_gclk_gen_src_t src, unsigned int *pf)
{
	unsigned int freq;

	switch (src) {
	case SAM_GCLK_GEN_SRC_XOSC0:
		freq = sam_xosc_frequencies[0];
		break;
	case SAM_GCLK_GEN_SRC_XOSC1:
		freq = sam_xosc_frequencies[1];
		break;
	case SAM_GCLK_GEN_SRC_GCLKGEN1:
		freq = sam_gclk_frequencies[1];
		break;
	case SAM_GCLK_GEN_SRC_OSCULP32K:
		freq = 32768u;
		break;
	case SAM_GCLK_GEN_SRC_XOSC32K:
		freq = sam_xosc32k_frequency;
		break;
	case SAM_GCLK_GEN_SRC_DFLL:
		freq = sam_dfll48m_frequency;
		break;
	case SAM_GCLK_GEN_SRC_DPLL0:
		freq = sam_dpll_frequencies[0];
		break;
	case SAM_GCLK_GEN_SRC_DPLL1:
		freq = sam_dpll_frequencies[1];
		break;
	case SAM_GCLK_GEN_SRC_GCLKIN:	/* This must be handled by callers. */
	default:
		freq = 0;
		break;
	}

	*pf = freq;
}

static void
sam_dfll_wait_sync(uint8_t mask)
{

	while ((OSCCTRL->DFLLSYNC.reg & mask) != 0)
		;
}

unsigned int
sam_dfll48_lock(sam_dfll48_lock_source_t lock_source, bool wait_for_lock)
{
	unsigned int src_freq, mul;
	uint8_t usbcrm = 0;
	uint32_t reg;

	CLOCK_ASSERT(0, lock_source == SAM_DFLL48_LOCK_OPEN_LOOP ||
	    lock_source == SAM_DFLL48_LOCK_GCLK ||
	    lock_source == SAM_DFLL48_LOCK_USB_SOF);

	if (lock_source == SAM_DFLL48_LOCK_GCLK) {
		unsigned int gen;

		/* Determine our peripheral channel's clock generator. */
		reg = GCLK->PCHCTRL[OSCCTRL_GCLK_ID_DFLL48].reg;
		reg &= reg & GCLK_PCHCTRL_GEN_Msk;
		gen = (unsigned int)(reg >> GCLK_PCHCTRL_GEN_Pos);
		CLOCK_ASSERT(0, gen < ARRAY_SIZE(sam_gclk_frequencies));

		/* Fetch the frequency of the source. */
		src_freq = sam_gclk_frequencies[gen];

		CLOCK_ASSERT(0, src_freq >= DFLL_REFCLK_MIN);
		CLOCK_ASSERT(0, src_freq <= DFLL_REFCLK_MAX);
	} else
	if (lock_source == SAM_DFLL48_LOCK_USB_SOF) {
		src_freq = 1000u;
		usbcrm = OSCCTRL_DFLLCTRLB_USBCRM;
	} else {
		/* Open-loop. */
		src_freq = FREQ_MHZ(48);
	}

	mul = FREQ_MHZ(48) / src_freq;
	if (mul > DFLL_MUL_MAX)
		mul = DFLL_MUL_MAX;

	if (lock_source != SAM_DFLL48_LOCK_OPEN_LOOP) {
		/*
		 * We assume the DFLL is running in open-loop mode and, as such,
		 * DFLLVAL contains the factory calibrated values.
		 * Perserve them.
		 */
		uint8_t ctrlb;

		/* XXX: What are good starting values for CSTEP and FSTEP? */
		OSCCTRL->DFLLMUL.reg = OSCCTRL_DFLLMUL_CSTEP(20) |
		    OSCCTRL_DFLLMUL_FSTEP(3);
		(void) OSCCTRL->DFLLMUL.reg;
		sam_dfll_wait_sync(OSCCTRL_DFLLSYNC_DFLLMUL);

		/* Wrtite the multiplier. */
		OSCCTRL->DFLLMUL.reg |= OSCCTRL_DFLLMUL_MUL(mul);
		(void) OSCCTRL->DFLLMUL.reg;
		sam_dfll_wait_sync(OSCCTRL_DFLLSYNC_DFLLMUL);

		/* Enable closed-loop mode. */
		ctrlb = OSCCTRL->DFLLCTRLB.reg;
		ctrlb &= ~(OSCCTRL_DFLLCTRLB_USBCRM | OSCCTRL_DFLLCTRLB_MODE);
		OSCCTRL->DFLLCTRLB.reg = ctrlb | usbcrm |OSCCTRL_DFLLCTRLB_MODE;
		sam_dfll_wait_sync(OSCCTRL_DFLLSYNC_DFLLCTRLB);

		if (wait_for_lock) {
			unsigned int timeout;

			/* Wait for lock. Timeout after ~30 mS @ 48 MHz */
			for (timeout = 10000u; timeout; timeout--) {
				hw_cycle_delay(500); /* About 30 uS @ 48 MHz */

				reg = OSCCTRL->STATUS.reg &
				    (OSCCTRL_STATUS_DFLLRCS |
				     OSCCTRL_STATUS_DFLLLCKC |
				     OSCCTRL_STATUS_DFLLLCKF |
				     OSCCTRL_STATUS_DFLLRDY |
				     OSCCTRL_STATUS_DFLLOOB);

				if (reg == (OSCCTRL_STATUS_DFLLLCKC |
					    OSCCTRL_STATUS_DFLLLCKF |
					    OSCCTRL_STATUS_DFLLRDY)) {
					/* Clock is locked and ready. */
					timeout = 1;
					break;
				}

				if ((reg & OSCCTRL_STATUS_DFLLRCS) != 0 ||
				    (reg & OSCCTRL_STATUS_DFLLOOB) != 0 ||
				    (reg & OSCCTRL_STATUS_DFLLRDY) == 0) {
					timeout = 0;
					break;
				}
			}

			if (timeout == 0) {
				/*
				 * We have not managed to achieve lock.
				 * Restore the previous DFLL configuration.
				 */
				OSCCTRL->DFLLCTRLB.reg = ctrlb;
				sam_dfll_wait_sync(OSCCTRL_DFLLSYNC_DFLLCTRLB);

				/* No lock. */
				return 0;
			}
		}
	} else {
		/* Open loop. */
		OSCCTRL->DFLLCTRLB.reg &= ~(OSCCTRL_DFLLCTRLB_USBCRM |
		    OSCCTRL_DFLLCTRLB_MODE);
		sam_dfll_wait_sync(OSCCTRL_DFLLSYNC_DFLLCTRLB);
	}

	sam_dfll48m_frequency = src_freq * mul;
	return sam_dfll48m_frequency;
}

static void
sam_gclk_wait_sync(uint32_t mask)
{

	while ((GCLK->SYNCBUSY.reg & mask) != 0)
		;
}

unsigned int
sam_gclk0_mainck_config(sam_gclk_gen_src_t src, uint8_t cpudiv,
    sam_gclk_gen_divsel_t divsel, uint8_t div, unsigned int xin_freq)
{
	unsigned int src_freq, cpu_freq;
	uint32_t ws, genctrl;

	CLOCK_ASSERT(0, divsel == SAM_GCLK_GEN_DIVSEL_DIRECT ||
	    divsel == SAM_GCLK_GEN_DIVSEL_POWER_OF_TWO);

	/* Ensure the Fhs vs. Fcpu constraint is not violated. */
	CLOCK_ASSERT(0, cpudiv >= MCLK->HSDIV.reg);

	/* Ensure cpudiv is a power-of-two. */
	CLOCK_ASSERT(0, (cpudiv & (cpudiv - 1)) == 0);

	/* Fetch the frequency of the selected source. */
	if (src == SAM_GCLK_GEN_SRC_GCLKIN) {
		/* External input pin frequency supplied by caller. */
		src_freq = xin_freq;

		/* Max external GCLK input frequency is 50 MHz. */
		CLOCK_ASSERT(0, src_freq <= FREQ_MHZ(50));
	} else {
		/* Fetch the frequency of the selected source. */
		gclk_source_freq(src, &src_freq);
	}

	/* Construct the generator control register value. */
	genctrl = GCLK_GENCTRL_SRC((uint32_t)src) | GCLK_GENCTRL_GENEN;

	/* 'divsel' determines how the divider is interpreted. */
	if (divsel == SAM_GCLK_GEN_DIVSEL_DIRECT) {
		/*
		 * Straight arithmetic division of input frequency.
		 * Compute the output frequency, accounting for rounding.
		 */
		if (div > 1) {
			src_freq = (src_freq + (div / 2u)) / div;

			if ((div & 1) != 0) {
				/* If divisor is odd, improve duty cycle. */
				genctrl |= GCLK_GENCTRL_IDC;
			}
		} else {
			div = 0;
		}
	} else {
		/* Divide by 2^(div+1) */
		genctrl |= GCLK_GENCTRL_DIVSEL;

		/* No point dividing by more than 2^28 */
		CLOCK_ASSERT(0, div <= 28);

		/* Compute the output frequency. */
		src_freq >>= div & 0x1fu;
	}

	CLOCK_ASSERT(0, src_freq > 0);

	/* Compute the CPU clock speed. */
	cpu_freq = src_freq / cpudiv;

	/* Don't exceed the CPU's max of 120 MHz */
	CLOCK_ASSERT(0, cpu_freq <= FREQ_MHZ(120));

	/*
	 * Configure Flash wait states according to frequency.
	 * See datasheet section 54.11: NVM Characteristics.
	 * We will assume Vdd is > 2.7 volts.
	 */
	if (cpu_freq <= FREQ_MHZ(24))
		ws = NVMCTRL_CTRLA_RWS(0);
	else
	if (cpu_freq <= FREQ_MHZ(51))
		ws = NVMCTRL_CTRLA_RWS(1);
	else
	if (cpu_freq <= FREQ_MHZ(77))
		ws = NVMCTRL_CTRLA_RWS(2);
	else
	if (cpu_freq <= FREQ_MHZ(101))
		ws = NVMCTRL_CTRLA_RWS(3);
	else
	if (cpu_freq <= FREQ_MHZ(119))
		ws = NVMCTRL_CTRLA_RWS(4);
	else
		ws = NVMCTRL_CTRLA_RWS(5);

	if (cpu_freq >= SystemCoreClock) {
		/*
		 * Increasing core clock speed.
		 *
		 * Set Flash wait states and CPU divisor *before*
		 * changing clocks.
		 */
		NVMCTRL->CTRLA.reg = ws |
		    (NVMCTRL->CTRLA.reg & ~NVMCTRL_CTRLA_RWS_Msk);
		(void) NVMCTRL->CTRLA.reg;
		__DSB();
		__ISB();

		MCLK->CPUDIV.reg = cpudiv;
		(void) MCLK->CPUDIV.reg;
		__DSB();
		__ISB();
	}

	/* Configure the new settings for GCLK 0. */
	GCLK->GENCTRL[0].reg = genctrl;
	__DSB();
	__ISB();
	sam_gclk_wait_sync(GCLK_SYNCBUSY_GENCTRL_GCLK0);

	if (cpu_freq < SystemCoreClock) {
		/*
		 * Decreasing core clock speed.
		 *
		 * Set Flash wait states and CPU divisor *after*
		 * changing clocks.
		 */
		MCLK->CPUDIV.reg = cpudiv;
		(void) MCLK->CPUDIV.reg;
		__DSB();
		__ISB();

		NVMCTRL->CTRLA.reg = ws |
		    (NVMCTRL->CTRLA.reg & ~NVMCTRL_CTRLA_RWS_Msk);
		(void) NVMCTRL->CTRLA.reg;
		__DSB();
		__ISB();
	}

	SystemCoreClock = cpu_freq;
	sam_gclk_frequencies[0] = src_freq;

	return sam_gclk_frequencies[0];
}

unsigned int
sam_gclk_gen_alloc(sam_gclk_gen_type_t type)
{
	unsigned int gen, low;

	CLOCK_ASSERT(0, type == SAM_GCLK_GEN_TYPE_NORMAL ||
	    type == SAM_GCLK_GEN_TYPE_FAST);

	gen = ARRAY_SIZE(sam_gclk_frequencies) - 1;
	low = (gen + 1) / 2;

	if (type == SAM_GCLK_GEN_TYPE_FAST) {
		gen = low - 1;
		low = 1;
	}

	for ( ; gen >= low; gen--) {
		if ((GCLK->GENCTRL[gen].reg & GCLK_GENCTRL_GENEN) == 0)
			break;
	}

	CLOCK_ASSERT(0, gen >= low);
	CLOCK_ASSERT(0, sam_gclk_frequencies[gen] == 0);

	return gen;
}

int
sam_gclk_gen_free(unsigned int gen)
{

	CLOCK_ASSERT(-1, gen > 0);
	CLOCK_ASSERT(-1, gen < ARRAY_SIZE(sam_gclk_frequencies));
	CLOCK_ASSERT(-1, (GCLK->GENCTRL[gen].reg & GCLK_GENCTRL_GENEN) != 0);

	/* XXX: For extra paranoia, verify unused in all peripheral channels. */

	/* Shut it down. */
	GCLK->GENCTRL[gen].reg = 0;
	sam_gclk_wait_sync(GCLK_SYNCBUSY_GENCTRL_GCLK0 << gen);

	/* Mark the generator as 'off'. */
	sam_gclk_frequencies[gen] = 0;

	return 0;
}

unsigned int
sam_gclk_gen_config(unsigned int gen, sam_gclk_gen_src_t src,
    sam_gclk_gen_divsel_t divsel, uint16_t div, unsigned int xin_freq)
{
	unsigned int src_freq;
	uint32_t genctrl;

	CLOCK_ASSERT(0, gen > 0);
	CLOCK_ASSERT(0, gen == 1 || div <= 255u);
	CLOCK_ASSERT(0, gen < ARRAY_SIZE(sam_gclk_frequencies));
	CLOCK_ASSERT(0, (GCLK->GENCTRL[gen].reg & GCLK_GENCTRL_GENEN) == 0);
	CLOCK_ASSERT(0, divsel == SAM_GCLK_GEN_DIVSEL_DIRECT ||
	    divsel == SAM_GCLK_GEN_DIVSEL_POWER_OF_TWO);

	if (src == SAM_GCLK_GEN_SRC_GCLKIN) {
		/* External input pin frequency supplied by caller. */
		src_freq = xin_freq;

		/* Max external GCLK input frequency is 50 MHz. */
		CLOCK_ASSERT(0, src_freq <= FREQ_MHZ(50));
	} else {
		/* Fetch the frequency of the selected source. */
		gclk_source_freq(src, &src_freq);
	}

	CLOCK_ASSERT(0, src_freq > 0);

	/* Construct the generator control register value. */
	genctrl = GCLK_GENCTRL_SRC((uint32_t)src) | GCLK_GENCTRL_GENEN;

	/* 'divsel' determines how the divider is interpreted. */
	if (divsel == SAM_GCLK_GEN_DIVSEL_DIRECT) {
		/*
		 * Straight arithmetic division of input frequency.
		 * Compute the output frequency, accounting for rounding.
		 */
		if (div > 1) {
			src_freq = (src_freq + (div / 2u)) / div;

			if ((div & 1) != 0) {
				/* If divisor is odd, improve duty cycle. */
				genctrl |= GCLK_GENCTRL_IDC;
			}
		} else {
			div = 0;
		}
	} else {
		/* Divide by 2^(div+1) */
		genctrl |= GCLK_GENCTRL_DIVSEL;

		/* No point dividing by more than 2^28 */
		CLOCK_ASSERT(0, div <= 28);

		/* Compute the output frequency. */
		src_freq >>= div & 0x1fu;
	}

	/*
	 * Validate the output frequency. It must be:
	 *  a) Non-zero. XXX: Very slow clocks and rounding errors.
	 *  b) <= 200 MHz for generators 1 to 7.
	 *  c) <= 100 MHz for generators 8 and up.
	 */
	CLOCK_ASSERT(0, src_freq > 0);
	CLOCK_ASSERT(0,
	    src_freq <= ((gen <= 7) ? FREQ_MHZ(200) : FREQ_MHZ(100)));

	/* Finish constructing genctrl register value. */
	genctrl |= GCLK_GENCTRL_DIV((uint32_t)div);

	/* Crank it up. */
	GCLK->GENCTRL[gen].reg = genctrl;
	sam_gclk_wait_sync(GCLK_SYNCBUSY_GENCTRL_GCLK0 << gen);

	/* Record its frequency. */
	sam_gclk_frequencies[gen] = src_freq;

	return src_freq;
}

int
sam_gclk_gen_xout(unsigned int gen, int oe, int oov)
{
	uint32_t reg;

	CLOCK_ASSERT(-1, gen < ARRAY_SIZE(sam_gclk_frequencies));
	CLOCK_ASSERT(-1, sam_gclk_frequencies[gen] > 0);

	reg = GCLK->GENCTRL[gen].reg & ~(GCLK_GENCTRL_OE | GCLK_GENCTRL_OOV);
	CLOCK_ASSERT(-1, (reg & GCLK_GENCTRL_SRC_Msk) !=
	    GCLK_GENCTRL_SRC_GCLKIN);

	if (oe)
		reg |= GCLK_GENCTRL_OE;

	if (oov)
		reg |= GCLK_GENCTRL_OOV;

	GCLK->GENCTRL[gen].reg = reg;
	sam_gclk_wait_sync(GCLK_SYNCBUSY_GENCTRL_GCLK0 << gen);

	return 0;
}

unsigned int
sam_gclk_periph_chan_enable(unsigned int pchan, unsigned int gen)
{
	uint32_t reg;

	CLOCK_ASSERT(0, pchan < ARRAY_SIZE(GCLK->PCHCTRL));
	CLOCK_ASSERT(0, gen < ARRAY_SIZE(sam_gclk_frequencies));
	CLOCK_ASSERT(0, sam_gclk_frequencies[gen] > 0);

	reg = GCLK->PCHCTRL[pchan].reg;
	if ((reg & GCLK_PCHCTRL_CHEN) != 0) {
		/* Peripheral channel already enabled */
		if ((reg & GCLK_PCHCTRL_GEN_Msk) == GCLK_PCHCTRL_GEN(gen)) {
			/* Short-circuit if the source is already set. */
			goto done;
		}

		/* Disable the channel. */
		GCLK->PCHCTRL[pchan].reg &= ~GCLK_PCHCTRL_CHEN;
		(void) GCLK->PCHCTRL[pchan].reg;
	}

	/* Select the generator source. */
	GCLK->PCHCTRL[pchan].reg = GCLK_PCHCTRL_GEN(gen);
	(void) GCLK->PCHCTRL[pchan].reg;

	/* Enable the channel. */
	GCLK->PCHCTRL[pchan].reg |= GCLK_PCHCTRL_CHEN;
	(void) GCLK->PCHCTRL[pchan].reg;
	__DSB();
	__ISB();

 done:
	return sam_gclk_frequencies[gen];
}

int
sam_gclk_periph_chan_disable(unsigned int pchan)
{
	uint32_t reg;

	CLOCK_ASSERT(-1, pchan < ARRAY_SIZE(GCLK->PCHCTRL));

	reg = GCLK->PCHCTRL[pchan].reg;
	if ((reg & GCLK_PCHCTRL_CHEN) != 0) {
		/* Peripheral channel is enabled */

		/* Disable the channel. */
		GCLK->PCHCTRL[pchan].reg &= ~GCLK_PCHCTRL_CHEN;
		(void) GCLK->PCHCTRL[pchan].reg;
		__DSB();
		__ISB();
	}

	return 0;
}

static void
sam_dpll_wait_sync(OscctrlDpll *dpll, uint32_t mask)
{

	while ((dpll->DPLLSYNCBUSY.reg & mask) != 0)
		;
}

unsigned int
sam_dpll_config(sam_dpll_id_t id, sam_dpll_refclk_t refclk,
    unsigned int output_freq)
{
	OscctrlDpll *dpll = &OSCCTRL->Dpll[id];
	unsigned int input_freq, divider, fckr, ldr, ldrfrac, err_freq, gen;
	uint32_t reg, ref, erratum, timeout;

	CLOCK_ASSERT(0, id < ARRAY_SIZE(OSCCTRL->Dpll));
	CLOCK_ASSERT(0, output_freq >= DPLL_OUTCLK_MIN);
	CLOCK_ASSERT(0, output_freq <= DPLL_OUTCLK_MAX);

	switch (refclk) {
	case SAM_DPLL_REFCLK_XOSC0:
		ref = OSCCTRL_DPLLCTRLB_REFCLK_XOSC0;
		input_freq = sam_xosc_frequencies[0];
		goto find_divider;

	case SAM_DPLL_REFCLK_XOSC1:
		ref = OSCCTRL_DPLLCTRLB_REFCLK_XOSC1;
		input_freq = sam_xosc_frequencies[1];

	find_divider:
		/*
		 * Reference clock is from one of the XOSCn osillators, and
		 * will need to be divided down.
		 *
		 * Work out the refclk divider required to stay within the
		 * acceptable input range.
		 */
		for (divider = 0; divider < DPLL_DIV_MAX; divider++) {
			fckr = DPLL_FCKR(input_freq, divider);

			/* Input frequency is too low? */
			CLOCK_ASSERT(0, fckr >= DPLL_REFCLK_MIN);

			/* Input frequency within valid range? */
			if (fckr <= DPLL_REFCLK_MAX)
				break;
		}

		/* Bail if the input frequency is too high. */
		CLOCK_ASSERT(0, divider < DPLL_DIV_MAX);
		break;

	case SAM_DPLL_REFCLK_GCLK:
		/*
		 * Source is one of the clock generators.
		 */
		ref = OSCCTRL_DPLLCTRLB_REFCLK_GCLK;

		/* Determine our peripheral channel's clock generator. */
		gen = (id == SAM_DPLL_ID_1) ? OSCCTRL_GCLK_ID_FDPLL1 :
		    OSCCTRL_GCLK_ID_FDPLL0;
		reg = GCLK->PCHCTRL[gen].reg & GCLK_PCHCTRL_GEN_Msk;
		gen = (unsigned int)(reg >> GCLK_PCHCTRL_GEN_Pos);
		CLOCK_ASSERT(0, gen < ARRAY_SIZE(sam_gclk_frequencies));

		/* Fetch the frequency of the source. */
		input_freq = sam_gclk_frequencies[gen];

		CLOCK_ASSERT(0, input_freq >= DPLL_REFCLK_MIN);
		CLOCK_ASSERT(0, input_freq <= DPLL_REFCLK_MAX);

		/* Reference clock bypasses the divider. */
		fckr = input_freq;
		divider = 0;
		break;

	case SAM_DPLL_REFCLK_XOSC32:
		/*
		 * Source is the external 32K crystal oscillator.
		 */
		ref = OSCCTRL_DPLLCTRLB_REFCLK_XOSC32;

		CLOCK_ASSERT(0, OSC32KCTRL->XOSC32K.reg &
		    OSC32KCTRL_XOSC32K_ENABLE);

		/* Reference clock bypasses the divider. */
		fckr = input_freq = sam_xosc32k_frequency;
		divider = 0;
		break;

	default:
		ref = 0;
		fckr = 0;
		CLOCK_ASSERT(0, 0);
		break;
	}

	/* Work out LDR and LDRFRAC */
	ldr = DPLL_LDR(fckr, output_freq);
	ldrfrac = DPLL_LDRFRAC(fckr, output_freq);

	/*
	 * For divided refclks, where the DPLL output frequency is not an exact
	 * match for the required freqency, we may be able to reduce the error
	 * by trying different dividers.
	 */
	if ((refclk == SAM_DPLL_REFCLK_XOSC0 ||
	     refclk == SAM_DPLL_REFCLK_XOSC1) &&
	    (err_freq = output_freq - DPLL_OUTPUT(fckr, ldr, ldrfrac)) != 0) {
		unsigned int try_div;

		/*
		 * Try consecutive dividers until refclk is too low, or
		 * we find one which results in an error of zero.
		 */
		for (try_div = divider + 1; err_freq != 0; try_div++) {
			unsigned int try_ldr, try_ldrfrac, try_err;

			/* Calculate refclk. */
			fckr = DPLL_FCKR(input_freq, try_div);

			/* refclk is too low. */
			if (fckr < DPLL_REFCLK_MIN)
				break;

			/* Work out ldr/ldrfrac for this refclk */
			try_ldr = DPLL_LDR(fckr, output_freq);
			try_ldrfrac = DPLL_LDRFRAC(fckr, output_freq);

			/* What's the error now? */
			try_err = output_freq -
			    DPLL_OUTPUT(fckr, try_ldr, try_ldrfrac);

			/* Smaller than the previous nearest? */
			if (try_err < err_freq) {
				err_freq = try_err;
				ldr = try_ldr;
				ldrfrac = try_ldrfrac;
				divider = try_div;
			}
		}
	} else {
		err_freq = 0;
	}

	/* See Erratum 2.13.1 for fckr <= 400 KHz */
	if (fckr <= 400000u)
		erratum = OSCCTRL_DPLLCTRLB_WUF | OSCCTRL_DPLLCTRLB_LBYPASS;
	else
		erratum = 0;

	/*
	 * We now have all the DPLL parameters.
	 */

	dpll->DPLLRATIO.reg = OSCCTRL_DPLLRATIO_LDR(ldr) |
	    OSCCTRL_DPLLRATIO_LDRFRAC(ldrfrac);
	__DSB();
	__ISB();
	sam_dpll_wait_sync(dpll, OSCCTRL_DPLLSYNCBUSY_DPLLRATIO);

	dpll->DPLLCTRLB.reg = ref | erratum |
	    OSCCTRL_DPLLCTRLB_DIV(divider) |
	    OSCCTRL_DPLLCTRLB_LTIME_DEFAULT |
	    OSCCTRL_DPLLCTRLB_FILTER(2);
	__DSB();
	__ISB();

	dpll->DPLLCTRLA.reg = OSCCTRL_DPLLCTRLA_ENABLE |
	    OSCCTRL_DPLLCTRLA_RUNSTDBY;
	__DSB();
	__ISB();
	sam_dpll_wait_sync(dpll, OSCCTRL_DPLLSYNCBUSY_ENABLE);

	/* Wait for the DPLL to be ready. */
	timeout = 10000u;
	do {
		hw_cycle_delay(50);
		reg = dpll->DPLLSTATUS.reg;
		reg &= OSCCTRL_DPLLSTATUS_LOCK | OSCCTRL_DPLLSTATUS_CLKRDY;
	} while (--timeout &&
	    reg != (OSCCTRL_DPLLSTATUS_LOCK | OSCCTRL_DPLLSTATUS_CLKRDY));

	CLOCK_ASSERT(0, reg == (OSCCTRL_DPLLSTATUS_LOCK |
	    OSCCTRL_DPLLSTATUS_CLKRDY));
	if (timeout == 0) {
		dpll->DPLLCTRLA.reg = 0;
		sam_dpll_wait_sync(dpll, OSCCTRL_DPLLSYNCBUSY_ENABLE);
		return 0;
	}

	/* Selected DPLL is running. Record its actual freqency. */
	sam_dpll_frequencies[id] = output_freq - err_freq;

	return sam_dpll_frequencies[id];
}

/*
 * Look-up table to map a peripheral id (ID_xx) to the appropriate MCLK
 * bus register, and the specific bit number within that register.
 * Also handles peripherals which live on both APBn *and* AHB.
 */
#define	MCLK_PERIPH_BUS_INVALID		0u	/* Device does not exist. */
#define	MCLK_PERIPH_BUS_AHB		1u	/* Device lives on AHB. */
#define	MCLK_PERIPH_BUS_APBA		2u	/* Device lives on APBA. */
#define	MCLK_PERIPH_BUS_APBB		3u	/* Device lives on APBB. */
#define	MCLK_PERIPH_BUS_APBC		4u	/* Device lives on APBC. */
#define	MCLK_PERIPH_BUS_APBD		5u	/* Device lives on APBD. */
#define	MCLK_PERIPH_BUS_MULTI		6u	/* Device is on AHB & APBn */
#define	MCLK_PERIPH_ENTRY_BUS(e)	((e) >> 5)
#define	MCLK_PERIPH_ENTRY_MASK(e)	(1u << ((e) & 0x1fu))
#define	MCLK_PERIPH_ENTRY_INIT(bus,bit)	(((bus) << 5) | ((bit) & 0x1fu))
static const uint8_t mclk_periph_id_map[ID_PERIPH_COUNT] = {
	[ID_PAC]        = MCLK_PERIPH_ENTRY_INIT(MCLK_PERIPH_BUS_MULTI, 12),
	[ID_PM]         = MCLK_PERIPH_ENTRY_INIT(MCLK_PERIPH_BUS_APBA, 1),
	[ID_MCLK]       = MCLK_PERIPH_ENTRY_INIT(MCLK_PERIPH_BUS_APBA, 2),
	[ID_RSTC]       = MCLK_PERIPH_ENTRY_INIT(MCLK_PERIPH_BUS_APBA, 3),
	[ID_OSCCTRL]    = MCLK_PERIPH_ENTRY_INIT(MCLK_PERIPH_BUS_APBA, 4),
	[ID_OSC32KCTRL] = MCLK_PERIPH_ENTRY_INIT(MCLK_PERIPH_BUS_APBA, 5),
	[ID_SUPC]       = MCLK_PERIPH_ENTRY_INIT(MCLK_PERIPH_BUS_APBA, 6),
	[ID_GCLK]       = MCLK_PERIPH_ENTRY_INIT(MCLK_PERIPH_BUS_APBA, 7),
	[ID_WDT]        = MCLK_PERIPH_ENTRY_INIT(MCLK_PERIPH_BUS_APBA, 8),
	[ID_RTC]        = MCLK_PERIPH_ENTRY_INIT(MCLK_PERIPH_BUS_APBA, 9),
	[ID_EIC]        = MCLK_PERIPH_ENTRY_INIT(MCLK_PERIPH_BUS_APBA, 10),
	[ID_FREQM]      = MCLK_PERIPH_ENTRY_INIT(MCLK_PERIPH_BUS_APBA, 11),
	[ID_SERCOM0]    = MCLK_PERIPH_ENTRY_INIT(MCLK_PERIPH_BUS_APBA, 12),
	[ID_SERCOM1]    = MCLK_PERIPH_ENTRY_INIT(MCLK_PERIPH_BUS_APBA, 13),
	[ID_TC0]        = MCLK_PERIPH_ENTRY_INIT(MCLK_PERIPH_BUS_APBA, 14),
	[ID_TC1]        = MCLK_PERIPH_ENTRY_INIT(MCLK_PERIPH_BUS_APBA, 15),

	[ID_USB]        = MCLK_PERIPH_ENTRY_INIT(MCLK_PERIPH_BUS_MULTI, 10),
	[ID_DSU]        = MCLK_PERIPH_ENTRY_INIT(MCLK_PERIPH_BUS_MULTI, 4),
	[ID_NVMCTRL]    = MCLK_PERIPH_ENTRY_INIT(MCLK_PERIPH_BUS_MULTI, 6),
	[ID_CMCC]       = MCLK_PERIPH_ENTRY_INIT(MCLK_PERIPH_BUS_AHB, 8),
	[ID_PORT]       = MCLK_PERIPH_ENTRY_INIT(MCLK_PERIPH_BUS_APBB, 4),
	[ID_DMAC]       = MCLK_PERIPH_ENTRY_INIT(MCLK_PERIPH_BUS_AHB, 9),
	[ID_HMATRIX]    = MCLK_PERIPH_ENTRY_INIT(MCLK_PERIPH_BUS_INVALID, 0),
	[ID_EVSYS]      = MCLK_PERIPH_ENTRY_INIT(MCLK_PERIPH_BUS_APBB, 7),
	[ID_SERCOM2]    = MCLK_PERIPH_ENTRY_INIT(MCLK_PERIPH_BUS_APBB, 9),
	[ID_SERCOM3]    = MCLK_PERIPH_ENTRY_INIT(MCLK_PERIPH_BUS_APBB, 10),
	[ID_TCC0]       = MCLK_PERIPH_ENTRY_INIT(MCLK_PERIPH_BUS_APBB, 11),
	[ID_TCC1]       = MCLK_PERIPH_ENTRY_INIT(MCLK_PERIPH_BUS_APBB, 12),
	[ID_TC2]        = MCLK_PERIPH_ENTRY_INIT(MCLK_PERIPH_BUS_APBB, 13),
	[ID_TC3]        = MCLK_PERIPH_ENTRY_INIT(MCLK_PERIPH_BUS_APBB, 14),
	[ID_RAMECC]     = MCLK_PERIPH_ENTRY_INIT(MCLK_PERIPH_BUS_APBB, 16),

#ifdef ID_CAN0
	[ID_CAN0]       = MCLK_PERIPH_ENTRY_INIT(MCLK_PERIPH_BUS_AHB, 17),
#endif
#ifdef ID_CAN1
	[ID_CAN1]       = MCLK_PERIPH_ENTRY_INIT(MCLK_PERIPH_BUS_AHB, 18),
#endif
#ifdef ID_GMAC
	[ID_GMAC]       = MCLK_PERIPH_ENTRY_INIT(MCLK_PERIPH_BUS_MULTI, 14),
#endif
	[ID_TCC2]       = MCLK_PERIPH_ENTRY_INIT(MCLK_PERIPH_BUS_APBC, 3),
#ifdef ID_TCC3
	[ID_TCC3]       = MCLK_PERIPH_ENTRY_INIT(MCLK_PERIPH_BUS_APBC, 4),
#endif
#ifdef ID_TC4
	[ID_TC4]        = MCLK_PERIPH_ENTRY_INIT(MCLK_PERIPH_BUS_APBC, 5),
#endif
#ifdef ID_TC5
	[ID_TC5]        = MCLK_PERIPH_ENTRY_INIT(MCLK_PERIPH_BUS_APBC, 6),
#endif
	[ID_PDEC]       = MCLK_PERIPH_ENTRY_INIT(MCLK_PERIPH_BUS_APBC, 7),
	[ID_AC]         = MCLK_PERIPH_ENTRY_INIT(MCLK_PERIPH_BUS_APBC, 8),
	[ID_AES]        = MCLK_PERIPH_ENTRY_INIT(MCLK_PERIPH_BUS_APBC, 9),
	[ID_TRNG]       = MCLK_PERIPH_ENTRY_INIT(MCLK_PERIPH_BUS_APBC, 10),
	[ID_ICM]        = MCLK_PERIPH_ENTRY_INIT(MCLK_PERIPH_BUS_MULTI, 19),
	[ID_PUKCC]      = MCLK_PERIPH_ENTRY_INIT(MCLK_PERIPH_BUS_AHB, 20),
	[ID_QSPI]       = MCLK_PERIPH_ENTRY_INIT(MCLK_PERIPH_BUS_MULTI, 13),
	[ID_CCL]        = MCLK_PERIPH_ENTRY_INIT(MCLK_PERIPH_BUS_APBC, 14),

	[ID_SERCOM4]    = MCLK_PERIPH_ENTRY_INIT(MCLK_PERIPH_BUS_APBD, 0),
	[ID_SERCOM5]    = MCLK_PERIPH_ENTRY_INIT(MCLK_PERIPH_BUS_APBD, 1),
#ifdef ID_SERCOM6
	[ID_SERCOM6]    = MCLK_PERIPH_ENTRY_INIT(MCLK_PERIPH_BUS_APBD, 2),
#endif
#ifdef ID_SERCOM7
	[ID_SERCOM7]    = MCLK_PERIPH_ENTRY_INIT(MCLK_PERIPH_BUS_APBD, 3),
#endif
#ifdef ID_TCC4
	[ID_TCC4]       = MCLK_PERIPH_ENTRY_INIT(MCLK_PERIPH_BUS_APBD, 4),
#endif
#ifdef ID_TC6
	[ID_TC6]        = MCLK_PERIPH_ENTRY_INIT(MCLK_PERIPH_BUS_APBD, 5),
#endif
#ifdef ID_TC7
	[ID_TC7]        = MCLK_PERIPH_ENTRY_INIT(MCLK_PERIPH_BUS_APBD, 6),
#endif
	[ID_ADC0]       = MCLK_PERIPH_ENTRY_INIT(MCLK_PERIPH_BUS_APBD, 7),
	[ID_ADC1]       = MCLK_PERIPH_ENTRY_INIT(MCLK_PERIPH_BUS_APBD, 8),
#ifdef ID_DAC
	[ID_DAC]        = MCLK_PERIPH_ENTRY_INIT(MCLK_PERIPH_BUS_APBD, 9),
#endif
#ifdef ID_I2S
	[ID_I2S]        = MCLK_PERIPH_ENTRY_INIT(MCLK_PERIPH_BUS_APBD, 10),
#endif
	[ID_PCC]        = MCLK_PERIPH_ENTRY_INIT(MCLK_PERIPH_BUS_APBD, 11),

#ifdef ID_SDHC0
	[ID_SDHC0]      = MCLK_PERIPH_ENTRY_INIT(MCLK_PERIPH_BUS_AHB, 15),
#endif
#ifdef ID_SDHC1
	[ID_SDHC1]      = MCLK_PERIPH_ENTRY_INIT(MCLK_PERIPH_BUS_AHB, 16),
#endif
};

static volatile uint32_t *
mclk_periph_id(unsigned int id, uint32_t *mask,
    volatile uint32_t **reg2, uint32_t *mask2)
{
	volatile uint32_t *rv;
	uint8_t entry;

	CLOCK_ASSERT(NULL, id < ID_PERIPH_COUNT);

	entry = mclk_periph_id_map[id];

	CLOCK_ASSERT(NULL, MCLK_PERIPH_ENTRY_BUS(entry) !=
	    MCLK_PERIPH_BUS_INVALID);

	*mask = MCLK_PERIPH_ENTRY_MASK(entry);
	*mask2 = 0;
	*reg2 = NULL;
	rv = NULL;

	switch (MCLK_PERIPH_ENTRY_BUS(entry)) {
	case MCLK_PERIPH_BUS_AHB:
		rv = &MCLK->AHBMASK.reg;
		break;

	case MCLK_PERIPH_BUS_APBA:
		rv = &MCLK->APBAMASK.reg;
		break;

	case MCLK_PERIPH_BUS_APBB:
		rv = &MCLK->APBBMASK.reg;
		break;

	case MCLK_PERIPH_BUS_APBC:
		rv = &MCLK->APBCMASK.reg;
		break;

	case MCLK_PERIPH_BUS_APBD:
		rv = &MCLK->APBDMASK.reg;
		break;

	case MCLK_PERIPH_BUS_MULTI:
		/*
		 * Peripheral has two clock control bits - one for AHB and
		 * another for APB[A-D].
		 * The 'bit' encoded in MCLK_PERIPH_ENTRY_MASK() is for AHB,
		 * while the APB bit is (1u << (id % 32)). The APB mask
		 * register is given by id / 32.
		 */
		 *reg2 = &MCLK->AHBMASK.reg;
		 *mask2 = MCLK_PERIPH_ENTRY_MASK(entry);
		 *mask = 1u << (id % 32u);
		switch (id / 32u) {
		case 0:
			rv = &MCLK->APBAMASK.reg;
			break;
		case 1:
			rv = &MCLK->APBBMASK.reg;
			break;
		case 2:
			rv = &MCLK->APBCMASK.reg;
			break;
		case 3:
			rv = &MCLK->APBDMASK.reg;
			break;
		default:
			CLOCK_ASSERT(NULL, 0);
		}
		break;

	default:
		CLOCK_ASSERT(NULL, 0);
	}

	return rv;
}

int
sam_periph_clock_status(unsigned int id)
{
	volatile uint32_t *mr1, *mr2;
	uint32_t mask1, mask2;
	int rv;

	mr1 = mclk_periph_id(id, &mask1, &mr2, &mask2);
	CLOCK_ASSERT(-1, mr1 != NULL);

	rv = (*mr1 & mask1) != 0;

	if (mr2 != NULL)
		rv = rv && (*mr2 & mask2) != 0;

	return rv;
}

int
sam_periph_clock_enable(unsigned int id)
{
	volatile uint32_t *mr1, *mr2;
	uint32_t mask1, mask2;

	mr1 = mclk_periph_id(id, &mask1, &mr2, &mask2);
	CLOCK_ASSERT(-1, mr1 != NULL);

	*mr1 |= mask1;
	if (mr2 != NULL)
		*mr2 |= mask2;
	__DSB();
	__ISB();

	return 0;
}

int
sam_periph_clock_disable(unsigned int id)
{
	volatile uint32_t *mr1, *mr2;
	uint32_t mask1, mask2;

	mr1 = mclk_periph_id(id, &mask1, &mr2, &mask2);
	CLOCK_ASSERT(-1, mr1 != NULL);

	*mr1 &= ~mask1;
	if (mr2 != NULL)
		*mr2 &= ~mask2;
	__DSB();
	__ISB();

	return 0;
}

void
sam_clock_dump(void)
{

	printf("%23s %lu\n", "SystemCoreClock", SystemCoreClock);
	printf("%23s %u\n", "sam_dfll48m_frequency", sam_dfll48m_frequency);
	printf("%23s %u\n", "sam_xosc32k_frequency", sam_xosc32k_frequency);
	printf("%23s %u\n", "sam_xosc_frequencies[0]", sam_xosc_frequencies[0]);
	printf("%23s %u\n", "sam_xosc_frequencies[1]", sam_xosc_frequencies[1]);
	printf("%23s %u\n", "sam_dpll_frequencies[0]", sam_dpll_frequencies[0]);
	printf("%23s %u\n", "sam_dpll_frequencies[1]", sam_dpll_frequencies[1]);

	for (unsigned int i = 0; i < ARRAY_SIZE(sam_gclk_frequencies); i++) {
		printf("%19s[%u] %u\n", "sam_gclk_frequencies", i,
		    sam_gclk_frequencies[i]);
	}
}
