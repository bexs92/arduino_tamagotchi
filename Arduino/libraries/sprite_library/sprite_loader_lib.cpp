
#include "sprite_loader_lib.h"
#include "Arduino.h"
#include <SdFat.h>
#include <vector>
#include <array>
#include <Adafruit_PCD8544.h>
#include <sprites.h>
#include <button.h>
#include "attack.h"
#include "clock.h"
#include "encyclopedia.h"
#include <tamagotchi.h>

sprite_sheet::sprite_sheet() {
    sprite_sheet_uo;
}

void sprite_sheet::add_sprite(const unsigned char* image, int size_x, int size_y) {
    //The numbers start at 0
    int list_size = sprite_sheet_uo.size();
    sprite new_sprite = {image,size_x,size_y};
    sprite_sheet_uo[list_size]=new_sprite;
}

sprite sprite_sheet::return_sprite(int number) {
    return sprite_sheet_uo[number];
};

//------------------------------------------------------

anim_sequence::anim_sequence(int seq_len)
: len(seq_len) {
    sprite_keyframes;
    transform_keyframes;
};

void anim_sequence::add_sprite_keyframe(int frame_number,int sprite_number) {
    sprite_keyframes[frame_number] = sprite_number;
};

void anim_sequence::add_transform_keyframe(int frame_number,int coord_x, int coord_y) {
    co_ordinate temp_coord = {coord_x,coord_y};
    transform_keyframes[frame_number] = temp_coord;
};

int anim_sequence::return_current_sprite(int frame_number,int total_seq_len) {

    int current_frame;

    if (playback_number>1){
        current_frame = frame_number%len;
    }

    else {
        current_frame = frame_number%total_seq_len;
    }

    int current_sprite;

    if (sprite_keyframes.count(current_frame)){
        sprite_index = current_frame;
        current_sprite = sprite_keyframes[current_frame];
    }
    else {
        current_sprite = sprite_keyframes[sprite_index];
    }

    return current_sprite;
};

co_ordinate anim_sequence::return_current_coord(int frame_number,int total_seq_len){

    int current_frame;

    if (playback_number>1){
        current_frame = frame_number%len;
    }

    else {
        current_frame = frame_number%total_seq_len;
    }

    co_ordinate current_transform;

    if (transform_keyframes.count(current_frame)){
        transform_index = current_frame;
        current_transform = transform_keyframes[current_frame];
    }
    else {
        current_transform = transform_keyframes[transform_index];
    }

    return current_transform;
};

void anim_sequence::make_loop(int number_of_loops) {
    playback_number=playback_number*number_of_loops;
};

int anim_sequence::get_seq_size() {
    return len;
};

//------------------------------------------------------
//------------------------------------------------------


compilation::compilation(int time_len)
: tl_len(time_len) {
    sequences;
}

void compilation::add_sequence(anim_sequence& added_seq) {

    int temp_number;

    if (sequences.size()>0){
        temp_number = last_frame_number;
        last_frame_number = (added_seq.get_seq_size()*added_seq.playback_number)+last_frame_number;
    }
    else {
        temp_number = 0;
        last_frame_number = added_seq.get_seq_size()*added_seq.playback_number;
    };

    sequences[temp_number]=&added_seq;
};

void compilation::create_one_off_frame(int sprite_number,int pos_x, int pos_y){

    anim_sequence solo_frame = anim_sequence(1);

    solo_frame.add_sprite_keyframe(0,sprite_number);
    solo_frame.add_transform_keyframe(0,pos_x,pos_y);

    Serial.println("Got here");

    add_sequence(solo_frame);

};

void compilation::play(int frame_number, Adafruit_PCD8544& lcd, sprite_sheet& ss) {

    int current_frame = frame_number%tl_len;

    anim_sequence* current_seq;

    if (sequences.count(current_frame)){
        seq_index = current_frame;
        current_seq = sequences[current_frame];
    }
    else {

        current_seq = sequences[seq_index];
    };

    co_ordinate current_transform = current_seq->return_current_coord(current_frame,tl_len);
    sprite current_sprite = ss.return_sprite(current_seq->return_current_sprite(current_frame,tl_len));

    lcd.drawBitmap(current_transform.pos_x,current_transform.pos_y,current_sprite.image,current_sprite.size_x,current_sprite.size_y,BLACK);

};


//------------------------------------------------------

uint8_t walk_L[SPRITE_SIZE];
uint8_t walk_R[SPRITE_SIZE];
uint8_t roar_L[SPRITE_SIZE];
uint8_t roar_R[SPRITE_SIZE];
uint8_t crouch_L[SPRITE_SIZE];
uint8_t crouch_R[SPRITE_SIZE];
uint8_t sleep_L[SPRITE_SIZE];
uint8_t sad_L[SPRITE_SIZE];
uint8_t sad_R[SPRITE_SIZE];
uint8_t happy_L[SPRITE_SIZE];

const char* training_list[6]{
    "HP",
    "MP",
    "OFF",
    "DEF",
    "SPD",
    "BRN"
};

SdFat sd;

int pooping_toggle=0;

bool loadSprite(const char* digimon,const char* action,const char* side,uint8_t* spriteBuffer) {

    char filename[32];
    snprintf(filename,sizeof(filename),"/%s/%s_%s.BIN",digimon,action,side);

    if (!sd.begin(D6)) {
        Serial.println("initialization failed!");
        while (1);
    }

    else{Serial.println(filename);}

    File spriteFile = sd.open(filename,FILE_READ);

    if (spriteFile) Serial.println("Managed to open file");

    if (!spriteFile) {
        Serial.println("Failed to open sprite file");
        Serial.println(filename);
        return false;
    }

    for  (int i = 0; i < SPRITE_SIZE && spriteFile.available(); i++) {
        spriteBuffer[i]=spriteFile.read();
    }

    spriteFile.close();

    return true;

}

