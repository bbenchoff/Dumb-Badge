/*
 * CPPproject.cpp
 *
 * Created: 1/21/2020 8:25:42 PM
 * Author : bench
 */ 


#include "sam.h"
#include <UTFT.h>
#include <math.h>
#include "definitions.h"

extern uint8_t SmallFont[];

UTFT myGLCD(NT35510_16, 46, 47, 44, 2, NOTINUSE);   //(byte model, int RS, int WR, int CS, int RST, int SER)

void AppInit(void);			// Application Hardware/Software Initialization
void ClocksInit(void);		// Configure Clock, Wait States and synch. Bus Clocks for 48MHz operation
void delay_ms(int delay_time);

int main(void)
{
	/* Initialize the SAM system - auto-generated CMSIS compliant function */
	/* NOT USED - Use AppInit() for all Hardware/System initialization */
	SystemInit();
	
	/* Application hardware and software initialization */
	AppInit();
	
	// Setup the LCD
	myGLCD.InitLCD();
	myGLCD.setFont(SmallFont);
	
    /* Replace with your application code */
    while (1) 
    {
		  int buf[798];
		  int x, x2;
		  int y, y2;
		  int r;
		  // Clear the screen and draw the frame
		  myGLCD.clrScr();
		  myGLCD.fillRect(0, 466, 799, 479);
		  myGLCD.setColor(255, 255, 255);
		  myGLCD.setBackColor(255, 0, 0);
		  myGLCD.print("* EastRising Technology *", CENTER, 1);
		  myGLCD.setBackColor(64, 64, 64);
		  myGLCD.setColor(255,255,0);
		  myGLCD.print(" http://www.buydisplay.com", CENTER, 467);

		  myGLCD.setColor(0, 0, 255);
		  myGLCD.drawRect(0, 14, 799, 465);

		  // Draw crosshairs
		  myGLCD.setColor(0, 0, 255);
		  myGLCD.setBackColor(0, 0, 0);
		  myGLCD.drawLine(399, 15, 399, 464);
		  myGLCD.drawLine(1, 239, 798, 239);
		  for (int i=9; i<790; i+=10)
		  myGLCD.drawLine(i, 237, i, 242);
		  for (int i=19; i<470; i+=10)
		  myGLCD.drawLine(397, i, 402, i);

		  // Draw sin-, cos- and tan-lines
		  myGLCD.setColor(0,255,255);
		  myGLCD.print("Sin", 5, 15);
		  for (int i=1; i<798; i++)
		  {
			  myGLCD.drawPixel(i,239+(sin(((i*1.13)*3.14)/180)*200));
		  }
		  
		  myGLCD.setColor(255,0,0);
		  myGLCD.print("Cos", 5, 27);
		  for (int i=1; i<798; i++)
		  {
			  myGLCD.drawPixel(i,239+(cos(((i*1.13)*3.14)/180)*200));
		  }

		  myGLCD.setColor(255,255,0);
		  myGLCD.print("Tan", 5, 39);
		  for (int i=1; i<798; i++)
		  {
			  myGLCD.drawPixel(i,239+(tan(((i*0.9)*3.14)/180)));
		  }

		  delay_ms(2000);

		  myGLCD.setColor(0,0,0);
		  myGLCD.fillRect(1,15,798,464);
		  myGLCD.setColor(0, 0, 255);
		  myGLCD.setBackColor(0, 0, 0);
		  myGLCD.drawLine(399, 15, 399, 464);
		  myGLCD.drawLine(1, 239, 798, 239);

		  // Draw a moving sinewave
		  x=1;
		  for (int i=1; i<(798*20); i++)
		  {
			  x++;
			  if (x==799)
			  x=1;
			  if (i>799)
			  {
				  if ((x==399)||(buf[x-1]==239))
				  myGLCD.setColor(0,0,255);
				  else
				  myGLCD.setColor(0,0,0);
				  myGLCD.drawPixel(x,buf[x-1]);
			  }
			  myGLCD.setColor(0,255,255);
			  y=239+(sin(((i*1.65)*3.14)/180)*(200-(i / 100)));
			  myGLCD.drawPixel(x,y);
			  buf[x-1]=y;
		  }

		  delay_ms(2000);
		  
		  myGLCD.setColor(0,0,0);
		  myGLCD.fillRect(1,15,798,464);

		  // Draw some random filled rectangles
		  for (int i=0; i<50; i++)
		  {
			  myGLCD.setColor(random(255), random(255), random(255));
			  x=2+random(746);
			  y=16+random(397);
			  x2=x+50;
			  y2=y+50;
			  myGLCD.fillRect(x, y, x2, y2);
		  }

		  delay_ms(2000);
		  
		  myGLCD.setColor(0,0,0);
		  myGLCD.fillRect(1,15,798,464);

		  // Draw some random filled, rounded rectangles
		  for (int i=0; i<50; i++)
		  {
			  myGLCD.setColor(random(255), random(255), random(255));
			  x=2+random(746);
			  y=16+random(397);
			  x2=x+50;
			  y2=y+50;
			  myGLCD.fillRoundRect(x, y, x2, y2);
		  }
		  
		  delay_ms(2000);
		  
		  myGLCD.setColor(0,0,0);
		  myGLCD.fillRect(1,15,798,464);

		  // Draw some random filled circles
		  for (int i=0; i<50; i++)
		  {
			  myGLCD.setColor(random(255), random(255), random(255));
			  x=27+random(746);
			  y=41+random(397);
			  myGLCD.fillCircle(x, y, 25);
		  }
		  
		  delay_ms(2000);
		  
		  myGLCD.setColor(0,0,0);
		  myGLCD.fillRect(1,15,798,464);

		  // Draw some lines in a pattern
		  myGLCD.setColor (255,0,0);
		  for (int i=15; i<463; i+=5)
		  {
			  myGLCD.drawLine(1, i, (i*1.66)-10, 463);
		  }
		  myGLCD.setColor (255,0,0);
		  for (int i=463; i>15; i-=5)
		  {
			  myGLCD.drawLine(798, i, (i*1.66)+30, 15);
		  }
		  myGLCD.setColor (0,255,255);
		  for (int i=463; i>15; i-=5)
		  {
			  myGLCD.drawLine(1, i, 770-(i*1.66), 15);
		  }
		  myGLCD.setColor (0,255,255);
		  for (int i=15; i<463; i+=5)
		  {
			  myGLCD.drawLine(798, i, 810-(i*1.66), 463);
		  }
		  
		  delay_ms(2000);
		  
		  myGLCD.setColor(0,0,0);
		  myGLCD.fillRect(1,15,798,464);

		  // Draw some random circles
		  for (int i=0; i<250; i++)
		  {
			  myGLCD.setColor(random(255), random(255), random(255));
			  x=32+random(736);
			  y=45+random(386);
			  r=random(30);
			  myGLCD.drawCircle(x, y, r);
		  }

		  delay_ms(2000);
		  
		  myGLCD.setColor(0,0,0);
		  myGLCD.fillRect(1,15,798,464);

		  // Draw some random rectangles
		  for (int i=0; i<250; i++)
		  {
			  myGLCD.setColor(random(255), random(255), random(255));
			  x=2+random(796);
			  y=16+random(447);
			  x2=2+random(796);
			  y2=16+random(447);
			  myGLCD.drawRect(x, y, x2, y2);
		  }

		  delay_ms(2000);
		  
		  myGLCD.setColor(0,0,0);
		  myGLCD.fillRect(1,15,798,464);

		  // Draw some random rounded rectangles
		  for (int i=0; i<250; i++)
		  {
			  myGLCD.setColor(random(255), random(255), random(255));
			  x=2+random(796);
			  y=16+random(447);
			  x2=2+random(796);
			  y2=16+random(447);
			  myGLCD.drawRoundRect(x, y, x2, y2);
		  }

		  delay_ms(2000);
		  
		  myGLCD.setColor(0,0,0);
		  myGLCD.fillRect(1,15,798,464);

		  for (int i=0; i<250; i++)
		  {
			  myGLCD.setColor(random(255), random(255), random(255));
			  x=2+random(796);
			  y=16+random(447);
			  x2=2+random(796);
			  y2=16+random(447);
			  myGLCD.drawLine(x, y, x2, y2);
		  }

		  delay_ms(2000);
		  
		  myGLCD.setColor(0,0,0);
		  myGLCD.fillRect(1,15,798,464);

		  for (int i=0; i<10000; i++)
		  {
			  myGLCD.setColor(random(255), random(255), random(255));
			  myGLCD.drawPixel(2+random(796), 16+random(447));
		  }

		  delay_ms(2000);

		  myGLCD.fillScr(0, 0, 255);
		  myGLCD.setColor(255, 0, 0);
		  myGLCD.fillRoundRect(320, 190, 479, 289);
		  
		  myGLCD.setColor(255, 255, 255);
		  myGLCD.setBackColor(255, 0, 0);
		  myGLCD.print("www.buydisplay.com", CENTER, 195);
		  myGLCD.print("That's it!", CENTER, 213);
		  myGLCD.print("Restarting in a", CENTER, 239);
		  myGLCD.print("few seconds...", CENTER, 252);
		  
		  myGLCD.setColor(0, 255, 0);
		  myGLCD.setBackColor(0, 0, 255);
		  myGLCD.print("Runtime: (msecs)", CENTER, 450);
		  myGLCD.printNumI(millis(), CENTER, 465);
		  
		  delay_ms(10000);
		
    }
}

