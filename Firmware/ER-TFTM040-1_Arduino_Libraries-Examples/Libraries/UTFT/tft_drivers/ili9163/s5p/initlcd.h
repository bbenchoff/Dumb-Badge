case ILI9163_S5P:
	LCD_Write_COM(0x11);//Sleep exit 
	delay(120);

	LCD_Write_COM(0x26);  //Set Default Gamma
    LCD_Write_DATA(0x04);
    LCD_Write_COM(0xB1);
    LCD_Write_DATA(0x08);//10 
    LCD_Write_DATA(0x10);//08 
    LCD_Write_COM(0xC0);  //Set VRH1[4:0] & VC[2:0] for VCI1 & GVDD
    LCD_Write_DATA(0x0C);
    LCD_Write_DATA(0x05);
    LCD_Write_COM(0xC1);  //Set BT[2:0] for AVDD & VCL & VGH & VGL
    LCD_Write_DATA(0x02);
    LCD_Write_COM(0xC5);  //Set VMH[6:0] & VML[6:0] for VOMH & VCOML
    LCD_Write_DATA(0x4E);
    LCD_Write_DATA(0x30);
    LCD_Write_COM(0xC7);
    LCD_Write_DATA(0xc0);     //offset=0//C0
    LCD_Write_COM(0x3A);  //Set Color Format
    LCD_Write_DATA(0x05);
    LCD_Write_COM(0x2A);  //Set Column Address
    LCD_Write_DATA(0x00);
    LCD_Write_DATA(0x00);
    LCD_Write_DATA(0x00);
    LCD_Write_DATA(0x7F);
    LCD_Write_COM(0x2B);  //Set Page Address
    LCD_Write_DATA(0x00);
    LCD_Write_DATA(0x00);
    LCD_Write_DATA(0x00);
    LCD_Write_DATA(0x9F);
 //   LCD_Write_COM(0xB4);  //frame inversion
//	LCD_Write_DATA(0x07);
    LCD_Write_COM(0x36);  //Set Scanning Direction
    LCD_Write_DATA(0xC0);
 //   LCD_Write_COM(0xEC);  //Set pumping clock frequency
   // LCD_Write_DATA(0x0B);
    LCD_Write_COM(0xF2);  //Enable Gamma bit
    LCD_Write_DATA(0x01);

	LCD_Write_COM(0xE0); 
    LCD_Write_DATA(0x3F);//p1          // xx VP63[5:0]             //       //
    LCD_Write_DATA(0x31);//p2          // xx VP62[5:0]             //       //
    LCD_Write_DATA(0x2D);//p3         // xx VP61[5:0]             //       //
    LCD_Write_DATA(0x2F);//p4          // xx VP59[5:0]             //       //
    LCD_Write_DATA(0x28);//p5          // xx VP57[5:0]             //       //
    LCD_Write_DATA(0x0D);//p6         // xxx VP50[4:0]  //       //
    LCD_Write_DATA(0x59);//p7          // x VP43[6:0]              //       //
    LCD_Write_DATA(0xA8);//p8          // VP36[3:0] VP27[3:0]        //       //
    LCD_Write_DATA(0x44);//p9          // x VP20[6:0]              //       //
    LCD_Write_DATA(0x18);//p10       // xxx VP13[4:0]  //       //
    LCD_Write_DATA(0x1F);//p11       // xx VP6[5:0]               //       //
    LCD_Write_DATA(0x10);//p12       // xx VP4[5:0]               //       //
    LCD_Write_DATA(0x07);//p13       // xx VP2[5:0]               //       //
    LCD_Write_DATA(0x02);//p14       // xx VP1[5:0]               //       //
    LCD_Write_DATA(0x00);//p15       // xx VP0[5:0]               //       //
    LCD_Write_COM(0xE1);    
    LCD_Write_DATA(0x00);//p1          // xx VN0[5:0]               //       //
    LCD_Write_DATA(0x0E);//p2         // xx VN1[5:0]               //       //
    LCD_Write_DATA(0x12);//p3          // xx VN2[5:0]               //       //
    LCD_Write_DATA(0x10);//p4          // xx VN4[5:0]              //       //
    LCD_Write_DATA(0x17);//p5          // xx VN6[5:0]               //       //
    LCD_Write_DATA(0x12);//p6          // xxx VN13[4:0] //       //
    LCD_Write_DATA(0x26);//p7          // x VN20[6:0]              //       //
    LCD_Write_DATA(0x57);//p8          // VN36[3:0] VN27[3:0]       //       //  
    LCD_Write_DATA(0x3B);//p9         // x VN43[6:0]              //       //
    LCD_Write_DATA(0x07);//p10       // xxx VN50[4:0] //       //
    LCD_Write_DATA(0x20);//p11       // xx VN57[5:0]            //       //
    LCD_Write_DATA(0x2F);//p12       // xx VN59[5:0]            //       //
    LCD_Write_DATA(0x38);//p13       // xx VN61[5:0]            //       //
    LCD_Write_DATA(0x3D);//p14       // xx VN62[5:0]            //       //       
    LCD_Write_DATA(0x3f);//p15         // xx VN63[5:0]            //       /

	
	LCD_Write_COM(0x29);//Display on
	break;