void loadCharacter(const char* digimon) {

    loadSprite(digimon,"WALK","L",walk_L);
    loadSprite(digimon,"WALK","R",walk_R);
    loadSprite(digimon,"ROAR","L",roar_L);
    loadSprite(digimon,"ROAR","R",roar_R);
    loadSprite(digimon,"CROUCH","L",crouch_L);
    loadSprite(digimon,"CROUCH","R",crouch_R);
    loadSprite(digimon,"SLEEP","L",sleep_L);
    loadSprite(digimon,"SAD","L",sad_L);
    loadSprite(digimon,"SAD","R",sad_R);
    loadSprite(digimon,"HAPPY","L",happy_L);
    sd.end();
}

const unsigned char* training_bmp[6]={
    full_heart,
    mp_bmp,
    off_bmp,
    def_bmp,
    spd_bmp,
    brn_bmp
};

const unsigned char* menu_array[9] = {
    null_item,
    menu_stats,
    menu_food,
    menu_training,
    menu_battle,
    menu_poop,
    menu_light,
    menu_med,
    menu_alert
};

const unsigned char* need_sprite[5]= {sml_meat, poop2, z_bub, sweat, skull};

// sml_meat, poop2, z_bub, sweat, skull
const int needs_order[32][8]{
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {1,1,1,1,1,1,1,1},
    {0,1,0,1,0,1,0,1},
    {2,2,2,2,2,2,2,2},
    {0,2,0,2,0,2,0,2},
    {1,2,1,2,1,2,1,2},
    {0,1,2,0,1,2,0,1},
    {3,3,3,3,3,3,3,3},
    {0,3,0,3,0,3,0,3},
    {1,3,1,3,1,3,1,3},
    {0,1,3,0,1,3,0,1},
    {2,3,2,3,2,3,2,3},
    {0,2,3,0,2,3,0,2},
    {1,2,3,1,2,3,1,2},
    {0,1,2,3,0,1,2,3},
    {4,4,4,4,4,4,4,4},
    {0,4,0,4,0,4,0,4},
    {1,4,1,4,1,4,1,4},
    {0,1,4,0,1,4,0,1},
    {2,4,2,4,2,4,2,4},
    {0,2,4,0,2,4,0,2},
    {1,2,4,1,2,4,1,2},
    {0,1,2,4,0,1,2,4},
    {3,4,3,4,3,4,3,4},
    {0,3,4,0,3,4,0,3},
    {1,3,4,1,3,4,1,3},
    {0,1,3,4,0,1,3,4},
    {2,3,4,2,3,4,2,3},
    {0,2,3,4,0,2,3,4},
    {1,2,3,4,1,2,3,4},
    {0,1,2,3,4,0,1,2}
};

const int h_dist[34] = {
    16,14,10,10,14,14,10,6,6,6,6,6,6,6,6,10,14,16,20,24,24,20,20,24,28,28,28,28,28,28,28,28,24,20
};

const int stored_h_dist[16][2] = {{0,16},{1,14},{2,10},{4,14},{6,10},{7,6},{15,10},{16,14},{17,16},{18,20},{19,24},{21,20},{23,24},{24,28},{32,24},{33,20}};

const int menu_steps_H[9]={0,4,14,25,36,4,14,25,36};
const int menu_steps_V[9]={0,4,4,4,4,36,36,36,36};

const int poop_steps_H[8]={38,38,30,30,22,22,14,14};
const int poop_steps_V[8]={22,11,22,11,22,11,22,11};

const int minus_poop[8]={1,1,2,2,3,3,4,4};

unsigned long action_time=0;
int action_frame =0;

const unsigned char* disc_frames[3][3]={
    {crouch_L,sad_L,sad_L},
    {happy_L,roar_L,sleep_L},
    {sun,thinking,null_item}
};

const unsigned char* side_menu_sprites [4][2][2]={
    {{SOUND_OFF,SOUND_ON},{INVERT_SOUND_OFF,INVERT_SOUND_ON}},
    {{LIGHT_OFF,LIGHT_ON},{INVERT_LIGHT_OFF,INVERT_LIGHT_ON}},
    {{SAVE_BTTN,SAVE_BTTN},{INVERT_SAVE_BTTN,INVERT_SAVE_BTTN}},
    {{ART_BTTN,ART_BTTN},{INVERT_ART_BTTN,INVERT_ART_BTTN}}
};

const int selection_array[4][4]{
    {1,0,0,0},
    {0,1,0,0},
    {0,0,1,0},
    {0,0,0,1}
};

const int menu_locations[4][4]{
    {74,2,9,9},
    {74,13,9,9},
    {52,24,15,10},
    {68,24,15,10}
};

animation::animation(Adafruit_PCD8544& display)
: lcd(display) {

    meat_sprites;
    symbol_sprites;
    toilet_sprites;
};

