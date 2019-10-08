/**
 * @brief It defines a object
 *
 * Added descriptions
 *
 * @file object.h
 * @author Profesores PPROG
 * @version 2.0
 * @date 13-01-2015
 * @copyright GNU Public License
 */

#ifndef OBJECT_H
#define OBJECT_H

#include "types.h"

typedef struct _Object Object;
/**
* @brief Creates an object
*
* object_create creates a new object with the given id
*
* @date 19/09/2019
* @author: Instructors
*
* @param id the id of the new object
* @return the object created
*/
Object* object_create(Id id);

/**
* @brief Destroys an object
*
* object_destroy destroys an object freeing its resources
*
* @date 19/09/2019
* @author: Instructors
*
* @param object the object to be destroyed
* @return the status of the function, for error management
*/
STATUS object_destroy(Object* object);

/**
* @brief Sets the name of the object
*
* object_set_name sets the name of an object
*
* @date 19/09/2019
* @author: Instructors
*
* @param object the object that will have its name changed
* @param name the name that it will set to the object
* @return the status of the functionl, for error management
*/
STATUS object_set_name(Object* object, char* name);

/**
* @brief Gets the object id
*
* object_get_id returns the id of the given object
*
* @date 19/09/2019
* @author: Instructors
*
* @param object the object from which it will return its id
* @return the id of the given object
*/
Id object_get_id(Object* object);

/**
* @brief Gets the name of the object
*
* object_get_name returns the name of a given object
*
* @date 19/09/2019
* @author: Instructors
*
* @param object the object whose name will be returned
* @return the name of the given object
*/
const char* object_get_name(Object* object);

/**
* @brief Prints the elements of the object
*
* object_print prints the given object and its elements
*
* @date 19/09/2019
* @author: Instructors
*
* @param object the object whose elements will be printed
* @return the status of the function, for error management
*/
STATUS object_print(Object* object);

#endif
