
#define tbt 64
#define TILEWIDTH 8
#define TILEHEIGHT 8

// background line filler
void myBGFiller8bit(std::uint8_t* line, std::uint32_t y, bool skip){

    int32_t x = 0;
    uint32_t tileIndex = (y/TILEWIDTH) * background_map[0];
    uint32_t jStart = (y%TILEWIDTH) *TILEWIDTH; // current line in current tile

    uint32_t lineOffset;
    uint32_t thisTile;
    auto lineP = &line[0];
    auto tilesP = &background_Tiles[0];\

    #define bgTileLine()\
        thisTile = background_map[2+tileIndex++];\
        lineOffset = (thisTile*tbt) + jStart;\
        lineP = &line[x];\
        x+=8;\
        tilesP = &background_Tiles[lineOffset];\
        *lineP++ = *tilesP++;\
        *lineP++ = *tilesP++;\
        *lineP++ = *tilesP++;\
        *lineP++ = *tilesP++;\
        *lineP++ = *tilesP++;\
        *lineP++ = *tilesP++;\
        *lineP++ = *tilesP++;\
        *lineP++ = *tilesP++;

    bgTileLine(); bgTileLine(); bgTileLine(); bgTileLine(); bgTileLine(); 
    bgTileLine(); bgTileLine(); bgTileLine(); bgTileLine(); bgTileLine(); 
    bgTileLine(); bgTileLine(); bgTileLine(); bgTileLine(); bgTileLine(); 
    bgTileLine(); bgTileLine(); bgTileLine(); bgTileLine(); bgTileLine(); 
    bgTileLine(); bgTileLine(); bgTileLine(); bgTileLine(); bgTileLine(); 
    bgTileLine(); bgTileLine(); bgTileLine();
}


void mySpriteFiller8bit(std::uint8_t* line, std::uint32_t y, bool skip){

    if(spriteLine[y]==0) return;

    auto scanLine = &line[0];

    int y2 = y;
    
    spriteLine[y]=0;
    if(spriteCount>=0){
        for(int32_t spriteIndex = 1; spriteIndex<=spriteCount; spriteIndex++){
            auto &sprite = sprites[spriteIndex];
            uint8_t paletteOffset = sprite.paletteOffset;
            if(sprite.bit==2){
                if((int)y >= sprite.y && (int)y < sprite.y + sprite.imageData[1]){
                    if(sprite.x>=0 && sprite.x<PROJ_LCDWIDTH){
                        int sWidth = sprite.imageData[0]/4;
                        uint32_t so = 2+(sWidth * (y2-sprite.y));
                        auto si = &sprite.imageData[so];
                        auto sl = &scanLine[sprite.x];
                        for(int x = sWidth-1; x>=0; x--){
                            auto pixel = si[x];
                            if(((pixel=*si)>>6)&3) *sl = paletteOffset + ((pixel>>6)&3);
                            sl++;
                            if(( pixel     >>4)&3) *sl = paletteOffset + ((pixel>>4)&3);
                            sl++;
                            if(( pixel     >>2)&3) *sl = paletteOffset + ((pixel>>2)&3);
                            sl++;
                            if(( pixel        )&3) *sl = paletteOffset + ((pixel   )&3);
                            sl++;
                            *si++;
                        }
                    } // if X
                } // if Y
            } // 2bpp

            if(sprite.bit==8){
                if((int)y >= sprite.y && (int)y < sprite.y + sprite.imageData[1]){
                    if(sprite.x>=0 && sprite.x<PROJ_LCDWIDTH){
                        int sWidth = sprite.imageData[0];
                        uint32_t so = 2+(sWidth * (y2-sprite.y));
                        auto si = &sprite.imageData[so];
                        auto sl = &scanLine[sprite.x];
                        for(int x = sWidth - 1; x >= 0; x--){
                            auto pixel = si[x];
                            if(pixel) 
                                sl[x] = paletteOffset + pixel;
                        }
                    } // if X
                } // if Y
            } // 8bpp

        } // for spriteCount
    } // sprite count >1

    return;
}


