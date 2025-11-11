#ifndef _TAMAGOTCHI_H
#define _TAMAGOTCHI_H

#include "Arduino.h"
#include <SdFat.h>

struct save_data {
    int species;
    int age;
    int weight;
    int hunger;
    int hp;
    int mp;
    int off;
    int def;
    int spd;
    int brn;
    int happy;
    int disc;
    int tired;
    int cm; /*cm short for care mistakes */
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


class Tamagotchi{

public:

    Tamagotchi();
    void initialise(int species_value);
    save_data create_save();
    void save_to_card(save_data& save);
    void load_from_card(save_data& save);
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

    int species;
    int age;
    int weight;
    int hunger;
    int hp;
    int mp;
    int off;
    int def;
    int spd;
    int brn;
    int happy;
    int disc;
    int tired;
    int cm; /*cm short for care mistakes */

    save_data save_file;
    File o_file;

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
