/*!
 * @file animation.h
 */

#ifndef animation_h
#define animation_h

#include "er_oled.h"
//#include "TrueRandom.h"
#include "bitmap.h"

extern ErOLED ErOLED;

void sweating_init();
void sweating_loop(int timer);
void lick_init();
void lick_loop(int timer);
//void rns_init();
//void rns_loop();

#endif