void animation::make_sequences(){

    //-------------------------------------------------------------

    //idle animation set up

    char_sprites.add_sprite(walk_L,16,16);    //0
    char_sprites.add_sprite(walk_R,16,16);    //1
    char_sprites.add_sprite(roar_L,16,16);    //2
    char_sprites.add_sprite(roar_R,16,16);    //3
    char_sprites.add_sprite(crouch_L,16,16);  //4
    char_sprites.add_sprite(crouch_R,16,16);  //5
    char_sprites.add_sprite(sleep_L,16,16);   //6
    char_sprites.add_sprite(sad_L,16,16);     //7
    char_sprites.add_sprite(sad_R,16,16);     //8
    char_sprites.add_sprite(happy_L,16,16);   //9

    //symbol sprites

    symbol_sprites.add_sprite(null_item,11,10);  //0
    symbol_sprites.add_sprite(sun,11,10);        //1
    symbol_sprites.add_sprite(thinking,11,10);   //2


    idle_walk.make_loop(8);

    //it's quicker to use a for loop to add the transform keyframes to the idle loop
    for(int i=0; i<17; i++){
        idle_walk.add_transform_keyframe(stored_h_dist[i][0],stored_h_dist[i][1],15);
    };

    idle_walk.sprite_keyframes={{0,0},{2,4},{3,5},{4,1},{5,0},{6,4},{8,5},{9,4},{10,2},{11,4},{12,2},{13,4},{14,5},{16,1},{19,5},{20,4},{21,0},{22,1},{23,5},{25,4},{26,5},{27,3},{28,5},{29,3},{30,5},{31,4},{33,0}};

    idle_walk_comp.add_sequence(idle_walk);

    //-------------------------------------------------------------

    //Eating animation
    solo_sprite.add_sprite_keyframe(0,4);
    solo_sprite.add_transform_keyframe(0,16,16);

    om_nom.make_loop(3);
    om_nom.add_sprite_keyframe(0,4);
    om_nom.add_sprite_keyframe(1,2);
    om_nom.add_transform_keyframe(0,16,16);

    //om_nom_comp.create_one_off_frame(4,16,16);
    om_nom_comp.add_sequence(solo_sprite);
    om_nom_comp.add_sequence(om_nom);
    om_nom_comp.add_sequence(solo_sprite);

    meat_sprites.add_sprite(sml_meat,11,10);        //0
    meat_sprites.add_sprite(sml_meat_half,11,10);   //1
    meat_sprites.add_sprite(sml_meat_empty,11,10);  //2
    meat_sprites.add_sprite(menu_food,11,10);       //3
    meat_sprites.add_sprite(food_half,11,10);       //4
    meat_sprites.add_sprite(food_third,11,10);      //5
    meat_sprites.add_sprite(food_empty,11,10);      //6
    meat_sprites.add_sprite(null_item,11,10);       //7

    sml_meat_eat.sprite_keyframes ={{0,0},{2,1},{3,2},{4,7}};

    sml_meat_eat.add_transform_keyframe(0,4,16);
    sml_meat_eat.add_transform_keyframe(1,4,21);

    sml_meat_comp.add_sequence(sml_meat_eat);

    big_meat_eat.sprite_keyframes ={{0,3},{2,4},{3,5},{4,6},{5,7}};
    big_meat_eat.add_transform_keyframe(0,4,16);
    big_meat_eat.add_transform_keyframe(1,4,21);

    big_meat_comp.add_sequence(big_meat_eat);

    //-------------------------------------------------------------

    //happy anim_sequence

    happy_seq.make_loop(3);
    happy_seq.sprite_keyframes = {{0,0},{1,2}};
    happy_seq.add_transform_keyframe(0,16,16);

    sun_seq.make_loop(3);
    sun_seq.sprite_keyframes = {{0,10},{1,9}};
    happy_seq.add_transform_keyframe(0,32,12);

    happy_comp.add_sequence(happy_seq);
    sun_comp.add_sequence(sun_seq);

    //-------------------------------------------------------------

    //toilet animation

    toilet_sprites.add_sprite(crouch_L,16,16);         //0
    toilet_sprites.add_sprite(walk_L,16,16);           //1
    toilet_sprites.add_sprite(happy_L,16,16);          //2
    toilet_sprites.add_sprite(toilet_1,16,16);         //3
    toilet_sprites.add_sprite(toilet_2,16,16);         //4
    toilet_sprites.add_sprite(fart_1,11,10);           //5
    toilet_sprites.add_sprite(fart_2,11,10);           //6
    toilet_sprites.add_sprite(music_note_1,11,10);     //7
    toilet_sprites.add_sprite(music_note_2,11,10);     //8
    toilet_sprites.add_sprite(sun,11,10);              //9
    toilet_sprites.add_sprite(null_item,11,10);        //10

    toilet_digi.sprite_keyframes ={{0,0},{1,1},{2,0},{3,1},{4,10},{6,7},{7,8},{8,10}};
    toilet_digi.add_transform_keyframe(0,32,16);
    toilet_digi.add_transform_keyframe(1,31,16);
    toilet_digi.add_transform_keyframe(2,30,16);
    toilet_digi.add_transform_keyframe(6,4,12);

    toilet_seq.sprite_keyframes = {{0,3},{3,4},{4,3},{9,10}};
    toilet_seq.add_transform_keyframe(0,8,16);
    toilet_seq.add_transform_keyframe(1,12,16);
    toilet_seq.add_transform_keyframe(2,16,16);

    toilet_symbols.sprite_keyframes = {{0,10},{6,5},{7,6}};
    toilet_symbols.add_transform_keyframe(0,32,12);

    toilet_digi_comp.add_sequence(toilet_digi);
    toilet_digi_comp.add_sequence(happy_seq);

    toilet_comp.add_sequence(toilet_seq);

    toilet_symbol_comp.add_sequence(toilet_symbols);
    toilet_symbol_comp.add_sequence(sun_seq);

    // anim_sequence toilet_seq = anim_sequence(14);
    // compilation toilet_comp = compilation(14);

}

