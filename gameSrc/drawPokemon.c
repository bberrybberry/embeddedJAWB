//TODO Docs

#include "drawPokemon.h"


void Graphics_Init(graphics_t* gptr) {
    //graphics_t* gptr = &gCntx; //TODO: Aaron, see if you agree with me changing param of init to void and doing this weird pointer thing
    initDisplay();
    Graphics_SetInputScreenSize(gptr, SCREEN_SIZE_320X240);
}

void drawPlayer(playerSprite ps, walkState ws, uint8_t location){
    //TODO
}

void drawGrass(grassState gs, uint8_t location){
    //TODO
}
void drawMap(MapStruct map){
    //adapted from Aaron's code in grTest main::drawMap(void)
    volatile int i, j;
    g_point_t pt;
    for (i = 0; i < GRID_X; i++) {
        for (j = 0; j < GRID_Y; j++) {
            pt.x = i * TILE_X;
            pt.y = j * TILE_Y;
            Graphics_DrawTile(&gCntx, pt, &map.map[i + j * GRID_X], TILE_X, TILE_Y);
        }
    }
}
void drawStatic(/*tile graphics*/){
    //TODO
}
void printMenu(uint8_t playerID, menuState ms, char* text){
    //TODO
}
void printStats(uint8_t time, char* text){
    //TODO
}
