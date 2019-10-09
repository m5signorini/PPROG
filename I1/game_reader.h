/**
 * @brief It defines the game reader for loading
 *
 * Added descriptions
 *
 * @file game.h
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
* @author: Instructors
*
* @param game the game that will be created
* @param filename the name of the file with the data for creating the game
* @return the status of the function for error management
*/
Game* game_reader_create_from_file(char* filename);


#endif
