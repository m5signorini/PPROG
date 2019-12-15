/**
 * @brief It defines the dialogue interface
 *
 *
 *
 * @file dialogue.h
 * @author Gonzalo Martín Rollán
 * @version 3.0
 * @date 01-12-2019
 * @copyright GNU Public License
 */

#ifndef DIALOGUE_H
#define DIALOGUE_H

#include "types.h"
#include "command.h"

typedef struct _Dialogue Dialogue;

/**
* @brief Creates a dialogue
*
* dialogue_create creates a new dialogue structure
*
* @date 21/11/2019
* @author: Gonzalo Martín Rollán
*
*
* @return a pointer to the dialogue created
*/
Dialogue* dialogue_create();

/**
* @brief Destroys a dialogue
*
* dialogue_destroy destroys a dialogue structure freeing its resources
*
* @date 21/11/2019
* @author: Gonzalo Martín Rollán
*
* @param dialogue the dialogue to be destroyed
* @return the status of the function, for error management
*/
STATUS dialogue_destroy(Dialogue* dialogue);

/**
* @brief Sets a dialogue's last cmd
*
* dialogue_set_last_cmd sets the last cmd of a dialogue to a given one
*
* @date 21/11/2019
* @author: Gonzalo Martín Rollán
*
* @param feedback the dialogue that will have its last cmd changed
* @param cmd the cmd that it will set to the dialogue
* @return the status of the function, for error management
*/
STATUS dialogue_set_last_cmd(Dialogue* feedback, T_Command cmd);

/**
* @brief Sets a dialogue's last cmd status
*
* dialogue_set_last_status sets the status of the last cmd of a dialogue to a given one
*
* @date 21/11/2019
* @author: Gonzalo Martín Rollán
*
* @param feedback the dialogue that will have its last status changed
* @param status the status that it will set to the dialogue
* @return the status of the function, for error management
*/
STATUS dialogue_set_last_status(Dialogue* feedback, STATUS status);

/**
* @brief Sets a dialogue's direction (for the move cmd)
*
* dialogue_set_direction sets the direction of the dialogue to a given one
* useful for the move cmd
*
* @date 21/11/2019
* @author: Gonzalo Martín Rollán
*
* @param feedback the dialogue that will have its direction changed
* @param dir the direction that it will set to the dialogue
* @return the status of the function, for error management
*/
STATUS dialogue_set_direction(Dialogue* feedback, DIRECTION dir);

/**
* @brief Sets a dialogue's feedback
*
* dialogue_set_feedback sets the feedback of the dialogue to a given one
*
*
* @date 21/11/2019
* @author: Gonzalo Martín Rollán
*
* @param feedback the dialogue that will have its feedback changed
* @param feedback the feedback that it will set to the dialogue
* @return the status of the function, for error management
*/
STATUS dialogue_set_feedback(Dialogue* feedback, const char* string);

/**
* @brief Sets a dialogue's description
*
* dialogue_set_description sets the description of the dialogue to a given one
*
*
* @date 21/11/2019
* @author: Gonzalo Martín Rollán
*
* @param feedback the dialogue that will have its description changed
* @param description the description that it will set to the dialogue
* @return the status of the function, for error management
*/
STATUS dialogue_set_description(Dialogue* feedback, const char* string);

/**
* @brief Gets a dialogue's last command
*
* dialogue_get_last_cmd returns the last cmd of a given dialogue
*
* @date 21/11/2019
* @author: Gonzalo Martín Rollán
*
* @param feedback the dialogue from which it will return its last command
* @return the last command of the given space
*/
T_Command dialogue_get_last_cmd(Dialogue* feedback);

/**
* @brief Gets a dialogue's last status
*
* dialogue_get_last_status returns the last status of a given dialogue
*
* @date 21/11/2019
* @author: Gonzalo Martín Rollán
*
* @param feedback the dialogue from which it will return its last status
* @return the last status of the given dialogue
*/
STATUS dialogue_get_last_status(Dialogue* feedback);

/**
* @brief Gets a dialogue's direction
*
* dialogue_get_direction returns the direction of a given dialogue
*
* @date 21/11/2019
* @author: Gonzalo Martín Rollán
*
* @param feedback the dialogue from which it will return its direction
* @return the direction of the given dialogue
*/
DIRECTION dialogue_get_direction(Dialogue* feedback);

/**
* @brief Gets a dialogue's feedback
*
* dialogue_get_feedback returns the feedback of a given dialogue
*
* @date 21/11/2019
* @author: Gonzalo Martín Rollán
*
* @param feedback the dialogue from which it will return its feedback
* @return the feedback of the given dialogue
*/
const char* dialogue_get_feedback(Dialogue* feedback);

/**
* @brief Gets a dialogue's description
*
* dialogue_get_description returns the description of a given dialogue
*
* @date 21/11/2019
* @author: Gonzalo Martín Rollán
*
* @param feedback the dialogue from which it will return its description
* @return the description of the given dialogue
*/
char* dialogue_get_description(Dialogue* feedback);

/**
* @brief Stores the result of a command in a dialogue
*
* dialogue_produce produces a dialogue with the results of a command
*
* @date 21/11/2019
* @author: Gonzalo Martín Rollán
*
* @param cmd the cmd given to the dialogue_create
* @param status the status of the command
* @param feedback the dialogue to be produced
* @return the status of the function, for error management
*/
STATUS dialogue_produce(T_Command cmd, STATUS status, Dialogue* feedback);

#endif
