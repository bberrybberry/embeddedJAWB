/*
 * map.h
 *
 *  Created on: Apr 22, 2017
 *      Author: Aaron
 */

#ifndef MAP_H_
#define MAP_H_

#include "genPlayerL.h"
#include "genPlayerR.h"
#include "genPlayerS.h"
#include "blackPokePlayer.h"
#include "black16x12.h"
#include "white16x12.h"
#include "graphics.h"

#define WIDTH				320
#define HEIGHT				240
#define TEXT_TILES			8
#define TILE_X				16
#define TILE_Y				12
#define GRID_X				WIDTH / TILE_X - TEXT_TILES
#define GRID_Y				HEIGHT / TILE_Y

g_pixel_t* gPLTilePtr = &genPlayerL[0];
g_pixel_t* gPRTilePtr = &genPlayerR[0];
g_pixel_t* gPSTilePtr = &genPlayerS[0];
g_pixel_t* blackTilePtr = &black16x12[0];
g_pixel_t* whiteTilePtr = &white16x12[0];

g_pixel_t* map[GRID_X * GRID_Y];




#endif /* MAP_H_ */
