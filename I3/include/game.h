/**
 * @brief It defines the game interface
 * for each command
 *
 * The game manages the spaces, players and objects
 *
 * @file game.h
 * @author Martin Sanchez Signorini
 * @version 3.0
 * @date 30-10-2019
 * @copyright GNU Public License
 */

#ifndef GAME_H
#define GAME_H

typedef struct _Game Game;

#include "command.h"
#include "space.h"
#include "player.h"
#include "object.h"
#include "die.h"
#include "link.h"

/**
* @brief Creates a new game
*
* game_create creates a game and returns it
*
* @date 25/10/2019
* @author: Martin Sanchez Signorini
*
* @return the game that will be created
*/
Game* game_create();

/**
* @brief Updates the game
*
* game_update updates the state of the game based on the commands
*
* @date 19/09/2019
* @author: Martin Sanchez Signorini
*
* @param game the game that will be updated
* @param cmd the command used to update the game
* @return the status of the function for command management
*/
STATUS game_update(Game* game, T_Command cmd);

/**
* @brief Ends a game
*
* game_destroy destroys the game freeing its resources
*
* @date 19/09/2019
* @author: Martin Sanchez Signorini
*
* @param game the game that will be destroyed
* @return the status of the function for error management
*/
STATUS game_destroy(Game* game);

/**
* @brief Checks if the game is over
*
* game_is_over checks if the game is over, returning TRUE if it is over
*
* @date 19/09/2019
* @author: Martin Sanchez Signorini
*
* @param game the game that will be checked
* @return TRUE if it is game over, FALSE otherwise
*/
BOOL   game_is_over(Game* game);

/**
* @brief Not defined yet
*/
void   game_print_screen(Game* game);

/**
* @brief Prints the data of the game
*
* game_print_data prints all the data that the game manages
*
* @date 19/09/2019
* @author: Martin Sanchez Signorini
*
* @param game the game whose data will be printed
*/
void   game_print_data(Game* game);

/**
* @brief Gets a specific space from a game
*
* game_get_space returns the space matching the passed id, in a game
*
* @date 19/09/2019
* @author: Martin Sanchez Signorini
*
* @param game the game where it will try to find the space
* @param id the id of the space to return
* @return the space matching the passed id
*/
Space* game_get_space(Game* game, Id id);

/**
* @brief Adds a space in a game
*
* game_add_space adds a specific space to the game
*
* @date 19/09/2019
* @author: Martin Sanchez Signorini
*
* @param game the game in which it will add the new space
* @param space the space that will be inserted in the game
* @return the status of the function for error management
*/
STATUS game_add_space(Game* game, Space* space);

/**
* @brief Gets the id of a space in a game
*
* game_get_space_id_at gets the id of the space in a given position
*
* @date 19/09/2019
* @author: Martin Sanchez Signorini
*
* @param game the game in which it will look for the space
* @param position index of the space that will be looked for
* @return the id of the space or NO_ID
*/
Id     game_get_space_id_at(Game* game, int position);

/**
* @brief Gets the player
*
* game_get_player returns the player inside the game
*
* @date 19/09/2019
* @author: Martin Sanchez Signorini
*
* @param game the game from which it will return its player
* @return the player in the game
*/
Player* game_get_player(Game* game);

/**
* @brief Sets the player
*
* game_set_player sets the player inside the game
*
* @date 19/09/2019
* @author: Martin Sanchez Signorini
*
* @param game the game in which it will set the player
* @param player the player to set in the game
* @return the status of the function for error management
*/
STATUS game_set_player(Game* game, Player* player);

/**
* @brief Adds an object in a game
*
* game_add_object adds a specific object to the game
*
* @date 25/10/2019
* @author: Martin Sanchez Signorini
*
* @param game the game in which it will add the new object
* @param obj the object that will be inserted in the game
* @return the status of the function for error management
*/
STATUS game_add_object(Game* game, Object* obj);

/**
* @brief Gets the object with matching id
*
* game_get_object returns the object inside the game
*
* @date 25/10/2019
* @author: Martin Sanchez Signorini
*
* @param game the game from which it will return its object
* @param id the id of the object to look for
* @return the object in the game
*/
Object* game_get_object(Game* game, Id id);

/**
* @brief Gets object in the specified index
*
* game_get_object_id_at return the id of the object indexed at index
* if NO_ID is returned there are no more objects in the game
*
* @date 25/10/2019
* @author: Martin Sanchez Signorini
*
* @param game the game from which it will return the object
* @param position index of the object to look for
* @return the id of the object if found or NO_ID
*/
Id game_get_object_id_at(Game* game, int position);

/**
* @brief Gets the object location
*
* game_get_object_location returns the location of the specified object inside the game
*
* @date 19/09/2019
* @author: Martin Sanchez Signorini
*
* @param game the game from which it will return its object's position
* @param id the id of the object to look for
* @return the id of the  location of the object in the game
*/
Id game_get_object_location(Game* game, Id id);

/**
* @brief Gets the last command
*
* game_get_last_command returns the last command executed
*
* @date 19/09/2019
* @author: Martin Sanchez Signorini
*
* @param game the game from which it will return its last command
* @return the last command executed in the game
*/
T_Command game_get_last_command(Game* game);

/**
* @brief Gets the last command status
*
* game_get_last_command_stat returns the status of the last command
*
* @date 29/10/2019
* @author: Martin Sanchez Signorini
*
* @param game the game from which it will return its last command status
* @return the lstatus of the last executed command
*/
STATUS game_get_last_command_stat(Game* game);

/**
* @brief Gets the die
*
* game_get_die returns the die inside the game
*
* @date 29/10/2019
* @author: Martin Sanchez Signorini
*
* @param game the game from which it will return its die
* @return the die in the game
*/
Die* game_get_die(Game* game);

/**
* @brief Sets the die
*
* game_set_die returns the die inside the game
*
* @date 29/10/2019
* @author: Martin Sanchez Signorini
*
* @param game the game which will have its die set
* @param die the die to be set in the game
* @return the status of the operation for error management
*/
STATUS game_set_die(Game* game, Die* die);

/**
* @brief Gets a specific link from a game
*
* game_get_link returns the link matching the passed id in a game
*
* @date 15/11/2019
* @author: Féix Estaún Bescós
*
* @param game the game where it will try to find the link
* @param id the id of the link to return
* @return the link matching the passed id
*/
Link* game_get_link(Game* game, Id id);

/**
* @brief Gets the id of a link in a game
*
* game_get_space_id_at gets the id of the link in a given position
*
* @date 15/11/2019
* @author: Féix Estaún Bescós
*
* @param game the game in which it will look for the link
* @param position index of the link that will be looked for
* @return the id of the link or NO_ID
*/
Id game_get_link_id_at(Game* game, int position);

/**
* @brief Adds a link to a game
*
* game_add_link adds a specific link to a game
*
* @date 15/11/2019
* @author: Féix Estaún Bescós
*
* @param game the game in which it will add the new link
* @param link the link that will be inserted in the game
* @return the status of the function for error management
*/
STATUS game_add_link(Game* game, Link* link);

/**
* @brief Gets the current description of a game
*
* game_get_description returns the description of the last thing inspected
*
* @date 21/11/2019
* @author: César Ramírez Martínez
*
* @param game the game from which it will return its description
* @return the description of the game
*/
char* game_get_description(Game*game);

#endif
