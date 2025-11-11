//This library contains tools and variables related to retreiving sprites

#ifndef _SPRITE_LOADER_LIB_H
#define _SPRITE_LOADER_LIB_H

#include "Arduino.h"
#include <SdFat.h>
#include <Adafruit_PCD8544.h>
#include <sprites.h>
#include <button.h>
#include <attack.h>
#include <clock.h>
#include <encyclopedia.h>
#include "tamagotchi.h"

#define SPRITE_SIZE 32

extern uint8_t walk_L[SPRITE_SIZE];
extern uint8_t walk_R[SPRITE_SIZE];
extern uint8_t roar_L[SPRITE_SIZE];
extern uint8_t roar_R[SPRITE_SIZE];
extern uint8_t crouch_L[SPRITE_SIZE];
extern uint8_t crouch_R[SPRITE_SIZE];
extern uint8_t sleep_L[SPRITE_SIZE];
extern uint8_t sad_L[SPRITE_SIZE];
extern uint8_t sad_R[SPRITE_SIZE];
extern uint8_t happy_L[SPRITE_SIZE];

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

 class animation{
     public:
        animation();
        void initialise(unsigned char* n_L,unsigned char* c_L,unsigned char* r_L,unsigned char* n_R,unsigned char* c_R,unsigned char* r_R);
        void retreiveFrame(int frameNo, unsigned long timeCheck,int need,int poops,Adafruit_PCD8544 lcd,Tamagotchi data,Statemachine sm,info_node info,int game_H,int game_M);
        void frame(uint8_t* image,int xPos, int yPos,int frame_number,int poops,int menu_number,Adafruit_PCD8544 lcd);
        void draw_menu(int frame_number,unsigned long time,int action,int need,Adafruit_PCD8544 lcd,Tamagotchi data,Statemachine sm,info_node info);
        void stat_page(int page_number, Adafruit_PCD8544 lcd,Tamagotchi data,info_node info);
        void food_page(int page_number,int frameNumber,unsigned long time,int action,Adafruit_PCD8544 lcd,Tamagotchi data);
        void training_page(int page_number, Adafruit_PCD8544 lcd,Tamagotchi data,Statemachine sm);
        void light_page(int page_number, Adafruit_PCD8544 lcd,Tamagotchi data);
        void disc_page(int page_number,int frame_number, int action,Adafruit_PCD8544 lcd,Tamagotchi data);
        void eating_anim(int frameNumber,unsigned long time,Adafruit_PCD8544 lcd,int meat);
        void toilet_anim(int frameNumber,Adafruit_PCD8544 lcd);
        void disc_anim(int frameNumber,Adafruit_PCD8544 lcd,int page);
        void need_anim(int frameNumber,int need,int poops,int menu_number,Adafruit_PCD8544 lcd);
        void clean_anim(int frameNumber,int poops,Adafruit_PCD8544 lcd);
        void pooping_anim(int frameNumber,int menu_number,int poops,int toggle,Adafruit_PCD8544 lcd);
        void nope_anim(int frameNumber,Adafruit_PCD8544 lcd);
        void hp_anim(int frameNumber,int page_number,Adafruit_PCD8544 lcd,Tamagotchi data, Statemachine sm);
        void mp_anim(int frameNumber,int buttonPush,Adafruit_PCD8544 lcd,Tamagotchi data, Statemachine sm,unsigned long time);
        void spd_anim(int frameNumber,Adafruit_PCD8544 lcd);
        void off_anim(int frameNumber,unsigned long charge_time,unsigned long time,int training_count,Adafruit_PCD8544 lcd);
        void rest_anim(int frameNumber,Adafruit_PCD8544 lcd);

    private:
        unsigned char* orderArray[34];


};

#endif


