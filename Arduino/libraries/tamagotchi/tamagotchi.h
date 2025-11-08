#ifndef _TAMAGOTCHI_H
#define _TAMAGOTCHI_H

#include "Arduino.h"

// struct Button {
//
//     int pin;
//     int bttn;
//     int toggle;
//     unsigned long last_time;
//     unsigned long diff;
// };

class Tamagotchi{

public:

    Tamagotchi();
    void set_last_hunger(unsigned long value);
    unsigned long get_last_hunger();
    unsigned long generate_next(unsigned long old_time,int min, int max);
    void gen_next_hunger(unsigned long old_time);
    unsigned long get_last_hunger_cm();
    unsigned long get_next_poop();
    unsigned long get_poop_cm();
    void set_infinite_poop(unsigned long old_time);
    void gen_disc_range(unsigned long old_time);
    unsigned long get_disc_range();
    void set_disc_range(unsigned long value);
    unsigned long get_overfeed();
    void set_overfeed(unsigned long value);
    void gen_overfeed(unsigned long time);
    unsigned long minute(unsigned long time);
    unsigned long second(unsigned long time);

    // void check(unsigned long time);
    // void set_menu_count(int entered_num);
    // void pin_mode();
    // void set_up_read();
    // int get_menu_count();
    // void set_page_count(int entered_num);
    // int get_page_count();
    // int get_in_menu();
    // void set_in_menu(int value);
    // int get_action();
    // void set_action(int value);

private:

    unsigned long hunger_interval;
    unsigned long hunger_range;
    unsigned long last_hunger;
    unsigned long cm_hunger_interval;
    unsigned long last_hunger_cm;
    unsigned long poop_interval;
    unsigned long poop_range;
    unsigned long next_poop;
    unsigned long cm_poop_interval;
    unsigned long disc_range;
    unsigned long overfeed;


};






#endif
