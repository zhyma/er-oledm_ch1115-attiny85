/***************************************************
//Web: http://www.buydisplay.com
EastRising Technology Co.,LTD
Examples for ER-OLEDM1.09-1
Display is Hardward SPI 4-Wire SPI Interface 
Tested and worked with:
Works with Arduino 1.6.0 IDE  
Test OK : Arduino DUE,Arduino mega2560,Arduino UNO Board 
****************************************************/
 
/*
  == Hardware connection ==
    OLED   =>    Arduino
  *1. GND    ->    GND
  *2. VCC    ->    3.3
  *3. SCL    ->    SCK
  *4. SDA    ->    MOSI
  *5. RES    ->    8 
  *6. DC     ->    9
  *7. CS     ->    10
*/


#include "tinySPI.h"
//#include <SPI.h>
#include "er_oled.h"

uint8_t oled_buf[WIDTH * HEIGHT / 8];

void setup() {
  er_oled_begin();
  delay(3000);
//  command(0xa7);
//  delay(3000);
}

void loop() {
//delay(100);
////  SPI.transfer(0x0f);
////command(0x0F);
  er_oled_display();

  delay(1000);  
  command(0xa7);//--set Negative display 
  delay(1000);
  command(0xa6);//--set normal display
}
