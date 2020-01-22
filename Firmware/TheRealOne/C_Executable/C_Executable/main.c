/** INCLUDES ******************************************************************/

#include "sam.h"
#include "definitions.h"
#include "instance\port.h"

/** MACROS ********************************************************************/

#define LCD_Read_Strobe		PORT_PB16;
#define LCD_Write_Strobe	PORT_PB17;
#define LCD_Reset			PORT_PB30;
#define LCD_Data_Command	PORT_PB23;
#define LCD_Chip_Select		PORT_PB22;
#define LCD_Data_Bus		0x0000FFFF;

#define swap(type, i, j) {type t = i; i = j; j = t;}

/** VARIABLES *****************************************************************/

static uint32_t ul_tickcount=0 ;	// Global state variable for tick count

unsigned int disp_x_size = 479;
unsigned int disp_y_size = 799;

/** LOCAL PROTOTYPES **********************************************************/

void AppInit(void);			// Application Hardware/Software Initialization
void ClocksInit(void);	// Configure Clock, Wait States and synch. Bus Clocks for 48MHz operation

/*#define Clear_Bit(reg, bitmask) *reg &= ~bitmask;
#define Set_Bit(reg, bitmask) *reg |= bitmask;
#define pulse_high(reg, bitmask) Set_Bit(reg, bitmask); Clear_Bit(reg, bitmask);
#define pulse_low(reg, bitmask) Clear_Bit(reg, bitmask); Set_Bit(reg, bitmask);
*/
/** main() ********************************************************************/



int main(void){
	
	/* Initialize the SAM system - auto-generated CMSIS compliant function */
	/* NOT USED - Use AppInit() for all Hardware/System initialization */
	SystemInit();
	
	/* Application hardware and software initialization */
	AppInit();

	/* Replace with your application code */
	while(1){
		
		InitLCD();
		
		LCD_ClrScr();
		
		LCD_SetColor(0,0,0);
		
		LCD_FillRect(0,0,799, 479);
		
		delay_ms(1000);
		
		LCD_SetColor(255,128,0);
		
		LCD_FillRect(0,0,799,479);
		
		delay_ms(1000);
		
	}
} // main()


