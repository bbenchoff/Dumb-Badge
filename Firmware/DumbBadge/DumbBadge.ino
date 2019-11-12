/*
 * Electrical setup: LCD data pins are a 16-bit bus from PB00 to PB15 
 * 
 * 
 * LCD uses 8080-series interface, with 19 wires, 16 of which are the data bus
 * the CSX (active low) enables the parallel interface, WRX is the parallel data write
 * RDX is the parallel data read.
 * 
 * Graphics chip controller reads the data on the rising edge of the wrx signal.
 * The D/CX is the data, command flag. When D/CX = 1 bits are display RAM data or
 * command paramaters. When D/CX = 0, the bits are commands.
 * 
 * The interface is set with the IM0 through IM3 pins. Functions below:
 * 
 *                  | D/CX  | RDX | WRX | Function
 *                  | 0       1     R   | Write 16-bit command
 * 16 bit parallel  | 1       1     R   | Write 16-bit display data or parameter
 *                  | 1       R     1   | Read 16-bit display data
 *                  | 1       R     1   | Read 16-bit parameter or status
 *                  
 *                  
 *                  
 *                  
 */ 


  __p1 = RS;
  __p2 = WR;
  __p3 = CS;
  __p4 = RST;
  __p5 = SER;


void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}

void send_bus_16(uint16_t data)
{
  REG_PORT_OUTCLR0 = 0x0000FFFF; //send PB0 through PB15
  REG_PORT_OUTSET0 = data;
}

void send_bus_8(uint8_t data)
{
  REG_PORT_OUTCLR0 = 0x000000FF; //send PB0 through PB07
  REG_PORT_OUTSET0 = data;
}

void setXY(word x1, word y1, word x2, word y2)
{
  send_bus_16(0x2A00);  //
  send_bus_8(x1>>8);    //  This section sets the row and column address
  send_bus_16(0x2a01);  //  to define area of frame memory MPU can acess.
  send_bus_8(x1);       //  Information on layout of the frame memory
  send_bus_16(0x2A02);  //  is given on pg. 75-77 of the datasheet.
  send_bus_8(x2>>8);    //
  send_bus_16(0x2A03);  //  Effectively, we are setting a 1x1 pixel area of the display -- just one pixel total.
  send_bus_8(x2);       //  
                        //  This could use optimization.
  send_bus_16(0x2B00);  //
  send_bus_8(y1>>8);    //
  send_bus_16(0x2B01);  //
  send_bus_8(y1);       //
  send_bus_16(0x2B02);  //    
  send_bus_8(y2>>8);    //      
  send_bus_16(0x2B03);  //
  send_bus_8(y2);       //

  send_bus_16(0x2C00);  //  Memory write, transfers data from MPU interface to frame memory // datasheet page 139

}

