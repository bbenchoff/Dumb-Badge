/*
 * globals.h
 *
 * Created: 6/29/2020 2:08:54 PM
 *  Author: bench
 */ 


#ifndef GLOBALS_H
#define GLOBALS_H


//Pin Definitions
#define KB_ROW0		PORT_PA02
#define KB_ROW1		PORT_PA03
#define KB_ROW2		PORT_PA04
#define KB_ROW3		PORT_PA05
#define KB_ROW4		PORT_PA06
#define KB_ROW5		PORT_PA07
#define KB_ROW6		PORT_PA10
#define KB_ROW7		PORT_PA11
#define KB_ROW8		PORT_PA12
#define KB_ROW9		PORT_PA13

#define	KB_COL0		PORT_PA16
#define	KB_COL1		PORT_PA17
#define	KB_COL2		PORT_PA18
#define	KB_COL3		PORT_PA19
#define	KB_COL4		PORT_PA20
#define	KB_COL5		PORT_PA21
#define	KB_COL6		PORT_PA27

#define LCD_Reset	PORT_PB30
#define LCD_CS		PORT_PB22
#define LCD_WR		PORT_PB17
#define LCD_DC		PORT_PB23
#define LCD_RD		PORT_PB16

//USART Definitions
#define RX_LEN 10
extern char rx_buf;

extern uint16_t fore_Color_High, fore_Color_Low;
extern uint16_t back_Color_High, back_Color_Low;

extern uint16_t display_X_size;
extern uint16_t display_Y_size;

extern uint16_t xCharPos;
extern uint16_t yCharPos;

extern unsigned char scanCodeBuffer[20];

extern unsigned char keyDownBuffer[20];

extern bool capsLock;
extern bool scrollLock;
extern bool sPoNgEbObCaSe;

extern bool cursorBlinkState;
extern uint8_t cursorBuffer[200];

extern unsigned char consoleDisplay[80][24];

#endif /* GLOBALS_H_ */