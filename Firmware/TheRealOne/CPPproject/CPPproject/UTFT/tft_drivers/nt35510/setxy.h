case NT35510_16:
	LCD_Write_COM(0x2a,0x00); 
	LCD_Write_DATA(x1>>8);
	LCD_Write_COM(0x2a,0x01);
	LCD_Write_DATA(x1);
	LCD_Write_COM(0x2a,0x02); 
	LCD_Write_DATA(x2>>8);
	LCD_Write_COM(0x2a,0x03); 
	LCD_Write_DATA(x2);


	LCD_Write_COM(0x2b,0x00); 
	LCD_Write_DATA(y1>>8);
	LCD_Write_COM(0x2b,0x01); 
	LCD_Write_DATA(y1);
	LCD_Write_COM(0x2b,0x02); 
	LCD_Write_DATA(y2>>8);
	LCD_Write_COM(0x2b,0x03); 
	LCD_Write_DATA(y2);

	LCD_Write_COM(0x2c,0x00); 
	break;
