/**
 * @file
 * 
 * @author Breanna Higgins,
 *
 * @brief Top level module of the pokemon game. This modules communicates the low
 * level logic of the game management module with the actual business logic of the
 * pokemon game modules.
 */

#ifndef POKEMONGAME_H_
#define POKEMONGAME_H_


#include "system.h"
#include "random_int.h"
#include "stddef.h"
#include "strings.h"
#include "game.h"
#include "timing.h"
#include "task.h"
#include "terminal.h"
#include "game_controller.h"
#include "pokemon.h"

/////////////////////////////////////////////////////////////////////////////////////
//
// Enums
//
/////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////
//
// Defines
//
/////////////////////////////////////////////////////////////////////////////////////

/**
 * @def GAME_TIME_LIMIT
 * @brief The number of seconds in a game
 */
#define GAME_TIME_LIMIT				120

/**
 * @def SECOND
 * @brief One second in milliseconds
 */
#define SECOND						1000

/**
 * @def SHAKING_GRASS_PERIOD
 * @brief Period for shaking grass or pokemon generation
 */
#define SHAKING_GRASS_PERIOD		8 * SECOND

/**
 * @def ITEM_GENERATION_PERIOD
 * @brief Period for generating items
 */
#define ITEM_GENERATION_PERIOD		6 * SECOND

/**
 * @def INITIAL_COORDINATE_VALUE
 * @brief Value set as initial x and y coordinates
 */
#define INITIAL_COORDINATE_VALUE	255

/**
 * @def PACKET_SIZE
 * @brief Packet size that is sent to
 */
#define PACKET_SIZE					11

/**
 * @def PACKET_POKEMON_BIT
 * @brief Bit that the pokemon indicator is in
 */
#define PACKET_POKEMON_BIT			0x40

/**
 * @def PACKET_ITEM_BIT
 * @brief Bit that the item indicator is in
 */
#define PACKET_ITEM_BIT				0x80

/**
 * @def PACKET_ITEM_ITERATOR
 * @brief Bits that the item index is stored in, will be shifted for each player
 */
#define PACKET_ITEM_ITERATOR		0x03

/**
 * @def PACKET_INDICATOR_BYTE_0
 * @brief Index of the first indicator byte
 */
#define PACKET_INDICATOR_BYTE_0		0

/**
 * @def PACKET_INDICATOR_BYTE_1
 * @brief Index of the second indicator byte
 */
#define PACKET_INDICATOR_BYTE_1		1

/**
 * @def PACKET_POKEMON_X
 * @brief Index of the x coordinate of the pokemon in the packet
 */
#define PACKET_POKEMON_X			2

/**
 * @def PACKET_POKEMON_Y
 * @brief Index of the y coordinate of the pokemon in the packet
 */
#define PACKET_POKEMON_Y			3

/**
 * @def PACKET_ITEM_X
 * @brief Index of the x coordinate of the item in the packet
 */
#define PACKET_ITEM_X				4

/**
 * @def PACKET_ITEM_Y
 * @brief Index of the y coordinate of the item in the packet
 */
#define PACKET_ITEM_Y				5

/**
 * @def PACKET_POKEMON_NAME_START
 * @brief Beginning index of the pokemon name bytes in the packet
 */
#define PACKET_POKEMON_NAME_START	6

/**
 * @def PACKET_ITEM_ID
 * @brief Packet that has the item index stored
 */
#define PACKET_ITEM_ID				10

/////////////////////////////////////////////////////////////////////////////////////
//
// Global Variables
//
/////////////////////////////////////////////////////////////////////////////////////

/**
 * @var g_startTime
 * @brief Time when the game is first started
 */
uint32_t g_startTime;

/**
 * @var g_pauseTime
 * @brief Time when the game is paused
 */
uint32_t g_pauseTime;

/////////////////////////////////////////////////////////////////////////////////////
//
// Functions
//
/////////////////////////////////////////////////////////////////////////////////////

/**
 * @fn pkmnGameInit(void)
 * @param ptr Pointer to the nrf24 configuration structure
 * @brief Register game within game management module
 */
void pkmnGameInit(nrf24_t* ptr);

/**
 * @fn pkmnPlay(void)
 *
 * @brief Register button call backs and initialize first game state
 */
void pkmnPlay(void);

/**
 * @fn pkmnHelp(void)
 *
 * @brief Configure help text
 */
void pkmnHelp(void);

