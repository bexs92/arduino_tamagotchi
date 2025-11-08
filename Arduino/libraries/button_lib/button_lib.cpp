#include "button_lib.h"
#include "Arduino.h"


const int A_max_count[8] = {5,2,3,0,0,2,0,2};

const char* menu_array[8][5] = {
    {"1.1 Name & age","1.2 Hunger & nutrition","1.3 Hp,MP,OFF,DEF,SPEED,BRAIN","1.4 Battles","1.5 happiness & discipline"},
    {"2.1 Meat_selected","2.2 vitimin selected","Nope","Nope","Nope"},
    {"3.1 HP & MP","3.2 OFF & DEF","3.3 SPEED & BRAINS","Nope","Nope"},
    {"4.1 Battle","Nope","Nope","Nope","Nope"},
    {"5.1 CLearing poop","Nope","Nope","Nope","Nope"},
    {"6.1 Light ON","6.2 light OFF","Nope","Nope","Nope"},
    {"7.1 giving medical treatment","Nope","Nope","Nope","Nope"},
    {"8.1 Praise","8.2 Discipline","Nope","Nope","Nope"}
};

Button::Button(){

    pin=0;
    bttn=0;
    toggle=0;
    last_time=0;
    diff=0;
    disabled=0;

    A_count=0;
    B_count=0;
    C_count=0;

    menu_count=0;
    page_count=0;

    A_limit=0;

};

void Button::initialise(int entered_pin) {
    pin=entered_pin;
}

void Button::pin_mode() {
    pinMode(pin,INPUT);
};

int Button::set_up_read() {
    bttn = digitalRead(pin);

};

void Button::disable() {
    disabled=1;
}

void Button::enable() {
    disabled=0;
};

int Button::return_diff(){
    return diff;
};

int Button::check(int time,String message){


    if(disabled!=1){
        if(bttn!=toggle){
            diff = time-last_time;
            if (diff>500){
                if (toggle==0){
                    toggle=1;
                    Serial.println(message);
                    if (message=="A"){
                        A_bttn_pushed();
                    }
                    if (message=="B"){
                        B_bttn_pushed();
                    }
                    if (message=="C"){
                        C_bttn_pushed();
                    }


                    return 1;
                }
                else{
                    toggle=0;
                    return 0;
                }
                last_time=time;
            }

        };
    };
};

void Button::A_bttn_pushed(){

    if (B_count==0){
        A_limit=8;
        if (A_count<A_limit){
            A_count = A_count+1;
            menu_count = A_count;
            Serial.println(menu_count);
        }

        else {
            reset();
        }
    }

    else {
        A_limit=A_max_count[menu_count];
        if (A_count<A_limit){
            A_count = A_count+1;
            page_count = A_count;
        }

        else {
            reset();
        }
    }

};

void Button::B_bttn_pushed(){

    if(B_count==0){
        if (menu_count>0){
            B_count=B_count+1;
            //Serial.println(retreive_menu(menu_count,page_count));
            Serial.println("retreive menu");

        }

        else{
            Serial.println("Selecting menu option");

        }
    }
    else{
        reset();
    }

}

void Button::C_bttn_pushed(){
    reset();
}

void Button::reset(){
    A_count = 0;
    B_count = 0;
    A_limit=0;

    menu_count = 0;
    page_count = 0;
    Serial.println("Cancelled");
}

int Button::return_menu(){
    return menu_count;
}

int Button::return_page(){
    return page_count;
}


StateMachine::StateMachine(int pin_1, int pin_2,int pin_3){

        A_bttn_pin=pin_1;
        B_bttn_pin=pin_2;
        C_bttn_pin=pin_3;

        A.initialise(pin_1);
        B.initialise(pin_2);
        C.initialise(pin_3);

        toggle=0;
        last_time=0;
        diff=0;

        menu_count =0;
        page_count =0;
        A_count = 0;
        B_count = 0;

    };


void StateMachine::pin_mode(){
        A.pin_mode();
        B.pin_mode();
        C.pin_mode();
    }

void StateMachine::set_up_read(){
        A.set_up_read();
        B.set_up_read();
        C.set_up_read();
    };

void StateMachine::check(int time){

    A_check = A.check(time,"A");
    B_check = B.check(time,"B");
    C_check = C.check(time,"C");

    if (A_check!=toggle){
        diff = time-last_time;
        if (diff>500){
            if (B_count==0){
                A_limit=8;
                if (A_count<A_limit){
                    A_count = A_count+1;
                    menu_count = A_count;
                    Serial.println(menu_count);
                    toggle=1;
                    A_check=false;
                }

                else {
                    reset();
                    toggle=0;
                    A_check=false;
                }
            }
            else {
                A_limit=A_max_count[menu_count];
                if (A_count<A_limit){
                    A_count = A_count+1;
                    page_count = A_count;
                    toggle=1;
                    A_check=false;
                }

                else {
                    reset();
                    toggle=0;
                    A_check=false;
                }


            }
            last_time=time;
        }


    if (B_check==true){
        if (B.return_diff()>500) {
            if(B_count==0){
                if (menu_count>0){
                    B_count=B_count+1;
                    //Serial.println(retreive_menu(menu_count,page_count));
                    Serial.println("retreive menu");
                    toggle=1;
                    B_check=false;
                    }

                else{
                    Serial.println("Nope");
                    toggle=0;
                    B_check=false;
                    }
                }
            else{
                reset();
                toggle=0;
                B_check=false;
                }
            };

    };

    if (C_check==true){
        if(C.return_diff()>500){
            reset();
            toggle=0;
            C_check=false;
        }
    }

    };
}

void StateMachine::reset(){
    A_count = 0;
    B_count = 0;

    A.enable();
    B.enable();
    C.enable();
    menu_count = 0;
    page_count = 0;
    Serial.println("Cancelled");
}

int StateMachine::return_menu_number(){
    return A.return_menu()-1;
}

int StateMachine::return_page_number(){
    return page_count;
}

// char StateMachine::retreive_menu(int menu,int page_no){
//     //String current_menu[5] = menu_array[menu];
//     char menu_text = menu_array[menu][page_no];
//
//     return menu_text;
// }

