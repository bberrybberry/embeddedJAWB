/**
 * @file pokemonGame
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

///////////////////////////////////// DEBUG FUNCTS //////////////////////////////////////
#define DEBUG_MODE //comment out to leave debug mode

void DEBUG_upPressed(uint8_t player);
void DEBUG_downPressed(uint8_t player);

/**
 * move the selected player up
 *
 * @param dir: 0 = up, 1 = down, 2 = right, 3 = left
 * @param player: player number index
 */
void DEBUG_upPressed(uint8_t player){
	DEBUG_playerMoveTest(0, player);
}
/**
 * move the selected player down
 *
 * @param player: player number index
 */
void DEBUG_downPressed(uint8_t player){
	DEBUG_playerMoveTest(1, player);
}
/////////////////////////////////////////////////////////////////////////////////////////


void drawTest(){
	initMap();
}

void pkmnGameInit(void){
    // Register the module with the game system and give it the name "pokemon"
    game.id = Game_Register("pokemon", "Play pokemon with friends", pkmnPlay, pkmnHelp);
}

void pkmnPlay(void){
    Game_RegisterInputCallback(inputCallback);

    //init pokemon game
    initGame();
}

void pkmnHelp(void){
    //TODO
    Game_Printf("help text TBD\r\n");
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
        //TODO
//        if(input->controller[i].button.up) MoveUp(&player[i]);
//        if(input->controller[i].button.down) MoveDown(&player[i]);
//        if(input->controller[i].button.left) MoveLeft(&player[i]);
//        if(input->controller[i].button.right) MoveRight(&player[i]);
    }
#ifdef DEBUG_MODE
    if(input->controller[0].button.up) DEBUG_upPressed(0);
    if(input->controller[0].button.down) DEBUG_downPressed(0);
#endif

    if(TimeSince(time) > 1000) {
        Game_CharXY('F', 0, MAP_HEIGHT+1);
        Game_Printf("PS: %d  ", fps);
        fps = 0;
        time = TimeNow();
    }
    Game_CharXY(' ', 0, MAP_HEIGHT+2);
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