void animation::initialise(unsigned char* n_L,unsigned char* c_L,unsigned char* r_L,unsigned char* n_R,unsigned char* c_R,unsigned char* r_R) {


    orderArray[0]=n_L;
    orderArray[1]=n_L;
    orderArray[2]=c_L;
    orderArray[3]=c_R;
    orderArray[4]=n_R;
    orderArray[5]=n_L;
    orderArray[6]=c_L;
    orderArray[7]=c_L;
    orderArray[8]=c_R;
    orderArray[9]=c_L;
    orderArray[10]=r_L;
    orderArray[11]=c_L;
    orderArray[12]=r_L;
    orderArray[13]=c_L;
    orderArray[14]=c_R;
    orderArray[15]=c_R;
    orderArray[16]=n_R;

    //now reversing the order

    orderArray[17]=n_R;
    orderArray[18]=n_R;
    orderArray[19]=c_R;
    orderArray[20]=c_L;
    orderArray[21]=n_L;
    orderArray[22]=n_R;
    orderArray[23]=c_R;
    orderArray[24]=c_R;
    orderArray[25]=c_L;
    orderArray[26]=c_R;
    orderArray[27]=r_R;
    orderArray[28]=c_R;
    orderArray[29]=r_R;
    orderArray[30]=c_R;
    orderArray[31]=c_L;
    orderArray[32]=c_L;
    orderArray[33]=n_L;

}

void animation::retreiveFrame(int frame_number, unsigned long time_check,int need,int
                              poops,Tamagotchi data,Statemachine sm,info_node info,int game_H,int game_M){


    if(sm.get_in_menu()==1){
        draw_menu(frame_number,time_check,sm.get_action(),need,data,sm,info);
        if(sm.get_menu_count()>0){
            draw_side_menu(data.sound_status,data.light_status);
        }
    }

    else{

        if(need>0){
            need_anim(frame_number,need,poops,sm.get_menu_count());
        }

        else{

            if(pooping_toggle!=poops){
                if(poops!=0){
                    pooping_anim(frame_number,sm.get_menu_count(),poops,sm.get_in_menu());
                }
                else{
                    pooping_toggle=0;
                }
            }

            else {
                int horizontal_dist = h_dist[frame_number];

                if(poops>0){
                    horizontal_dist=horizontal_dist-((minus_poop[poops])*5);
                }

                //BEXS please note the poop indent will not be happening right now - maybe it can be an exra container?
                // OR maybe can just have a transform function in the comp?

                //idle_walk_comp.play(frame_number,lcd,char_sprites);
                comp_frame(idle_walk_comp,char_sprites,frame_number,poops,sm.get_menu_count());

                //frame(orderArray[frame_number],horizontal_dist,15,frame_number,poops,sm.get_menu_count());

            }

        }
        draw_side_menu(data.sound_status,data.light_status);
    }

    draw_clock(game_H,game_M,lcd);

    lcd.display();
}

void animation::comp_frame(compilation& comp,sprite_sheet ss,int frame_number,int poops,int menu_number) {
    lcd.clearDisplay();
    comp.play(frame_number,lcd,ss);
    lcd.drawRect(0,0,50,48,BLACK);

    lcd.drawBitmap(menu_steps_H[menu_number],menu_steps_V[menu_number],menu_array[menu_number],11,10,BLACK);

    if (poops>0){
        if (frame_number%2==0){
            for(int i=0; i<poops; i++){
                lcd.drawBitmap(poop_steps_H[i],poop_steps_V[i],poop1,11,10,BLACK);
            }
        }
        else{
            for(int i=0; i<poops; i++){
                lcd.drawBitmap(poop_steps_H[i],poop_steps_V[i],poop2,11,10,BLACK);
            }
        };

    };
};

void animation::frame(uint8_t* image,int xPos, int yPos,int frame_number,int poops,int menu_number) {

    lcd.clearDisplay();
    lcd.drawBitmap(xPos,yPos,image,16,16,BLACK);
    //idle_walk_comp.play(frame_number,lcd,char_sprites);
    lcd.drawRect(0,0,50,48,BLACK);

    lcd.drawBitmap(menu_steps_H[menu_number],menu_steps_V[menu_number],menu_array[menu_number],11,10,BLACK);

    if (poops>0){
        if (frame_number%2==0){
            for(int i=0; i<poops; i++){
                lcd.drawBitmap(poop_steps_H[i],poop_steps_V[i],poop1,11,10,BLACK);
            }
        }
        else{
            for(int i=0; i<poops; i++){
                lcd.drawBitmap(poop_steps_H[i],poop_steps_V[i],poop2,11,10,BLACK);
            }
        }

    }

 };

