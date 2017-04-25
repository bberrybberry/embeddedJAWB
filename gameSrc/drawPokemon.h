/**
 * @file drawPokemon
 * @author Breanna Higgins
 *
 * @brief Utilities for drawing visuals of pokemon game
 */

//#include "pokemonImages.h"

/////////////////////////////////////////////////////////////////////////////////////
//
// Defines
//
/////////////////////////////////////////////////////////////////////////////////////

//TODO: Docs for defines
#define TILE_X      16
#define TILE_Y      12
#define MAP_WIDTH   12*TILE_X
#define MAP_HEIGHT  20*TILE_Y

//TODO Fix this
/////////////////////////////////////////////////////////////////////////////////////
//
// Enums
//
/////////////////////////////////////////////////////////////////////////////////////

///**
//* @enum gameState
//* @brief Defines direction of the ball's path, as defined as leaving the paddle
//*/
//typedef enum{
//    PAUSE,
//    PLAY,
//    GAME_OVER_WIN,
//    GAME_OVER_LOSE
//} gameState;



typedef enum {AARON, BREANNA, JOSH, WALT} playerSprite;

typedef enum{LEFT, RIGHT, STAND} walkState;

typedef enum{GRASS, SHAKE_UP, SHAKE_DOWN} grassState;

typedef enum{RUN_BALL, BALL_SELECT, NONE} menuState;

/////////////////////////////////////////////////////////////////////////////////////
//
// Functions
//
/////////////////////////////////////////////////////////////////////////////////////

void drawPlayer(playerSprite ps, walkState ws, uint8_t location);
void drawGrass(grassState gs, uint8_t location);
void drawStatic(/*tile graphics*/);
void printMenu(uint8_t playerID, menuState ms, char* text);
void printStats(uint8_t time, char* text);

