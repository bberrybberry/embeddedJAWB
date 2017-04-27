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
const g_pixel_t* aaronRTilePtr = &aaronR[0];
const g_pixel_t* aaronLTilePtr = &aaronL[0];
const g_pixel_t* breannaRTilePtr = &breannaR[0];
const g_pixel_t* breannaLTilePtr = &breannaL[0];
const g_pixel_t* waltRTilePtr = &waltR[0];
const g_pixel_t* waltLTilePtr = &waltL[0];

//static ground
const g_pixel_t* goundTilePtr = &ground[0];
const g_pixel_t* treesTilePtr = &trees[0];
const g_pixel_t* rocksTilePtr = &rocks[0];

//playable ground
const g_pixel_t* grassTilePtr = &grass[0];

//other
const g_pixel_t* blackTilePtr = &black16x12[0];



#endif /* POKEMONIMAGES_H_ */
