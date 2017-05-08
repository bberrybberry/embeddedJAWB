/**
 * @file
 *
 * Pokemon Game Module:
 *
 * TODO: Write better docs
 *
 * Author: Breanna Higgins,
 */


#include "pokemonGame.h"

nrf24_t* nrf;

/**
 * @var g_pokemonX
 * @brief Global variable for x coordinate of most recent shaking grass tile
 */
uint8_t g_pokemonX = INITIAL_COORDINATE_VALUE;

/**
 * @var g_pokemonY
 * @brief Global variable for y coordinate of most recent shaking grass tile
 */
uint8_t g_pokemonY = INITIAL_COORDINATE_VALUE;

/**
 * @var g_itemX
 * @brief Global variable for x coordinate of most recent item tile
 */
uint8_t g_itemX = INITIAL_COORDINATE_VALUE;

/**
 * @var g_itemY
 * @brief Global variable for y coordinate of most recent item tile
 */
uint8_t g_itemY = INITIAL_COORDINATE_VALUE;

void pkmnGameInit(nrf24_t* nrfPtr){
    // Register the module with the game system and give it the name "pokemon"
    game.id = Game_Register("pokemon", "Play pokemon with friends", pkmnPlay, pkmnHelp);
    nrf = nrfPtr;

}

void pkmnPlay(void){
    Game_RegisterInputCallback(inputCallback);

    if (nrf->ReceivedPayload) {
    	game.client = false;
    }
    else {
    	game.client = true;
    }

    Game_RegisterHostPacketizer(packetizer);

    //init pokemon game
    game.currGameState = PAUSE;
    game.currNumItems = 0;
    game.currNumPkmn = 0;

    initGame();
    callbackInit();
}

void pkmnHelp(void){
    Game_Printf("Use up, down, left, and right to move your players, use\r\n"
    		"the start button to pause/un pause, use A and B\r\n"
    		"to choose between ball and run respectively, use left\r\n"
    		"and right to change ball select options and A to select\r\n"
    		"a ball to throw. Run to a special point in the grass to\r\n"
    		"look for pokemon and pick up items to replenish your\r\n"
    		"pokeball counts.");
}

uint8_t packetizer(uint8_t* buffer) {
	static uint8_t pokemonX = INITIAL_COORDINATE_VALUE, pokemonY = INITIAL_COORDINATE_VALUE;
	static uint8_t itemX = INITIAL_COORDINATE_VALUE, itemY = INITIAL_COORDINATE_VALUE;
	volatile uint8_t i;
	uint8_t size = 0;
	union64_t packet;
	packet.quad_word = 0;

	// Send pause state in packet
	if (game.currGameState == PAUSE) {
		packet.ub[0].bits.b0 = 1;
	}
	else {
		packet.ub[0].bits.b0 = 0;
	}

	// Send if a new pokemon has appeared on the map
	if (pokemonX != g_pokemonX && pokemonY != g_pokemonY) {
		packet.ub[0].bits.b1 = 1;
		packet.ub[PACKET_POKEMON_X].b = g_pokemonX;
		packet.ub[PACKET_POKEMON_Y].b = g_pokemonY;
		pokemonX = g_pokemonX;
		pokemonY = g_pokemonY;
	}

	// Send if a new item has appeard on the map
	if (itemX != g_itemX && itemY != g_itemY) {
		packet.ub[0].bits.b2 = 1;
		packet.ub[PACKET_ITEM_X].b = g_itemX;
		packet.ub[PACKET_ITEM_Y].b = g_itemY;
		itemX = g_itemX;
		itemY = g_itemY;
	}

	// Send if any of the players have picked up an item or pokemon
	for (i = 0; i < MAX_PLAYERS; i++) {
		if (game.item != DEFAULT_ITEM_VALUE) {
			packet.ub[PACKET_ITEM_ID].b = game.item;
			game.item = DEFAULT_ITEM_VALUE;
		}

		if (game.pkmn) {
			packet.ub[PACKET_POKEMON_ID].b = game.pkmn->index;
			game.pkmn = 0;
		}
	}

	for (i = 0; i < PACKET_SIZE; i++) {
		*buffer = packet.ub[i].b;
		size++;
		buffer++;
	}

	return size;
}

void shakingGrassUpdate(void) {
	if(game.currNumPkmn < MAX_PKMN_ONSCREEN){
		if (game.client) {
			setShakingGrass(g_pokemonX, g_pokemonY);
		}
		else {
			uint8_t x, y;
			generateShakingGrass(&x, &y);

			g_pokemonX = x;
			g_pokemonY = y;
		}

		++game.currNumPkmn;
	}
}

void itemUpdate(void) {
	if(game.currNumItems < MAX_ITEMS_ONSCREEN){
		if (game.client) {
			drawItem(g_itemX, g_itemY);
		}
		else {
			uint8_t x, y;
			generateItems(&x, &y);

			g_itemX = x;
			g_itemY = y;
		}

		++game.currNumItems;
	}
}