/*******************************************************************************
	Function:		void InitLCD(void)
	
	Inits the LCD. Does Magic.
*******************************************************************************/
void InitLCD(void)
{
	REG_PORT_OUTSET1 = LCD_Reset;
	delay_ms(5);
	REG_PORT_OUTCLR1 = LCD_Reset;
	delay_ms(15);
	REG_PORT_OUTSET1 = LCD_Reset;
	delay_ms(15);
	REG_PORT_OUTCLR1 = LCD_Chip_Select;

	LCD_Write_COM(0xF0,0x00);LCD_Write_DATA(0x55);
	LCD_Write_COM(0xF0,0x01);LCD_Write_DATA(0xAA);
	LCD_Write_COM(0xF0,0x02);LCD_Write_DATA(0x52);
	LCD_Write_COM(0xF0,0x03);LCD_Write_DATA(0x08);
	LCD_Write_COM(0xF0,0x04);LCD_Write_DATA(0x01);
	
	//#AVDD Set AVDD 5.2V
	LCD_Write_COM(0xB0,0x00);LCD_Write_DATA(0x0D);
	LCD_Write_COM(0xB0,0x01);LCD_Write_DATA(0x0D);
	LCD_Write_COM(0xB0,0x02);LCD_Write_DATA(0x0D);
	
	//#AVDD ratio
	LCD_Write_COM(0xB6,0x00);LCD_Write_DATA(0x34);
	LCD_Write_COM(0xB6,0x01);LCD_Write_DATA(0x34);
	LCD_Write_COM(0xB6,0x02);LCD_Write_DATA(0x34);
	 
	//#AVEE  -5.2V
	LCD_Write_COM(0xB1,0x00);LCD_Write_DATA(0x0D);
	LCD_Write_COM(0xB1,0x01);LCD_Write_DATA(0x0D);
	LCD_Write_COM(0xB1,0x02);LCD_Write_DATA(0x0D);
	
	//#AVEE ratio
	LCD_Write_COM(0xB7,0x00);LCD_Write_DATA(0x34);
	LCD_Write_COM(0xB7,0x01);LCD_Write_DATA(0x34);
	LCD_Write_COM(0xB7,0x02);LCD_Write_DATA(0x34);
	
	//#VCL  -2.5V
	LCD_Write_COM(0xB2,0x00);LCD_Write_DATA(0x00);
	LCD_Write_COM(0xB2,0x01);LCD_Write_DATA(0x00);
	LCD_Write_COM(0xB2,0x02);LCD_Write_DATA(0x00);
	
	//#VCL ratio
	LCD_Write_COM(0xB8,0x00);LCD_Write_DATA(0x24);
	LCD_Write_COM(0xB8,0x01);LCD_Write_DATA(0x24);
	LCD_Write_COM(0xB8,0x02);LCD_Write_DATA(0x24); 
	
	//#VGH  15V
	LCD_Write_COM(0xBF,0x00);LCD_Write_DATA(0x01);
	LCD_Write_COM(0xB3,0x00);LCD_Write_DATA(0x0F);
	LCD_Write_COM(0xB3,0x01);LCD_Write_DATA(0x0F);
	LCD_Write_COM(0xB3,0x02);LCD_Write_DATA(0x0F);
	
	//#VGH  ratio
	LCD_Write_COM(0xB9,0x00);LCD_Write_DATA(0x34);
	LCD_Write_COM(0xB9,0x01);LCD_Write_DATA(0x34);
	LCD_Write_COM(0xB9,0x02);LCD_Write_DATA(0x34); 
	
	//#VGL_REG  -10V
	LCD_Write_COM(0xB5,0x00);LCD_Write_DATA(0x08);
	LCD_Write_COM(0xB5,0x00);LCD_Write_DATA(0x08);
	LCD_Write_COM(0xB5,0x01);LCD_Write_DATA(0x08);
	LCD_Write_COM(0xC2,0x00);LCD_Write_DATA(0x03);
	
	//#VGLX  ratio
	LCD_Write_COM(0xBA,0x00);LCD_Write_DATA(0x24);
	LCD_Write_COM(0xBA,0x01);LCD_Write_DATA(0x24);
	LCD_Write_COM(0xBA,0x02);LCD_Write_DATA(0x24);
	
	//#VGMP/VGSP 4.5V/0V
	LCD_Write_COM(0xBC,0x00);LCD_Write_DATA(0x00);
	LCD_Write_COM(0xBC,0x01);LCD_Write_DATA(0x78);
	LCD_Write_COM(0xBC,0x02);LCD_Write_DATA(0x00);
	
	//#VGMN/VGSN -4.5V/0V
	LCD_Write_COM(0xBD,0x00);LCD_Write_DATA(0x00);
	LCD_Write_COM(0xBD,0x01);LCD_Write_DATA(0x78);
	LCD_Write_COM(0xBD,0x02);LCD_Write_DATA(0x00);
	
	//#VCOM  -1.325V
	LCD_Write_COM(0xBE,0x00);LCD_Write_DATA(0x00);
	LCD_Write_COM(0xBE,0x01);LCD_Write_DATA(0x89);
	
	 //Gamma Setting	 
	LCD_Write_COM(0xD1,0x00);LCD_Write_DATA(0x00);
	LCD_Write_COM(0xD1,0x01);LCD_Write_DATA(0x2D);
	LCD_Write_COM(0xD1,0x02);LCD_Write_DATA(0x00);
	LCD_Write_COM(0xD1,0x03);LCD_Write_DATA(0x2E);
	LCD_Write_COM(0xD1,0x04);LCD_Write_DATA(0x00); 
	LCD_Write_COM(0xD1,0x05);LCD_Write_DATA(0x32);
	LCD_Write_COM(0xD1,0x06);LCD_Write_DATA(0x00);
	LCD_Write_COM(0xD1,0x07);LCD_Write_DATA(0x44);
	LCD_Write_COM(0xD1,0x08);LCD_Write_DATA(0x00);
	LCD_Write_COM(0xD1,0x09);LCD_Write_DATA(0x53);
	LCD_Write_COM(0xD1,0x0A);LCD_Write_DATA(0x00);
	LCD_Write_COM(0xD1,0x0B);LCD_Write_DATA(0x88);
	LCD_Write_COM(0xD1,0x0C);LCD_Write_DATA(0x00);
	LCD_Write_COM(0xD1,0x0D);LCD_Write_DATA(0xB6);
	LCD_Write_COM(0xD1,0x0E);LCD_Write_DATA(0x00);
	LCD_Write_COM(0xD1,0x0F);LCD_Write_DATA(0xF3);
	LCD_Write_COM(0xD1,0x10);LCD_Write_DATA(0x01);
	LCD_Write_COM(0xD1,0x11);LCD_Write_DATA(0x22);
	LCD_Write_COM(0xD1,0x12);LCD_Write_DATA(0x01);
	LCD_Write_COM(0xD1,0x13);LCD_Write_DATA(0x64);
	LCD_Write_COM(0xD1,0x14);LCD_Write_DATA(0x01);
	LCD_Write_COM(0xD1,0x15);LCD_Write_DATA(0x92);
	LCD_Write_COM(0xD1,0x16);LCD_Write_DATA(0x01);
	LCD_Write_COM(0xD1,0x17);LCD_Write_DATA(0xD4);
	LCD_Write_COM(0xD1,0x18);LCD_Write_DATA(0x02);	
	LCD_Write_COM(0xD1,0x19);LCD_Write_DATA(0x07);
	LCD_Write_COM(0xD1,0x1A);LCD_Write_DATA(0x02);
	LCD_Write_COM(0xD1,0x1B);LCD_Write_DATA(0x08);
	LCD_Write_COM(0xD1,0x1C);LCD_Write_DATA(0x02);
	LCD_Write_COM(0xD1,0x1D);LCD_Write_DATA(0x34);
	LCD_Write_COM(0xD1,0x1E);LCD_Write_DATA(0x02);
	LCD_Write_COM(0xD1,0x1F);LCD_Write_DATA(0x5F);
	LCD_Write_COM(0xD1,0x20);LCD_Write_DATA(0x02);
	LCD_Write_COM(0xD1,0x21);LCD_Write_DATA(0x78);
	LCD_Write_COM(0xD1,0x22);LCD_Write_DATA(0x02);
	LCD_Write_COM(0xD1,0x23);LCD_Write_DATA(0x94);
	LCD_Write_COM(0xD1,0x24);LCD_Write_DATA(0x02);
	LCD_Write_COM(0xD1,0x25);LCD_Write_DATA(0xA6);
	LCD_Write_COM(0xD1,0x26);LCD_Write_DATA(0x02);
	LCD_Write_COM(0xD1,0x27);LCD_Write_DATA(0xBB);
	LCD_Write_COM(0xD1,0x28);LCD_Write_DATA(0x02); 
	LCD_Write_COM(0xD1,0x29);LCD_Write_DATA(0xCA);
	LCD_Write_COM(0xD1,0x2A);LCD_Write_DATA(0x02);
	LCD_Write_COM(0xD1,0x2B);LCD_Write_DATA(0xDB);
	LCD_Write_COM(0xD1,0x2C);LCD_Write_DATA(0x02);
	LCD_Write_COM(0xD1,0x2D);LCD_Write_DATA(0xE8);
	LCD_Write_COM(0xD1,0x2E);LCD_Write_DATA(0x02);
	LCD_Write_COM(0xD1,0x2F);LCD_Write_DATA(0xF9);
	LCD_Write_COM(0xD1,0x30);LCD_Write_DATA(0x03); 
	LCD_Write_COM(0xD1,0x31);LCD_Write_DATA(0x1F);
	LCD_Write_COM(0xD1,0x32);LCD_Write_DATA(0x03);
	LCD_Write_COM(0xD1,0x33);LCD_Write_DATA(0x7F);
			 
	LCD_Write_COM(0xD2,0x00);LCD_Write_DATA(0x00);
	LCD_Write_COM(0xD2,0x01);LCD_Write_DATA(0x2D);
	LCD_Write_COM(0xD2,0x02);LCD_Write_DATA(0x00);
	LCD_Write_COM(0xD2,0x03);LCD_Write_DATA(0x2E);
	LCD_Write_COM(0xD2,0x04);LCD_Write_DATA(0x00); 
	LCD_Write_COM(0xD2,0x05);LCD_Write_DATA(0x32);
	LCD_Write_COM(0xD2,0x06);LCD_Write_DATA(0x00);
	LCD_Write_COM(0xD2,0x07);LCD_Write_DATA(0x44);
	LCD_Write_COM(0xD2,0x08);LCD_Write_DATA(0x00);
	LCD_Write_COM(0xD2,0x09);LCD_Write_DATA(0x53);
	LCD_Write_COM(0xD2,0x0A);LCD_Write_DATA(0x00);
	LCD_Write_COM(0xD2,0x0B);LCD_Write_DATA(0x88);
	LCD_Write_COM(0xD2,0x0C);LCD_Write_DATA(0x00);
	LCD_Write_COM(0xD2,0x0D);LCD_Write_DATA(0xB6);
	LCD_Write_COM(0xD2,0x0E);LCD_Write_DATA(0x00);
	LCD_Write_COM(0xD2,0x0F);LCD_Write_DATA(0xF3);
	LCD_Write_COM(0xD2,0x10);LCD_Write_DATA(0x01);
	LCD_Write_COM(0xD2,0x11);LCD_Write_DATA(0x22);
	LCD_Write_COM(0xD2,0x12);LCD_Write_DATA(0x01);
	LCD_Write_COM(0xD2,0x13);LCD_Write_DATA(0x64);
	LCD_Write_COM(0xD2,0x14);LCD_Write_DATA(0x01);
	LCD_Write_COM(0xD2,0x15);LCD_Write_DATA(0x92);
	LCD_Write_COM(0xD2,0x16);LCD_Write_DATA(0x01);
	LCD_Write_COM(0xD2,0x17);LCD_Write_DATA(0xD4);
	LCD_Write_COM(0xD2,0x18);LCD_Write_DATA(0x02);	
	LCD_Write_COM(0xD2,0x19);LCD_Write_DATA(0x07);
	LCD_Write_COM(0xD2,0x1A);LCD_Write_DATA(0x02);
	LCD_Write_COM(0xD2,0x1B);LCD_Write_DATA(0x08);
	LCD_Write_COM(0xD2,0x1C);LCD_Write_DATA(0x02);
	LCD_Write_COM(0xD2,0x1D);LCD_Write_DATA(0x34);
	LCD_Write_COM(0xD2,0x1E);LCD_Write_DATA(0x02);
	LCD_Write_COM(0xD2,0x1F);LCD_Write_DATA(0x5F);
	LCD_Write_COM(0xD2,0x20);LCD_Write_DATA(0x02);
	LCD_Write_COM(0xD2,0x21);LCD_Write_DATA(0x78);
	LCD_Write_COM(0xD2,0x22);LCD_Write_DATA(0x02);
	LCD_Write_COM(0xD2,0x23);LCD_Write_DATA(0x94);
	LCD_Write_COM(0xD2,0x24);LCD_Write_DATA(0x02);
	LCD_Write_COM(0xD2,0x25);LCD_Write_DATA(0xA6);
	LCD_Write_COM(0xD2,0x26);LCD_Write_DATA(0x02);
	LCD_Write_COM(0xD2,0x27);LCD_Write_DATA(0xBB);
	LCD_Write_COM(0xD2,0x28);LCD_Write_DATA(0x02); 
	LCD_Write_COM(0xD2,0x29);LCD_Write_DATA(0xCA);
	LCD_Write_COM(0xD2,0x2A);LCD_Write_DATA(0x02);
	LCD_Write_COM(0xD2,0x2B);LCD_Write_DATA(0xDB);
	LCD_Write_COM(0xD2,0x2C);LCD_Write_DATA(0x02);
	LCD_Write_COM(0xD2,0x2D);LCD_Write_DATA(0xE8);
	LCD_Write_COM(0xD2,0x2E);LCD_Write_DATA(0x02);
	LCD_Write_COM(0xD2,0x2F);LCD_Write_DATA(0xF9);
	LCD_Write_COM(0xD2,0x30);LCD_Write_DATA(0x03); 
	LCD_Write_COM(0xD2,0x31);LCD_Write_DATA(0x1F);
	LCD_Write_COM(0xD2,0x32);LCD_Write_DATA(0x03);
	LCD_Write_COM(0xD2,0x33);LCD_Write_DATA(0x7F);
		 
	LCD_Write_COM(0xD3,0x00);LCD_Write_DATA(0x00);
	LCD_Write_COM(0xD3,0x01);LCD_Write_DATA(0x2D);
	LCD_Write_COM(0xD3,0x02);LCD_Write_DATA(0x00);
	LCD_Write_COM(0xD3,0x03);LCD_Write_DATA(0x2E);
	LCD_Write_COM(0xD3,0x04);LCD_Write_DATA(0x00); 
	LCD_Write_COM(0xD3,0x05);LCD_Write_DATA(0x32);
	LCD_Write_COM(0xD3,0x06);LCD_Write_DATA(0x00);
	LCD_Write_COM(0xD3,0x07);LCD_Write_DATA(0x44);
	LCD_Write_COM(0xD3,0x08);LCD_Write_DATA(0x00);
	LCD_Write_COM(0xD3,0x09);LCD_Write_DATA(0x53);
	LCD_Write_COM(0xD3,0x0A);LCD_Write_DATA(0x00);
	LCD_Write_COM(0xD3,0x0B);LCD_Write_DATA(0x88);
	LCD_Write_COM(0xD3,0x0C);LCD_Write_DATA(0x00);
	LCD_Write_COM(0xD3,0x0D);LCD_Write_DATA(0xB6);
	LCD_Write_COM(0xD3,0x0E);LCD_Write_DATA(0x00);
	LCD_Write_COM(0xD3,0x0F);LCD_Write_DATA(0xF3);
	LCD_Write_COM(0xD3,0x10);LCD_Write_DATA(0x01);
	LCD_Write_COM(0xD3,0x11);LCD_Write_DATA(0x22);
	LCD_Write_COM(0xD3,0x12);LCD_Write_DATA(0x01);
	LCD_Write_COM(0xD3,0x13);LCD_Write_DATA(0x64);
	LCD_Write_COM(0xD3,0x14);LCD_Write_DATA(0x01);
	LCD_Write_COM(0xD3,0x15);LCD_Write_DATA(0x92);
	LCD_Write_COM(0xD3,0x16);LCD_Write_DATA(0x01);
	LCD_Write_COM(0xD3,0x17);LCD_Write_DATA(0xD4);
	LCD_Write_COM(0xD3,0x18);LCD_Write_DATA(0x02);	
	LCD_Write_COM(0xD3,0x19);LCD_Write_DATA(0x07);
	LCD_Write_COM(0xD3,0x1A);LCD_Write_DATA(0x02);
	LCD_Write_COM(0xD3,0x1B);LCD_Write_DATA(0x08);
	LCD_Write_COM(0xD3,0x1C);LCD_Write_DATA(0x02);
	LCD_Write_COM(0xD3,0x1D);LCD_Write_DATA(0x34);
	LCD_Write_COM(0xD3,0x1E);LCD_Write_DATA(0x02);
	LCD_Write_COM(0xD3,0x1F);LCD_Write_DATA(0x5F);
	LCD_Write_COM(0xD3,0x20);LCD_Write_DATA(0x02);
	LCD_Write_COM(0xD3,0x21);LCD_Write_DATA(0x78);
	LCD_Write_COM(0xD3,0x22);LCD_Write_DATA(0x02);
	LCD_Write_COM(0xD3,0x23);LCD_Write_DATA(0x94);
	LCD_Write_COM(0xD3,0x24);LCD_Write_DATA(0x02);
	LCD_Write_COM(0xD3,0x25);LCD_Write_DATA(0xA6);
	LCD_Write_COM(0xD3,0x26);LCD_Write_DATA(0x02);
	LCD_Write_COM(0xD3,0x27);LCD_Write_DATA(0xBB);
	LCD_Write_COM(0xD3,0x28);LCD_Write_DATA(0x02); 
	LCD_Write_COM(0xD3,0x29);LCD_Write_DATA(0xCA);
	LCD_Write_COM(0xD3,0x2A);LCD_Write_DATA(0x02);
	LCD_Write_COM(0xD3,0x2B);LCD_Write_DATA(0xDB);
	LCD_Write_COM(0xD3,0x2C);LCD_Write_DATA(0x02);
	LCD_Write_COM(0xD3,0x2D);LCD_Write_DATA(0xE8);
	LCD_Write_COM(0xD3,0x2E);LCD_Write_DATA(0x02);
	LCD_Write_COM(0xD3,0x2F);LCD_Write_DATA(0xF9);
	LCD_Write_COM(0xD3,0x30);LCD_Write_DATA(0x03); 
	LCD_Write_COM(0xD3,0x31);LCD_Write_DATA(0x1F);
	LCD_Write_COM(0xD3,0x32);LCD_Write_DATA(0x03);
	LCD_Write_COM(0xD3,0x33);LCD_Write_DATA(0x7F);
		 
	LCD_Write_COM(0xD4,0x00);LCD_Write_DATA(0x00);
	LCD_Write_COM(0xD4,0x01);LCD_Write_DATA(0x2D);
	LCD_Write_COM(0xD4,0x02);LCD_Write_DATA(0x00);
	LCD_Write_COM(0xD4,0x03);LCD_Write_DATA(0x2E);
	LCD_Write_COM(0xD4,0x04);LCD_Write_DATA(0x00); 
	LCD_Write_COM(0xD4,0x05);LCD_Write_DATA(0x32);
	LCD_Write_COM(0xD4,0x06);LCD_Write_DATA(0x00);
	LCD_Write_COM(0xD4,0x07);LCD_Write_DATA(0x44);
	LCD_Write_COM(0xD4,0x08);LCD_Write_DATA(0x00);
	LCD_Write_COM(0xD4,0x09);LCD_Write_DATA(0x53);
	LCD_Write_COM(0xD4,0x0A);LCD_Write_DATA(0x00);
	LCD_Write_COM(0xD4,0x0B);LCD_Write_DATA(0x88);
	LCD_Write_COM(0xD4,0x0C);LCD_Write_DATA(0x00);
	LCD_Write_COM(0xD4,0x0D);LCD_Write_DATA(0xB6);
	LCD_Write_COM(0xD4,0x0E);LCD_Write_DATA(0x00);
	LCD_Write_COM(0xD4,0x0F);LCD_Write_DATA(0xF3);
	LCD_Write_COM(0xD4,0x10);LCD_Write_DATA(0x01);
	LCD_Write_COM(0xD4,0x11);LCD_Write_DATA(0x22);
	LCD_Write_COM(0xD4,0x12);LCD_Write_DATA(0x01);
	LCD_Write_COM(0xD4,0x13);LCD_Write_DATA(0x64);
	LCD_Write_COM(0xD4,0x14);LCD_Write_DATA(0x01);
	LCD_Write_COM(0xD4,0x15);LCD_Write_DATA(0x92);
	LCD_Write_COM(0xD4,0x16);LCD_Write_DATA(0x01);
	LCD_Write_COM(0xD4,0x17);LCD_Write_DATA(0xD4);
	LCD_Write_COM(0xD4,0x18);LCD_Write_DATA(0x02);	
	LCD_Write_COM(0xD4,0x19);LCD_Write_DATA(0x07);
	LCD_Write_COM(0xD4,0x1A);LCD_Write_DATA(0x02);
	LCD_Write_COM(0xD4,0x1B);LCD_Write_DATA(0x08);
	LCD_Write_COM(0xD4,0x1C);LCD_Write_DATA(0x02);
	LCD_Write_COM(0xD4,0x1D);LCD_Write_DATA(0x34);
	LCD_Write_COM(0xD4,0x1E);LCD_Write_DATA(0x02);
	LCD_Write_COM(0xD4,0x1F);LCD_Write_DATA(0x5F);
	LCD_Write_COM(0xD4,0x20);LCD_Write_DATA(0x02);
	LCD_Write_COM(0xD4,0x21);LCD_Write_DATA(0x78);
	LCD_Write_COM(0xD4,0x22);LCD_Write_DATA(0x02);
	LCD_Write_COM(0xD4,0x23);LCD_Write_DATA(0x94);
	LCD_Write_COM(0xD4,0x24);LCD_Write_DATA(0x02);
	LCD_Write_COM(0xD4,0x25);LCD_Write_DATA(0xA6);
	LCD_Write_COM(0xD4,0x26);LCD_Write_DATA(0x02);
	LCD_Write_COM(0xD4,0x27);LCD_Write_DATA(0xBB);
	LCD_Write_COM(0xD4,0x28);LCD_Write_DATA(0x02); 
	LCD_Write_COM(0xD4,0x29);LCD_Write_DATA(0xCA);
	LCD_Write_COM(0xD4,0x2A);LCD_Write_DATA(0x02);
	LCD_Write_COM(0xD4,0x2B);LCD_Write_DATA(0xDB);
	LCD_Write_COM(0xD4,0x2C);LCD_Write_DATA(0x02);
	LCD_Write_COM(0xD4,0x2D);LCD_Write_DATA(0xE8);
	LCD_Write_COM(0xD4,0x2E);LCD_Write_DATA(0x02);
	LCD_Write_COM(0xD4,0x2F);LCD_Write_DATA(0xF9);
	LCD_Write_COM(0xD4,0x30);LCD_Write_DATA(0x03); 
	LCD_Write_COM(0xD4,0x31);LCD_Write_DATA(0x1F);
	LCD_Write_COM(0xD4,0x32);LCD_Write_DATA(0x03);
	LCD_Write_COM(0xD4,0x33);LCD_Write_DATA(0x7F);
		 
	LCD_Write_COM(0xD5,0x00);LCD_Write_DATA(0x00);
	LCD_Write_COM(0xD5,0x01);LCD_Write_DATA(0x2D);
	LCD_Write_COM(0xD5,0x02);LCD_Write_DATA(0x00);
	LCD_Write_COM(0xD5,0x03);LCD_Write_DATA(0x2E);
	LCD_Write_COM(0xD5,0x04);LCD_Write_DATA(0x00); 
	LCD_Write_COM(0xD5,0x05);LCD_Write_DATA(0x32);
	LCD_Write_COM(0xD5,0x06);LCD_Write_DATA(0x00);
	LCD_Write_COM(0xD5,0x07);LCD_Write_DATA(0x44);
	LCD_Write_COM(0xD5,0x08);LCD_Write_DATA(0x00);
	LCD_Write_COM(0xD5,0x09);LCD_Write_DATA(0x53);
	LCD_Write_COM(0xD5,0x0A);LCD_Write_DATA(0x00);
	LCD_Write_COM(0xD5,0x0B);LCD_Write_DATA(0x88);
	LCD_Write_COM(0xD5,0x0C);LCD_Write_DATA(0x00);
	LCD_Write_COM(0xD5,0x0D);LCD_Write_DATA(0xB6);
	LCD_Write_COM(0xD5,0x0E);LCD_Write_DATA(0x00);
	LCD_Write_COM(0xD5,0x0F);LCD_Write_DATA(0xF3);
	LCD_Write_COM(0xD5,0x10);LCD_Write_DATA(0x01);
	LCD_Write_COM(0xD5,0x11);LCD_Write_DATA(0x22);
	LCD_Write_COM(0xD5,0x12);LCD_Write_DATA(0x01);
	LCD_Write_COM(0xD5,0x13);LCD_Write_DATA(0x64);
	LCD_Write_COM(0xD5,0x14);LCD_Write_DATA(0x01);
	LCD_Write_COM(0xD5,0x15);LCD_Write_DATA(0x92);
	LCD_Write_COM(0xD5,0x16);LCD_Write_DATA(0x01);
	LCD_Write_COM(0xD5,0x17);LCD_Write_DATA(0xD4);
	LCD_Write_COM(0xD5,0x18);LCD_Write_DATA(0x02);	
	LCD_Write_COM(0xD5,0x19);LCD_Write_DATA(0x07);
	LCD_Write_COM(0xD5,0x1A);LCD_Write_DATA(0x02);
	LCD_Write_COM(0xD5,0x1B);LCD_Write_DATA(0x08);
	LCD_Write_COM(0xD5,0x1C);LCD_Write_DATA(0x02);
	LCD_Write_COM(0xD5,0x1D);LCD_Write_DATA(0x34);
	LCD_Write_COM(0xD5,0x1E);LCD_Write_DATA(0x02);
	LCD_Write_COM(0xD5,0x1F);LCD_Write_DATA(0x5F);
	LCD_Write_COM(0xD5,0x20);LCD_Write_DATA(0x02);
	LCD_Write_COM(0xD5,0x21);LCD_Write_DATA(0x78);
	LCD_Write_COM(0xD5,0x22);LCD_Write_DATA(0x02);
	LCD_Write_COM(0xD5,0x23);LCD_Write_DATA(0x94);
	LCD_Write_COM(0xD5,0x24);LCD_Write_DATA(0x02);
	LCD_Write_COM(0xD5,0x25);LCD_Write_DATA(0xA6);
	LCD_Write_COM(0xD5,0x26);LCD_Write_DATA(0x02);
	LCD_Write_COM(0xD5,0x27);LCD_Write_DATA(0xBB);
	LCD_Write_COM(0xD5,0x28);LCD_Write_DATA(0x02); 
	LCD_Write_COM(0xD5,0x29);LCD_Write_DATA(0xCA);
	LCD_Write_COM(0xD5,0x2A);LCD_Write_DATA(0x02);
	LCD_Write_COM(0xD5,0x2B);LCD_Write_DATA(0xDB);
	LCD_Write_COM(0xD5,0x2C);LCD_Write_DATA(0x02);
	LCD_Write_COM(0xD5,0x2D);LCD_Write_DATA(0xE8);
	LCD_Write_COM(0xD5,0x2E);LCD_Write_DATA(0x02);
	LCD_Write_COM(0xD5,0x2F);LCD_Write_DATA(0xF9);
	LCD_Write_COM(0xD5,0x30);LCD_Write_DATA(0x03);
	LCD_Write_COM(0xD5,0x31);LCD_Write_DATA(0x1F);
	LCD_Write_COM(0xD5,0x32);LCD_Write_DATA(0x03);
	LCD_Write_COM(0xD5,0x33);LCD_Write_DATA(0x7F);
		 
	LCD_Write_COM(0xD6,0x00);LCD_Write_DATA(0x00);
	LCD_Write_COM(0xD6,0x01);LCD_Write_DATA(0x2D);
	LCD_Write_COM(0xD6,0x02);LCD_Write_DATA(0x00);
	LCD_Write_COM(0xD6,0x03);LCD_Write_DATA(0x2E);
	LCD_Write_COM(0xD6,0x04);LCD_Write_DATA(0x00); 
	LCD_Write_COM(0xD6,0x05);LCD_Write_DATA(0x32);
	LCD_Write_COM(0xD6,0x06);LCD_Write_DATA(0x00);
	LCD_Write_COM(0xD6,0x07);LCD_Write_DATA(0x44);
	LCD_Write_COM(0xD6,0x08);LCD_Write_DATA(0x00);
	LCD_Write_COM(0xD6,0x09);LCD_Write_DATA(0x53);
	LCD_Write_COM(0xD6,0x0A);LCD_Write_DATA(0x00);
	LCD_Write_COM(0xD6,0x0B);LCD_Write_DATA(0x88);
	LCD_Write_COM(0xD6,0x0C);LCD_Write_DATA(0x00);
	LCD_Write_COM(0xD6,0x0D);LCD_Write_DATA(0xB6);
	LCD_Write_COM(0xD6,0x0E);LCD_Write_DATA(0x00);
	LCD_Write_COM(0xD6,0x0F);LCD_Write_DATA(0xF3);
	LCD_Write_COM(0xD6,0x10);LCD_Write_DATA(0x01);
	LCD_Write_COM(0xD6,0x11);LCD_Write_DATA(0x22);
	LCD_Write_COM(0xD6,0x12);LCD_Write_DATA(0x01);
	LCD_Write_COM(0xD6,0x13);LCD_Write_DATA(0x64);
	LCD_Write_COM(0xD6,0x14);LCD_Write_DATA(0x01);
	LCD_Write_COM(0xD6,0x15);LCD_Write_DATA(0x92);
	LCD_Write_COM(0xD6,0x16);LCD_Write_DATA(0x01);
	LCD_Write_COM(0xD6,0x17);LCD_Write_DATA(0xD4);
	LCD_Write_COM(0xD6,0x18);LCD_Write_DATA(0x02);	
	LCD_Write_COM(0xD6,0x19);LCD_Write_DATA(0x07);
	LCD_Write_COM(0xD6,0x1A);LCD_Write_DATA(0x02);
	LCD_Write_COM(0xD6,0x1B);LCD_Write_DATA(0x08);
	LCD_Write_COM(0xD6,0x1C);LCD_Write_DATA(0x02);
	LCD_Write_COM(0xD6,0x1D);LCD_Write_DATA(0x34);
	LCD_Write_COM(0xD6,0x1E);LCD_Write_DATA(0x02);
	LCD_Write_COM(0xD6,0x1F);LCD_Write_DATA(0x5F); 
	LCD_Write_COM(0xD6,0x20);LCD_Write_DATA(0x02);
	LCD_Write_COM(0xD6,0x21);LCD_Write_DATA(0x78);
	LCD_Write_COM(0xD6,0x22);LCD_Write_DATA(0x02);
	LCD_Write_COM(0xD6,0x23);LCD_Write_DATA(0x94);
	LCD_Write_COM(0xD6,0x24);LCD_Write_DATA(0x02);
	LCD_Write_COM(0xD6,0x25);LCD_Write_DATA(0xA6);
	LCD_Write_COM(0xD6,0x26);LCD_Write_DATA(0x02);
	LCD_Write_COM(0xD6,0x27);LCD_Write_DATA(0xBB);
	LCD_Write_COM(0xD6,0x28);LCD_Write_DATA(0x02); 
	LCD_Write_COM(0xD6,0x29);LCD_Write_DATA(0xCA);
	LCD_Write_COM(0xD6,0x2A);LCD_Write_DATA(0x02);
	LCD_Write_COM(0xD6,0x2B);LCD_Write_DATA(0xDB);
	LCD_Write_COM(0xD6,0x2C);LCD_Write_DATA(0x02);
	LCD_Write_COM(0xD6,0x2D);LCD_Write_DATA(0xE8);
	LCD_Write_COM(0xD6,0x2E);LCD_Write_DATA(0x02);
	LCD_Write_COM(0xD6,0x2F);LCD_Write_DATA(0xF9); 
	LCD_Write_COM(0xD6,0x30);LCD_Write_DATA(0x03); 
	LCD_Write_COM(0xD6,0x31);LCD_Write_DATA(0x1F);
	LCD_Write_COM(0xD6,0x32);LCD_Write_DATA(0x03);
	LCD_Write_COM(0xD6,0x33);LCD_Write_DATA(0x7F);
	 
	//#LV2 Page 0 enable
	LCD_Write_COM(0xF0,0x00);LCD_Write_DATA(0x55);
	LCD_Write_COM(0xF0,0x01);LCD_Write_DATA(0xAA);
	LCD_Write_COM(0xF0,0x02);LCD_Write_DATA(0x52);
	LCD_Write_COM(0xF0,0x03);LCD_Write_DATA(0x08);
	LCD_Write_COM(0xF0,0x04);LCD_Write_DATA(0x00); 
	
	//#DISPLAY CONTROL
	LCD_Write_COM(0xB1,0x00);LCD_Write_DATA(0xCC);
	LCD_Write_COM(0xB1,0x01);LCD_Write_DATA(0x00); 
	
	//#SOURCE HOLD TIME
	LCD_Write_COM(0xB6,0x00);LCD_Write_DATA(0x05);
	
	//Set Gate EQ     
	LCD_Write_COM(0xB7,0x00);LCD_Write_DATA(0x70); 
	LCD_Write_COM(0xB7,0x01);LCD_Write_DATA(0x70);
	
	//#Source EQ control (Mode 2)
	LCD_Write_COM(0xB8,0x00);LCD_Write_DATA(0x01);
	LCD_Write_COM(0xB8,0x01);LCD_Write_DATA(0x03);
	LCD_Write_COM(0xB8,0x02);LCD_Write_DATA(0x03);
	LCD_Write_COM(0xB8,0x03);LCD_Write_DATA(0x03);
	
	//#INVERSION MODE
	LCD_Write_COM(0xBC,0x00);LCD_Write_DATA(0x02);
	LCD_Write_COM(0xBC,0x01);LCD_Write_DATA(0x00);	
	LCD_Write_COM(0xBC,0x02);LCD_Write_DATA(0x00); 
	
	//#Timing control
	LCD_Write_COM(0xC9,0x00);LCD_Write_DATA(0xD0);   
	LCD_Write_COM(0xC9,0x01);LCD_Write_DATA(0x02);
	LCD_Write_COM(0xC9,0x02);LCD_Write_DATA(0x50);
	LCD_Write_COM(0xC9,0x03);LCD_Write_DATA(0x50); 
	LCD_Write_COM(0xC9,0x04);LCD_Write_DATA(0x50); 
	

   	LCD_Write_COM(0x35,0x00);LCD_Write_DATA(0x00); 


  	LCD_Write_COM(0x3A,0x00);LCD_Write_DATA(0x55); //Data format 16-Bits

  	LCD_Write_COM(0x36,0x00);LCD_Write_DATA(0x00);   

  	LCD_Write_COM(0x11,0x00);   //StartUp  
  
  	delay_ms(120);

  	LCD_Write_COM(0x29,0x00);   //Display On  
   	delay_ms(100);
	
	REG_PORT_OUTSET1 = LCD_Chip_Select;
	
}


