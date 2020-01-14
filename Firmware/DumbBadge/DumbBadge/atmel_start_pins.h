/*
 * Code generated from Atmel Start.
 *
 * This file will be overwritten when reconfiguring your Atmel Start project.
 * Please copy examples or other code you want to keep to a separate file
 * to avoid losing it when reconfiguring.
 */
#ifndef ATMEL_START_PINS_H_INCLUDED
#define ATMEL_START_PINS_H_INCLUDED

#include <hal_gpio.h>

// SAMD21 has 8 pin functions

#define GPIO_PIN_FUNCTION_A 0
#define GPIO_PIN_FUNCTION_B 1
#define GPIO_PIN_FUNCTION_C 2
#define GPIO_PIN_FUNCTION_D 3
#define GPIO_PIN_FUNCTION_E 4
#define GPIO_PIN_FUNCTION_F 5
#define GPIO_PIN_FUNCTION_G 6
#define GPIO_PIN_FUNCTION_H 7

#define Crystal1 GPIO(GPIO_PORTA, 0)
#define Crystal2 GPIO(GPIO_PORTA, 1)
#define PA04 GPIO(GPIO_PORTA, 4)
#define PA05 GPIO(GPIO_PORTA, 5)
#define PA08 GPIO(GPIO_PORTA, 8)
#define PA09 GPIO(GPIO_PORTA, 9)
#define PA24 GPIO(GPIO_PORTA, 24)
#define PA25 GPIO(GPIO_PORTA, 25)
#define LCD_Data_00 GPIO(GPIO_PORTB, 0)
#define LCD_Data_01 GPIO(GPIO_PORTB, 1)
#define LCD_Data_02 GPIO(GPIO_PORTB, 2)
#define LCD_Data_03 GPIO(GPIO_PORTB, 3)
#define LCD_Data_04 GPIO(GPIO_PORTB, 4)
#define LCD_Data_05 GPIO(GPIO_PORTB, 5)
#define LCD_Data_06 GPIO(GPIO_PORTB, 6)
#define LCD_Data_07 GPIO(GPIO_PORTB, 7)
#define LCD_Data_08 GPIO(GPIO_PORTB, 8)
#define LCD_Data_09 GPIO(GPIO_PORTB, 9)
#define LCD_Data_10 GPIO(GPIO_PORTB, 10)
#define LCD_Data_11 GPIO(GPIO_PORTB, 11)
#define LCD_Data_12 GPIO(GPIO_PORTB, 12)
#define LCD_Data_13 GPIO(GPIO_PORTB, 13)
#define LCD_Data_14 GPIO(GPIO_PORTB, 14)
#define LCD_Data_15 GPIO(GPIO_PORTB, 15)
#define LCD_RD GPIO(GPIO_PORTB, 16)
#define LCD_WR GPIO(GPIO_PORTB, 17)
#define LCD_CS GPIO(GPIO_PORTB, 22)
#define LCD_DC GPIO(GPIO_PORTB, 23)
#define LCD_RST GPIO(GPIO_PORTB, 30)

#endif // ATMEL_START_PINS_H_INCLUDED
