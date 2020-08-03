/*
 * keyboard.h
 *
 * Created: 6/29/2020 3:39:26 PM
 *  Author: bench
 */ 


#ifndef KEYBOARD_H
#define KEYBOARD_H

void printKeyboardBuffer(void);
void readKeyboard(void);

bool bufferContains(int scanCode);
bool scanCodesContains(int scanCode);
bool keyDown(int scancode);
void removeFromKeyDown(int scancode);

void drawCursorBuffer(void);
void moveCursor(uint8_t x, uint8_t y);
void clearCursorBuffer(void);
void invertCursorBuffer(void);
void drawBlank(void);

void blinkCursor(void);


#endif /* KEYBOARD_H_ */