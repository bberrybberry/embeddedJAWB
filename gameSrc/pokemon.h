/**
 * @file
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

/**
 * @def MAX_STRING_LENGTH
 * @brief Max number of characters a pokemon name can be
 */
#define MAX_STRING_LENGTH   16

/**
 * @def MAX_PLAYERS
 * @brief Max number of players that can play
 */
#define MAX_PLAYERS			4

/**
 * @def MAX_PKMN
 * @brief Max number of pokemon in the play
 */
#define MAX_PKMN			6

/**
 * @def PLAYER1_INIT_X
 * @brief Initial X coordinate of tile for player 1
 */
#define PLAYER1_INIT_X	5

/**
 * @def PLAYER1_INIT_Y
 * @brief Initial Y coordinate of tile for player 1
 */
#define PLAYER1_INIT_Y	9

/**
 * @def PLAYER2_INIT_X
 * @brief Initial X coordinate of tile for player 2
 */
#define PLAYER2_INIT_X	6

/**
 * @def PLAYER2_INIT_Y
 * @brief Initial Y coordinate of tile for player 2
 */
#define PLAYER2_INIT_Y	10

/**
 * @def PLAYER3_INIT_X
 * @brief Initial X coordinate of tile for player 3
 */
#define PLAYER3_INIT_X	6

/**
 * @def PLAYER3_INIT_Y
 * @brief Initial Y coordinate of tile for player 3
 */
#define PLAYER3_INIT_Y	9

/**
 * @def PLAYER4_INIT_X
 * @brief Initial X coordinate of tile for player 4
 */
#define PLAYER4_INIT_X	5

/**
 * @def PLAYER4_INIT_Y
 * @brief Initial Y coordinate of tile for player 4
 */
#define PLAYER4_INIT_Y	10

/**
 * @def CATCH_CHECK_1
 * @brief First modifier for capture check
 */
#define CATCH_CHECK_1 1048560

/**
 * @def CATCH_CHECK_2
 * @brief Second modifier for capture check
 */
#define CATCH_CHECK_2 16711680

//TODO DOXYGEN THIS SHIT
#define MAX_ITEMS   3
#define MAX_SHAKING_GRASS   15
/////////////////////////////////////////////////////////////////////////////////////
//
// Structs
//
/////////////////////////////////////////////////////////////////////////////////////

/**
 * @struct pokemon_t
 * @brief Structure that defines a pokemon
 */
typedef struct{
    char* name;            ///< Name of pokemon
    uint8_t spawnRate;      ///< Spawn rate for random generation, out of 100
    uint8_t catchRate;      ///< Catch rate of pokemon (percentage chance of successful ball catch)
    uint8_t points;         ///< Points to award player for successful catch
} pokemon_t;

/**
 * @struct pokePlayer_t
 * @brief Structure that defines a player
 */
typedef struct{
    playerSprite sprite;    ///< Sprite of player (relates to graphics)
    int8_t pbCount;        ///< Player inventory of pokeballs
    int8_t gbCount;        ///< Player inventory of great balls
    int8_t ubCount;        ///< Player inventory of ultra balls
    uint16_t score;         ///< Player score
    uint8_t tileX;          ///< X tile position of the player
    uint8_t tileY;          ///< Y tile position of the player
    bool status;            ///< Whether or not the player is currently playing true: is playing false: is not playing
    bool mvmt;              ///< Whether or not the player can move
    pokemon_t* encountered;    ///< Player's recently encountered pokemon (usually null);
} pokePlayer_t;
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
 * @var pkmnList[MAX_PKMN]
 * @brief Container for all types of pokemon contained in the game
 */
pokemon_t pkmnList[MAX_PKMN];
/**
 * @var pkmnWeights[MAX_PKMN]
 * @brief Parallel array to pkmnList for weighted generation of pokemon
 */
uint8_t pkmnWeights[MAX_PKMN];

uint8_t itemWeights[MAX_ITEMS];
/////////////////////////////////////////////////////////////////////////////////////
//
// Functions
//
/////////////////////////////////////////////////////////////////////////////////////


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
 * @fn initTextBox(void)
 * @brief Initializes the text boxes on the right of the screen
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
 * @brief set up the types of pokemon used throughout the game
 */
void initPokemon(void);

/**
 * @fn movePlayerUp(uint8_t playerIndex)
 * @param playerIndex index of the player (matches controller number and player
 * array indexing)
 *
 * @brief move the selected player up. Do nothing if the desired location is invalid
 */
void movePlayerUp(uint8_t playerIndex);


/**
 * @fn movePlayerDown(uint8_t playerIndex)
 * @param playerIndex index of the player (matches controller number and player
 * array indexing)
 *
 * @brief move the selected player down. Do nothing if the desired location is invalid
 */
void movePlayerDown(uint8_t playerIndex);


/**
 * @fn movePlayerLeft(uint8_t playerIndex)
 * @param playerIndex index of the player (matches controller number and player
 * array indexing)
 *
 * @brief move the selected player left. Do nothing if the desired location is invalid
 */
