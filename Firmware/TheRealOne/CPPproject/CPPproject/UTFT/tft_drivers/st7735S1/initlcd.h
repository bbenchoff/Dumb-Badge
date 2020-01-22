case ST7735S_S5P_80160:
	LCD_Write_COM(0x11);//Sleep exit 
	delay(120);
 
		LCD_Write_COM(0x21); 
		
		LCD_Write_COM(0xB1);     
		LCD_Write_DATA(0x05);   
		LCD_Write_DATA(0x3A);   
		LCD_Write_DATA(0x3A);   
		
		LCD_Write_COM(0xB2);     
		LCD_Write_DATA(0x05);   
		LCD_Write_DATA(0x3A);   
		LCD_Write_DATA(0x3A);   
		
		LCD_Write_COM(0xB3);     
		LCD_Write_DATA(0x05);   
		LCD_Write_DATA(0x3A);   
		LCD_Write_DATA(0x3A);   
		LCD_Write_DATA(0x05);   
		LCD_Write_DATA(0x3A);   
		LCD_Write_DATA(0x3A);   
		
		LCD_Write_COM(0xB4);     //Dot inversion
		LCD_Write_DATA(0x03);   
		
		LCD_Write_COM(0xC0);     
		LCD_Write_DATA(0x62);   
		LCD_Write_DATA(0x02);   
		LCD_Write_DATA(0x04);   
		
		LCD_Write_COM(0xC1);     
		LCD_Write_DATA(0xC0);   
		
		LCD_Write_COM(0xC2);     
		LCD_Write_DATA(0x0D);   
		LCD_Write_DATA(0x00);   
		
		LCD_Write_COM(0xC3);     
		LCD_Write_DATA(0x8D);   
		LCD_Write_DATA(0x6A);   
		
		LCD_Write_COM(0xC4);     
		LCD_Write_DATA(0x8D);   
		LCD_Write_DATA(0xEE);   
		
		LCD_Write_COM(0xC5);     //VCOM
		LCD_Write_DATA(0x0E);   
		
		LCD_Write_COM(0xE0);
		LCD_Write_DATA(0x10);
		LCD_Write_DATA(0x0E);
		LCD_Write_DATA(0x02);
		LCD_Write_DATA(0x03);
		LCD_Write_DATA(0x0E);
		LCD_Write_DATA(0x07);
		LCD_Write_DATA(0x02);
		LCD_Write_DATA(0x07);
		LCD_Write_DATA(0x0A);
		LCD_Write_DATA(0x12);
		LCD_Write_DATA(0x27);
		LCD_Write_DATA(0x37);
		LCD_Write_DATA(0x00);
		LCD_Write_DATA(0x0D);
		LCD_Write_DATA(0x0E);
		LCD_Write_DATA(0x10);
		
		
		LCD_Write_COM(0xE1);
		LCD_Write_DATA(0x10);
		LCD_Write_DATA(0x0E);
		LCD_Write_DATA(0x03);
		LCD_Write_DATA(0x03);
		LCD_Write_DATA(0x0F);
		LCD_Write_DATA(0x06);
		LCD_Write_DATA(0x02);
		LCD_Write_DATA(0x08);
		LCD_Write_DATA(0x0A);
		LCD_Write_DATA(0x13);
		LCD_Write_DATA(0x26);
		LCD_Write_DATA(0x36);
		LCD_Write_DATA(0x00);
		LCD_Write_DATA(0x0D);
		LCD_Write_DATA(0x0E);
		LCD_Write_DATA(0x10);
		

		
		LCD_Write_COM(0x36);     
		LCD_Write_DATA(0xC8);   

	LCD_Write_COM(0x3A); //65k mode 
	LCD_Write_DATA(0x05); 
	LCD_Write_COM(0x29);//Display on
	break;
