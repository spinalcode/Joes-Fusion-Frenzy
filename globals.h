#define spriteColour 128
#define fontColour 251

long int lastMillis;
long int fpsCount;
long int fpsCounter;

// for my own sprite renderer
#define NUMSPRITES 64

struct SPRITE_DATA {
    const uint8_t *imageData; // image data
    const uint8_t *maskData; // image data
    uint8_t paletteOffset; // palette data
    int16_t x;  // x postition
    int16_t y;  // y position
    int16_t scale; // scale of sprite
    int16_t offset; // tile render pixel offset
    uint8_t bit;
    uint8_t hFlip;
} sprites[NUMSPRITES];
int spriteCount = -1;
uint8_t spriteLine[176];

const uint8_t *spriteFrameData[] = {
    joe_01,joe_02,joe_03,joe_04,joe_05,
    joe_06,joe_07,joe_08,joe_09,joe_10,
    joe_11,joe_12
};

// ------- Audio stuff --------
char musicName[] = "22050_16bit_mono.pcm"; 
#define my_TIMER_16_0_IRQn 16          // for Timer setup
#include "timer_11u6x.h"
#include "clock_11u6x.h"

File bgmFile;

#define audioBufferSize 512
unsigned char audioBuffer[2048];
int bufferOffset[4]={ audioBufferSize*3,  0, audioBufferSize, audioBufferSize*2 };

uint8_t currentBuffer = 0;
uint8_t completeBuffer = 0;         // Which section is full
long int audioOffset=0;

// writeDAC() from Pokitto MiniLib
inline void writeDAC(unsigned char out) {
    volatile unsigned char* P1 = (unsigned char*)(0xa0000020);
    volatile unsigned char* P2 = (unsigned char*)(0xa0000040);
    P1[28] = out & 1; out >>= 1;
    P1[29] = out & 1; out >>= 1;
    P1[30] = out & 1; out >>= 1;
    P1[31] = out & 1; out >>= 1;
    P2[20] = out & 1; out >>= 1;
    P2[21] = out & 1; out >>= 1;
    P2[22] = out & 1; out >>= 1;
    P2[23] = out;
}

void audioTimer(void){
	if (Chip_TIMER_MatchPending(LPC_TIMER16_0, 1)) {
        writeDAC(audioBuffer[audioOffset]);
        if(++audioOffset == audioBufferSize*4){
            audioOffset = 0;
        }
        //currentBuffer = audioOffset/audioBufferSize;
        currentBuffer = audioOffset >> 9;

        // last thing we reset the time
    	Chip_TIMER_ClearMatch(LPC_TIMER16_0, 1);
    }
}

// timer init stolen directly from Pokittolib
void initTimer(uint32_t sampleRate){
    /* Initialize 32-bit timer 0 clock */
	Chip_TIMER_Init(LPC_TIMER16_0);
    /* Timer rate is system clock rate */
	uint32_t timerFreq = Chip_Clock_GetSystemClockRate();
	/* Timer setup for match and interrupt at TICKRATE_HZ */
	Chip_TIMER_Reset(LPC_TIMER16_0);
	/* Enable both timers to generate interrupts when time matches */
	Chip_TIMER_MatchEnableInt(LPC_TIMER16_0, 1);
    /* Setup 32-bit timer's duration (32-bit match time) */
	Chip_TIMER_SetMatch(LPC_TIMER16_0, 1, (timerFreq / sampleRate));
	/* Setup both timers to restart when match occurs */
	Chip_TIMER_ResetOnMatchEnable(LPC_TIMER16_0, 1);
	/* Start both timers */
	Chip_TIMER_Enable(LPC_TIMER16_0);
	/* Clear both timers of any pending interrupts */
	NVIC_ClearPendingIRQ((IRQn_Type)my_TIMER_16_0_IRQn);
    /* Redirect IRQ vector - Jonne*/
    NVIC_SetVector((IRQn_Type)my_TIMER_16_0_IRQn, (uint32_t)&audioTimer);
	/* Enable both timer interrupts */
	NVIC_EnableIRQ((IRQn_Type)my_TIMER_16_0_IRQn);
}

// ------- Audio stuff --------


void drawSprite(int x, int y, const uint8_t *imageData, uint8_t paletteOffset, int bit){

    // if out of screen bounds, don't bother
    if(x<-16 || x>220) return;
    if(y<-imageData[1] || y>175) return;

    if(++spriteCount>NUMSPRITES-1)spriteCount=NUMSPRITES-1; // don't overflow the sprite max

    sprites[spriteCount].x = x;
    sprites[spriteCount].y = y;
    sprites[spriteCount].scale = 128;
    sprites[spriteCount].bit = bit;
    sprites[spriteCount].imageData = imageData;
    sprites[spriteCount].paletteOffset = paletteOffset;

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
    drawSprite(x+((x1++)*8), y, guiFont[character], fontColour,2);
  }
}

