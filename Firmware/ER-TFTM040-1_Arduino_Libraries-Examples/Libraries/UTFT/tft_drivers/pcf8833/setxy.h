case PCF8833:
	LCD_Write_COM(0x2a); 
  	LCD_Write_DATA(x1);
  	LCD_Write_DATA(x2);
	LCD_Write_COM(0x2b); 
  	LCD_Write_DATA(y1);
  	LCD_Write_DATA(y2);
	LCD_Write_COM(0x2c); 
	break;
