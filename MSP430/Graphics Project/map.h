/*
 * map.h
 *
 *  Created on: Apr 22, 2017
 *      Author: Aaron
 */

#ifndef MAP_H_
#define MAP_H_

#include "genPokePlayer.h"
#include "blackPokePlayer.h"
#include "black16x12.h"
#include "white16x12.h"
#include "graphics.h"

#define WIDTH				320
#define HEIGHT				240
#define TILE_X				16
#define TILE_Y				12
#define GRID_X				WIDTH / TILE_X
#define GRID_Y				HEIGHT / TILE_Y

g_pixel_t* gPPTilePtr = &black16x12[0];//&genPokePlayer[0];
g_pixel_t* blackTilePtr = &black16x12[0];
g_pixel_t* whiteTilePtr = &white16x12[0];

g_pixel_t* map[GRID_X * GRID_Y];// = {
//		whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr,
//		whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr,
//		whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr,
//		whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr,
//		whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr,
//		whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr,
//		whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr,
//		whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr,
//		whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr,
//		whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr,
//		whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr,
//		whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr,
//		whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr,
//		whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr,
//		whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr,
//		whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr,
//		whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr,
//		whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr,
//		whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr,
//		whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr, whiteTilePtr
//};



#endif /* MAP_H_ */
