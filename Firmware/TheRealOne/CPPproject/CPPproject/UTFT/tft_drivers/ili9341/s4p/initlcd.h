case ILI9341_S4P:
	/*
////////////////////////////////////////////////////////////TFTM022-1
 	LCD_Write_COM(0xCF);   
	LCD_Write_DATA(0x00); 
	LCD_Write_DATA(0xc3); 
	LCD_Write_DATA(0X30); 
      
 	LCD_Write_COM(0xED);   
	LCD_Write_DATA(0x64); 
	LCD_Write_DATA(0x03); 
	LCD_Write_DATA(0X12); 
	LCD_Write_DATA(0X81); 
      
 	LCD_Write_COM(0xE8);   
	LCD_Write_DATA(0x85); 
	LCD_Write_DATA(0x10); 
	LCD_Write_DATA(0x79); 
      
 	LCD_Write_COM(0xCB);   
	LCD_Write_DATA(0x39); 
	LCD_Write_DATA(0x2C); 
	LCD_Write_DATA(0x00); 
	LCD_Write_DATA(0x34); 
	LCD_Write_DATA(0x02); 
      
 	LCD_Write_COM(0xF7);   
	LCD_Write_DATA(0x20); 
      
 	LCD_Write_COM(0xEA);   
	LCD_Write_DATA(0x00); 
	LCD_Write_DATA(0x00); 
      
 	LCD_Write_COM(0xC0);    //Power control 
	LCD_Write_DATA(0x22);   //VRH[5:0] 
      
 	LCD_Write_COM(0xC1);    //Power control 
	LCD_Write_DATA(0x11);   //SAP[2:0];BT[3:0] 
      
 	LCD_Write_COM(0xC5);    //VCM control 
	LCD_Write_DATA(0x3d); 
    //LCD_DataWrite_ILI9341(0x30); 
	LCD_Write_DATA(0x20); 
      
 	LCD_Write_COM(0xC7);    //VCM control2 
    //LCD_DataWrite_ILI9341(0xBD); 
	LCD_Write_DATA(0xA0); //0xB0 
    
 	LCD_Write_COM(0x36);    // Memory Access Control 
	LCD_Write_DATA(0x08); 
      
 	LCD_Write_COM(0x3A);   
	LCD_Write_DATA(0x55); 
    
 	LCD_Write_COM(0xB1);   
	LCD_Write_DATA(0x00);   
	LCD_Write_DATA(0x13); 
      
 	LCD_Write_COM(0xB6);    // Display Function Control 
	LCD_Write_DATA(0x0A); 
	LCD_Write_DATA(0xA2); 
    
 	LCD_Write_COM(0xF6);     
	LCD_Write_DATA(0x01); 
	LCD_Write_DATA(0x30); 
      
 	LCD_Write_COM(0xF2);    // 3Gamma Function Disable 
	LCD_Write_DATA(0x00); 
      
 	LCD_Write_COM(0x26);    //Gamma curve selected 
	LCD_Write_DATA(0x01); 
      
 	LCD_Write_COM(0xE0);    //Set Gamma 
	LCD_Write_DATA(0x0F); 
	LCD_Write_DATA(0x3F); 
	LCD_Write_DATA(0x2F); 
	LCD_Write_DATA(0x0C); 
	LCD_Write_DATA(0x10); 
	LCD_Write_DATA(0x0A); 
	LCD_Write_DATA(0x53); 
	LCD_Write_DATA(0XD5); 
	LCD_Write_DATA(0x40); 
	LCD_Write_DATA(0x0A); 
	LCD_Write_DATA(0x13); 
	LCD_Write_DATA(0x03); 
	LCD_Write_DATA(0x08); 
	LCD_Write_DATA(0x03); 
	LCD_Write_DATA(0x00); 
      
 	LCD_Write_COM(0XE1);    //Set Gamma 
	LCD_Write_DATA(0x00); 
	LCD_Write_DATA(0x00); 
	LCD_Write_DATA(0x10); 
	LCD_Write_DATA(0x03); 
	LCD_Write_DATA(0x0F); 
	LCD_Write_DATA(0x05); 
	LCD_Write_DATA(0x2C); 
	LCD_Write_DATA(0xA2); 
	LCD_Write_DATA(0x3F); 
	LCD_Write_DATA(0x05); 
	LCD_Write_DATA(0x0E); 
	LCD_Write_DATA(0x0C); 
	LCD_Write_DATA(0x37); 
	LCD_Write_DATA(0x3C); 
	LCD_Write_DATA(0x0F); 
      
   LCD_Write_COM(0x11);    //Exit Sleep 
    delay(120); 
				
    LCD_Write_COM(0x29);    //Display on 
    LCD_Write_COM(0x2c); 
	break;
////////////////////////////////////////////////////////////
*/