void LCD_hw_special_init()
{
	REG_PORT_DIRSET1 = 0x00010000;
	REG_PORT_OUTSET1 = PORT_PB16;
	
	REG_PORT_DIRSET1 = LCD_Read_Strobe;
	REG_PORT_DIRSET1 = LCD_Write_Strobe;
	REG_PORT_DIRSET1 = LCD_Reset;
	REG_PORT_DIRSET1 = LCD_Data_Command;
	REG_PORT_DIRSET1 = LCD_Chip_Select;
	
}

void LCD_Write_Bus(char VH,char VL)
{

	REG_PORT_OUTCLR1 = 0x0000ffff;
	REG_PORT_OUTSET1 = (VH << 8) | VL;
	REG_PORT_OUTCLR1 = LCD_Write_Strobe;
	REG_PORT_OUTSET1 = LCD_Write_Strobe;
}

//LCD_Write_COM writes 8-bit command
void LCD_Write_COM(char VL)
{
	REG_PORT_OUTCLR1 = LCD_Data_Command;
	LCD_Write_Bus(0x00,VL);
}

//LCD_Write_Com writes 16-bit command
void LCD_Write_COM(char VH, char VL)
{
	REG_PORT_OUTCLR1 = LCD_Data_Command;
	LCD_Write_Bus(VH, VL);
}

