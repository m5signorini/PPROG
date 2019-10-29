/**
 * @brief It defines a space
 *
 * Added descriptions
 *
 * @file space.h
 * @author Profesores PPROG
 * @version 2.0
 * @date 13-01-2015
 * @copyright GNU Public License
 */

#ifndef SPACE_H
#define SPACE_H

#include "types.h"

typedef struct _Space Space;

#define MAX_SPACES 100
#define FIRST_SPACE 1

/**
* @brief Creates a space
*
* space_create creates a new space with the given id
*
* @date 19/09/2019
* @author: Profesores PPROG
*
* @param id the id of the new space
* @return the space created
*/
Space* space_create(Id id);

/**
* @brief Destroys a space
*
* space_destroy destroys a space freeing its resources
*
* @date 19/09/2019
* @author: Profesores PPROG
*
* @param space the space to be destroyed
* @return the status of the function, for error management
*/
STATUS space_destroy(Space* space);

/**
* @brief Gets a space id
*
* space_get_id returns the id of the given space
*
* @date 19/09/2019
* @author: Profesores PPROG
*
* @param space the space from which it will return its id
* @return the id of the given space
*/
Id space_get_id(Space* space);

/**
* @brief Sets a name
*
* space_set_name sets the name of a space to the given one
*
* @date 19/09/2019
* @author: Profesores PPROG
*
* @param space the space that will have itss name changed
* @param name the name that it will set to the space
* @return the status of the functionl, for error management
*/
STATUS space_set_name(Space* space, char* name);

/**
* @brief Gets the name of a space
*
* space_get_name returns the name of a given space
*
* @date 19/09/2019
* @author: Profesores PPROG
*
* @param space the space from which it will return its name
* @return the name of the given space
*/
const char* space_get_name(Space* space);

/**
* @brief Sets the id of the north space
*
* space_set_north sets the id of the north space of the give
* space, to the given id
*
* @date 19/09/2019
* @author: Profesores PPROG
*
* @param space the space whose north will have its id changed
* @param id the new id for the north of the space
* @return the status of the function, for error management
*/
STATUS space_set_north(Space* space, Id id);

/**
* @brief Gets the id of the north space
*
* space_get_north gets the id of the north space of the given
* space, to the given id
*
* @date 19/09/2019
* @author: Profesores PPROG
*
* @param space the space whose north it will get its id
* @return the id of the north of the given space
*/
Id space_get_north(Space* space);

/**
* @brief Sets the id of the south space
*
* space_set_south sets the id of the south space of the given
* space, to the given id
*
* @date 19/09/2019
* @author: Profesores PPROG
*
* @param space the space whose south will have its id changed
* @param id the new id for the south of the space
* @return the status of the function, for error management
*/
STATUS space_set_south(Space* space, Id id);

/**
* @brief Gets the id of the south space
*
* space_get_south gets the id of the south space of the given
* space, to the given id
*
* @date 19/09/2019
* @author: Profesores PPROG
*
* @param space the space whose south it will get its id
* @return the id of the south of the given space
*/
Id space_get_south(Space* space);

/**
* @brief Sets the id of the east space
*
* space_set_east sets the id of the east space of the given
* space, to the given id
*
* @date 19/09/2019
* @author: Profesores PPROG
*
* @param space the space whose east will have its id changed
* @param id the new id for the neastof the space
* @return the status of the function, for error management
*/
STATUS space_set_east(Space* space, Id id);

/**
* @brief Gets the id of the east space
*
* space_get_east gets the id of the east space of the given
* space, to the given id
*
* @date 19/09/2019
* @author: Profesores PPROG
*
* @param space the space whose east it will get its id
* @return the id of the east of the given space
*/
Id space_get_east(Space* space);

/**
* @brief Sets the id of the west space
*
* space_set_west sets the id of the west space of the given
* space, to the given id
*
* @date 19/09/2019
* @author: Profesores PPROG
*
* @param space the space whose west will have its id changed
* @param id the new id for the west of the space
* @return the status of the function, for error management
*/
STATUS space_set_west(Space* space, Id id);

/**
* @brief Gets the id of the west space
*
* space_get_west gets the id of the west space of the given
* space, to the given id
*
* @date 19/09/2019
* @author: Profesores PPROG
*
* @param space the space whose west it will get its id
* @return the id of the west of the given space
*/
Id space_get_west(Space* space);

/**
* @brief Sets the object in a space
*
* space_set_object sets the object inside the space, to the given one
*
* @date 19/09/2019
* @author: Profesores PPROG
*
* @param space the space whose object will be set
* @param value the object that will be set to the space
* @return the status of the function, for error management
*/
STATUS space_set_object(Space* space, Id value);

/**
* @brief Gets the object in a space
*
* space_get_object gets the object inside the given space
*
* @date 19/09/2019
* @author: Profesores PPROG
*
* @param space the space whose object will be returned
* @return the object inside the space
*/
Id space_get_object(Space* space);

/**
* @brief Prints the space
*
* space_print prints the given space
*
* @date 19/09/2019
* @author: Profesores PPROG
*
* @param space the space which will be printed
* @return the status of the function, for error management
*/
STATUS space_print(Space* space);

#endif
