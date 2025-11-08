
#include "sprite_loader_lib.h"
#include "Arduino.h"
#include <SD.h>
#include <Adafruit_PCD8544.h>

uint8_t walk_L[SPRITE_SIZE];
uint8_t walk_R[SPRITE_SIZE];
uint8_t roar_L[SPRITE_SIZE];
uint8_t roar_R[SPRITE_SIZE];
uint8_t crouch_L[SPRITE_SIZE];
uint8_t crouch_R[SPRITE_SIZE];

bool loadSprite(const char* digimon,const char* action,const char* side,uint8_t* spriteBuffer) {

    char filename[32];
    snprintf(filename,sizeof(filename),"/%s/%s_%s.BIN",digimon,action,side);

    if (!SD.begin(53)) {
        Serial.println("initialization failed!");
        while (1);
    }

    else{Serial.println(filename);}

    File spriteFile = SD.open(filename,FILE_READ);

    if (spriteFile) Serial.println("Managed to open file");
    else Serial.println("No luck");

    if (!spriteFile) {
        Serial.println("Failed to open sprite file");
        Serial.println(filename);
        return false;
    }

    for  (int i = 0; i < SPRITE_SIZE && spriteFile.available(); i++) {
        spriteBuffer[i]=spriteFile.read();
        Serial.println(spriteBuffer[i]);
    }

    spriteFile.close();

    Serial.println("Sprite loaded");

    return true;

}

void loadCharacter(const char* digimon) {
    loadSprite(digimon,"WALK","L",walk_L);
    loadSprite(digimon,"WALK","R",walk_R);
    loadSprite(digimon,"ROAR","L",roar_L);
    loadSprite(digimon,"ROAR","R",roar_R);
    loadSprite(digimon,"CROUCH","L",crouch_L);
    loadSprite(digimon,"CROUCH","R",crouch_R);
}

// 'empty', 11x10px
const unsigned char empty_heart [] PROGMEM = {
    0x00, 0x00, 0x31, 0x80, 0x4a, 0x40, 0x44, 0x40, 0x40, 0x40, 0x40, 0x40, 0x20, 0x80, 0x11, 0x00,
    0x0a, 0x00, 0x04, 0x00
};

// 'heart', 11x10px
const unsigned char full_heart [] PROGMEM = {
    0x00, 0x00, 0x31, 0x80, 0x7b, 0xc0, 0x5f, 0xc0, 0x5f, 0xc0, 0x7f, 0xc0, 0x3f, 0x80, 0x1f, 0x00,
    0x0e, 0x00, 0x04, 0x00
};

// 'stats', 11x10px
const unsigned char menu_stats [] PROGMEM = {
    0x0e, 0x00, 0x31, 0x80, 0x40, 0x40, 0x8a, 0x20, 0xaa, 0xa0, 0xa0, 0xa0, 0x84, 0x20, 0x8e, 0x20,
    0x71, 0xc0, 0x00, 0x00
};

// 'food', 11x10px
const unsigned char menu_food [] PROGMEM = {
    0x70, 0x00, 0xde, 0x00, 0xbf, 0x00, 0x75, 0x80, 0x7f, 0xc0, 0x7f, 0xc0, 0x2e, 0xc0, 0x1f, 0x20,
    0x0f, 0x60, 0x01, 0xc0
};

// 'training', 11x10px
const unsigned char menu_training [] PROGMEM = {
    0x20, 0xc0, 0x70, 0xc0, 0xf8, 0x00, 0xe3, 0xc0, 0xee, 0xc0, 0xe0, 0xc0, 0xf9, 0xc0, 0xfb, 0x40,
    0xfa, 0x60, 0x71, 0x20
};

// 'battle', 11x10px
const unsigned char menu_battle [] PROGMEM = {
    0x60, 0xc0, 0x60, 0xc0, 0x00, 0x00, 0x67, 0xc0, 0x70, 0xc0, 0x7c, 0xc0, 0x60, 0xc0, 0x51, 0x40,
    0x59, 0x40, 0x8a, 0x20
};

