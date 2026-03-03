
#include "sprite_loader_lib.h"
#include "Arduino.h"
#include <Adafruit_PCD8544.h>
#include <sprites.h>

void A_fire_tower(int frameNumber,unsigned char* crouch_L,unsigned char* roar_L,Adafruit_PCD8544 lcd) {

    const int frame=7;
    const int dist =32;


    if ((frameNumber%frame)==0){
        lcd.drawBitmap(32,16,crouch_L,16,16,BLACK);
    }

    if ((frameNumber%frame)==1){
        lcd.drawBitmap(32,16,crouch_L,16,16,BLACK);
    }

    if ((frameNumber%frame)==2){
        lcd.drawBitmap(32,16,roar_L,16,16,BLACK);
        lcd.drawBitmap(22,16,F_1_1,8,16,BLACK);
    }

    if ((frameNumber%frame)==3){
        lcd.drawBitmap(32,16,roar_L,16,16,BLACK);
        lcd.drawBitmap(22,16,F_1_2,8,16,BLACK);
        lcd.drawBitmap(16,16,F_1_1,8,16,BLACK);
    }

    if ((frameNumber%frame)==4){
        lcd.drawBitmap(32,16,roar_L,16,16,BLACK);
        lcd.drawBitmap(16,16,F_1_2,8,16,BLACK);
        lcd.drawBitmap(8,16,F_1_1,8,16,BLACK);
    }
    if ((frameNumber%frame)==5){
        lcd.drawBitmap(32,16,roar_L,16,16,BLACK);
        lcd.drawBitmap(8,16,F_1_2,8,16,BLACK);
    }

    if ((frameNumber%frame)==6){
        lcd.drawBitmap(32,16,roar_L,16,16,BLACK);

    }


    //lcd.display();
}
//prominance beam
void A_p_beam(int frameNumber,unsigned char* crouch_L,unsigned char* roar_L,Adafruit_PCD8544 lcd) {

    const int frame=7;
    const int dist =32;

    if ((frameNumber%frame)==0){
        lcd.drawBitmap(32,16,crouch_L,16,16,BLACK);
    }

    if ((frameNumber%frame)==1){
        lcd.drawBitmap(32,16,crouch_L,16,16,BLACK);
    }

    if ((frameNumber%frame)==2){
        lcd.drawBitmap(32,16,roar_L,16,16,BLACK);
        lcd.drawBitmap(22,16,F_2_1,8,16,BLACK);
    }

    if ((frameNumber%frame)==3){
        lcd.drawBitmap(32,16,roar_L,16,16,BLACK);
        lcd.drawBitmap(16,16,F_2_1,8,16,BLACK);
        lcd.drawBitmap(22,16,F_2_2,8,16,BLACK);
    }

    if ((frameNumber%frame)==4){
        lcd.drawBitmap(32,16,roar_L,16,16,BLACK);
        lcd.drawBitmap(8,16,F_2_1,8,16,BLACK);
        lcd.drawBitmap(22,16,F_2_2,8,16,BLACK);
        lcd.drawBitmap(16,16,F_2_2,8,16,BLACK);
    }
    if ((frameNumber%frame)==5){
        lcd.drawBitmap(32,16,roar_L,16,16,BLACK);
        lcd.drawBitmap(8,16,F_2_1,8,16,BLACK);
        //lcd.drawBitmap(16,16,F_2_2,8,16,BLACK);
    }

    if ((frameNumber%frame)==6){
        lcd.drawBitmap(32,16,roar_L,16,16,BLACK);
        //lcd.drawBitmap(8,16,F_2_2,8,16,BLACK);

    }


    //lcd.display();
}

void A_spit_fire(int frameNumber,unsigned char* crouch_L,unsigned char* roar_L,Adafruit_PCD8544 lcd) {

    const int frame=7;
    const int dist =32;

    if ((frameNumber%frame)==0){
        lcd.drawBitmap(32,16,crouch_L,16,16,BLACK);
    }

    if ((frameNumber%frame)==1){
        lcd.drawBitmap(32,16,crouch_L,16,16,BLACK);
    }

    if ((frameNumber%frame)==2){
        lcd.drawBitmap(32,16,roar_L,16,16,BLACK);
        lcd.drawBitmap(22,16,F_3_1,8,16,BLACK);
    }

    if ((frameNumber%frame)==3){
        lcd.drawBitmap(32,16,roar_L,16,16,BLACK);
        lcd.drawBitmap(18,16,F_3_2,8,16,BLACK);

    }

    if ((frameNumber%frame)==4){
        lcd.drawBitmap(32,16,roar_L,16,16,BLACK);
        lcd.drawBitmap(12,16,F_3_1,8,16,BLACK);

    }
    if ((frameNumber%frame)==5){
        lcd.drawBitmap(32,16,roar_L,16,16,BLACK);
        lcd.drawBitmap(8,16,F_3_2,8,16,BLACK);
    }

    if ((frameNumber%frame)==6){
        lcd.drawBitmap(32,16,roar_L,16,16,BLACK);

    }


    //lcd.display();
}

