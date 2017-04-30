/**
 * @file pokemon
 * @author Breanna Higgins
 * @brief TODO
 * TODO: Everything
 */

#include "pokemon.h"
#include "graphics.h" //needed for types and defines
//#include "pokemonImages.h" //needed to check contents of map
#include "timing.h"

///////////////////////////////////// DEBUG FUNCTS //////////////////////////////////////
//comment out to leave debug mode
//#define DEBUG_MODE1 //test movements
#define DEBUG_MODE2 //test pokemon generation

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

void DEBUG_pokeGeneration(){
	//set defined locations to shaking grass

	uint8_t locX1, locX2, locX3, locY1, locY2, locY3;
	locX1 = 5;
	locY1 = 0;
	locX2 = 1;
	locY2 = 3;
	locX3 = 7;
	locY3 = 8;

	setShakingGrass(locX1, locY1);
}
/////////////////////////////////////////////////////////////////////////////////////////

uint8_t binarySearch(uint8_t arr[], uint8_t item, uint8_t low, uint8_t high){
	if(high <= low){
		return (item > arr[low]) ? low + 1 : low;
	}
	uint8_t mid = (low + high)/2;
	if(item == arr[mid]){
		return ++mid;
	}
	if(item > arr[mid]){
		return binarySearch(arr, item, ++mid, high);
	}

	return binarySearch(arr, item,low, --mid);
}

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
    players[0].status = true;

    //set up menus and text
    initTextBox();

    //set up pokemon for generation
    initPokemon();

    //pause game
    pauseGame();
    //wait for someone to unpause game before starting\

    //set up time and first item/pokemon generations
}

void initMap(){
    drawMap();
}

void initPlayers(){
    //register players 1-4
	volatile int i;
	for(i = 0; i < MAX_PLAYERS; i++){
		players[i].pbCount = 15;
		players[i].gbCount = 10;
		players[i].ubCount = 5;
		players[i].mvmt = false;
		players[i].status = false;
		players[i].score = 0;

		//info different to each unique player define here
		switch(i){
		case 0:
			players[i].sprite = AARON;
			players[i].tileX = PLAYER1_INIT_X;
			players[i].tileY = PLAYER1_INIT_Y;
			break;
		case 1:
			players[i].sprite = BREANNA;
			players[i].tileX = PLAYER2_INIT_X;
			players[i].tileY = PLAYER2_INIT_Y;
			break;
		case 2:
			players[i].sprite = JOSH;
			players[i].tileX = PLAYER3_INIT_X;
			players[i].tileY = PLAYER3_INIT_Y;
			break;
		case 3:
			players[i].sprite = WALT;
			players[i].tileX = PLAYER4_INIT_X;
			players[i].tileY = PLAYER4_INIT_Y;
			break;
		}

		//draw players in init pos
		drawPlayer(players[i].sprite, STAND, players[i].tileX, players[i].tileY);
	}


}

void initPokemon(){
	//TODO: fill pkmnList[] and pkmnWeights as desired
	pkmnList[0].name = "Bulbasaur";
	pkmnList[0].spawnRate = 50;
	pkmnList[0].catchRate = 100;
	pkmnList[0].points = 10;

	//TODO, unhardcode
	pkmnList[1] = pkmnList[0];
	pkmnList[2] = pkmnList[0];
	pkmnList[3] = pkmnList[0];
	pkmnList[4] = pkmnList[0];
	pkmnList[5] = pkmnList[0];

	pkmnWeights[0] = 100;
	pkmnWeights[1] = 100;
	pkmnWeights[2] = 100;
	pkmnWeights[3] = 100;
	pkmnWeights[4] = 100;
	pkmnWeights[5] = 100;
}

void movePlayerUp(uint8_t playerIndex){
	g_point_t initPt;
	initPt.x = players[playerIndex].tileX;
	initPt.y = players[playerIndex].tileY;
	if ((initPt.y - 1) < GRID_Y && //location exists
			players[playerIndex].status && // player is in game
			checkPlayerLocValid(&players[playerIndex], initPt.x, initPt.y -1) //valid location (collision detection)
	) {
		if (map.grid[initPt.x + initPt.y * GRID_X]) {
			//redraw bg tile
			drawStatic(map.grid[initPt.x + initPt.y * GRID_X], &initPt);
		}
		else {
			//TODO: Error state handling: Graphics_DrawTile(&gCntx, p1, &blackTilePtr, TILE_X, TILE_Y);
		}

		drawPlayer(players[playerIndex].sprite, STAND, players[playerIndex].tileX, --players[playerIndex].tileY);
	}
}

