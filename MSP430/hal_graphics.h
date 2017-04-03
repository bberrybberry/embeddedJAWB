/*
 * booster_graphics.h
 *
 *  Created on: Mar 27, 2017
 *      Author: Aaron
 *
 *      MSP must run at 25MHz
 */

#ifndef HAL_GRAPHICS_H_
#define HAL_GRAPHICS_H_

#include <msp430f5529.h>
#include "grlib.h"
#include "button.h"
#include "imageButton.h"
#include "radioButton.h"
#include "checkbox.h"
#include "driverlib.h"
#include "touch_F5529LP.h"
#include "LcdDriver/kitronix320x240x16_ssd2119_spi.h"
#include "Images/images.h"

#define WIDTH	320
#define HEIGHT	240

typedef struct rectangle_t {
	uint16_t minX;
	uint16_t minY;
	uint16_t maxX;
	uint16_t maxY;
} rectangle_t;

typedef struct line_t {
	uint16_t x1;
	uint16_t y1;
	uint16_t x2;
	uint16_t y2;
} line_t;

//typedef struct {
//	Graphics_Context g_sContext;
//} hal_graphics_t;

Graphics_Context g_sContext;

void initDisplay(void);

unsigned long pixelToHex(uint8_t pixel);
unsigned long colorToHex(uint8_t color[3]);

void clearDisplay(void);

void drawPixel(uint32_t color, uint16_t x, uint16_t y);
void drawLine(uint32_t color, line_t* line);
void drawRectangle(uint32_t color, rectangle_t* rect);
void fillRectangle(uint32_t color, rectangle_t* rect);
void drawThickRectangle(uint32_t color, uint8_t thickness, rectangle_t* rect);

void drawString(uint32_t color, char* string, int32_t length, uint16_t x, uint16_t y, uint8_t opaque);


#endif /* HAL_GRAPHICS_H_ */