void animation::draw_menu(int frame_number,unsigned long time ,int action,int need,Tamagotchi data,Statemachine sm,info_node info){

    int menu_number = sm.get_menu_count();
    int page_number = sm.get_page_count();

    //CLearing the display

    lcd.clearDisplay();
    lcd.drawRect(0,0,50,48,BLACK);

    //highlighting the menu icon

    lcd.drawBitmap(menu_steps_H[menu_number],menu_steps_V[menu_number],menu_array[menu_number],11,10,BLACK);

    lcd.setCursor(4,16);

    if (menu_number==0){
        Serial.println("Middle menu button seleted");
        select_side_menu(data.sound_status,data.light_status,page_number);
    }

    if (menu_number==1){
        stat_page(page_number,data,info);
    }

    if (menu_number==2){
        if(page_number<2){
            food_page(page_number,frame_number,time,action,data);
        }
        else {
            nope_anim(frame_number);
        }
    }

    if (menu_number==3){
        if(action==1){
            if(page_number==0){
                hp_anim(sm.get_training(),page_number,data,sm);
            }
            if(page_number==1){
                mp_anim(frame_number,sm.get_training(),data,sm,time);
            }

            if(page_number==2){
                off_anim(frame_number,sm.get_time_store(),time,sm.get_training());
            }

            if(page_number==4){
                spd_anim(sm.get_training());
            }

        }
        else{
            training_page(page_number,data,sm);
        }
    }

    if (menu_number==4){
        Serial.println("Battle selected");
    }

    if (menu_number==5){

        if(page_number==1){
            clean_anim(frame_number,1);
        }
        else {
            toilet_anim(frame_number);
        }

    }

    if (menu_number==6){
        if(action==1){
            if(page_number==0){
                rest_anim(frame_number);
            }
            else{
                rest_anim(frame_number);
            }
        }
        else{
            light_page(page_number,data);
        }

    }

    if (menu_number==6){
        Serial.println("Medical selected");
    }

    if (menu_number==8){
        disc_page(page_number,frame_number,action,data);
    }
}

void animation::stat_page(int page_number,Tamagotchi data,info_node info){
    lcd.setTextColor(BLACK,WHITE);

    if (page_number==0) {
        char buffer_1[16];

        sprintf(buffer_1, "%s",info.get_name());

        lcd.setCursor(4,16);

        lcd.println(buffer_1); // Print the formatted string

        lcd.drawBitmap(4,26,info.get_type_bitmap(),11,10,BLACK);

        for (int i=0; i<3; i++){
            if(info.get_element_array()[i]!=6){
               lcd.drawBitmap((15+(i*10)),26,info.get_element_bitmap(info.get_element_array()[i]),11,10,BLACK);
            }
        }
    }

    if (page_number==1) {
        char buffer_3[30];
        char buffer_4[30];
        sprintf(buffer_3, "%d days",data.age);
        sprintf(buffer_4, "%d kg",data.weight);

        lcd.drawBitmap(2,14,age,11,10,BLACK);
        lcd.drawBitmap(2,24,scales,11,10,BLACK);

        lcd.setCursor(13,16);
        lcd.setTextWrap(false);
        lcd.println(buffer_3);

        lcd.setCursor(13,26);
        lcd.println(buffer_4);
    }

    if (page_number==2) {

        lcd.setCursor(4,16);
        lcd.println("Hunger:");

        for (int i=0; i<data.hunger; i++) {
            lcd.drawBitmap(4+(i*10),24,full_heart,11,10,BLACK);
        }

        for (int i=data.hunger; i<4; i++) {
            lcd.drawBitmap(4+(i*10),24,empty_heart,11,10,BLACK);
        }

    }

    if (page_number==3) {
        char buffer_3[30];
        char buffer_4[30];
        sprintf(buffer_3, "HP:%d",data.hp);
        sprintf(buffer_4, "MP:%d",data.mp);

        lcd.setCursor(4,16);
        lcd.println(buffer_3);

        lcd.setCursor(4,26);
        lcd.println(buffer_4);
    }

    if (page_number==4) {
        char buffer_3[30];
        char buffer_4[30];
        sprintf(buffer_3, "OFF:%d",data.off);
        sprintf(buffer_4, "DEF:%d",data.def);

        lcd.setCursor(4,16);
        lcd.println(buffer_3);

        lcd.setCursor(4,26);
        lcd.println(buffer_4);
    }

    if (page_number==5) {
        char buffer_3[30];
        char buffer_4[30];
        sprintf(buffer_3, "SPD:%d",data.spd);
        sprintf(buffer_4, "BRN:%d",data.brn);

        lcd.setCursor(4,16);
        lcd.println(buffer_3);

        lcd.setCursor(4,26);
        lcd.println(buffer_4);
    }

    if (page_number==6) {

        int transfer =1;

        lcd.setCursor(4,16);
        lcd.println("Happiness");

        int happy_diff= (data.happy)%10;


        if (happy_diff>4){
            transfer = ((data.happy-happy_diff)+10)/10;
        }
        else {
            transfer = (data.happy-happy_diff)/10;
        }

        lcd.drawRect(5,26,33,10,BLACK);

        Serial.println(transfer);

        for (int i=0; i<transfer; i++) {
            lcd.drawRect((7+(3*i)),28,2,6,BLACK);
        }

    }

    if (page_number==7) {

        int transfer =1;

        lcd.setCursor(4,16);
        lcd.println("Discipline");

        int disc_diff= (data.disc)%10;


        if (disc_diff>4){
            transfer = ((data.disc-disc_diff)+10)/10;
        }
        else {
            transfer = (data.disc-disc_diff)/10;
        }

        lcd.drawRect(5,26,33,10,BLACK);

        Serial.println(transfer);

        for (int i=0; i<transfer; i++) {
            lcd.drawRect((7+(3*i)),28,2,6,BLACK);
        }

    }
}

