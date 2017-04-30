/*
 * booster_graphics.h
 *
 *  Created on: Mar 27, 2017
 *      Author: Aaron
 *
 *      MSP must run at 25MHz
 */
/**
 * @file
 * @brief Header file for hal_graphics
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
#include "kitronix320x240x16_ssd2119_spi.h"
#include "Images/images.h"

/**
 * @def WIDTH
 * @brief Width of the display
 */
#define WIDTH	320

/**
 * @def HEIGHT
 * @brief Height of the display
 */
#define HEIGHT	240

/**
 * @struct rectangle_t
 * @brief Rectangle structure that contains top left and bottom right points
 */
typedef struct rectangle_t {
	uint16_t minX; /**< X coordinate of top left*/
	uint16_t minY; /**< Y coordinate of top left*/
	uint16_t maxX; /**< X coordinate of bottom right*/
	uint16_t maxY; /**< Y coordinate of bottom right*/
} rectangle_t;

/**
 * @struct line_t
 * @brief Line structure that contains top left and bottom right points
 */
typedef struct line_t {
	uint16_t x1; /**< X coordinate of top left*/
	uint16_t y1; /**< Y coordinate of top left*/
	uint16_t x2; /**< X coordinate of bottom right*/
	uint16_t y2; /**< Y coordinate of bottom right*/
} line_t;

/**
 * @brief Display specific struct, unused
 */
typedef struct {
	//Graphics_Context g_sContext;
} hal_graphics_t;

/**
 * @var Graphics_Context g_sContext
 * @brief Context for display, defined from MSP Graphics Library
 */
Graphics_Context g_sContext;

/**
 * @fn initDisplay(void)
 * @brief Initializes the graphics context and communication with display
 */
void initDisplay(void);

/**
 * @fn pixelToHex(uint8_t pixel)
 * @param pixel Full value of the pixel structure
 * @brief Convert pixel structure defined in graphics.h to hex color
 */
unsigned long pixelToHex(uint8_t pixel);

/**
 * @fn colorToHex(uint8_t color[3])
 * @param color Foreground or backgroud color
 * @brief Converts color from context defined in grpahics.h in foreground or background
 */
unsigned long colorToHex(uint8_t color[3]);

/**
 * @fn clearDisplay(void)
 * @brief Removes everything off the display, turns screen to black
 */
void clearDisplay(void);

/**
 * @fn drawPixel(uint32_t color, uint16_t x, uint16_t y)
 * @param color Hex color
 * @param x X coordinate of the pixel
 * @param y Y coordinate of the pixel
 * @brief Draws a single pixel at the specified coordinate
 */
void drawPixel(uint32_t color, uint16_t x, uint16_t y);

/**
 * @fn drawLine(uint32_t color, line_t* line)
 * @param color Hex color
 * @param line Pointer to line structure
 * @brief Draws the line defined in the given line structure
 */
void drawLine(uint32_t color, line_t* line);

/**
 * @fn drawRectangle(uint32_t color, rectangle_t* rect)
 * @param color Hex color
 * @param rect Pointer to rectangle structure
 * @brief Draws the rectangle defined in the given line structure
 * The rectangle as a thickness of one pixel
 */
void drawRectangle(uint32_t color, rectangle_t* rect);

/**
 * @fn fillRectangle(uint32_t color, rectangle_t* rect)
 * @param color Hex color
 * @param rect Pointer to rectangle structure
 * @brief Draws a filled in rectangle defined in the give rectangle structure
 */
void fillRectangle(uint32_t color, rectangle_t* rect);

/**
 * @fn drawThickRectangle(uint32_t color, uint8_t thickness, rectangle_t* rect);
 * @param color Hex color
 * @param thickness Number of pixels thick
 * @param rect Pointer to rectangle structure
 * @brief Draws the given rectangle with the specified thickness
 */
void drawThickRectangle(uint32_t color, uint8_t thickness, rectangle_t* rect);

/**
 * @fn setFont(const Graphics_Font* font)
 * @param font New font
 * @brief Changes the font defined in the display context to the given font
 */
void setFont(const Graphics_Font* font);

/**
 * @fn drawString(uint32_t color, char* string, int32_t length, uint16_t x, uint16_t y, uint8_t opaque)
 * @param textColor Hex color
 * @param bgColor Hex color
 * @param string Pointer to beginning of char array
 * @param lenght Length of the string to be drawn
 * @param x X coordinate of the top left corner of the text
 * @param y Y coordinate of the top left corner of the text
 * @param opaque Treated as boolean if the string is transparent
 * @brief Draws the given string on the display at the given location
 */
void drawString(uint32_t color, uint32_t bgColor, char* string, int32_t length, uint16_t x, uint16_t y, uint8_t opaque);


#endif /* HAL_GRAPHICS_H_ */