void A_red_inferno(int frameNumber,unsigned char* crouch_L,unsigned char* roar_L,Adafruit_PCD8544 lcd) {

    const int frame=7;
    const int dist =32;

    if ((frameNumber%frame)==0){
        lcd.drawBitmap(32,16,crouch_L,16,16,BLACK);
    }

    if ((frameNumber%frame)==1){
        lcd.drawBitmap(32,16,crouch_L,16,16,BLACK);
    }

    if ((frameNumber%frame)==2){
        lcd.drawBitmap(32,16,roar_L,16,16,BLACK);
        lcd.drawBitmap(16,16,F_4_1,15,16,BLACK);
    }

    if ((frameNumber%frame)==3){
        lcd.drawBitmap(32,16,roar_L,16,16,BLACK);
        lcd.drawBitmap(16,16,F_4_2,15,16,BLACK);

    }

    if ((frameNumber%frame)==4){
        lcd.drawBitmap(32,16,roar_L,16,16,BLACK);
        lcd.drawBitmap(11,16,F_4_3,15,16,BLACK);

    }
    if ((frameNumber%frame)==5){
        lcd.drawBitmap(32,16,roar_L,16,16,BLACK);
        lcd.drawBitmap(6,16,F_4_2,15,16,BLACK);

    }

    if ((frameNumber%frame)==6){
        lcd.drawBitmap(32,16,roar_L,16,16,BLACK);

    }


    //lcd.display();
}

void A_magma_bomb(int frameNumber,unsigned char* crouch_L,unsigned char* roar_L,Adafruit_PCD8544 lcd) {

    const int frame=8;
    const int dist =32;

    if ((frameNumber%frame)==0){
        lcd.drawBitmap(32,16,crouch_L,16,16,BLACK);
    }

    if ((frameNumber%frame)==1){
        lcd.drawBitmap(32,16,crouch_L,16,16,BLACK);
    }

    if ((frameNumber%frame)==2){
        lcd.drawBitmap(32,16,roar_L,16,16,BLACK);
        lcd.drawBitmap(22,18,F_5_1,4,4,BLACK);
    }

    if ((frameNumber%frame)==3){
        lcd.drawBitmap(32,16,roar_L,16,16,BLACK);
        lcd.drawBitmap(16,16,F_5_2,7,7,BLACK);

    }

    if ((frameNumber%frame)==4){
        lcd.drawBitmap(32,16,roar_L,16,16,BLACK);
        lcd.drawBitmap(11,20,F_5_3,7,7,BLACK);

    }
    if ((frameNumber%frame)==5){
        lcd.drawBitmap(32,16,roar_L,16,16,BLACK);
        lcd.drawBitmap(6,16,F_5_4,15,16,BLACK);

    }

    if ((frameNumber%frame)==6){
        lcd.drawBitmap(32,16,roar_L,16,16,BLACK);
        lcd.drawBitmap(6,16,F_5_5,15,16,BLACK);

    }
    if ((frameNumber%frame)==7){
        lcd.drawBitmap(32,16,roar_L,16,16,BLACK);
        lcd.drawBitmap(6,16,F_5_6,15,16,BLACK);

    }

    //lcd.display();
}

void A_heat_laser(int frameNumber,unsigned char* crouch_L,unsigned char* roar_L,Adafruit_PCD8544 lcd) {

    const int frame=7;
    const int dist =32;

    if ((frameNumber%frame)==0){
        lcd.drawBitmap(32,16,crouch_L,16,16,BLACK);
    }

    if ((frameNumber%frame)==1){
        lcd.drawBitmap(32,16,crouch_L,16,16,BLACK);
    }

    if ((frameNumber%frame)==2){
        lcd.drawBitmap(32,16,roar_L,16,16,BLACK);
        lcd.drawCircle(28,24,2,BLACK);
        lcd.drawCircle(28,24,4,BLACK);

    }

    if ((frameNumber%frame)==3){
        lcd.drawBitmap(32,16,roar_L,16,16,BLACK);
        //lcd.fillRect(2,16,46,16,BLACK);
        lcd.drawCircle(28,24,3,BLACK);
        lcd.drawCircle(28,24,5,BLACK);
        lcd.drawBitmap(4,16,F_6_1,46,16,BLACK);

    }

    if ((frameNumber%frame)==4){
        lcd.drawBitmap(32,16,roar_L,16,16,BLACK);
        lcd.fillRect(2,16,46,16,BLACK);

    }
    if ((frameNumber%frame)==5){
        lcd.drawBitmap(32,16,roar_L,16,16,BLACK);
        lcd.drawBitmap(4,16,F_6_1,46,16,BLACK);
    }

    if ((frameNumber%frame)==6){
        lcd.drawBitmap(32,16,roar_L,16,16,BLACK);
    }

    //lcd.display();
}

