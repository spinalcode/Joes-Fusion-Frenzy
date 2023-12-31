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
#include "sounds.h"
#include "sprites2.h"
#include "globals.h"
#include "ball.h"
#include "background.h"
#include "screen.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;

int cursor_x = 0;
int currentBall = rand()%5;
int clawLength = 24;
int clawFrame = 3;
int clawTime=0;
bool gettingNextBall = false;
bool gotNextBall = false;
int oldCursor_x = 0;
int claw_y = 15;
#define CLAWSPEED 4

void playLevel(){

    int bx = cursor_x;
    int by = 2;


    if(gettingNextBall==false){
        
        if(_Right_But[HELD]){
            cursor_x+=(DELTA/2);
        }    
        if(_Left_But[HELD]){
            cursor_x-=(DELTA/2);
        }    
    
        if(_A_But[NEW]){
            balls[numBalls].x = bx + 4;
            balls[numBalls].y = by + clawLength;
            balls[numBalls].px = balls[numBalls].x;
            balls[numBalls].py = balls[numBalls].y;
            balls[numBalls].fx = 0;
            balls[numBalls].fy = 0;
            balls[numBalls].frameNumber = currentBall;
            balls[numBalls].radius = ballRad[currentBall];
            numBalls++;
            currentBall = rand()%4;
            clawFrame = 2;
            clawTime=5;
            gettingNextBall=true;
            gotNextBall = false;
            cursor_x = cursor_x & 254;
            oldCursor_x = cursor_x;
        }    
    
        drawSprite(bx, by, claw[0], claw_pal, 4);
        drawSprite(bx-8, by+claw_y, claw[(clawFrame*2)], claw_pal, 4);
    
        if(clawFrame == 3){
            drawMaskedSprite(bx + 4 - ballRad[currentBall], by + clawLength, spriteFrameData[currentBall], spritePalData[currentBall], spriteMaskData[currentBall], 8);
        }
        
        drawSprite(bx, by+claw_y,   claw[1+(clawFrame*2)], claw_pal, 4);
    
    }else{
        // gettingNextBall
        if(gotNextBall==false){
            if(cursor_x < 170){
                cursor_x+=CLAWSPEED;
                if(clawFrame != 3){
                    if(--clawTime==0){
                        clawTime=5;
                        if(clawFrame >1)
                            clawFrame--;
                    }
                }
            }else{
                cursor_x = 170;
                if(claw_y < (64-(ballRad[currentBall]*1.5))-15){
                    claw_y+=CLAWSPEED;
                }else{
                    if(--clawTime<=0){
                        clawTime=5;
                        clawFrame++;
                    }
                    if(clawFrame==4){
                        clawFrame=3;
                    }
                }
            }

        }else{
            if(claw_y > 15){
                claw_y-=CLAWSPEED;
            }else{
                if(cursor_x > oldCursor_x){
                    cursor_x-=CLAWSPEED;
                }else{
                    cursor_x = oldCursor_x;
                    gettingNextBall=false;
                    gotNextBall=false;
                }
            }
            
        }

            drawSprite(bx, by, claw[0], claw_pal, 4);
            drawSprite(bx-8, by+claw_y, claw[(clawFrame*2)], claw_pal, 4);
            if(clawFrame == 3){
                gotNextBall=true;
                //printf("gotNextBall\n");
                drawMaskedSprite(bx + 4 - ballRad[currentBall], by+claw_y+(15-(ballRad[currentBall]*0.5)), spriteFrameData[currentBall], spritePalData[currentBall], spriteMaskData[currentBall], 8);
                
            }else{
                drawMaskedSprite(174 - ballRad[currentBall], 64-(ballRad[currentBall]*2), spriteFrameData[currentBall], spritePalData[currentBall], spriteMaskData[currentBall], 8);
            }
            drawSprite(bx, by+claw_y,   claw[1+(clawFrame*2)], claw_pal, 4);


    }

    for(int t=0; t<DELTA; t++){
        updateBalls(1);
    }
    drawBalls();
    keepAnimating();
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
    Audio::ADPCMSource::play("22050_16bit_adpcm.wav")->setLoop(true);

    while (_A_But[HELD]){
        updateButtons();
    }
    numBalls = 0;

    while(PC::isRunning()){
        if( !PC::update() ) 
            continue;

        spriteCount = 0;

        updateButtons();

        playLevel();

        char tempText[64];
        sprintf(tempText,"FPS:%d",fpsCount);
        myPrint(0,0,tempText);
        sprintf(tempText,"Got:%d, Get:%d", gotNextBall, gettingNextBall);
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