void inputCallback(game_network_payload_t * input){
    //TODO: Make this ungeneric input code

    static uint8_t index = 0;
    static uint8_t fps = 0;
    static uint32_t time = 0;
    volatile uint8_t i;

    fps++;
    if(index != 0 && input->index != index + 1) {
        Game_Printf("index skip");
    }
    index = input->index;
    for(i = 0; i < 4; i++) {
        if(input->controller[i].button.up) upPressed(i);//MoveUp(&player[i]);
        if(input->controller[i].button.down) downPressed(i);
        if(input->controller[i].button.left) leftPressed(i);
        if(input->controller[i].button.right) rightPressed(i);
        if(input->controller[i].button.A) aPressed(i);
        if(input->controller[i].button.B) bPressed(i);
        if(input->controller[i].button.start) startPressed(i);
        if(input->controller[i].button.select) selectPressed(i);
    }

    if (game.client) {
    	// Get new pokemon
    	if (input->user_data[PACKET_INDICATOR] & PACKET_POKEMON_BIT) {
    		g_pokemonX = input->user_data[PACKET_POKEMON_X];
    		g_pokemonY = input->user_data[PACKET_POKEMON_Y];

    		for (i = 0; i < MAX_PKMN_ONSCREEN; i++) {
    			if (allPkmnValidEntries[i]) {
    				allPkmnValidEntries[i] = false;
    				allPkmn[i].locX = g_pokemonX;
    				allPkmn[i].locY = g_pokemonY;
    				allPkmn[i].pokemon = &pkmnList[input->user_data[PACKET_POKEMON_ID]];
    				setShakingGrass(g_pokemonX, g_pokemonY);
    				break;
    			}
    		}
    	}

    	// Get new item
    	if (input->user_data[PACKET_INDICATOR] & PACKET_ITEM_BIT) {
    		g_itemX = input->user_data[PACKET_ITEM_X];
    		g_itemY = input->user_data[PACKET_ITEM_Y];

    		for (i = 0; i < MAX_ITEMS_ONSCREEN; i++) {
    			if (allItemsValidEntries[i]) {
    				allItemsValidEntries[i] = false;
    				allItems[i].locX = g_itemX;
    				allItems[i].locY = g_itemY;
    				allItems[i].itemID = input->user_data[PACKET_ITEM_ID];
    	    		drawItem(g_itemX, g_itemY);
    	    		break;
    			}
    		}
    	}
    }

    if(TimeSince(time) > 1000) {
        Game_CharXY('F', 0, MAP_HEIGHT+1);
        Game_Printf("PS: %d  ", fps);
        fps = 0;
        time = TimeNow();
    }

    Game_CharXY(' ', 0, MAP_HEIGHT+2);

}

void callbackInit(void) {
//	controller_buttons_t mask;
//	mask.all_buttons = 0xFFFF;
//	GameControllerHost_RegisterPressCallback(0, p1Handler, mask, 0);
//	GameControllerHost_RegisterPressCallback(1, p2Handler, mask, 0);
//	GameControllerHost_RegisterPressCallback(2, p3Handler, mask, 0);
//	GameControllerHost_RegisterPressCallback(3, p4Handler, mask, 0);
}

void pkmnGameOver(void){
    // clear the input callback
    Game_RegisterInputCallback(0);
    // set cursor below bottom of map
    Game_CharXY('\r', 0, MAP_HEIGHT + 2);
    // show score
    Game_Printf("Game Over!");
    // show cursor (it was hidden at the beginning
    Game_ShowCursor();
    Game_GameOver();
}

void upPressed(uint8_t player){
	if(game.currGameState == PLAY) {
		movePlayerUp(player);
	}
}

void downPressed(uint8_t player){
	if(game.currGameState == PLAY) {
		movePlayerDown(player);
	}
}

void leftPressed(uint8_t player){
	if(game.currGameState == PLAY) {
		leftBallOption(player);
		movePlayerLeft(player);
	}
}

void rightPressed(uint8_t player){
	if(game.currGameState == PLAY) {
		rightBallOption(player);
		movePlayerRight(player);
	}
}

void aPressed(uint8_t player){
	if(game.currGameState == PLAY) {
		throwBall(player);
		selectBall(player);
	}
}

void bPressed(uint8_t player){
	if(game.currGameState == PLAY) {
		selectRun(player);
	}
}

