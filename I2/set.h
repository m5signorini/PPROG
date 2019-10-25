/**
 * @brief It defines sets to manage different groups of elements
 *
 * Added descriptions
 *
 * @file set.h
 * @author César Ramírez Martínez
 * @version 1.0
 * @date 10-10-1019
 * @copyright GNU Public License
 */

#ifndef SET_H
#define SET_H

#include "types.h"

typedef struct _Set Set;
/**
* @brief Creates a set
*
* set_create creates a new set
*
* @date 10/10/2019
* @author: César Ramírez Martínez
*
* @return the set already created
*/
Set* set_create();

/**
* @brief Destroys a set
*
* set_destroy destroys an set freeing its resources
*
* @date 10/10/2019
* @author: César Ramírez Martínez
*
* @param set the set to be destroyed
* @return the status of the function, for error management
*/
STATUS set_destroy(Set* set);

/**
* @brief adds an id in the set
*
* set_add_id adds the id of an element that will be introduced in the set
*
* @date 10/10/2019
* @author: César Ramírez Martínez
*
* @param set the set in which the id will be introduced
* @param id the id that will be added to the set
* @return the status of the function, for error management
*/
STATUS set_add_id(Set* set, Id id);

/**
* @brief Checks if an id is in the set
*
* set_has_id checks wheter an id is in the set and returns its position in the set
*
* @date 10/10/2019
* @author: César Ramírez Martínez
*
* @param set the set we check if it has th id
* @param id the id we want to check
* @return the position of the id in the set if it is in, or -1 if it is not
*/
 int set_has_id (Set* set, Id id);

/**
* @brief Deletes the id
*
* set_delete_id deletes the id of an element that will be eliminated from the set
*
* @date 10/10/2019
* @author: César Ramírez Martínez
*
* @param set the set from which the id will be deleted
* @return the status of the function, for error management
*/
STATUS set_delete_id(Set* set, Id id);

/**
* @brief Prints a set
*
* set_print prints a set, the ids of its elements and the total elements in the set
*
* @date 10/10/2019
* @author: César Ramírez Martínez
*
* @param set the set that will be printed
* @return the status of the function, for error management
*/
STATUS set_print(Set* set);

/**
* @brief Prints a set
*
* set_print prints a set, the ids of its elements and the total elements in the set
*
* @date 10/10/2019
* @author: César Ramírez Martínez
*
* @param set the set that will be printed
* @return the status of the function, for error management
*/
int set_get_n_elements(Set* set);
Id set_get_id_at(Set* set, int index);


#endif
