/**
* @brief It implements all the functions used to manage a die
*
* @file object.c
* @author Martin Sanchez
* @version 1.0
* @date 20-09-2019
* @copyright GNU Public License
*/

#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "die.h"

struct _Die {
  Id id;  /*!< Id of the die.*/
  int min;  /*!< Minimun value of the die.*/
  int max;  /*!< Maximum value of the die.*/
  int last;  /*!< Last result of the die.*/
};


Die* die_create(Id id, int min, int max) {
  if(id == NO_ID || min > max) return NULL;
  Die* die = NULL;
  srand(time(NULL));

  die = (Die*)malloc(sizeof(Die));
  if(die == NULL) {
    return NULL;
  }

  die->id = id;
  die->max = max;
  die->min = min;
  die->last = min;

  return die;
}

STATUS die_destroy(Die* die) {
  if(die == NULL) return ERROR;
  free(die);
  return OK;
}

int die_roll(Die* die) {
  if(die == NULL) return 0;

  int a = die->min; /* Valor minimo inclusive */
  int b = die->max; /* Valor maximo inclusive */
  int range = (b-a)+1; // 11 (0-10)

  /* rand()/(RAND_MAX + 1.) nos da un numero en [0,1) */
  /* lo multiplicamos por el rango y sumamos el minimo*/
  die->last = (rand()/(RAND_MAX + 1.))*range + a;

  return die->last;
}

int die_get_last(Die* die) {
  if(die == NULL) return 0;
  return die->last;
}

STATUS die_print(Die* die) {
  if (die == NULL) {
    return ERROR;
  }

  if(fprintf(stdout, "--> Die (Id: %ld; Last: %d; Min: %d; Max: %d)\n", die->id, die->last, die->min, die->max)<1){
    return ERROR;
  }
  return OK;
}
