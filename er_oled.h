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
void SPIWrite(uint8_t *buffer, int bufferLength);
void command(uint8_t cmd);


#endif
