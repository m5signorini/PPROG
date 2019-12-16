/**
* @brief It defines the game reader for loading
*
* Added descriptions
*
* @file game_reader.h
* @author Martin Sanchez Signorini
* @version 2.0
* @date 26-09-2019
*/


#ifndef GAME_READER_H
#define GAME_READER_H

#include "game.h"


/**
* @brief Creates a game from a file
*
* game_reader_create_from_file creates a game based on the data of a file
*
* @date 19/09/2019
* @author: Martin Sanchez Signorini
*
* @param filename the name of the file with the data for creating the game
* @return game the game that will be created
*/
Game* game_reader_create_from_file(char* filename);


#endif
