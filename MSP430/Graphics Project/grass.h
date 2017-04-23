/**
 * @file
 * This is an autogenerated file
 * edit at your own risk.
 * Generated from an image located at grass.png
 *
 * Each entry follows the format outlined below
 *
 *			1		1		2		2		2	bits
 *			T		X		BB		GG		RR	LSB
 * 
 * Assumes the tile is being draw from left to right, top to bottom.
 * Now supports transparent pixels!
 */


#ifndef _GRASS_H_
#define _GRASS_H_

#include "graphics.h"

/**
 * @def GRASS_TILE_X
 * @brief Number of pixels along x direction
 */
#define GRASS_TILE_X	16
/**
 * @def GRASS_TILE_Y
 * @brief Number of pixels along y direction
 */
#define GRASS_TILE_Y	12

/**
 * @var grass[GRASS_TILE_X * GRASS_TILE_Y]
 * @brief Pixel array that makes up the image grass.png
 */
g_pixel_t grass[GRASS_TILE_X * GRASS_TILE_Y] = {
	0x8,	0x8,	0x8,	0x8,	0x8,	0x8,	0x8,	0x8,	0x8,	0x8,	0x8,	0x8,	0x8,	0x8,	0x8,	0x8,	
	0x8,	0x8,	0x8,	0x8,	0x8,	0x8,	0x8,	0x8,	0x8,	0x8,	0x8,	0x8,	0x8,	0x8,	0x8,	0x8,	
	0x8,	0x8,	0x8,	0x8,	0x8,	0x8,	0x8,	0x8,	0x8,	0x8,	0x8,	0x8,	0x8,	0x8,	0x8,	0x8,	
	0x8,	0x8,	0x8,	0x8,	0x8,	0x8,	0x8,	0x8,	0x8,	0x8,	0x8,	0x8,	0x8,	0x8,	0x8,	0x8,	
	0x8,	0x8,	0x8,	0x8,	0x8,	0x8,	0x4,	0x8,	0x8,	0x8,	0x8,	0x8,	0x8,	0x8,	0x8,	0x8,	
	0x8,	0x8,	0x8,	0x8,	0x8,	0x8,	0x8,	0x4,	0x8,	0x8,	0x8,	0x8,	0x8,	0x8,	0x8,	0x8,	
	0x8,	0x8,	0x8,	0x8,	0x4,	0x8,	0x8,	0x8,	0x8,	0x8,	0x8,	0x8,	0x4,	0x8,	0x8,	0x8,	
	0x8,	0x8,	0x8,	0x8,	0x8,	0x4,	0x8,	0x8,	0x8,	0x8,	0x8,	0x4,	0x8,	0x8,	0x8,	0x8,	
	0x8,	0x8,	0x8,	0x8,	0x8,	0x4,	0x8,	0x8,	0x4,	0x8,	0x8,	0x4,	0x8,	0x8,	0x8,	0x8,	
	0x8,	0x8,	0x8,	0x8,	0x8,	0x8,	0x8,	0x8,	0x8,	0x8,	0x8,	0x8,	0x8,	0x8,	0x8,	0x8,	
	0x8,	0x8,	0x8,	0x8,	0x8,	0x8,	0x8,	0x8,	0x8,	0x8,	0x8,	0x8,	0x8,	0x8,	0x8,	0x8,	
	0x8,	0x8,	0x8,	0x8,	0x8,	0x8,	0x8,	0x8,	0x8,	0x8,	0x8,	0x8,	0x8,	0x8,	0x8,	0x8
	};

#endif