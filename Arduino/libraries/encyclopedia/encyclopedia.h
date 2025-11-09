 #ifndef _ENCYCLOPEDIA_H
 #define _ENCYCLOPEDIA_H

 #include "Arduino.h"
 #include <sprites.h>

class info_node{

public:

    info_node();
    void initialise(int species);
    const char* get_name();
    const char* get_file_name();
    int get_type_int();
    const unsigned char* get_type_bitmap();
    int* get_element_array();
    const unsigned char* get_element_bitmap(int element_int);
    int get_level();

private:
    const char* species_name;
    const char* file_name;
    int type; //0=data, 1=vaccine, 2=virus
    int elements[3]; //0=fire, 1=fighting, 2=lightning, 3=earth,4=ice/water,5=mech,6=null_item
    int level;//0=baby, 1=in-training, 2=rookie, 3=champion, 4=ultimate, 5=mega

};


#endif
