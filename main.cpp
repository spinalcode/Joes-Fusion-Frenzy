#include "Pokitto.h"
// ------- Audio stuff --------
#include <File>
#include <LibAudio>
#include <ADPCMSource.h>
// ------- Audio stuff --------


#include "fonts.h"
#include "globals.h"
#include "sprites.h"
#include "ball.h"
#include "background.h"
#include "screen.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;




int main() {
    using PC=Pokitto::Core;
    using PD=Pokitto::Display;
    using PB=Pokitto::Buttons;
    using PS=Pokitto::Sound;

    PD::setTASRowMask(0b1111'11111111'11111111);

    PC::begin();

    PD::invisiblecolor = 0;
    PD::adjustCharStep = 0;
    PD::adjustLineStep = 0;

    PD::load565Palette(background_Tiles_pal); // load main palette

    // sprites palette starts at 128
    for(int t=0; t< sizeof(sprites_pal)/sizeof(uint16_t); t++){
        PD::palette[t+128] = sprites_pal[t];
    }
    // font palette starts at 251
    for(int t=0; t<sizeof(font_pal)/sizeof(uint16_t); t++){
        PD::palette[t+fontColour] = font_pal[t];
    }


    PD::lineFillers[0] = myBGFiller8bit; // map layer
    PD::lineFillers[1] = mySpriteFiller8bit; // sprite layer


    int scale[20];
    int x[20];
    int y[20];
    int sd[20];
    int ox[20];
    int oy[20];
    const uint8_t *imageData[20];
    const uint8_t *maskData[20];

    ox[0] = 8; oy[0] = 8;
    ox[1] = 10; oy[1] = 10;
    ox[2] = 13; oy[2] = 12;
    ox[3] = 15; oy[3] = 14;
    ox[4] = 18; oy[4] = 17;
    ox[5] = 23; oy[5] = 24;
    ox[6] = 24; oy[6] = 23;
    ox[7] = 26; oy[7] = 25;
    ox[8] = 29; oy[8] = 27;
    ox[9] = 32; oy[9] = 31;
    ox[10] = 34; oy[10] = 33;
    ox[11] = 64; oy[11] = 66;


    for(int t=0; t<5; t++){
        scale[t] = 0;
        x[t] = random(110);
        y[t] = random(88);
        sd[t] = random(1);
        if(sd[t]==0)sd[t]=-1;
    }
    imageData[0] = joe_01;
    imageData[1] = joe_02;
    imageData[2] = joe_03;
    imageData[3] = joe_04;
    imageData[4] = joe_05;
    imageData[5] = joe_06;
    imageData[6] = joe_07;
    imageData[7] = joe_08;
    imageData[8] = joe_09;
    imageData[9] = joe_10;
    imageData[10] = joe_11;
    imageData[11] = joe_12;

    long int lastMillis = PC::getTime();


    // play bgm
    //PS::playMusicStream(musicName);
/*
    if(bgmFile.openRO(musicName)){
        initTimer(22050);
    };
*/

    Audio::ADPCMSource::play("22050_16bit_adpcm.wav")->setLoop(true);

    initBalls();

    while(PC::isRunning()){
        if( !PC::update() ) 
            continue;
        spriteCount = 0;
/*
        drawSprite(0, 32, imageData[0], 128, 8);
        drawSprite(16, 32, imageData[1], 128, 8);
        drawSprite(36, 32, imageData[2], 128, 8);
        drawSprite(60, 32, imageData[3], 128, 8);
        drawSprite(90, 32, imageData[4], 128, 8);
        drawSprite(0, 64, imageData[5], 128, 8);
        drawSprite(40, 64, imageData[6], 128, 8);
        drawSprite(85, 64, imageData[7], 128, 8);
        drawSprite(0, 100, imageData[8], 128, 8);
        drawSprite(64, 100, imageData[9], 128, 8);
        drawSprite(128, 100, imageData[10], 128, 8);
        drawSprite(100, 100, imageData[11], 128, 8);

        drawSprite(0, 8, full_pal, 0, 8);
*/

        char tempText[64];
        sprintf(tempText,"FPS:%d",fpsCount);
        myPrint(0,0,tempText);

//        drawSprite(110,88, joe_01, sprite_palette_pal, 8);

        fpsCounter++;
        if(PC::getTime() >= lastMillis+1000){
            lastMillis = PC::getTime();
            fpsCount = fpsCounter;
            fpsCounter = 0;
        }

        updateBalls();

/*
    // Update music playing
    if( currentBuffer != completeBuffer){
        completeBuffer = currentBuffer;
        if(!bgmFile.read(&audioBuffer[bufferOffset[completeBuffer]], audioBufferSize)){
            // something
        }
    }
*/

    }
    
   return 1; 
}
