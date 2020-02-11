/**************************This is 80 width line*******************************/

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
*/
#include <asf.h>

/** MACROS ********************************************************************/
#define LCD_Reset PORT_PB30
#define LCD_CS	PORT_PB22
#define LCD_WR	PORT_PB17
#define LCD_DC	PORT_PB23
#define LCD_RD	PORT_PB16

#define SwapUint16(x , y) { uint16_t temp = x; x = y; y = temp; }

/** VARIABLES *****************************************************************/

char fore_Color_High, fore_Color_Low, back_Color_High, back_Color_Low;
uint16_t display_X_size = 479;
uint16_t display_Y_size = 799;


/** LOCAL PROTOTYPES **********************************************************/

void InitLCD(void);
void LCD_Write_Bus(char VH, char VL);
void LCD_Write_COM16(char VH, char VL);
void LCD_Write_COM8(char VL);
void LCD_Write_DATA16(char VH, char VL);
void LCD_Write_DATA8(char VL);

void setColorRGB(char r, char g, char b);
void setColorHex(uint16_t color);
void setBackColorRGB(char r, char g, char b);
void setBackColorHex(uint16_t color);

void clrScr(void);
void clrXY(void);
void setXY(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);

void fillRect(int x1, int y1, int x2, int y2);
void LCD_Fast_Fill(int ch, int cl, long pix);

void configure_usart(void);

struct usart_module usart_instance;

/** STUFF BEGINS HERE *********************************************************/
int main (void)
{
	system_init();
	delay_init();
	
	configure_usart();

	/* Pin Initialization, begin with pin cleared */



	
	REG_PORT_DIRSET1 = 0x0000ffff;		//this is the LCD data bus, PB00 - PB15
	REG_PORT_DIRSET1 = PORT_PB00;
	REG_PORT_DIRSET1 = PORT_PB01;
	REG_PORT_DIRSET1 = PORT_PB02;
	REG_PORT_DIRSET1 = PORT_PB03;
	REG_PORT_DIRSET1 = PORT_PB04;
	REG_PORT_DIRSET1 = PORT_PB05;
	REG_PORT_DIRSET1 = PORT_PB06;
	REG_PORT_DIRSET1 = PORT_PB07;
	REG_PORT_DIRSET1 = PORT_PB08;
	REG_PORT_DIRSET1 = PORT_PB09;
	REG_PORT_DIRSET1 = PORT_PB10;
	REG_PORT_DIRSET1 = PORT_PB11;
	REG_PORT_DIRSET1 = PORT_PB12;
	REG_PORT_DIRSET1 = PORT_PB13;
	REG_PORT_DIRSET1 = PORT_PB14;
	REG_PORT_DIRSET1 = PORT_PB15;
	
	REG_PORT_DIRSET1 = LCD_Reset;
	REG_PORT_DIRSET1 = LCD_CS;
	REG_PORT_DIRSET1 = LCD_WR;
	REG_PORT_DIRSET1 = LCD_DC;
	REG_PORT_DIRSET1 = LCD_RD;
	
	REG_PORT_OUTCLR1 = LCD_Reset;
	REG_PORT_OUTCLR1 = LCD_CS;
	REG_PORT_OUTCLR1 = LCD_WR;
	REG_PORT_OUTCLR1 = LCD_DC;
	REG_PORT_OUTCLR1 = LCD_RD;
	REG_PORT_OUTCLR1 = PORT_PB00;
	REG_PORT_OUTCLR1 = PORT_PB01;
	REG_PORT_OUTCLR1 = PORT_PB02;
	REG_PORT_OUTCLR1 = PORT_PB03;
	REG_PORT_OUTCLR1 = PORT_PB04;
	REG_PORT_OUTCLR1 = PORT_PB05;
	REG_PORT_OUTCLR1 = PORT_PB06;
	REG_PORT_OUTCLR1 = PORT_PB07;
	REG_PORT_OUTCLR1 = PORT_PB08;
	REG_PORT_OUTCLR1 = PORT_PB09;
	REG_PORT_OUTCLR1 = PORT_PB10;
	REG_PORT_OUTCLR1 = PORT_PB11;
	REG_PORT_OUTCLR1 = PORT_PB12;
	REG_PORT_OUTCLR1 = PORT_PB13;
	REG_PORT_OUTCLR1 = PORT_PB14;
	REG_PORT_OUTCLR1 = PORT_PB15;
	
	InitLCD();

	/* This skeleton code simply sets the LED to the state of the button. */
	while (1) {
		
		/*
		uint8_t string[] = "This is too fucking hard\r\n";
		usart_write_buffer_wait(&usart_instance, string, sizeof(string));
/		uint16_t temp;
		while (true) {
			if (usart_read_wait(&usart_instance, &temp) == STATUS_OK) {
				while (usart_write_wait(&usart_instance, temp) != STATUS_OK) {
				}
			}
		}
		
		*/
		clrScr();
		setColorRGB(255,0,0);
		fillRect(0,0,799,479);
		
		delay_ms(500);
		
		setColorRGB(0,255,0);
		setBackColorRGB(255,0,0);
		
		fillRect(0, 0, 799, 479);
		
		delay_ms(500);
		
		setColorRGB(0,0,255);
		setBackColorRGB(255,255,0);
		
		fillRect(0, 0, 799, 479);
		
		delay_ms(500);
		
		/* Is button pressed? */
		/* this is a sanity check and came from the default
		microchip 'set the clocks and blink a LED' project */
		if (port_pin_get_input_level(BUTTON_0_PIN) == BUTTON_0_ACTIVE) {
			/* Yes, so turn LED on. */
			delay_ms(1000);
			port_pin_set_output_level(LED_0_PIN, LED_0_ACTIVE);
		} else {
			/* No, so turn LED off. */
			port_pin_set_output_level(LED_0_PIN, !LED_0_ACTIVE);
		}
	}
}

/**************************SERCOM STUFF*******************************/
void configure_usart(void)
{
	struct usart_config config_usart;
	usart_get_config_defaults(&config_usart);
	#if(SAMR30E)
	{
		config_usart.baudrate    = 9600;
		config_usart.mux_setting = CDC_SERCOM_MUX_SETTING;
		config_usart.pinmux_pad0 = CDC_SERCOM_PINMUX_PAD0;
		config_usart.pinmux_pad1 = CDC_SERCOM_PINMUX_PAD1;
		config_usart.pinmux_pad2 = CDC_SERCOM_PINMUX_PAD2;
		config_usart.pinmux_pad3 = CDC_SERCOM_PINMUX_PAD3;
		while (usart_init(&usart_instance,
		CDC_MODULE, &config_usart) != STATUS_OK) {
		}
	}
	#else
	{
		config_usart.baudrate    = 9600;
		config_usart.mux_setting = EDBG_CDC_SERCOM_MUX_SETTING;
		config_usart.pinmux_pad0 = EDBG_CDC_SERCOM_PINMUX_PAD0;
		config_usart.pinmux_pad1 = EDBG_CDC_SERCOM_PINMUX_PAD1;
		config_usart.pinmux_pad2 = EDBG_CDC_SERCOM_PINMUX_PAD2;
		config_usart.pinmux_pad3 = EDBG_CDC_SERCOM_PINMUX_PAD3;
		while (usart_init(&usart_instance,
		EDBG_CDC_MODULE, &config_usart) != STATUS_OK) {
		}
	}
	#endif
	usart_enable(&usart_instance);
}

