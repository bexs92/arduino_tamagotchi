
#include <Adafruit_PCD8544.h>
#include <SPI.h>
#include <SdFat.h>
#include <sprite_loader_lib.h>
#include <button.h>
#include <tamagotchi.h>
#include <Arduino.h>
#include <encyclopedia.h>

#define CE D9
#define RST D10
#define DC D11
#define DIN D12  
#define CLK D13

Adafruit_PCD8544 new_lcd = Adafruit_PCD8544(CLK,DIN,DC,CE,RST);

animation sprite_anim = animation(new_lcd);

int frameNumber=0;

const char* digimon;
info_node info;

unsigned long previous_time = 0;

unsigned long interval = 500;

Statemachine sm = Statemachine();

const int led_pin = A5;

unsigned long last_action=0;
int action_toggle=0;

const unsigned long action_time[9][12] = {
  /*null*/{0,0,0,0,0,0,0,0,0,0,0,0},
  /*stat_page*/{0,0,0,0,0,0,0,0,0,0,0,0},
  /*food_page*/{2000,3000,2000,0,0,0,0,0,0,0,0,0},
  /*training_page*/{3000,3000,3000,3000,3000,3000,500,500,500,500,500,500},
  /*battle_page*/{0,0,0,0,0,0,0,0,0,0,0,0},
  /*poop_page*/{6500,2000,0,0,0,0,0,0,0,0,0,0},
  /*light_page*/{2000,2000,0,0,0,0,0,0,0,0,0,0},
  /*med_page*/{0,0,0,0,0,0,0,0,0,0,0,0},
  /*disc_page*/{2000,2000,2000,0,0,0,0,0,0,0,0,0}
  
};

Tamagotchi data;

int hunger_toggle=0;
int poop_toggle=0;
int sleepy_toggle=0;
int tired_toggle=0;
int sick_toggle=0;

int onscreen_poops=0;
int overfeed_counter=0;
int training_counter=0;

int return_needs(int hungry, int poop, int sleepy, int tired, int sick) {
  int combined = (hungry*1)+(poop*2)+(sleepy*4)+(tired*8)+(sick*16);
  return combined;
}

int game_time_D=0;
int game_time_H=0;
int game_time_M=0;

const unsigned long minute_interval=1000;

unsigned long game_time_pt=0;

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);

//loading from card reader;
  save_data empty ={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
  
  data.load_from_card(empty);
  data.transfer(empty);

  //data.initialise(21); 

  info.initialise(data.species);

  sm.pin_mode();
  
  pinMode(led_pin,OUTPUT);
  analogWrite(led_pin,data.light_status*200);
  
  new_lcd.begin();
  new_lcd.setContrast(72);

  new_lcd.clearDisplay();

  new_lcd.setTextSize(1);
  new_lcd.setTextColor(BLACK);

  digimon = info.get_file_name();

  loadCharacter(digimon); 

  //animation sprite_anim = animation(new_lcd);

  sprite_anim.make_sequences();

  sprite_anim.initialise(walk_L,crouch_L,roar_L,walk_R,crouch_R,roar_R);

  new_lcd.clearDisplay();

}

