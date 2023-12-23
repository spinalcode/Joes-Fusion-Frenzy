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
#include "sprites2.h"
#include "globals.h"
#include "ball.h"
#include "background.h"
#include "screen.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;

int cursor_x = 0;
int currentBall = rand()%5;

void playLevel(){

    int bx = cursor_x;
    int by = 24;

    if(_Right_But[HELD]){
        cursor_x++;
    }    
    if(_Left_But[HELD]){
        cursor_x--;
    }    

    if(_A_But[NEW]){
/*
        float x = (double)rand() / RAND_MAX * W + L;
        float y = (double)rand() / RAND_MAX * H;
        balls[numBalls].x = x;
        balls[numBalls].y = y;
        balls[numBalls].dx = 0;
        balls[numBalls].dy = 0;
        balls[numBalls].r = ballRad[currentBall];
        balls[numBalls].frameNumber = currentBall;
        currentBall = rand()%11;
        numBalls++;
*/
        balls[numBalls].x = bx+16;
        balls[numBalls].y = by;
        balls[numBalls].px = bx+16;
        balls[numBalls].py = by;
        balls[numBalls].fx = 0;
        balls[numBalls].fy = 0;
        balls[numBalls].frameNumber = currentBall;
        //balls[numBalls].r = ballRad[currentBall];
        balls[numBalls].radius = ballRad[currentBall];
        //balls[numBalls].grav = GRAVITY;//ballGrav[currentBall];
        numBalls++;
        currentBall = rand()%4;        
    }    


    drawSprite(bx, by, spriteFrameData[currentBall], spritePalData[currentBall], 8);

    drawMaskedSprite(bx -16, 0, hand1, hand1_pal, hand1_mask, 8);

    updateBalls(1);
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

    PD::lineFillers[0] = myBGFiller16bit; // map layer
    PD::lineFillers[1] = mySpriteFiller16bit; // sprite layer

    long int lastMillis = PC::getTime();

    // play bgm
//    Audio::ADPCMSource::play("22050_16bit_adpcm.wav")->setLoop(true);

    //initBalls();
    
    while(PC::isRunning()){
        if( !PC::update() ) 
            continue;
        spriteCount = 0;

        updateButtons();

        playLevel();

        char tempText[64];
        sprintf(tempText,"FPS:%d",fpsCount);
        myPrint(0,0,tempText);
        sprintf(tempText,"Joes:%d",numBalls);
        myPrint(0,8,tempText);

        fpsCounter++;
        if(PC::getTime() >= lastMillis+1000){
            lastMillis = PC::getTime();
            fpsCount = fpsCounter;
            fpsCounter = 0;
        }


    }
    
   return 1; 
}
