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

#define LCD_WR_PORT_OUTPUT_REGISTER *(portOutputRegister(digitalPinToPort(LCD_WR_PIN)))
#define LCD_RS_PORT_OUTPUT_REGISTER *(portOutputRegister(digitalPinToPort(LCD_RS_PIN)))

#define SCREEN_WIDTH tft_display_SCREEN_WIDTH
#define SCREEN_HEIGHT tft_display_SCREEN_HEIGHT

#define POSITIVE_BITS_8 B11111111
#define POSITIVE_BITS_16 (POSITIVE_BITS_8 << 8 | POSITIVE_BITS_8)
#define POSITIVE_BITS_32 (POSITIVE_BITS_16 << 16 | POSITIVE_BITS_16)


void Lcd_Writ_Bus(unsigned char bits) {
    // For the ifdef below: We are doing port manipulations to write
    // output faster than we could via individual digitalWrite calls.
    // The main reason its faster is batching.
    //
    // The else clause is the naive implementation. It works, but damn
    // it is slow.
#if defined(ARDUINO_AVR_UNO)
    // https://www.instructables.com/Arduino-and-Port-Manipulation/
    PORTD = (PORTD & B00000011) | (bits & B11111100); // Digital Pins 7 to 0 (LSB maps to 0)
    PORTB = (PORTB & B11111100) | (bits & B00000011); // Digital Pins 13 to 8 (LSB maps to 8)
#elif defined(ARDUINO_SAM_DUE)
    // https://forum.arduino.cc/t/arduino-due-ports-manipulation/452044/3
    // Port table at https://github.com/arduino/ArduinoCore-sam/blob/master/variants/arduino_due_x/variant.cpp#L21
    // (bits & B00001000) // Pin 3
    // (bits & B00010000) // Pin 4
    // (bits & B00100000) // Pin 5
    // (bits & B01000000) // Pin 6
    // (bits & B10000000) // Pin 7
    // (bits & B00000001) // Pin 8
    // (bits & B00000010) // Pin 9
    // PIOB -> PIO_SODR = ARDUINO_SAM_DUE_PIN_MASK
    //   PB25
    // 1 << 25
    // PIOB->PIO_SODR = (PIOB->PIO_SODR & (POSITIVE_BITS_32 xor (1<<25))) | (((bits & B00000100) >> 2) << 25); // Pin 2
    // REG_PIOB_SODR = 0x1 << 25
    digitalWrite(2, (bits & B00000100) >> 2);
    digitalWrite(3, (bits & B00001000) >> 3);
    digitalWrite(4, (bits & B00010000) >> 4);
    digitalWrite(5, (bits & B00100000) >> 5);
    digitalWrite(6, (bits & B01000000) >> 6);
    digitalWrite(7, (bits & B10000000) >> 7);
    digitalWrite(8, (bits & B00000001) >> 0);
    digitalWrite(9, (bits & B00000010) >> 1);
    // if (((bits & B00000010) >> 1) == 1) {
    //   REG_PIOD_SODR |= ((bits & B00000010) >> 1) << 9;
    // } else {
    //   REG_PIOD_CODR |= ((bits & B00000010) >> 1) << 9;
    // }
#else
    digitalWrite(2, (bits & B00000100) >> 2);
    digitalWrite(3, (bits & B00001000) >> 3);
    digitalWrite(4, (bits & B00010000) >> 4);
    digitalWrite(5, (bits & B00100000) >> 5);
    digitalWrite(6, (bits & B01000000) >> 6);
    digitalWrite(7, (bits & B10000000) >> 7);
    digitalWrite(8, (bits & B00000001) >> 0);
    digitalWrite(9, (bits & B00000010) >> 1);
#endif

    LCD_WR_PORT_OUTPUT_REGISTER &= ~digitalPinToBitMask(LCD_WR_PIN);
    LCD_WR_PORT_OUTPUT_REGISTER |= digitalPinToBitMask(LCD_WR_PIN);
}


void Lcd_Write_Com(unsigned char VH)
{
    LCD_RS_PORT_OUTPUT_REGISTER &= ~digitalPinToBitMask(LCD_RS_PIN); // LCD_RS_PIN=0;
    Lcd_Writ_Bus(VH);
}

