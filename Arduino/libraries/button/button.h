 #ifndef _BUTTON_H
 #define _BUTTON_H

 #include "Arduino.h"

 struct Button {

     int pin;
     int bttn;
     int toggle;
     unsigned long last_time;
     unsigned long diff;
 };


class Statemachine{

    public:

     Statemachine();
     void check(unsigned long time,int sound_status);
     void set_menu_count(int entered_num);
     void pin_mode();
     void set_up_read();
     int get_menu_count();
     void set_page_count(int entered_num);
     int get_page_count();
     int get_in_menu();
     void set_in_menu(int value);
     int get_action();
     void set_action(int value);
     int get_training();
     void set_training(int value);
     unsigned long get_time_store();
     void set_time_store(unsigned long value);

    private:

     Button A;
     Button B;
     Button C;
     int menu_count;
     int page_count;
     int in_menu;
     int in_action;
     int training_count;
     unsigned long time_store;

 };

 #endif