void animation::food_page(int page_number,int frameNumber,unsigned long time,int action,Tamagotchi data){


    if (page_number==0) {

        if(action==1) {
            eating_anim(frameNumber,time,page_number);
        }

        else {
            lcd.drawBitmap(32,14,menu_food,11,10,BLACK);

            lcd.setCursor(4,16);
            lcd.setTextColor(WHITE,BLACK);
            lcd.println("meat"); // Print the formatted string

            lcd.setCursor(4,26);
            lcd.setTextColor(BLACK,WHITE);
            lcd.println("sirloin");
        }

    }

    if (page_number==1) {

        if(action==1) {
             eating_anim(frameNumber,time,page_number);
        }

        else {
        lcd.drawBitmap(32,14,menu_food,11,10,WHITE);

        lcd.setCursor(4,16);
        lcd.setTextColor(BLACK,WHITE);
        lcd.println("meat"); // Print the formatted string

        lcd.setCursor(4,26);
        lcd.setTextColor(WHITE,BLACK);
        lcd.println("sirloin");
        }

    }

}

void animation::training_page(int page_number,Tamagotchi data,Statemachine sm){

    if(page_number<6){

        if(page_number%2==0){

            lcd.drawBitmap(4,14,training_bmp[page_number],11,10,BLACK);
            lcd.drawBitmap(4,24,training_bmp[page_number+1],11,10,BLACK);


            lcd.setCursor(16,16);
            lcd.setTextColor(WHITE,BLACK);
            lcd.println(training_list[page_number]); // Print the formatted string

            lcd.setCursor(16,26);
            lcd.setTextColor(BLACK,WHITE);
            lcd.println(training_list[page_number+1]);

        }

        else {

            lcd.drawBitmap(4,14,training_bmp[page_number-1],11,10,BLACK);
            lcd.drawBitmap(4,24,training_bmp[page_number],11,10,BLACK);

            lcd.setCursor(16,16);
            lcd.setTextColor(BLACK,WHITE);
            lcd.println(training_list[page_number-1]); // Print the formatted string

            lcd.setCursor(16,26);
            lcd.setTextColor(WHITE,BLACK);
            lcd.println(training_list[page_number]);

        }
    }

    else {
        int current_stat[6] = {data.hp,data.mp,data.off,data.def,data.spd,data.brn};

        lcd.setCursor(4,8);
        lcd.println(training_list[page_number-6]);

        lcd.setCursor(4,18);
        lcd.println(current_stat[page_number-6]-(sm.get_training()*5));

        lcd.setCursor(4,28);
        lcd.println("+");
        lcd.setCursor(8,28);
        lcd.println(sm.get_training()*5);

    }

}

void animation::light_page(int page_number, Tamagotchi data){


    if (page_number==0) {

        lcd.setCursor(4,16);
        lcd.setTextColor(WHITE,BLACK);
        lcd.println("REST"); // Print the formatted string

        lcd.setCursor(4,26);
        lcd.setTextColor(BLACK,WHITE);
        lcd.println("SLEEP");

    }

    if (page_number==1) {

        lcd.setCursor(4,16);
        lcd.setTextColor(BLACK,WHITE);
        lcd.println("REST"); // Print the formatted string

        lcd.setCursor(4,26);
        lcd.setTextColor(WHITE,BLACK);
        lcd.println("SLEEP");

    }

}

void animation::disc_page(int page_number,int frame_number,int action, Tamagotchi data){

    if (action==0) {
        lcd.drawBitmap(2,14,praise_bmp,11,10,BLACK);
        lcd.drawBitmap(2,24,scold_bmp,11,10,BLACK);


        if (page_number==0) {

            lcd.setCursor(14,16);
            lcd.setTextColor(WHITE,BLACK);
            lcd.println("Praise"); // Print the formatted string

            lcd.setCursor(15,26);
            lcd.setTextColor(BLACK,WHITE);
            lcd.println("Scold");

        }

        if (page_number==1) {

            lcd.setCursor(14,16);
            lcd.setTextColor(BLACK,WHITE);
            lcd.println("Praise"); // Print the formatted string

            lcd.setCursor(15,26);
            lcd.setTextColor(WHITE,BLACK);
            lcd.println("Scold");

        }

    }

    if(action==1){
        disc_anim(frame_number,page_number);
    }

}

void animation::eating_anim(int frameNumber,unsigned long time,int meat){

    lcd.clearDisplay();
    lcd.drawRect(0,0,50,48,BLACK);

    //---------------------------------------------------------------------------------------

    if (meat==0){
        sml_meat_comp.play(frameNumber,lcd,meat_sprites);
    }

    else {
        big_meat_comp.play(frameNumber,lcd,meat_sprites);
    };

    om_nom_comp.play(frameNumber,lcd,char_sprites);

}

void animation::toilet_anim(int frameNumber) {

    lcd.clearDisplay();
    lcd.drawRect(0,0,50,48,BLACK);

    toilet_digi_comp.play(frameNumber,lcd,toilet_sprites);
    toilet_comp.play(frameNumber,lcd,toilet_sprites);
    toilet_symbol_comp.play(frameNumber,lcd,toilet_sprites);

    pooping_toggle=0;
}

void animation::clean_anim(int frameNumber,int poops){
    int c_h_dist = 38;

    if(poops>0){
        c_h_dist=c_h_dist-((minus_poop[poops])*5);
    }

    if (frameNumber%4==0){
        lcd.drawBitmap(16,16,clear,6,17,BLACK);
    }

    if (frameNumber%4==1){
        lcd.drawBitmap(24,16,clear,6,17,BLACK);
    }

    if (frameNumber%4==2){
        lcd.drawBitmap(32,16,clear,6,17,BLACK);
    }

    if (frameNumber%4==3){
        lcd.drawBitmap(42,16,clear,6,17,BLACK);
         pooping_toggle=poops;
    }

}


