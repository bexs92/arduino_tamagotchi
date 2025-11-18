#include "tamagotchi.h"
#include "Arduino.h"
#include <SdFat.h>



SdFat sd_reader;

Tamagotchi::Tamagotchi(){
    species;
    age;
    weight;
    hunger;
    hp;
    mp;
    off;
    def;
    spd;
    brn;
    happy;
    disc;
    tired;
    cm; /*cm short for care mistakes */
    sound_status;
    light_status;
    hunger_interval;
    hunger_range;
    last_hunger;
    cm_hunger_interval;
    last_hunger_cm;
    poop_interval;
    poop_range;
    next_poop;
    cm_poop_interval;
    overfeed;
    disc_range;
    save_file;
    o_file;
    w_file;
}

void Tamagotchi::transfer(save_data transfer){
    species= transfer.species;
    age= transfer.age;
    weight= transfer.weight;
    hunger=transfer.hunger;
    hp=transfer.hp;
    mp=transfer.mp;
    off=transfer.off;
    def=transfer.def;
    spd=transfer.spd;
    brn=transfer.brn;
    happy=transfer.happy;
    disc=transfer.disc;
    tired=transfer.tired;
    cm=transfer.cm;
    sound_status=transfer.sound_status;
    light_status=transfer.light_status;
    hunger_interval=minute(2);
    hunger_range=second(30);
    last_hunger=minute(1);
    cm_hunger_interval = minute(1);
    last_hunger_cm=last_hunger+cm_hunger_interval;
    poop_interval=second(30);
    poop_range=second(20);
    next_poop=minute(12);
    cm_poop_interval =second(30);
    overfeed=0;
    disc_range=0;
}


void Tamagotchi::initialise(int species_value){

    species=species_value;
    age=4;
    weight=20;
    hunger=4;
    hp=1009;
    mp=2060;
    off=132;
    def=100;
    spd=102;
    brn=100;
    happy=52;
    disc=88;
    tired=80;
    cm=0;
    sound_status=1;
    light_status=1;
    hunger_interval=minute(2);
    hunger_range=second(30);
    last_hunger=minute(1);
    cm_hunger_interval = minute(1);
    last_hunger_cm=last_hunger+cm_hunger_interval;
    poop_interval=second(30);
    poop_range=second(20);
    next_poop=minute(12);
    cm_poop_interval =second(30);
    overfeed=0;
    disc_range=0;
}

save_data Tamagotchi::create_save(){
    save_file = (save_data) {
        species,
        age,
        weight,
        hunger,
        hp,
        mp,
        off,
        def,
        spd,
        brn,
        happy,
        disc,
        tired,
        cm,
        sound_status,
        light_status,
        // hunger_interval,
        // hunger_range,
        // last_hunger,
        // cm_hunger_interval,
        // last_hunger_cm,
        // poop_interval,
        // poop_range,
        // next_poop,
        // cm_poop_interval,
        // overfeed,
        // disc_range
    };

    return save_file;
}

void Tamagotchi::save_to_card(save_data& save){

    if (!sd_reader.begin(D6)) {
        Serial.println("initialization failed!");
        while (1);
    }

    sd_reader.remove("tama.dat");

    w_file = sd_reader.open("tama.dat", FILE_WRITE);

    //sd_reader.remove("tama.dat");

    if (w_file) {
        //sd_reader.remove("tama.dat");
        w_file.write((uint8_t*)&save,sizeof(save_data));
        w_file.flush();
        w_file.close();
        Serial.println("got here");
        Serial.println("saving file");
        delay(300);
    }
    else {
        Serial.println("failed to save");
    }
    sd_reader.end();
}

