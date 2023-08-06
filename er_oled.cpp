/***************************************************
//Web: http://www.buydisplay.com
EastRising Technology Co.,LTD
****************************************************/
#include "tinySPI.h"
#include "er_oled.h"

#include <Arduino.h>

void sendCommand(uint8_t cmd){
  digitalWrite(OLED_DC, LOW);
  SPIWrite(cmd);
  digitalWrite(OLED_DC, HIGH);
}

void SPIWrite(uint8_t data) {
  #ifdef _software_SPI
    shiftOut(OLED_SDA, OLED_SCL, MSBFIRST, data);
  #else
    SPI.transfer(data);
  #endif
}

void er_oled_begin()
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

void er_oled_display()
{   
  uint8_t page,i;   
  uint8_t buff = 0x01;
  for (page = 0; page < PAGES; page++) {         
      sendCommand(0xB0 + page);/* set page address */     
      sendCommand(0x00);   /* set low column address */      
      sendCommand(0x10);  /* set high column address */      
      //digitalWrite(OLED_DC, HIGH);
      //SPIWrite(pBuf, WIDTH); /* write data  one page*/
      //pBuf += WIDTH;        
      for(i = 0; i< WIDTH; i++ ) {
        digitalWrite(OLED_DC, HIGH);
        buff = buff << 1;
        if (buff==0)
          buff = 0x01;
        SPIWrite(buff);
      }        
  }
}
