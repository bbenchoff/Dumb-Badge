case ILI9488_16:
	LCD_Write_COM(0x11);
	delay(20);

 	LCD_Write_COM(0xE0);
	LCD_Write_DATA(0x00);
	LCD_Write_DATA(0x03);
	LCD_Write_DATA(0x09);
	LCD_Write_DATA(0x08);
	LCD_Write_DATA(0x16);
	LCD_Write_DATA(0x0A);
	LCD_Write_DATA(0x3F);
	LCD_Write_DATA(0x78);
	LCD_Write_DATA(0x4C);
	LCD_Write_DATA(0x09);
	LCD_Write_DATA(0x0A);
	LCD_Write_DATA(0x08);
	LCD_Write_DATA(0x16);
	LCD_Write_DATA(0x1A);
	LCD_Write_DATA(0x0F);
	

	LCD_Write_COM(0XE1);
	LCD_Write_DATA(0x00);
	LCD_Write_DATA(0x16);
	LCD_Write_DATA(0x19);
	LCD_Write_DATA(0x03);
	LCD_Write_DATA(0x0F);
	LCD_Write_DATA(0x05);
	LCD_Write_DATA(0x32);
	LCD_Write_DATA(0x45);
	LCD_Write_DATA(0x46);
	LCD_Write_DATA(0x04);
	LCD_Write_DATA(0x0E);
	LCD_Write_DATA(0x0D);
	LCD_Write_DATA(0x35);
	LCD_Write_DATA(0x37);
	LCD_Write_DATA(0x0F);
	  
	
	
	 
	LCD_Write_COM(0XC0);      //Power Control 1 
	LCD_Write_DATA(0x17);    //Vreg1out 
	LCD_Write_DATA(0x15);    //Verg2out 
	 
	LCD_Write_COM(0xC1);      //Power Control 2     
	LCD_Write_DATA(0x41);    //VGH,VGL 
	 
	LCD_Write_COM(0xC5);      //Power Control 3 
	LCD_Write_DATA(0x00); 
	LCD_Write_DATA(0x12);    //Vcom 
	LCD_Write_DATA(0x80);
	 
	LCD_Write_COM(0x36);      //Memory Access 
	LCD_Write_DATA(0x48); 
	 
	LCD_Write_COM(0x3A);      // Interface Pixel Format 
	LCD_Write_DATA(0x55); 	  //16 bit    
	 
	LCD_Write_COM(0XB0);      // Interface Mode Control 
	LCD_Write_DATA(0x00);     
	 
	LCD_Write_COM(0xB1);      //Frame rate 
	LCD_Write_DATA(0xA0);    //60Hz 
	 
	LCD_Write_COM(0xB4);      //Display Inversion Control 
	LCD_Write_DATA(0x02);    //2-dot 
	 
	LCD_Write_COM(0XB6);      //Display Function Control  RGB/MCU Interface Control 	
	LCD_Write_DATA(0x02);    //MCU 
	LCD_Write_DATA(0x02);    //Source,Gate scan dieection 
	  
	LCD_Write_COM(0XE9);      // Set Image Functio
	LCD_Write_DATA(0x00);    // Disable 24 bit data
	 
	LCD_Write_COM(0xF7);      // Adjust Control 
	LCD_Write_DATA(0xA9);     
	LCD_Write_DATA(0x51);     
	LCD_Write_DATA(0x2C);     
	LCD_Write_DATA(0x82);    // D7 stream, loose 

	LCD_Write_COM(0x11); //Sleep out
	delay(120);
	LCD_Write_COM(0x29);


	break;
