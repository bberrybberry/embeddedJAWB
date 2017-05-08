/**
 * @file pokemon
 * @author Breanna Higgins
 * @brief TODO
 * TODO: Everything
 */

#include "pokemon.h"
#include "graphics.h" //needed for types and defines
#include "timing.h"
#include "random_int.h"

uint8_t binarySearch(uint8_t arr[], uint8_t item, uint8_t low, uint8_t high){
    if(low>=high)
        return low;
    uint8_t mid = (high+low)/2;
    if(item>arr[mid])
        return binarySearch(arr, item, ++mid, high);
    else if(item<arr[mid])
        return binarySearch(arr, item, low, --mid);
    else
        return mid;
}

void initGame(){

    //set up map
    initMap();

    //init players
    initPlayers();
    //TODO: Find dynamic way to know how many players are playing
    players[0].status = true;
    players[1].status = true;

    //set up menus and text
    initTextBox();

    //set up pokemon for generation
    initPokemon();

    initItems();

    //set up time and first item/pokemon generations (clear collections)
    volatile int i;
    for(i = 0; i < MAX_ITEMS_ONSCREEN; i++){
    	allItemsValidEntries[i] = true;
    }
    for(i = 0; i < MAX_PKMN_ONSCREEN; i++){
    	allPkmnValidEntries[i] = true;
    }
}

void initMap(){
    drawMap();
}

