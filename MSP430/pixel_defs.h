/*
 * pixel_defs.h
 *
 *  Created on: Apr 21, 2017
 *      Author: Aaron
 */

#ifndef PIXEL_DEFS_H_
#define PIXEL_DEFS_H_

#define LOW_RED_PX		0x01
#define MED_RED_PX		0x02
#define HIGH_RED_PX		0x03

#define LOW_GREEN_PX	0x04
#define MED_GREEN_PX	0x08
#define HIGH_GREEN_PX	0x0C

#define LOW_BLUE_PX		0x10
#define MED_BLUE_PX		0x20
#define HIGH_BLUE_PX	0x30

#define LOW_WHITE_PX	LOW_RED_PX | LOW_GREEN_PX | LOW_BLUE_PX
#define MED_WHITE_PX	MED_RED_PX | MED_GREEN_PX | MED_BLUE_PX
#define HIGH_WHITE_PX	HIGH_RED_PX | HIGH_GREEN_PX | HIGH_BLUE_PX

#define BLACK_PX		0x00

#define TRANSPARENT		0x80
#define UNUSED			0x40


#endif /* PIXEL_DEFS_H_ */
