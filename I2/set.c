/**
 * @brief It implements all the functions used to manage sets
 *
 * @file object.c
 * @author César Ramírez Martínes
 * @version 1.0
 * @date 10-10-2019
 * @copyright GNU Public License
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "types.h"
#include "set.h"

#define MAX_N_ELEMENTS 51

struct _Set {
  Id id_array[MAX_N_ELEMENTS];
  int n_elements;
};

Set* set_create() {
  Set *newset = NULL;
  int i;

  newset = (Set *) malloc(sizeof (Set));

  if (newset == NULL) {
    return NULL;
  }

  for (i = 0; i < MAX_N_ELEMENTS; i++){
    newset->id_array[i] = NO_ID;
  }

  newset->n_elements = 0;

  return newset;
}


STATUS set_destroy(Set* set) {
  if (set == NULL) {
    return ERROR;
  }

  free(set);
  set = NULL;

  return OK;
}


STATUS set_add_id(Set* set, Id id) {
  int i;
  if (set == NULL || id < 0) {
    return ERROR;
  }

  i = set_has_id(set, id);
  if(i == -2){
    return ERROR;

  }
  
  if(i > -1){
    return OK;
  }

  set->id_array[set->n_elements] = id;
  set->n_elements++;

  return OK;
}


int set_has_id (Set* set, Id id){
  int i;
  if (set == NULL || id == NO_ID){
    return -2;
  }

  for (i = 0; i < set->n_elements; i++){
    if (set->id_array[i] == id){
      return i;
    }
  }
    return -1;
}


STATUS set_delete_id(Set* set, Id id) {
  int i;

  if (set == NULL || id < 0) {
    return ERROR;
  }

  i = set_has_id(set, id);
  if(i == -2){
    return OK;
  }

  set->id_array[i] = set->id_array[set->n_elements-1];
  set->id_array[set->n_elements-1] = NO_ID;
  set->n_elements--;

  return OK;
}

Id set_get_id_at(Set* set, int index){
  if (set == NULL || index < 0 || index > set->n_elements){
    return NO_ID;
  }

  return set->id_array[index];
}

int set_get_n_elements(Set* set){
  if (set == NULL){
    return ERROR;
  }

  return set->n_elements;
}


STATUS set_print(Set* set) {
  int i;

  if (set == NULL) {
    return ERROR;
  }

  if (!fprintf(stdout, "--> Elements in the set:\n")){
    return ERROR;
  }
  for (i = 0; i < set->n_elements; i++){
    if (!fprintf(stdout, "Element: %d, Id: %ld\n", i+1, set->id_array[i])){
      return ERROR;
    }
  }
  if (!fprintf(stdout, "Number of elements in the set: %d\n", set->n_elements)){
  return ERROR;
  }

return OK;
}
