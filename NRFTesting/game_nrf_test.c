/*
 * game_nrf_test.c
 *
 *  Created on: April 8, 2017
 *      Author: Muhlbaier
 */


#include "system.h"
#include "random_int.h"
#include "stddef.h"
#include "strings.h"
#include "game.h"
#include "timing.h"
#include "task.h"
#include "terminal.h"
#include "random_int.h"
#include "game_controller.h"

#define TILE_X 16
#define TILE_Y 12
#define MAP_WIDTH 12*TILE_X
#define MAP_HEIGHT 20*TILE_Y

/// game structure
static struct {
    char x; ///< x coordinate of gun
    char c; ///< character of gun
    int score; ///< score for the round
    int shots_fired; ///< shots fired for the round
    uint8_t id; ///< ID of game=
} game;
static char pkmnWeight[] = {5, 15, 30, 50, 75, 100};
static char_object_t player[4];
//static char playLoc= {-1, -1, -1, -1};       //Tile location of each player
                                            //index 0 is player 1, index 3 is player 4
                                            //-1 player not in game
// note the user doesn't need to access these functions directly so they are
// defined here instead of in the .h file
// further they are made static so that no other files can access them
// ALSO OTHER MODULES CAN USE THESE SAME NAMES SINCE THEY ARE STATIC
static void Play(void);
static void Help(void);
static char checkCollision(char x, char y);
static void MoveRight(char_object_t * o);
static void MoveLeft(char_object_t * o);
static void MoveUp(char_object_t * o);
static void MoveDown(char_object_t * o);
static void encounter();
static char checkCollision(char xLoc, char yLoc);
static char getPkmn();
static char binarySearch(char a[], char item, char low, char high);
static void GameOver(void);

static char binarySearch(char a[], char item, char low, char high)
{
    if (high <= low)
        return (item > a[low])?  (low + 1): low;

    int mid = (low + high)/2;

    if(item == a[mid])
        return mid+1;

    if(item > a[mid])
        return binarySearch(a, item, mid+1, high);
    return binarySearch(a, item, low, mid-1);
}

void Game_nRF_Test_Init(void) {
    // Register the module with the game system and give it the name "MUH3"
    game.id = Game_Register("nRF", "Test the nRF24L01+ game network", Play, Help);
    //pkmnWeight = {5, 15, 30, 50, 75, 100};
}

void Help(void) { 
    Game_Printf("help text TBD\r\n");
}

static void InputCallback(game_network_payload_t * input) {
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
		if(input->controller[i].button.up) MoveUp(&player[i]);
		if(input->controller[i].button.down) MoveDown(&player[i]);
		if(input->controller[i].button.left) MoveLeft(&player[i]);
		if(input->controller[i].button.right) MoveRight(&player[i]);
	}
	if(TimeSince(time) > 1000) {
		Game_CharXY('F', 0, MAP_HEIGHT+1);
		Game_Printf("PS: %d  ", fps);
		fps = 0;
		time = TimeNow();
	}
	Game_CharXY(' ', 0, MAP_HEIGHT+2);
}

void Play(void) {
    Game_RegisterInputCallback(InputCallback);

    // clear the screen
    Game_ClearScreen();
    // draw a box around our map
    Game_DrawRect(0, 0, MAP_WIDTH, MAP_HEIGHT);
    
    // initialize game variables
    player[0].c = '1';
    player[0].x = 5;
    player[0].y = 5;
    player[1].c = '2';
	player[1].x = 25;
	player[1].y = 5;
	player[2].c = '3';
	player[2].x = 5;
	player[2].y = 15;
	player[3].c = '4';
	player[3].x = 25;
	player[3].y = 15;
	Game_CharXY(player[0].c, player[0].x, player[0].y);
	Game_CharXY(player[1].c, player[1].x, player[1].y);
	Game_CharXY(player[2].c, player[2].x, player[2].y);
	Game_CharXY(player[3].c, player[3].x, player[3].y);

    // hide cursor
    Game_HideCursor();
}

static void MoveRight(char_object_t * o) {
    // make sure we can move right
    if (o->x < MAP_WIDTH - 1) {
        // clear location
        Game_CharXY(' ', o->x, o->y);
        //int move;
        o->x +=TILE_X;

        if(checkCollision(o->x, o->y)==0){
        // update
        Game_CharXY(o->c, o->x, o->y);
        if(random_int(1,2) == 2 ){
            encounter(o);
        }
        }
    }
}
//array of pkmn structs
//has name, catch rate, and ptValue
static void encounter(char_object_t * o){
    char pkmn = getPkmn();
    //Print Player o Encounters
    char caught =0;
    while(caught==0/*&& run == 0*/){

    }
}
/*TODO make cursur select*/
static char getPkmn(){
    //gen pkmn
    char x = random_int(1, 100);
    char index = binarySearch(pkmnWeight, x, 0, 6);
    return index;
}
static void MoveLeft(char_object_t * o) {
    // make sure we can move right
    if (o->x > 1) {
        // clear location
    	Game_CharXY(' ', o->x, o->y);
    	//x-=TILE_X
    	o->x-=TILE_X;
        if(checkCollision(o->x, o->y)==0)
        // update
        Game_CharXY(o->c, o->x, o->y);
    }
}

static void MoveUp(char_object_t * o) {
    // make sure we can move right
    if (o->y > 1 ) {
        // clear location
    	Game_CharXY(' ', o->x, o->y);
    	o->y-=TILE_Y;
        if(checkCollision(o->x, o->y)==0)
    	// update
        Game_CharXY(o->c, o->x, o->y);
    }
}

static void MoveDown(char_object_t * o) {
    // make sure we can move right
    if (o->y < MAP_HEIGHT - 1) {
        // clear location
        Game_CharXY(' ', o->x, o->y);
        o->y +=TILE_Y;
        if(checkCollision(o->x, o->y)==0)
        // update
        Game_CharXY(o->c, o->x, o->y);
    }
}
static char checkCollision(char xLoc, char yLoc){
    volatile uint8_t i;
    char collide = 0;
    for(i = 0; i < 3 && !collide; i++){
        if(player[i].x == xLoc && player[i].y ==yLoc){
            collide = 1;
        }
    }
    return collide;
}
void GameOver(void) {
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
