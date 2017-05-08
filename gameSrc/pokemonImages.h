/**
 * @file
 *
 * @author Breanna Higgins, Aaron Guidarelli, Walter Marroquin, Josh Velez
 *
 * @brief Collection of strctures that define the tile pictures used
 * throughout the game.
 */
/*
 *
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
#include "aaronL.h"
#include "aaronR.h"
#include "aaronS.h"
#include "black16x12.h"
#include "breannaR.h"
#include "breannaL.h"
#include "breannaS.h"
#include "genPlayerL.h"
#include "genPlayerR.h"
#include "genPlayerS.h"
#include "grass.h"
#include "ground.h"
#include "item.h"
#include "joshL.h"
#include "joshR.h"
#include "joshS.h"
#include "rocks.h"
#include "shakingGrass.h"
#include "trees.h"
#include "waltL.h"
#include "waltR.h"
#include "waltS.h"
#include "white16x12.h"

/**
 * @var gCntx
 * @brief Graphics context for Muhlbaier's graphics functions
 */
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

//players
/**
 * @var aaronSTilePtr
 * @brief Pointer to standing Aaron player tile
 */
const g_pixel_t* aaronSTilePtr = &aaronS[0];

/**
 * @var aaronRTilePtr
 * @brief Pointer to right Aaron player tile
 */
const g_pixel_t* aaronRTilePtr = &aaronR[0];

/**
 * @var aaronLTilePtr
 * @brief Pointer to left Aaron player tile
 */
const g_pixel_t* aaronLTilePtr = &aaronL[0];

/**
 * @var breannaSTilePtr
 * @brief Pointer to standing Breanna player tile
 */
const g_pixel_t* breannaSTilePtr = &breannaS[0];

/**
 * @var breannaRTilePtr
 * @brief Pointer to right Breanna player tile
 */
const g_pixel_t* breannaRTilePtr = &breannaR[0];

/**
 * @var breannaLTilePtr
 * @brief Pointer to left Breanna player tile
 */
const g_pixel_t* breannaLTilePtr = &breannaL[0];
/**
 * @var itemTilePtr
 * @brief Pointer to item on grass tile
 */
const g_pixel_t* itemTilePtr = &item[0];
/**
 * @var joshSTilePtr
 * @brief Pointer to standing Josh player tile
 */
const g_pixel_t* joshSTilePtr = &joshS[0];

/**
 * @var joshRTilePtr
 * @brief Pointer to right Josh player tile
 */
const g_pixel_t* joshRTilePtr = &joshR[0];

/**
 * @var joshLTilePtr
 * @brief Pointer to left Josh player tile
 */
const g_pixel_t* joshLTilePtr = &joshL[0];

/**
 * @var waltSTilePtr
 * @brief Pointer to standing Walt player tile
 */
const g_pixel_t* waltSTilePtr = &waltS[0];

/**
 * @var waltRTilePtr
 * @brief Pointer to right Walt player tile
 */
const g_pixel_t* waltRTilePtr = &waltR[0];

/**
 * @var waltLTilePtr
 * @brief Pointer to left Walt player tile
 */
const g_pixel_t* waltLTilePtr = &waltL[0];

//static ground

/**
 * @var groundTilePtr
 * @brief Pointer to the ground tile
 */
const g_pixel_t* groundTilePtr = &ground[0];

/**
 * @var treesTilePtr
 * @brief Pointer to the tree tile
 */
const g_pixel_t* treesTilePtr = &trees[0];

/**
 * @var rocksTilePtr
 * @brief Pointer to the rocks tile
 */
const g_pixel_t* rocksTilePtr = &rocks[0];

//playable ground

/**
 * @var grassTilePtr
 * @brief Pointer to normal grass tile
 */
const g_pixel_t* grassTilePtr = &grass[0];

/**
 * @var shakingGrassTilePtr
 * @brief Pointer to shaking grass tile pointer
 */
const g_pixel_t* shakingGrassTilePtr = &shakingGrass[0];

//other

/**
 * @var blackTilePtr
 * @brief Pointer to a tile of black pixels
 */
const g_pixel_t* blackTilePtr = &black16x12[0];



#endif /* POKEMONIMAGES_H_ */
