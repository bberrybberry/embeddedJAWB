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

/// game structure
static struct {
    gameState currGameState;    ///< Current state of the game
    uint8_t id;                 ///< ID of game
} game;

void pkmnGameInit(void){
    // Register the module with the game system and give it the name "pokemon"
    game.id = Game_Register("pokemon", "Play pokemon with friends", pkmnPlay, pkmnHelp);
}

void pkmnPlay(void){
    Game_RegisterInputCallback(inputCallback);

    //init pokemon game
    initGame();
    callbackInit();
    game.currGameState = PAUSE;
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
	union64_t test;
	test = 0;
	if (game.currGameState == PAUSE) {
		test.ub[0].bits.b0 = 1;
	}
	else {
		test.ub[0].bits.b0 = 0;
	}
}

void inputCallback(game_network_payload_t * input){
    //TODO: Make this ungeneric input code

    static uint8_t index = 0;
    static uint8_t fps = 0;
    static uint32_t time = 0;
    uint8_t i;
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
//	mask.all_buttons = 0x0000;
//	mask.button.A = 1;
//	GameControllerHost_RegisterPressCallback(0, aHandler, mask, 0);
//	mask.all_buttons = 0x0000;
//	mask.button.B = 1;
//	GameControllerHost_RegisterPressCallback(0, bHandler, mask, 0);
//	mask.all_buttons = 0x0000;
//	mask.button.start = 1;
//	GameControllerHost_RegisterPressCallback(0, startHandler, mask, 0);
//	mask.all_buttons = 0x0000;
//	mask.button.up = 1;
//	GameControllerHost_RegisterPressCallback(0, upHandler, mask, 0);
//	mask.all_buttons = 0x0000;
//	mask.button.down = 1;
//	GameControllerHost_RegisterPressCallback(0, downHandler, mask, 0);
//	mask.all_buttons = 0x0000;
//	mask.button.left = 1;
//	GameControllerHost_RegisterPressCallback(0, leftHandler, mask, 0);
//	mask.all_buttons = 0x0000;
//	mask.button.right = 1;
//	GameControllerHost_RegisterPressCallback(0, rightHandler, mask, 0);
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
		Task_Remove((task_fn_t)generateShakingGrass, 0);
		Task_Remove((task_fn_t)generateItems, 0);
		pauseGame();
	}
	else if (game.currGameState == PAUSE) {
		if (initial) {
			Task_Schedule((task_fn_t)updateTimeRemaining, 0, 0, SECOND);
			Task_Schedule((task_fn_t)generateShakingGrass, 0, SHAKING_GRASS_PERIOD, SHAKING_GRASS_PERIOD);
			Task_Schedule((task_fn_t)generateItems, 0, ITEM_GENERATION_PERIOD, ITEM_GENERATION_PERIOD);
			game.currGameState = PLAY;
			playGame();
			initial = 0;
		}
		else {
			Task_Schedule((task_fn_t)updateTimeRemaining, 0, SECOND - ((g_pauseTime - g_startTime) % SECOND), SECOND);
			Task_Schedule((task_fn_t)generateShakingGrass, 0,
					SHAKING_GRASS_PERIOD - ((g_pauseTime - g_startTime) % SHAKING_GRASS_PERIOD), SHAKING_GRASS_PERIOD);
			Task_Schedule((task_fn_t)generateItems, 0,
					ITEM_GENERATION_PERIOD - ((g_pauseTime - g_startTime) % ITEM_GENERATION_PERIOD), ITEM_GENERATION_PERIOD);
			game.currGameState = PLAY;
			playGame();
		}
	}
}

void selectPressed(uint8_t player){
	if(game.currGameState == PLAY) {

	}
}

void upHandler(controller_buttons_t btn, void* handle) {
	upPressed(0);
}

void downHandler(controller_buttons_t btn, void* handle) {
	downPressed(0);
}

void leftHandler(controller_buttons_t btn, void* handle) {
	leftPressed(0);
}

void rightHandler(controller_buttons_t btn, void* handle) {
	rightPressed(0);
}

void aHandler(controller_buttons_t btn, void* handle) {
	aPressed(0);
}

void bHandler(controller_buttons_t btn, void* handle) {
	bPressed(0);
}

void startHandler(controller_buttons_t btn, void* handle) {
	startPressed(0);
}

void selectHandler(controller_buttons_t btn, void* handle) {
	selectPressed(0);
}

void updateTimeRemaining(void) {
	static uint8_t timeRemaining = GAME_TIME_LIMIT + 1;
	timeRemaining--;

	updateTime(timeRemaining);
}
