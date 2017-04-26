/**
 * @file pokemon
 *
 * @author Breanna Higgins,
 *
 * @brief Business logic of pokemon game. This is a four player time-based game where
 * each player runs around to catch the most pokemon in a fixed amount of time.
 */

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


/////////////////////////////////////////////////////////////////////////////////////
//
// Enums
//
/////////////////////////////////////////////////////////////////////////////////////



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
// Functions
//
/////////////////////////////////////////////////////////////////////////////////////

//TODO: Docs

void initGame(void);
void initMap(void);
void initTextBox(void);
void initPlayers(void);
void playGame(void);
void pauseGame(void);
pokemon_t generatePokemon(void);
void updatePlayerLoc(pokePlayer_t player);
void checkAllCollisions(void);
bool checkItem(pokePlayer_t player);
bool checkPlayerLocValid(pokePlayer_t player);
bool checkGrass(pokePlayer_t player);
void updateGrass(uint8_t location);
void updateTime(uint8_t time);
void updateScores(pokePlayer_t player, uint8_t score);
void runEncounter(void);
void generateItems(void);

