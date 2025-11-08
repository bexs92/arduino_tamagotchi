 #ifndef _BUTTON_LIB_H
 #define _BUTTON_LIB_H

 #include "Arduino.h"

 extern const int A_max_count[8];

 extern const char* menu_array[8][5];

 class Button{

 public:

     Button();
     void initialise(int entered_pin);
     int set_up_read();
     void pin_mode();
     int check(int time,String message);
     int return_diff();
     void disable();
     void enable();
     void A_bttn_pushed();
     void B_bttn_pushed();
     void C_bttn_pushed();
     void reset();
     int return_menu();
     int return_page();

 private:
     int pin;
     int bttn;
     int toggle;
     int last_time;
     int diff;
     int disabled;

     int A_count;
     int B_count;
     int C_count;

     int menu_count;
     int page_count;
     int A_limit;

 };

class StateMachine{

 public:

     StateMachine(int pin_1, int pin_2,int pin_3);
     void pin_mode();
     void set_up_read();
     void check(int time);
     void retreive_menu();
     void reset();
     int return_menu_number();
     int return_page_number();
     char retreive_menu(int menu,int page_no);

 private:
     int A_bttn_pin;
     int B_bttn_pin;
     int C_bttn_pin;

     Button A;
     Button B;
     Button C;

     int A_limit;
     int A_count;
     int B_count;
     int menu_count;
     int page_count;

     int toggle;
     int last_time;
     int diff;
     bool A_check;
     bool B_check;
     bool C_check;

 };

 #endif
