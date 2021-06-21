/*
 * VT-69.c
 *
 * Created: 6/10/2021 11:07:04 AM
 * Author : bench
 */ 

#include "sam.h"

#include <stdio.h>

// Constants for Clock generators
#define GENERIC_CLOCK_GENERATOR_MAIN		(0u)
#define GENERIC_CLOCK_GENERATOR_XOSC32K		(3u)
#define GENERIC_CLOCK_GENERATOR_48M			(1u)
#define GENERIC_CLOCK_GENERATOR_48M_SYNC	GCLK_SYNCBUSY_GENCTRL1
#define GENERIC_CLOCK_GENERATOR_100M		(2u)
#define GENERIC_CLOCK_GENERATOR_100M_SYNC	GCLK_SYNCBUSY_GENCTRL2
#define GENERIC_CLOCK_GENERATOR_12M			(4u)
#define GENERIC_CLOCK_GENERATOR_12M_SYNC	GCLK_SYNCBUSY_GENCTRL4

//USE DPLL0 for 120MHZ
#define MAIN_CLOCK_SOURCE				  GCLK_GENCTRL_SRC_DPLL0

#define GENERIC_CLOCK_GENERATOR_1M		  (5u)



#define GENERIC_CLOCK_GENERATOR_OSC32K    (1u)
#define GENERIC_CLOCK_GENERATOR_OSCULP32K (2u) /* Initialized at reset for WDT */
#define GENERIC_CLOCK_GENERATOR_OSC8M     (3u)
// Constants for Clock multiplexers
#define GENERIC_CLOCK_MULTIPLEXER_DFLL48M (0u)

#define F_CPU 120000000

void SystemInit(void);

int main(void)
{
	
	SystemInit();
	
    /* Replace with your application code */
    while (1) 
    {
		
		
    }
}

