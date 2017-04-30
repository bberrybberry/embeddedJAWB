/**
 * @file pokemon
 * @author Breanna Higgins
 * @brief TODO
 * TODO: Everything
 */

#include "pokemon.h"
#include "graphics.h" //needed for types and defines

///////////////////////////////////// DEBUG FUNCTS //////////////////////////////////////
//#define DEBUG_MODE //comment out to leave debug mode

pokePlayer_t g_DEBUG_player;

void DEBUG_playerMoveTest();
void DEBUG_movePlayer(uint8_t dir);

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
	g_DEBUG_player.tileY = 9;
	g_DEBUG_player.status = true;
	g_DEBUG_player.mvmt = true;

	//draw player at default loc
	drawPlayer(g_DEBUG_player.sprite, LEFT, g_DEBUG_player.tileX, g_DEBUG_player.tileY);
}

/**
 * move the player in specified direction
 *
 * @param dir: 0 = up, 1 = down, 2 = right, 3 = left
 */
void DEBUG_movePlayer(uint8_t dir){
	g_point_t initPt;
	initPt.x = g_DEBUG_player.tileX;
	initPt.y = g_DEBUG_player.tileY;
	switch(dir){
	case 0: //up
		if ((initPt.y - 1) < GRID_Y ) {
			if (map.grid[initPt.x + initPt.y * GRID_X]) {
				//redraw bg tile
				drawStatic(map.grid[initPt.x + initPt.y * GRID_X], &initPt);
			}
			else {
				//TODO: Error state handling: Graphics_DrawTile(&gCntx, p1, &blackTilePtr, TILE_X, TILE_Y);
			}

			drawPlayer(g_DEBUG_player.sprite, LEFT, g_DEBUG_player.tileX, --g_DEBUG_player.tileY);
		}
		break;
	case 1: //down
		if ((initPt.y + 1) < GRID_Y ) {
			if (map.grid[initPt.x + initPt.y * GRID_X]) {
				//redraw bg tile
				drawStatic(map.grid[initPt.x + initPt.y * GRID_X], &initPt);
			}
			else {
				//TODO: Error state handling: Graphics_DrawTile(&gCntx, p1, &blackTilePtr, TILE_X, TILE_Y);
			}

			drawPlayer(g_DEBUG_player.sprite, LEFT, g_DEBUG_player.tileX, ++g_DEBUG_player.tileY);
		}
		break;
	case 2: //right
		if ((initPt.x + 1) < GRID_X ) {
			if (map.grid[initPt.x + initPt.y * GRID_X]) {
				//redraw bg tile
				drawStatic(map.grid[initPt.x + initPt.y * GRID_X], &initPt);
			}
			else {
				//TODO: Error state handling: Graphics_DrawTile(&gCntx, p1, &blackTilePtr, TILE_X, TILE_Y);
			}

			drawPlayer(g_DEBUG_player.sprite, LEFT, ++g_DEBUG_player.tileX, g_DEBUG_player.tileY);
		}
		break;
	case 3: //left
		if ((initPt.x - 1) < GRID_X ) {
			if (map.grid[initPt.x + initPt.y * GRID_X]) {
				//redraw bg tile
				drawStatic(map.grid[initPt.x + initPt.y * GRID_X], &initPt);
			}
			else {
				//TODO: Error state handling: Graphics_DrawTile(&gCntx, p1, &blackTilePtr, TILE_X, TILE_Y);
			}

			drawPlayer(g_DEBUG_player.sprite, LEFT, --g_DEBUG_player.tileX, g_DEBUG_player.tileY);
		}
		break;
	}
}
/////////////////////////////////////////////////////////////////////////////////////////


void initGame(){
    //set up map
    initMap();

#ifdef DEBUG_MODE
    DEBUG_playerMoveTest();

    return; //exit method immediately while we're debugging things
#endif

    //init players
    initPlayers();
    //TODO: Find dynamic way to know how many players are playing
    players[0]->status = true;

    //set up menus and text
    initTextBox();

    //pause game
    pauseGame();

    //set up time and first item/pokemon generations

    //wait for someone to unpause game before starting
}

void initMap(){
    drawMap();
}

void initPlayers(){
    //register players 1-4
	volatile int i;
	for(i = 0; i < 3; i++){
		players[i]->pbCount = 15;
		players[i]->gbCount = 10;
		players[i]->ubCount = 5;
		players[i]->mvmt = false;
		players[i]->status = false;
		players[i]->score = 0;

		//info different to each unique player define here
		switch(i){
		case 0:
			players[i]->sprite = AARON;
			players[i]->tileX = PLAYER1_INIT_X;
			players[i]->tileY = PLAYER1_INIT_Y;
			break;
		case 1:
			players[i]->sprite = BREANNA;
			players[i]->tileX = PLAYER2_INIT_X;
			players[i]->tileY = PLAYER2_INIT_Y;
			break;
		case 2:
			players[i]->sprite = JOSH;
			players[i]->tileX = PLAYER3_INIT_X;
			players[i]->tileY = PLAYER3_INIT_Y;
			break;
		case 3:
			players[i]->sprite = WALT;
			players[i]->tileX = PLAYER4_INIT_X;
			players[i]->tileY = PLAYER4_INIT_Y;
			break;
		}

		//draw players in init pos
		drawPlayer(players[i]->sprite, STAND, players[i]->tileX, players[i]->tileY);
	}


}

void initTextBox(){
	drawInitMenu();
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

bool checkAllCollisions(uint8_t xLoc, uint8_t yLoc){
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

//void upPressed(controller_buttons_t input, void* player) {
////    static uint8_t right = 0x01;
////
////    if ((t1.y - 1) < GRID_Y ) {
////        if(checkAllCollisions(player->tileX, player->tileY-1)==0){
////        if (map.map[t1.x + t1.y * GRID_X]) {
////            Graphics_DrawTile(&gCntx, p1, &map.map[t1.x + t1.y * GRID_X], TILE_X, TILE_Y);
////        }
////        else {
////            Graphics_DrawTile(&gCntx, p1, &blackTilePtr, TILE_X, TILE_Y);
////        }
////
////        t1.y--;
////        p1.y = t1.y * TILE_Y;
////        //Graphics_DrawTile(&gCntx, p1, &gPSTilePtr, TILE_X, TILE_Y);
////        Graphics_DrawTile(&gCntx, p1, right ? &aaronRTilePtr : &aaronLTilePtr, TILE_X, TILE_Y);
////        right ^= 0x01;
////    }
////    }
//}
static char checkCollision(char xLoc, char yLoc){
}



