/***************************************************
//Web: http://www.buydisplay.com
EastRising Technology Co.,LTD
****************************************************/
  
#ifndef _er_oled_H_
#define _er_oled_H_

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


void er_oled_begin();
//void er_oled_display(uint8_t* buffer);
void er_oled_display();
void er_oled_clear(uint8_t* buffer);
void er_oled_fill(uint8_t* buffer);
void er_oled_pixel(int x,int y,char color, uint8_t* buffer);
void er_oled_bitmap(uint8_t x,uint8_t y,const uint8_t *pBmp, uint8_t chWidth, uint8_t chHeight, uint8_t* buffer);
void er_oled_char1616(uint8_t x,uint8_t y,uint8_t chChar, uint8_t* buffer);
void er_oled_char3216(uint8_t x, uint8_t y, uint8_t chChar, uint8_t* buffer);
void er_oled_string(uint8_t x, uint8_t y, const char *pString, uint8_t Size, uint8_t Mode, uint8_t* buffer);
void SPIWrite(uint8_t *buffer, int bufferLength);
void command(uint8_t cmd);


#endif
