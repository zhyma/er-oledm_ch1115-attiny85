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
  *3. SCL    ->    2
  *4. SDA    ->    1
  *5. RES    ->    3
  *6. DC     ->    4
  *7. CS     ->    10K TO GND
*/


#include "tinySPI.h"
//#include <SPI.h>
#include "er_oled.h"

#include "animation.h"
#include "bitmap.h"

uint8_t oled_buf[WIDTH * HEIGHT / 8];

void setup() {
  ErOled.init();
  delay(100);
  ErOled.drawBitmap(NULL, 0, 0, 128, 8);
  delay(100);
}

void loop() {
//  ErOled.drawBitmap(lick_0, 36, 2, 56, 1);
//
//  delay(3000);
  uint8_t countDown = 200;
  lick_init();
  while(countDown > 0){
    lick_loop(countDown);
    countDown -= 1;
  }
  
  countDown = 200;
  sweating_init();
  while(countDown > 0){
    sweating_loop(countDown);
    countDown -= 1;
  }
  
}
