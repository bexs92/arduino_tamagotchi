#include "button.h"
#include "Arduino.h"

/*
const char* menu_array[8][5] = {
    {"1.1 Name & age","1.2 Hunger & nutrition","1.3 Hp,MP,OFF,DEF,SPEED,BRAIN","1.4 Battles","1.5 happiness & discipline"},
    {"2.1 Meat_selected","2.2 vitimin selected","Nope","Nope","Nope"},
    {"3.1 HP & MP","3.2 OFF & DEF","3.3 SPEED & BRAINS","Nope","Nope"},
    {"4.1 Battle","Nope","Nope","Nope","Nope"},
    {"5.1 CLearing poop","Nope","Nope","Nope","Nope"},
    {"6.1 Light ON","6.2 light OFF","Nope","Nope","Nope"},
    {"7.1 giving medical treatment","Nope","Nope","Nope","Nope"},
    {"8.1 Praise","8.2 Discipline","Nope","Nope","Nope"}
};*/

//--------------------------------------------------------------------------------------------

const int C_mid = 262;
const int C_sharp = 277;
const int D_mid = 294;
const int E_flat = 311;
const int E_mid = 330;
const int F_mid = 349;
const int F_sharp = 370;
const int G_mid = 392;
const int A_flat = 415;
const int A_mid = 440;
const int B_flat = 466;
const int B_mid = 494;
const int C_high = 523;

const int major_scale[8] = {C_mid,D_mid,E_mid,F_mid,G_mid,A_mid,B_mid,C_high};

const int sound_pin = A0;

int tone_prev_time = 0;

//--------------------------------------------------------------------------------------------

const int A_max_count[8] = {8,2,6,0,0,2,0,2};

//--------------------------------------------------------------------------------------------

Statemachine::Statemachine(){
    menu_count=0;
    page_count=0;
    in_menu=0;
    //transferring from older board - a=10,b=9,c=8
    A=(Button){A1,0,1,0,0};
    B=(Button){A2,0,1,0,0};
    C=(Button){A3,0,1,0,0};

    training_count=0;
    time_store = 0;
}

void Statemachine::pin_mode(){
    pinMode(A.pin,INPUT_PULLUP);
    pinMode(B.pin,INPUT_PULLUP);
    pinMode(C.pin,INPUT_PULLUP);
}

void Statemachine::set_up_read(){
    A.bttn = digitalRead(A.pin);
    B.bttn = digitalRead(B.pin);
    C.bttn = digitalRead(C.pin);
}

void Statemachine::check(unsigned long time){

//------------------------------------------------------------------------------

    // if(A.bttn==0){
    //     Serial.println("A");
    // }

        if(A.bttn!=A.toggle){
            A.diff=time-A.last_time;

            if (A.diff>50){
                if(A.toggle==1){
                    A.toggle=0;
                    if (in_menu==1){
                        page_count=(page_count+1)%A_max_count[menu_count-1];
                        tone(sound_pin,C_mid);
                    }
                    else {
                        menu_count=(menu_count+1)%9;
                        tone(sound_pin,major_scale[menu_count-1]);
                        //Serial.println(menu_count);
                    }
                }
                else {
                    A.toggle=1;
                    noTone(sound_pin);
                };

                A.last_time=time;
            };
        }

        if(B.bttn!=B.toggle){
            B.diff=time-B.last_time;

            if (B.diff>50){
                if(B.toggle==1){
                    B.toggle=0;
                    if (in_menu==1){
                        Serial.println("selected_option");
                        // in_action=1;
                        // tone(sound_pin,G_mid);
                        if(menu_count==3){
                            if(page_count<6){
                                if(page_count!=2){
                                    training_count=training_count+1;
                                    in_action=1;
                                    tone(sound_pin,G_mid);
                                }
                                else{
                                    in_action=1;
                                    tone(sound_pin,G_mid);
                                    if(time-time_store<1500){
                                        if(training_count==0){
                                            training_count=round(((((time-time_store)*100)/1500))/10)+1;
                                        }
                                    }
                                }
                            }
                        }

                        else {
                            in_action=1;
                            tone(sound_pin,G_mid);
                        }

                    }
                    else {
                        Serial.println("opening menu");
                        tone(sound_pin,C_mid);
                        in_menu=1;
                        page_count=0;
                        if(menu_count==5){
                            in_action=1;
                        }
                    }
                }
                else {
                    B.toggle=1;
                    noTone(sound_pin);
                };
                B.last_time=time;
            };
        }


        if(C.bttn!=C.toggle){
            C.diff=time-C.last_time;

            if (C.diff>50){
                if(C.toggle==1){
                    C.toggle=0;
                    tone(sound_pin,125);
                    menu_count=0;
                    page_count=0;
                    A.toggle=1;
                    A.diff=0;
                    A.last_time=0;
                    B.toggle=1;
                    B.diff=0;
                    B.last_time=0;
                    in_menu=0;
                    in_action=0;
                    training_count=0;

                }
                else {
                    C.toggle=1;
                    noTone(sound_pin);
                };

                C.last_time=time;
            };
        }

//------------------------------------------------------------------------------


};

void Statemachine::set_menu_count(int entered_num){
    menu_count=entered_num;
};

int Statemachine::get_menu_count(){
    return menu_count;
};

void Statemachine::set_page_count(int entered_num){
    page_count=entered_num;
};

int Statemachine::get_page_count(){
    return page_count;
};

int Statemachine::get_in_menu(){
    return in_menu;
}

void Statemachine::set_in_menu(int value){
    in_menu=value;
}

int Statemachine::get_action(){
    return in_action;
}

void Statemachine::set_action(int value){
    in_action=value;
}

int Statemachine::get_training(){
    return training_count;
}

void Statemachine::set_training(int value){
    training_count=value;
}

unsigned long Statemachine::get_time_store(){
    return time_store;
}

void Statemachine::set_time_store(unsigned long value){
    time_store=value;
}


