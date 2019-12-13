/**
 * @brief It defines the game management for saving and loading games
 *
 *
 *
 * @file game_managemenet.h
 * @author Félix Estaún
 * @version 2.0
 * @date 26-09-2019
 */


#ifndef GAME_MANAGEMENT_H
#define GAME_MANAGEMENT_H

#include "game.h"


/**
* @brief Creates a game from a file
*
* game_management_create_from_file creates a game based on the data of a file
*
* @date 19/09/2019
* @author: Martin Sanchez Signorini
*
* @param filename the name of the file with the data for creating the game
* @return game the game that will be created
*/
Game* game_management_create_from_file(char* filename);
Game* game_management_load_from_file(Game* game, char* filename);

/**
* @brief Saves a game to a file
*
* game_management_create_from_file saves a game state to a data file given
*
* @date 13/12/2019
* @author: Félix Estaún
*
* @param filename the name of the file where the data will be stored
* @param game the game that will be stored
* @return OK if everything went right or ERROR if an error occured
*/
STATUS game_management_save(Game* game, char* filename);


#endif
