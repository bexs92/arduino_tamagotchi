#include "clock.h"
#include "Arduino.h"
#include <Adafruit_PCD8544.h>
#include <sprites.h>

const unsigned char* clock_bitmaps[24]={
    clock_0,
    clock_1,
    clock_2,
    clock_3,
    clock_4,
    clock_5,
    clock_6,
    clock_7,
    clock_8,
    clock_9,
    clock_10,
    clock_11,
    clock_12,
    clock_13,
    clock_14,
    clock_15,
    clock_16,
    clock_17,
    clock_18,
    clock_19,
    clock_20,
    clock_21,
    clock_22,
    clock_23
};

extern const unsigned char* number_bitmap[10] = {
    number_0,
    number_1,
    number_2,
    number_3,
    number_4,
    number_5,
    number_6,
    number_7,
    number_8,
    number_9
};

void draw_clock(int hours,int minutes,Adafruit_PCD8544 lcd){

    lcd.drawBitmap(52,0,clock_bitmaps[hours],17,17,BLACK);

    float angle = 0.105*(minutes-15);

    int y_value = round(4*(sin(angle)));
    int x_value = round(4*(cos(angle)));

    if(minutes>16&&minutes<42){
        lcd.drawLine(60,8,60+x_value,8+y_value,BLACK);
    }

    else {
        lcd.drawLine(60,8,60+x_value,8+y_value,WHITE);
    }


    lcd.drawBitmap(52,18,number_bitmap[round(hours/10)],3,5,BLACK);
    lcd.drawBitmap(56,18,number_bitmap[hours%10],3,5,BLACK);
    lcd.drawBitmap(59,18,number_colon,3,5,BLACK);
    lcd.drawBitmap(62,18,number_bitmap[round(minutes/10)],3,5,BLACK);
    lcd.drawBitmap(66,18,number_bitmap[minutes%10],3,5,BLACK);
}
