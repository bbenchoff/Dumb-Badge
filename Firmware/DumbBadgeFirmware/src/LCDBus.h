/*
 * LCD.h
 *
 * Created: 6/29/2020 10:17:27 AM
 *  Author: bench
 */ 

#ifndef LCDBus_H
#define LCDBus_H

void InitLCD(void);

void LCD_Write_Bus(char VH, char VL);
void LCD_Write_COM16(char VH, char VL);
void LCD_Write_COM8(char VL);
void LCD_Write_DATA16(char VH, char VL);
void LCD_Write_DATA8(char VL);


#endif
