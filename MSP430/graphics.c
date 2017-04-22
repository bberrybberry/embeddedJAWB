/*
 * graphics.c
 *
 *  Created on: Apr 1, 2017
 *      Author: Aaron
 */

#include "graphics.h"
#include "hal_graphics.h"
#include <stdarg.h>
#include <stdio.h>

#define MAX_CHAR_LIMIT	200

void Graphics_Init(graphics_t * gptr) {
	initDisplay();
	Graphics_SetInputScreenSize(gptr, SCREEN_SIZE_320X240);
}

void Graphics_SetInputScreenSize(graphics_t * gptr, enum screen_size_e screen_size) {
	gptr->screen_size = screen_size;
}

void Graphics_DrawTile(graphics_t * gptr, g_point_t position, g_pixel_t *tile[], char x, char y) {
	volatile uint16_t i, j;
	for(i = 0; i < y; i++) {
		for(j = 0; j < x; j++) {
			if ((*(*tile + (j+i*x))).transparent == 0) {
				drawPixel(pixelToHex((uint8_t)(*(*tile+(j+i*x))).all), position.x + j, position.y + i);
			}
		}
	}
}

void Graphics_SetBackground(graphics_t * gptr, uint8_t color[3]) {
	gptr->background[0] = color[0];
	gptr->background[1] = color[1];
	gptr->background[2] = color[2];
}

void Graphics_SetForeground(graphics_t * gptr, uint8_t color[3]) {
	gptr->foreground[0] = color[0];
	gptr->foreground[1] = color[1];
	gptr->foreground[2] = color[2];
}

void Graphics_DrawLine(graphics_t * gptr, g_point_t p1, g_point_t p2) {
	line_t line;

	line.x1 = p1.x; line.y1 = p1.y;
	line.x2 = p2.x; line.y2 = p2.y;

	drawLine(colorToHex(gptr->foreground), &line);
}

void Graphics_DrawPixel(graphics_t * gptr, g_point_t p) {
	drawPixel(colorToHex(gptr->foreground), p.x, p.y);
}

void Graphics_DrawRectangle(graphics_t * gptr, g_point_t top_left, g_point_t bottom_right) {
	rectangle_t rect;

	switch(gptr->screen_size) {
	case SCREEN_SIZE_320X240:
		rect.minX = top_left.x;
		rect.minY = top_left.y;
		rect.maxX = bottom_right.x;
		rect.maxY = bottom_right.y;
		break;
	case SCREEN_SIZE_128X64:
		rect.minX = (top_left.x / 128) * 320;
		rect.minY = (top_left.y / 64) * 240;
		rect.maxX = (bottom_right.x / 128) * 320;
		rect.maxY = (bottom_right.y / 64) * 240;
		break;
	case SCREEN_SIZE_160X128:
		rect.minX = (top_left.x / 160) * 320;
		rect.minY = (top_left.y / 128) * 240;
		rect.maxX = (bottom_right.x / 160) * 320;
		rect.maxY = (bottom_right.y / 128) * 240;
		break;
	default:
		break;
	}

	drawRectangle(colorToHex(gptr->foreground), &rect);
}

void Graphics_DrawText(graphics_t * gptr, g_point_t position, char * str, ...) {
	int32_t len = 0;
	char string[MAX_CHAR_LIMIT];
	char* strPtr = &string[0];
	va_list valist;
	va_start(valist, str);
	vsprintf(strPtr, str, valist);

	while(*strPtr != '\0') {
		len++;
		strPtr++;
	}

	drawString(colorToHex(gptr->foreground), &string[0], len, position.x, position.y, true);
}

void Graphics_ClearScreen(graphics_t * gptr) {
	clearDisplay();
}

void Graphics_UpdateScreen(graphics_t * gptr) {

}



