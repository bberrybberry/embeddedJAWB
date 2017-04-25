//TODO Docs

#include "drawPokemon.h"

//TODO: Aaron: Explain what this is and tell us if this the correct way to store this
graphics_t gCntx;

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
