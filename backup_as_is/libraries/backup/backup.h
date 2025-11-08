//This library contains tools and variables related to retreiving sprites

#ifndef _SPRITE_LOADER_LIB_H
#define _SPRITE_LOADER_LIB_H

#include "Arduino.h"
#include <SD.h>
#include <Adafruit_PCD8544.h>

#define SPRITE_SIZE 32

extern uint8_t walk_L[SPRITE_SIZE];
extern uint8_t walk_R[SPRITE_SIZE];
extern uint8_t roar_L[SPRITE_SIZE];
extern uint8_t roar_R[SPRITE_SIZE];
extern uint8_t crouch_L[SPRITE_SIZE];
extern uint8_t crouch_R[SPRITE_SIZE];

bool loadSprite(const char* digimon,const char* action,const char* side,uint8_t* spriteBuffer);

void loadCharacter(const char* digimon);

extern const unsigned char empty_heart [] PROGMEM;
extern const unsigned char full_heart [] PROGMEM;
extern const unsigned char menu_stats [] PROGMEM;
extern const unsigned char menu_food [] PROGMEM;
extern const unsigned char menu_training [] PROGMEM;
extern const unsigned char menu_battle [] PROGMEM;
extern const unsigned char menu_poop [] PROGMEM;
extern const unsigned char menu_light [] PROGMEM;
extern const unsigned char menu_med [] PROGMEM;
extern const unsigned char menu_alert [] PROGMEM;

//const int menu_array

class animation{
    public:
        animation();
        void initialise(unsigned char* n_L,unsigned char* c_L,unsigned char* r_L,unsigned char* n_R,unsigned char* c_R,unsigned char* r_R);
        void retreiveFrame(int frameNo, int timeCheck,int toggle,Adafruit_PCD8544 lcd);
        void frame(uint8_t* image,int xPos, int yPos,int timeCheck,int toggle,Adafruit_PCD8544 lcd);

}


#endif


