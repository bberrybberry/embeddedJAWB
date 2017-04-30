/**
 * @file drawPokemon
 * @author Breanna Higgins
 *
 * @brief Utilities for drawing visuals of pokemon game
 *
 * TODO: Docs
 */

#ifndef DRAWPOKEMON_H_
#define DRAWPOKEMON_H_

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
//#include "pokemonImages.h" moved to .c

/////////////////////////////////////////////////////////////////////////////////////
//
// Defines
//
/////////////////////////////////////////////////////////////////////////////////////

//TODO: Docs for defines
#define WIDTH               320
#define HEIGHT              240
#define TEXT_TILES          8
#define TILE_X              16
#define TILE_Y              12
#define GRID_X              ((WIDTH / TILE_X) - TEXT_TILES)
#define GRID_Y              (HEIGHT / TILE_Y)
#define MAP_WIDTH   		12 * TILE_X
#define MAP_HEIGHT  		20 * TILE_Y
#define MENU_HEIGHT			4

#define VERT_PADDING		1
#define HORI_PADDING		3

/////////////////////////////////////////////////////////////////////////////////////
//
// Structs
//
/////////////////////////////////////////////////////////////////////////////////////

typedef struct {
    const g_pixel_t* grid[GRID_X * GRID_Y];
} MapStruct;
MapStruct map;


/////////////////////////////////////////////////////////////////////////////////////
//
// Enums
//
/////////////////////////////////////////////////////////////////////////////////////

typedef enum {AARON, BREANNA, JOSH, WALT} playerSprite;

typedef enum{LEFT, RIGHT, STAND} walkState;

typedef enum{GRASS, SHAKE} grassState;

typedef enum{RUN_BALL, BALL_SELECT, NONE} menuState;

/////////////////////////////////////////////////////////////////////////////////////
//
// Functions
//
/////////////////////////////////////////////////////////////////////////////////////
void initDrawGraphics(void);
void drawPlayer(playerSprite ps, walkState ws, uint8_t locX, uint8_t locY);
void drawGrass(grassState gs, uint8_t locX, uint8_t locY);
void drawMap();
void drawStatic(const g_pixel_t* tileImg, g_point_t* pos);
void drawInitMenu(void);
void printScore(uint8_t playerID, uint16_t score);
void printPokemon(uint8_t playerID, char* pokemon);
void printMenu(uint8_t playerID, menuState ms, int8_t pb, int8_t gb, int8_t ub, char* text);

void printStats(uint8_t time, char* text);

bool isTreeTile(uint8_t locX, uint8_t locY);
bool isRockTile(uint8_t locX, uint8_t locY);

#endif /* DRAWPOKEMON_H_ */
