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
  char description[MAX_DESC + 1];
  Id north;
  Id south;
  Id east;
  Id west;
  Set* objects;
  char image[IMG_NUM][IMG_SIZE];
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

  new_space->objects = objects;

  memset(new_space->name, 0, WORD_SIZE + 1);
  memset(new_space->description, 0, MAX_DESC + 1);
  memset(new_space->image, 0, IMG_SIZE*IMG_NUM);


  return new_space;
}

STATUS space_destroy(Space* space) {
  if (!space) {
    return ERROR;
  }

  if(set_destroy(space->objects) == ERROR){
    return ERROR;
  }

  free(space);
  space = NULL;

  return OK;
}

STATUS space_set_image(Space* space, char* image, int pos){
  if (image == NULL || space == NULL || pos > IMG_NUM-1){
    return ERROR;
  }
  if (!strncpy(space->image[pos], image, IMG_SIZE-1)){
    return ERROR;
  }
  return OK;
}

const char* space_get_image(Space* space, int pos){
  if (space == NULL || pos > IMG_NUM-1){
    return NULL;
  }
  return space->image[pos];
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

STATUS space_set_description(Space* space, char* description) {
  if (!space || !description) {
    return ERROR;
  }

  if (!strncpy(space->description, description, MAX_DESC)) {
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
   if (set_has_id (space->objects, id) > -1){
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
  if (set_add_id(space->objects, value) == ERROR){
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
  if (set_delete_id(space->objects, value) == ERROR){
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

const char * space_get_description(Space* space) {
  if (!space) {
    return NULL;
  }
  return space->description;
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
  return set_get_id_at(space->objects, index);
}

STATUS space_print(Space* space) {
  Id idaux = NO_ID;

  if (!space) {
    return ERROR;
  }

  if(!fprintf(stdout, "--> Space (Id: %ld; Name: %s, Description: %s)\n", space->id, space->name, space->description)){
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

  if (set_print(space->objects) == ERROR){
    return ERROR;
  }
  fprintf(stdout, "%s\n", space->image_up);
  fprintf(stdout, "%s\n", space->image_mid);
  fprintf(stdout, "%s\n", space->image_down);



  return OK;
}
