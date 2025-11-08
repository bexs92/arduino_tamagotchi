 #ifndef _ATTACK_H
 #define _ATTACK_H

 #include "Arduino.h"
 #include <Adafruit_PCD8544.h>
 #include <sprites.h>


 /*
  Fire tower
  prominence beam
  spit fire
  red inferno
  magma bomb
  heat laser
  infinity burn
  meltdown

  */

 const int frame_len[8]={7,7,7,7,8,7,8,11};

 void A_fire_tower(int frameNumber,unsigned char* crouch_L,unsigned char* roar_L,Adafruit_PCD8544 lcd);

 void A_p_beam(int frameNumber,unsigned char* crouch_L,unsigned char* roar_L,Adafruit_PCD8544 lcd);

 void A_spit_fire(int frameNumber,unsigned char* crouch_L,unsigned char* roar_L,Adafruit_PCD8544 lcd);

 void A_red_inferno(int frameNumber,unsigned char* crouch_L,unsigned char* roar_L,Adafruit_PCD8544 lcd);

  void A_magma_bomb(int frameNumber,unsigned char* crouch_L,unsigned char* roar_L,Adafruit_PCD8544 lcd);

  void A_heat_laser(int frameNumber,unsigned char* crouch_L,unsigned char* roar_L,Adafruit_PCD8544 lcd);

void A_infinity_burn(int frameNumber,unsigned char* crouch_L,unsigned char* roar_L,Adafruit_PCD8544 lcd);

void A_meltdown(int frameNumber,unsigned char* crouch_L,unsigned char* roar_L,Adafruit_PCD8544 lcd);


 #endif
