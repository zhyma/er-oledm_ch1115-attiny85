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
//        SPI.transfer(buffer[i]);
        shiftOut(1, 2,MSBFIRST, buffer[i]);
    }
}

void er_oled_begin()
{

    pinMode(OLED_RST, OUTPUT);
    pinMode(OLED_DC, OUTPUT);
    digitalWrite(OLED_DC, HIGH);
//    pinMode(OLED_CS, OUTPUT);
//    SPI.begin();
    
//    SPI.setClockDivider(SPI_CLOCK_DIV128);
    
//    digitalWrite(OLED_CS, LOW);
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

void er_oled_display(uint8_t* pBuf)
{    uint8_t page,i;   
    for (page = 0; page < PAGES; page++) {         
        command(0xB0 + page);/* set page address */     
        command(0x00);   /* set low column address */      
        command(0x10);  /* set high column address */      
        //digitalWrite(OLED_DC, HIGH);
        //SPIWrite(pBuf, WIDTH); /* write data  one page*/
        //pBuf += WIDTH;        
        for(i = 0; i< WIDTH; i++ ) {
          digitalWrite(OLED_DC, HIGH);
//          SPIWrite(pBuf, 1);// write data one
          shiftOut(1, 2,MSBFIRST, 0xff);
//          *pBuf++;
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

void er_oled_char1616(uint8_t x, uint8_t y, uint8_t chChar, uint8_t* buffer)
{
	uint8_t i, j;
	uint8_t chTemp = 0, y0 = y, chMode = 0;

	for (i = 0; i < 32; i++) {
		chTemp = pgm_read_byte(&Font1612[chChar - 0x30][i]);
		for (j = 0; j < 8; j++) {
			chMode = chTemp & 0x80? 1 : 0; 
			er_oled_pixel(x, y, chMode, buffer);
			chTemp <<= 1;
			y++;
			if ((y - y0) == 16) {
				y = y0;
				x++;
				break;
			}
		}
	}
}

void er_oled_char(unsigned char x, unsigned char y, char acsii, char size, char mode, uint8_t* buffer)
{
    unsigned char i, j, y0=y;
    char temp;
    unsigned char ch = acsii - ' ';
    for(i = 0;i<size;i++) {
        if(size == 12)
        {
            if(mode)temp = pgm_read_byte(&Font1206[ch][i]);
            else temp = ~pgm_read_byte(&Font1206[ch][i]);
        }
        else 
        {            
            if(mode)temp = pgm_read_byte(&Font1608[ch][i]);
            else temp = ~pgm_read_byte(&Font1608[ch][i]);
        }
        for(j =0;j<8;j++)
        {
            if(temp & 0x80) er_oled_pixel(x, y, 1, buffer);
            else er_oled_pixel(x, y, 0, buffer);
            temp <<= 1;
            y++;
            if((y-y0) == size)
            {
                y = y0;
                x++;
                break;
            }
        }
    }
}

void er_oled_string(uint8_t x, uint8_t y, const char *pString, uint8_t Size, uint8_t Mode, uint8_t* buffer)
{
    while (*pString != '\0') {       
        if (x > (WIDTH - Size / 2)) {
            x = 0;
            y += Size;
            if (y > (HEIGHT - Size)) {
                y = x = 0;
            }
        }
        
        er_oled_char(x, y, *pString, Size, Mode, buffer);
        x += Size / 2;
        pString++;
    }
}

void er_oled_char3216(uint8_t x, uint8_t y, uint8_t chChar, uint8_t* buffer)
{
    uint8_t i, j;
    uint8_t chTemp = 0, y0 = y, chMode = 0;

    for (i = 0; i < 64; i++) {
        chTemp = pgm_read_byte(&Font3216[chChar - 0x30][i]);
        for (j = 0; j < 8; j++) {
            chMode = chTemp & 0x80? 1 : 0; 
            er_oled_pixel(x, y, chMode, buffer);
            chTemp <<= 1;
            y++;
            if ((y - y0) == 32) {
                y = y0;
                x++;
                break;
            }
        }
    }
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