void SystemInit(void)
{
		//Set NVM Read Wait States to 0
		NVMCTRL->CTRLA.reg |= NVMCTRL_CTRLA_RWS(0);
	
		//Enable XOSC32K clock (External on-board 32.768Hz oscillator)
		OSC32KCTRL->XOSC32K.reg = OSC32KCTRL_XOSC32K_ENABLE | OSC32KCTRL_XOSC32K_EN32K | OSC32KCTRL_XOSC32K_EN32K | OSC32KCTRL_XOSC32K_CGM_XT | OSC32KCTRL_XOSC32K_XTALEN;
		while( (OSC32KCTRL->STATUS.reg & OSC32KCTRL_STATUS_XOSC32KRDY) == 0 ){
			 /* Wait for oscillator to be ready */
		}
	
		//software reset 
		GCLK->CTRLA.bit.SWRST = 1;
		while ( GCLK->SYNCBUSY.reg & GCLK_SYNCBUSY_SWRST ){
			  /* wait for reset to complete */
		}
	
		//	Put XOSC32K as source of Generic Clock Generator 3
		GCLK->GENCTRL[GENERIC_CLOCK_GENERATOR_XOSC32K].reg = GCLK_GENCTRL_SRC(GCLK_GENCTRL_SRC_XOSC32K) | //generic clock gen 3
		GCLK_GENCTRL_GENEN;
	
		while ( GCLK->SYNCBUSY.reg & GCLK_SYNCBUSY_GENCTRL3 ){
			  /* Wait for synchronization */
		}
	
		 /* ----------------------------------------------------------------------------------------------
		 * 3) Put OSCULP32K as source for Generic Clock Generator 0
		 */
		GCLK->GENCTRL[0].reg = GCLK_GENCTRL_SRC(GCLK_GENCTRL_SRC_OSCULP32K) | GCLK_GENCTRL_GENEN;
	
	  /* ----------------------------------------------------------------------------------------------
	   * 4) Enable DFLL48M clock
	   */

	  while ( GCLK->SYNCBUSY.reg & GCLK_SYNCBUSY_GENCTRL0 ){
		/* Wait for synchronization */
	  }
  
	 /* DFLL Configuration in Open Loop mode */
 
	 OSCCTRL->DFLLCTRLA.reg = 0;
	 //GCLK->PCHCTRL[OSCCTRL_GCLK_ID_DFLL48].reg = (1 << GCLK_PCHCTRL_CHEN_Pos) | GCLK_PCHCTRL_GEN(GCLK_PCHCTRL_GEN_GCLK3_Val);
 
	 OSCCTRL->DFLLMUL.reg = OSCCTRL_DFLLMUL_CSTEP( 0x1 ) |
	 OSCCTRL_DFLLMUL_FSTEP( 0x1 ) |
	 OSCCTRL_DFLLMUL_MUL( 0 );
 
	 while ( OSCCTRL->DFLLSYNC.reg & OSCCTRL_DFLLSYNC_DFLLMUL )
	 {
		 /* Wait for synchronization */
	 }
 
	 OSCCTRL->DFLLCTRLB.reg = 0;
	 while ( OSCCTRL->DFLLSYNC.reg & OSCCTRL_DFLLSYNC_DFLLCTRLB )
	 {
		 /* Wait for synchronization */
	 }
 
	 OSCCTRL->DFLLCTRLA.reg |= OSCCTRL_DFLLCTRLA_ENABLE;
	 while ( OSCCTRL->DFLLSYNC.reg & OSCCTRL_DFLLSYNC_ENABLE )
	 {
		 /* Wait for synchronization */
	 }
 
	 OSCCTRL->DFLLVAL.reg = OSCCTRL->DFLLVAL.reg;
	 while( OSCCTRL->DFLLSYNC.bit.DFLLVAL );
 
	 OSCCTRL->DFLLCTRLB.reg = OSCCTRL_DFLLCTRLB_WAITLOCK |
	 OSCCTRL_DFLLCTRLB_CCDIS | OSCCTRL_DFLLCTRLB_USBCRM ;
 
	 while ( !OSCCTRL->STATUS.bit.DFLLRDY )
	 {
		 /* Wait for synchronization */
	 }
 
	 GCLK->GENCTRL[GENERIC_CLOCK_GENERATOR_1M].reg = GCLK_GENCTRL_SRC(GCLK_GENCTRL_SRC_DFLL_Val) | GCLK_GENCTRL_GENEN | GCLK_GENCTRL_DIV(48u);
 
	 while ( GCLK->SYNCBUSY.bit.GENCTRL5 ){
		 /* Wait for synchronization */
	 }
 
	 /* ------------------------------------------------------------------------
	  * Set up the PLLs
	  */
	
	  //PLL0 is 120MHz
	  GCLK->PCHCTRL[OSCCTRL_GCLK_ID_FDPLL0].reg = (1 << GCLK_PCHCTRL_CHEN_Pos) | GCLK_PCHCTRL_GEN(GCLK_PCHCTRL_GEN_GCLK5_Val);
  
	  // This rounds to nearest full-MHz increment; not currently using frac
	  OSCCTRL->Dpll[0].DPLLRATIO.reg = OSCCTRL_DPLLRATIO_LDRFRAC(0x00) | OSCCTRL_DPLLRATIO_LDR((F_CPU - 500000) / 1000000);
  
	  while(OSCCTRL->Dpll[0].DPLLSYNCBUSY.bit.DPLLRATIO);
  
	  //MUST USE LBYPASS DUE TO BUG IN REV A OF SAMD51
	  OSCCTRL->Dpll[0].DPLLCTRLB.reg = OSCCTRL_DPLLCTRLB_REFCLK_GCLK | OSCCTRL_DPLLCTRLB_LBYPASS;
  
	  OSCCTRL->Dpll[0].DPLLCTRLA.reg = OSCCTRL_DPLLCTRLA_ENABLE;
  
	  while( OSCCTRL->Dpll[0].DPLLSTATUS.bit.CLKRDY == 0 || OSCCTRL->Dpll[0].DPLLSTATUS.bit.LOCK == 0 );
  
	  //PLL1 is 100MHz
	  GCLK->PCHCTRL[OSCCTRL_GCLK_ID_FDPLL1].reg = (1 << GCLK_PCHCTRL_CHEN_Pos) | GCLK_PCHCTRL_GEN(GCLK_PCHCTRL_GEN_GCLK5_Val);
  
	  OSCCTRL->Dpll[1].DPLLRATIO.reg = OSCCTRL_DPLLRATIO_LDRFRAC(0x00) | OSCCTRL_DPLLRATIO_LDR(99); //100 Mhz
  
	  while(OSCCTRL->Dpll[1].DPLLSYNCBUSY.bit.DPLLRATIO);
  
	  //MUST USE LBYPASS DUE TO BUG IN REV A OF SAMD51
	  OSCCTRL->Dpll[1].DPLLCTRLB.reg = OSCCTRL_DPLLCTRLB_REFCLK_GCLK | OSCCTRL_DPLLCTRLB_LBYPASS;
  
	  OSCCTRL->Dpll[1].DPLLCTRLA.reg = OSCCTRL_DPLLCTRLA_ENABLE;
  
	  while( OSCCTRL->Dpll[1].DPLLSTATUS.bit.CLKRDY == 0 || OSCCTRL->Dpll[1].DPLLSTATUS.bit.LOCK == 0 );
  
  
	  /* ------------------------------------------------------------------------
	  * Set up the peripheral clocks
	  */
  
	  //48MHZ CLOCK FOR USB AND STUFF
	  GCLK->GENCTRL[GENERIC_CLOCK_GENERATOR_48M].reg = GCLK_GENCTRL_SRC(GCLK_GENCTRL_SRC_DFLL_Val) |
		GCLK_GENCTRL_IDC |
		//GCLK_GENCTRL_OE |
		GCLK_GENCTRL_GENEN;
  
	  while ( GCLK->SYNCBUSY.reg & GENERIC_CLOCK_GENERATOR_48M_SYNC)
		{
		  /* Wait for synchronization */
		}
  
	  //100MHZ CLOCK FOR OTHER PERIPHERALS
	  GCLK->GENCTRL[GENERIC_CLOCK_GENERATOR_100M].reg = GCLK_GENCTRL_SRC(GCLK_GENCTRL_SRC_DPLL1_Val) |
		GCLK_GENCTRL_IDC |
		//GCLK_GENCTRL_OE |
		GCLK_GENCTRL_GENEN;
  
	  while ( GCLK->SYNCBUSY.reg & GENERIC_CLOCK_GENERATOR_100M_SYNC)
		{
		  /* Wait for synchronization */
		}
  
	  //12MHZ CLOCK FOR DAC
	  GCLK->GENCTRL[GENERIC_CLOCK_GENERATOR_12M].reg = GCLK_GENCTRL_SRC(GCLK_GENCTRL_SRC_DFLL_Val) |
		GCLK_GENCTRL_IDC |
		GCLK_GENCTRL_DIV(4) |
		//GCLK_GENCTRL_DIVSEL |
		//GCLK_GENCTRL_OE |
		GCLK_GENCTRL_GENEN;
  
	  while ( GCLK->SYNCBUSY.reg & GENERIC_CLOCK_GENERATOR_12M_SYNC)
		{
		  /* Wait for synchronization */
		}
  
	  /*---------------------------------------------------------------------
	   * Set up main clock
	   */
  
	  GCLK->GENCTRL[GENERIC_CLOCK_GENERATOR_MAIN].reg = GCLK_GENCTRL_SRC(MAIN_CLOCK_SOURCE) |
		GCLK_GENCTRL_IDC |
		//GCLK_GENCTRL_OE |
		GCLK_GENCTRL_GENEN;
  

	  while ( GCLK->SYNCBUSY.reg & GCLK_SYNCBUSY_GENCTRL0 )
		{
		  /* Wait for synchronization */
		}
  
	  MCLK->CPUDIV.reg = MCLK_CPUDIV_DIV_DIV1;
  
	  /* Use the LDO regulator by default */
	  SUPC->VREG.bit.SEL = 0; 
  
	  /*---------------------------------------------------------------------
	   * Start up the "Debug Watchpoint and Trace" unit, so that we can use
	   * it's 32bit cycle counter for timing.
	   */
	  CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
	  DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;

	  /* ----------------------------------------------------------------------------------------------
	   * 5) Load AC factory calibration values
	   */

	  uint32_t bias0 = (*((uint32_t *)AC_FUSES_BIAS0_ADDR) & AC_FUSES_BIAS0_Msk) >> AC_FUSES_BIAS0_Pos;
	  AC->CALIB.reg = AC_CALIB_BIAS0(bias0);

	//USB Calibration
	uint32_t usbtransn = (*((uint32_t *)USB_FUSES_TRANSN_ADDR) & USB_FUSES_TRANSN_Msk) >> USB_FUSES_TRANSN_Pos;
	uint32_t usbtransp = (*((uint32_t *)USB_FUSES_TRANSP_ADDR) & USB_FUSES_TRANSP_Msk) >> USB_FUSES_TRANSP_Pos;
	uint32_t usbtrim = (*((uint32_t *)USB_FUSES_TRIM_ADDR) & USB_FUSES_TRIM_Msk) >> USB_FUSES_TRIM_Pos;
	USB->DEVICE.PADCAL.reg = USB_PADCAL_TRIM(usbtrim)
	| USB_PADCAL_TRANSN(usbtransn)
	| USB_PADCAL_TRANSP(usbtransp);
	
}