void loop() {
  // put your main code here, to run repeatedly:
    unsigned long time = millis();

    sm.set_up_read();

    sm.check(time,data.sound_status);

  //game time
    if(time-game_time_pt>=minute_interval){
      game_time_pt=time;
      if(game_time_M<60){
        game_time_M=game_time_M+1;
        }
      else{
        game_time_M=0;
        if (game_time_H<24){
          game_time_H=game_time_H+1;
          }
        else{
          game_time_H=0;
          game_time_D=game_time_D+1;
        }
      }
    }
    
    
    if(time-previous_time>=interval){
      previous_time=time;
      if(frameNumber<33){
        frameNumber = frameNumber+1;
        }
      else{
        frameNumber=0;
        }

    }

    sprite_anim.retreiveFrame(frameNumber,time,return_needs(hunger_toggle,poop_toggle,sleepy_toggle,tired_toggle,sick_toggle),
    onscreen_poops,data,sm,info,game_time_H,game_time_M
    );
    

  //something that checks data
  if(data.get_last_hunger()<time){
    if(hunger_toggle==0){
      hunger_toggle=1;
      if(data.hunger>0){
        data.hunger=data.hunger-1;
      }
    }
  }

  if(data.get_last_hunger_cm()<time){
    data.cm=data.cm+1;
    if(data.happy>2){
      data.happy=data.happy-2;
    }
    hunger_toggle=0;
    data.gen_next_hunger(time);
    frameNumber=0;
  }

  if(data.get_next_poop()<time){
    if(poop_toggle==0){
      poop_toggle=1;
    }
  }

  if(data.get_next_poop()+data.get_poop_cm()<time){
      poop_toggle=0;
      data.set_infinite_poop(time);
      data.cm=data.cm+1;
      onscreen_poops=onscreen_poops+1;
      frameNumber=0;
      data.gen_disc_range(time);
  }

  if(data.tired<=20){
    tired_toggle=1;
  }
  if(data.tired>20){
    tired_toggle=0;
  }
  
  //checking for button pushes
  if (action_toggle!=sm.get_action()){
    Serial.println("In the action toggle");
      if(sm.get_action()==1){
          //do the action and change the data stats
          frameNumber=0;
          Serial.println("In action");
          
          action_toggle=1;
          last_action=time;

          if (sm.get_menu_count()==0){
            if(sm.get_page_count()==0){
              Serial.println("Sound off");
              if(data.sound_status==1){
                data.sound_status=0;
              }
              else {
                data.sound_status=1;
              }
            }
            if(sm.get_page_count()==1){
              Serial.println("Light off");
              if(data.light_status==1){
                data.light_status=0;
                analogWrite(led_pin,0);
              }
              else {
                data.light_status=1;
                analogWrite(led_pin,200);
              }
            }

            if(sm.get_page_count()==2){
              Serial.println("Saving...");
              save_data save_temp = data.create_save();
              data.save_to_card(save_temp);
              delay(3000);
            }
            if(sm.get_page_count()==3){
              Serial.println("opening art");
            }
            else {
            
            }
          }         

          if (sm.get_menu_count()==2){
            if(overfeed_counter<6){
              if(sm.get_page_count()==0){

                  if (data.hunger==3){
                    hunger_toggle=0;
                    data.gen_next_hunger(time);
                  }

                  if (data.hunger<4){
                      data.hunger=data.hunger+1;
                      data.happy=data.happy+1;
                      data.disc=data.disc+1;
                  }

                  else{
                      data.happy=data.happy-1;
                      data.disc=data.disc-1;
                  }

                  data.weight=data.weight+1;
              }
              if(sm.get_page_count()==1){
                  if (data.hunger<2){
                      data.hunger=data.hunger+2;
                      data.happy=data.happy+1;
                      data.disc=data.disc+1;
                      data.tired=data.tired+5;
                  }

                  if (data.hunger==2){
                      data.hunger=data.hunger+1;
                      data.happy=data.happy+1;
                      data.disc=data.disc+1;
                      hunger_toggle=0;
                      data.gen_next_hunger(time);
                  }

                  if (data.hunger==3){
                      data.hunger=data.hunger+1;
                      data.happy=data.happy+1;
                      data.disc=data.disc+1;
                      hunger_toggle=0;
                      data.gen_next_hunger(time);
                  }

                  if(data.hunger==4) {
                      data.happy=data.happy-1;
                      data.disc=data.disc-1;
                  }
              data.weight=data.weight+2;
              }

              if(data.get_overfeed()>time){
                overfeed_counter=overfeed_counter+1;
              }
              else {
                data.gen_overfeed(time);
                overfeed_counter=0;
              }

            }//
            
            else {
              //Here's the swap to the no animation
              sm.set_page_count(2);
              data.gen_disc_range(time);
            }
          }
          //training menu
          if (sm.get_menu_count()==3){
              if(game_time_H<23){
                game_time_H=game_time_H+1;
              }
              if(game_time_H==23){
                game_time_H=0;
              }

              if(hunger_toggle==1){
                  data.cm=data.cm+1;
                  hunger_toggle=0;
                  data.gen_next_hunger(time);
                  frameNumber=0;
              }

              if(poop_toggle==1){
                  poop_toggle=0;
                  data.set_infinite_poop(time);
                  data.cm=data.cm+1;
                  onscreen_poops=onscreen_poops+1;
                  frameNumber=0;
                  data.gen_disc_range(time);
              }
            
              if(data.tired>8){
                data.tired=data.tired-8;
              }
              if(data.tired<60){
                if(data.happy>1){
                  data.happy=data.happy-1;
                }
              }
              if(tired_toggle==1){
                if(data.happy>4){
                  data.happy=data.happy-4;
                }
                if(data.disc>3){
                  data.disc=data.disc-3;
                }
              }

              if(sm.get_page_count()==2){
                interval=250;
                sm.set_time_store(time);
              }
          }

          if (sm.get_menu_count()==5){
            frameNumber=0;
            if(poop_toggle==1){
              poop_toggle=0;
              data.set_infinite_poop(time);
              if (data.weight>1){
                data.weight-1;
              }
            }
            else{
              sm.set_page_count(1);
            }
            onscreen_poops=0;
          }

          if(sm.get_menu_count()==6){
            if(sm.get_page_count()==0){
                data.tired=data.tired+20;
              }
            else{
              data.tired=100;
            }
            if(game_time_H<23){
              game_time_H=game_time_H+1;
            }
            if(game_time_H==23){
              game_time_H=0;
            }
          }

          if (sm.get_menu_count()==8){
              if(sm.get_page_count()==0){
                  data.happy=data.happy+2;
                  data.disc=data.disc-4;
              }
              
              if(sm.get_page_count()==1){
                  if(data.get_disc_range()>time){
                    data.disc=data.disc+4;
                    data.set_disc_range(time-1);
                    sm.set_page_count(2);
                    overfeed_counter=0;
                    data.set_overfeed(0);
                  }
                  else {
                    data.happy=data.happy-4;
                    data.disc=data.disc+2;
                  }
              }
          }
      }
      
      else {
          action_toggle=0;
          sm.set_action(0);
          interval=500;
          if(sm.get_menu_count()==5){
             sm.set_in_menu(0);
          }
          //training menu
          if (sm.get_menu_count()==3){
            if (sm.get_page_count()==0){
              data.hp=data.hp+(sm.get_training()*5);
              sm.set_page_count(6);
            }
            if (sm.get_page_count()==1){
              data.mp=data.mp+(sm.get_training()*5);
              sm.set_page_count(7);
            }
            if (sm.get_page_count()==2){
              data.off=data.off+(round(sm.get_training()*0.5));
              sm.set_page_count(8);
            }
            if (sm.get_page_count()==3){
              data.def=data.def+(round(sm.get_training()*2.5));
              sm.set_page_count(9);
            }
            if (sm.get_page_count()==4){
              data.spd=data.spd+(round(sm.get_training()*2.5));
              sm.set_page_count(10);
            }

            if (sm.get_page_count()==5){
              data.brn=data.brn+(sm.get_training()*2.5);
              sm.set_page_count(11);

            }

          }
      }
  }

  else {
      if(time-last_action>=action_time[sm.get_menu_count()][sm.get_page_count()]){
        //Serial.println(action_time[sm.get_menu_count()][sm.get_page_count()]);
        sm.set_action(0);
        if(sm.get_menu_count()==5){
             sm.set_in_menu(0);
             sm.set_page_count(0);
          }
        if(sm.get_menu_count()==8){
          if(sm.get_page_count()==2){
             sm.set_page_count(1);
          }
        }

        if(sm.get_menu_count()==2){
          if(sm.get_page_count()==2){
            sm.set_page_count(0);
          }
        }
        
        if(sm.get_menu_count()==3){
          if(time-last_action>5000){
            if(sm.get_page_count()>5){
              sm.set_page_count(sm.get_page_count()-6);
              sm.set_training(0);
            }
          }
        }
      }
  }   
}