void initPlayers(){
    //register players 1-4
	volatile int i;
	for(i = 0; i < MAX_PLAYERS; i++){
		//TODO set these back to 15/10/5, set to lower numbers now for debugging purposes
		players[i].pbCount = 1;
		players[i].gbCount = 1;
		players[i].ubCount = 1;
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
	pkmnList[0].name = "Chansey";
	pkmnList[0].spawnRate = 1;
	pkmnList[0].catchRate = 30;
	pkmnList[0].points = 60;
	pkmnList[0].index = 0;

	pkmnList[1].name = "Gyrados";
	pkmnList[1].spawnRate = 4;
	pkmnList[1].catchRate = 45;
	pkmnList[1].points = 50;
	pkmnList[1].index = 1;

    pkmnList[2].name = "Jigglypuff";
    pkmnList[2].spawnRate = 10;
    pkmnList[2].catchRate = 45;
    pkmnList[2].points = 40;
    pkmnList[2].index = 2;

    pkmnList[3].name = "Growlithe";
    pkmnList[3].spawnRate = 25;
    pkmnList[3].catchRate = 170;
    pkmnList[3].points = 30;
    pkmnList[3].index = 3;

    pkmnList[4].name = "Pikachu";
    pkmnList[4].spawnRate = 25;
    pkmnList[4].catchRate = 190;
    pkmnList[4].points = 20;
    pkmnList[4].index = 4;

    pkmnList[5].name = "Pidgey";
    pkmnList[5].spawnRate = 35;
    pkmnList[5].catchRate = 255;
    pkmnList[5].points = 10;
    pkmnList[5].index = 5;
    
    game.pkmn = 0;

    volatile uint8_t i;
    for(i = 0; i<MAX_PKMN; i++){
        if(i==0)
        	pkmnWeights[i] = pkmnList[i].spawnRate;
        else
            pkmnWeights[i] = pkmnList[i].spawnRate+pkmnWeights[i-1];
    }
}

void initItems(){
    itemWeights[0] = 10;
    itemWeights[1] = 40;
    itemWeights[2] = 100;

    game.item = DEFAULT_ITEM_VALUE;
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
		bool encounterFound = checkShakingGrass(players[playerIndex].tileX, players[playerIndex].tileY - 1);
        bool itemFound = checkItemLoc(players[playerIndex].tileX, players[playerIndex].tileY - 1);
		if (map.grid[initPt.x + initPt.y * GRID_X]) {
			//redraw bg tile
			drawStatic(map.grid[initPt.x + initPt.y * GRID_X], &initPt);
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
		bool encounterFound = checkShakingGrass(players[playerIndex].tileX, players[playerIndex].tileY + 1);
		bool itemFound = checkItemLoc(players[playerIndex].tileX, players[playerIndex].tileY + 1);
		if (map.grid[initPt.x + initPt.y * GRID_X]) {
			//redraw bg tile
			drawStatic(map.grid[initPt.x + initPt.y * GRID_X], &initPt);
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
		bool encounterFound = checkShakingGrass(players[playerIndex].tileX - 1, players[playerIndex].tileY);
		bool itemFound = checkItemLoc(players[playerIndex].tileX - 1, players[playerIndex].tileY);
		if (map.grid[initPt.x + initPt.y * GRID_X]) {
			//redraw bg tile
			drawStatic(map.grid[initPt.x + initPt.y * GRID_X], &initPt);
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
		bool encounterFound = checkShakingGrass(players[playerIndex].tileX + 1, players[playerIndex].tileY);
		bool itemFound = checkItemLoc(players[playerIndex].tileX + 1, players[playerIndex].tileY);
		if (map.grid[initPt.x + initPt.y * GRID_X]) {
			//redraw bg tile
			drawStatic(map.grid[initPt.x + initPt.y * GRID_X], &initPt);
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

void generateShakingGrass(uint8_t* x, uint8_t* y) {
	volatile int i;
	bool display = false;
	uint8_t count = 0;

	//find some place to generate pokemon
	while(!display) {
		*x = random_int(0, GRID_X - 1);
		*y = random_int(0, GRID_Y - 1);
		display = true;
		if (!isGrass(*x, *y)) {
			display = false;
		}
		if (checkShakingGrass(*x, *y)) {
			display = false;
		}
		if (checkItemLoc(*x, *y)) {
			display = false;
		}
		for (i = 0; i < MAX_PLAYERS; i++) {
			if ((*x == players[i].tileX) && (*y == players[i].tileY)) {
				display = false;
			}
		}

		if (count > 30) {
			break;
		}
		count++;
	}
	if (display) {
		//add this encounter spot to the array of encounters
		int8_t validIndex = -1;
		for(i = 0; i < MAX_PKMN_ONSCREEN; i++){
			//try to find a valid location
			if(allPkmnValidEntries[i] == true){
				//save index
				validIndex = i;

				//flag as no longer valid
				allPkmnValidEntries[i] = false;

				//found what you wanted, exit loop now
				break;
			}
		}

		//if didn't find a valid entry for this pokemon onscreen, exit now
		if(validIndex < 0){
			return;
		}

		//add this encounter to collection of encounters
		encounter_t thisEncounter;
		thisEncounter.locX = *x;
		thisEncounter.locY = *y;
		thisEncounter.pokemon = generatePokemon();
		allPkmn[validIndex] = thisEncounter;

		//draw
		setShakingGrass(*x, *y);
	}
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

void printGameOverStats(){
	//find winning player
	uint8_t winScore = 0;
	uint8_t winPlayer = 0;

	volatile int i;
	for(i = 0; i < MAX_PLAYERS; i++){
		if(players[i].score > winScore){
			winScore = players[i].score;
			winPlayer = i;
		}
	}

	//print stats
	printEndStats(winPlayer, winScore);
}

void updateTime(uint8_t time){
    printTime(time);
}

void updateScores(uint8_t playerID, uint8_t score){
    printScore(playerID, score);
}

void runEncounter(uint8_t playerInd){
    //stop player movement
	players[playerInd].mvmt = false;

	//find which encounter this is (assuming if you get to this point, you actually found an encounter)
	volatile int i;
	int8_t encounterInd = -1;
	for(i = 0; i < MAX_PKMN_ONSCREEN; i++){
		if(allPkmn[i].locX == players[playerInd].tileX && allPkmn[i].locY == players[playerInd].tileY){
			encounterInd = i;
			break;
		}
	}

	//pass around the pokemon inside this encounter
	pokemon_t* encounterPkmn = allPkmn[encounterInd].pokemon;

	//print pokemon
	if (!game.client) {
		players[playerInd].encountered = encounterPkmn;//();
		game.pkmn = players[playerInd].encountered;
	}
	else {
		players[playerInd].encountered = game.pkmn;
	}

	printPokemon(playerInd, FOUND_MSG, players[playerInd].encountered->name);

	//change menu
	printMenu(playerInd, RUN_BALL, -1, -1, -1, "");

	//update pokemon count
	game.currNumPkmn--;
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
		if(players[player].pbCount == 0 && players[player].gbCount != 0){ //if first option is empty, select second option
			players[player].pbCount *= -1;
			players[player].gbCount *= 1;
			players[player].ubCount *= -1;

			printMenu(player, BALL_SELECT, players[player].pbCount, players[player].gbCount, players[player].ubCount, "Great balls");
		}
		else if(players[player].gbCount == 0 && players[player].ubCount != 0){ //if second option is empty, select third option
			players[player].pbCount *= -1;
			players[player].gbCount *= -1;
			players[player].ubCount *= 1;

			printMenu(player, BALL_SELECT, players[player].pbCount, players[player].gbCount, players[player].ubCount, "Ultra balls");

		}
		else if(players[player].ubCount == 0){ //if everything is empty, end encounter
			//resume movement
			players[player].mvmt = true;

			//clear menu
			//TODO: Have a message to let player know they ran out of balls
			printMenu(player, NONE, 0, 0, 0, "");
			printPokemon(player, NONE_MSG, "");

			//early exit
			return;
		}
		else{ //you have pokeballs, pick first option
			players[player].pbCount *= 1;
			players[player].gbCount *= -1;
			players[player].ubCount *= -1;

			printMenu(player, BALL_SELECT, players[player].pbCount, players[player].gbCount, players[player].ubCount, "Poke balls");

		}

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
	if(players[player].mvmt == false && ( //player is in menu state
			//check if only one ball count is non-zero value, meaning player is in ball select options
			(players[player].pbCount > 0 && players[player].gbCount <= 0 && players[player].ubCount <= 0) ||	//pb selected
			(players[player].pbCount <= 0 && players[player].gbCount > 0 && players[player].ubCount <= 0) ||	//gb selected
			(players[player].pbCount <= 0 && players[player].gbCount <= 0 && players[player].ubCount > 0)		//ul selected
			)){

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
	uint8_t thresh = random_int(1, 50);

    uint16_t catchValue = (uint16_t)catchRate*(uint16_t)multiplier;
    uint16_t catch = CATCH_CHECK_1 / (CATCH_CHECK_2 / catchValue);

	if(thresh < catch){
		players[player].score += players[player].encountered->points;
		printScore(player, players[player].score);
		printPokemon(player, CAUGHT_MSG, players[player].encountered->name);
		players[player].encountered = 0;
	}
	else{
		printPokemon(player, RAN_MSG, players[player].encountered->name);
		players[player].encountered = 0;
	}

	//find which encounter this is (assuming if you get to this point, you actually found an encounter)
	volatile int i;
	int8_t encounterInd = -1;
	for(i = 0; i < MAX_PKMN_ONSCREEN; i++){
		if(allPkmn[i].locX == players[player].tileX && allPkmn[i].locY == players[player].tileY){
			encounterInd = i;
			break;
		}
	}

	//return this spot as a valid encounter generation point
	allPkmnValidEntries[encounterInd] = true;

	//clear menu
	printMenu(player, NONE, -1, -1, -1, "");

	//remove shaking grass
	drawGrass(GRASS, players[player].tileX, players[player].tileY);
	//redraw player
	drawPlayer(players[player].sprite, STAND, players[player].tileX, players[player].tileY);
}

void generateItems(uint8_t* x, uint8_t* y){
	volatile int i;
	bool display = false;
	uint8_t count = 0;
	while(!display) {
		*x = random_int(0, GRID_X - 1);
		*y = random_int(0, GRID_Y - 1);
		display = true;
		if (!isGrass(*x, *y)) {
			display = false;
		}
		if (checkItemLoc(*x, *y)) {
			display = false;
		}
		if (checkShakingGrass(*x, *y)) {
			display = false;
		}
		for (i = 0; i < MAX_PLAYERS; i++) {
			if ((*x == players[i].tileX) && (*y == players[i].tileY)) {
				display = false;
			}
		}

		if (count > 30) {
			break;
		}
		count++;
	}

	if (display) {
		int8_t validIndex = -1;
		for (i = 0; i < MAX_ITEMS_ONSCREEN; i++) {
			if (allItemsValidEntries[i]) {
				validIndex = i;
				allItemsValidEntries[i] = false;
				break;
			}
		}

		if (validIndex < 0) {
			return;
		}

		uint8_t r = random_int(0, 100);

		item_t item;
		item.locX = *x;
		item.locY = *y;
		item.itemID = binarySearch(itemWeights, r, 0, TOTAL_ITEMS-1);
		allItems[validIndex] = item;

		drawItem(*x, *y);
	}
}

void itemSpawn(uint8_t playerInd){
	volatile uint8_t i;
	uint8_t index = 255;
	for (i = 0; i < MAX_ITEMS_ONSCREEN; i++) {
		if (allItemsValidEntries[i]) {
			if (allItems[i].locX == players[playerInd].tileX && allItems[i].locY == players[playerInd].tileY) {
				index = allItems[i].itemID;
				break;
			}
		}
	}

	if (index == 255) {
		return;
	}

    uint8_t curr = players[playerInd].pbCount+players[playerInd].gbCount+players[playerInd].ubCount;
    if (curr<=BAG_MAX){
    	if (!game.client) {
    		game.item = index;
    	}

		switch(index) {
		case 0:
			++players[playerInd].ubCount;
			printPokemon(playerInd, ULTRABALL_MSG,"");
			break;
		case 1:
			++players[playerInd].gbCount;
			printPokemon(playerInd, GREATBALL_MSG,"");
			break;
		case 2:
			++players[playerInd].pbCount;
			printPokemon(playerInd, POKEBALL_MSG,"");
			break;
		default:
			++players[playerInd].pbCount;
			break;
		}
		//remove item tile
		drawGrass(GRASS, players[playerInd].tileX, players[playerInd].tileY);
		//redraw player
		drawPlayer(players[playerInd].sprite, STAND, players[playerInd].tileX, players[playerInd].tileY);

		//update item count
		game.currNumItems--;

    }else{
        printPokemon(playerInd, FULL_MSG,"");
    }
}

bool checkItemLoc(uint8_t locX, uint8_t locY){
    if (locX < GRID_X && locY < GRID_Y) { //check if location is in bounds (in reference to array, not grid)
        return isItem(locX, locY);
    }
    else{
    	return false;
    }
}
