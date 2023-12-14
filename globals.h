//#define spriteColour 128
//#define fontColour 251
#include "mbed.h"

long int lastMillis;
long int fpsCount;
long int fpsCounter;

// for my own sprite renderer
#define NUMSPRITES 200

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
    //sprites[spriteCount].paletteOffset = paletteOffset;

    // make sure we know there are sprites on these lines
    int y2 = y+sprites[spriteCount].imageData[1];
    for(int t=y; t<y2; t++){
        if(t>=0 && t<176)
            spriteLine[t]=1;
    }
}


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

