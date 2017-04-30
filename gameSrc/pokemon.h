/**
 * @file pokemon
 *
 * @author Breanna Higgins,
 *
 * @brief Business logic of pokemon game. This is a four player time-based game where
 * each player runs around to catch the most pokemon in a fixed amount of time.
 */

#ifndef POKEMON_H_
#define POKEMON_H_

#include <stdint.h>
#include <stdbool.h>
#include "drawPokemon.h"

/////////////////////////////////////////////////////////////////////////////////////
//
// Defines
//
/////////////////////////////////////////////////////////////////////////////////////

//TODO Docs
#define MAX_STRING_LENGTH   16
#define MAX_PLAYERS			4
#define MAX_PKMN			6

#define PLAYER1_INIT_X	5
#define PLAYER1_INIT_Y	9
#define PLAYER2_INIT_X	6
#define PLAYER2_INIT_Y	10
#define PLAYER3_INIT_X	6
#define PLAYER3_INIT_Y	9
#define PLAYER4_INIT_X	5
#define PLAYER4_INIT_Y	10

/////////////////////////////////////////////////////////////////////////////////////
//
// Structs
//
/////////////////////////////////////////////////////////////////////////////////////

/**
 * TODO Docs
 */
typedef struct{
    playerSprite sprite;    ///< Sprite of player (relates to graphics)
    uint8_t pbCount;        ///< Player inventory of pokeballs
    uint8_t gbCount;        ///< Player inventory of great balls
    uint8_t ubCount;        ///< Player inventory of ultra balls
    uint16_t score;         ///< Player score
    uint8_t tileX;          ///< X tile position of the player
    uint8_t tileY;          ///< Y tile position of the player
    bool status;            ///< Whether or not the player is currently playing true: is playing false: is not playing
    bool mvmt;              ///< Whether or not the player can move
} pokePlayer_t;
typedef struct{
    char name[MAX_STRING_LENGTH];            ///< Name of pokemon
    uint8_t spawnRate;      ///< Spawn rate for random generation, out of 100
    uint8_t catchRate;      ///< Catch rate of pokemon (percentage chance of successful ball catch)
    uint8_t points;         ///< Points to award player for successful catch
} pokemon_t;

//TODO: Define weights for random pokemon generation


/////////////////////////////////////////////////////////////////////////////////////
//
// Globals
//
/////////////////////////////////////////////////////////////////////////////////////

/**
 * @var players
 * @brief Container for all players currently in the game
 */
pokePlayer_t players[MAX_PLAYERS];
/**
 * @var pkmnList[]
 * @brief Container for all types of pokemon contained in the game
 */
pokemon_t pkmnList[MAX_PKMN];
/**
 * @var pkmnWeight[]
 * @brief Parallel array to pkmnList for weighted generation of pokemon
 */
uint8_t pkmnWeights[MAX_PKMN];


/////////////////////////////////////////////////////////////////////////////////////
//
// Functions
//
/////////////////////////////////////////////////////////////////////////////////////

//TODO: Docs

/**
 * @fn initGame(void)
 * @brief Set up of initial game state
 */
void initGame(void);

/**
 * @fn initMap(void)
 * @brief Calls to set up graphics for initial map layout
 */
void initMap(void);

/**
 * TODO !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 */
void initTextBox(void);

/**
 * @fn initPlayers(void)
 * @brief Sets up four players. All players are given inital stats and each player has
 * a different sprite and starting position. After players are defined, they are drawn
 * to the display.
 */
void initPlayers(void);

/**
 * @fn initPokemon(void);
 * @breif set up the types of pokemon used throughout the game
 */
void initPokemon(void);

/**
 * @fn movePlayerUp(uint8_t playerIndex)
 * @param uint8_t playerIndex index of the player (matches controller number and player
 * array indexing)
 *
 * @brief move the selected player up. Do nothing if the desired location is invalid
 */
void movePlayerUp(uint8_t playerIndex);


/**
 * @fn movePlayerDown(uint8_t playerIndex)
 * @param uint8_t playerIndex index of the player (matches controller number and player
 * array indexing)
 *
 * @brief move the selected player down. Do nothing if the desired location is invalid
 */
void movePlayerDown(uint8_t playerIndex);


/**
 * @fn movePlayerLeft(uint8_t playerIndex)
 * @param uint8_t playerIndex index of the player (matches controller number and player
 * array indexing)
 *
 * @brief move the selected player left. Do nothing if the desired location is invalid
 */
void movePlayerLeft(uint8_t playerIndex);


/**
 * @fn movePlayerRight(uint8_t playerIndex)
 * @param uint8_t playerIndex index of the player (matches controller number and player
 * array indexing)
 *
 * @brief move the selected player right. Do nothing if the desired location is invalid
 */
void movePlayerRight(uint8_t playerIndex);

/**
 * @fn checkPlayerLocValid(pokePlayer_t* player, uint8_t locX, uint8_t locY)
 * @param pokePlayer_t* player
 * @param uint8_t locX
 * @param uint8_t locY
 * @return bool True if location is valid, false otherwise
 *
 * @brief Check is the location the player is attempting to move into is a valid
 * location (ie, is not rocks, trees, or another player)
 */
bool checkPlayerLocValid(pokePlayer_t* player, uint8_t locX, uint8_t locY);

void playGame(void);
void pauseGame(void);
pokemon_t generatePokemon(void);
void updatePlayerLoc(pokePlayer_t player);
bool checkAllCollisions(uint8_t xLoc, uint8_t yLoc);
bool checkItem(pokePlayer_t player);
bool checkGrass(pokePlayer_t player);
void updateGrass(uint8_t location);
void updateTime(uint8_t time);
void updateScores(pokePlayer_t player, uint8_t score);
void runEncounter(void); //TODO: Walt, a bad merge somewhere messed up the encounter code, check your diffs on the commit at April 26, 2017 12:10:28 AM
void generateItems(void);

/**
 * TODO: Walt: Docs
 */
uint8_t binarySearch(uint8_t arr[], uint8_t item, uint8_t low, uint8_t high);


#endif /* POKEMON_H_ */
