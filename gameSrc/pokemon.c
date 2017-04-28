/**
 * @file pokemon
 * @author Breanna Higgins
 * @brief TODO
 * TODO: Everything
 */

#include "pokemon.h"
#include "graphics.h"
//#include "pokemonImages.h"

///////////////////////////////////// DEBUG FUNCTS //////////////////////////////////////
#define DEBUG_MODE //comment out to leave debug mode

pokePlayer_t g_DEBUG_player;

void DEBUG_playerMoveTest();
void DEBUG_movePlayer(uint8_t dir, pokePlayer_t player);

/**
 * set up move player test
 */
void DEBUG_playerMoveTest(){
	//set up default player
	g_DEBUG_player.sprite = BREANNA;
	g_DEBUG_player.pbCount = 10;
	g_DEBUG_player.gbCount = 10;
	g_DEBUG_player.ubCount = 10;
	g_DEBUG_player.score = 123;
	g_DEBUG_player.tileX = 5;
	g_DEBUG_player.tileY = 5;
	g_DEBUG_player.status = true;
	g_DEBUG_player.mvmt = true;

	//draw player at default loc
	drawPlayer(g_DEBUG_player.sprite, LEFT, g_DEBUG_player.tileX, g_DEBUG_player.tileY);
}

/**
 * move the player in specified direction
 *
 * @param dir: 0 = up, 1 = down, 2 = right, 3 = left
 * @param player: poke player struct
 */
void DEBUG_movePlayer(uint8_t dir, pokePlayer_t player){
	g_point_t initPt;
	initPt.x = player.tileX;
	initPt.y = player.tileY;
	switch(dir){
	case 0: //up

		break;
	case 1: //down

		break;
	case 2: //right

		break;
	case 3: //left

		break;
	}
}
/////////////////////////////////////////////////////////////////////////////////////////


void initGame(){

    //draw initial game
    //initDrawGraphics();

    //set up map
    initMap();

#ifdef DEBUG_MODE
    DEBUG_playerMoveTest();

    return; //exit method immediately while we're debugging things
#endif

    //init players
    initPlayers();

    //set up menus and text
    initTextBox();

    //pause game
    pauseGame();

    //set up time and first item/pokemon generations

    //wait for someone to unpause game before starting
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
    drawMap();
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
//        if(player[i].x == xLoc && player[i].y ==yLoc){
//            collide = 1;
//        }
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
//    static uint8_t right = 0x01;
//
//    if ((t1.y - 1) < GRID_Y ) {
//        if(checkAllCollisions(player->tileX, player->tileY-1)==0){
//        if (map.map[t1.x + t1.y * GRID_X]) {
//            Graphics_DrawTile(&gCntx, p1, &map.map[t1.x + t1.y * GRID_X], TILE_X, TILE_Y);
//        }
//        else {
//            Graphics_DrawTile(&gCntx, p1, &blackTilePtr, TILE_X, TILE_Y);
//        }
//
//        t1.y--;
//        p1.y = t1.y * TILE_Y;
//        //Graphics_DrawTile(&gCntx, p1, &gPSTilePtr, TILE_X, TILE_Y);
//        Graphics_DrawTile(&gCntx, p1, right ? &aaronRTilePtr : &aaronLTilePtr, TILE_X, TILE_Y);
//        right ^= 0x01;
//    }
//    }
}
static char checkCollision(char xLoc, char yLoc){
}



