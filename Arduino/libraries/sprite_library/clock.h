#ifndef _CLOCK_H
#define _CLOCK_H

#include "Arduino.h"
#include <Adafruit_PCD8544.h>
#include <sprites.h>

void draw_clock(int hours,int minutes,Adafruit_PCD8544 lcd);

#endif
