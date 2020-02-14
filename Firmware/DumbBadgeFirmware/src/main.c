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

static uint8_t chip_Serial_Number = (0x0080A00C ^ 0x0080A040 ^ 
									0x0080A044 ^ 0x0080A048) % 65535;


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
void setPixel(uint16_t color);
void drawPixel(int x, int y);


void fillRect(int x1, int y1, int x2, int y2);
void LCD_Fast_Fill(int ch, int cl, long pix);
void drawKare(void);

void configure_usart(void);

struct usart_module usart_instance;

/** STUFF BEGINS HERE *********************************************************/
int main (void)
{
	system_init();
	delay_init();

	srand(chip_Serial_Number);

	configure_usart();

	/* Pin Initialization, begin with pin cleared */

	REG_PORT_DIRSET1 = 0x0000ffff;		//this is the LCD data bus, PB00 - PB15
	REG_PORT_DIRSET1 = LCD_Reset;
	REG_PORT_DIRSET1 = LCD_CS;
	REG_PORT_DIRSET1 = LCD_WR;
	REG_PORT_DIRSET1 = LCD_DC;
	REG_PORT_DIRSET1 = LCD_RD;

	REG_PORT_OUTCLR1 = 0x0000ffff;	
	REG_PORT_OUTCLR1 = LCD_Reset;
	REG_PORT_OUTCLR1 = LCD_CS;
	REG_PORT_OUTCLR1 = LCD_WR;
	REG_PORT_OUTCLR1 = LCD_DC;
	REG_PORT_OUTCLR1 = LCD_RD;

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
		setColorRGB(0,0,0);
		setBackColorRGB(0,0,0);
		fillRect(0,0,799,479);
		
		drawKare();
		
		delay_ms(5000);
		
		setColorRGB(255,0,0);
		fillRect(0,0,799,479);
		
		/*
		
		delay_ms(500);
		
		setColorRGB(0,255,0);
		setBackColorRGB(255,0,0);
		
		fillRect(0, 0, 799, 479);
		
		delay_ms(500);
		
		setColorRGB(0,0,255);
		setBackColorRGB(255,255,0);
		
		fillRect(0, 0, 799, 479);
		
		delay_ms(500);
		
		setColorRGB(0,0,0);
		setBackColorRGB(0,0,0);
		
		fillRect(0, 0, 799, 479);

		for(int i = 0; i<100; i++)
		{
			switch (rand()%3)
			{
				case 0: setColorRGB(255,0,0); break;
				case 1: setColorRGB(0,255,0); break;
				case 2: setColorRGB(0,0,255); break;
			}
			drawPixel((rand()%800), (rand()%480));
		}
		
		*/
		delay_ms(1000);
		
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


/**************************LCD STUFF**********************************/

void setPixel(uint16_t color)
{
	//Sets color to rrrrrggggggbbbbb
	LCD_Write_DATA16((color>>8),(color&0xFF)); 
}

void drawPixel(int x, int y)
{
	REG_PORT_OUTCLR1 = LCD_CS;
	setXY(x,y,x,y);
	setPixel((fore_Color_High<<8)|fore_Color_Low);
	REG_PORT_OUTSET1 = LCD_CS;
	clrXY();
}

void fillRect(int x1, int y1, int x2, int y2)
{
	if (x1>x2)
		SwapUint16(x1, x2);
	if (y1>y2)
		SwapUint16(y1, y2);
	
	REG_PORT_OUTCLR1 = LCD_CS;
	setXY(x1, y1, x2, y2);
	REG_PORT_OUTSET1 = LCD_DC;
	LCD_Fast_Fill(fore_Color_High, fore_Color_Low, 
		(((long)(x2-x1)+1)*((long)(y2-y1)+1)));
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
		for (int j=0; j<16; j++)
		{
			REG_PORT_OUTCLR1 = LCD_WR;
			REG_PORT_OUTSET1 = LCD_WR;
		}
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
	setXY(0,0,display_X_size,display_Y_size);
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

void drawKare(void)
{

	uint16_t graphic[104] = {10,10,20,20,20,0,380,10,380,10,390,20,0,20,10,290,390,20,400,290,
		10,290,20,300,380,290,390,300,20,300,380,310,0,30,50,40,0,50,50,60,80,30,280,40,70,40,
		80,190,80,190,280,200,280,40,290,190,0,70,50,80,0,90,50,100,0,110,50,120,0,130,50,140,
		0,150,50,160,0,170,50,180,0,190,50,200,300,200,370,210,30,220,370,230,30,240,370,250,
		30,260,370,270,90,280,300,290};
		
	uint16_t happyface[28] = {180,80,190,130,170,130,190,140,140,60,150,100,210,60,220,100,
		130,150,140,160,140,160,220,170,220,150,230,160};

	int offsetGraphicX = 190;
	int offsetGraphicY = 70;
	int scaleGraphic = 1;
	
	setBackColorRGB(0,0,0);
	setColorRGB(0,0,0);
	
	fillRect(0,0,display_X_size,display_Y_size);
	
	setColorRGB(255,255,255);
	setBackColorRGB(0,0,0);
	
	for(int i = 0; i < 104; i = i+4)
	{
		fillRect(graphic[i]+offsetGraphicX,graphic[i+1]+offsetGraphicY,graphic[i+2]+offsetGraphicX,graphic[i+3]+offsetGraphicY);
	}
	
	for(int i = 0; i < 28; i = i+4)
	{
		fillRect((happyface[i]+offsetGraphicX)*scaleGraphic,(happyface[i+1]+offsetGraphicY)*scaleGraphic,
		(happyface[i+2]+offsetGraphicX)*scaleGraphic,(happyface[i+3]+offsetGraphicY)*scaleGraphic);
	}
	
}



/**************************InitLCD()**********************************/
void InitLCD(void)
{
	
	/*
	InitLCD() sets the pinMode of all the LCD control pins (write,
	read, D/C, Chip Select, Reset) as output. Then follows data 
	sheet initialization:
	
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
			(120+100+15+15+5). This does not include writing all
			black to the display.
		5b) I have changed this to a 5ms startup; seems to work.
	6) pull Chip Select high.
	
	If you are reading this, I must impress something upon you: I
	don't have any idea how or why this works. The data sheet for
	the NT35510 LCD Driver IC is incomplete. This code comes from
	a vendor example using an 8051 micro.
		
	I know the data sheet is incomplete because the commands below
	are not listed. I have no idea what this section of code is or
	does; nor does anyone outside of the people who designed this
	chip.
	
	That said, this section of code does correctly initialize the
	LCD. If you have any desire to change or edit this code, may
	whatever god you believe in have mercy on your soul.
		
	The following code was refactored to be utterly incomprehensible
	and full of magic numbers on purpose. I suggest you do not screw
	with this, as there is no documentation at all.
	*/
	
	REG_PORT_DIRSET1 = 0x00010000;
	REG_PORT_OUTSET1 = PORT_PB16;
	
	REG_PORT_OUTSET1 = LCD_Reset;
	delay_ms(5);
	REG_PORT_OUTCLR1 = LCD_Reset;
	delay_ms(15);
	REG_PORT_OUTSET1 = LCD_Reset;
	REG_PORT_OUTCLR1 = LCD_CS;		
	
static char baal[70] = {0xF0,0xF0,0xF0,0xF0,0xF0,0xB0,0xB0,
		0xB0,0xB6,0xB6,0xB6,0xB1,0xB1,0xB1,0xB7,0xB7,0xB7,0xB2,0xB2,
		0xB2,0xB8,0xB8,0xB8,0xBF,0xB3,0xB3,0xB3,0xB9,0xB9,0xB9,0xB5,
		0xB5,0xB5,0xC2,0xBA,0xBA,0xBA,0xBC,0xBC,0xBC,0xBD,0xBD,0xBD,
		0xBE,0xBE,0xF0,0xF0,0xF0,0xF0,0xF0,0xB1,0xB1,0xB6,0xB7,0xB7,
		0xB8,0xB8,0xB8,0xB8,0xBC,0xBC,0xBC,0xC9,0xC9,0xC9,0xC9,0xC9,
		0x35,0x3A,0x36};
		
static char maweth[70] = {0x00,0x01,0x02,0x03,0x04,0x00,0x01,
		0x02,0x00,0x01,0x02,0x00,0x01,0x02,0x00,0x01,0x02,0x00,0x01,
		0x02,0x00,0x01,0x02,0x00,0x01,0x02,0x00,0x01,0x02,0x00,0x00,
		0x01,0x00,0x00,0x01,0x02,0x00,0x01,0x02,0x00,0x01,0x02,0x00,
		0x01,0x00,0x01,0x02,0x03,0x04,0x00,0x00,0x00,0x00,0x01,0x00,
		0x01,0x02,0x03,0x00,0x01,0x02,0x00,0x01,0x02,0x03,0x04,0x00,
		0x00,0x00};
				
static char lucifer[70] = {0x55,0xAA,0x52,0x08,0x01,0x0D,0x0D,0x0D,
		0x34,0x34,0x34,0x0D,0x0D,0x0D,0x34,0x34,0x34,0x00,0x00,0x00,
		0x24,0x24,0x24,0x01,0x0F,0x0F,0x0F,0x34,0x34,0x34,0x08,0x08,
		0x08,0x03,0x24,0x24,0x24,0x00,0x78,0x00,0x00,0x78,0x00,0x00,
		0x89,0x55,0xAA,0x52,0x08,0x00,0xCC,0x00,0x05,0x70,0x70,0x01,
		0x03,0x03,0x03,0x02,0x00,0x00,0xD0,0x02,0x50,0x50,0x50,0x00,
		0x55,0x00};

		
	for(int i = 0; i < 70; i++)
	{
		LCD_Write_COM16(baal[i],maweth[i]);
		LCD_Write_DATA8(lucifer[i]);
	}
	
  	LCD_Write_COM16(0x11,0x00);   //StartUp  
  
  	delay_ms(100);

  	LCD_Write_COM16(0x29,0x00);   //Display On  
	  
   	delay_ms(120);
	
	REG_PORT_OUTSET1 = LCD_CS;
	
	setColorRGB(255, 255, 255);
	setBackColorRGB(0, 0, 0);
	
}

