/**
 * @brief It defines a link
 *
 * Now bidirectional
 *
 * @file link.h
 * @author Félix Estaún
 * @version 2.0
 * @date 01-11-2019
 */

#ifndef LINK_H
#define LINK_H

#include "types.h"

typedef struct _Link Link;

/**
* @brief Creates a link
*
* link_create creates a new link with the given id
*
* @date 01/11/2019
* @author: Félix Estaún
*
* @param id the id of the new link
* @return the link created with its id
*/
Link* link_create(Id id);

/**
* @brief Destroys a link
*
* link_destroy destroys a link freeing its resources
*
* @date 01/11/2019
* @author: Félix Estaún
*
* @param link the link to be destroyed
* @return the status of the function, for error management
*/
STATUS link_destroy(Link* link);

/**
* @brief Gets the id of a link
*
* link_get_id returns the id of a given link
*
* @date 01/11/2019
* @author: Félix Estaún
*
* @param link the link whose id will be returned
* @return the id of the given link
*/
Id link_get_id(Link* link);

/**
* @brief Sets the name of a link
*
* link_set_name sets the name of a given link
*
* @date 01/11/2019
* @author: Félix Estaún
*
* @param link the link that will have its name set
* @param name the name that will be set to the link
* @return the status of the functionl, for error management
*/
STATUS link_set_name(Link* link, char* name);

/**
* @brief Gets the name of a link
*
* link_get_name returns the name of a given link
*
* @date 01/11/2019
* @author: Félix Estaún
*
* @param link the link whose name will be returned
* @return the name of the given link
*/
const char * link_get_name(Link* link);

/**
* @brief Sets first connection of a link
*
* link_set_space1 sets the first out of two connections of a given link
*
* @date 01/11/2019
* @author: Félix Estaún
*
* @param link the link that will have its connection set
* @param from the Id of the space that will set as the connection
* @return the status of the functionl, for error management
*/
STATUS link_set_space1(Link* link, Id from);

/**
* @brief Gets the id of the first space connected by a link
*
* link_get_space1 gets the id of the first space out of two connected by a given link
*
* @date 01/11/2019
* @author: Félix Estaún
*
* @param link the link whose first connection will be returned
* @return the id of the first space connected by the link
*/
Id link_get_space1(Link* link);

/**
* @brief Sets second connection of a link
*
* link_set_space1 sets the second out of two connections of a given link
*
* @date 01/11/2019
* @author: Félix Estaún
*
* @param link the link that will have its connection set
* @param from the Id of the space that will set as the connection
* @return the status of the functionl, for error management
*/
STATUS link_set_space2(Link* link, Id to);

/**
* @brief Gets the id of the second space connected by a link
*
* link_get_space1 gets the id of the second space out of two connected by a given link
*
* @date 01/11/2019
* @author: Félix Estaún
*
* @param link the link whose second connection will be returned
* @return the id of the second space connected by the link
*/
Id link_get_space2(Link* link);

/**
* @brief Sets the "open" parameter of a link
*
* link_set_open sets the "open" parameter of a given link
*
* @date 01/11/2019
* @author: Félix Estaún
*
* @param link the link whose "open" parameter" will be set
* @param open the Boolean value that will be set to the "open" parameter
* @return the status of the function, for error management
*/
STATUS link_set_open(Link* link, BOOL open);

/**
* @brief Gets the "open" parameter of a link
*
* link_get_open gets the Boolean value of the "open" parameter of a given link
*
* @date 01/11/2019
* @author: Félix Estaún
*
* @param link the link whose "open" parameter will be returned
* @return the Boolean value of the "open" parameter of the link
*/
BOOL link_get_open(Link* link);

/**
* @brief Gets the id of the space connected by a link in where the player is NOT currently in
*
* link_get_to gets the id of the space out of two connected by a given link in
* which the player is NOT currently in
*
* @date 01/11/2019
* @author: Félix Estaún
*
* @param link the link whose connection will be returned
* @param current_id the id of the current space of the player
* @return the id of the space connected by the link, other than the one the player is in
*/
Id link_get_to(Link* link, Id current_id);

/**
* @brief Prints a link
*
* link_print prints a given link and all its parameters
*
* @date 01/11/2019
* @author: Félix Estaún
*
* @param link the link which will be printed
* @return the status of the function, for error management
*/
STATUS link_print(Link *link);

#endif
