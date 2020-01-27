case ILI9342_S4P:
	LCD_Write_COM(0x11);//sleep out 
	delay(120);
//************* Start Initial Sequence **********//	 
  	LCD_Write_COM(0xc8);
	LCD_Write_DATA(0xFF);
	LCD_Write_DATA(0x93);
	LCD_Write_DATA(0x42); 
 
	
  	LCD_Write_COM(0x36);       //Memory Access Control
 	LCD_Write_DATA(0xc8);//MY,MX,MV,ML,BGR,MH
  	

   	LCD_Write_COM(0x3A);       //Pixel Format Set
 	LCD_Write_DATA(0x55);//DPI [2:0],DBI [2:0]
	
	LCD_Write_COM(0xC0);
	LCD_Write_DATA(0x10);
	LCD_Write_DATA(0x10);
	
	LCD_Write_COM(0xC1);
	LCD_Write_DATA(0x36);
		
	LCD_Write_COM(0xC5);	 //VCOM
	LCD_Write_DATA(0xC3);
						   	  

  	LCD_Write_COM(0xE0);    //Set Gamma 
	LCD_Write_DATA(0x00); 
	LCD_Write_DATA(0x05); 
	LCD_Write_DATA(0x08); 
	LCD_Write_DATA(0x02); 
	LCD_Write_DATA(0x1A); 
	LCD_Write_DATA(0x0C); 
	LCD_Write_DATA(0x42); 
	LCD_Write_DATA(0X7A); 
	LCD_Write_DATA(0x54); 
	LCD_Write_DATA(0x08); 
	LCD_Write_DATA(0x0D); 
	LCD_Write_DATA(0x0C); 
	LCD_Write_DATA(0x23); 
	LCD_Write_DATA(0x25); 
	LCD_Write_DATA(0x0F); 
      
 	LCD_Write_COM(0XE1);    //Set Gamma 
	LCD_Write_DATA(0x00); 
	LCD_Write_DATA(0x29); 
	LCD_Write_DATA(0x2F); 
	LCD_Write_DATA(0x03); 
	LCD_Write_DATA(0x0F); 
	LCD_Write_DATA(0x05); 
	LCD_Write_DATA(0x42); 
	LCD_Write_DATA(0x55); 
	LCD_Write_DATA(0x53); 
	LCD_Write_DATA(0x06); 
	LCD_Write_DATA(0x0F); 
	LCD_Write_DATA(0x0C); 
	LCD_Write_DATA(0x38); 
	LCD_Write_DATA(0x3A); 
	LCD_Write_DATA(0x0F);  

    LCD_Write_COM(0x11);    //Exit Sleep 
    delay(120); 
				
    LCD_Write_COM(0x29);    //Display on 
    LCD_Write_COM(0x2c); 
	break;

