/**
 * @file
 * @author Breanna Higgins, Aaron Guidarelli, Walter Marroquin, Josh Velez
 *
 * @brief Utilities for drawing visuals of pokemon game
 */

#ifndef DRAWPOKEMON_H_
#define DRAWPOKEMON_H_

// System Includes
#include <msp430f5529.h>
#include <stdint.h>

//GrLib Includes
#include "grlib.h"
#include "driverlib.h"

// Embedded Library Includes
#include "system.h"
#include "game_controller_host.h"
#include "game_controller.h"
#include "game.h"
#include "uart.h"
#include "hal_general.h"
#include "hal_uart.h"
#include "task.h"
#include "timing.h"
#include "terminal.h"
#include "random_int.h"

//Custom Includes
#include "graphics.h"
#include "pixel_defs.h"
//#include "pokemonImages.h" moved to .c

/////////////////////////////////////////////////////////////////////////////////////
//
// Defines
//
/////////////////////////////////////////////////////////////////////////////////////


/**
 * @def WIDTH
 * @brief Width of the display in pixels
 */
#define WIDTH               320

/**
 * @def HEIGHT
 * @brief Height of the display in pixels
 */
#define HEIGHT              240

/**
 * @def TEXT_TILES
 * @brief Number of tiles reserved for the menu
 */
#define TEXT_TILES          8

/**
 * @def TILE_X
 * @brief Number of pixels of tile in x direction
 */
#define TILE_X              16

/**
 * @def TILE_Y
 * @brief Numeber of pixels of tile in y direction
 */
#define TILE_Y              12

/**
 * @def GRID_X
 * @brief Number of tiles of the grid in x direction
 */
#define GRID_X              ((WIDTH / TILE_X) - TEXT_TILES)

/**
 * @def GRID_Y
 * @brief Number of tiles of the grid in y direction
 */
#define GRID_Y              (HEIGHT / TILE_Y)

/**
 * @def MAP_WIDTH
 * @brief Number of pixels on the grid in x direction
 */
#define MAP_WIDTH   		GRID_X * TILE_X

/**
 * @def MAP_HEIGHT
 * @brief Number of pixels on the grid in y direction
 */
#define MAP_HEIGHT  		GRID_Y * TILE_Y

/**
 * @def MENU_HEIGHT
 * @brief Number of tiles high the menu is
 */
#define MENU_HEIGHT			4

/**
 * @def VERT_PADDING
 * @brief Pixels given for vertical padding of text
 */
#define VERT_PADDING		1

/**
 * @def HORI_PADDING
 * @brief Pixels given for horizontal padding of text
 */
#define HORI_PADDING		3

/////////////////////////////////////////////////////////////////////////////////////
//
// Structs
//
/////////////////////////////////////////////////////////////////////////////////////

/**
 * @struct MapStruct
 * @brief Structure containing the map
 * @details Used as structure in order to initialize after declaration
 */
typedef struct {
    const g_pixel_t* grid[GRID_X * GRID_Y]; /**< Grid containing pointers to all tiles */
} MapStruct;

/**
 * @var map
 * @brief Global map structure
 */
MapStruct map;


/////////////////////////////////////////////////////////////////////////////////////
//
// Enums
//
/////////////////////////////////////////////////////////////////////////////////////

/**
 * @enum playerSprite
 * @brief Enumeration of the four player sprites available
 */
typedef enum {AARON,	/**< Aaron sprite*/
			  BREANNA,  /**< Breanna sprite*/
			  JOSH, 	/**< Josh sprite*/
			  WALT		/**< Walt sprite*/
} playerSprite;

/**
 * @enum walkState
 * @brief Enumeration of the three walk states.
 */
typedef enum {LEFT, 	/**< Walking left*/
			  RIGHT, 	/**< Walking right*/
			  STAND		/**< Standing*/
} walkState;

/**
 * @enum grassState
 * @brief Enumeration of the two grass states.
 */
typedef enum {GRASS,	/**< Static grass*/
			  SHAKE		/**< Shaking grass*/
} grassState;

/**
 * @enum menuState
 * @brief Enumeration of the menu states
 */
typedef enum {RUN_BALL, 	/**< Selecting to run or throw a pokeball*/
			  BALL_SELECT, 	/**< Selecting which ball to throw*/
			  NONE			/**< No menu visible*/
} menuState;


/**
 * @enum pokeMsgType
 * @brief Pokemon message type to describe how to show pokemon found in the menu
 */
typedef enum {FOUND_MSG, 	/**< Show that the player just found this pokemon*/
			  RAN_MSG, 		/**< Show that the pokemon has ran away*/
			  CAUGHT_MSG, 	/**< Show that the pokemon was successfully caught*/
			  POKEBALL_MSG, /**< Show that a pokeball was found*/
			  GREATBALL_MSG,/**< Show that a greatball was found*/
			  ULTRABALL_MSG,/**< Show that a ultraball was found*/
			  FULL_MSG,     /**< Show that players bag is full*/
			  NONE_MSG		/**< No pokemon information to show*/
} pokeMsgType;

/////////////////////////////////////////////////////////////////////////////////////
//
// Functions
//
/////////////////////////////////////////////////////////////////////////////////////