void fillRect(int x1, int y1, int x2, int y2)
{
	if (x1>x2)
	{
		SwapUint16(x1, x2);
	}
	if (y1>y2)
	{
		SwapUint16(y1, y2);
	}
	
	REG_PORT_OUTCLR1 = LCD_CS;
	setXY(x1, y1, x2, y2);
	REG_PORT_OUTSET1 = LCD_DC;
	LCD_Fast_Fill(fore_Color_High, fore_Color_Low, (((long)(x2-x1)+1)*((long)(y2-y1)+1)));
	REG_PORT_OUTSET1 = LCD_CS;
}

void LCD_Fast_Fill(int ch, int cl, long pix)
{
	int blocks;

	REG_PORT_OUTCLR1 = 0x0000ffff;
	REG_PORT_OUTSET1 = (ch << 8) | cl;

	blocks = pix/16;
	for (int i=0; i<blocks; i++)
	{
		REG_PORT_OUTCLR1 = LCD_WR;
		REG_PORT_OUTSET1 = LCD_WR;
		
		REG_PORT_OUTCLR1 = LCD_WR;
		REG_PORT_OUTSET1 = LCD_WR;
		
		REG_PORT_OUTCLR1 = LCD_WR;
		REG_PORT_OUTSET1 = LCD_WR;
		
		REG_PORT_OUTCLR1 = LCD_WR;
		REG_PORT_OUTSET1 = LCD_WR;
		
		REG_PORT_OUTCLR1 = LCD_WR;
		REG_PORT_OUTSET1 = LCD_WR;
		
		REG_PORT_OUTCLR1 = LCD_WR;
		REG_PORT_OUTSET1 = LCD_WR;
		
		REG_PORT_OUTCLR1 = LCD_WR;
		REG_PORT_OUTSET1 = LCD_WR;
		
		REG_PORT_OUTCLR1 = LCD_WR;
		REG_PORT_OUTSET1 = LCD_WR;
		
		REG_PORT_OUTCLR1 = LCD_WR;
		REG_PORT_OUTSET1 = LCD_WR;
		
		REG_PORT_OUTCLR1 = LCD_WR;
		REG_PORT_OUTSET1 = LCD_WR;
		
		REG_PORT_OUTCLR1 = LCD_WR;
		REG_PORT_OUTSET1 = LCD_WR;
		
		REG_PORT_OUTCLR1 = LCD_WR;
		REG_PORT_OUTSET1 = LCD_WR;
		
		REG_PORT_OUTCLR1 = LCD_WR;
		REG_PORT_OUTSET1 = LCD_WR;
		
		REG_PORT_OUTCLR1 = LCD_WR;
		REG_PORT_OUTSET1 = LCD_WR;
		
		REG_PORT_OUTCLR1 = LCD_WR;
		REG_PORT_OUTSET1 = LCD_WR;
		
		REG_PORT_OUTCLR1 = LCD_WR;
		REG_PORT_OUTSET1 = LCD_WR;
	}
	
	if ((pix % 16) != 0)
		for (int i=0; i<(pix % 16)+1; i++)
		{
			REG_PORT_OUTCLR1 = LCD_WR;
			REG_PORT_OUTSET1 = LCD_WR;
		}
}
	


void clrScr(void)
{
	REG_PORT_OUTCLR1 = LCD_CS;
	clrXY();
}

void clrXY(void)
{
	setXY(0,0,display_Y_size,display_X_size);
}

void setXY(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
		
	SwapUint16(x1, y1);
	SwapUint16(x2, y2);
	y1=display_Y_size-y1;
	y2=display_Y_size-y2;
	SwapUint16(y1, y2);
	
	LCD_Write_COM16(0x2a,0x00);
	LCD_Write_DATA8(x1>>8);
	LCD_Write_COM16(0x2a,0x01);
	LCD_Write_DATA8(x1);
	LCD_Write_COM16(0x2a,0x02);
	LCD_Write_DATA8(x2>>8);
	LCD_Write_COM16(0x2a,0x03);
	LCD_Write_DATA8(x2);


	LCD_Write_COM16(0x2b,0x00);
	LCD_Write_DATA8(y1>>8);
	LCD_Write_COM16(0x2b,0x01);
	LCD_Write_DATA8(y1);
	LCD_Write_COM16(0x2b,0x02);
	LCD_Write_DATA8(y2>>8);
	LCD_Write_COM16(0x2b,0x03);
	LCD_Write_DATA8(y2);

	LCD_Write_COM16(0x2c,0x00);
}


void LCD_Write_Bus(char VH, char VL)
{
	REG_PORT_OUTCLR1 = 0x0000ffff;
	REG_PORT_OUTSET1 = (VH << 8) | VL;
	REG_PORT_OUTCLR1 = LCD_WR;
	REG_PORT_OUTSET1 = LCD_WR;
}

void LCD_Write_COM16(char VH, char VL)
{
	REG_PORT_OUTCLR1 = LCD_DC;
	LCD_Write_Bus(VH,VL);
}

void LCD_Write_COM8(char VL)
{
	REG_PORT_OUTCLR1 = LCD_DC;
	LCD_Write_Bus(0x00, VL);
}

void LCD_Write_DATA16(char VH, char VL)
{
	REG_PORT_OUTSET1 = LCD_DC;
	LCD_Write_Bus(VH,VL);
}

void LCD_Write_DATA8(char VL)
{
	REG_PORT_OUTSET1 = LCD_DC;
	LCD_Write_Bus(0x00, VL);
}

