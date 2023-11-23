#include "Pokitto.h"
// ------- Audio stuff --------
#include <File>
#include <LibAudio>
#include <ADPCMSource.h>
// ------- Audio stuff --------

#include "FixedPoints.h"
#include "FixedPointsCommon.h"
#include "buttonhandling.h"
#include "fonts.h"
#include "globals.h"
#include "sprites.h"
#include "ball.h"
#include "background.h"
#include "screen.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;



int cursor_x = 0;
int currentBall = rand()%5;

void playLevel(){

    int bx = cursor_x;
    int by = 48;

    if(_Right_But[HELD]){
        cursor_x++;
    }    
    if(_Left_But[HELD]){
        cursor_x--;
    }    

    if(_A_But[NEW]){
        balls[numBalls].x = bx+16;
        balls[numBalls].y = by;
        balls[numBalls].px = balls[numBalls].x;
        balls[numBalls].py = balls[numBalls].y;
        balls[numBalls].fx = 0;
        balls[numBalls].fy = 0;
        balls[numBalls].frameNumber = currentBall;
        balls[numBalls].radius = ballRad[balls[numBalls].frameNumber];//rand() % 20 + 10;
        numBalls++;
        currentBall = rand()%5;
    }    



    switch(currentBall){
        case 0:
            drawSprite(bx, by, joe_01, 128, 8);
            break;
        case 1:
            drawSprite(bx, by, joe_02, 128, 8);
            break;
        case 2:
            drawSprite(bx, by, joe_03, 128, 8);
            break;
        case 3:
            drawSprite(bx, by, joe_04, 128, 8);
            break;
        case 4:
            drawSprite(bx, by, joe_05, 128, 8);
            break;
        case 5:
            drawSprite(bx, by, joe_06, 128, 8);
            break;
        case 6:
            drawSprite(bx, by, joe_07, 128, 8);
            break;
        case 7:
            drawSprite(bx, by, joe_08, 128, 8);
            break;
        case 8:
            drawSprite(bx, by, joe_09, 128, 8);
            break;
        case 9:
            drawSprite(bx, by, joe_10, 128, 8);
            break;
        case 10:
            drawSprite(bx, by, joe_11, 128, 8);
            break;
        case 11:
            drawSprite(bx, by, joe_12, 128, 8);
            break;
    }

    drawSprite(bx -16, by -52, hand1, 128, 8);

    updateBalls();
    
}





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

        updateButtons();

        playLevel();

        char tempText[64];
        sprintf(tempText,"FPS:%d",fpsCount);
        myPrint(0,0,tempText);

        fpsCounter++;
        if(PC::getTime() >= lastMillis+1000){
            lastMillis = PC::getTime();
            fpsCount = fpsCounter;
            fpsCounter = 0;
        }


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
