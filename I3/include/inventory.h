/**
 * @brief It defines a inventory
 *
 * Added descriptions
 *
 * @file inventory.h
 * @author César Ramírez Martínez
 * @version 1.0
 * @date 20-09-2019
 * @copyright GNU Public License
 */

#ifndef inventory_H
#define inventory_H

#include "types.h"

typedef struct _Inventory Inventory;
/**
* @brief Creates a inventory
*
* inventory_create creates a new inventory
*
* @date 20/09/2019
* @author: César Ramírez Martínez
*
* @return the inventory created
*/
Inventory* inventory_create();

/**
* @brief Destroys a inventory
*
* inventory_destroy destroys a inventory freeing the memory previosly assigned
*
* @date 20/09/2019
* @author: César Ramírez Martínez
*
* @param inventory the inventory to be destroyed
* @return the status of the function, for error management
*/
STATUS inventory_destroy(Inventory* inventory);

/**
* @brief Checks if an object is in the inventory
*
* inventory_has_id checks wheter an object is in the inventory
*
* @date 10/10/2019
* @author: César Ramírez Martínez
*
* @param inventory the inventory we check if it has the object
* @param id the id of the object we want to check
* @return TRUE if it has the object FALSE otherwise
*/
BOOL inventory_has_object(Inventory* inventory, Id id);

/**
* @brief adds an id in the inventory
*
* inventory_add_id adds the id of an element that will be introduced in the inventory
*
* @date 10/10/2019
* @author: César Ramírez Martínez
*
* @param inventory the inventory in which the id will be introduced
* @param id the id that will be added to the inventory
* @return the status of the function, for error management
*/
STATUS inventory_add_id(Inventory* inventory, Id id);

/**
* @brief gets the max number of elements of a inventory
*
* inventory_get_max returns the total number of elements that can be stored in the inventory
*
* @date 10/10/2019
* @author: César Ramírez Martínez
*
* @param inventory the inventory we will return its max number of elements
* @return the total number of elements
*/
int inventory_get_max(Inventory* inventory);

/**
* @brief inventorys the max number of elements of a inventory
*
* inventory_set_max inventorys the total number of elements that can be stored in the inventory
*
* @date 10/10/2019
* @author: César Ramírez Martínez
*
* @param inventory the inventory we will return its max number of elements
* @param max the max number of elements the inventory will be able to put up with
* @return the status of the function, for error management
*/
STATUS inventory_set_max(Inventory* inventory, int max);

/**
* @brief Deletes the id
*
* inventory_delete_id deletes the id of an element that will be eliminated from the inventory
*
* @date 10/10/2019
* @author: César Ramírez Martínez
*
* @param inventory the inventory from which the id will be deleted
* @return the status of the function, for error management
*/
STATUS inventory_delete_id(Inventory* inventory, Id id);

/**
* @brief Gets the inventory's location id
*
* inventory_get_id_at returns the id of the object located in a given index of the inventory
*
* @date 20/09/2019
* @author: César Ramírez Martínez
*
* @param inventory the inventory's whose id in a given index will be returned
* @param index the position of the id that will be returned
* @return Id of the object in the given position
*/
Id inventory_get_id_at(Inventory* inventory, int index);

/**
* @brief Prints an inventory
*
*inventory_print prints an inventory, the ids of its elements and the total elements in the inventory
*
* @date 10/10/2019
* @author: César Ramírez Martínez
*
* @param inventory the inventory that will be printed
* @return the status of the function, for error management
*/

STATUS inventory_print(Inventory* inventory);

/**
* @brief gets the number of elements of an inventory
*
*inventory_get_number_objects returns the total number of elements stored in the inventory
*
* @date 10/10/2019
* @author: César Ramírez Martínez
*
* @param inventory the inventory we want to count its elements
* @return the total number of elements
*/
int inventory_get_number_objects(Inventory* inventory);

#endif
