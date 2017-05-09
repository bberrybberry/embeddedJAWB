/**
 * @file
 * This is an autogenerated file
 * edit at your own risk.
 * Generated from an image located at trees.png
 *
 * Each entry follows the format outlined below
 *
 *			1		1		2		2		2	bits
 *			T		X		BB		GG		RR	LSB
 * 
 * Assumes the tile is being draw from left to right, top to bottom.
 * Now supports transparent pixels!
 * @author Aaron Guidarelli
 * @addtogroup graphics
 * @{
 */


#ifndef _TREES_H_
#define _TREES_H_

#include "graphics.h"

/**
 * @def TREES_TILE_X
 * @brief Number of pixels along x direction
 */
#define TREES_TILE_X	16
/**
 * @def TREES_TILE_Y
 * @brief Number of pixels along y direction
 */
#define TREES_TILE_Y	12

/**
 * @var trees[TREES_TILE_X * TREES_TILE_Y]
 * @brief Pixel array that makes up the image trees.png
 */
const g_pixel_t trees[TREES_TILE_X * TREES_TILE_Y] = {
	0x8,	0x8,	0x4,	0x4,	0x18,	0x18,	0x18,	0x18,	0x4,	0x4,	0x18,	0x18,	0x18,	0x4,	0x4,	0x8,	
	0x8,	0x4,	0x18,	0x18,	0x18,	0x18,	0x18,	0x18,	0x18,	0x4,	0x18,	0x18,	0x18,	0x18,	0x18,	0x4,	
	0x4,	0x18,	0x4,	0x18,	0x4,	0x18,	0x18,	0x4,	0x4,	0x18,	0x4,	0x18,	0x18,	0x18,	0x4,	0x18,	
	0x18,	0x18,	0x18,	0x4,	0x18,	0x18,	0x4,	0x18,	0x4,	0x18,	0x18,	0x4,	0x18,	0x4,	0x18,	0x18,	
	0x18,	0x18,	0x18,	0x18,	0x18,	0x18,	0x18,	0x18,	0x18,	0x18,	0x18,	0x4,	0x18,	0x18,	0x18,	0x18,	
	0x18,	0x4,	0x4,	0x1,	0x18,	0x18,	0x18,	0x1,	0x4,	0x4,	0x18,	0x4,	0x18,	0x1,	0x18,	0x4,	
	0x4,	0x18,	0x4,	0x6,	0x1,	0x18,	0x1,	0x6,	0x4,	0x18,	0x1,	0x4,	0x1,	0x6,	0x18,	0x4,	
	0x8,	0x4,	0x18,	0x18,	0x6,	0x6,	0x6,	0x18,	0x18,	0x4,	0x6,	0x1,	0x6,	0x6,	0x4,	0x8,	
	0x8,	0x8,	0x4,	0x4,	0x6,	0x6,	0x6,	0x4,	0x4,	0x8,	0x4,	0x1,	0x6,	0x6,	0x8,	0x8,	
	0x8,	0x8,	0x8,	0x8,	0x6,	0x6,	0x1,	0x8,	0x8,	0x8,	0x8,	0x6,	0x6,	0x1,	0x8,	0x8,	
	0x8,	0x8,	0x8,	0x6,	0x6,	0x6,	0x1,	0x6,	0x8,	0x8,	0x6,	0x6,	0x6,	0x1,	0x6,	0x8,	
	0x8,	0x8,	0x8,	0x8,	0x6,	0x1,	0x6,	0x8,	0x8,	0x8,	0x8,	0x6,	0x1,	0x6,	0x8,	0x8
	};

#endif
/** @}*/
