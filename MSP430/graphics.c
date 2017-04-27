/*
 * graphics.c
 *
 *  Created on: Apr 1, 2017
 *      Author: Aaron
 */
/**
 * @file
 * @brief Source file for graphics.c
 *
 * This is the source code for running the TI Launchpad LCD Boosterpack
 * for the MSP430F5529.
 */
#include "graphics.h"
#include "hal_graphics.h"
#include <stdarg.h>
#include <stdio.h>

/**
 * @def MAX_CHAR_LIMIT
 * @brief This is an arbitrary limit for the number of characters that can be drawn on one line
 *
 * @details This is used to define the size of the char array the vsprintf function stores the resulting string
 */
#define MAX_CHAR_LIMIT	200

/**
 * @fn Graphics_Init(graphics_t * gptr)
 * @param gptr Pointer to the graphics context
 * @brief Initializes the graphics module
 *
 * @details Initializes the SPI for the boosterpack LCD and sets the screen size to 320x240
 */
void Graphics_Init(graphics_t * gptr) {
	initDisplay();
	Graphics_SetInputScreenSize(gptr, SCREEN_SIZE_320X240);
}

/**
 * @fn Graphics_SetInputScreenSize(graphics_t * gptr, enum screen_size_e screen_size)
 * @param gptr Pointer to the graphics context
 * @param screen_size Screen size that the graphics context will be set to
 * @brief Sets the screen size of the graphics context
 */
void Graphics_SetInputScreenSize(graphics_t * gptr, enum screen_size_e screen_size) {
	gptr->screen_size = screen_size;
}

/**
 * @fn Graphics_DrawTile(graphics_t * gptr, g_point_t position, g_pixel_t *tile[], char x, char y)
 * @param gptr Pointer to the graphics context
 * @param position Point of the top left corner of the tile
 * @param *tile[] Array of pointers to g_pixel_t structures
 * @param x X size, or width, of the tile
 * @param y Y size, or height, of the tile
 * @brief Draws the pixels defined in the tile array according to the given width and height
 *
 * @details The order in which the tile is drawn is from left to right, top to bottom. Meaning it starts at
 * the top left corner, moves right and then goes down when the width is reached.
 */
void Graphics_DrawTile(graphics_t * gptr, g_point_t position, g_pixel_t *tile[], char x, char y) {
	volatile uint16_t i, j;
	char width, height;
	switch(gptr->screen_size) {
	case SCREEN_SIZE_320X240:
		width = x;
		height = y;
		break;
	case SCREEN_SIZE_128X64:
		position.x = (uint16_t)((position.x / 128.0f) * 320);
		position.y = (uint16_t)((position.y / 64.0f) * 240);
		width = (char)((x / 128.0f) * 320);
		height = (char)((y / 64.0f) * 240);
		break;
	case SCREEN_SIZE_160X128:
		position.x = (uint16_t)((position.x / 160.0f) * 320);
		position.y = (uint16_t)((position.y / 128.0f) * 240);
		width = (char)((x / 160.0f) * 320);
		height = (char)((y / 128.0f) * 240);
		break;
	default:
		break;
	}

	for(i = 0; i < height; i++) {
		for(j = 0; j < width; j++) {
			if ((*(*tile + (j+i*width))).transparent == 0) {
				drawPixel(pixelToHex((uint8_t)(*(*tile+(j+i*width))).all), position.x + j, position.y + i);
			}
		}
	}
}

/**
 * @fn Graphics_SetBackground(graphics_t * gptr, uint8_t color[3])
 * @param gptr Pointer to the graphics context
 * @param color[3] Array of colors in RGB hex format
 * @brief Sets the background color of the display to the given color
 *
 * @details The color array is set up as color[0] = R, color[1] = G, color[2] = B
 */
void Graphics_SetBackground(graphics_t * gptr, uint8_t color[3]) {
	gptr->background[0] = color[0];
	gptr->background[1] = color[1];
	gptr->background[2] = color[2];
}

/**
 * @fn Graphics_SetForeground(graphics_t * gptr, uint8_t color[3])
 * @param gptr Pointer to the graphics context
 * @param color[3] Array of colors in RGB hex format
 * @brief Sets the foreground color of the display to the given color
 *
 * @details The color array is set up as color[0] = R, color[1] = G, color[2] = B
 */
void Graphics_SetForeground(graphics_t * gptr, uint8_t color[3]) {
	gptr->foreground[0] = color[0];
	gptr->foreground[1] = color[1];
	gptr->foreground[2] = color[2];
}

/**
 * @fn Graphics_DrawLine(graphics_t * gptr, g_point_t p1, g_point_t p2)
 * @param gptr Pointer to graphics context
 * @param p1 First point on the line
 * @param p2 Second point on the line
 * @brief Draws a line between the given points
 */