//TFTM028-4 TFTM032-3 TFTM024-3 TFTM026-1
 	LCD_Write_COM(0xCF);   
	LCD_Write_DATA(0x00); 
	LCD_Write_DATA(0xc3); 
	LCD_Write_DATA(0X30); 
      
 	LCD_Write_COM(0xED);   
	LCD_Write_DATA(0x64); 
	LCD_Write_DATA(0x03); 
	LCD_Write_DATA(0X12); 
	LCD_Write_DATA(0X81); 
      
 	LCD_Write_COM(0xE8);   
	LCD_Write_DATA(0x85); 
	LCD_Write_DATA(0x10); 
	LCD_Write_DATA(0x79); 
      
 	LCD_Write_COM(0xCB);   
	LCD_Write_DATA(0x39); 
	LCD_Write_DATA(0x2C); 
	LCD_Write_DATA(0x00); 
	LCD_Write_DATA(0x34); 
	LCD_Write_DATA(0x02); 
      
 	LCD_Write_COM(0xF7);   
	LCD_Write_DATA(0x20); 
      
 	LCD_Write_COM(0xEA);   
	LCD_Write_DATA(0x00); 
	LCD_Write_DATA(0x00); 
      
 	LCD_Write_COM(0xC0);    //Power control 
	LCD_Write_DATA(0x22);   //VRH[5:0] 
      
 	LCD_Write_COM(0xC1);    //Power control 
	LCD_Write_DATA(0x11);   //SAP[2:0];BT[3:0] 
      
 	LCD_Write_COM(0xC5);    //VCM control 
	LCD_Write_DATA(0x3a); //3d
    //LCD_DataWrite_ILI9341(0x30); 
	LCD_Write_DATA(0x20); 
      
 	LCD_Write_COM(0xC7);    //VCM control2 
    //LCD_DataWrite_ILI9341(0xBD); 
	LCD_Write_DATA(0xc5); //0xB0 
    
 	LCD_Write_COM(0x36);    // Memory Access Control 
	LCD_Write_DATA(0x08); 
      
 	LCD_Write_COM(0x3A);   
	LCD_Write_DATA(0x55); 
    
 	LCD_Write_COM(0xB1);   
	LCD_Write_DATA(0x00);   
	LCD_Write_DATA(0x13); 
      
 	LCD_Write_COM(0xB6);    // Display Function Control 
	LCD_Write_DATA(0x0A); 
	LCD_Write_DATA(0xA2); 
    
 	LCD_Write_COM(0xF6);     
	LCD_Write_DATA(0x01); 
	LCD_Write_DATA(0x30); 
      
 	LCD_Write_COM(0xF2);    // 3Gamma Function Disable 
	LCD_Write_DATA(0x00); 
      
 	LCD_Write_COM(0x26);    //Gamma curve selected 
	LCD_Write_DATA(0x01); 
      
 	LCD_Write_COM(0xE0);    //Set Gamma 
	LCD_Write_DATA(0x0F); 
	LCD_Write_DATA(0x3F); 
	LCD_Write_DATA(0x2F); 
	LCD_Write_DATA(0x0C); 
	LCD_Write_DATA(0x10); 
	LCD_Write_DATA(0x0A); 
	LCD_Write_DATA(0x53); 
	LCD_Write_DATA(0XD5); 
	LCD_Write_DATA(0x40); 
	LCD_Write_DATA(0x0A); 
	LCD_Write_DATA(0x13); 
	LCD_Write_DATA(0x03); 
	LCD_Write_DATA(0x08); 
	LCD_Write_DATA(0x03); 
	LCD_Write_DATA(0x00); 
      
 	LCD_Write_COM(0XE1);    //Set Gamma 
	LCD_Write_DATA(0x00); 
	LCD_Write_DATA(0x00); 
	LCD_Write_DATA(0x10); 
	LCD_Write_DATA(0x03); 
	LCD_Write_DATA(0x0F); 
	LCD_Write_DATA(0x05); 
	LCD_Write_DATA(0x2C); 
	LCD_Write_DATA(0xA2); 
	LCD_Write_DATA(0x3F); 
	LCD_Write_DATA(0x05); 
	LCD_Write_DATA(0x0E); 
	LCD_Write_DATA(0x0C); 
	LCD_Write_DATA(0x37); 
	LCD_Write_DATA(0x3C); 
	LCD_Write_DATA(0x0F); 

    LCD_Write_COM(0x11);    //Exit Sleep 
    delay(120); 
				
    LCD_Write_COM(0x29);    //Display on 
    LCD_Write_COM(0x2c); 
	break;

