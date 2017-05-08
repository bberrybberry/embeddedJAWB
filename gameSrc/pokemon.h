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

/**
 * @def TOTAL_ITEMS
 * @brief Number of unique items each player will hold
 */
#define TOTAL_ITEMS   3

/**
 * @def BAG_MAX 
 * @brief Total number of items one player can hold
 */
#define BAG_MAX 99

/**
 * @def MAX_SHAKING_GRASS
 * @brief Total number of items one player can hold
 */
#define MAX_SHAKING_GRASS   15

/**
 * @def MAX_ITEMS_ONSCREEN
 * @brief Maximum number of generated items to have onscreen at once
 */
#define MAX_ITEMS_ONSCREEN			8

/**
 * @def MAX_PKMN_ONSCREEN
 * @brief Maximum number of generated pokemon to have onscreen at once
 */
#define MAX_PKMN_ONSCREEN			12

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
    uint8_t index;			///< Index of the pokemon in the array of pokemon
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

/**
 * @struct game
 * @brief Game structre that contains global information
 */
typedef struct {
    gameState currGameState;    ///< Current state of the game
    bool client;				///< True if this instance is a client, false otherwise
    uint8_t id;                 ///< ID of game
    uint8_t currNumItems;		///< Current number of items generated
    uint8_t currNumPkmn;		///< Current number of pokemon generated
    pokemon_t* pkmn[MAX_PLAYERS];// = {void*, void*, void*, void*};
    uint8_t items[MAX_PLAYERS];// = {255, 255, 255, 255};
} game_t;

/**
 * @struct encounter_t
 * @brief Structure to define the pokemon held inside an encounter spot
 */
typedef struct{
	pokemon_t* pokemon; ///< Pointer to pokemon from list held in this encounter
	uint8_t locX; ///< X location of encounter grass spot
	uint8_t locY; ///< Y location of encounter grass spot
} encounter_t;


/**
 * @struct item_t
 * @brief Structure to define the item held inside an item spot
 */
typedef struct{
	uint8_t itemID; ///< Item id corresponding 0-1-2 to poke-great-ultra
	uint8_t locX; ///< X location of item grass spot
	uint8_t locY; ///< Y location of item grass spot
} item_t;

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
/**
 * @var itemWeights[MAX_ITEMS];
 * @brief used for weighted generation of Items
 */
uint8_t itemWeights[TOTAL_ITEMS];

/**
 * @var game
 * @brief Defintion of game structure
 */
game_t game;

/**
 * @var allPkmn[]
 * @brief collection of all pokemon currently in the game
 */
encounter_t allPkmn[MAX_PKMN_ONSCREEN];

/**
 * @var allPkmnValidEntries[]
 * @brief Parallel array to allPkmn to show next available index to generate a pokemon into the location
 *
 * (I know we should have just made a list data structure but there's only so much you can do at one time)
 */
bool allPkmnValidEntries[MAX_PKMN_ONSCREEN];

/**
 * @var allItems[]
 * @brief collection of all items currently in the game
 */
item_t allItems[MAX_ITEMS_ONSCREEN];

/**
 * @var allItemsValidEntries[]
 * @brief Parallel array to allPkmn to show next available index to generate an item into the location
 */
bool allItemsValidEntries[MAX_ITEMS_ONSCREEN];

/////////////////////////////////////////////////////////////////////////////////////
//
// Functions
//
/////////////////////////////////////////////////////////////////////////////////////


/**
 * @fn initGame()
 * @brief Set up of initial game state
 */
void initGame();

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
 * @fn leftBallOption(uint8_t player)
 * @param player Index of the player
 * @brief Routine that runs when the player presses left in ball selection menu
 */
void leftBallOption(uint8_t player);

/**
 * @fn rightBallOption(uint8_t player)
 * @param player Index of the player
 * @brief Routine that runs when the player presses right in ball selection menu
 */
void rightBallOption(uint8_t player);

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
 * @fn generateShakingGrass(uint8_t* x, uint8_t* y)
 * @param x Pointer to x coordinate
 * @param y Pointer to y coordinate
 * @brief Determines which tile the pokemon are spawned on
 */
void generateShakingGrass(uint8_t* x, uint8_t* y);

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
 * @fn generateItems(uint8_t* x, uint8_t* y)
 * @brief Generates the location of randomly placed pokeballs
 */
void generateItems(uint8_t* x, uint8_t* y);

//TODO Walt comment ur code!!!!!!!!
/**
 *  @fn binarySearch(uint8_t arr[], uint8_t item, uint8_t low, uint8_t high)
 *  @param item 
 *  @param low 
 *  @param high 
 *  @brief
 */
uint8_t binarySearch(uint8_t arr[], uint8_t item, uint8_t low, uint8_t high);

/**
 *  @fn initItems(void)
 *  @brief Initializes the pokeball, greatball, and ultraball items
 */
void initItems(void);

/**
 *  @fn itemSpawn(uint8_t playerInd)
 *  @param playerInd Index of the player in the encounter
 *  @brief
 */
void itemSpawn(uint8_t playerInd);

/**
 *  @fn checkItemLoc(uint8_t locX, uint8_t locY)
 *  @param locX X coordinate of the tile
 *  @param locY Y coordinate of the tile
 *  @brief Returns if the tile has an item on it
 */
bool checkItemLoc(uint8_t locX, uint8_t locY);

/**
 * @fn printGameOverStats(void)
 * @brief Print final stats when game is over
 */

void printGameOverStats(void);

#endif /* POKEMON_H_ */
