/**
 * @file pokemon
 * @author Breanna Higgins
 * @brief TODO
 * TODO: Everything
 */

#include "pokemon.h"

void initGame(){

    //draw initial game

    //set up map
    initMap();

    //init players
    initPlayers();

    //set up menus and text
    initTextBox();

    //pause game
    pauseGame();

    //set up time and first item/pokemon generations

    //wait for someone to unpause game before starting
}

void initMap(){
    //TODO
}

void initPlayers(){
    //TODO
}

void initTextBox(){
    //TODO
}

void playGame(){
    //TODO
}

void pauseGame(){
    //TODO
}

pokemon_t generatePokemon(){
    //TODO
}

void updatePlayerLoc(pokePlayer_t player){
    //TODO
}

void checkAllCollisions(){
    //TODO
}

bool checkItem(pokePlayer_t player){
    //TODO
}

bool checkPlayerLocValid(pokePlayer_t player){
    //TODO
}

bool checkGrass(pokePlayer_t player){
    //TODO
}

void updateGrass(uint8_t location){
    //TODO
}

void updateTime(uint8_t time){
    //TODO
}

void updateScores(pokePlayer_t player, uint8_t score){
    //TODO
}

void runEncounter(){
    //TODO
}

void generateItems(){
    //TODO
}

