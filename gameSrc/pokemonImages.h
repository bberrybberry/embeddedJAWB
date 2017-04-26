/*
 * pokemonImages.h
 *
 *  Created on: Apr 25, 2017
 *      Author: bbhig
 *
 * A lot of this code is based around map.h
 */

#ifndef POKEMONIMAGES_H_
#define POKEMONIMAGES_H_

//Images
#include "genPlayerL.h"
#include "genPlayerR.h"
#include "genPlayerS.h"
#include "black16x12.h"
#include "white16x12.h"
#include "grass.h"
#include "ground.h"
#include "trees.h"
#include "rocks.h"
#include "aaronR.h"
#include "aaronL.h"
#include "breannaR.h"
#include "breannaL.h"
#include "waltR.h"
#include "waltL.h"

//TODO: Aaron: Explain what this is and tell us if this the correct way to store this
graphics_t gCntx;

/////////////////////////////////////////////////////////////////////////////////////
//
// Defines
//
/////////////////////////////////////////////////////////////////////////////////////
#define WIDTH               320
#define HEIGHT              240
#define TEXT_TILES          8
#define TILE_X              16
#define TILE_Y              12
#define GRID_X              ((WIDTH / TILE_X) - TEXT_TILES)
#define GRID_Y              (HEIGHT / TILE_Y)


/////////////////////////////////////////////////////////////////////////////////////
//
// Image pointers
//
/////////////////////////////////////////////////////////////////////////////////////
//g_pixel_t* gPLTilePtr = &genPlayerL[0];
//g_pixel_t* gPRTilePtr = &genPlayerR[0];
//g_pixel_t* gPSTilePtr = &genPlayerS[0];
//g_pixel_t* whiteTilePtr = &white16x12[0];

//players
g_pixel_t* aaronRTilePtr = &aaronR[0];
g_pixel_t* aaronLTilePtr = &aaronL[0];
g_pixel_t* breannaRTilePtr = &breannaR[0];
g_pixel_t* breannaLTilePtr = &breannaL[0];
g_pixel_t* waltRTilePtr = &waltR[0];
g_pixel_t* waltLTilePtr = &waltL[0];

//static ground
g_pixel_t* goundTilePtr = &ground[0];
g_pixel_t* treesTilePtr = &trees[0];
g_pixel_t* rocksTilePtr = &rocks[0];

//playable ground
g_pixel_t* grassTilePtr = &grass[0];

//other
g_pixel_t* blackTilePtr = &black16x12[0];

/////////////////////////////////////////////////////////////////////////////////////
//
// Structs
//
/////////////////////////////////////////////////////////////////////////////////////

typedef struct {
    g_pixel_t* map[GRID_X * GRID_Y];
} MapStruct;
MapStruct map;


#endif /* POKEMONIMAGES_H_ */