/**
 * @file
 * @mainpage Pokemon
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

/**
 * @enum gameState
 * @brief Defines possible global states of the game
 */
typedef enum{
    PAUSE,		/**< Game is paused*/
    PLAY,		/**< Game is being played*/
    GAME_OVER	/**< Game is over*/
} gameState;

/////////////////////////////////////////////////////////////////////////////////////
//
// Defines
//
/////////////////////////////////////////////////////////////////////////////////////

/**
 * @def GAME_TIME_LIMIT
 * @brief The number of seconds in a game
 */
#define GAME_TIME_LIMIT	120

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
 *
 * @brief Register game within game mangement module
 */
void pkmnGameInit(void);

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

void upHandler(controller_buttons_t btn, void* handle);
void downHandler(controller_buttons_t btn, void* handle);
void leftHandler(controller_buttons_t btn, void* handle);
void rightHandler(controller_buttons_t btn, void* handle);
void aHandler(controller_buttons_t btn, void* handle);
void bHandler(controller_buttons_t btn, void* handle);
void startHandler(controller_buttons_t btn, void* handle);
void selectHandler(controller_buttons_t btn, void* handle);


/**
 * @fn updateTimeRemaining(void)
 * @brief Updates the time remaining on the clock
 */
void updateTimeRemaining(void);


#endif /* POKEMONGAME_H_ */
