/*
 * booster_graphics.c
 *
 *  Created on: Mar 27, 2017
 *      Author: Aaron
 */

#include <hal_graphics.h>


void initDisplay(void) {
	Kitronix320x240x16_SSD2119Init();
	Graphics_initContext(&g_sContext, &g_sKitronix320x240x16_SSD2119);
	Graphics_setBackgroundColor(&g_sContext, GRAPHICS_COLOR_BLACK);
	Graphics_setFont(&g_sContext, &g_sFontCmss20b);
	Graphics_clearDisplay(&g_sContext);

	touch_initInterface();
}

unsigned long pixelToHex(uint8_t pixel) {
	unsigned long red, green, blue;
	const uint8_t multiplier = 85;

	red = multiplier * (pixel & 0x03);
	green = multiplier * ((pixel & (0x03 << 2)) >> 2);
	blue = multiplier * ((pixel & (0x03 << 4)) >> 4);
	//unsigned long color = (red << 16) | (green << 8) | (blue << 0);
	return (red << 16) | (green << 8) | (blue << 0);
}

unsigned long colorToHex(uint8_t color[3]) {
	return ((long)color[0] << 16) | ((long)color[1] << 8) | (color[2] << 0);
}

void clearDisplay(void) {
	Graphics_clearDisplay(&g_sContext);
}

void drawPixel(uint32_t color, uint16_t x, uint16_t y) {
	Graphics_drawPixel(&g_sContext, x, y);
}

void drawLine(uint32_t color, line_t* line) {
	Graphics_setForegroundColor(&g_sContext, color);
	Graphics_drawLine(&g_sContext, line->x1, line->y1, line->x2, line->y2);
}

void drawRectangle(uint32_t color, rectangle_t* rect) {
	Graphics_Rectangle rectangle = {rect->minX, rect->minY, rect->maxX, rect->maxY};
	Graphics_setForegroundColor(&g_sContext, color);
	Graphics_drawRectangle(&g_sContext, &rectangle);
}

void fillRectangle(uint32_t color, rectangle_t* rect) {
	Graphics_Rectangle rectangle = {rect->minX, rect->minY, rect->maxX, rect->maxY};
	Graphics_setForegroundColor(&g_sContext, color);
	Graphics_fillRectangle(&g_sContext, &rectangle);
}

void drawThickRectangle(uint32_t color, uint8_t thickness, rectangle_t* rect) {
	volatile int i;
	Graphics_Rectangle rectangle = {rect->minX, rect->minY, rect->maxX, rect->maxY};
	Graphics_setForegroundColor(&g_sContext, color);
	for (i = 0; i < thickness; i++) {
		Graphics_drawRectangle(&g_sContext, &rectangle);

		rectangle.xMax--;
		rectangle.xMin++;
		rectangle.yMax--;
		rectangle.yMin++;
		if ((rectangle.xMax == rectangle.xMin) || (rectangle.yMax == rectangle.yMin)) {
			break;
		}
	}

}

void drawString(uint32_t color, char* string, int32_t length, uint16_t x, uint16_t y, uint8_t opaque) {
	Graphics_setForegroundColor(&g_sContext, color);
	Graphics_drawString(&g_sContext, (int8_t*)string, length, 10, 10, opaque);
}