// 'poop', 11x10px
const unsigned char menu_poop [] PROGMEM = {
    0x08, 0x00, 0x0e, 0x00, 0x1f, 0x00, 0x31, 0x80, 0x3f, 0x80, 0x5f, 0x40, 0xe0, 0xe0, 0xff, 0xe0,
    0x7f, 0xc0, 0x3f, 0x80
};

// 'light', 11x10px
const unsigned char menu_light [] PROGMEM = {
    0x84, 0x20, 0x40, 0x40, 0x0e, 0x00, 0x1f, 0x00, 0x35, 0x80, 0xaa, 0xa0, 0x2e, 0x80, 0x15, 0x00,
    0x4e, 0x40, 0x8e, 0x20
};

// 'bandage', 11x10px
const unsigned char menu_med [] PROGMEM = {
    0x13, 0x00, 0x2c, 0x80, 0x48, 0x40, 0x90, 0x60, 0x60, 0xc0, 0x41, 0xa0, 0x83, 0x20, 0x46, 0x40,
    0x2c, 0x80, 0x1b, 0x00
};

// 'alert', 11x10px
const unsigned char menu_alert [] PROGMEM = {
    0x10, 0x00, 0x18, 0x00, 0x9f, 0x80, 0x3f, 0xc0, 0x1f, 0x60, 0xc7, 0xe0, 0x01, 0xe0, 0x3f, 0xe0,
    0x9f, 0xc0, 0x0f, 0x80
};

const unsigned char* menu_array[8] = {

    menu_stats,
    menu_food,
    menu_training,
    menu_battle,
    menu_poop,
    menu_light,
    menu_med,
    menu_alert

};

animation::animation{
public:

    unsigned char* orderArray[34];

    int h_dist[34] = {
        16,14,10,10,14,14,10,6,6,6,6,6,6,6,6,10,14,16,20,24,24,20,20,24,28,28,28,28,28,28,28,28,24,20
    };

    //Constructor

    animation(){;}

    void initialise(unsigned char* n_L,unsigned char* c_L,unsigned char* r_L,unsigned char* n_R,unsigned char* c_R,unsigned char* r_R) {

        orderArray[0]=n_L;
        orderArray[1]=n_L;
        orderArray[2]=c_L;
        orderArray[3]=c_R;
        orderArray[4]=n_R;
        orderArray[5]=n_L;
        orderArray[6]=c_L;
        orderArray[7]=c_L;
        orderArray[8]=c_R;
        orderArray[9]=c_L;
        orderArray[10]=r_L;
        orderArray[11]=c_L;
        orderArray[12]=r_L;
        orderArray[13]=c_L;
        orderArray[14]=c_R;
        orderArray[15]=c_R;
        orderArray[16]=n_L;

        //now reversing the order

        orderArray[17]=n_R;
        orderArray[18]=n_R;
        orderArray[19]=c_R;
        orderArray[20]=c_L;
        orderArray[21]=n_L;
        orderArray[22]=n_R;
        orderArray[23]=c_R;
        orderArray[24]=c_R;
        orderArray[25]=c_L;
        orderArray[26]=c_R;
        orderArray[27]=r_R;
        orderArray[28]=c_R;
        orderArray[29]=r_R;
        orderArray[30]=c_R;
        orderArray[31]=c_L;
        orderArray[32]=c_L;
        orderArray[33]=n_L;

    }

    void retreiveFrame(int frameNo, int timeCheck,int toggle,Adafruit_PCD8544 lcd){
        int horizontal_dist = h_dist[frameNo];

        frame(orderArray[frameNo],horizontal_dist,15,timeCheck,toggle,lcd);
    }

    void frame(uint8_t* image,int xPos, int yPos,int timeCheck,int toggle,Adafruit_PCD8544 lcd) {

//        if (toggle==1) {
//        lcd.clearDisplay();
//      }

        if(timeCheck%500==0){
            lcd.clearDisplay();
        }

        lcd.drawBitmap(xPos,yPos,image,16,16,BLACK);
        lcd.drawRect(0,0,48,48,BLACK);

        //if menu number add here

        lcd.display();

    }

};
