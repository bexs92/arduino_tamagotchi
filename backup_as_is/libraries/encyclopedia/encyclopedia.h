 #ifndef _ENCYCLOPEDIA_H
 #define _ENCYCLOPEDIA_H

 #include "Arduino.h"

 // const unsigned char* element[7]={
 //     fire,
 //     fighting,
 //     lightning,
 //     earth,
 //     sweat,
 //     mech,
 //     null_item
 // };

struct digimon_data {
    //uint8_t version;
    const char* species_name;
    const int type; //0=data, 1=vaccine, 2=virus
    const int elements[3]; //0=fire, 1=fighting, 2=lightning, 3=earth,4=ice/water,5=mech,6=null_item
    const int level;//0=baby, 1=in-training, 2=rookie, 3=champion, 4=ultimate, 5=mega
    //fighting moves;
    //evolutions
    //possible list of requirements for evolutions
    //sleeping time
    //ratio/power multiplier for training
    //addition of stats when evolved to
};

#endif
