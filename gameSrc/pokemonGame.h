/**
 * @file pokemonGame
 *
 * @author Breanna Higgins,
 *
 * @brief Top level module of the pokemon game. This modules communicates the low
 * level logic of the game management module with the actual business logic of the
 * pokemon game modules.
 */

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
 * @param TODO Docs
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