//LCD_Write_Data writes data 16-bit
void LCD_Write_DATA(char VH, char VL)
{
	REG_PORT_OUTSET1 = LCD_Data_Command;
	LCD_Write_Bus(VH,VL);
}

//LCD_Write_Data writes 8-bit data
void LCD_Write_DATA(char VL)
{
	REG_PORT_OUTSET1 = LCD_Data_Command;
	LCD_Write_Bus(0x00,VL);
}

void LCD_Write_COM_DATA(char com1, int dat1)
{
	LCD_Write_COM(com1);
	LCD_Write_DATA(dat1>>8,dat1);
}

void setXY(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2)
{
	swap(unsigned int, x1, y1);
	swap(unsigned int, x2, y2);
	y1 = disp_y_size-y1;
	y2 = disp_y_size-y2;
	swap(unsigned int, y1, y2);
	
	LCD_Write_COM(0x2a,0x00);
	LCD_Write_DATA(x1>>8);
	LCD_Write_COM(0x2a,0x01);
	LCD_Write_DATA(x1);
	LCD_Write_COM(0x2a,0x02);
	LCD_Write_DATA(x2>>8);
	LCD_Write_COM(0x2a,0x03);
	LCD_Write_DATA(x2);
	
	LCD_Write_COM(0x2b,0x00);
	LCD_Write_DATA(y1>>8);
	LCD_Write_COM(0x2b,0x01);
	LCD_Write_DATA(y1);
	LCD_Write_COM(0x2b,0x02);
	LCD_Write_DATA(y2>>8);
	LCD_Write_COM(0x2b,0x03);
	LCD_Write_DATA(y2);

	LCD_Write_COM(0x2c,0x00);
}

