/**
 * @brief It implements all the functions used to manage the spaces of the game
 *
 * @file space.c
 * @author Profesores PPROG
 * @version 1.0
 * @date 27-09-2019
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "space.h"
#include "set.h"

struct _Space {
  Id id;
  char name[WORD_SIZE + 1];
  Id north;
  Id south;
  Id east;
  Id west;
  Set* object;
  char image_up[IMG_SIZE];
  char image_mid[IMG_SIZE];
  char image_down[IMG_SIZE];
};

Space* space_create(Id id) {

  Space *new_space = NULL;
  Set* objects = NULL;

  if (id == NO_ID)
    return NULL;

  new_space = (Space *) malloc(sizeof (Space));

  if (new_space == NULL) {
    return NULL;
  }

  objects = set_create();

  if (objects == NULL) {
    free(new_space);
    return NULL;
  }

  new_space->id = id;

  new_space->north = NO_ID;
  new_space->south = NO_ID;
  new_space->east = NO_ID;
  new_space->west = NO_ID;

  new_space->object = objects;

  memset(new_space->name, 0, WORD_SIZE + 1);
  memset(new_space->image_up, 0, IMG_SIZE);
  memset(new_space->image_mid, 0, IMG_SIZE);
  memset(new_space->image_down, 0, IMG_SIZE);

  return new_space;
}

STATUS space_destroy(Space* space) {
  if (!space) {
    return ERROR;
  }

  if(set_destroy(space->object) == ERROR){
    return ERROR;
  }

  free(space);
  space = NULL;

  return OK;
}

STATUS space_set_image_up(Space* space, char* image_up){
  if (image_up == NULL || space == NULL){
    return ERROR;
  }
  if (!strncpy(space->image_up, image_up, IMG_SIZE-1)){
    return ERROR;
  }
  return OK;
}

STATUS space_set_image_mid(Space* space, char* image_mid){
  if (image_mid == NULL || space == NULL){
    return ERROR;
  }
  if (!strncpy(space->image_mid, image_mid, IMG_SIZE-1)){
    return ERROR;
  }
  return OK;
}

STATUS space_set_image_down(Space* space, char* image_down){
  if (image_down == NULL || space == NULL){
    return ERROR;
  }
  if (!strncpy(space->image_down, image_down, IMG_SIZE-1)){
    return ERROR;
  }
  return OK;
}

const char* space_get_image_up(Space* space){
  if (space == NULL){
    return ERROR;
  }
  return space->image_up;
}

const char* space_get_image_mid(Space* space){
  if (space == NULL){
    return ERROR;
  }
  return space->image_mid;
}

const char* space_get_image_down(Space* space){
  if (space == NULL){
    return ERROR;
  }
  return space->image_down;
}

STATUS space_set_name(Space* space, char* name) {
  if (!space || !name) {
    return ERROR;
  }

  if (!strncpy(space->name, name, WORD_SIZE)) {
    return ERROR;
  }

  return OK;
}

STATUS space_set_north(Space* space, Id id) {
  if (!space || id == NO_ID) {
    return ERROR;
  }
  space->north = id;
  return OK;
}

STATUS space_set_south(Space* space, Id id) {
  if (!space || id == NO_ID) {
    return ERROR;
  }
  space->south = id;
  return OK;
}

STATUS space_set_east(Space* space, Id id) {
  if (!space || id == NO_ID) {
    return ERROR;
  }
  space->east = id;
  return OK;
}

STATUS space_set_west(Space* space, Id id) {
  if (!space || id == NO_ID) {
    return ERROR;
  }
  space->west = id;
  return OK;
}

BOOL space_has_object(Space* space, Id id){
  if (space == NULL || id <= NO_ID){
    return TRUE;
  }
   if (set_has_id (space->object, id) > -1){
     return TRUE;
   }
  return FALSE;
}


STATUS space_add_object(Space* space, Id value) {
  if (!space || value <= NO_ID) {
    return ERROR;
  }
  if (space_has_object(space, value) == TRUE){
    return OK;
  }
  if (set_add_id(space->object, value) == ERROR){
    return ERROR;
  }
  return OK;
}

STATUS space_delete_object(Space* space, Id value) {
  if (!space || value <= NO_ID) {
    return ERROR;
  }
  if (space_has_object(space, value) == FALSE){
    return OK;
  }
  if (set_delete_id(space->object, value) == ERROR){
    return ERROR;
  }
  return OK;
}

const char * space_get_name(Space* space) {
  if (!space) {
    return NULL;
  }
  return space->name;
}

Id space_get_id(Space* space) {
  if (!space) {
    return NO_ID;
  }
  return space->id;
}

Id space_get_north(Space* space) {
  if (!space) {
    return NO_ID;
  }
  return space->north;
}

Id space_get_south(Space* space) {
  if (!space) {
    return NO_ID;
  }
  return space->south;
}

Id space_get_east(Space* space) {
  if (!space) {
    return NO_ID;
  }
  return space->east;
}

Id space_get_west(Space* space) {
  if (!space) {
    return NO_ID;
  }
  return space->west;
}

Id space_get_object(Space* space, int index) {
  if (!space) {
    return NO_ID;
  }
  return set_get_id_at(space->object, index);
}

int space_n_of_objects(Space* space) {
  if (!space) {
    return -1;
  }
  return set_get_n_elements(space->object);
}

STATUS space_print(Space* space) {
  Id idaux = NO_ID;

  if (!space) {
    return ERROR;
  }

  if(!fprintf(stdout, "--> Space (Id: %ld; Name: %s)\n", space->id, space->name)){
    return ERROR;
  }

  idaux = space_get_north(space);
  if (NO_ID != idaux) {
    fprintf(stdout, "---> North link: %ld.\n", idaux);
  } else {
    fprintf(stdout, "---> No north link.\n");
  }

  idaux = space_get_south(space);
  if (NO_ID != idaux) {
    fprintf(stdout, "---> South link: %ld.\n", idaux);
  } else {
    fprintf(stdout, "---> No south link.\n");
  }

  idaux = space_get_east(space);
  if (NO_ID != idaux) {
    fprintf(stdout, "---> East link: %ld.\n", idaux);
  } else {
    fprintf(stdout, "---> No east link.\n");
  }

  idaux = space_get_west(space);
  if (NO_ID != idaux) {
    fprintf(stdout, "---> West link: %ld.\n", idaux);
  } else {
    fprintf(stdout, "---> No west link.\n");
  }

  if (set_print(space->object) == ERROR){
    return ERROR;
  }
  fprintf(stdout, "%s\n", space->image_up);
  fprintf(stdout, "%s\n", space->image_mid);
  fprintf(stdout, "%s\n", space->image_down);



  return OK;
}