/*******************************************************************************
 * Function:        void AppInit(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This routine takes care of all of the 1-time hardware/software
 *                  initialization that is required.
 *
 * Note:
 *
 ******************************************************************************/
void AppInit(void){
	
	/*	Clock initialization (CPU, AHB, APBx, Asynchronous Peripheral Clocks)
		The System RC Oscillator (RCSYS) provides the source for the main clock
		at chip startup. It is set to 1MHz.
		
		Add code here to change the system clock
	*/
	ClocksInit();
	
	// Assign the LED0 pin as OUTPUT
	PORT->Group[LED0_PORT].DIRSET.reg = LED0_PIN_MASK;
	// Set the LED0 pin level, i.e. put to 3.3V -> this light off the LED
	PORT->Group[LED0_PORT].OUTSET.reg = LED0_PIN_MASK;

	// Configure SysTick to trigger an ISR every millisecond using a 48MHz CPU Clock
	SysTick->CTRL = 0;					// Disable SysTick
	SysTick->LOAD = 47999UL;			// Set reload register for 1mS interrupts
	NVIC_SetPriority(SysTick_IRQn, 3);	// Set interrupt priority to least urgency
	SysTick->VAL = 0;					// Reset the SysTick counter value
	SysTick->CTRL = 0x00000007;			// Enable SysTick, Enable SysTick Exceptions, Use CPU Clock
	NVIC_EnableIRQ(SysTick_IRQn);		// Enable SysTick Interrupt
	
	
} // AppInit()


