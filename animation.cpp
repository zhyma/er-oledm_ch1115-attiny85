/*!
 * @file animation.cpp
 */

#include "animation.h"
#include <Arduino.h>

void sweating_init(){
//  oled.clearArea(0, 0, 128, 4);
   oled.drawBitmap(NULL, 0, 0, 128, 4);
  delay(100);
  oled.drawBitmap(sweat, 96, 1, 16, 2);
}

void sweating_loop(int timer){
  if (timer%20==0)
    oled.drawBitmap(eye_x, 32, 0, 64, 4);
  else if (timer%20==10)
//    oled.clearArea(32, 0, 64, 4);
    oled.drawBitmap(NULL, 32, 0, 64, 4);
  else
    delay(100);
}

void lick_init(){
//  oled.clearArea(0, 0, 128, 4);
   oled.drawBitmap(NULL, 0, 0, 128, 4);
  delay(100);
//  oled.drawBitmap(sweat, 96, 1, 16, 2);
}

void lick_loop(int timer){
  if (timer%60==45)
    oled.drawBitmap(lick_0, 36, 2, 56, 1);
  else if (timer%60==40)
    oled.drawBitmap(lick_1, 36, 2, 56, 1);
  else if (timer%60==35)
    oled.drawBitmap(lick_2, 36, 2, 28, 2);
  else if (timer%60==30)
    oled.drawBitmap(lick_3, 36, 2, 44, 2);
  else if (timer%60==25)
    oled.drawBitmap(lick_4, 42, 2, 44, 2);
  else if (timer%60==20)
    oled.drawBitmap(lick_5, 58, 2, 28, 2);
  else if (timer%60==15)
    oled.drawBitmap(lick_0, 36, 2, 56, 1);
  else
    delay(20);
}

//// reboot Root Name Servers!
//void rns_init(){
//  uint8_t result = 0;
//  oled.drawBitmap(NULL, 0, 0, 128, 4);
//  delay(100);
//  for (int i=0;i<5;i++){
//    result = get_rand();
////    oled.printBigNumber(result%10, 4+24*i, 0);
//    oled.drawBitmap(bigNumbers[result%10], 4+24*i, 0, 24, 4);
//  }
//}
//
//void rns_loop(){
//  int result = get_rand();
////  oled.printBigNumber(result%10, 4+(result/10)%5*24, 0);
//  oled.drawBitmap(bigNumbers[result%10], 4+(result/10)%5*24, 0, 24, 4);
//}
