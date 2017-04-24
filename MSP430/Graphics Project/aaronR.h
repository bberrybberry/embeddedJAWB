/**
 * @file
 * This is an autogenerated file
 * edit at your own risk.
 * Generated from an image located at Images/aaron_r.png
 *
 * Each entry follows the format outlined below
 *
 *			1		1		2		2		2	bits
 *			T		X		BB		GG		RR	LSB
 * 
 * Assumes the tile is being draw from left to right, top to bottom.
 * Now supports transparent pixels!
 */


#ifndef _AARONR_H_
#define _AARONR_H_

#include "graphics.h"

/**
 * @def AARONR_TILE_X
 * @brief Number of pixels along x direction
 */
#define AARONR_TILE_X	16
/**
 * @def AARONR_TILE_Y
 * @brief Number of pixels along y direction
 */
#define AARONR_TILE_Y	12

/**
 * @var aaronR[AARONR_TILE_X * AARONR_TILE_Y]
 * @brief Pixel array that makes up the image Images/aaron_r.png
 */
g_pixel_t aaronR[AARONR_TILE_X * AARONR_TILE_Y] = {
	0xbf,	0xbf,	0xbf,	0xbf,	0xbf,	0x30,	0x30,	0x30,	0x30,	0x30,	0x30,	0x30,	0xbf,	0xbf,	0xbf,	0xbf,	
	0xbf,	0xbf,	0xbf,	0xbf,	0x30,	0x30,	0x30,	0x3f,	0x3f,	0x3f,	0x30,	0x30,	0x10,	0xbf,	0xbf,	0xbf,	
	0xbf,	0xbf,	0xbf,	0xbf,	0x10,	0x10,	0x3f,	0x30,	0x30,	0x30,	0x3f,	0x10,	0x10,	0xbf,	0xbf,	0xbf,	
	0xbf,	0x30,	0x30,	0x30,	0x30,	0x30,	0x30,	0x30,	0x30,	0x30,	0x30,	0x30,	0x10,	0xf,	0xbf,	0xbf,	
	0xbf,	0xbf,	0x10,	0x10,	0x10,	0x10,	0x10,	0x10,	0x10,	0x10,	0x6,	0x6,	0xf,	0xb,	0xbf,	0xbf,	
	0xbf,	0xbf,	0xbf,	0xbf,	0x1b,	0x1b,	0x39,	0x1b,	0x1b,	0x1b,	0x39,	0x1b,	0xb,	0xbf,	0xbf,	0xbf,	
	0xbf,	0xbf,	0xbf,	0xbf,	0xbf,	0x1b,	0x1b,	0x1b,	0x1b,	0x1b,	0x1b,	0x1b,	0xbf,	0xbf,	0xbf,	0xbf,	
	0xbf,	0xbf,	0xbf,	0xbf,	0x1b,	0x6,	0x1,	0x1,	0x2a,	0x1,	0x1,	0x6,	0xbf,	0xbf,	0xbf,	0xbf,	
	0xbf,	0xbf,	0xbf,	0x1b,	0x1b,	0xbf,	0x7,	0x7,	0x1,	0x7,	0x7,	0x1b,	0x1b,	0xbf,	0xbf,	0xbf,	
	0xbf,	0xbf,	0xbf,	0xbf,	0xbf,	0xbf,	0x7,	0x7,	0x1,	0x7,	0x7,	0xbf,	0xbf,	0xbf,	0xbf,	0xbf,	
	0xbf,	0xbf,	0xbf,	0xbf,	0xbf,	0xbf,	0x20,	0x20,	0xbf,	0x20,	0x0,	0x0,	0xbf,	0xbf,	0xbf,	0xbf,	
	0xbf,	0xbf,	0xbf,	0xbf,	0xbf,	0xbf,	0x0,	0x1b,	0xbf,	0x0,	0x0,	0xbf,	0xbf,	0xbf,	0xbf,	0xbf
	};

#endif