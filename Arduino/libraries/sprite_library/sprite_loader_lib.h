//This library contains tools and variables related to retreiving sprites

#ifndef _SPRITE_LOADER_LIB_H
#define _SPRITE_LOADER_LIB_H

#include "Arduino.h"
#include <SdFat.h>
#include <vector>
#include <array>
#include <unordered_map>
#include <Adafruit_PCD8544.h>
#include <sprites.h>
#include <button.h>
#include <attack.h>
#include <clock.h>
#include <encyclopedia.h>
#include "tamagotchi.h"

#define SPRITE_SIZE 32

//----------------------------------------------------------------------

struct sprite {
    const unsigned char* image;
    int size_x;
    int size_y;
};

struct co_ordinate {
    int pos_x;
    int pos_y;
};

class sprite_sheet {
    //stores images in a map
public:
    std::unordered_map<int,sprite> sprite_sheet_uo;
    sprite_sheet();
    void add_sprite(const unsigned char* image,int size_x, int size_y);
    sprite return_sprite(int number);
private:
};

//----------------------------------------------------------------------

class anim_sequence {

public:
    int transform_index = 0;
    int sprite_index = 0;
    int playback_number = 1;
    std::unordered_map<int,int> sprite_keyframes;
    std::unordered_map<int,co_ordinate> transform_keyframes;
    anim_sequence(int seq_len);
    void add_sprite_keyframe(int frame_number,int sprite_number);
    void add_transform_keyframe(int frame_number,int coord_x, int coord_y);
    int return_current_sprite(int frame_number,int total_seq_len);
    co_ordinate return_current_coord(int frame_number,int total_seq_len);
    void make_loop(int number_of_loops);
    int get_seq_size();

private:
    int len;
};

//----------------------------------------------------------------------



class compilation {
public:
    int seq_index=0;
    int last_frame_number = 0;
    std::unordered_map<int,anim_sequence*> sequences;

    compilation(int time_len);
    void add_sequence(anim_sequence& added_seq);
    void create_one_off_frame(int sprite_number,int pos_x, int pos_y);
    void play(int frame_number, Adafruit_PCD8544& lcd, sprite_sheet& ss);

    private:
    int tl_len;
};


//----------------------------------------------------------------------

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

        sprite_sheet char_sprites = sprite_sheet();
        sprite_sheet symbol_sprites = sprite_sheet();
        //-----------------------------------------------

        anim_sequence idle_walk = anim_sequence(34);
        compilation idle_walk_comp = compilation(34);
        //-----------------------------------------------


        sprite_sheet meat_sprites = sprite_sheet();

        anim_sequence solo_sprite = anim_sequence(1);


        anim_sequence om_nom = anim_sequence(2);
        compilation om_nom_comp = compilation(7);

        anim_sequence sml_meat_eat = anim_sequence(5);
        anim_sequence big_meat_eat = anim_sequence(7);

        compilation sml_meat_comp = compilation(5);
        compilation big_meat_comp = compilation(7);

        //-----------------------------------------------

        anim_sequence happy_seq = anim_sequence(2);
        anim_sequence sun_seq = anim_sequence(2);

        compilation happy_comp = compilation(6);
        compilation sun_comp = compilation(6);

        //-----------------------------------------------

        sprite_sheet toilet_sprites = sprite_sheet();
        anim_sequence toilet_digi= anim_sequence(8);
        anim_sequence toilet_seq= anim_sequence(14);
        anim_sequence toilet_symbols= anim_sequence(8);

        compilation toilet_digi_comp = compilation(14);
        compilation toilet_comp = compilation(14);
        compilation toilet_symbol_comp = compilation(14);

        //-----------------------------------------------

        animation(Adafruit_PCD8544& display);
        void make_sequences();
        void initialise(unsigned char* n_L,unsigned char* c_L,unsigned char* r_L,unsigned char* n_R,unsigned char* c_R,unsigned char* r_R);
        void retreiveFrame(int frameNo, unsigned long timeCheck,int need,int poops,Tamagotchi data,Statemachine sm,info_node info,int game_H,int game_M);
        void comp_frame(compilation& comp,sprite_sheet ss,int frame_number,int poops,int menu_number);
        void frame(uint8_t* image,int xPos, int yPos,int frame_number,int poops,int menu_number);
        void draw_menu(int frame_number,unsigned long time,int action,int need,Tamagotchi data,Statemachine sm,info_node info);
        void stat_page(int frame_number,int page_number,Tamagotchi data,info_node info);
        void food_page(int page_number,int frameNumber,unsigned long time,int action,Tamagotchi data);
        void training_page(int page_number, Tamagotchi data,Statemachine sm);
        void light_page(int page_number,Tamagotchi data);
        void disc_page(int page_number,int frame_number, int action,Tamagotchi data);
        void eating_anim(int frameNumber,unsigned long time,int meat);
        void toilet_anim(int frameNumber);
        void disc_anim(int frameNumber,int page);
        void need_anim(int frameNumber,int need,int poops,int menu_number);
        void clean_anim(int frameNumber,int poops);
        void pooping_anim(int frameNumber,int menu_number,int poops,int toggle);
        void nope_anim(int frameNumber);
        void hp_anim(int frameNumber,int page_number,Tamagotchi data, Statemachine sm);
        void mp_anim(int frameNumber,int buttonPush,Tamagotchi data, Statemachine sm,unsigned long time);
        void spd_anim(int frameNumber);
        void def_anim(int frameNumber);
        void off_anim(int frameNumber,unsigned long charge_time,unsigned long time,int training_count);
        void brn_anim(int frameNumber,unsigned long charge_time,unsigned long time,int training_count);
        void rest_anim(int frameNumber);
        void draw_side_menu(int sound_status, int light_status);
        void select_side_menu(int sound_status, int light_status,int page_number);
        void display_art();



    private:
        unsigned char* orderArray[34];
        Adafruit_PCD8544& lcd;

};

#endif