void LCD_set_direction_registers(void)
{

	REG_PORT_DIRSET1 = 0x0000ffff;

}

void LCD_fast_fill_16(int ch, int cl, long pix)
{
	long blocks;

	REG_PORT_OUTCLR1 = 0x0000ffff;
	REG_PORT_OUTSET1 = (ch << 8) | cl;

	blocks = pix/16;
	for (int i=0; i<blocks; i++)
	{
		REG_PORT_OUTCLR1 = LCD_Write_Strobe;
		REG_PORT_OUTSET1 = LCD_Write_Strobe;
		REG_PORT_OUTCLR1 = LCD_Write_Strobe;
		REG_PORT_OUTSET1 = LCD_Write_Strobe;
		REG_PORT_OUTCLR1 = LCD_Write_Strobe;
		REG_PORT_OUTSET1 = LCD_Write_Strobe;
		REG_PORT_OUTCLR1 = LCD_Write_Strobe;
		REG_PORT_OUTSET1 = LCD_Write_Strobe;
		REG_PORT_OUTCLR1 = LCD_Write_Strobe;
		REG_PORT_OUTSET1 = LCD_Write_Strobe;
		REG_PORT_OUTCLR1 = LCD_Write_Strobe;
		REG_PORT_OUTSET1 = LCD_Write_Strobe;
		REG_PORT_OUTCLR1 = LCD_Write_Strobe;
		REG_PORT_OUTSET1 = LCD_Write_Strobe;
		REG_PORT_OUTCLR1 = LCD_Write_Strobe;
		REG_PORT_OUTSET1 = LCD_Write_Strobe;
		REG_PORT_OUTCLR1 = LCD_Write_Strobe;
		REG_PORT_OUTSET1 = LCD_Write_Strobe;
		REG_PORT_OUTCLR1 = LCD_Write_Strobe;
		REG_PORT_OUTSET1 = LCD_Write_Strobe;
		REG_PORT_OUTCLR1 = LCD_Write_Strobe;
		REG_PORT_OUTSET1 = LCD_Write_Strobe;
		REG_PORT_OUTCLR1 = LCD_Write_Strobe;
		REG_PORT_OUTSET1 = LCD_Write_Strobe;
		REG_PORT_OUTCLR1 = LCD_Write_Strobe;
		REG_PORT_OUTSET1 = LCD_Write_Strobe;
		REG_PORT_OUTCLR1 = LCD_Write_Strobe;
		REG_PORT_OUTSET1 = LCD_Write_Strobe;
		REG_PORT_OUTCLR1 = LCD_Write_Strobe;
		REG_PORT_OUTSET1 = LCD_Write_Strobe;
		REG_PORT_OUTCLR1 = LCD_Write_Strobe;
		REG_PORT_OUTSET1 = LCD_Write_Strobe;	
	}
	if ((pix % 16) != 0)
	for (int i=0; i<(pix % 16)+1; i++)
	{
		REG_PORT_OUTCLR1 = LCD_Write_Strobe;
		REG_PORT_OUTSET1 = LCD_Write_Strobe;
	}
}

