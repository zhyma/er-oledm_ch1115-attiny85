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
//  Serial.begin(9600);
//  Serial.print("OLED Example\n");

  /* display an image of bitmap matrix */

  pinMode(0, OUTPUT);
  pinMode(1, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  er_oled_begin();
}

void loop() {
//  shiftOut(1, 2,MSBFIRST, 0x0f);
////digitalWrite(0, HIGH);
////digitalWrite(1, HIGH);
////digitalWrite(2, HIGH);
////digitalWrite(3, HIGH);
////digitalWrite(4, HIGH);
//delay(10);
////digitalWrite(0, LOW);
////digitalWrite(1, LOW);
////digitalWrite(2, LOW);
////digitalWrite(3, LOW);
////digitalWrite(4, LOW);
//delay(10);

//er_oled_begin();
delay(100);

//  er_oled_display(oled_buf);
}
