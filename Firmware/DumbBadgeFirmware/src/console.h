/*
 * console.h
 *
 * Created: 6/29/2020 3:04:38 PM
 *  Author: bench
 */ 


#ifndef CONSOLE_H
#define CONSOLE_H

void drawChar(uint8_t character);
void scrollDown(uint8_t topLine, uint8_t count);
void newLine(void);
void nullifyConsole(void);

void writeString(const char str[]);

void blinkCursor(void);

void arrowKey(int scancode);

#endif /* CONSOLE_H_ */