/*******************************************************************************
 * Function:        void ClocksInit(void)
 *
 * PreCondition:    OSC8M Enabled, CPU and Synch. Bus Clocks at reset condition (1 MHz)
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    CPU and Synchronous Bus Clocks at 48 MHz.
 *					8 MHz Asynchronous Peripheral Clock available on GCLK 3
 *					Flash Read Wait States Adjusted Accordingly.
 *					GCLK_MAIN output on PA28
 *
 * Overview:
 *
 *	Configure a 48 MHz Synchronous Clock for (CPU, AHB, APBx) & Set Flash Wait States for 48MHz
 *		- Use DFLL48M Source (Closed Loop, using external 32.768 kHz crystal)
 *  Configure a 8 MHz Asynchronous Clock on Clock Generator 3 for use with peripherals. 
 *		- Use OSC8M Source
 *
 *	At reset:
 *	- OSC8M clock source is enabled with a divider by 8 (1MHz).
 *	- Generic Clock Generator 0 (GCLKMAIN) is using OSC8M as source.
 *	- OSCULP32K is enabled and fed to Generic Clock Generator 2
 *	- 0 Flash wait states (NVCTRL->CTRLB.RWS = 0)
 *	- Instruction cache is enabled (NVMCTRL->CTRLB.CACHEDIS = 0)
 *	- CPU, APBx clock division is by 1 (CPU, APBx Buses running at 1MHz)
 *	- APBA clocks are connected to EIC, RTC, WDT, GCLK, SYSCTRL,PM, PAC0 peripherals.
 *		
 *	The following steps will be followed to switch over to the 48MHz clock
 *	1) Set Flash wait states for 48 MHz (per Table 37-40 in data sheet)
 *	2) Enable XOSC32K clock (External on-board 32.768Hz oscillator), will be used as DFLL48M reference.
 *	3) Put XOSC32K as source of Generic Clock Generator 1, 
 *	4) Put Generic Clock Generator 1 as source for Generic Clock Multiplexer 0 (DFLL48M reference)
 *	5) Enable DFLL48M clock
 *	6) Switch Generic Clock Generator 0 to DFLL48M. CPU will run at 48MHz.
 *	7) Modify prescaler value of OSC8M to produce 8MHz output
 *	8) Put OSC8M as source for Generic Clock Generator 3
 *	9) Set CPU and APBx BUS Clocks for 48MHz operation
 *	 
 * Notes:
 *
 ******************************************************************************/
