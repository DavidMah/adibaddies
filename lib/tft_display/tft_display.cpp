//Technical support:goodtft@163.com
// Breakout/Arduino UNO pin usage:
// LCD Data Bit :   7   6   5   4   3   2   1   0
// Uno dig. pin :   7   6   5   4   3   2   9   8
// Uno port/pin : PD7 PD6 PD5 PD4 PD3 PD2 PB1 PB0
// Mega dig. pin:  29  28  27  26  25  24  23  22
#include <Arduino.h>
#include "tft_display.h"

#define LCD_RD_PIN   A0
#define LCD_WR_PIN   A1
#define LCD_RS_PIN   A2
#define LCD_CS_PIN   A3
#define LCD_REST_PIN A4

#define SCREEN_WIDTH tft_display_SCREEN_WIDTH
#define SCREEN_HEIGHT tft_display_SCREEN_HEIGHT

#define PORT_OUTPUT_REGISTER portOutputRegister
#define DIGITAL_PIN_TO_PORT digitalPinToPort
#define DIGITAL_PIN_TO_BIT_MASK digitalPinToBitMask


void Lcd_Writ_Bus(unsigned char d) {
  PORTD = (PORTD & B00000011) | ((d) & B11111100);
  PORTB = (PORTB & B11111100) | ((d) & B00000011);
  *(PORT_OUTPUT_REGISTER(DIGITAL_PIN_TO_PORT(LCD_WR_PIN))) &=  ~DIGITAL_PIN_TO_BIT_MASK(LCD_WR_PIN);
  *(PORT_OUTPUT_REGISTER(DIGITAL_PIN_TO_PORT(LCD_WR_PIN)))|=  DIGITAL_PIN_TO_BIT_MASK(LCD_WR_PIN);
}


void Lcd_Write_Com(unsigned char VH)
{
  *(PORT_OUTPUT_REGISTER(DIGITAL_PIN_TO_PORT(LCD_RS_PIN))) &=  ~DIGITAL_PIN_TO_BIT_MASK(LCD_RS_PIN);//LCD_RS_PIN=0;
  Lcd_Writ_Bus(VH);
}

void Lcd_Write_Data(unsigned char VH)
{
  *(PORT_OUTPUT_REGISTER(DIGITAL_PIN_TO_PORT(LCD_RS_PIN)))|=  DIGITAL_PIN_TO_BIT_MASK(LCD_RS_PIN);//LCD_RS_PIN=1;
  Lcd_Writ_Bus(VH);
}

void Lcd_Write_Com_Data(unsigned char com,unsigned char dat)
{
  Lcd_Write_Com(com);
  Lcd_Write_Data(dat);
}

void Address_set(unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2)
{
        Lcd_Write_Com(0x2a);
	Lcd_Write_Data(x1>>8);
	Lcd_Write_Data(x1);
	Lcd_Write_Data(x2>>8);
	Lcd_Write_Data(x2);
        Lcd_Write_Com(0x2b);
	Lcd_Write_Data(y1>>8);
	Lcd_Write_Data(y1);
	Lcd_Write_Data(y2>>8);
	Lcd_Write_Data(y2);
	Lcd_Write_Com(0x2c);
}

