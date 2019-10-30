/**
 * @brief It defines the dice interface
 *
 * The dice is used for generating random ints
 *
 * @file game.h
 * @author Martin Sanchez Signorini
 * @version 3.0
 * @date 03-10-2019
 * @copyright GNU Public License
 */

#ifndef DIE_H
#define DIE_H

#include "types.h"

typedef struct _Die Die;

/**
* @brief Creates a new die
*
* die_create creates a die and returns it
*
* @date 25/10/2019
* @author: Martin Sanchez Signorini
*
* @return the die that will be created
*/
Die* die_create(Id id, int min, int max);

/**
* @brief Destroys a die
*
* die_destroy destroys the die
*
* @date 25/10/2019
* @author: Martin Sanchez Signorini
*
* @param die the die that will be destroyed
* @return the status of the function for error management
*/
STATUS die_destroy(Die* die);

/**
* @brief Rolls a die
*
* die_roll rolls the die
*
* @date 25/10/2019
* @author: Martin Sanchez Signorini
*
* @param die the die that will be rolled
* @return the number rolled
*/
int die_roll(Die* die);

/**
* @brief Gets last roll of a die
*
* die_get_last gets the last roll of the die
*
* @date 25/10/2019
* @author: Martin Sanchez Signorini
*
* @param die the die that will be checked
* @return the last number rolled
*/
int die_get_last(Die* die);

/**
* @brief Prints the data of the die
*
* die_print prints all the dice data
*
* @date 25/10/2019
* @author: Martin Sanchez Signorini
*
* @param die the die that will be printed
* @return status for error management
*/
STATUS die_print(Die* die);

#endif
