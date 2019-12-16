/**
* @brief It defines an object
*
* Added descriptions
*
* @file object.h
* @author César Ramírez Martínez
* @version 1.0
* @date 20-09-2019
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
* @date 20/09/2019
* @author: César Ramírez Martínez
*
* @param id the id of the new object
* @return the object created with its id
*/
Object* object_create(Id id);

/**
* @brief Destroys an object
*
* object_destroy destroys an object freeing its resources
*
* @date 20/09/2019
* @author: César Ramírez Martínez
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
* @date 20/09/2019
* @author: César Ramírez Martínez
*
* @param object the object that will have its name set
* @param name the name that will set to the object
* @return the status of the function, for error management
*/
STATUS object_set_name(Object* object, char* name);

/**
* @brief Sets the description of the object
*
* object_set_description sets the description of an object
*
* @date 20/09/2019
* @author: César Ramírez Martínez
*
* @param object the object that will have its description set
* @param description the description that will set to the object
* @return the status of the function, for error management
*/
STATUS object_set_description(Object* object, char* description);

/**
* @brief Sets the moved description of the object
*
* object_set_moved_description sets the moved description of an object
*
* @date 20/09/2019
* @author: César Ramírez Martínez
*
* @param object the object that will have its moved_description set
* @param description the moved description that will set to the object
* @return the status of the function, for error management
*/
STATUS object_set_moved_description(Object* object, char* description);

/**
* @brief Sets the id of the link that an object can open
*
* object_set_open sets the id of the that can be opened by the object
*
* @date 20/09/2019
* @author: César Ramírez Martínez
*
* @param object the object that will be able to open the link
* @param open the id of the link that will be openable by the object
* @return the status of the function, for error management
*/
STATUS object_set_open(Object* object, Id open);

/**
* @brief Sets if an object is movable
*
* object_set_movable sets the mobility of an object
*
* @date 20/09/2019
* @author: César Ramírez Martínez
*
* @param object the object that will be able movable or not
* @param movable TRUE if it is movable FALSE otherwise
* @return the status of the function, for error management
*/
STATUS object_set_movable(Object* object, BOOL movable);

/**
* @brief Sets if an object has moved
*
* object_set_moved sets if an object has been moved
*
* @date 20/09/2019
* @author: César Ramírez Martínez
*
* @param object the object that will have been moved or not
* @param movable TRUE if it is movable FALSE otherwise
* @return the status of the function, for error management
*/
STATUS object_set_moved(Object* object, BOOL moved);

/**
* @brief Sets if an object is hidden
*
* object_set_hidden sets if an object is hidden
*
* @date 20/09/2019
* @author: César Ramírez Martínez
*
* @param object the object that will be hidden or not
* @param movable TRUE if it is hidden FALSE otherwise
* @return the status of the function, for error management
*/
STATUS object_set_hidden(Object* object, BOOL hidden);

/**
* @brief Sets if an object can illuminate
*
* object_set_illuminate sets if an object can illuminate
*
* @date 20/09/2019
* @author: César Ramírez Martínez
*
* @param object the object that will be able to illuminate or not
* @param movable TRUE if it is able illuminate FALSE otherwise
* @return the status of the function, for error management
*/
STATUS object_set_illuminate(Object* object, BOOL illuminate);

/**
* @brief Sets if an object is illuminating
*
* object_set_turnedon sets if an object is illuminating
*
* @date 20/09/2019
* @author: César Ramírez Martínez
*
* @param object the object that is illuminating or not
* @param movable TRUE if it is illuminating FALSE otherwise
* @return the status of the function, for error management
*/
STATUS object_set_turnedon(Object* object, BOOL turnedon);

/**
* @brief Gets the object id
*
* object_get_id returns the id of the given object
*
* @date 20/09/2019
* @author: César Ramírez Martínez
*
* @param object the object whose id will be returned
* @return the id of the given object
*/
Id object_get_id(Object* object);

/**
* @brief Gets the name of the object
*
* object_get_name returns the name of a given object
*
* @date 20/09/2019
* @author: César Ramírez Martínez
*
* @param object the object whose name will be returned
* @return the name of the given object
*/
const char* object_get_name(Object* object);

/**
* @brief Gets the description of the object (the moved or the default one)
*
* object_get_description returns the description of a given object
*
* @date 20/09/2019
* @author: César Ramírez Martínez
*
* @param object the object whose description will be returned
* @return the description of the given object (default or moved)
*/
const char * object_get_description(Object* object);

/**
* @brief Gets the moved description of the object
*
* object_get_moved_description returns the moved description of a given object
*
* @date 20/09/2019
* @author: César Ramírez Martínez
*
* @param object the object whose moved description will be returned
* @return the moved decription of the given object
*/
const char * object_get_moved_description(Object* object);

/**
* @brief Gets the default description of the object
*
* object_get_default_description returns the default description of a given object
*
* @date 20/09/2019
* @author: César Ramírez Martínez
*
* @param object the object whose default description will be returned
* @return the default decription of the given object
*/
const char * object_get_default_description(Object* object);

/**
* @brief Gets the id of the link that the object can open
*
* object_get_open returns the id of the openable link by the object
*
* @date 20/09/2019
* @author: César Ramírez Martínez
*
* @param object the object whose openable link will be returned
* @return the default id of the link
*/
Id object_get_open(Object* object);

/**
* @brief Gets if an object is movable or not
*
* object_get_movable returns if an object is movable or not
*
* @date 20/09/2019
* @author: César Ramírez Martínez
*
* @param object that will be checked it is movable or not
* @return TRUE if it is movable FALSE otherwise
*/
BOOL object_get_movable(Object* object);

/**
* @brief Gets if an object has been moved or not
*
* object_get_moved returns if an object has been moved or not
*
* @date 20/09/2019
* @author: César Ramírez Martínez
*
* @param object that will be checked it has been moved
* @return TRUE if it is moved FALSE otherwise
*/
BOOL object_get_moved(Object* object);

/**
* @brief Gets if an object is hidden or not
*
* object_get_hidden returns if an object is hidden or not
*
* @date 20/09/2019
* @author: César Ramírez Martínez
*
* @param object that will be checked it is hidden
* @return TRUE if it is hidden FALSE otherwise
*/
BOOL object_get_hidden(Object* object);

/**
* @brief Gets if an object can be illuminated or not
*
* object_get_illuminated returns if an object is can be illuminated or not
*
* @date 20/09/2019
* @author: César Ramírez Martínez
*
* @param object that will be checked it can be illuminated
* @return TRUE if it can be illuminated FALSE otherwise
*/
BOOL object_get_illuminate(Object* object);

/**
* @brief Gets if an object is illuminating or not
*
* object_get_turnedon returns if an object is illuminating at the moment or not
*
* @date 20/09/2019
* @author: César Ramírez Martínez
*
* @param object that will be checked it is illuminating
* @return TRUE if it is illuminating FALSE otherwise
*/
BOOL object_get_turnedon(Object* object);

/**
* @brief Prints the elements of the object
*
* object_print prints the given object and its elements
*
* @date 20/09/2019
* @author: César Ramírez Martínez
*
* @param object the object whose elements will be printed
* @return the status of the function, for error management
*/
STATUS object_print(Object* object);

#endif