void Lcd_Init(void)
{
  digitalWrite(LCD_REST_PIN,HIGH);
  delay(5);
  digitalWrite(LCD_REST_PIN,LOW);
  delay(15);
  digitalWrite(LCD_REST_PIN,HIGH);
  delay(15);

  digitalWrite(LCD_CS_PIN,HIGH);
  digitalWrite(LCD_WR_PIN,HIGH);
  digitalWrite(LCD_CS_PIN,LOW);  //CS

    Lcd_Write_Com(0xCB);
    Lcd_Write_Data(0x39);
    Lcd_Write_Data(0x2C);
    Lcd_Write_Data(0x00);
    Lcd_Write_Data(0x34);
    Lcd_Write_Data(0x02);

    Lcd_Write_Com(0xCF);
    Lcd_Write_Data(0x00);
    Lcd_Write_Data(0XC1);
    Lcd_Write_Data(0X30);

    Lcd_Write_Com(0xE8);
    Lcd_Write_Data(0x85);
    Lcd_Write_Data(0x00);
    Lcd_Write_Data(0x78);

    Lcd_Write_Com(0xEA);
    Lcd_Write_Data(0x00);
    Lcd_Write_Data(0x00);

    Lcd_Write_Com(0xED);
    Lcd_Write_Data(0x64);
    Lcd_Write_Data(0x03);
    Lcd_Write_Data(0X12);
    Lcd_Write_Data(0X81);

    Lcd_Write_Com(0xF7);
    Lcd_Write_Data(0x20);

    Lcd_Write_Com(0xC0);    //Power control
    Lcd_Write_Data(0x23);   //VRH[5:0]

    Lcd_Write_Com(0xC1);    //Power control
    Lcd_Write_Data(0x10);   //SAP[2:0];BT[3:0]

    Lcd_Write_Com(0xC5);    //VCM control
    Lcd_Write_Data(0x3e);   //Contrast
    Lcd_Write_Data(0x28);

    Lcd_Write_Com(0xC7);    //VCM control2
    Lcd_Write_Data(0x86);   //--

    Lcd_Write_Com(0x36);    // Memory Access Control
    Lcd_Write_Data(0x48);

    Lcd_Write_Com(0x3A);
    Lcd_Write_Data(0x55);

    Lcd_Write_Com(0xB1);
    Lcd_Write_Data(0x00);
    Lcd_Write_Data(0x18);

    Lcd_Write_Com(0xB6);    // Display Function Control
    Lcd_Write_Data(0x08);
    Lcd_Write_Data(0x82);
    Lcd_Write_Data(0x27);

    Lcd_Write_Com(0x11);    //Exit Sleep
    delay(120);
				
    Lcd_Write_Com(0x29);    //Display on
    Lcd_Write_Com(0x2c);
}



/* int RGB(int red, int green, int blue) {*/
/*   return red << 16 | green << 8 | blue;*/
/* }*/

void LCD_Clear(unsigned int j)
{	
  unsigned int i,m;
 Address_set(0,0,240,320);
  //Lcd_Write_Com(0x02c); //write_memory_start
  //digitalWrite(LCD_RS_PIN,HIGH);
  digitalWrite(LCD_CS_PIN,LOW);

  for(i=0;i<240;i++) {
    for(m=0;m<320;m++)
    {
      Lcd_Write_Data(j>>8);
      Lcd_Write_Data(j);

    }
  }
  digitalWrite(LCD_CS_PIN,HIGH);
}

void tft_display_setup()
{
  for(int pin=0; pin<10; pin+=1) {
    pinMode(pin, OUTPUT);
  }
  pinMode(A0,OUTPUT);
  pinMode(A1,OUTPUT);
  pinMode(A2,OUTPUT);
  pinMode(A3,OUTPUT);
  pinMode(A4,OUTPUT);
  digitalWrite(A0, HIGH);
  digitalWrite(A1, HIGH);
  digitalWrite(A2, HIGH);
  digitalWrite(A3, HIGH);
  digitalWrite(A4, HIGH);
  Lcd_Init();
}

void tft_display_drawVerticalLine(unsigned int x, unsigned int y, unsigned int height, unsigned int color) {	
  unsigned int i,j;
  Lcd_Write_Com(0x02c); //write_memory_start
  digitalWrite(LCD_RS_PIN,HIGH);
  digitalWrite(LCD_CS_PIN,LOW);
  height+=x;
  Address_set(x,y,height,y);
  j=height*2;
  for(i=1;i<=j;i++) {
    Lcd_Write_Data(color);
  }
  digitalWrite(LCD_CS_PIN,HIGH);
}

void tft_display_drawHorizontalLine(unsigned int x, unsigned int y, unsigned int l, unsigned int c) {	
  unsigned int i,j;
  Lcd_Write_Com(0x02c); //write_memory_start
  digitalWrite(LCD_RS_PIN,HIGH);
  digitalWrite(LCD_CS_PIN,LOW);
  l=l+y;
  Address_set(x,y,x,l);
  j=l*2;
  for(i=1;i<=j;i++) {
    Lcd_Write_Data(c);
  }
  digitalWrite(LCD_CS_PIN,HIGH);
}
