/**
 * @file
 * This is an autogenerated file
 * edit at your own risk.
 * Generated from an image located at josh_l.png
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


#ifndef _JOSHL_H_
#define _JOSHL_H_

#include "graphics.h"

/**
 * @def JOSHL_TILE_X
 * @brief Number of pixels along x direction
 */
#define JOSHL_TILE_X	16
/**
 * @def JOSHL_TILE_Y
 * @brief Number of pixels along y direction
 */
#define JOSHL_TILE_Y	12

/**
 * @var joshL[JOSHL_TILE_X * JOSHL_TILE_Y]
 * @brief Pixel array that makes up the image josh_l.png
 */
const g_pixel_t joshL[JOSHL_TILE_X * JOSHL_TILE_Y] = {
	0xbf,	0xbf,	0xbf,	0xbf,	0xbf,	0xf,	0xf,	0xf,	0xf,	0xf,	0xf,	0xf,	0x8f,	0xbf,	0xbf,	0xbf,	
	0xbf,	0xbf,	0xbf,	0xbf,	0xf,	0xf,	0xf,	0x3f,	0x3f,	0x3f,	0xf,	0xf,	0x17,	0x97,	0xbf,	0xbf,	
	0xbf,	0xbf,	0xbf,	0xbf,	0x17,	0x17,	0x3f,	0xf,	0xf,	0xf,	0x3f,	0x17,	0x17,	0x97,	0xbf,	0xbf,	
	0xbf,	0xf,	0xf,	0xf,	0xf,	0xf,	0xf,	0xf,	0xf,	0xf,	0xf,	0xf,	0x17,	0x1,	0xbf,	0xbf,	
	0xbf,	0x8f,	0x17,	0x17,	0x17,	0x17,	0x17,	0x17,	0x17,	0x17,	0x6,	0x6,	0x1,	0x0,	0xbf,	0xbf,	
	0xbf,	0x8f,	0x97,	0x97,	0x1b,	0x1b,	0x0,	0x1b,	0x1b,	0x1b,	0x0,	0x1b,	0x0,	0x81,	0xbf,	0xbf,	
	0xbf,	0xbf,	0x97,	0x97,	0x97,	0x1b,	0x1b,	0x1b,	0x1b,	0x1b,	0x1b,	0x1b,	0x81,	0x81,	0xbf,	0xbf,	
	0xbf,	0xbf,	0xbf,	0xbf,	0xbf,	0x6,	0x1,	0x1,	0x2a,	0x1,	0x1,	0x6,	0x1b,	0x80,	0xbf,	0xbf,	
	0xbf,	0xbf,	0xbf,	0xbf,	0x1b,	0x1b,	0x36,	0x36,	0x1,	0x36,	0x36,	0xb6,	0x1b,	0x1b,	0xbf,	0xbf,	
	0xbf,	0xbf,	0xbf,	0xbf,	0xbf,	0x9b,	0x36,	0x36,	0x1,	0x36,	0x36,	0xb6,	0x9b,	0x9b,	0xbf,	0xbf,	
	0xbf,	0xbf,	0xbf,	0xbf,	0xbf,	0x0,	0x0,	0x20,	0xb6,	0x20,	0x20,	0xb6,	0xbf,	0x9b,	0xbf,	0xbf,	
	0xbf,	0xbf,	0xbf,	0xbf,	0xbf,	0x80,	0x0,	0x0,	0xb6,	0x1b,	0x0,	0xb6,	0xbf,	0xbf,	0xbf,	0xbf
	};

#endif
/** @}*/