void animation::disc_anim(int frameNumber,int page) {

    if (frameNumber%2==0){
        lcd.drawBitmap(16,16,disc_frames[0][page],16,16,BLACK);
    }

    else{
        lcd.drawBitmap(16,16,disc_frames[1][page],16,16,BLACK);
        lcd.drawBitmap(32,12,disc_frames[2][page],11,10,BLACK);

    }
}

int needs_frame = 0;

void animation::need_anim(int frameNumber,int need,int poops,int menu_number) {

    lcd.clearDisplay();
    lcd.drawRect(0,0,50,48,BLACK);

    int n_h_dist = 16;
    int bub_dist =32;

    if(poops>0){
        n_h_dist=n_h_dist-((minus_poop[poops])*5);
        bub_dist = bub_dist-((minus_poop[poops])*5);
    }

    if (frameNumber%2==0){
        frame(sad_L, n_h_dist, 16,frameNumber,poops,menu_number);
        lcd.drawBitmap(bub_dist,16,bubble_small,12,13,BLACK);
    }

    else{

        frame(roar_L, n_h_dist, 16,frameNumber,poops,menu_number);
        lcd.drawBitmap(bub_dist,16,bubble_big,12,13,BLACK);
        lcd.drawBitmap(bub_dist,15,need_sprite[needs_order[need][((frameNumber%16)-1)/2]],11,10,BLACK);

     }

    lcd.drawBitmap(menu_steps_H[menu_number],menu_steps_V[menu_number],menu_array[menu_number],11,10,BLACK);

}

void animation::pooping_anim(int frameNumber,int menu_number,int poops,int toggle) {

    int p_h_dist = 28;

    if(poops>0){
       p_h_dist=p_h_dist-((minus_poop[poops])*5);
    }

    if (frameNumber%6==0){
        frame(sleep_L, p_h_dist, 16,frameNumber,poops,menu_number);
    }

    if (frameNumber%6==1){
        frame(sleep_L, p_h_dist, 16,frameNumber,poops,menu_number);
    }

    if (frameNumber%6==2){
         frame(sleep_L, p_h_dist, 16,frameNumber,poops,menu_number);
    }

    if (frameNumber%6==3){
        frame(roar_L, p_h_dist, 16,frameNumber,poops,menu_number);
    }
    if (frameNumber%6==4){
        frame(roar_L, p_h_dist, 16,frameNumber,poops,menu_number);
    }

    if (frameNumber%6==5){
        frame(roar_L, p_h_dist, 16,frameNumber,poops,menu_number);
        pooping_toggle=poops;
    }

}

void animation::nope_anim(int frameNumber) {

    Serial.println("checking");

    if (frameNumber%2==0){
        lcd.drawBitmap(16,16,sad_L,16,16,BLACK);
    }

    else{
        lcd.drawBitmap(16,16,sad_R,16,16,BLACK);
    }

}

void animation::hp_anim(int frameNumber,int page_number,Tamagotchi data,Statemachine sm) {


        const int blob = 12;

        if (frameNumber%blob==0){
            lcd.drawBitmap(32,16,crouch_L,16,16,BLACK);
            lcd.drawBitmap(12,16,boulder,16,16,BLACK);
        }

        if (frameNumber%blob==1){
            lcd.drawBitmap(30,16,walk_L,16,16,BLACK);
            lcd.drawBitmap(12,16,boulder,16,16,BLACK);
        }

        if (frameNumber%blob==2){
            lcd.drawBitmap(28,16,crouch_L,16,16,BLACK);
            lcd.drawBitmap(12,16,boulder,16,16,BLACK);
        }

        if (frameNumber%blob==3){
            lcd.drawBitmap(26,16,walk_L,16,16,BLACK);
            lcd.drawBitmap(12,16,boulder,16,16,BLACK);
        }
        //after here is pushing

        if (frameNumber%blob==4){
            lcd.drawBitmap(24,16,crouch_L,16,16,BLACK);
            lcd.drawBitmap(10,16,boulder,16,16,BLACK);
            lcd.drawBitmap(4,16,cloud,9,16,BLACK);
        }

        if (frameNumber%blob==5){
            lcd.drawBitmap(24,16,walk_L,16,16,BLACK);
            lcd.drawBitmap(11,16,boulder,16,16,BLACK);
        }

        if (frameNumber%blob==6){
            lcd.drawBitmap(24,16,crouch_L,16,16,BLACK);
            lcd.drawBitmap(10,16,boulder,16,16,BLACK);
            lcd.drawBitmap(4,16,cloud,9,16,BLACK);
        }

        if (frameNumber%blob==7){
            lcd.drawBitmap(24,16,walk_L,16,16,BLACK);
            lcd.drawBitmap(11,16,boulder,16,16,BLACK);
        }

        if (frameNumber%blob==8){
            lcd.drawBitmap(24,16,roar_L,16,16,BLACK);
            lcd.drawBitmap(9,12,boulder,16,16,BLACK);
            lcd.drawBitmap(9,16,b_shadow,16,16,BLACK);
        }

        if (frameNumber%blob==9){
            lcd.drawBitmap(24,16,roar_L,16,16,BLACK);
            lcd.drawBitmap(6,8,boulder,16,16,BLACK);
            lcd.drawBitmap(6,16,b_shadow,16,16,BLACK);
        }

        if (frameNumber%blob==10){
            lcd.drawBitmap(24,16,roar_L,16,16,BLACK);
            lcd.drawBitmap(4,16,boulder,16,16,BLACK);
            lcd.drawBitmap(14,16,r_cloud,9,16,BLACK);
        }

        if (frameNumber%blob==11){
            lcd.drawBitmap(24,16,walk_L,16,16,BLACK);
            lcd.drawBitmap(4,16,boulder,16,16,BLACK);
        }


}

