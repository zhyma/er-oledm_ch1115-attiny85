/***************************************************
//Web: http://www.buydisplay.com
EastRising Technology Co.,LTD
****************************************************/
#include "tinySPI.h"
#include "er_oled.h"

#include <Arduino.h>
#include <avr/pgmspace.h>

void ErOLED::sendCommand(uint8_t cmd){
  digitalWrite(OLED_DC, LOW);
  SPIWrite(cmd);
  digitalWrite(OLED_DC, HIGH);
}

void ErOLED::SPIWrite(uint8_t data) {
  #ifdef _software_SPI
    shiftOut(OLED_SDA, OLED_SCL, MSBFIRST, data);
  #else
    SPI.transfer(data);
  #endif
}

void ErOLED::init()
{
    #ifdef _software_SPI
    pinMode(OLED_SDA, OUTPUT);
    pinMode(OLED_SCL, OUTPUT);
    #endif
    
    pinMode(OLED_RST, OUTPUT);
    pinMode(OLED_DC, OUTPUT);
    digitalWrite(OLED_DC, HIGH);
    #ifndef _software_SPI
      SPI.begin();
    #endif

    digitalWrite(OLED_RST, HIGH);
    delay(10);
    digitalWrite(OLED_RST, LOW);
    delay(10);
    digitalWrite(OLED_RST, HIGH);
    delay(100);

    for (uint8_t i = 0; i < OLED_INIT_LEN; i++){
      sendCommand(pgm_read_byte(&OLED_INIT_CMD[i]));
    }

    delay(100);
}


void ErOLED::setCursorXY(byte X, byte Y){
  // Y up to down,    unit: 1 page (8 pixels)
  // X left to right, unit: 1 seg  (1 pixel)
    sendCommand(0xB0 + Y);/* set page address */     
    sendCommand(0x00 + (X & 0x0F));   /* set low column address */      
    sendCommand(0x10 + ((X>>4)&0x0F));  /* set high column address */    
}

void ErOLED::drawBitmap(const byte *bitmap, byte X, byte Y, uint8_t w, uint8_t h)
{   
  uint8_t i,j;
  setCursorXY(X, Y);
  digitalWrite(OLED_DC, HIGH);
  for (i = 0; i < h; i++) {         
          
      for(j = 0; j< w; j++ ) {
        if (bitmap==NULL)
          SPIWrite(0); // clear area
        else
          SPIWrite(pgm_read_byte(&bitmap[i*w+j]));
      }
      setCursorXY(X, ++Y);
  }
}

ErOLED ErOled;  // Preinstantiate Objects
