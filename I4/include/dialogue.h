/**
 * @brief It defines the dice interface
 *
 * The dice is used for generating random ints
 *
 * @file die.h
 * @author Martin Sanchez Signorini
 * @version 3.0
 * @date 03-10-2019
 * @copyright GNU Public License
 */

#ifndef DIALOGUE_H
#define DIALOGUE_H

#include "types.h"
#include "command.h"

typedef struct _Dialogue Dialogue;

Dialogue* dialogue_create();
STATUS dialogue_destroy(Dialogue* dialogue);

STATUS dialogue_set_last_cmd(Dialogue* feedback, T_Command cmd);
STATUS dialogue_set_last_status(Dialogue* feedback, STATUS status);
STATUS dialogue_set_direction(Dialogue* feedback, DIRECTION dir);
STATUS dialogue_set_feedback(Dialogue* feedback, const char* string);

T_Command dialogue_get_last_cmd(Dialogue* feedback);
STATUS dialogue_get_last_status(Dialogue* feedback);
STATUS dialogue_get_direction(Dialogue* feedback);
const char* dialogue_get_feedback(Dialogue* feedback);

STATUS dialogue_produce(T_Command cmd, STATUS status, Dialogue* feedback);

#endif
