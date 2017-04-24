/**
 * @file pokemonGame
 *
 * Pokemon Game Module:
 *
 * TODO: Write better docs
 *
 * Author: Breanna Higgins,
 */

#include "system.h"
#include "random_int.h"
#include "stddef.h"
#include "strings.h"
#include "game.h"
#include "timing.h"
#include "task.h"
#include "terminal.h"
#include "game_controller.h"
#include "pokemon.h"
#include "drawPokemon.h"

/// game structure
static struct {
    char x; ///< x coordinate of gun
    char c; ///< character of gun
    int score; ///< score for the round
    int shots_fired; ///< shots fired for the round
    uint8_t id; ///< ID of game=
} game;

//Not sure why this stops compiling when not declared like this :/
void pkmnPlay();
void pkmnHelp();
void inputCallback(game_network_payload_t * input);

void pkmnGameInit(void){
    // Register the module with the game system and give it the name "pokemon"
    game.id = Game_Register("pokemon", "Play pokemon with friends", pkmnPlay, pkmnHelp);
}

void pkmnPlay(void){
    Game_RegisterInputCallback(inputCallback);

    //TODO Add game code from pokemon.h to start on display
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
