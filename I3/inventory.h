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
* inventory_create creates a new inventory with the given id
*
* @date 20/09/2019
* @author: César Ramírez Martínez
*
* @param id the id of the new inventory
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
* @brief Sets the location of the inventory
*
* inventory_set_location sets the location of a inventory previously created
*
* @date 20/09/2019
* @author: César Ramírez Martínez
*
* @param inventory the inventory that will have its id location setted
* @param idLocation the id of the location that will be setted to the inventory
* @return the status of the function, for error management
*/
BOOL inventory_has_object(Inventory* inventory, Id id);

/**
* @brief Sets the object that the inventory has picked
*
* inventory_set_object sets the object that the inventory has picked
*
* @date 20/09/2019
* @author: César Ramírez Martínez
*
* @param inventory the inventory that will have its id object setted
* @param idObject the id of the object that will be setted to the inventory
* @return the status of the function, for error management
*/
STATUS inventory_add_id(Inventory* inventory, Id id);

/**
* @brief Sets the name of the inventory
*
* inventory_set_name sets the name of a inventory
*
* @date 20/09/2019
* @author: César Ramírez Martínez
*
* @param inventory the inventory that will have its set changed
* @param name the name that will be set to the inventory
* @return the status of the function, for error management
*/
STATUS inventory_set_max(Inventory* inventory, int max);

/**
* @brief Gets the inventory id
*
* inventory_get_id returns the id of the given inventory
*
* @date 20/09/2019
* @author: César Ramírez Martínez
*
* @param inventory the inventory whose id will be returned
* @return the id of the given inventory
*/
STATUS inventory_delete_id(Inventory* inventory, Id id);

/**
* @brief Gets the inventory's location id
*
* inventory_get_idLocation returns the id of the location where the inventory is placed
*
* @date 20/09/2019
* @author: César Ramírez Martínez
*
* @param inventory the inventory's whose id location will be returned
* @return the id´s ocation of the given inventory
*/
Id inventory_get_id_at(Inventory* inventory, int index);

/**
* @brief Gets the id of the object that is picked by the inventory
*
* inventory_get_idObject returns the id of the object picked
*
* @date 20/09/2019
* @author: César Ramírez Martínez
*
* @param inventory the inventory whose id object it will returnef
* @return the idObject of the given inventory
*/
STATUS inventory_print(Inventory* inventory);

#endif