void A_infinity_burn(int frameNumber,unsigned char* crouch_L,unsigned char* roar_L,Adafruit_PCD8544 lcd) {

    const int frame=8;
    const int dist =32;


    if ((frameNumber%frame)==0){
        lcd.drawBitmap(32,16,crouch_L,16,16,BLACK);
    }

    if ((frameNumber%frame)==1){
        lcd.drawBitmap(32,16,crouch_L,16,16,BLACK);
    }

    if ((frameNumber%frame)==2){
        lcd.drawBitmap(32,16,roar_L,16,16,BLACK);
        lcd.drawBitmap(22,16,F_1_1,8,16,BLACK);
    }

    if ((frameNumber%frame)==3){
        lcd.drawBitmap(32,16,roar_L,16,16,BLACK);
        lcd.drawBitmap(22,16,F_1_2,8,16,BLACK);
        lcd.drawBitmap(16,16,F_1_1,8,16,BLACK);
    }

    if ((frameNumber%frame)==4){
        lcd.drawBitmap(32,16,roar_L,16,16,BLACK);
        lcd.drawBitmap(22,16,F_8_1,8,16,BLACK);
        lcd.drawBitmap(15,16,F_1_2,8,16,BLACK);
        lcd.drawBitmap(8,16,F_1_1,8,16,BLACK);


    }
    if ((frameNumber%frame)==5){
        lcd.drawBitmap(32,16,roar_L,16,16,BLACK);
        lcd.drawBitmap(15,16,F_8_1,8,16,BLACK);
        lcd.drawBitmap(8,16,F_1_2,8,16,BLACK);

    }

    if ((frameNumber%frame)==6){
        lcd.drawBitmap(32,16,roar_L,16,16,BLACK);
        lcd.drawBitmap(8,16,F_8_1,8,16,BLACK);

    }

    if ((frameNumber%frame)==7){
        lcd.drawBitmap(32,16,roar_L,16,16,BLACK);

    }


    //lcd.display();
}

void A_meltdown(int frameNumber,unsigned char* crouch_L,unsigned char* roar_L,Adafruit_PCD8544 lcd) {

    const int frame=11;
    const int dist =32;


    if ((frameNumber%frame)==0){
        lcd.drawBitmap(32,16,crouch_L,16,16,BLACK);
    }

    if ((frameNumber%frame)==1){
        lcd.drawBitmap(32,16,crouch_L,16,16,BLACK);
    }

    if ((frameNumber%frame)==2){
        lcd.drawBitmap(32,16,roar_L,16,16,BLACK);
        lcd.drawBitmap(6,16,F_5_4,15,16,BLACK);
    }

    if ((frameNumber%frame)==3){
        lcd.drawBitmap(32,16,roar_L,16,16,BLACK);
        lcd.drawBitmap(6,16,F_5_5,15,16,BLACK);

    }

    if ((frameNumber%frame)==4){
        lcd.drawBitmap(32,16,roar_L,16,16,BLACK);
        lcd.drawBitmap(6,16,F_5_6,15,16,BLACK);
    }

    if ((frameNumber%frame)==5){
        lcd.drawBitmap(32,16,roar_L,16,16,BLACK);
        lcd.drawBitmap(8,16,F_8_1,8,16,BLACK);

    }

    if ((frameNumber%frame)==6){
        lcd.drawBitmap(32,16,roar_L,16,16,BLACK);
        lcd.drawBitmap(6,16,F_8_2,15,16,BLACK);

    }

    if ((frameNumber%frame)==7){
        lcd.drawBitmap(32,16,roar_L,16,16,BLACK);
        lcd.drawBitmap(6,16,F_8_3,15,16,BLACK);
    }

    if ((frameNumber%frame)==8){
        lcd.drawBitmap(32,16,roar_L,16,16,BLACK);
        lcd.drawBitmap(6,16,F_8_4,15,16,BLACK);
        lcd.drawBitmap(2,16,F_6_1,46,16,BLACK);
    }

    if ((frameNumber%frame)==9){
        lcd.drawBitmap(32,16,roar_L,16,16,BLACK);
        lcd.drawBitmap(6,16,F_8_4,15,16,BLACK);
        //lcd.drawBitmap(6,16,F_8_5,15,16,BLACK);
    }
    if ((frameNumber%frame)==10){
        lcd.drawBitmap(32,16,roar_L,16,16,BLACK);
        lcd.drawBitmap(6,16,F_8_5,15,16,BLACK);
        //lcd.drawBitmap(6,16,F_8_5,15,16,BLACK);
    }

    //lcd.display();
}