void ClocksInit(void){
	
	uint32_t tempDFLL48CalibrationCoarse;	/* used to retrieve DFLL48 coarse calibration value from NVM */

	/* ----------------------------------------------------------------------------------------------
	* 1) Set Flash wait states for 48 MHz (per Table 37-40 in data sheet)
	*/
	
	NVMCTRL->CTRLB.bit.RWS = 1;		/* 1 wait state required @ 3.3V & 48MHz */
	
	/* ----------------------------------------------------------------------------------------------
	* 2) Enable XOSC32K clock (External on-board 32.768kHz oscillator), will be used as DFLL48M reference.
	*/
	
	// Configure SYSCTRL->XOSC32K settings
	SYSCTRL_XOSC32K_Type sysctrl_xosc32k = {
		.bit.WRTLOCK = 0,		/* XOSC32K configuration is not locked */
		.bit.STARTUP = 0x2,		/* 3 cycle start-up time */
		.bit.ONDEMAND = 0,		/* Osc. is always running when enabled */
		.bit.RUNSTDBY = 0,		/* Osc. is disabled in standby sleep mode */
		.bit.AAMPEN = 0,		/* Disable automatic amplitude control */
		.bit.EN32K = 1,			/* 32kHz output is disabled */
		.bit.XTALEN = 1			/* Crystal connected to XIN32/XOUT32 */
	};
	// Write these settings
	SYSCTRL->XOSC32K.reg = sysctrl_xosc32k.reg;
	// Enable the Oscillator - Separate step per data sheet recommendation (sec 17.6.3)
	SYSCTRL->XOSC32K.bit.ENABLE = 1;
	
	// Wait for XOSC32K to stabilize
	while(!SYSCTRL->PCLKSR.bit.XOSC32KRDY);
	
	/* ----------------------------------------------------------------------------------------------
	* 3) Put XOSC32K as source of Generic Clock Generator 1
	*/
	
	// Set the Generic Clock Generator 1 output divider to 1
	// Configure GCLK->GENDIV settings
	GCLK_GENDIV_Type gclk1_gendiv = {
		.bit.DIV = 1,								/* Set output division factor = 1 */
		.bit.ID = GENERIC_CLOCK_GENERATOR_XOSC32K	/* Apply division factor to Generator 1 */
	};
	// Write these settings
	GCLK->GENDIV.reg = gclk1_gendiv.reg;
	
	// Configure Generic Clock Generator 1 with XOSC32K as source
	GCLK_GENCTRL_Type gclk1_genctrl = {
		.bit.RUNSTDBY = 0,		/* Generic Clock Generator is stopped in stdby */
		.bit.DIVSEL =  0,		/* Use GENDIV.DIV value to divide the generator */
		.bit.OE = 0,			/* Disable generator output to GCLK_IO[1] */
		.bit.OOV = 0,			/* GCLK_IO[1] output value when generator is off */
		.bit.IDC = 1,			/* Generator duty cycle is 50/50 */
		.bit.GENEN = 1,			/* Enable the generator */
		.bit.SRC = 0x05,		/* Generator source: XOSC32K output */
		.bit.ID = GENERIC_CLOCK_GENERATOR_XOSC32K			/* Generator ID: 1 */
	};
	// Write these settings
	GCLK->GENCTRL.reg = gclk1_genctrl.reg;
	// GENCTRL is Write-Synchronized...so wait for write to complete
	while(GCLK->STATUS.bit.SYNCBUSY);
	
	/* ----------------------------------------------------------------------------------------------
	* 4) Put Generic Clock Generator 1 as source for Generic Clock Multiplexer 0 (DFLL48M reference)
	*/
	
	GCLK_CLKCTRL_Type gclk_clkctrl = {
		.bit.WRTLOCK = 0,		/* Generic Clock is not locked from subsequent writes */
		.bit.CLKEN = 1,			/* Enable the Generic Clock */
		.bit.GEN = GENERIC_CLOCK_GENERATOR_XOSC32K, 	/* Generic Clock Generator 1 is the source */
		.bit.ID = 0x00			/* Generic Clock Multiplexer 0 (DFLL48M Reference) */
	};
	// Write these settings
	GCLK->CLKCTRL.reg = gclk_clkctrl.reg;
	
	/* ----------------------------------------------------------------------------------------------
	* 5) Enable DFLL48M clock
	*/
	
	// DFLL Configuration in Closed Loop mode, cf product data sheet chapter
	// 17.6.7.1 - Closed-Loop Operation
	
	// Enable the DFLL48M in open loop mode. Without this step, attempts to go into closed loop mode at 48 MHz will
	// result in Processor Reset (you'll be at the in the Reset_Handler in startup_samd21.c).
	// PCLKSR.DFLLRDY must be one before writing to the DFLL Control register
	// Note that the DFLLRDY bit represents status of register synchronization - NOT clock stability
	// (see Data Sheet 17.6.14 Synchronization for detail)
	while(!SYSCTRL->PCLKSR.bit.DFLLRDY);
	SYSCTRL->DFLLCTRL.reg = (uint16_t)(SYSCTRL_DFLLCTRL_ENABLE);
	while(!SYSCTRL->PCLKSR.bit.DFLLRDY);
	
	// Set up the Multiplier, Coarse and Fine steps
	SYSCTRL_DFLLMUL_Type sysctrl_dfllmul = {
		.bit.CSTEP = 31,		/* Coarse step - use half of the max value (63) */
		.bit.FSTEP = 511,		/* Fine step - use half of the max value (1023) */
		.bit.MUL = 1465			/* Multiplier = MAIN_CLK_FREQ (48MHz) / EXT_32K_CLK_FREQ (32768 Hz) */
	};
	// Write these settings
	SYSCTRL->DFLLMUL.reg = sysctrl_dfllmul.reg;
	// Wait for synchronization
	while(!SYSCTRL->PCLKSR.bit.DFLLRDY);
	
	// To reduce lock time, load factory calibrated values into DFLLVAL (cf. Data Sheet 17.6.7.1)
	// Location of value is defined in Data Sheet Table 10-5. NVM Software Calibration Area Mapping
	
	// Get factory calibrated value for "DFLL48M COARSE CAL" from NVM Software Calibration Area
	tempDFLL48CalibrationCoarse = *(uint32_t*)FUSES_DFLL48M_COARSE_CAL_ADDR;
	tempDFLL48CalibrationCoarse &= FUSES_DFLL48M_COARSE_CAL_Msk;
	tempDFLL48CalibrationCoarse = tempDFLL48CalibrationCoarse>>FUSES_DFLL48M_COARSE_CAL_Pos;
	// Write the coarse calibration value
	SYSCTRL->DFLLVAL.bit.COARSE = tempDFLL48CalibrationCoarse;
	// Switch DFLL48M to Closed Loop mode and enable WAITLOCK
	while(!SYSCTRL->PCLKSR.bit.DFLLRDY);
	SYSCTRL->DFLLCTRL.reg |= (uint16_t) (SYSCTRL_DFLLCTRL_MODE | SYSCTRL_DFLLCTRL_WAITLOCK);
	
	/* ----------------------------------------------------------------------------------------------
	* 6) Switch Generic Clock Generator 0 to DFLL48M. CPU will run at 48MHz.
	*/
	
	// Now that DFLL48M is running, switch CLKGEN0 source to it to run the core at 48 MHz.
	// Enable output of Generic Clock Generator 0 (GCLK_MAIN) to the GCLK_IO[0] GPIO Pin
	GCLK_GENCTRL_Type gclk_genctrl0 = {
		.bit.RUNSTDBY = 0,		/* Generic Clock Generator is stopped in stdby */
		.bit.DIVSEL =  0,		/* Use GENDIV.DIV value to divide the generator */
		.bit.OE = 1,			/* Enable generator output to GCLK_IO[0] */
		.bit.OOV = 0,			/* GCLK_IO[0] output value when generator is off */
		.bit.IDC = 1,			/* Generator duty cycle is 50/50 */
		.bit.GENEN = 1,			/* Enable the generator */
		.bit.SRC = 0x07,		/* Generator source: DFLL48M output */
		.bit.ID = GENERIC_CLOCK_GENERATOR_MAIN			/* Generator ID: 0 */
	};
	GCLK->GENCTRL.reg = gclk_genctrl0.reg;
	// GENCTRL is Write-Synchronized...so wait for write to complete
	while(GCLK->STATUS.bit.SYNCBUSY);
	
	// Direct the GCLK_IO[0] output to PA28
	// PORT_WRCONFIG_Type port0_wrconfig = {
	//	.bit.HWSEL = 1,			/* Pin# (28) - falls in the upper half of the 32-pin PORT group */
	//	.bit.WRPINCFG = 1,		/* Update PINCFGy registers for all pins selected */
	//	.bit.WRPMUX = 1,		/* Update PMUXn registers for all pins selected */
	//	.bit.PMUX = 7,			/* Peripheral Function H selected (GCLK_IO[0]) */
	//	.bit.PMUXEN = 1,		/* Enable peripheral Multiplexer */
	//	.bit.PINMASK = (uint16_t)(1 << (28-16)) /* Select the pin(s) to be configured */
	//};
	// Write these settings
	//PORT->Group[0].WRCONFIG.reg = port0_wrconfig.reg; 
	//
	
	/* ----------------------------------------------------------------------------------------------
	* 7) Modify prescaler value of OSC8M to produce 8MHz output
	*/

	SYSCTRL->OSC8M.bit.PRESC = 0;		/* Prescale by 1 */
	SYSCTRL->OSC8M.bit.ONDEMAND = 0 ;	/* Oscillator is always on if enabled */
	
	/* ----------------------------------------------------------------------------------------------
	* 8) Put OSC8M as source for Generic Clock Generator 3
	*/
	
	// Set the Generic Clock Generator 3 output divider to 1
	// Configure GCLK->GENDIV settings
	GCLK_GENDIV_Type gclk3_gendiv = {
		.bit.DIV = 1,								/* Set output division factor = 1 */
		.bit.ID = GENERIC_CLOCK_GENERATOR_OSC8M		/* Apply division factor to Generator 3 */
	};
	// Write these settings
	GCLK->GENDIV.reg = gclk3_gendiv.reg;
	
	// Configure Generic Clock Generator 3 with OSC8M as source
	GCLK_GENCTRL_Type gclk3_genctrl = {
		.bit.RUNSTDBY = 0,		/* Generic Clock Generator is stopped in stdby */
		.bit.DIVSEL =  0,		/* Use GENDIV.DIV value to divide the generator */
		.bit.OE = 0,			/* Disable generator output to GCLK_IO[1] */
		.bit.OOV = 0,			/* GCLK_IO[2] output value when generator is off */
		.bit.IDC = 1,			/* Generator duty cycle is 50/50 */
		.bit.GENEN = 1,			/* Enable the generator */
		.bit.SRC = 0x06,		/* Generator source: OSC8M output */
		.bit.ID = GENERIC_CLOCK_GENERATOR_OSC8M			/* Generator ID: 3 */
	};
	// Write these settings
	GCLK->GENCTRL.reg = gclk3_genctrl.reg;
	// GENCTRL is Write-Synchronized...so wait for write to complete
	while(GCLK->STATUS.bit.SYNCBUSY);
	
	/* ----------------------------------------------------------------------------------------------
	* 9) Set CPU and APBx BUS Clocks to 48MHz
	*/
	PM->CPUSEL.reg  = PM_CPUSEL_CPUDIV_DIV1 ;
	PM->APBASEL.reg = PM_APBASEL_APBADIV_DIV1_Val ;
	PM->APBBSEL.reg = PM_APBBSEL_APBBDIV_DIV1_Val ;
	PM->APBCSEL.reg = PM_APBCSEL_APBCDIV_DIV1_Val ;
	
} // ClockSysInit48M()

/*******************************************************************************
 * Function:        void SysTick_Handler(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This interrupt handler is called on SysTick timer underflow
 *
 * Note:
 *
 ******************************************************************************/
void SysTick_Handler(void){
	
	ul_tickcount++ ;
	// Toggle LEDs every second (i.e. 1000ms)
	if(ul_tickcount % 1000 == 0){
		// Toggle LED pin output level.
		PORT->Group[LED0_PORT].OUTTGL.reg = LED0_PIN_MASK;
	}
} // SysTick_Handler()

void delay_ms(int delay_time){
	
	uint16_t ul_tickcount++	;
	while(ul_tickcount % delay_time == 0){}
		
	return;
	
}