void Graphics_DrawLine(graphics_t * gptr, g_point_t p1, g_point_t p2) {
	line_t line;

	switch(gptr->screen_size) {
	case SCREEN_SIZE_320X240:
		line.x1 = p1.x; line.y1 = p1.y;
		line.x2 = p2.x; line.y2 = p2.y;
		break;
	case SCREEN_SIZE_128X64:
		line.x1 = (uint16_t)((p1.x / 128.0f) * 320);
		line.x2 = (uint16_t)((p2.x / 128.0f) * 320);
		line.y1 = (uint16_t)((p1.y / 64.0f) * 240);
		line.y2 = (uint16_t)((p2.y / 64.0f) * 240);
		break;
	case SCREEN_SIZE_160X128:
		line.x1 = (uint16_t)((p1.x / 160.0f) * 320);
		line.x2 = (uint16_t)((p2.x / 160.0f) * 320);
		line.y1 = (uint16_t)((p1.y / 128.0f) * 240);
		line.y2 = (uint16_t)((p2.y / 128.0f) * 240);
		break;
	default:
		break;
	}

	drawLine(colorToHex(gptr->foreground), &line);
}

/**
 * @fn Graphics_DrawPixel(graphics_t * gptr, g_point_t p)
 * @param gptr Pointer to the graphics context
 * @param p Point of the pixel
 * @brief Draws a pixel at the specified point with the foreground color
 */
void Graphics_DrawPixel(graphics_t * gptr, g_point_t p) {
	switch (gptr->screen_size) {
	case SCREEN_SIZE_320X240:
		break;
	case SCREEN_SIZE_128X64:
		p.x = (uint16_t)((p.x / 128.0f) * 320);
		p.y = (uint16_t)((p.y / 64.0f) * 240);
		break;
	case SCREEN_SIZE_160X128:
		p.x = (uint16_t)((p.x / 160.0f) * 320);
		p.y = (uint16_t)((p.y / 128.0f) * 240);
		break;
	default:
		break;
	}

	drawPixel(colorToHex(gptr->foreground), p.x, p.y);
}

/**
 * @fn Graphics_DrawRectangle(graphics_t * gptr, g_point_t top_left, g_point_t bottom_right)
 * @param gptr Pointer to the graphics context
 * @param top_left Point of the top left corner of the rectangle
 * @param bottom_right Point of the bottom right corner of the rectangle
 * @brief Draws a rectangle with the specified corners with the foreground color
 */
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
		rect.minX = (uint16_t)((top_left.x / 128.0f) * 320);
		rect.minY = (uint16_t)((top_left.y / 64.0f) * 240);
		rect.maxX = (uint16_t)((bottom_right.x / 128.0f) * 320);
		rect.maxY = (uint16_t)((bottom_right.y / 64.0f) * 240);
		break;
	case SCREEN_SIZE_160X128:
		rect.minX = (uint16_t)((top_left.x / 160.0f) * 320);
		rect.minY = (uint16_t)((top_left.y / 128.0f) * 240);
		rect.maxX = (uint16_t)((bottom_right.x / 160.0f) * 320);
		rect.maxY = (uint16_t)((bottom_right.y / 128.0f) * 240);
		break;
	default:
		break;
	}

	drawRectangle(colorToHex(gptr->foreground), &rect);
}

/**
 * @fn Graphics_DrawText(graphics_t * gptr, g_point_t position, char * str, ...)
 * @param gptr Pointer to the graphics context
 * @param position Top left point of the text
 * @param str Pointer to char array that stores the string
 * @param ... Variable argument list for "printf"ing onto the screen
 * @brief Prints the string on the screen at the specified point
 *
 * @details Allows for full printf support with all options available
 */
void Graphics_DrawText(graphics_t * gptr, g_point_t position, char * str, ...) {
	int32_t len = 0;
	char string[MAX_CHAR_LIMIT];
	char* strPtr = &string[0];
	va_list valist;

	switch(gptr->screen_size) {
	case SCREEN_SIZE_320X240:
		break;
	case SCREEN_SIZE_128X64:
		position.x = (uint16_t)((position.x / 128.0f) * 320);
		position.y = (uint16_t)((position.y / 64.0f) * 240);
		break;
	case SCREEN_SIZE_160X128:
		position.x = (uint16_t)((position.x / 160.0f) * 320);
		position.y = (uint16_t)((position.y / 128.0f) * 240);
		break;
	default:
		break;
	}

	va_start(valist, str);
	vsprintf(strPtr, str, valist);

	while(*strPtr != '\0') {
		len++;
		strPtr++;
	}

	drawString(colorToHex(gptr->foreground), &string[0], len, position.x, position.y, true);
}

/**
 * @fn Graphics_ClearScreen(graphics_t * gptr)
 * @param gptr Pointer to the graphics context
 * @brief Sets the entire screen to black
 */
void Graphics_ClearScreen(graphics_t * gptr) {
	clearDisplay();
}

/**
 * @fn Graphics_UpdateScreen(graphics_t * gptr)
 * @param gptr Pointer to the graphics context
 * @brief Ensures that everything sent to be displayed is displayed
 */
void Graphics_UpdateScreen(graphics_t * gptr) {

}