void Tamagotchi::load_from_card(save_data& save){
    Serial.println("loading file");

    if (!sd_reader.begin(D6)) {
        Serial.println("initialization failed!");
        while (1);
    }

    o_file = sd_reader.open("tama.dat", FILE_READ);
    if (o_file) {
        o_file.read((uint8_t*)&save, sizeof(save_data));
        Serial.println("loading file");




        // species=                save.species;
        // age=                    save.age;
        // weight=                 save.weight;
        // hunger=                 save.hunger;
        // hp=                     save.hp;
        // mp=                     save.mp;
        // off=                    save.off;
        // def=                    save.def;
        // spd=                    save.spd;
        // brn=                    save.brn;
        // happy=                  save.happy;
        // disc=                   save.disc;
        // tired=                  save.tired;
        // cm=                     save.cm;
        // sound_status=           save.sound_status;
        // light_status=           save.light_status;
        // // hunger_interval=        save.hunger_interval;
        // // hunger_range=           save.hunger_range;
        // // last_hunger=            save.last_hunger;
        // // cm_hunger_interval=     save.cm_hunger_interval;
        // // last_hunger_cm=         save.last_hunger_cm;
        // // poop_interval=          save.poop_interval;
        // // poop_range=             save.poop_range;
        // // next_poop=              save.next_poop;
        // // cm_poop_interval=       save.cm_poop_interval;
        // // overfeed=               save.overfeed;
        // // disc_range=             save.disc_range;
        // hunger_interval=minute(2);
        // hunger_range=second(30);
        // last_hunger=minute(1);
        // cm_hunger_interval = minute(1);
        // last_hunger_cm=last_hunger+cm_hunger_interval;
        // poop_interval=second(30);
        // poop_range=second(20);
        // next_poop=minute(12);
        // cm_poop_interval =second(30);
        // overfeed=0;
        // disc_range=0;

        o_file.close();
    }
    else {
        Serial.println("failed to load, initialising a default digimon");
        initialise(14);
        //initialise(67);
        //o_file.close();
    }
    sd_reader.end();

}

void Tamagotchi::delete_file(){
    if (!sd_reader.begin(D6)) {
        Serial.println("initialization failed!");
        while (1);
    }

    sd_reader.remove("tama.dat");
    sd_reader.end();
}

void Tamagotchi::set_last_hunger(unsigned long value){

    last_hunger = value;
}

unsigned long Tamagotchi::get_last_hunger(){

    return last_hunger;
}

unsigned long Tamagotchi::generate_next(unsigned long old_time,int min, int max){
    unsigned long next = (random(min,max))+old_time;
    return next;
}

void Tamagotchi::gen_next_hunger(unsigned long old_time){
    int min = hunger_interval-hunger_range;
    int max = hunger_interval+hunger_range;
    set_last_hunger(generate_next(old_time,min,max));
    last_hunger_cm = last_hunger+cm_hunger_interval;
    next_poop=generate_next(old_time,poop_interval-poop_range,poop_interval+poop_range);
}

unsigned long Tamagotchi::get_last_hunger_cm() {
    return last_hunger_cm;
}

unsigned long Tamagotchi::get_next_poop() {
    return next_poop;
}

unsigned long Tamagotchi::get_poop_cm() {
    return cm_poop_interval;
}

void Tamagotchi::set_infinite_poop(unsigned long old_time) {
    next_poop = old_time+minute(12);
}

void Tamagotchi::gen_disc_range(unsigned long old_time) {
    disc_range = old_time+minute(1);
}

void Tamagotchi::set_disc_range(unsigned long value) {
    disc_range=value;
}

unsigned long Tamagotchi::get_disc_range() {
    return disc_range;
}

unsigned long Tamagotchi::get_overfeed() {
    return overfeed;
}

void Tamagotchi::set_overfeed(unsigned long value) {
    overfeed=value;
}

void Tamagotchi::gen_overfeed(unsigned long time) {
    overfeed=time+minute(1);
}

unsigned long Tamagotchi::minute(unsigned long time) {
    return (time*second(60));
}

unsigned long Tamagotchi::second(unsigned long time) {
    return (time*1000);
}