void LCD_fast_fill_8(int ch, long pix)
{
	long blocks;

	REG_PORT_OUTCLR1 = 0x0000ffff;
	REG_PORT_OUTSET1 = ch << 8;


	blocks = pix/16;
	for (int i=0; i<blocks; i++)
	{
		REG_PORT_OUTCLR1 = LCD_Write_Strobe;
		REG_PORT_OUTSET1 = LCD_Write_Strobe;
		REG_PORT_OUTCLR1 = LCD_Write_Strobe;
		REG_PORT_OUTSET1 = LCD_Write_Strobe;
		REG_PORT_OUTCLR1 = LCD_Write_Strobe;
		REG_PORT_OUTSET1 = LCD_Write_Strobe;
		REG_PORT_OUTCLR1 = LCD_Write_Strobe;
		REG_PORT_OUTSET1 = LCD_Write_Strobe;
		REG_PORT_OUTCLR1 = LCD_Write_Strobe;
		REG_PORT_OUTSET1 = LCD_Write_Strobe;
		REG_PORT_OUTCLR1 = LCD_Write_Strobe;
		REG_PORT_OUTSET1 = LCD_Write_Strobe;
		REG_PORT_OUTCLR1 = LCD_Write_Strobe;
		REG_PORT_OUTSET1 = LCD_Write_Strobe;
		REG_PORT_OUTCLR1 = LCD_Write_Strobe;
		REG_PORT_OUTSET1 = LCD_Write_Strobe;
		REG_PORT_OUTCLR1 = LCD_Write_Strobe;
		REG_PORT_OUTSET1 = LCD_Write_Strobe;
		REG_PORT_OUTCLR1 = LCD_Write_Strobe;
		REG_PORT_OUTSET1 = LCD_Write_Strobe;
		REG_PORT_OUTCLR1 = LCD_Write_Strobe;
		REG_PORT_OUTSET1 = LCD_Write_Strobe;
		REG_PORT_OUTCLR1 = LCD_Write_Strobe;
		REG_PORT_OUTSET1 = LCD_Write_Strobe;
		REG_PORT_OUTCLR1 = LCD_Write_Strobe;
		REG_PORT_OUTSET1 = LCD_Write_Strobe;
		REG_PORT_OUTCLR1 = LCD_Write_Strobe;
		REG_PORT_OUTSET1 = LCD_Write_Strobe;
		REG_PORT_OUTCLR1 = LCD_Write_Strobe;
		REG_PORT_OUTSET1 = LCD_Write_Strobe;
		REG_PORT_OUTCLR1 = LCD_Write_Strobe;
		REG_PORT_OUTSET1 = LCD_Write_Strobe;
		
		REG_PORT_OUTCLR1 = LCD_Write_Strobe;
		REG_PORT_OUTSET1 = LCD_Write_Strobe;
		REG_PORT_OUTCLR1 = LCD_Write_Strobe;
		REG_PORT_OUTSET1 = LCD_Write_Strobe;
		REG_PORT_OUTCLR1 = LCD_Write_Strobe;
		REG_PORT_OUTSET1 = LCD_Write_Strobe;
		REG_PORT_OUTCLR1 = LCD_Write_Strobe;
		REG_PORT_OUTSET1 = LCD_Write_Strobe;
		REG_PORT_OUTCLR1 = LCD_Write_Strobe;
		REG_PORT_OUTSET1 = LCD_Write_Strobe;
		REG_PORT_OUTCLR1 = LCD_Write_Strobe;
		REG_PORT_OUTSET1 = LCD_Write_Strobe;
		REG_PORT_OUTCLR1 = LCD_Write_Strobe;
		REG_PORT_OUTSET1 = LCD_Write_Strobe;
		REG_PORT_OUTCLR1 = LCD_Write_Strobe;
		REG_PORT_OUTSET1 = LCD_Write_Strobe;
		REG_PORT_OUTCLR1 = LCD_Write_Strobe;
		REG_PORT_OUTSET1 = LCD_Write_Strobe;
		REG_PORT_OUTCLR1 = LCD_Write_Strobe;
		REG_PORT_OUTSET1 = LCD_Write_Strobe;
		REG_PORT_OUTCLR1 = LCD_Write_Strobe;
		REG_PORT_OUTSET1 = LCD_Write_Strobe;
		REG_PORT_OUTCLR1 = LCD_Write_Strobe;
		REG_PORT_OUTSET1 = LCD_Write_Strobe;
		REG_PORT_OUTCLR1 = LCD_Write_Strobe;
		REG_PORT_OUTSET1 = LCD_Write_Strobe;
		REG_PORT_OUTCLR1 = LCD_Write_Strobe;
		REG_PORT_OUTSET1 = LCD_Write_Strobe;
		REG_PORT_OUTCLR1 = LCD_Write_Strobe;
		REG_PORT_OUTSET1 = LCD_Write_Strobe;
		REG_PORT_OUTCLR1 = LCD_Write_Strobe;
		REG_PORT_OUTSET1 = LCD_Write_Strobe;
	}
	if ((pix % 16) != 0)
	for (int i=0; i<(pix % 16)+1; i++)
	{
		REG_PORT_OUTCLR1 = LCD_Write_Strobe;
		REG_PORT_OUTSET1 = LCD_Write_Strobe;
		
		REG_PORT_OUTCLR1 = LCD_Write_Strobe;
		REG_PORT_OUTSET1 = LCD_Write_Strobe;
		
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
	
	
	//Code here sets LCD control pins as output
	REG_PORT_DIRSET1 = LCD_Read_Strobe;
	REG_PORT_DIRSET1 = LCD_Write_Strobe;
	REG_PORT_DIRSET1 = LCD_Reset;
	REG_PORT_DIRSET1 = LCD_Data_Command;
	REG_PORT_DIRSET1 = LCD_Chip_Select;
	
	//Configure the LCD bus (pins PB00 - PB15 as output
	REG_PORT_DIRSET1 = LCD_Data_Bus;
	
	
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
	
	ul_tickcount++	;
	while(ul_tickcount % delay_time == 0){}
		
	return;
	
}