/**
 * @fn initDrawGraphics(void)
 * @brief Initializes the graphics
 */
void initDrawGraphics(void);

/**
 * @fn drawPlayer(playerSprite ps, walkState ws, uint8_t locX, uint8_t locY)
 * @param ps Player sprite of the player being drawn
 * @param ws Walk state of the player being drawn
 * @param locX X coordinate of the player being drawn in tiles
 * @param locY Y coordinate of the player being drawn in tiles
 * @brief Draws a player with the given specs
 */
void drawPlayer(playerSprite ps, walkState ws, uint8_t locX, uint8_t locY);

/**
 * @fn drawGrass(grassState gs, uint8_t locX, uint8_t locY)
 * @param gs State of the grass
 * @param locX X coordinate of the grass in tiles
 * @param locY Y coordinate of the grass in tiles
 * @brief Draws grass with the current state at the specified location
 */
void drawGrass(grassState gs, uint8_t locX, uint8_t locY);

/**
 * @fn drawItem(uint8_t locX, uint8_t locY)
 * @param locX X coordinate of the grass in tiles
 * @param locY Y coordinate of the grass in tiles
 * @brief Draws item at the specified location
 */
void drawItem(uint8_t locX, uint8_t locY);

/**
 * @fn drawMap()
 * @brief Draws the inital map
 */
void drawMap();

//TODO Fill this in right
/**
 * @fn drawStatic(const g_pixel_t* tileImg, g_point_t* pos)
 * @param tileImg Pointer to tile being drawn
 * @param pos Pointer to position being drawn
 * @brief Draws a tile at the specified location
 */
void drawStatic(const g_pixel_t* tileImg, g_point_t* pos);

/**
 * @fn drawInitMenu(void)
 * @brief Draws the initial menu
 */
void drawInitMenu(void);

/**
 * @fn printScore(uint8_t playerID, uint16_t score)
 * @param playerID Index of the player
 * @param score Score of the player
 * @brief Prints the score for the given player
 */
void printScore(uint8_t playerID, uint16_t score);

/**
 * @fn printPokemon(uint8_t playerID, pokeMsgType msgType, char* pokemon)
 * @param playerID Prints the pokemon for the given player
 * @param msgType Defines the type of pokemon message to be printed
 * @param pokemon String of the pokemon
 * @brief Prints the name of the pokemon for the given player
 */
void printPokemon(uint8_t playerID, pokeMsgType msgType, char* pokemon);

/**
 * @fn printMenu(uint8_t playerID, menuState ms, int8_t pb, int8_t gb, int8_t ub, char* text)
 * @param playerID Index of the player
 * @param ms Current menu state
 * @param pb Number of pokeballs the player has
 * @param gb Number of greatballs the player has
 * @param ub Number of ultraballs the player has
 * @param text Text to draw on the menu
 * @brief Prints the given menu with the given values of pokeballs
 *
 * @details Insert negative numbers for the type of pokeballs that are not drawn
 */
void printMenu(uint8_t playerID, menuState ms, int8_t pb, int8_t gb, int8_t ub, char* text);

/**
 * @fn printStats(uint8_t playerInd, uint8_t playerStat)
 * @param playerInd Index of player for specified stat
 * @param playerStat Status of player to specify (recommended stat: final score)
 * @brief Prints the specified stats at the end of the game
 */
void printEndStats(uint8_t playerInd, uint8_t playerStat);

/**
 * @fn printTime(uint8_t time)
 * @param Given time
 * @brief Print current time
 */
void printTime(uint8_t time);

/**
 * @fn isTreeTile(uint8_t locX, uint8_t locY)
 * @param locX X coordinate of the tile
 * @param locY Y coordinate of the tile
 * @brief Returns if the tile is a tree
 */
bool isTreeTile(uint8_t locX, uint8_t locY);

/**
 * @fn isRockTile(uint8_t locX, uint8_t locY)
 * @param locX X coordinate of the tile
 * @param locY Y coordinate of the tile
 * @brief Returns if the tile is a rock
 */
bool isRockTile(uint8_t locX, uint8_t locY);

/**
 * @fn isShakingGrass(uint8_t locX, uint8_t locY)
 * @param locX X coordinate of the tile
 * @param locY Y coordinate of the tile
 * @brief Returns if the tile is shaking grass
 */
bool isShakingGrass(uint8_t locX, uint8_t locY);

/**
 * @fn isGrass(uint8_t locX, uint8_t locY)
 * @param locX X coordinate of the tile
 * @param locY Y coordinate of the tile
 * @brief Returns if the tile is normal grass
 */
bool isGrass(uint8_t locX, uint8_t locY);

/**
 * @fn isGround(uint8_t locX, uint8_t locY)
 * @param locX X coordinate of the tile
 * @param locY Y coordinate of the tile
 * @brief Returns if the tile is ground
 */
bool isGround(uint8_t locX, uint8_t locY);

/**
 * @fn isItem(uint8_t locX, uint8_t locY)
 * @param locX X coordinate of the tile
 * @param locY Y coordinate of the tile
 * @brief Returns if the tile has an item
 */
bool isItem(uint8_t locX, uint8_t locY);

#endif /* DRAWPOKEMON_H_ */
