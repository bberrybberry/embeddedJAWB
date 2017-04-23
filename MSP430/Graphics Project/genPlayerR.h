/**
 * @file
 * This is an autogenerated file
 * edit at your own risk.
 * Generated from an image located at genPlayer_r.png
 *
 * Each entry follows the format outlined below
 *
 *			1		1		2		2		2	bits
 *			T		X		BB		GG		RR	LSB
 * 
 * Assumes the tile is being draw from left to right, top to bottom.
 * Now supports transparent pixels!
 */


#ifndef _GENPLAYERR_H_
#define _GENPLAYERR_H_

#include "graphics.h"

/**
 * @def GENPLAYERR_TILE_X
 * @brief Number of pixels along x direction
 */
#define GENPLAYERR_TILE_X	16
/**
 * @def GENPLAYERR_TILE_Y
 * @brief Number of pixels along y direction
 */
#define GENPLAYERR_TILE_Y	12

/**
 * @var genPlayerR[GENPLAYERR_TILE_X * GENPLAYERR_TILE_Y]
 * @brief Pixel array that makes up the image genPlayer_r.png
 */
g_pixel_t genPlayerR[GENPLAYERR_TILE_X * GENPLAYERR_TILE_Y] = {
	0xbf,	0xbf,	0xbf,	0xbf,	0xbf,	0x3,	0x3,	0x3,	0x3,	0x3,	0x3,	0x3,	0xbf,	0xbf,	0xbf,	0xbf,	
	0xbf,	0xbf,	0xbf,	0xbf,	0x3,	0x3,	0x3,	0x3f,	0x3f,	0x3f,	0x3,	0x3,	0x2,	0xbf,	0xbf,	0xbf,	
	0xbf,	0xbf,	0xbf,	0xbf,	0x2,	0x2,	0x3f,	0x3,	0x3,	0x3,	0x3f,	0x2,	0x2,	0xbf,	0xbf,	0xbf,	
	0xbf,	0x3,	0x3,	0x3,	0x3,	0x3,	0x3,	0x3,	0x3,	0x3,	0x3,	0x3,	0x2,	0x1,	0xbf,	0xbf,	
	0xbf,	0xbf,	0x2,	0x2,	0x2,	0x2,	0x2,	0x2,	0x2,	0x2,	0x6,	0x6,	0x1,	0x6,	0xbf,	0xbf,	
	0xbf,	0xbf,	0xbf,	0xbf,	0x1b,	0x1b,	0x20,	0x1b,	0x1b,	0x1b,	0x20,	0x1b,	0x6,	0xbf,	0xbf,	0xbf,	
	0xbf,	0xbf,	0xbf,	0xbf,	0xbf,	0x1b,	0x1b,	0x1b,	0x1b,	0x1b,	0x1b,	0x1b,	0xbf,	0xbf,	0xbf,	0xbf,	
	0xbf,	0xbf,	0xbf,	0xbf,	0x1b,	0x6,	0x4,	0x4,	0x2a,	0x4,	0x4,	0x6,	0xbf,	0xbf,	0xbf,	0xbf,	
	0xbf,	0xbf,	0xbf,	0x1b,	0x1b,	0xbf,	0x8,	0x8,	0x4,	0x8,	0x8,	0x1b,	0x1b,	0xbf,	0xbf,	0xbf,	
	0xbf,	0xbf,	0xbf,	0xbf,	0xbf,	0xbf,	0x8,	0x8,	0x4,	0x8,	0x8,	0xbf,	0xbf,	0xbf,	0xbf,	0xbf,	
	0xbf,	0xbf,	0xbf,	0xbf,	0xbf,	0xbf,	0x20,	0x20,	0xbf,	0x20,	0x0,	0x0,	0xbf,	0xbf,	0xbf,	0xbf,	
	0xbf,	0xbf,	0xbf,	0xbf,	0xbf,	0xbf,	0x0,	0x1b,	0xbf,	0x0,	0x0,	0xbf,	0xbf,	0xbf,	0xbf,	0xbf
	};

#endif