void movePlayerLeft(uint8_t playerIndex);


/**
 * @fn movePlayerRight(uint8_t playerIndex)
 * @param playerIndex index of the player (matches controller number and player
 * array indexing)
 *
 * @brief move the selected player right. Do nothing if the desired location is invalid
 */
void movePlayerRight(uint8_t playerIndex);

/**
 * @fn checkPlayerLocValid(pokePlayer_t* player, uint8_t locX, uint8_t locY)
 * @param player
 * @param locX
 * @param locY
 * @return bool True if location is valid, false otherwise
 *
 * @brief Check is the location the player is attempting to move into is a valid
 * location (ie, is not rocks, trees, or another player)
 */
bool checkPlayerLocValid(pokePlayer_t* player, uint8_t locX, uint8_t locY);

/**
 * @fn checkShakingGrass(uint8_t locX, uint8_t locY)
 * @param locX X coordinate of the tile
 * @param locY Y coordinate of the tile
 * @brief Checks if the grass at the specified tile is shaking
 */
bool checkShakingGrass(uint8_t locX, uint8_t locY);

/**
 * @fn setShakingGrass(uint8_t locX, uint8_t locY)
 * @param locX X coordinate of the tile
 * @param locY Y coordinate of the tile
 * @brief Sets the specified tile as shaking grass
 */
void setShakingGrass(uint8_t locX, uint8_t locY);

/**
 * @fn selectRun(uint8_t player)
 * @param player Index of the player
 * @brief Routine that runs when the player wants to run
 */
void selectRun(uint8_t player);

/**
 * @fn selectBall(uint8_t player)
 * @param player Index of the player
 * @brief Routine that runs when the player wants to select a pokeball
 */
void selectBall(uint8_t player);

/**
 * @fn lBallOpt(uint8_t player)
 * @param player Index of the player
 * @brief Routine that runs when the player presses left in ball selection menu
 */
void lBallOpt(uint8_t player);

/**
 * @fn rBallOpt(uint8_t player)
 * @param player Index of the player
 * @brief Routine that runs when the player presses right in ball selection menu
 */
void rBallOpt(uint8_t player);

/**
 * @fn throwBall(uint8_t player)
 * @param player Index of the player
 * @brief Routine that runs when the player throws a ball
 */
void throwBall(uint8_t player);

//TODO Fill this in right
/**
 * @fn captureEvent(uint8_t player, uint8_t multiplier)
 * @param player
 * @param multiplier
 * @param catchRate
 * @brief
 */
void captureEvent(uint8_t player, uint8_t multiplier, uint8_t catchRate);

/**
 * @fn playGame(void)
 * @brief Initiates the gameplay
 */
void playGame(void);

/**
 * @fn pauseGame(void)
 * @brief Pauses thte gameplay
 */
void pauseGame(void);

/**
 * @fn generateShakingGrass(void)
 * @brief Determines which tile the pokemon are spawned on
 */
void generateShakingGrass(void);

/**
 * @fn generatePokemon(void)
 * @brief Generates a random pokemon at a random tile
 */
pokemon_t* generatePokemon(void);

/**
 * @fn updatePlayerLoc(pokePlayer_t* player)
 * @param player Pointer to player struct
 * @brief Updates the current location of the player in the player struct
 */
void updatePlayerLoc(pokePlayer_t* player);

//TODO fill this in right
/**
 * @fn checkItem(pokePlayer_t* player)
 * @param player Pointer to player struct
 * @brief
 */
bool checkItem(pokePlayer_t* player);

//TODO fill this in right
/**
 * @fn checkGrass(pokePlayer_t* player)
 * @param player Pointer to player struct
 * @brief
 */
bool checkGrass(pokePlayer_t* player);

//TODO fill this in right
/**
 * @fn updateGrass(uint8_t location)
 * @param location
 * @brief
 */
void updateGrass(uint8_t location);

/**
 * @fn updateTime(uint8_t time)
 * @param time Current remaining time to display
 * @brief Updates the time on the screen
 */
void updateTime(uint8_t time);

/**
 * @fn updateScores(uint8_t playerID, uint8_t score)
 * @param playerID Index of the player
 * @param score New score of the player
 * @brief New score to put into the player struct
 */
void updateScores(uint8_t playerID, uint8_t score);

//TODO fill this in right
/**
 * @fn runEncounter(uint8_t playerInd)
 * @param playerInd Index of the player in the encounter
 * @brief Routine that runs when the player has an encounter
 */
void runEncounter(uint8_t playerInd);

//TODO fill this in right
/**
 * @fn generateItems(void)
 * @brief Generates the location of randomly placed pokeballs
 */
void generateItems(uint8_t locX, uint8_t locY);

/**
 * TODO: Walt: Docs
 */
uint8_t binarySearch(uint8_t arr[], uint8_t item, uint8_t low, uint8_t high);

void initItems();
#endif /* POKEMON_H_ */
