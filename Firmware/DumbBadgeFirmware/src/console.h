/*
 * console.h
 *
 * Created: 6/29/2020 3:04:38 PM
 *  Author: bench
 */ 


#ifndef CONSOLE_H
#define CONSOLE_H

void drawChar(uint8_t character);
void newLine(void);
void clearConsole(void);

void writeString(char str[]);

void readCursor(uint16_t cursorLocationX, uint16_t cursorLocationY);


#endif /* CONSOLE_H_ */