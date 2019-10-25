/**
 * @brief It defines the dice interface
 *
 * The dice is used for generating random ints
 *
 * @file game.h
 * @author Martin Sanchez Signorini
 * @version 2.0
 * @date 03-10-2019
 * @copyright GNU Public License
 */

#ifndef DIE_H
#define DIE_H

#include "types.h"

typedef struct _Die Die;

Die* die_create(Id id, int min, int max);

STATUS die_destroy(Die* die);

int die_roll(Die* die);

int die_get_last(Die* die);

STATUS die_print(Die* die);

#endif