void movePlayerDown(uint8_t playerIndex){
	g_point_t initPt;
	initPt.x = players[playerIndex].tileX;
	initPt.y = players[playerIndex].tileY;
	if ((initPt.y + 1) < GRID_Y && //location exists
			players[playerIndex].status && // player is in game
			checkPlayerLocValid(&players[playerIndex], initPt.x, initPt.y +1)  //valid location (collision detection)
	) {
		if (map.grid[initPt.x + initPt.y * GRID_X]) {
			//redraw bg tile
			drawStatic(map.grid[initPt.x + initPt.y * GRID_X], &initPt);
		}
		else {
			//TODO: Error state handling: Graphics_DrawTile(&gCntx, p1, &blackTilePtr, TILE_X, TILE_Y);
		}

		drawPlayer(players[playerIndex].sprite, STAND, players[playerIndex].tileX, ++players[playerIndex].tileY);
	}
}

void movePlayerLeft(uint8_t playerIndex){
	g_point_t initPt;
	initPt.x = players[playerIndex].tileX;
	initPt.y = players[playerIndex].tileY;
	if ((initPt.x - 1) < GRID_X && //location exists
			players[playerIndex].status && // player is in game
			checkPlayerLocValid(&players[playerIndex], initPt.x -1, initPt.y)  //valid location (collision detection)
	) {
		if (map.grid[initPt.x + initPt.y * GRID_X]) {
			//redraw bg tile
			drawStatic(map.grid[initPt.x + initPt.y * GRID_X], &initPt);
		}
		else {
			//TODO: Error state handling: Graphics_DrawTile(&gCntx, p1, &blackTilePtr, TILE_X, TILE_Y);
		}

		drawPlayer(players[playerIndex].sprite, STAND, --players[playerIndex].tileX, players[playerIndex].tileY);
	}
}

void movePlayerRight(uint8_t playerIndex){
	g_point_t initPt;
	initPt.x = players[playerIndex].tileX;
	initPt.y = players[playerIndex].tileY;
	if ((initPt.x + 1) < GRID_X && //location exists
			players[playerIndex].status && // player is in game
			checkPlayerLocValid(&players[playerIndex], initPt.x +1, initPt.y)  //valid location (collision detection)
	) {
		if (map.grid[initPt.x + initPt.y * GRID_X]) {
			//redraw bg tile
			drawStatic(map.grid[initPt.x + initPt.y * GRID_X], &initPt);
		}
		else {
			//TODO: Error state handling: Graphics_DrawTile(&gCntx, p1, &blackTilePtr, TILE_X, TILE_Y);
		}

		drawPlayer(players[playerIndex].sprite, STAND, ++players[playerIndex].tileX, players[playerIndex].tileY);

		//check if encounter occurs
		if(checkShakingGrass(players[playerIndex].tileX, players[playerIndex].tileY)){
			//enter encounter
		}
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
    uint8_t r = 5; //TODO: replace with random num gen
    uint8_t index = binarySearch(pkmnWeights, r, 0, MAX_PKMN);
    switch(index){
    case 0:
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
	default:
		return pkmnList[0];
    }
}

//char checkAllCollisions(char xLoc, char yLoc){
//    //TODO
//    volatile uint8_t i;
//    char collide = 0;
//    for(i = 0; i < 3 && collide != 1; i++){
////        if(player[i].x == xLoc && player[i].y ==yLoc){
////            collide = 1;
////        }
//    }
//    return collide;
//}

bool checkItem(pokePlayer_t player){
    //TODO
}

bool checkPlayerLocValid(pokePlayer_t* player, uint8_t locX, uint8_t locY){
    volatile int i;

    //check if about to hit another player
    for(i = 0; i < MAX_PLAYERS; i++){
    	if(players[i].sprite == player->sprite) continue; //don't collide with yourself

    	if(players[i].tileX == locX && players[i].tileY == locY){
    		return false;
    	}
    }

    //check if running into tree or rock
    if(isTreeTile(locX, locY) || isRockTile(locX, locY)){
    	return false;
    }

    //if you get here, you're good!
    return true;
}

bool checkShakingGrass(uint8_t locX, uint8_t locY){
	return isShakingGrass(locX, locY);
}

void setShakingGrass(uint8_t locX, uint8_t locY){
	//TODO: check that grass is drawn in valid location
	drawGrass(SHAKE, locX, locY);
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



