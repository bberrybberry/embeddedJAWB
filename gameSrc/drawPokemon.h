/**
 * @file drawPokemon
 * @author Breanna Higgins
 *
 * @brief Utilities for drawing visuals of pokemon game
 *
 * TODO: Docs
 */

// System Includes
#include <msp430f5529.h>
#include <stdint.h>

//GrLib Includes
#include "grlib.h"
#include "driverlib.h"

// Embedded Library Includes
#include "system.h"
#include "game_controller_host.h"
#include "game_controller.h"
#include "game.h"
#include "uart.h"
#include "hal_general.h"
#include "hal_uart.h"
#include "task.h"
#include "timing.h"
#include "terminal.h"
#include "random_int.h"

//Custom Includes
#include "graphics.h"
#include "pixel_defs.h"
#include "map.h"
#include "pokemonImages.h"

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

/////////////////////////////////////////////////////////////////////////////////////
//
// Enums
//
/////////////////////////////////////////////////////////////////////////////////////

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
void drawMap(MapStruct map);
void drawStatic(/*tile graphics*/);
void printMenu(uint8_t playerID, menuState ms, char* text);
void printStats(uint8_t time, char* text);