void Lcd_Write_Data(unsigned char VH)
{
    LCD_RS_PORT_OUTPUT_REGISTER |= digitalPinToBitMask(LCD_RS_PIN); // LCD_RS_PIN=1;
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
    digitalWrite(LCD_CS_PIN,LOW);  // CS

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

    Lcd_Write_Com(0xC0);    // Power control
    Lcd_Write_Data(0x23);   // VRH[5:0]

    Lcd_Write_Com(0xC1);    // Power control
    Lcd_Write_Data(0x10);   // SAP[2:0];BT[3:0]

    Lcd_Write_Com(0xC5);    // VCM control
    Lcd_Write_Data(0x3e);   // Contrast
    Lcd_Write_Data(0x28);

    Lcd_Write_Com(0xC7);    // VCM control2
    Lcd_Write_Data(0x86);   // --

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

void tft_display_setup() {
    pinMode(0, OUTPUT);
    pinMode(1, OUTPUT);
    pinMode(2, OUTPUT);
    pinMode(3, OUTPUT);
    pinMode(4, OUTPUT);
    pinMode(5, OUTPUT);
    pinMode(6, OUTPUT);
    pinMode(7, OUTPUT);
    pinMode(8, OUTPUT);
    pinMode(9, OUTPUT);
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

void tft_display_drawHorizontalLine(unsigned int x, unsigned int y, unsigned int width, unsigned int color) {
    unsigned int i,j;
    Lcd_Write_Com(0x02c); // write_memory_start
    digitalWrite(LCD_RS_PIN,HIGH);
    digitalWrite(LCD_CS_PIN,LOW);

    Address_set(x, y, x+width, y);
    for (int index = 0; index < width; index += 1) {
        Lcd_Write_Data(color);
        Lcd_Write_Data(color);
    }
    digitalWrite(LCD_CS_PIN,HIGH);
}

void tft_display_drawVerticalLine(unsigned int x, unsigned int y, unsigned int height, unsigned int color) {
    unsigned int i,j;
    Lcd_Write_Com(0x02c); // write_memory_start
    digitalWrite(LCD_RS_PIN,HIGH);
    digitalWrite(LCD_CS_PIN,LOW);

    Address_set(x, y, x, y+height);
    for (int index = 0; index < height; index += 1) {
        Lcd_Write_Data(color);
        Lcd_Write_Data(color);
    }
    digitalWrite(LCD_CS_PIN,HIGH);
}

void tft_display_drawRectangle(unsigned int x, unsigned int y, unsigned int width, unsigned int height, unsigned int color) {
    for (int index = 0; index < height; index += 1) {
        tft_display_drawHorizontalLine(x, y+index, width, color);
    }
}

void tft_display_drawRectanglePoints(unsigned int x, unsigned int y, unsigned int x2, unsigned int y2, unsigned int color) {
    for (int index = 0; index < max(y, y2); index += 1) {
        tft_display_drawHorizontalLine(min(x, x2), min(y, y2)+index, abs(x2-x), color);
    }
}

void tft_display_moveRectangle(unsigned int priorX, unsigned int priorY, unsigned int width, unsigned int height, unsigned int color, unsigned int backgroundColor, unsigned int newX, unsigned int newY) {
    auto movedLeft = (priorX > newX);
    auto movedRight = (priorX < newX);
    auto movedDown = (priorY < newY);
    auto movedUp = (priorY > newY);

    if (!movedLeft && !movedRight && !movedDown && !movedUp) {
        // No change, so don't need to do anything
    } else if (width < abs(newX - priorX) || height < abs(newY - priorY)) {
        unsigned int xPoints[4] = {
            movedRight ? priorX : newX,
            movedRight ? newX : priorX,
            movedRight ? priorX+width : newX+width,
            movedRight ? newX+width : priorX+width,
        };
        unsigned int yPoints[4] = {
            movedDown ? priorY : newY,
            movedDown ? newY : priorY,
            movedDown ? priorY+width : newY+width,
            movedDown ? newY+width : priorY+width,
        };

        // Crazy algo that doesn't work
        // if (movedRight || movedDown) {
        //   tft_display_drawRectanglePoints(xPoints[0], yPoints[0], xPoints[1], yPoints[1], backgroundColor); // A
        // }
        // if (movedDown) {
        //   tft_display_drawRectanglePoints(xPoints[1], yPoints[0], xPoints[2], yPoints[1], backgroundColor); // B
        // }
        // if (movedLeft || movedDown) {
        //   tft_display_drawRectanglePoints(xPoints[2], yPoints[0], xPoints[3], yPoints[1], backgroundColor); // C
        // }
        // if (movedRight) {
        //   tft_display_drawRectanglePoints(xPoints[0], yPoints[1], xPoints[1], yPoints[2], backgroundColor); // D
        // }
        // // E is the center, never needs to be touched
        // if (movedLeft) {
        //   tft_display_drawRectanglePoints(xPoints[1], yPoints[1], xPoints[3], yPoints[2], backgroundColor); // F
        // }
        // if (movedRight || movedUp) {
        //   tft_display_drawRectanglePoints(xPoints[0], yPoints[2], xPoints[1], yPoints[3], backgroundColor); // G
        // }
        // if (movedUp) {
        //   tft_display_drawRectanglePoints(xPoints[1], yPoints[2], xPoints[2], yPoints[3], backgroundColor); // H
        // }
        // if (movedLeft) {
        //   tft_display_drawRectanglePoints(xPoints[2], yPoints[2], xPoints[3], yPoints[3], backgroundColor); // I
        // }

        tft_display_drawRectangle(priorX, priorY, width, height, backgroundColor);
        tft_display_drawRectangle(newX, newY, width, height, color);
    } else {
        // No overlap, we have to erase the old to replace with the new
        tft_display_drawRectangle(priorX, priorY, width, height, backgroundColor);
        tft_display_drawRectangle(newX, newY, width, height, color);

        // min(priorY, newY)

        // tft_display_drawRectangle(priorX, priorY, newX-priorX, newY-priorY, backgroundColor); // A
        // tft_display_drawRectangle(priorX, priorY, newX-priorX, newY-priorY, backgroundColor); // B
        // tft_display_drawRectangle(priorX, priorY, newX-priorX, newY-priorY, backgroundColor); // C
        // tft_display_drawRectangle(priorX, priorY, newX-priorX, newY-priorY, backgroundColor); // D
        // tft_display_drawRectangle(priorX, priorY, newX-priorX, newY-priorY, color); // E
        // tft_display_drawRectangle(priorX, priorY, newX-priorX, newY-priorY, color); // F
        // tft_display_drawRectangle(priorX, priorY, newX-priorX, newY-priorY, color); // G
        // tft_display_drawRectangle(priorX, priorY, newX-priorX, newY-priorY, color); // H
    }
}

void tft_display_drawCircle(unsigned int x, unsigned int y, unsigned int radius, unsigned int color) {
    int diameter = radius*2;
    for (int index = 0; index < diameter; index += 1) {
        int width = int(sqrt((radius*radius) - (radius - index)*(radius-index)));
        tft_display_drawHorizontalLine(
            radius-width,
            y+index,
            width*2,
            color);
    }
}
