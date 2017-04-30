/**
 * @file pokemonGame
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

/**
 * @enum gameState
 * @brief Defines possible global states of the game
 */
typedef enum{
    PAUSE,
    PLAY,
    GAME_OVER
} gameState;

/////////////////////////////////////////////////////////////////////////////////////
//
// Defines
//
/////////////////////////////////////////////////////////////////////////////////////

#define GAME_TIME_LIMIT	120

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
 * @param game_network_payload_t * playload from networ
 *
 * @brief Listen to game controller inputs
 */
void inputCallback(game_network_payload_t * input);

/**
 * @fn pkmnGameOver(void)
 *
 * @brief Clear callbacks and set end of a game state
 */
void pkmnGameOver(void);

/**
 * @fn upPressed(uint8_t player)
 * @param uint8_t player index of players that is respond
 *
 * @brief Response to "up" pressed on a game controller
 */
void upPressed(uint8_t player);

/**
 * @fn downPressed(uint8_t player)
 * @param uint8_t player index of players that is respond
 *
 * @brief Response to "down" pressed on a game controller
 */
void downPressed(uint8_t player);

/**
 * @fn leftPressed(uint8_t player)
 * @param uint8_t player index of players that is respond
 *
 * @brief Response to "left" pressed on a game controller
 */
void leftPressed(uint8_t player);

/**
 * @fn rightPressed(uint8_t player)
 * @param uint8_t player index of players that is respond
 *
 * @brief Response to "right" pressed on a game controller
 */
void rightPressed(uint8_t player);

/**
 * @fn updateTime(void)
 * @brief Updates the time remaining on the clock
 */
void updateTimeRemaining(void);

#endif /* POKEMONGAME_H_ */
