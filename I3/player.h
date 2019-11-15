/**
 * @brief It defines a player
 *
 * Added descriptions
 *
 * @file player.h
 * @author César Ramírez Martínez
 * @version 1.0
 * @date 20-09-2019
 * @copyright GNU Public License
 */

#ifndef player_H
#define player_H

#include "types.h"

typedef struct _Player Player;
/**
* @brief Creates a player
*
* player_create creates a new player with the given id
*
* @date 20/09/2019
* @author: César Ramírez Martínez
*
* @param id the id of the new player
* @return the player created
*/
Player* player_create(Id id);

/**
* @brief Destroys a player
*
* player_destroy destroys a player freeing the memory previosly assigned
*
* @date 20/09/2019
* @author: César Ramírez Martínez
*
* @param player the player to be destroyed
* @return the status of the function, for error management
*/
STATUS player_destroy(Player* player);

STATUS player_inventory_set_max(Player* player, int max);

int player_inventory_get_max(Player* player);

/**
* @brief Sets the location of the player
*
* player_set_location sets the location of a player previously created
*
* @date 20/09/2019
* @author: César Ramírez Martínez
*
* @param player the player that will have its id location setted
* @param idLocation the id of the location that will be setted to the player
* @return the status of the function, for error management
*/
STATUS player_set_location(Player* player, Id idLocation);

/**
* @brief Sets the object that the player has picked
*
* player_set_object sets the object that the player has picked
*
* @date 20/09/2019
* @author: César Ramírez Martínez
*
* @param player the player that will have its id object setted
* @param idObject the id of the object that will be setted to the player
* @return the status of the function, for error management
*/
STATUS player_add_object(Player* player, Id idObject);
//mal
/**
* @brief Sets the name of the player
*
* player_set_name sets the name of a player
*
* @date 20/09/2019
* @author: César Ramírez Martínez
*
* @param player the player that will have its set changed
* @param name the name that will be set to the player
* @return the status of the function, for error management
*/
STATUS player_set_name(Player* player, char* name);

/**
* @brief Gets the player id
*
* player_get_id returns the id of the given player
*
* @date 20/09/2019
* @author: César Ramírez Martínez
*
* @param player the player whose id will be returned
* @return the id of the given player
*/
Id player_get_id(Player* player);

/**
* @brief Gets the player's location id
*
* player_get_idLocation returns the id of the location where the player is placed
*
* @date 20/09/2019
* @author: César Ramírez Martínez
*
* @param player the player's whose id location will be returned
* @return the id´s ocation of the given player
*/
Id player_get_location(Player* player);

/**
* @brief Gets the id of the object that is picked by the player
*
* player_get_idObject returns the id of the object picked
*
* @date 20/09/2019
* @author: César Ramírez Martínez
*
* @param player the player whose id object it will returnef
* @return the idObject of the given player
*/
STATUS player_delete_object(Player* player, Id idObject);
//mal
/**
* @brief Gets the name of the player
*
* player_get_name returns the name of a given player
*
* @date 20/09/2019
* @author: César Ramírez Martínez
*
* @param player the player whose name will be returned
* @return the name of the given player
*/
const char* player_get_name(Player* player);

/**
* @brief Prints the player
*
* player_print prints the given player and its elements
*
* @date 20/09/2019
* @author: César Ramírez Martínez
*
* @param player the player whose elements will be printed
* @return the status of the function, for error management
*/
STATUS player_print(Player* player);
Id player_get_object_at(Player* player, int index);
int player_get_number_objects(Player* player);

#endif
