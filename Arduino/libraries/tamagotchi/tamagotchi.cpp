#include "tamagotchi.h"
#include "Arduino.h"


Tamagotchi::Tamagotchi(){

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