/**
 * @fn packetizer(uint8_t* buffer)
 * @param buffer Beginning of buffer in the packet being sent or received
 * @brief Returns the length of the user data being used
 * @details
 *
 * The packet is filled according to the following format:
 *
 *		1.7	1.6	1.5	1.4	1.3	1.2	1.1	1.0		1		1		1		1		1		4		1		bytes
 *		Itm	Pkm	X	X	X	X	X	Pse		In		Xp		Yp		Xi		Yi		PkNm	Itms
 * 
 * Pse	-	Pause Indicator bit<br>
 * X 	-	Don't Care<br>
 * Pkm	-	Pokemon, e.g. shaking grass, has been added to map<br>
 * Itm	-	Item has been added to map<br>
 * In	-	Indicator byte for pokemon and items for each player<br>
 * Xp	-	X coordinate of the pokemon<br>
 * Yp 	-	Y coordinate of the pokemon<br>
 * Xi	-	X coordinate of the item<br>
 * Yi	-	Y coordinate of the item<br>
 * PkNm	-
 * Itms	-
 */
uint8_t packetizer(uint8_t* buffer);

/**
 * @fn shakingGrassUpdate(void)
 * @brief Adds a new shaking grass tile and alerts the packetizer to the new pokemon
 */
void shakingGrassUpdate(void);

/**
 * @fn itemUpdate(void)
 * @brief Adds a new item tile and alerts the packetizer to the new item
 */
void itemUpdate(void);

/**
 * @fn inputCallback(game_network_payload_t * input)
 * @param input Payload from the network
 *
 * @brief Listen to game controller inputs
 */
void inputCallback(game_network_payload_t * input);

/**
 * @fn callbackInit(void)
 * @brief Initializes all the callbacks for the controller connected
 * directly to the host
 */
void callbackInit(void);

/**
 * @fn pkmnGameOver(void)
 *
 * @brief Clear callbacks and set end of a game state
 */
void pkmnGameOver(void);

/**
 * @fn upPressed(uint8_t player)
 * @param player index of players that is respond
 *
 * @brief Response to "up" pressed on a game controller
 */
void upPressed(uint8_t player);

/**
 * @fn downPressed(uint8_t player)
 * @param player index of players that is respond
 *
 * @brief Response to "down" pressed on a game controller
 */
void downPressed(uint8_t player);

/**
 * @fn leftPressed(uint8_t player)
 * @param player index of players that is respond
 *
 * @brief Response to "left" pressed on a game controller
 */
void leftPressed(uint8_t player);

/**
 * @fn rightPressed(uint8_t player)
 * @param player index of players that is respond
 *
 * @brief Response to "right" pressed on a game controller
 */
void rightPressed(uint8_t player);

/**
 * @fn aPressed(uint8_t player)
 * @param player index of players that is respond
 *
 * @brief Response to "a" pressed on a game controller
 */
void aPressed(uint8_t player);

/**
 * @fn bPressed(uint8_t player)
 * @param player index of players that is respond
 *
 * @brief Response to "b" pressed on a game controller
 */
void bPressed(uint8_t player);

/**
 * @fn startPressed(uint8_t player)
 * @param player Index of the player
 *
 * @brief Response to when the start button is pressed
 */
void startPressed(uint8_t player);

/**
 * @fn selectPressed(uint8_t player)
 * @param player Index of the player that pressed
 *
 * @brief Response to when the select button is pressed
 */
void selectPressed(uint8_t player);

/**
 * @fn p1Handler(controller_buttons_t btn, void* handle)
 * @param btn Controller button input
 * @param handle Void pointer to any data
 * @brief Callback function to interface with GameControllerHost
 */
void p1Handler(controller_buttons_t btn, void* handle);

/**
 * @fn p2Handler(controller_buttons_t btn, void* handle)
 * @param btn Controller button input
 * @param handle Void pointer to any data
 * @brief Callback function to interface with GameControllerHost
 */
void p2Handler(controller_buttons_t btn, void* handle);

/**
 * @fn p3Handler(controller_buttons_t btn, void* handle)
 * @param btn Controller button input
 * @param handle Void pointer to any data
 * @brief Callback function to interface with GameControllerHost
 */
void p3Handler(controller_buttons_t btn, void* handle);

/**
 * @fn p4Handler(controller_buttons_t btn, void* handle)
 * @param btn Controller button input
 * @param handle Void pointer to any data
 * @brief Callback function to interface with GameControllerHost
 */
void p4Handler(controller_buttons_t btn, void* handle);

/**
 * @fn updateTimeRemaining(void)
 * @brief Updates the time remaining on the clock
 */
void updateTimeRemaining(void);


#endif /* POKEMONGAME_H_ */
