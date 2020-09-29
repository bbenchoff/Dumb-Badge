/*
 * LCD.h
 *
 * Created: 6/29/2020 1:45:57 PM
 *  Author: bench
 */ 


#ifndef LCD_H
#define LCD_H

void setColorRGB(uint8_t r, uint8_t g, uint8_t b);
void setColorHex(uint16_t color);
void setBackColorRGB(unsigned char r, unsigned char g, unsigned char b);
void setBackColorHex(uint16_t color);

void fillRect(int x1, int y1, int x2, int y2);
void fillRectBackColor(int x1, int y1, int x2, int y2);
void LCD_Fast_Fill(int ch, int cl, long pix);

void clrScr(void);
void clrXY(void);
void setXY(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
void setPixel(uint16_t color);
void drawPixel(uint16_t x, uint16_t y);
void setDrawDirection(void);
void clearScreen(void);




#endif /* LCD_H_ */