void startPressed(uint8_t player){
	static uint8_t initial = 1;

	if (game.currGameState == PLAY) {
		game.currGameState = PAUSE;
		g_pauseTime = TimeNow();
		Task_Remove((task_fn_t)updateTimeRemaining, 0);
		if (!game.client) {
			Task_Remove((task_fn_t)generateShakingGrass, 0);
			Task_Remove((task_fn_t)generateItems, 0);
		}
	}
	else if (game.currGameState == PAUSE) {
		if (initial) {
			Task_Schedule((task_fn_t)updateTimeRemaining, 0, 0, SECOND);
			if (!game.client) {
				Task_Schedule((task_fn_t)shakingGrassUpdate, 0, SHAKING_GRASS_PERIOD, SHAKING_GRASS_PERIOD);
				Task_Schedule((task_fn_t)itemUpdate, 0, ITEM_GENERATION_PERIOD, ITEM_GENERATION_PERIOD);
			}
			game.currGameState = PLAY;
			initial = 0;
		}
		else {
			Task_Schedule((task_fn_t)updateTimeRemaining, 0, SECOND - ((g_pauseTime - g_startTime) % SECOND), SECOND);
			if (!game.client) {
				Task_Schedule((task_fn_t)shakingGrassUpdate, 0,
						SHAKING_GRASS_PERIOD - ((g_pauseTime - g_startTime) % SHAKING_GRASS_PERIOD), SHAKING_GRASS_PERIOD);
				Task_Schedule((task_fn_t)itemUpdate, 0,
						ITEM_GENERATION_PERIOD - ((g_pauseTime - g_startTime) % ITEM_GENERATION_PERIOD), ITEM_GENERATION_PERIOD);
			}
			game.currGameState = PLAY;
		}
	}
}

void selectPressed(uint8_t player){
	if(game.currGameState == PLAY) {

	}
}

void p1Handler(controller_buttons_t btn, void* handle) {

	if (btn.primary_buttons & (0x01) << 0) {
		upPressed(0);
	}
	if (btn.primary_buttons & (0x01) << 1) {
		downPressed(0);
	}
	if (btn.primary_buttons & (0x01) << 2) {
		leftPressed(0);
	}
	if (btn.primary_buttons & (0x01) << 3) {
		rightPressed(0);
	}
	if (btn.primary_buttons & (0x01) << 4) {
		aPressed(0);
	}
	if (btn.primary_buttons & (0x01) << 5) {
		bPressed(0);
	}
	if (btn.primary_buttons & (0x01) << 6) {
		startPressed(0);
	}
	if (btn.primary_buttons & (0x01) << 7) {
		selectPressed(0);
	}
}

void p2Handler(controller_buttons_t btn, void* handle) {
	if (btn.primary_buttons & (0x01) << 0) {
		upPressed(1);
	}
	if (btn.primary_buttons & (0x01) << 1) {
		downPressed(1);
	}
	if (btn.primary_buttons & (0x01) << 2) {
		leftPressed(1);
	}
	if (btn.primary_buttons & (0x01) << 3) {
		rightPressed(1);
	}
	if (btn.primary_buttons & (0x01) << 4) {
		aPressed(1);
	}
	if (btn.primary_buttons & (0x01) << 5) {
		bPressed(1);
	}
	if (btn.primary_buttons & (0x01) << 6) {
		startPressed(1);
	}
	if (btn.primary_buttons & (0x01) << 7) {
		selectPressed(1);
	}
}

void p3Handler(controller_buttons_t btn, void* handle) {
	if (btn.primary_buttons & (0x01) << 0) {
		upPressed(2);
	}
	if (btn.primary_buttons & (0x01) << 1) {
		downPressed(2);
	}
	if (btn.primary_buttons & (0x01) << 2) {
		leftPressed(2);
	}
	if (btn.primary_buttons & (0x01) << 3) {
		rightPressed(2);
	}
	if (btn.primary_buttons & (0x01) << 4) {
		aPressed(2);
	}
	if (btn.primary_buttons & (0x01) << 5) {
		bPressed(2);
	}
	if (btn.primary_buttons & (0x01) << 6) {
		startPressed(2);
	}
	if (btn.primary_buttons & (0x01) << 7) {
		selectPressed(2);
	}
}

void p4Handler(controller_buttons_t btn, void* handle) {
	if (btn.primary_buttons & (0x01) << 0) {
		upPressed(3);
	}
	if (btn.primary_buttons & (0x01) << 1) {
		downPressed(3);
	}
	if (btn.primary_buttons & (0x01) << 2) {
		leftPressed(3);
	}
	if (btn.primary_buttons & (0x01) << 3) {
		rightPressed(3);
	}
	if (btn.primary_buttons & (0x01) << 4) {
		aPressed(3);
	}
	if (btn.primary_buttons & (0x01) << 5) {
		bPressed(3);
	}
	if (btn.primary_buttons & (0x01) << 6) {
		startPressed(3);
	}
	if (btn.primary_buttons & (0x01) << 7) {
		selectPressed(3);
	}
}

void updateTimeRemaining(void) {
	static uint8_t timeRemaining = GAME_TIME_LIMIT + 1;
	timeRemaining--;

	updateTime(timeRemaining);

	//check game over: timeout
	if(timeRemaining == 0){
		//end game
		//TODO

		//print final stats

	}
}
