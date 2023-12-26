//#define spriteColour 128
//#define fontColour 251
#include "mbed.h"
using Fract = SQ15x16;
#define MAX_BALLS 100
#define DAMPING 0.00001
#define GRAVITY 0.075
#define SPEED 1
#define TWO_PI (3.14159 * 2)
#define DELTA 4

long int lastMillis;
long int fpsCount;
long int fpsCounter;

// for my own sprite renderer
#define NUMSPRITES 200

uint8_t curExplode=0;
bool stillAnimating = false;
uint8_t animCount = 0;

struct SPRITE_DATA {
    const uint8_t *imageData; // image data
    const uint8_t *maskData; // mask data
    const uint16_t *paletteData; // image data
    uint8_t paletteOffset; // palette data
    uint8_t x;  // x postition
    uint8_t y;  // y position
    uint8_t offset; // tile render pixel offset
    uint8_t bit;
} sprites[NUMSPRITES];
int spriteCount = -1;
uint8_t spriteLine[176];

struct animData {
    uint8_t x;  // x postition
    uint8_t y;  // y position
    uint8_t frameNumber; // which ball?
    uint8_t frame;
    uint8_t count;
} anims[2];

uint8_t newBallX;
uint8_t newBallY;
uint8_t newBallRad;
uint8_t newBallFrame;

int numBalls = 0;

typedef struct {
    Fract x, y;
    Fract px, py;
    Fract fx, fy;
    int radius;
    int frameNumber;
} Ball;

Ball balls[MAX_BALLS];
int ballRad[] = {4, 5, 7, 8, 11, 14, 16, 19, 22, 27, 32};

uint8_t quad[4][MAX_BALLS];
uint8_t qCount[4];

uint8_t canvasLeft = 48;
uint8_t canvasRight = 151;
uint8_t canvasBottom = 160;


const uint8_t *spriteFrameData[] = {
    joe_01,joe_02,joe_03,joe_04,joe_05,
    joe_06,joe_07,joe_08,joe_09,joe_10,
    joe_11
};

const uint16_t *spritePalData[] = {
    joe_01_pal,joe_02_pal,joe_03_pal,joe_04_pal,joe_05_pal,
    joe_06_pal,joe_07_pal,joe_08_pal,joe_09_pal,joe_10_pal,
    joe_11_pal
};

const uint8_t *spriteMaskData[] = {
    joe_01_mask,joe_02_mask,joe_03_mask,joe_04_mask,joe_05_mask,
    joe_06_mask,joe_07_mask,joe_08_mask,joe_09_mask,joe_10_mask,
    joe_11_mask
};

const uint8_t *spriteBurstData[] = {
	burst_01[0], burst_01[1], burst_01[2], burst_01[3],
	burst_02[0], burst_02[1], burst_02[2], burst_02[3],
	burst_03[0], burst_03[1], burst_03[2], burst_03[3],
	burst_04[0], burst_04[1], burst_04[2], burst_04[3],
	burst_05[0], burst_05[1], burst_05[2], burst_05[3],
	burst_06[0], burst_06[1], burst_06[2], burst_06[3],
	burst_07[0], burst_07[1], burst_07[2], burst_07[3],
	burst_08[0], burst_08[1], burst_08[2], burst_08[3],
	burst_09[0], burst_09[1], burst_09[2], burst_09[3],
	burst_10[0], burst_10[1], burst_10[2], burst_10[3],
	burst_11[0], burst_11[1], burst_11[2], burst_11[3],
};


void drawSprite(int x, int y, const uint8_t *imageData, const uint16_t *paletteData, int bit){

    // if out of screen bounds, don't bother
    if(x<-16 || x>220) return;
    if(y<-imageData[1] || y>175) return;

    if(++spriteCount>NUMSPRITES-1)spriteCount=NUMSPRITES-1; // don't overflow the sprite max

    sprites[spriteCount].x = x;
    sprites[spriteCount].y = y;
    sprites[spriteCount].bit = bit;
    sprites[spriteCount].imageData = imageData;
    sprites[spriteCount].paletteData = paletteData;
    sprites[spriteCount].maskData = NULL;
    //sprites[spriteCount].paletteOffset = paletteOffset;

    // make sure we know there are sprites on these lines
    int y2 = y+sprites[spriteCount].imageData[1];
    for(int t=y; t<y2; t++){
        if(t>=0 && t<176)
            spriteLine[t]=1;
    }
}


// print text
void myPrint(char x, char y, const char* text) {
  uint8_t numChars = strlen(text);
  uint8_t x1 = 0;//2+x+28*y;
  for (uint8_t t = 0; t < numChars; t++) {
    uint8_t character = text[t];
    drawSprite(x+((x1++)*8), y, guiFont[character], font_pal,2);
  }
}

void drawMaskedSprite(int x, int y, const uint8_t *imageData, const uint16_t *paletteData, const uint8_t *maskData, int bit){

    // if out of screen bounds, don't bother
    if(x<-16 || x>220) return;
    //if(y<-imageData[1] || y>175) return;

    if(++spriteCount>NUMSPRITES-1)spriteCount=NUMSPRITES-1; // don't overflow the sprite max

    sprites[spriteCount].x = x;
    sprites[spriteCount].y = y;
    sprites[spriteCount].bit = bit;
    sprites[spriteCount].imageData = imageData;
    sprites[spriteCount].paletteData = paletteData;
    if(maskData != NULL)
        sprites[spriteCount].maskData = maskData;

    // make sure we know there are sprites on these lines
    int y2 = y+sprites[spriteCount].imageData[1];
    for(int t=y; t<y2; t++){
        if(t>=0 && t<176)
            spriteLine[t]=1;
    }
}



void startExplosion(int x, int y, uint8_t frameNumber){

    anims[curExplode].x = x;
    anims[curExplode].y = y;
    anims[curExplode].frameNumber = frameNumber;
    anims[curExplode].frame = 0;
    animCount = 2;
    curExplode = 1-curExplode;
}

void keepAnimating(){

    stillAnimating = false;
    if(animCount > 0){
        for(int t=0; t<2; t++){
            if(anims[t].frame<4){
                stillAnimating = true;
                drawMaskedSprite(anims[t].x, anims[t].y, spriteFrameData[anims[t].frameNumber], spritePalData[anims[t].frameNumber], spriteBurstData[anims[t].frame + anims[t].frameNumber*4], 8);
            }
        }
        animCount--;
        if(animCount==0){
            anims[0].frame++;
            anims[1].frame++;
            animCount=2;
        }
    }

    if(anims[0].frame==4 && stillAnimating==true){
        // create a new ball in their place
        if(newBallX >=0){
            balls[numBalls].x = newBallX;
            balls[numBalls].y = newBallY;
            balls[numBalls].px = newBallX;
            balls[numBalls].py = newBallY;
            balls[numBalls].fx = 0;
            balls[numBalls].fy = 0;
            balls[numBalls].frameNumber = newBallFrame;
            balls[numBalls].radius = newBallRad;
            numBalls++;
        }
    }


}