void initLCD()
{
  send_bus_16(0xF000);send_bus_8(0x55);
  send_bus_16(0xF001);send_bus_8(0xAA);
  send_bus_16(0xF002);send_bus_8(0x52);
  send_bus_16(0xF003);send_bus_8(0x08);
  send_bus_16(0xF004);send_bus_8(0x01);
  
  //#AVDD Set AVDD 5.2V
  send_bus_16(0xB000);send_bus_8(0x0D);
  send_bus_16(0xB001);send_bus_8(0x0D);
  send_bus_16(0xB002);send_bus_8(0x0D);
  
  //#AVDD ratio
  send_bus_16(0xB600);send_bus_8(0x34);
  send_bus_16(0xB601);send_bus_8(0x34);
  send_bus_16(0xB602);send_bus_8(0x34);
   
  //#AVEE  -5.2V
  send_bus_16(0xB100);send_bus_8(0x0D);
  send_bus_16(0xB101);send_bus_8(0x0D);
  send_bus_16(0xB102);send_bus_8(0x0D);
  
  //#AVEE ratio
  send_bus_16(0xB700);send_bus_8(0x34);
  send_bus_16(0xB701);send_bus_8(0x34);
  send_bus_16(0xB702);send_bus_8(0x34);
  
  //#VCL  -2.5V
  send_bus_16(0xB200);send_bus_8(0x00);
  send_bus_16(0xB201);send_bus_8(0x00);
  send_bus_16(0xB202);send_bus_8(0x00);
  
  //#VCL ratio
  send_bus_16(0xB800);send_bus_8(0x24);
  send_bus_16(0xB801);send_bus_8(0x24);
  send_bus_16(0xB802);send_bus_8(0x24); 
  
  //#VGH  15V
  send_bus_16(0xBF00);send_bus_8(0x01);
  send_bus_16(0xB300);send_bus_8(0x0F);
  send_bus_16(0xB301);send_bus_8(0x0F);
  send_bus_16(0xB302);send_bus_8(0x0F);
  
  //#VGH  ratio
  send_bus_16(0xB900);send_bus_8(0x34);
  send_bus_16(0xB901);send_bus_8(0x34);
  send_bus_16(0xB902);send_bus_8(0x34); 
  
  //#VGL_REG  -10V
  send_bus_16(0xB500);send_bus_8(0x08);
  send_bus_16(0xB500);send_bus_8(0x08);
  send_bus_16(0xB501);send_bus_8(0x08);
  send_bus_16(0xC200);send_bus_8(0x03);
  
  //#VGLX  ratio
  send_bus_16(0xBA00);send_bus_8(0x24);
  send_bus_16(0xBA01);send_bus_8(0x24);
  send_bus_16(0xBA02);send_bus_8(0x24);
  
  //#VGMP/VGSP 4.5V/0V
  send_bus_16(0xBC00);send_bus_8(0x00);
  send_bus_16(0xBC01);send_bus_8(0x78);
  send_bus_16(0xBC02);send_bus_8(0x00);
  
  //#VGMN/VGSN -4.5V/0V
  send_bus_16(0xBD00);send_bus_8(0x00);
  send_bus_16(0xBD01);send_bus_8(0x78);
  send_bus_16(0xBD02);send_bus_8(0x00);
  
  //#VCOM  -1.325V
  send_bus_16(0xBE00);send_bus_8(0x00);
  send_bus_16(0xBE01);send_bus_8(0x89);//69
  
  //Gamma Setting   
  send_bus_16(0xD100);send_bus_8(0x00);
  send_bus_16(0xD101);send_bus_8(0x2D);
  send_bus_16(0xD102);send_bus_8(0x00);
  send_bus_16(0xD103);send_bus_8(0x2E);
  send_bus_16(0xD104);send_bus_8(0x00); 
  send_bus_16(0xD105);send_bus_8(0x32);
  send_bus_16(0xD106);send_bus_8(0x00);
  send_bus_16(0xD107);send_bus_8(0x44);
  send_bus_16(0xD108);send_bus_8(0x00);
  send_bus_16(0xD109);send_bus_8(0x53);
  send_bus_16(0xD10A);send_bus_8(0x00);
  send_bus_16(0xD10B);send_bus_8(0x88);
  send_bus_16(0xD10C);send_bus_8(0x00);
  send_bus_16(0xD10D);send_bus_8(0xB6);
  send_bus_16(0xD10E);send_bus_8(0x00);
  send_bus_16(0xD10F);send_bus_8(0xF3);  //
  send_bus_16(0xD110);send_bus_8(0x01);
  send_bus_16(0xD111);send_bus_8(0x22);
  send_bus_16(0xD112);send_bus_8(0x01);
  send_bus_16(0xD113);send_bus_8(0x64);
  send_bus_16(0xD114);send_bus_8(0x01);
  send_bus_16(0xD115);send_bus_8(0x92);
  send_bus_16(0xD116);send_bus_8(0x01);
  send_bus_16(0xD117);send_bus_8(0xD4);
  send_bus_16(0xD118);send_bus_8(0x02);  
  send_bus_16(0xD119);send_bus_8(0x07);
  send_bus_16(0xD11A);send_bus_8(0x02);
  send_bus_16(0xD11B);send_bus_8(0x08);
  send_bus_16(0xD11C);send_bus_8(0x02);
  send_bus_16(0xD11D);send_bus_8(0x34);
  send_bus_16(0xD11E);send_bus_8(0x02);
  send_bus_16(0xD11F);send_bus_8(0x5F); //
  send_bus_16(0xD120);send_bus_8(0x02);
  send_bus_16(0xD121);send_bus_8(0x78);
  send_bus_16(0xD122);send_bus_8(0x02);
  send_bus_16(0xD123);send_bus_8(0x94);
  send_bus_16(0xD124);send_bus_8(0x02);
  send_bus_16(0xD125);send_bus_8(0xA6);
  send_bus_16(0xD126);send_bus_8(0x02);
  send_bus_16(0xD127);send_bus_8(0xBB);
  send_bus_16(0xD128);send_bus_8(0x02); 
  send_bus_16(0xD129);send_bus_8(0xCA);
  send_bus_16(0xD12A);send_bus_8(0x02);
  send_bus_16(0xD12B);send_bus_8(0xDB);
  send_bus_16(0xD12C);send_bus_8(0x02);
  send_bus_16(0xD12D);send_bus_8(0xE8);
  send_bus_16(0xD12E);send_bus_8(0x02);
  send_bus_16(0xD12F);send_bus_8(0xF9); //
  send_bus_16(0xD130);send_bus_8(0x03); 
  send_bus_16(0xD131);send_bus_8(0x1F);
  send_bus_16(0xD132);send_bus_8(0x03);
  send_bus_16(0xD133);send_bus_8(0x7F);
       
  send_bus_16(0xD200);send_bus_8(0x00);
  send_bus_16(0xD201);send_bus_8(0x2D);
  send_bus_16(0xD202);send_bus_8(0x00);
  send_bus_16(0xD203);send_bus_8(0x2E);
  send_bus_16(0xD204);send_bus_8(0x00); 
  send_bus_16(0xD205);send_bus_8(0x32);
  send_bus_16(0xD206);send_bus_8(0x00);
  send_bus_16(0xD207);send_bus_8(0x44);
  send_bus_16(0xD208);send_bus_8(0x00);
  send_bus_16(0xD209);send_bus_8(0x53);
  send_bus_16(0xD20A);send_bus_8(0x00);
  send_bus_16(0xD20B);send_bus_8(0x88);
  send_bus_16(0xD20C);send_bus_8(0x00);
  send_bus_16(0xD20D);send_bus_8(0xB6);
  send_bus_16(0xD20E);send_bus_8(0x00);
  send_bus_16(0xD20F);send_bus_8(0xF3);  //
  send_bus_16(0xD210);send_bus_8(0x01);
  send_bus_16(0xD211);send_bus_8(0x22);
  send_bus_16(0xD212);send_bus_8(0x01);
  send_bus_16(0xD213);send_bus_8(0x64);
  send_bus_16(0xD214);send_bus_8(0x01);
  send_bus_16(0xD215);send_bus_8(0x92);
  send_bus_16(0xD216);send_bus_8(0x01);
  send_bus_16(0xD217);send_bus_8(0xD4);
  send_bus_16(0xD218);send_bus_8(0x02);  
  send_bus_16(0xD219);send_bus_8(0x07);
  send_bus_16(0xD21A);send_bus_8(0x02);
  send_bus_16(0xD21B);send_bus_8(0x08);
  send_bus_16(0xD21C);send_bus_8(0x02);
  send_bus_16(0xD21D);send_bus_8(0x34);
  send_bus_16(0xD21E);send_bus_8(0x02);
  send_bus_16(0xD21F);send_bus_8(0x5F); //
  send_bus_16(0xD220);send_bus_8(0x02);
  send_bus_16(0xD221);send_bus_8(0x78);
  send_bus_16(0xD222);send_bus_8(0x02);
  send_bus_16(0xD223);send_bus_8(0x94);
  send_bus_16(0xD224);send_bus_8(0x02);
  send_bus_16(0xD225);send_bus_8(0xA6);
  send_bus_16(0xD226);send_bus_8(0x02);
  send_bus_16(0xD227);send_bus_8(0xBB);
  send_bus_16(0xD228);send_bus_8(0x02); 
  send_bus_16(0xD229);send_bus_8(0xCA);
  send_bus_16(0xD22A);send_bus_8(0x02);
  send_bus_16(0xD22B);send_bus_8(0xDB);
  send_bus_16(0xD22C);send_bus_8(0x02);
  send_bus_16(0xD22D);send_bus_8(0xE8);
  send_bus_16(0xD22E);send_bus_8(0x02);
  send_bus_16(0xD22F);send_bus_8(0xF9); //
  send_bus_16(0xD230);send_bus_8(0x03); 
  send_bus_16(0xD231);send_bus_8(0x1F);
  send_bus_16(0xD232);send_bus_8(0x03);
  send_bus_16(0xD233);send_bus_8(0x7F);
     
  send_bus_16(0xD300);send_bus_8(0x00);
  send_bus_16(0xD301);send_bus_8(0x2D);
  send_bus_16(0xD302);send_bus_8(0x00);
  send_bus_16(0xD303);send_bus_8(0x2E);
  send_bus_16(0xD304);send_bus_8(0x00); 
  send_bus_16(0xD305);send_bus_8(0x32);
  send_bus_16(0xD306);send_bus_8(0x00);
  send_bus_16(0xD307);send_bus_8(0x44);
  send_bus_16(0xD308);send_bus_8(0x00);
  send_bus_16(0xD309);send_bus_8(0x53);
  send_bus_16(0xD30A);send_bus_8(0x00);
  send_bus_16(0xD30B);send_bus_8(0x88);
  send_bus_16(0xD30C);send_bus_8(0x00);
  send_bus_16(0xD30D);send_bus_8(0xB6);
  send_bus_16(0xD30E);send_bus_8(0x00);
  send_bus_16(0xD30F);send_bus_8(0xF3);  //
  send_bus_16(0xD310);send_bus_8(0x01);
  send_bus_16(0xD311);send_bus_8(0x22);
  send_bus_16(0xD312);send_bus_8(0x01);
  send_bus_16(0xD313);send_bus_8(0x64);
  send_bus_16(0xD314);send_bus_8(0x01);
  send_bus_16(0xD315);send_bus_8(0x92);
  send_bus_16(0xD316);send_bus_8(0x01);
  send_bus_16(0xD317);send_bus_8(0xD4);
  send_bus_16(0xD318);send_bus_8(0x02);  
  send_bus_16(0xD319);send_bus_8(0x07);
  send_bus_16(0xD31A);send_bus_8(0x02);
  send_bus_16(0xD31B);send_bus_8(0x08);
  send_bus_16(0xD31C);send_bus_8(0x02);
  send_bus_16(0xD31D);send_bus_8(0x34);
  send_bus_16(0xD31E);send_bus_8(0x02);
  send_bus_16(0xD31F);send_bus_8(0x5F); //
  send_bus_16(0xD320);send_bus_8(0x02);
  send_bus_16(0xD321);send_bus_8(0x78);
  send_bus_16(0xD322);send_bus_8(0x02);
  send_bus_16(0xD323);send_bus_8(0x94);
  send_bus_16(0xD324);send_bus_8(0x02);
  send_bus_16(0xD325);send_bus_8(0xA6);
  send_bus_16(0xD326);send_bus_8(0x02);
  send_bus_16(0xD327);send_bus_8(0xBB);
  send_bus_16(0xD328);send_bus_8(0x02); 
  send_bus_16(0xD329);send_bus_8(0xCA);
  send_bus_16(0xD32A);send_bus_8(0x02);
  send_bus_16(0xD32B);send_bus_8(0xDB);
  send_bus_16(0xD32C);send_bus_8(0x02);
  send_bus_16(0xD32D);send_bus_8(0xE8);
  send_bus_16(0xD32E);send_bus_8(0x02);
  send_bus_16(0xD32F);send_bus_8(0xF9); //
  send_bus_16(0xD330);send_bus_8(0x03); 
  send_bus_16(0xD331);send_bus_8(0x1F);
  send_bus_16(0xD332);send_bus_8(0x03);
  send_bus_16(0xD333);send_bus_8(0x7F);
     
  send_bus_16(0xD400);send_bus_8(0x00);
  send_bus_16(0xD401);send_bus_8(0x2D);
  send_bus_16(0xD402);send_bus_8(0x00);
  send_bus_16(0xD403);send_bus_8(0x2E);
  send_bus_16(0xD404);send_bus_8(0x00); 
  send_bus_16(0xD405);send_bus_8(0x32);
  send_bus_16(0xD406);send_bus_8(0x00);
  send_bus_16(0xD407);send_bus_8(0x44);
  send_bus_16(0xD408);send_bus_8(0x00);
  send_bus_16(0xD409);send_bus_8(0x53);
  send_bus_16(0xD40A);send_bus_8(0x00);
  send_bus_16(0xD40B);send_bus_8(0x88);
  send_bus_16(0xD40C);send_bus_8(0x00);
  send_bus_16(0xD40D);send_bus_8(0xB6);
  send_bus_16(0xD40E);send_bus_8(0x00);
  send_bus_16(0xD40F);send_bus_8(0xF3);  //
  send_bus_16(0xD410);send_bus_8(0x01);
  send_bus_16(0xD411);send_bus_8(0x22);
  send_bus_16(0xD412);send_bus_8(0x01);
  send_bus_16(0xD413);send_bus_8(0x64);
  send_bus_16(0xD414);send_bus_8(0x01);
  send_bus_16(0xD415);send_bus_8(0x92);
  send_bus_16(0xD416);send_bus_8(0x01);
  send_bus_16(0xD417);send_bus_8(0xD4);
  send_bus_16(0xD418);send_bus_8(0x02);  
  send_bus_16(0xD419);send_bus_8(0x07);
  send_bus_16(0xD41A);send_bus_8(0x02);
  send_bus_16(0xD41B);send_bus_8(0x08);
  send_bus_16(0xD41C);send_bus_8(0x02);
  send_bus_16(0xD41D);send_bus_8(0x34);
  send_bus_16(0xD41E);send_bus_8(0x02);
  send_bus_16(0xD41F);send_bus_8(0x5F); //
  send_bus_16(0xD420);send_bus_8(0x02);
  send_bus_16(0xD421);send_bus_8(0x78);
  send_bus_16(0xD422);send_bus_8(0x02);
  send_bus_16(0xD423);send_bus_8(0x94);
  send_bus_16(0xD424);send_bus_8(0x02);
  send_bus_16(0xD425);send_bus_8(0xA6);
  send_bus_16(0xD426);send_bus_8(0x02);
  send_bus_16(0xD427);send_bus_8(0xBB);
  send_bus_16(0xD428);send_bus_8(0x02); 
  send_bus_16(0xD429);send_bus_8(0xCA);
  send_bus_16(0xD42A);send_bus_8(0x02);
  send_bus_16(0xD42B);send_bus_8(0xDB);
  send_bus_16(0xD42C);send_bus_8(0x02);
  send_bus_16(0xD42D);send_bus_8(0xE8);
  send_bus_16(0xD42E);send_bus_8(0x02);
  send_bus_16(0xD42F);send_bus_8(0xF9); //
  send_bus_16(0xD430);send_bus_8(0x03); 
  send_bus_16(0xD431);send_bus_8(0x1F);
  send_bus_16(0xD432);send_bus_8(0x03);
  send_bus_16(0xD433);send_bus_8(0x7F);
     
  send_bus_16(0xD500);send_bus_8(0x00);
  send_bus_16(0xD501);send_bus_8(0x2D);
  send_bus_16(0xD502);send_bus_8(0x00);
  send_bus_16(0xD503);send_bus_8(0x2E);
  send_bus_16(0xD504);send_bus_8(0x00); 
  send_bus_16(0xD505);send_bus_8(0x32);
  send_bus_16(0xD506);send_bus_8(0x00);
  send_bus_16(0xD507);send_bus_8(0x44);
  send_bus_16(0xD508);send_bus_8(0x00);
  send_bus_16(0xD509);send_bus_8(0x53);
  send_bus_16(0xD50A);send_bus_8(0x00);
  send_bus_16(0xD50B);send_bus_8(0x88);
  send_bus_16(0xD50C);send_bus_8(0x00);
  send_bus_16(0xD50D);send_bus_8(0xB6);
  send_bus_16(0xD50E);send_bus_8(0x00);
  send_bus_16(0xD50F);send_bus_8(0xF3);  //
  send_bus_16(0xD510);send_bus_8(0x01);
  send_bus_16(0xD511);send_bus_8(0x22);
  send_bus_16(0xD512);send_bus_8(0x01);
  send_bus_16(0xD513);send_bus_8(0x64);
  send_bus_16(0xD514);send_bus_8(0x01);
  send_bus_16(0xD515);send_bus_8(0x92);
  send_bus_16(0xD516);send_bus_8(0x01);
  send_bus_16(0xD517);send_bus_8(0xD4);
  send_bus_16(0xD518);send_bus_8(0x02);  
  send_bus_16(0xD519);send_bus_8(0x07);
  send_bus_16(0xD51A);send_bus_8(0x02);
  send_bus_16(0xD51B);send_bus_8(0x08);
  send_bus_16(0xD51C);send_bus_8(0x02);
  send_bus_16(0xD51D);send_bus_8(0x34);
  send_bus_16(0xD51E);send_bus_8(0x02);
  send_bus_16(0xD51F);send_bus_8(0x5F); //
  send_bus_16(0xD520);send_bus_8(0x02);
  send_bus_16(0xD521);send_bus_8(0x78);
  send_bus_16(0xD522);send_bus_8(0x02);
  send_bus_16(0xD523);send_bus_8(0x94);
  send_bus_16(0xD524);send_bus_8(0x02);
  send_bus_16(0xD525);send_bus_8(0xA6);
  send_bus_16(0xD526);send_bus_8(0x02);
  send_bus_16(0xD527);send_bus_8(0xBB);
  send_bus_16(0xD528);send_bus_8(0x02); 
  send_bus_16(0xD529);send_bus_8(0xCA);
  send_bus_16(0xD52A);send_bus_8(0x02);
  send_bus_16(0xD52B);send_bus_8(0xDB);
  send_bus_16(0xD52C);send_bus_8(0x02);
  send_bus_16(0xD52D);send_bus_8(0xE8);
  send_bus_16(0xD52E);send_bus_8(0x02);
  send_bus_16(0xD52F);send_bus_8(0xF9); //
  send_bus_16(0xD530);send_bus_8(0x03); 
  send_bus_16(0xD531);send_bus_8(0x1F);
  send_bus_16(0xD532);send_bus_8(0x03);
  send_bus_16(0xD533);send_bus_8(0x7F);
     
  send_bus_16(0xD600);send_bus_8(0x00);
  send_bus_16(0xD601);send_bus_8(0x2D);
  send_bus_16(0xD602);send_bus_8(0x00);
  send_bus_16(0xD603);send_bus_8(0x2E);
  send_bus_16(0xD604);send_bus_8(0x00); 
  send_bus_16(0xD605);send_bus_8(0x32);
  send_bus_16(0xD606);send_bus_8(0x00);
  send_bus_16(0xD607);send_bus_8(0x44);
  send_bus_16(0xD608);send_bus_8(0x00);
  send_bus_16(0xD609);send_bus_8(0x53);
  send_bus_16(0xD60A);send_bus_8(0x00);
  send_bus_16(0xD60B);send_bus_8(0x88);
  send_bus_16(0xD60C);send_bus_8(0x00);
  send_bus_16(0xD60D);send_bus_8(0xB6);
  send_bus_16(0xD60E);send_bus_8(0x00);
  send_bus_16(0xD60F);send_bus_8(0xF3);  //
  send_bus_16(0xD610);send_bus_8(0x01);
  send_bus_16(0xD611);send_bus_8(0x22);
  send_bus_16(0xD612);send_bus_8(0x01);
  send_bus_16(0xD613);send_bus_8(0x64);
  send_bus_16(0xD614);send_bus_8(0x01);
  send_bus_16(0xD615);send_bus_8(0x92);
  send_bus_16(0xD616);send_bus_8(0x01);
  send_bus_16(0xD617);send_bus_8(0xD4);
  send_bus_16(0xD618);send_bus_8(0x02);  
  send_bus_16(0xD619);send_bus_8(0x07);
  send_bus_16(0xD61A);send_bus_8(0x02);
  send_bus_16(0xD61B);send_bus_8(0x08);
  send_bus_16(0xD61C);send_bus_8(0x02);
  send_bus_16(0xD61D);send_bus_8(0x34);
  send_bus_16(0xD61E);send_bus_8(0x02);
  send_bus_16(0xD61F);send_bus_8(0x5F); //
  send_bus_16(0xD620);send_bus_8(0x02);
  send_bus_16(0xD621);send_bus_8(0x78);
  send_bus_16(0xD622);send_bus_8(0x02);
  send_bus_16(0xD623);send_bus_8(0x94);
  send_bus_16(0xD624);send_bus_8(0x02);
  send_bus_16(0xD625);send_bus_8(0xA6);
  send_bus_16(0xD626);send_bus_8(0x02);
  send_bus_16(0xD627);send_bus_8(0xBB);
  send_bus_16(0xD628);send_bus_8(0x02); 
  send_bus_16(0xD629);send_bus_8(0xCA);
  send_bus_16(0xD62A);send_bus_8(0x02);
  send_bus_16(0xD62B);send_bus_8(0xDB);
  send_bus_16(0xD62C);send_bus_8(0x02);
  send_bus_16(0xD62D);send_bus_8(0xE8);
  send_bus_16(0xD62E);send_bus_8(0x02);
  send_bus_16(0xD62F);send_bus_8(0xF9); //
  send_bus_16(0xD630);send_bus_8(0x03); 
  send_bus_16(0xD631);send_bus_8(0x1F);
  send_bus_16(0xD632);send_bus_8(0x03);
  send_bus_16(0xD633);send_bus_8(0x7F);
   
  //#LV2 Page 0 enable
  send_bus_16(0xF000);send_bus_8(0x55);
  send_bus_16(0xF001);send_bus_8(0xAA);
  send_bus_16(0xF002);send_bus_8(0x52);
  send_bus_16(0xF003);send_bus_8(0x08);
  send_bus_16(0xF004);send_bus_8(0x00); 
  
  //#DISPLAY CONTROL
  send_bus_16(0xB100);send_bus_8(0xCC);
  send_bus_16(0xB101);send_bus_8(0x00); 

  //#SOURCE HOLD TIME
  send_bus_16(0xB600);send_bus_8(0x05);
  
  //Set Gate EQ     
  send_bus_16(0xB700);send_bus_8(0x70); 
  send_bus_16(0xB701);send_bus_8(0x70);
  
  //#Source EQ control (Mode 2)
  send_bus_16(0xB800);send_bus_8(0x01);
  send_bus_16(0xB801);send_bus_8(0x03);
  send_bus_16(0xB802);send_bus_8(0x03);
  send_bus_16(0xB803);send_bus_8(0x03);
  
  //#INVERSION MODE
  send_bus_16(0xBC00);send_bus_8(0x02);
  send_bus_16(0xBC01);send_bus_8(0x00);  
  send_bus_16(0xBC02);send_bus_8(0x00); 
  
  //#Timing control
  send_bus_16(0xC900);send_bus_8(0xD0);   
  send_bus_16(0xC901);send_bus_8(0x02);
  send_bus_16(0xC902);send_bus_8(0x50);
  send_bus_16(0xC903);send_bus_8(0x50); 
  send_bus_16(0xC904);send_bus_8(0x50); 
  

  send_bus_16(0x3500);   send_bus_8(0x00); 


  send_bus_16(0x3A00);   send_bus_8(0x55); //Data format 16-Bits

  send_bus_16(0x3600);   send_bus_8(0x00);   


  send_bus_16(0x1100);   //StartUp  
  delay(120);
  send_bus_16(0x2900);   //Display On  
  delay(100);
  
}