int last_mp=0;
unsigned long mp_time=0;

void animation::mp_anim(int frameNumber,int buttonPush,Tamagotchi data,Statemachine sm,unsigned long time) {

    if(frameNumber%2==0){
        lcd.drawBitmap(8,13,waterfall_3,30,19,BLACK);
    }

    else {
        lcd.drawBitmap(8,13,waterfall_4,30,19,BLACK);
    }

    if (last_mp!=buttonPush){
        last_mp=buttonPush;
        mp_time = time;

    }
    else {
        if (time-mp_time<300){
            lcd.drawBitmap(16,16,roar_L,16,16,BLACK);
        }
        else {
            lcd.drawBitmap(16,16,sleep_L,16,16,BLACK);
        }

    }

}

void animation::spd_anim(int frameNumber) {

    if (frameNumber%2==0){
        lcd.drawBitmap((32-3*(frameNumber%10)),16,crouch_L,16,16,BLACK);
    }

    else{
        lcd.drawBitmap((32-3*(frameNumber%10)),16,walk_L,16,16,BLACK);
    }

     lcd.drawBitmap(4,28,finish_line,16,7,BLACK);

}

void animation::off_anim(int frameNumber,unsigned long charge_time,unsigned long time,int training_count) {

    //BEXS this needs to be adjusted to the different frame lengths for different attacks

    //A_fire_tower(frameNumber,crouch_L,roar_L,lcd);
    //A_p_beam(frameNumber,crouch_L,roar_L,lcd);
    //A_spit_fire(frameNumber,crouch_L,roar_L,lcd);
    //A_red_inferno(frameNumber,crouch_L,roar_L,lcd);
    //A_magma_bomb(frameNumber,crouch_L,roar_L,lcd);
    //A_heat_laser(frameNumber,crouch_L,roar_L,lcd);
    //A_meltdown(frameNumber,crouch_L,roar_L,lcd);

    if(time-charge_time<1500){
        if(training_count==0){
            lcd.drawBitmap(32,16,crouch_L,16,16,BLACK);
            lcd.drawBitmap(4,16,training_bag_1,16,16,BLACK);
            lcd.drawRect(5,26,33,10,BLACK);

            int percent=round(((((time-charge_time)*100)/1500))/10);


            for (int i=0; i<percent+1; i++) {
                lcd.drawRect((7+(3*i)),28,2,6,BLACK);
            }

        }
        else {
            lcd.drawBitmap(32,16,crouch_L,16,16,BLACK);
            lcd.drawRect(5,26,33,10,BLACK);
            lcd.drawBitmap(4,16,training_bag_1,16,16,BLACK);

            for (int i=0; i<training_count; i++) {
                lcd.drawRect((7+(3*i)),28,2,6,BLACK);
            }
        }

    }
    else {
        A_meltdown(frameNumber,crouch_L,roar_L,lcd);

        if (frameNumber%11==8){
            lcd.drawBitmap(4,16,training_bag_2,16,16,BLACK);
        }

        if (frameNumber%11==9){
            lcd.drawBitmap(4,16,training_bag_3,16,16,BLACK);
        }

        if (frameNumber%11==10){
            if(training_count>8){
                lcd.drawBitmap(4,16,training_bag_4,16,16,BLACK);
            }
            else {
                lcd.drawBitmap(4,16,training_bag_1,16,16,BLACK);
            }
        }
        else{
            if(training_count>8){
                lcd.drawBitmap(4,16,training_bag_4,16,16,BLACK);
            }
            else {
                lcd.drawBitmap(4,16,training_bag_1,16,16,BLACK);
            }
        }
    }

    //lcd.display();

}

//---------------------------------------------------------------------------------------------

void animation::rest_anim(int frameNumber) {

    lcd.fillRect(2,16,46,16,BLACK);

    if (frameNumber%2==0){
        lcd.drawBitmap(16,16,sleep_z_1,11,10,WHITE);
    }

    else{
        lcd.drawBitmap(16,16,sleep_z_2,11,10,WHITE);
    }

}


void animation::draw_side_menu(int sound_status, int light_status){

    const unsigned char* selected_sprites[4]={
        side_menu_sprites[0][0][sound_status],side_menu_sprites[1][0][light_status],SAVE_BTTN,ART_BTTN
    };

    for (int i=0; i<4; i++) {
        lcd.drawBitmap(menu_locations[i][0],menu_locations[i][1],selected_sprites[i],menu_locations[i][2],menu_locations[i][3],BLACK);
    }

}

void animation::select_side_menu(int sound_status, int light_status,int page_number){

    const unsigned char* selected_sprites[4]={
        side_menu_sprites[0][selection_array[page_number][0]][sound_status],
        side_menu_sprites[1][selection_array[page_number][1]][light_status],
        side_menu_sprites[2][selection_array[page_number][2]][0],
        side_menu_sprites[3][selection_array[page_number][3]][0]
    };

    for (int i=0; i<4; i++) {
        lcd.drawBitmap(menu_locations[i][0],
                       menu_locations[i][1],
                       selected_sprites[i],
                       menu_locations[i][2],
                       menu_locations[i][3],
                       BLACK);
    }


}



