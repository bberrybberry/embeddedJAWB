/**
 * @file
 * This is an autogenerated file
 * edit at your own risk.
 * Generated from an image located at blackPokePlayer.png
 *
 * Each entry follows the format outlined below
 *
 *			1		1		2		2		2	bits
 *			T		X		BB		GG		RR	LSB
 * 
 * Assumes the tile is being draw from left to right, top to bottom.
 * Now supports transparent pixels!
 */


#ifndef _BLACKPOKEPLAYER_H_
#define _BLACKPOKEPLAYER_H_

#include "graphics.h"

/**
 * @def BLACKPOKEPLAYER_TILE_X
 * @brief Number of pixels along x direction
 */
#define BLACKPOKEPLAYER_TILE_X	12
/**
 * @def BLACKPOKEPLAYER_TILE_Y
 * @brief Number of pixels along y direction
 */
#define BLACKPOKEPLAYER_TILE_Y	16

/**
 * @var blackPokePlayer[BLACKPOKEPLAYER_TILE_X * BLACKPOKEPLAYER_TILE_Y]
 * @brief Pixel array that makes up the image blackPokePlayer.png
 */
const g_pixel_t blackPokePlayer[BLACKPOKEPLAYER_TILE_X * BLACKPOKEPLAYER_TILE_Y] = {
	0xbf,	0xbf,	0xbf,	0xbf,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0xbf,	0xbf,	
	0xbf,	0xbf,	0xbf,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0xbf,	
	0xbf,	0xbf,	0xbf,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0xbf,	
	0xbf,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0xbf,	
	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	
	0xbf,	0xbf,	0xbf,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0xbf,	
	0xbf,	0xbf,	0xbf,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0xbf,	
	0xbf,	0xbf,	0xbf,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0xbf,	0xbf,	
	0xbf,	0xbf,	0xbf,	0xbf,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0xbf,	0xbf,	
	0xbf,	0xbf,	0xbf,	0xbf,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0xbf,	0xbf,	
	0xbf,	0xbf,	0xbf,	0xbf,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0xbf,	0xbf,	
	0xbf,	0xbf,	0xbf,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0xbf,	
	0xbf,	0xbf,	0xbf,	0xbf,	0xbf,	0x0,	0x0,	0x0,	0x0,	0xbf,	0xbf,	0xbf,	
	0xbf,	0xbf,	0xbf,	0xbf,	0xbf,	0x0,	0xbf,	0xbf,	0x0,	0xbf,	0xbf,	0xbf,	
	0xbf,	0xbf,	0xbf,	0xbf,	0xbf,	0x0,	0xbf,	0xbf,	0x0,	0xbf,	0xbf,	0xbf,	
	0xbf,	0xbf,	0xbf,	0xbf,	0x0,	0x0,	0xbf,	0xbf,	0x0,	0x0,	0xbf,	0xbf
	};

#endif
