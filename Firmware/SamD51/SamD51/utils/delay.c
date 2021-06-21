// DOM-IGNORE-BEGIN
/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
 */
// DOM-IGNORE-END

#include <sam.h>
#include <stdio.h>
#include "delay.h"

static inline uint32_t _get_cycles_for_ms_internal(const uint16_t ms, const uint32_t freq, const uint8_t power);
static uint32_t _get_cycles_for_ms(const uint16_t ms);
static void _delay_cycles(uint32_t cycles);

#if CONF_CPU_FREQUENCY < 1000
#define CPU_FREQ_POWER 3
#elif CONF_CPU_FREQUENCY < 10000
#define CPU_FREQ_POWER 4
#elif CONF_CPU_FREQUENCY < 100000
#define CPU_FREQ_POWER 5
#elif CONF_CPU_FREQUENCY < 1000000
#define CPU_FREQ_POWER 6
#elif CONF_CPU_FREQUENCY < 10000000
#define CPU_FREQ_POWER 7
#elif CONF_CPU_FREQUENCY < 100000000
#define CPU_FREQ_POWER 8
#elif CONF_CPU_FREQUENCY < 1000000000
#define CPU_FREQ_POWER 9
#endif

static inline uint32_t _get_cycles_for_ms_internal(const uint16_t ms, const uint32_t freq, const uint8_t power)
{
	switch (power) {
		case 9:
		return (ms * (freq / 1000000) + 2) / 3 * 1000;
		case 8:
		return (ms * (freq / 100000) + 2) / 3 * 100;
		case 7:
		return (ms * (freq / 10000) + 2) / 3 * 10;
		case 6:
		return (ms * (freq / 1000) + 2) / 3;
		case 5:
		return (ms * (freq / 100) + 29) / 30;
		case 4:
		return (ms * (freq / 10) + 299) / 300;
		default:
		return (ms * (freq / 1) + 2999) / 3000;
	}
}

static uint32_t _get_cycles_for_ms(const uint16_t ms)
{
	return _get_cycles_for_ms_internal(ms, CONF_CPU_FREQUENCY, CPU_FREQ_POWER);
}

__attribute__((section(".ramfunc")))
static void _delay_cycles(uint32_t cycles)
{
	cycles /= 4;

	asm volatile (
	"__delay:\n"
	"subs %[cycles], %[cycles], #1 \n"
	"nop \n"
	"bne __delay\n"
	:[cycles] "+l"(cycles)
	);
}

void delay_ms(const uint16_t ms) {
	_delay_cycles(_get_cycles_for_ms(ms));
}

void delay_cycles(const uint32_t cycles) {
	_delay_cycles(cycles);
}