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
#include "random_int.h"

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
	setShakingGrass(locX2, locY2);
	setShakingGrass(locX3, locY3);
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

#ifdef DEBUG_MODE1
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

#ifdef DEBUG_MODE2
    DEBUG_pokeGeneration();
#endif

    //pause game
    //pauseGame();
    //wait for someone to unpause game before starting\

    //set up time and first item/pokemon generations
}

void initMap(){
    drawMap();
}
//TODO create initPkmn()
void initPlayers(){
    //register players 1-4
	volatile int i;
	for(i = 0; i < MAX_PLAYERS; i++){
		players[i].pbCount = 15;
		players[i].gbCount = 10;
		players[i].ubCount = 5;
		players[i].mvmt = true;
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
	pkmnList[0].name = "Chansey";
	pkmnList[0].spawnRate = 1;
	pkmnList[0].catchRate = 30;
	pkmnList[0].points = 60;

	pkmnList[1].name = "Gyrados";
	pkmnList[1].spawnRate = 4;
	pkmnList[1].catchRate = 45;
	pkmnList[1].points = 50;

    pkmnList[2].name = "Jigglypuff";
    pkmnList[2].spawnRate = 10;
    pkmnList[2].catchRate = 45;
    pkmnList[2].points = 40;

    pkmnList[3].name = "Growlithe";
    pkmnList[3].spawnRate = 25;
    pkmnList[3].catchRate = 170;
    pkmnList[3].points = 30;

    pkmnList[4].name = "Pikachu";
    pkmnList[4].spawnRate = 25;
    pkmnList[4].catchRate = 190;
    pkmnList[4].points = 20;

    pkmnList[5].name = "Pidgey";
    pkmnList[5].spawnRate = 35;
    pkmnList[5].catchRate = 255;
    pkmnList[5].points = 10;
	//TODO, unhardcode
	/*pkmnList[1] = pkmnList[0];
	pkmnList[2] = pkmnList[0];
	pkmnList[3] = pkmnList[0];
	pkmnList[4] = pkmnList[0];
	pkmnList[5] = pkmnList[0];

	pkmnWeights[0] = 100;
	pkmnWeights[1] = 100;
	pkmnWeights[2] = 100;
	pkmnWeights[3] = 100;
	pkmnWeights[4] = 100;
	pkmnWeights[5] = 100;*/
    volatile uint8_t i;
    for(i = 0; i<MAX_PKMN; i++){
        if(i==0)
        pkmnWeights[i] = pkmnList[i].spawnRate;
        else
            pkmnWeights[i] = pkmnList[i].spawnRate+pkmnList[i-1].spawnRate;
    }
}
void initItems(){
    itemWeights[0] = 10;
    itemWeights[1] = 40;
    itemWeights[2] = 50;
}
void movePlayerUp(uint8_t playerIndex){
	g_point_t initPt;
	initPt.x = players[playerIndex].tileX;
	initPt.y = players[playerIndex].tileY;
	if ((initPt.y - 1) < GRID_Y && //location exists
			players[playerIndex].status && // player is in game
			players[playerIndex].mvmt && //player is in moving state
			checkPlayerLocValid(&players[playerIndex], initPt.x, initPt.y -1) //valid location (collision detection)
	) {
		//need to check for encounter before drawing otherwise you may walk over and redraw plain grass
		bool encounterFound = checkShakingGrass(players[playerIndex].tileX, players[playerIndex].tileY -1);
        bool itemFound = checkItemLoc(players[playerIndex].tileX, players[playerIndex].tileY+1);
		if (map.grid[initPt.x + initPt.y * GRID_X]) {
			//redraw bg tile
			drawStatic(map.grid[initPt.x + initPt.y * GRID_X], &initPt);
		}
		else {
			//TODO: Error state handling: Graphics_DrawTile(&gCntx, p1, &blackTilePtr, TILE_X, TILE_Y);
		}

		drawPlayer(players[playerIndex].sprite, STAND, players[playerIndex].tileX, --players[playerIndex].tileY);

		//check if encounter occurs
		if(encounterFound){
			//enter encounter
			runEncounter(playerIndex);
		}
		if(itemFound){
		    itemSpawn(playerIndex);
		}
	}
}

void movePlayerDown(uint8_t playerIndex){
	g_point_t initPt;
	initPt.x = players[playerIndex].tileX;
	initPt.y = players[playerIndex].tileY;
	if ((initPt.y + 1) < GRID_Y && //location exists
			players[playerIndex].status && // player is in game
			players[playerIndex].mvmt && //player is in moving state
			checkPlayerLocValid(&players[playerIndex], initPt.x, initPt.y +1)  //valid location (collision detection)
	) {
		//need to check for encounter before drawing otherwise you may walk over and redraw plain grass
		bool encounterFound = checkShakingGrass(players[playerIndex].tileX, players[playerIndex].tileY +1);
		bool itemFound = checkItemLoc(players[playerIndex].tileX, players[playerIndex].tileY+1);
		if (map.grid[initPt.x + initPt.y * GRID_X]) {
			//redraw bg tile
			drawStatic(map.grid[initPt.x + initPt.y * GRID_X], &initPt);
		}
		else {
			//TODO: Error state handling: Graphics_DrawTile(&gCntx, p1, &blackTilePtr, TILE_X, TILE_Y);
		}

		drawPlayer(players[playerIndex].sprite, STAND, players[playerIndex].tileX, ++players[playerIndex].tileY);

		//check if encounter occurs
		if(encounterFound){
			//enter encounter
			runEncounter(playerIndex);
		}
		if(itemFound){
		    itemSpawn(playerIndex);
		}
	}
}

void movePlayerLeft(uint8_t playerIndex){
	g_point_t initPt;
	initPt.x = players[playerIndex].tileX;
	initPt.y = players[playerIndex].tileY;
	if ((initPt.x - 1) < GRID_X && //location exists
			players[playerIndex].status && // player is in game
			players[playerIndex].mvmt && //player is in moving state
			checkPlayerLocValid(&players[playerIndex], initPt.x -1, initPt.y)  //valid location (collision detection)
	) {
		//need to check for encounter before drawing otherwise you may walk over and redraw plain grass
		bool encounterFound = checkShakingGrass(players[playerIndex].tileX -1, players[playerIndex].tileY);
		bool itemFound = checkItemLoc(players[playerIndex].tileX -1, players[playerIndex].tileY);
		if (map.grid[initPt.x + initPt.y * GRID_X]) {
			//redraw bg tile
			drawStatic(map.grid[initPt.x + initPt.y * GRID_X], &initPt);
		}
		else {
			//TODO: Error state handling: Graphics_DrawTile(&gCntx, p1, &blackTilePtr, TILE_X, TILE_Y);
		}

		drawPlayer(players[playerIndex].sprite, STAND, --players[playerIndex].tileX, players[playerIndex].tileY);

		//check if encounter occurs
		if(encounterFound){
			//enter encounter
			runEncounter(playerIndex);
		}
		if(itemFound){
		    itemSpawn(playerIndex);

		}
	}
}

void movePlayerRight(uint8_t playerIndex){
	g_point_t initPt;
	initPt.x = players[playerIndex].tileX;
	initPt.y = players[playerIndex].tileY;
	if ((initPt.x + 1) < GRID_X && //location exists
			players[playerIndex].status && // player is in game
			players[playerIndex].mvmt && //player is in moving state
			checkPlayerLocValid(&players[playerIndex], initPt.x +1, initPt.y)  //valid location (collision detection)
	) {
		//need to check for encounter before drawing otherwise you may walk over and redraw plain grass
		bool encounterFound = checkShakingGrass(players[playerIndex].tileX +1, players[playerIndex].tileY);
		bool itemFound = checkItemLoc(players[playerIndex].tileX +1, players[playerIndex].tileY);
		if (map.grid[initPt.x + initPt.y * GRID_X]) {
			//redraw bg tile
			drawStatic(map.grid[initPt.x + initPt.y * GRID_X], &initPt);
		}
		else {
			//TODO: Error state handling: Graphics_DrawTile(&gCntx, p1, &blackTilePtr, TILE_X, TILE_Y);
		}

		drawPlayer(players[playerIndex].sprite, STAND, ++players[playerIndex].tileX, players[playerIndex].tileY);

		//check if encounter occurs
		if(encounterFound){
			//enter encounter
			runEncounter(playerIndex);
		}
		if(itemFound){
		    itemSpawn(playerIndex);
		}
	}
}


void initTextBox(){
	drawInitMenu();
}

void playGame(){
    //TODO
}

void pauseGame(){
    //TODO
}

void generateShakingGrass(void) {
	uint8_t x, y;
	volatile int i;
	bool display = false;

	while(!display) {
		x = random_int(0, GRID_X - 1);
		y = random_int(0, GRID_Y - 1);
		display = true;
		if (!isGrass(x, y)) {
			display = false;
		}
		if (checkShakingGrass(x, y)) {
			display = false;
		}
		for (i = 0; i < MAX_PLAYERS; i++) {
			if ((x == players[i].tileX) && (y == players[i].tileY)) {
				display = false;
			}
		}
	}

	setShakingGrass(x, y);
}

pokemon_t* generatePokemon(){
    uint8_t r = random_int(0, 100); //TODO: replace with random num gen
    uint8_t index = binarySearch(pkmnWeights, r, 0, MAX_PKMN);
    if(index<MAX_PKMN)
        return &pkmnList[index];
    else
        return &pkmnList[5];
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
	if (locX < GRID_X && locY < GRID_Y) {
		return isShakingGrass(locX, locY);
	}
	else {
		return false;
	}
}

void setShakingGrass(uint8_t locX, uint8_t locY){
	if (locX < GRID_X && locY < GRID_Y) {
		drawGrass(SHAKE, locX, locY);
	}
}

void updateTime(uint8_t time){
    printStats(time, "");
}

void updateScores(uint8_t playerID, uint8_t score){
    printScore(playerID, score);
}

void runEncounter(uint8_t playerInd){
    //stop player movement
	players[playerInd].mvmt = false;

	//print pokemon
	players[playerInd].encountered = generatePokemon();
	printPokemon(playerInd, FOUND_MSG, players[playerInd].encountered->name);

	//change menu
	printMenu(playerInd, RUN_BALL, -1, -1, -1, "");
}

void selectRun(uint8_t player){
	if(players[player].mvmt == false){
		//end encounter
		players[player].mvmt = true;

		//clear menu
		printPokemon(player, NONE_MSG, "");
		printMenu(player, NONE, -1, -1, -1, "");

		//remove shaking grass
		drawGrass(GRASS, players[player].tileX, players[player].tileY);

		//redraw player
		drawPlayer(players[player].sprite, STAND, players[player].tileX, players[player].tileY);
	}
}

void selectBall(uint8_t player){
	if(players[player].mvmt == false){
		//change menu to ball select
		//circularly define one as only pos to optionally display them
		players[player].pbCount *= 1;
		players[player].gbCount *= -1;
		players[player].ubCount *= -1;
		printMenu(player, BALL_SELECT, players[player].pbCount, players[player].gbCount, players[player].ubCount, "Poke balls");

	}
}

void leftBallOption(uint8_t player){
	if(players[player].mvmt == false && //player is in menu state
			(players[player].pbCount < 0 || players[player].gbCount < 0 ||players[player].ubCount < 0) //player has negative balls meaning player is in ball select options
			){
		if(players[player].pbCount > 0 ){ //has balls and is selected
			//move selection to ub, if possible, else gb, else nothing
			if(players[player].ubCount != 0){
				players[player].pbCount *= -1; //make curr negative
				players[player].ubCount *= -1; //make curr not negative, becomes new curr
				printMenu(player, BALL_SELECT, players[player].pbCount, players[player].gbCount, players[player].ubCount, "Ultra balls");

			}
			else if(players[player].gbCount != 0){
				players[player].pbCount *= -1; //make curr negative
				players[player].gbCount *= -1; //make curr not negative, becomes new curr
				printMenu(player, BALL_SELECT, players[player].pbCount, players[player].gbCount, players[player].ubCount, "Great balls");

			}
		}
		else if(players[player].gbCount > 0){
			//move selection to pb if possible, else ub, else nothing
			if(players[player].pbCount != 0){
				players[player].gbCount *= -1; //make curr negative
				players[player].pbCount *= -1; //make curr not negative, becomes new curr
				printMenu(player, BALL_SELECT, players[player].pbCount, players[player].gbCount, players[player].ubCount, "Poke balls");

			}
			else if(players[player].ubCount != 0){
				players[player].gbCount *= -1; //make curr negative
				players[player].ubCount *= -1; //make curr not negative, becomes new curr
				printMenu(player, BALL_SELECT, players[player].pbCount, players[player].gbCount, players[player].ubCount, "Ultra balls");

			}
		}
		else if(players[player].ubCount > 0){
			//move selection to gb, if possible, else pb, else nothing
			if(players[player].gbCount != 0){
				players[player].ubCount *= -1; //make curr negative
				players[player].gbCount *= -1; //make curr not negative, becomes new curr
				printMenu(player, BALL_SELECT, players[player].pbCount, players[player].gbCount, players[player].ubCount, "Great balls");

			}
			else if(players[player].pbCount != 0){
				players[player].ubCount *= -1; //make curr negative
				players[player].pbCount *= -1; //make curr not negative, becomes new curr
				printMenu(player, BALL_SELECT, players[player].pbCount, players[player].gbCount, players[player].ubCount, "Poke balls");

			}
		}
	}
}

void rightBallOption(uint8_t player){
	if(players[player].mvmt == false && //player is in menu state
			(players[player].pbCount < 0 || players[player].gbCount < 0 ||players[player].ubCount < 0) //player has negative balls meaning player is in ball select options
			){
		if(players[player].pbCount > 0 ){ //has balls and is selected
			//move selection to gb, if possible, else ub, else nothing
			if(players[player].gbCount != 0){
				players[player].pbCount *= -1; //make curr negative
				players[player].gbCount *= -1; //make curr not negative, becomes new curr
				printMenu(player, BALL_SELECT, players[player].pbCount, players[player].gbCount, players[player].ubCount, "Great balls");

			}
			else if(players[player].ubCount != 0){
				players[player].pbCount *= -1; //make curr negative
				players[player].ubCount *= -1; //make curr not negative, becomes new curr
				printMenu(player, BALL_SELECT, players[player].pbCount, players[player].gbCount, players[player].ubCount, "Ultra balls");

			}
		}
		else if(players[player].gbCount > 0){
			//move selection to ub if possible, else pb, else nothing
			if(players[player].ubCount != 0){
				players[player].gbCount *= -1; //make curr negative
				players[player].ubCount *= -1; //make curr not negative, becomes new curr
				printMenu(player, BALL_SELECT, players[player].pbCount, players[player].gbCount, players[player].ubCount, "Ultra balls");

			}
			else if(players[player].pbCount != 0){
				players[player].gbCount *= -1; //make curr negative
				players[player].pbCount *= -1; //make curr not negative, becomes new curr
				printMenu(player, BALL_SELECT, players[player].pbCount, players[player].gbCount, players[player].ubCount, "Poke balls");

			}
		}
		else if(players[player].ubCount > 0){
			//move selection to pb, if possible, else gb, else nothing
			if(players[player].pbCount != 0){
				players[player].ubCount *= -1; //make curr negative
				players[player].pbCount *= -1; //make curr not negative, becomes new curr
				printMenu(player, BALL_SELECT, players[player].pbCount, players[player].gbCount, players[player].ubCount, "Poke balls");

			}
			else if(players[player].gbCount != 0){
				players[player].ubCount *= -1; //make curr negative
				players[player].gbCount *= -1; //make curr not negative, becomes new curr
				printMenu(player, BALL_SELECT, players[player].pbCount, players[player].gbCount, players[player].ubCount, "Great balls");

			}
		}
	}
}

void throwBall(uint8_t player){
    uint8_t catchRate = players[player].encountered->catchRate;
	if(players[player].mvmt == false && //player is in menu state
			(players[player].pbCount < 0 || players[player].gbCount < 0 ||players[player].ubCount < 0) //player has negative balls meaning player is in ball select options
			){
		if(players[player].pbCount > 0 ){ //has balls and is selected
			--players[player].pbCount;
			if(players[player].pbCount < 0 ) players[player].pbCount = 0; //don't let count fall below zero
			captureEvent(player, 1, catchRate);
		}
		else if(players[player].gbCount > 0){
			--players[player].gbCount;
			if(players[player].gbCount < 0 ) players[player].gbCount = 0; //don't let count fall below zero
			captureEvent(player, 2, catchRate);
		}
		else if(players[player].ubCount > 0){
			--players[player].ubCount;
			if(players[player].ubCount < 0 ) players[player].ubCount = 0; //don't let count fall below zero
			captureEvent(player, 3, catchRate);
		}

		//change negative values to positive to exit this state
		if(players[player].pbCount < 0 ){
			players[player].pbCount *= -1;
		}
		if(players[player].gbCount < 0){
			players[player].gbCount *= -1;
		}
		if(players[player].ubCount < 0){
			players[player].ubCount *= -1;
		}

		//resume movement
		players[player].mvmt = true;

	}
}

void captureEvent(uint8_t player, uint8_t multiplier, uint8_t catchRate){
	//try to catch pokemon
	//throw ball at encountered pokemon
	//int rand = random_int(1, 100); //TODO: Random numbers
	uint8_t thresh = random_int(1, 32);

    uint8_t catchValue = catchRate*multiplier;
    uint16_t catch = CATCH_CHECK_1 / (CATCH_CHECK_2 / catchValue);


	if(catch < thresh){
		players[player].score += players[player].encountered->points;
		printScore(player, players[player].score);
		printPokemon(player, CAUGHT_MSG, players[player].encountered->name);
		players[player].encountered = 0;
	}
	else{
		printPokemon(player, RAN_MSG, players[player].encountered->name);
		players[player].encountered = 0;
	}

	//clear menu
	printMenu(player, NONE, -1, -1, -1, "");

	//remove shaking grass
	drawGrass(GRASS, players[player].tileX, players[player].tileY);
	//redraw player
	drawPlayer(players[player].sprite, STAND, players[player].tileX, players[player].tileY);
}

void generateItems(uint8_t locX, uint8_t locY){
    //TODO
    if (locX < GRID_X && locY < GRID_Y) {
    //    drawGrass(SHAKE, locX, locY);
    }
}
void itemSpawn(uint8_t playerInd){
    uint8_t r = random_int(0, 100); //TODO: replace with random num gen
    uint8_t index = binarySearch(itemWeights, r, 0, MAX_ITEMS);
    switch(index) {
    case 0:
        players[playerInd].ubCount++;
        break;
    case 1:
        players[playerInd].gbCount++;
        break;
    case 2:
        players[playerInd].pbCount++;
        break;
    default:
        players[playerInd].pbCount++;
        break;
    }
}
bool checkItemLoc(uint8_t locX, uint8_t locY){
    if (locX < GRID_X && locY < GRID_Y) {
        return true;//isShakingGrass(locX, locY);
    }
    else {
        return false;
    }
}
