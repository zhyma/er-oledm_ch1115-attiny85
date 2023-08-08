/***************************************************
//Web: http://www.buydisplay.com
EastRising Technology Co.,LTD
****************************************************/
  
#ifndef _oled_ch1115_12864_H_
#define _oled_ch1115_12864_H_

#include <Arduino.h>
#include <avr/pgmspace.h>

//#define _software_SPI

#define WIDTH 128
#define HEIGHT 64
#define PAGES HEIGHT/8

#ifdef _software_SPI
#define OLED_SDA 1
#define OLED_SCL 2
#endif

#define OLED_RST 3
#define OLED_DC  4

#define OLED_INIT_LEN   28
const uint8_t OLED_INIT_CMD[] PROGMEM = {
  0xAE,             // display off
  0x00, 0x10, 0xB0, // set lower column address, higher column address, and page address
  0x40,             //set display start lines
  0x81, 0x00,       //contract control, default 0x80
  0x82, 0x00,       //iref resistor set and adjust ISEG
  0xA0,             // set segment remap 0xA0
  0xA2,             // set seg pads hardware configuration
  0xA4,             // disable entire display on (0xA4, 0xA5)
  0xA6,             // normal (0xA7 is reverse)
  0xA8,             // multiplex ratio
  0x3F,             // duty = 1/64
  0xC0,             // Com scan direction 0xC0
  0xD3, 0x00,       // set display offset
  0xD5, 0xA0,       // set osc division
  0xD9, 0x22,       // set pre-charge period
  0xDB, 0x40,       // set vcomh
  0x31,             // set pump 7.4v
  0xAD,             // set charge pump enable
  0x8B,             // set dc-dc enable (0x8A=disable; 0x8B=enable)
  0xAF
};

class ErOLED {
  public:
    void init();
    //void er_oled_display(uint8_t* buffer);
    void SPIWrite(uint8_t data);
    void sendCommand(uint8_t cmd);
    void drawBitmap(const byte *bitmap, byte X, byte Y, uint8_t w, uint8_t h);
    void setCursorXY(byte X, byte Y);
};

extern ErOLED oled;

#endif
