/***************************************************
//Web: http://www.buydisplay.com
EastRising Technology Co.,LTD
****************************************************/
#include "tinySPI.h"
#include "er_oled.h"

#include <Arduino.h>

void command(uint8_t cmd){
    digitalWrite(OLED_DC, LOW);
    SPIWrite(&cmd, 1);
    digitalWrite(OLED_DC, HIGH);
}

void SPIWrite(uint8_t *buffer, int bufferLength) {
    int i;
    for (i = 0; i < bufferLength; i++) {
        #ifdef _software_SPI
          shiftOut(OLED_SDA, OLED_SCL, MSBFIRST, buffer[i]);
        #else
          SPI.transfer(buffer[i]);
        #endif
    }
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
    command(0xAE); /*display off*/ 
    command(0x00); /*set lower column address*/ 
    command(0x10); /*set higher column address*/
    command(0xB0); /*set page address*/ 
    command(0x40); /*set display start lines*/ 
    command(0x81); /*contract control*/ 
    command(0x80); /*4d*/ 
    command(0x82); /* iref resistor set and adjust ISEG*/ 
    command(0x00); 
    command(0xA0); /*set segment remap 0xA0*/ 
    command(0xA2); /*set seg pads hardware configuration*/ 
    command(0xA4); /*Disable Entire Display On (0xA4/0xA5)*/ 
    command(0xA6); /*normal / reverse*/ 
    command(0xA8); /*multiplex ratio*/ 
    command(0x3F); /*duty = 1/64*/ 
    command(0xC0); /*Com scan direction 0XC0*/ 
    command(0xD3); /*set display offset*/ 
    command(0x00); /* */ 
    command(0xD5); /*set osc division*/ 
    command(0xa0); 
    command(0xD9); /*set pre-charge period*/ 
    command(0x22); 
    command(0xdb); /*set vcomh*/ 
    command(0x40); 
    command(0x31); /* Set pump 7.4v */ 
    command(0xad); /*set charge pump enable*/ 
    command(0x8b); /*Set DC-DC enable (0x8a=disable; 0x8b=enable) */ 
    
    command(0xAF);
    delay(100);
}

void er_oled_display()
{   
  uint8_t page,i;   
  uint8_t buff = {0xff};
  for (page = 0; page < PAGES; page++) {         
      command(0xB0 + page);/* set page address */     
      command(0x00);   /* set low column address */      
      command(0x10);  /* set high column address */      
      //digitalWrite(OLED_DC, HIGH);
      //SPIWrite(pBuf, WIDTH); /* write data  one page*/
      //pBuf += WIDTH;        
      for(i = 0; i< WIDTH; i++ ) {
        digitalWrite(OLED_DC, HIGH);
        SPIWrite(buff, 1);
      }        
  }
}

void er_oled_fill(uint8_t* buffer)
{
  int i;
  for(i = 0;i < WIDTH * HEIGHT / 8;i++)
  {
    buffer[i] = 0xff;
  }
}

void er_oled_clear(uint8_t* buffer)
{
	int i;
	for(i = 0;i < WIDTH * HEIGHT / 8;i++)
	{
		buffer[i] = 0;
	}
}

void er_oled_pixel(int x, int y, char color, uint8_t* buffer)
{
    if(x > WIDTH || y > HEIGHT)return ;
    if(color)
        buffer[x+(y/8)*WIDTH] |= 1<<(y%8);
    else
        buffer[x+(y/8)*WIDTH] &= ~(1<<(y%8));
}



void er_oled_bitmap(uint8_t x,uint8_t y,const uint8_t *pBmp, uint8_t chWidth, uint8_t chHeight, uint8_t* buffer)
{
	uint8_t i, j, byteWidth = (chWidth + 7)/8;
	for(j = 0;j < chHeight;j++){
		for(i = 0;i <chWidth;i++){
			if(pgm_read_byte(pBmp + j * byteWidth + i / 8) & (128 >> (i & 7))){
				er_oled_pixel(x + i,y + j, 1, buffer);
			}
		}
	}		
}
