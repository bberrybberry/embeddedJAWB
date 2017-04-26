/**
 * @file pokemon
 * @author Breanna Higgins
 * @brief TODO
 * TODO: Everything
 */

#include "pokemon.h"
#include "graphics.h"
//#include "pokemonImages.h"
static pokePlayer_t player[MAX_PLAYERS]; //player[0] corresponds to player 1, player[1] to 2 and so on

void initGame(){

    //draw initial game
    initDrawGraphics();

    //set up map
    initMap();

    //init players
    initPlayers();

    //set up menus and text
    initTextBox();

    //pause game
    pauseGame();

    //set up time and first item/pokemon generations

    //wait for someone to unpause game before starting
    volatile uint8_t i;
    for(i = 0; i<MAX_PLAYERS; i++){
        /*if(i==0){
            player[i].status = false;
        } else {
            player[i].status = true;
        }*/
        switch(i){
        case 0:
            player[i].sprite = AARON;
            player[i].tileX  = 4;
            player[i].tileY  = 9;
            player[i].status = true;
            break;
        case 1:
            player[i].sprite = BREANNA;
            player[i].tileX  = 5;
            player[i].tileY  = 10;
            player[i].status = false;
            break;
        case 2:
            player[i].sprite = JOSH;
            player[i].tileX  = 5;
            player[i].tileY  = 9;
            player[i].status   = true;
            break;
        case 3:
            player[i].sprite = WALT;
            player[i].tileX  = 4;
            player[i].tileY  = 10;
            player[i].status = false;
            break;
        }
        player[i].pbCount = 5;
        player[i].gbCount = 3;
        player[i].ubCount = 1;
        player[i].mvmt    = true;
    }
}

void initMap(){
    //fill map structure with world map
//    map = (MapStruct){grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, rocksTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr,
//                grassTilePtr, grassTilePtr, treesTilePtr, treesTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr,
//                grassTilePtr, grassTilePtr, treesTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, treesTilePtr, treesTilePtr, grassTilePtr,
//                grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, treesTilePtr, rocksTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, treesTilePtr, grassTilePtr,
//                grassTilePtr, rocksTilePtr, grassTilePtr, goundTilePtr, goundTilePtr, goundTilePtr, goundTilePtr, goundTilePtr, goundTilePtr, grassTilePtr, treesTilePtr, grassTilePtr,
//                grassTilePtr, grassTilePtr, goundTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, goundTilePtr, grassTilePtr, grassTilePtr,
//                grassTilePtr, goundTilePtr, treesTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, treesTilePtr, grassTilePtr, grassTilePtr, goundTilePtr, grassTilePtr,
//                grassTilePtr, goundTilePtr, treesTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, goundTilePtr, grassTilePtr,
//                goundTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, goundTilePtr,
//                goundTilePtr, goundTilePtr, goundTilePtr, goundTilePtr, rocksTilePtr, goundTilePtr, goundTilePtr, rocksTilePtr, goundTilePtr, goundTilePtr, goundTilePtr, goundTilePtr,
//                goundTilePtr, goundTilePtr, goundTilePtr, goundTilePtr, rocksTilePtr, goundTilePtr, goundTilePtr, rocksTilePtr, goundTilePtr, goundTilePtr, goundTilePtr, goundTilePtr,
//                goundTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, goundTilePtr,
//                grassTilePtr, goundTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, goundTilePtr, grassTilePtr,
//                grassTilePtr, goundTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, treesTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, goundTilePtr, grassTilePtr,
//                grassTilePtr, grassTilePtr, goundTilePtr, grassTilePtr, grassTilePtr, rocksTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, goundTilePtr, grassTilePtr, grassTilePtr,
//                grassTilePtr, treesTilePtr, grassTilePtr, goundTilePtr, goundTilePtr, goundTilePtr, goundTilePtr, goundTilePtr, goundTilePtr, grassTilePtr, rocksTilePtr, treesTilePtr,
//                grassTilePtr, rocksTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr,
//                grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, rocksTilePtr, grassTilePtr, grassTilePtr, treesTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr,
//                grassTilePtr, treesTilePtr, treesTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, treesTilePtr, treesTilePtr, grassTilePtr, grassTilePtr, grassTilePtr,
//                grassTilePtr, grassTilePtr, treesTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, treesTilePtr, grassTilePtr, grassTilePtr, grassTilePtr, grassTilePtr
//    };

    //draw map
    drawMap(map);
}

void initPlayers(){
    //TODO

    //register players 1-4

    //draw players in init pos
}

void initTextBox(){
    //TODO
}

void playGame(){
    //TODO
}

void pauseGame(){
    //TODO

    //TODO: How to access game variable from pokemonGame to set state to pause
}

pokemon_t generatePokemon(){
    //TODO
}

void updatePlayerLoc(pokePlayer_t player){
    //TODO
}

char checkAllCollisions(char xLoc, char yLoc){
    //TODO
    volatile uint8_t i;
    char collide = 0;
    for(i = 0; i < 3 && collide != 1; i++){
        if(player[i].tileX == xLoc && player[i].tileY ==yLoc){
            collide = 1;
        }
    }
    return collide;
}

bool checkItem(pokePlayer_t player){
    //TODO
}

bool checkPlayerLocValid(pokePlayer_t player){
    //TODO
}

bool checkGrass(pokePlayer_t player){
    //TODO
}

void updateGrass(uint8_t location){
    //TODO
}

void updateTime(uint8_t time){
    //TODO
}

void updateScores(pokePlayer_t player, uint8_t score){
    //TODO
}

void runEncounter(){
    //TODO
}

void generateItems(){
    //TODO
}

void upPressed(controller_buttons_t input, void* player) {
    static uint8_t right = 0x01;
    //player->position
    /*if ((t1.y - 1) < GRID_Y ) {
        if(checkAllCollisions(player->tileX, player->tileY-1)==0){
        if (map.map[t1.x + t1.y * GRID_X]) {
            Graphics_DrawTile(&gCntx, p1, &map.map[t1.x + t1.y * GRID_X], TILE_X, TILE_Y);
        }
        else {
            Graphics_DrawTile(&gCntx, p1, &blackTilePtr, TILE_X, TILE_Y);
        }

        t1.y--;
        p1.y = t1.y * TILE_Y;
        //Graphics_DrawTile(&gCntx, p1, &gPSTilePtr, TILE_X, TILE_Y);
        Graphics_DrawTile(&gCntx, p1, right ? &aaronRTilePtr : &aaronLTilePtr, TILE_X, TILE_Y);
        right ^= 0x01;
    }
    }*/
}