void InitLCD(void)
{
	
	/*
	InitLCD() sets the pinMode of all the LCD control pins (write, read, D/C, 
	Chip Select, Reset) as output. Then follows data sheet initialization:
	
	0) for some fucking reason, pull PB16 high
	1) pull Reset high, delay 5ms
	2) pull Reset low, delay 15ms
	3) pull Reset high, delay 15ms
	4) pull Chip Select low
	5) Write initialization procedure for LCD
		5a) this includes 120ms delay after startup
			and 100ms delay after turning the display on
			(command 0x29..)
			resulting in total time to initialize display as 255ms
			(120+100+15+15+5). This does not include writing all black
			to the display.
	6) pull Chip Select high.
	*/
	
	REG_PORT_DIRSET1 = 0x00010000;
	REG_PORT_OUTSET1 = PORT_PB16;
	
	REG_PORT_OUTSET1 = LCD_Reset;
	delay_ms(5);
	REG_PORT_OUTCLR1 = LCD_Reset;
	delay_ms(15);
	REG_PORT_OUTSET1 = LCD_Reset;
	REG_PORT_OUTCLR1 = LCD_CS;		
	
	//LCD CS pin can be permanently grounded per data sheet version 0.00 page 85
	//However, we're going to do whatever I stole from the Chinese in this 
	//instance because this is a fucking load of bullshit
									
	LCD_Write_COM16(0xF0,0x00);	LCD_Write_DATA8(0x55);
	LCD_Write_COM16(0xF0,0x01);	LCD_Write_DATA8(0xAA);
	LCD_Write_COM16(0xF0,0x02);	LCD_Write_DATA8(0x52);
	LCD_Write_COM16(0xF0,0x03);	LCD_Write_DATA8(0x08);
	LCD_Write_COM16(0xF0,0x04);	LCD_Write_DATA8(0x01);
	
	//#AVDD Set AVDD 5.2V
	LCD_Write_COM16(0xB0,0x00);	LCD_Write_DATA8(0x0D);
	LCD_Write_COM16(0xB0,0x01);	LCD_Write_DATA8(0x0D);
	LCD_Write_COM16(0xB0,0x02);	LCD_Write_DATA8(0x0D);
	
	//#AVDD ratio
	LCD_Write_COM16(0xB6,0x00);	LCD_Write_DATA8(0x34);
	LCD_Write_COM16(0xB6,0x01);	LCD_Write_DATA8(0x34);
	LCD_Write_COM16(0xB6,0x02);	LCD_Write_DATA8(0x34);
	 
	//#AVEE  -5.2V
	LCD_Write_COM16(0xB1,0x00);	LCD_Write_DATA8(0x0D);
	LCD_Write_COM16(0xB1,0x01);	LCD_Write_DATA8(0x0D);
	LCD_Write_COM16(0xB1,0x02);	LCD_Write_DATA8(0x0D);
	
	//#AVEE ratio
	LCD_Write_COM16(0xB7,0x00);	LCD_Write_DATA8(0x34);
	LCD_Write_COM16(0xB7,0x01);	LCD_Write_DATA8(0x34);
	LCD_Write_COM16(0xB7,0x02);	LCD_Write_DATA8(0x34);
	
	//#VCL  -2.5V
	LCD_Write_COM16(0xB2,0x00);	LCD_Write_DATA8(0x00);
	LCD_Write_COM16(0xB2,0x01);	LCD_Write_DATA8(0x00);
	LCD_Write_COM16(0xB2,0x02);	LCD_Write_DATA8(0x00);
	
	//#VCL ratio
	LCD_Write_COM16(0xB8,0x00);	LCD_Write_DATA8(0x24);
	LCD_Write_COM16(0xB8,0x01);	LCD_Write_DATA8(0x24);
	LCD_Write_COM16(0xB8,0x02);	LCD_Write_DATA8(0x24); 
	
	//#VGH  15V
	LCD_Write_COM16(0xBF,0x00);	LCD_Write_DATA8(0x01);
	LCD_Write_COM16(0xB3,0x00);	LCD_Write_DATA8(0x0F);
	LCD_Write_COM16(0xB3,0x01);	LCD_Write_DATA8(0x0F);
	LCD_Write_COM16(0xB3,0x02);	LCD_Write_DATA8(0x0F);
	
	//#VGH  ratio
	LCD_Write_COM16(0xB9,0x00);	LCD_Write_DATA8(0x34);
	LCD_Write_COM16(0xB9,0x01);	LCD_Write_DATA8(0x34);
	LCD_Write_COM16(0xB9,0x02);	LCD_Write_DATA8(0x34); 
	
	//#VGL_REG  -10V
	LCD_Write_COM16(0xB5,0x00);	LCD_Write_DATA8(0x08);
	LCD_Write_COM16(0xB5,0x00);	LCD_Write_DATA8(0x08);
	LCD_Write_COM16(0xB5,0x01);	LCD_Write_DATA8(0x08);
	LCD_Write_COM16(0xC2,0x00);	LCD_Write_DATA8(0x03);
	
	//#VGLX  ratio
	LCD_Write_COM16(0xBA,0x00);	LCD_Write_DATA8(0x24);
	LCD_Write_COM16(0xBA,0x01);	LCD_Write_DATA8(0x24);
	LCD_Write_COM16(0xBA,0x02);	LCD_Write_DATA8(0x24);
	
	//#VGMP/VGSP 4.5V/0V
	LCD_Write_COM16(0xBC,0x00);	LCD_Write_DATA8(0x00);
	LCD_Write_COM16(0xBC,0x01);	LCD_Write_DATA8(0x78);
	LCD_Write_COM16(0xBC,0x02);	LCD_Write_DATA8(0x00);
	
	//#VGMN/VGSN -4.5V/0V
	LCD_Write_COM16(0xBD,0x00);	LCD_Write_DATA8(0x00);
	LCD_Write_COM16(0xBD,0x01);	LCD_Write_DATA8(0x78);
	LCD_Write_COM16(0xBD,0x02);	LCD_Write_DATA8(0x00);
	
	//#VCOM  -1.325V
	LCD_Write_COM16(0xBE,0x00);	LCD_Write_DATA8(0x00);
	LCD_Write_COM16(0xBE,0x01);	LCD_Write_DATA8(0x89);
	
	 //Gamma Setting	 
	LCD_Write_COM16(0xD1,0x00);	LCD_Write_DATA8(0x00);
	LCD_Write_COM16(0xD1,0x01);	LCD_Write_DATA8(0x2D);
	LCD_Write_COM16(0xD1,0x02);	LCD_Write_DATA8(0x00);
	LCD_Write_COM16(0xD1,0x03);	LCD_Write_DATA8(0x2E);
	LCD_Write_COM16(0xD1,0x04);	LCD_Write_DATA8(0x00); 
	LCD_Write_COM16(0xD1,0x05);	LCD_Write_DATA8(0x32);
	LCD_Write_COM16(0xD1,0x06);	LCD_Write_DATA8(0x00);
	LCD_Write_COM16(0xD1,0x07);	LCD_Write_DATA8(0x44);
	LCD_Write_COM16(0xD1,0x08);	LCD_Write_DATA8(0x00);
	LCD_Write_COM16(0xD1,0x09);	LCD_Write_DATA8(0x53);
	LCD_Write_COM16(0xD1,0x0A);	LCD_Write_DATA8(0x00);
	LCD_Write_COM16(0xD1,0x0B);	LCD_Write_DATA8(0x88);
	LCD_Write_COM16(0xD1,0x0C);	LCD_Write_DATA8(0x00);
	LCD_Write_COM16(0xD1,0x0D);	LCD_Write_DATA8(0xB6);
	LCD_Write_COM16(0xD1,0x0E);	LCD_Write_DATA8(0x00);
	LCD_Write_COM16(0xD1,0x0F);	LCD_Write_DATA8(0xF3);
	LCD_Write_COM16(0xD1,0x10);	LCD_Write_DATA8(0x01);
	LCD_Write_COM16(0xD1,0x11);	LCD_Write_DATA8(0x22);
	LCD_Write_COM16(0xD1,0x12);	LCD_Write_DATA8(0x01);
	LCD_Write_COM16(0xD1,0x13);	LCD_Write_DATA8(0x64);
	LCD_Write_COM16(0xD1,0x14);	LCD_Write_DATA8(0x01);
	LCD_Write_COM16(0xD1,0x15);	LCD_Write_DATA8(0x92);
	LCD_Write_COM16(0xD1,0x16);	LCD_Write_DATA8(0x01);
	LCD_Write_COM16(0xD1,0x17);	LCD_Write_DATA8(0xD4);
	LCD_Write_COM16(0xD1,0x18);	LCD_Write_DATA8(0x02);	
	LCD_Write_COM16(0xD1,0x19);	LCD_Write_DATA8(0x07);
	LCD_Write_COM16(0xD1,0x1A);	LCD_Write_DATA8(0x02);
	LCD_Write_COM16(0xD1,0x1B);	LCD_Write_DATA8(0x08);
	LCD_Write_COM16(0xD1,0x1C);	LCD_Write_DATA8(0x02);
	LCD_Write_COM16(0xD1,0x1D);	LCD_Write_DATA8(0x34);
	LCD_Write_COM16(0xD1,0x1E);	LCD_Write_DATA8(0x02);
	LCD_Write_COM16(0xD1,0x1F);	LCD_Write_DATA8(0x5F);
	LCD_Write_COM16(0xD1,0x20);	LCD_Write_DATA8(0x02);
	LCD_Write_COM16(0xD1,0x21);	LCD_Write_DATA8(0x78);
	LCD_Write_COM16(0xD1,0x22);	LCD_Write_DATA8(0x02);
	LCD_Write_COM16(0xD1,0x23);	LCD_Write_DATA8(0x94);
	LCD_Write_COM16(0xD1,0x24);	LCD_Write_DATA8(0x02);
	LCD_Write_COM16(0xD1,0x25);	LCD_Write_DATA8(0xA6);
	LCD_Write_COM16(0xD1,0x26);	LCD_Write_DATA8(0x02);
	LCD_Write_COM16(0xD1,0x27);	LCD_Write_DATA8(0xBB);
	LCD_Write_COM16(0xD1,0x28);	LCD_Write_DATA8(0x02); 
	LCD_Write_COM16(0xD1,0x29);	LCD_Write_DATA8(0xCA);
	LCD_Write_COM16(0xD1,0x2A);	LCD_Write_DATA8(0x02);
	LCD_Write_COM16(0xD1,0x2B);	LCD_Write_DATA8(0xDB);
	LCD_Write_COM16(0xD1,0x2C);	LCD_Write_DATA8(0x02);
	LCD_Write_COM16(0xD1,0x2D);	LCD_Write_DATA8(0xE8);
	LCD_Write_COM16(0xD1,0x2E);	LCD_Write_DATA8(0x02);
	LCD_Write_COM16(0xD1,0x2F);	LCD_Write_DATA8(0xF9);
	LCD_Write_COM16(0xD1,0x30);	LCD_Write_DATA8(0x03); 
	LCD_Write_COM16(0xD1,0x31);	LCD_Write_DATA8(0x1F);
	LCD_Write_COM16(0xD1,0x32);	LCD_Write_DATA8(0x03);
	LCD_Write_COM16(0xD1,0x33);	LCD_Write_DATA8(0x7F);
	
	LCD_Write_COM16(0xD2,0x00);	LCD_Write_DATA8(0x00);
	LCD_Write_COM16(0xD2,0x01);	LCD_Write_DATA8(0x2D);
	LCD_Write_COM16(0xD2,0x02);	LCD_Write_DATA8(0x00);
	LCD_Write_COM16(0xD2,0x03);	LCD_Write_DATA8(0x2E);
	LCD_Write_COM16(0xD2,0x04);	LCD_Write_DATA8(0x00); 
	LCD_Write_COM16(0xD2,0x05);	LCD_Write_DATA8(0x32);
	LCD_Write_COM16(0xD2,0x06);	LCD_Write_DATA8(0x00);
	LCD_Write_COM16(0xD2,0x07);	LCD_Write_DATA8(0x44);
	LCD_Write_COM16(0xD2,0x08);	LCD_Write_DATA8(0x00);
	LCD_Write_COM16(0xD2,0x09);	LCD_Write_DATA8(0x53);
	LCD_Write_COM16(0xD2,0x0A);	LCD_Write_DATA8(0x00);
	LCD_Write_COM16(0xD2,0x0B);	LCD_Write_DATA8(0x88);
	LCD_Write_COM16(0xD2,0x0C);	LCD_Write_DATA8(0x00);
	LCD_Write_COM16(0xD2,0x0D);	LCD_Write_DATA8(0xB6);
	LCD_Write_COM16(0xD2,0x0E);	LCD_Write_DATA8(0x00);
	LCD_Write_COM16(0xD2,0x0F);	LCD_Write_DATA8(0xF3);
	LCD_Write_COM16(0xD2,0x10);	LCD_Write_DATA8(0x01);
	LCD_Write_COM16(0xD2,0x11);	LCD_Write_DATA8(0x22);
	LCD_Write_COM16(0xD2,0x12);	LCD_Write_DATA8(0x01);
	LCD_Write_COM16(0xD2,0x13);	LCD_Write_DATA8(0x64);
	LCD_Write_COM16(0xD2,0x14);	LCD_Write_DATA8(0x01);
	LCD_Write_COM16(0xD2,0x15);	LCD_Write_DATA8(0x92);
	LCD_Write_COM16(0xD2,0x16);	LCD_Write_DATA8(0x01);
	LCD_Write_COM16(0xD2,0x17);	LCD_Write_DATA8(0xD4);
	LCD_Write_COM16(0xD2,0x18);	LCD_Write_DATA8(0x02);	
	LCD_Write_COM16(0xD2,0x19);	LCD_Write_DATA8(0x07);
	LCD_Write_COM16(0xD2,0x1A);	LCD_Write_DATA8(0x02);
	LCD_Write_COM16(0xD2,0x1B);	LCD_Write_DATA8(0x08);
	LCD_Write_COM16(0xD2,0x1C);	LCD_Write_DATA8(0x02);
	LCD_Write_COM16(0xD2,0x1D);	LCD_Write_DATA8(0x34);
	LCD_Write_COM16(0xD2,0x1E);	LCD_Write_DATA8(0x02);
	LCD_Write_COM16(0xD2,0x1F);	LCD_Write_DATA8(0x5F);
	LCD_Write_COM16(0xD2,0x20);	LCD_Write_DATA8(0x02);
	LCD_Write_COM16(0xD2,0x21);	LCD_Write_DATA8(0x78);
	LCD_Write_COM16(0xD2,0x22);	LCD_Write_DATA8(0x02);
	LCD_Write_COM16(0xD2,0x23);	LCD_Write_DATA8(0x94);
	LCD_Write_COM16(0xD2,0x24);	LCD_Write_DATA8(0x02);
	LCD_Write_COM16(0xD2,0x25);	LCD_Write_DATA8(0xA6);
	LCD_Write_COM16(0xD2,0x26);	LCD_Write_DATA8(0x02);
	LCD_Write_COM16(0xD2,0x27);	LCD_Write_DATA8(0xBB);
	LCD_Write_COM16(0xD2,0x28);	LCD_Write_DATA8(0x02); 
	LCD_Write_COM16(0xD2,0x29);	LCD_Write_DATA8(0xCA);
	LCD_Write_COM16(0xD2,0x2A);	LCD_Write_DATA8(0x02);
	LCD_Write_COM16(0xD2,0x2B);	LCD_Write_DATA8(0xDB);
	LCD_Write_COM16(0xD2,0x2C);	LCD_Write_DATA8(0x02);
	LCD_Write_COM16(0xD2,0x2D);	LCD_Write_DATA8(0xE8);
	LCD_Write_COM16(0xD2,0x2E);	LCD_Write_DATA8(0x02);
	LCD_Write_COM16(0xD2,0x2F);	LCD_Write_DATA8(0xF9);
	LCD_Write_COM16(0xD2,0x30);	LCD_Write_DATA8(0x03); 
	LCD_Write_COM16(0xD2,0x31);	LCD_Write_DATA8(0x1F);
	LCD_Write_COM16(0xD2,0x32);	LCD_Write_DATA8(0x03);
	LCD_Write_COM16(0xD2,0x33);	LCD_Write_DATA8(0x7F);
		 
	LCD_Write_COM16(0xD3,0x00);	LCD_Write_DATA8(0x00);
	LCD_Write_COM16(0xD3,0x01);	LCD_Write_DATA8(0x2D);
	LCD_Write_COM16(0xD3,0x02);	LCD_Write_DATA8(0x00);
	LCD_Write_COM16(0xD3,0x03);	LCD_Write_DATA8(0x2E);
	LCD_Write_COM16(0xD3,0x04);	LCD_Write_DATA8(0x00); 
	LCD_Write_COM16(0xD3,0x05);	LCD_Write_DATA8(0x32);
	LCD_Write_COM16(0xD3,0x06);	LCD_Write_DATA8(0x00);
	LCD_Write_COM16(0xD3,0x07);	LCD_Write_DATA8(0x44);
	LCD_Write_COM16(0xD3,0x08);	LCD_Write_DATA8(0x00);
	LCD_Write_COM16(0xD3,0x09);	LCD_Write_DATA8(0x53);
	LCD_Write_COM16(0xD3,0x0A);	LCD_Write_DATA8(0x00);
	LCD_Write_COM16(0xD3,0x0B);	LCD_Write_DATA8(0x88);
	LCD_Write_COM16(0xD3,0x0C);	LCD_Write_DATA8(0x00);
	LCD_Write_COM16(0xD3,0x0D);	LCD_Write_DATA8(0xB6);
	LCD_Write_COM16(0xD3,0x0E);	LCD_Write_DATA8(0x00);
	LCD_Write_COM16(0xD3,0x0F);	LCD_Write_DATA8(0xF3);
	LCD_Write_COM16(0xD3,0x10);	LCD_Write_DATA8(0x01);
	LCD_Write_COM16(0xD3,0x11);	LCD_Write_DATA8(0x22);
	LCD_Write_COM16(0xD3,0x12);	LCD_Write_DATA8(0x01);
	LCD_Write_COM16(0xD3,0x13);	LCD_Write_DATA8(0x64);
	LCD_Write_COM16(0xD3,0x14);	LCD_Write_DATA8(0x01);
	LCD_Write_COM16(0xD3,0x15);	LCD_Write_DATA8(0x92);
	LCD_Write_COM16(0xD3,0x16);	LCD_Write_DATA8(0x01);
	LCD_Write_COM16(0xD3,0x17);	LCD_Write_DATA8(0xD4);
	LCD_Write_COM16(0xD3,0x18);	LCD_Write_DATA8(0x02);	
	LCD_Write_COM16(0xD3,0x19);	LCD_Write_DATA8(0x07);
	LCD_Write_COM16(0xD3,0x1A);	LCD_Write_DATA8(0x02);
	LCD_Write_COM16(0xD3,0x1B);	LCD_Write_DATA8(0x08);
	LCD_Write_COM16(0xD3,0x1C);	LCD_Write_DATA8(0x02);
	LCD_Write_COM16(0xD3,0x1D);	LCD_Write_DATA8(0x34);
	LCD_Write_COM16(0xD3,0x1E);	LCD_Write_DATA8(0x02);
	LCD_Write_COM16(0xD3,0x1F);	LCD_Write_DATA8(0x5F);
	LCD_Write_COM16(0xD3,0x20);	LCD_Write_DATA8(0x02);
	LCD_Write_COM16(0xD3,0x21);	LCD_Write_DATA8(0x78);
	LCD_Write_COM16(0xD3,0x22);	LCD_Write_DATA8(0x02);
	LCD_Write_COM16(0xD3,0x23);	LCD_Write_DATA8(0x94);
	LCD_Write_COM16(0xD3,0x24);	LCD_Write_DATA8(0x02);
	LCD_Write_COM16(0xD3,0x25);	LCD_Write_DATA8(0xA6);
	LCD_Write_COM16(0xD3,0x26);	LCD_Write_DATA8(0x02);
	LCD_Write_COM16(0xD3,0x27);	LCD_Write_DATA8(0xBB);
	LCD_Write_COM16(0xD3,0x28);	LCD_Write_DATA8(0x02); 
	LCD_Write_COM16(0xD3,0x29);	LCD_Write_DATA8(0xCA);
	LCD_Write_COM16(0xD3,0x2A);	LCD_Write_DATA8(0x02);
	LCD_Write_COM16(0xD3,0x2B);	LCD_Write_DATA8(0xDB);
	LCD_Write_COM16(0xD3,0x2C);	LCD_Write_DATA8(0x02);
	LCD_Write_COM16(0xD3,0x2D);	LCD_Write_DATA8(0xE8);
	LCD_Write_COM16(0xD3,0x2E);	LCD_Write_DATA8(0x02);
	LCD_Write_COM16(0xD3,0x2F);	LCD_Write_DATA8(0xF9);
	LCD_Write_COM16(0xD3,0x30);	LCD_Write_DATA8(0x03); 
	LCD_Write_COM16(0xD3,0x31);	LCD_Write_DATA8(0x1F);
	LCD_Write_COM16(0xD3,0x32);	LCD_Write_DATA8(0x03);
	LCD_Write_COM16(0xD3,0x33);	LCD_Write_DATA8(0x7F);
		 
	LCD_Write_COM16(0xD4,0x00);	LCD_Write_DATA8(0x00);
	LCD_Write_COM16(0xD4,0x01);	LCD_Write_DATA8(0x2D);
	LCD_Write_COM16(0xD4,0x02);	LCD_Write_DATA8(0x00);
	LCD_Write_COM16(0xD4,0x03);	LCD_Write_DATA8(0x2E);
	LCD_Write_COM16(0xD4,0x04);	LCD_Write_DATA8(0x00); 
	LCD_Write_COM16(0xD4,0x05);	LCD_Write_DATA8(0x32);
	LCD_Write_COM16(0xD4,0x06);	LCD_Write_DATA8(0x00);
	LCD_Write_COM16(0xD4,0x07);	LCD_Write_DATA8(0x44);
	LCD_Write_COM16(0xD4,0x08);	LCD_Write_DATA8(0x00);
	LCD_Write_COM16(0xD4,0x09);	LCD_Write_DATA8(0x53);
	LCD_Write_COM16(0xD4,0x0A);	LCD_Write_DATA8(0x00);
	LCD_Write_COM16(0xD4,0x0B);	LCD_Write_DATA8(0x88);
	LCD_Write_COM16(0xD4,0x0C);	LCD_Write_DATA8(0x00);
	LCD_Write_COM16(0xD4,0x0D);	LCD_Write_DATA8(0xB6);
	LCD_Write_COM16(0xD4,0x0E);	LCD_Write_DATA8(0x00);
	LCD_Write_COM16(0xD4,0x0F);	LCD_Write_DATA8(0xF3);
	LCD_Write_COM16(0xD4,0x10);	LCD_Write_DATA8(0x01);
	LCD_Write_COM16(0xD4,0x11);	LCD_Write_DATA8(0x22);
	LCD_Write_COM16(0xD4,0x12);	LCD_Write_DATA8(0x01);
	LCD_Write_COM16(0xD4,0x13);	LCD_Write_DATA8(0x64);
	LCD_Write_COM16(0xD4,0x14);	LCD_Write_DATA8(0x01);
	LCD_Write_COM16(0xD4,0x15);	LCD_Write_DATA8(0x92);
	LCD_Write_COM16(0xD4,0x16);	LCD_Write_DATA8(0x01);
	LCD_Write_COM16(0xD4,0x17);	LCD_Write_DATA8(0xD4);
	LCD_Write_COM16(0xD4,0x18);	LCD_Write_DATA8(0x02);	
	LCD_Write_COM16(0xD4,0x19);	LCD_Write_DATA8(0x07);
	LCD_Write_COM16(0xD4,0x1A);	LCD_Write_DATA8(0x02);
	LCD_Write_COM16(0xD4,0x1B);	LCD_Write_DATA8(0x08);
	LCD_Write_COM16(0xD4,0x1C);	LCD_Write_DATA8(0x02);
	LCD_Write_COM16(0xD4,0x1D);	LCD_Write_DATA8(0x34);
	LCD_Write_COM16(0xD4,0x1E);	LCD_Write_DATA8(0x02);
	LCD_Write_COM16(0xD4,0x1F);	LCD_Write_DATA8(0x5F);
	LCD_Write_COM16(0xD4,0x20);	LCD_Write_DATA8(0x02);
	LCD_Write_COM16(0xD4,0x21);	LCD_Write_DATA8(0x78);
	LCD_Write_COM16(0xD4,0x22);	LCD_Write_DATA8(0x02);
	LCD_Write_COM16(0xD4,0x23);	LCD_Write_DATA8(0x94);
	LCD_Write_COM16(0xD4,0x24);	LCD_Write_DATA8(0x02);
	LCD_Write_COM16(0xD4,0x25);	LCD_Write_DATA8(0xA6);
	LCD_Write_COM16(0xD4,0x26);	LCD_Write_DATA8(0x02);
	LCD_Write_COM16(0xD4,0x27);	LCD_Write_DATA8(0xBB);
	LCD_Write_COM16(0xD4,0x28);	LCD_Write_DATA8(0x02); 
	LCD_Write_COM16(0xD4,0x29);	LCD_Write_DATA8(0xCA);
	LCD_Write_COM16(0xD4,0x2A);	LCD_Write_DATA8(0x02);
	LCD_Write_COM16(0xD4,0x2B);	LCD_Write_DATA8(0xDB);
	LCD_Write_COM16(0xD4,0x2C);	LCD_Write_DATA8(0x02);
	LCD_Write_COM16(0xD4,0x2D);	LCD_Write_DATA8(0xE8);
	LCD_Write_COM16(0xD4,0x2E);	LCD_Write_DATA8(0x02);
	LCD_Write_COM16(0xD4,0x2F);	LCD_Write_DATA8(0xF9);
	LCD_Write_COM16(0xD4,0x30);	LCD_Write_DATA8(0x03); 
	LCD_Write_COM16(0xD4,0x31);	LCD_Write_DATA8(0x1F);
	LCD_Write_COM16(0xD4,0x32);	LCD_Write_DATA8(0x03);
	LCD_Write_COM16(0xD4,0x33);	LCD_Write_DATA8(0x7F);
		 
	LCD_Write_COM16(0xD5,0x00);	LCD_Write_DATA8(0x00);
	LCD_Write_COM16(0xD5,0x01);	LCD_Write_DATA8(0x2D);
	LCD_Write_COM16(0xD5,0x02);	LCD_Write_DATA8(0x00);
	LCD_Write_COM16(0xD5,0x03);	LCD_Write_DATA8(0x2E);
	LCD_Write_COM16(0xD5,0x04);	LCD_Write_DATA8(0x00); 
	LCD_Write_COM16(0xD5,0x05);	LCD_Write_DATA8(0x32);
	LCD_Write_COM16(0xD5,0x06);	LCD_Write_DATA8(0x00);
	LCD_Write_COM16(0xD5,0x07);	LCD_Write_DATA8(0x44);
	LCD_Write_COM16(0xD5,0x08);	LCD_Write_DATA8(0x00);
	LCD_Write_COM16(0xD5,0x09);	LCD_Write_DATA8(0x53);
	LCD_Write_COM16(0xD5,0x0A);	LCD_Write_DATA8(0x00);
	LCD_Write_COM16(0xD5,0x0B);	LCD_Write_DATA8(0x88);
	LCD_Write_COM16(0xD5,0x0C);	LCD_Write_DATA8(0x00);
	LCD_Write_COM16(0xD5,0x0D);	LCD_Write_DATA8(0xB6);
	LCD_Write_COM16(0xD5,0x0E);	LCD_Write_DATA8(0x00);
	LCD_Write_COM16(0xD5,0x0F);	LCD_Write_DATA8(0xF3);
	LCD_Write_COM16(0xD5,0x10);	LCD_Write_DATA8(0x01);
	LCD_Write_COM16(0xD5,0x11);	LCD_Write_DATA8(0x22);
	LCD_Write_COM16(0xD5,0x12);	LCD_Write_DATA8(0x01);
	LCD_Write_COM16(0xD5,0x13);	LCD_Write_DATA8(0x64);
	LCD_Write_COM16(0xD5,0x14);	LCD_Write_DATA8(0x01);
	LCD_Write_COM16(0xD5,0x15);	LCD_Write_DATA8(0x92);
	LCD_Write_COM16(0xD5,0x16);	LCD_Write_DATA8(0x01);
	LCD_Write_COM16(0xD5,0x17);	LCD_Write_DATA8(0xD4);
	LCD_Write_COM16(0xD5,0x18);	LCD_Write_DATA8(0x02);	
	LCD_Write_COM16(0xD5,0x19);	LCD_Write_DATA8(0x07);
	LCD_Write_COM16(0xD5,0x1A);	LCD_Write_DATA8(0x02);
	LCD_Write_COM16(0xD5,0x1B);	LCD_Write_DATA8(0x08);
	LCD_Write_COM16(0xD5,0x1C);	LCD_Write_DATA8(0x02);
	LCD_Write_COM16(0xD5,0x1D);	LCD_Write_DATA8(0x34);
	LCD_Write_COM16(0xD5,0x1E);	LCD_Write_DATA8(0x02);
	LCD_Write_COM16(0xD5,0x1F);	LCD_Write_DATA8(0x5F);
	LCD_Write_COM16(0xD5,0x20);	LCD_Write_DATA8(0x02);
	LCD_Write_COM16(0xD5,0x21);	LCD_Write_DATA8(0x78);
	LCD_Write_COM16(0xD5,0x22);	LCD_Write_DATA8(0x02);
	LCD_Write_COM16(0xD5,0x23);	LCD_Write_DATA8(0x94);
	LCD_Write_COM16(0xD5,0x24);	LCD_Write_DATA8(0x02);
	LCD_Write_COM16(0xD5,0x25);	LCD_Write_DATA8(0xA6);
	LCD_Write_COM16(0xD5,0x26);	LCD_Write_DATA8(0x02);
	LCD_Write_COM16(0xD5,0x27);	LCD_Write_DATA8(0xBB);
	LCD_Write_COM16(0xD5,0x28);	LCD_Write_DATA8(0x02); 
	LCD_Write_COM16(0xD5,0x29);	LCD_Write_DATA8(0xCA);
	LCD_Write_COM16(0xD5,0x2A);	LCD_Write_DATA8(0x02);
	LCD_Write_COM16(0xD5,0x2B);	LCD_Write_DATA8(0xDB);
	LCD_Write_COM16(0xD5,0x2C);	LCD_Write_DATA8(0x02);
	LCD_Write_COM16(0xD5,0x2D);	LCD_Write_DATA8(0xE8);
	LCD_Write_COM16(0xD5,0x2E);	LCD_Write_DATA8(0x02);
	LCD_Write_COM16(0xD5,0x2F);	LCD_Write_DATA8(0xF9);
	LCD_Write_COM16(0xD5,0x30);	LCD_Write_DATA8(0x03); 
	LCD_Write_COM16(0xD5,0x31);	LCD_Write_DATA8(0x1F);
	LCD_Write_COM16(0xD5,0x32);	LCD_Write_DATA8(0x03);
	LCD_Write_COM16(0xD5,0x33);	LCD_Write_DATA8(0x7F);
		 
	LCD_Write_COM16(0xD6,0x00);	LCD_Write_DATA8(0x00);
	LCD_Write_COM16(0xD6,0x01);	LCD_Write_DATA8(0x2D);
	LCD_Write_COM16(0xD6,0x02);	LCD_Write_DATA8(0x00);
	LCD_Write_COM16(0xD6,0x03);	LCD_Write_DATA8(0x2E);
	LCD_Write_COM16(0xD6,0x04);	LCD_Write_DATA8(0x00); 
	LCD_Write_COM16(0xD6,0x05);	LCD_Write_DATA8(0x32);
	LCD_Write_COM16(0xD6,0x06);	LCD_Write_DATA8(0x00);
	LCD_Write_COM16(0xD6,0x07);	LCD_Write_DATA8(0x44);
	LCD_Write_COM16(0xD6,0x08);	LCD_Write_DATA8(0x00);
	LCD_Write_COM16(0xD6,0x09);	LCD_Write_DATA8(0x53);
	LCD_Write_COM16(0xD6,0x0A);	LCD_Write_DATA8(0x00);
	LCD_Write_COM16(0xD6,0x0B);	LCD_Write_DATA8(0x88);
	LCD_Write_COM16(0xD6,0x0C);	LCD_Write_DATA8(0x00);
	LCD_Write_COM16(0xD6,0x0D);	LCD_Write_DATA8(0xB6);
	LCD_Write_COM16(0xD6,0x0E);	LCD_Write_DATA8(0x00);
	LCD_Write_COM16(0xD6,0x0F);	LCD_Write_DATA8(0xF3);
	LCD_Write_COM16(0xD6,0x10);	LCD_Write_DATA8(0x01);
	LCD_Write_COM16(0xD6,0x11);	LCD_Write_DATA8(0x22);
	LCD_Write_COM16(0xD6,0x12);	LCD_Write_DATA8(0x01);
	LCD_Write_COM16(0xD6,0x13);	LCD_Write_DATA8(0x64);
	LCD_Write_COM16(0xD6,0x14);	LCD_Write_DATA8(0x01);
	LCD_Write_COM16(0xD6,0x15);	LCD_Write_DATA8(0x92);
	LCD_Write_COM16(0xD6,0x16);	LCD_Write_DATA8(0x01);
	LCD_Write_COM16(0xD6,0x17);	LCD_Write_DATA8(0xD4);
	LCD_Write_COM16(0xD6,0x18);	LCD_Write_DATA8(0x02);	
	LCD_Write_COM16(0xD6,0x19);	LCD_Write_DATA8(0x07);
	LCD_Write_COM16(0xD6,0x1A);	LCD_Write_DATA8(0x02);
	LCD_Write_COM16(0xD6,0x1B);	LCD_Write_DATA8(0x08);
	LCD_Write_COM16(0xD6,0x1C);	LCD_Write_DATA8(0x02);
	LCD_Write_COM16(0xD6,0x1D);	LCD_Write_DATA8(0x34);
	LCD_Write_COM16(0xD6,0x1E);	LCD_Write_DATA8(0x02);
	LCD_Write_COM16(0xD6,0x1F);	LCD_Write_DATA8(0x5F);
	LCD_Write_COM16(0xD6,0x20);	LCD_Write_DATA8(0x02);
	LCD_Write_COM16(0xD6,0x21);	LCD_Write_DATA8(0x78);
	LCD_Write_COM16(0xD6,0x22);	LCD_Write_DATA8(0x02);
	LCD_Write_COM16(0xD6,0x23);	LCD_Write_DATA8(0x94);
	LCD_Write_COM16(0xD6,0x24);	LCD_Write_DATA8(0x02);
	LCD_Write_COM16(0xD6,0x25);	LCD_Write_DATA8(0xA6);
	LCD_Write_COM16(0xD6,0x26);	LCD_Write_DATA8(0x02);
	LCD_Write_COM16(0xD6,0x27);	LCD_Write_DATA8(0xBB);
	LCD_Write_COM16(0xD6,0x28);	LCD_Write_DATA8(0x02); 
	LCD_Write_COM16(0xD6,0x29);	LCD_Write_DATA8(0xCA);
	LCD_Write_COM16(0xD6,0x2A);	LCD_Write_DATA8(0x02);
	LCD_Write_COM16(0xD6,0x2B);	LCD_Write_DATA8(0xDB);
	LCD_Write_COM16(0xD6,0x2C);	LCD_Write_DATA8(0x02);
	LCD_Write_COM16(0xD6,0x2D);	LCD_Write_DATA8(0xE8);
	LCD_Write_COM16(0xD6,0x2E);	LCD_Write_DATA8(0x02);
	LCD_Write_COM16(0xD6,0x2F);	LCD_Write_DATA8(0xF9);
	LCD_Write_COM16(0xD6,0x30);	LCD_Write_DATA8(0x03); 
	LCD_Write_COM16(0xD6,0x31);	LCD_Write_DATA8(0x1F);
	LCD_Write_COM16(0xD6,0x32);	LCD_Write_DATA8(0x03);
	LCD_Write_COM16(0xD6,0x33);	LCD_Write_DATA8(0x7F);
	 
	//#LV2 Page 0 enable
	LCD_Write_COM16(0xF0,0x00);	LCD_Write_DATA8(0x55);
	LCD_Write_COM16(0xF0,0x01);	LCD_Write_DATA8(0xAA);
	LCD_Write_COM16(0xF0,0x02);	LCD_Write_DATA8(0x52);
	LCD_Write_COM16(0xF0,0x03);	LCD_Write_DATA8(0x08);
	LCD_Write_COM16(0xF0,0x04);	LCD_Write_DATA8(0x00); 
	
	//#DISPLAY CONTROL
	LCD_Write_COM16(0xB1,0x00);	LCD_Write_DATA8(0xCC);
	LCD_Write_COM16(0xB1,0x01);	LCD_Write_DATA8(0x00); 
	
	//#SOURCE HOLD TIME
	LCD_Write_COM16(0xB6,0x00);	LCD_Write_DATA8(0x05);
	
	//Set Gate EQ     
	LCD_Write_COM16(0xB7,0x00);	LCD_Write_DATA8(0x70); 
	LCD_Write_COM16(0xB7,0x01);	LCD_Write_DATA8(0x70);
	
	//#Source EQ control (Mode 2)
	LCD_Write_COM16(0xB8,0x00);	LCD_Write_DATA8(0x01);
	LCD_Write_COM16(0xB8,0x01);	LCD_Write_DATA8(0x03);
	LCD_Write_COM16(0xB8,0x02);	LCD_Write_DATA8(0x03);
	LCD_Write_COM16(0xB8,0x03);	LCD_Write_DATA8(0x03);
	
	//#INVERSION MODE
	LCD_Write_COM16(0xBC,0x00);	LCD_Write_DATA8(0x02);
	LCD_Write_COM16(0xBC,0x01);	LCD_Write_DATA8(0x00);	
	LCD_Write_COM16(0xBC,0x02);	LCD_Write_DATA8(0x00); 
	
	//#Timing control
	LCD_Write_COM16(0xC9,0x00);	LCD_Write_DATA8(0xD0);   
	LCD_Write_COM16(0xC9,0x01);	LCD_Write_DATA8(0x02);
	LCD_Write_COM16(0xC9,0x02);	LCD_Write_DATA8(0x50);
	LCD_Write_COM16(0xC9,0x03);	LCD_Write_DATA8(0x50); 
	LCD_Write_COM16(0xC9,0x04);	LCD_Write_DATA8(0x50); 
	

   	LCD_Write_COM16(0x35,0x00);   LCD_Write_DATA8(0x00); 


  	LCD_Write_COM16(0x3A,0x00);   LCD_Write_DATA8(0x55);

  	LCD_Write_COM16(0x36,0x00);   LCD_Write_DATA8(0x00);   


  	LCD_Write_COM16(0x11,0x00);   //StartUp  
  
  	delay_ms(120);

  	LCD_Write_COM16(0x29,0x00);   //Display On  
	  
   	delay_ms(100);
	
	REG_PORT_OUTSET1 = LCD_CS;
	
	setColorRGB(255, 255, 255);
	setBackColorRGB(0, 0, 0);
	
}

void setColorRGB(char r, char g, char b)
{
	fore_Color_High = ((r&248)|g>>5);
	fore_Color_Low = ((g&28)<<3|b>>3);
}

void setColorHex(uint16_t color)
{
	fore_Color_High = (color >> 8);
	fore_Color_Low = (color & 0xFF);
}

void setBackColorRGB(char r, char g, char b)
{
	back_Color_High = ((r&248)|g>>5);
	back_Color_Low = ((g&28)<<3|b>>3);
}

void setBackColorHex(uint16_t color)
{
	back_Color_High = (color >> 8);
	back_Color_Low = (color & 0xFF);
}
