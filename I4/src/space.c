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
  Id id;    /*!< Id of the space*/
  char name[WORD_SIZE + 1];   /*!< Name of the space */
  char description[MAX_DESC + 1];   /*!< Description of the space */
  char long_description[MAX_DESC + 1];   /*!< Extended description of the space */
  Id north;   /*!< Id of the north-link link of the space */
  Id south;   /*!< Id of the south-link of the space*/
  Id east;    /*!< Id of the east-link of the space*/
  Id west;    /*!< Id of the west-link of the space*/
  Id up;    /*!< Id of the up-link of the space*/
  Id down;    /*!< Id of the down-link of the space*/
  Set* objects;   /*!< Memory direction of the set that stores the objects of the space*/
  char image[IMG_NUM][IMG_SIZE];    /*!< A matrix of characters that compose a background image*/
  BOOL illuminated;    /*!< Bool value of the ilumination in the space*/
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
  new_space->up = NO_ID;
  new_space->down = NO_ID;
  new_space->illuminated = TRUE;

  new_space->objects = objects;

  memset(new_space->name, 0, WORD_SIZE + 1);
  memset(new_space->description, 0, MAX_DESC + 1);
  memset(new_space->long_description, 0, MAX_DESC + 1);
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

Id space_get_object_at(Space* space, int index) {
  if (!space) {
    return NO_ID;
  }
  return set_get_id_at(space->objects, index);
}

STATUS space_print(Space* space) {
  Id idaux = NO_ID;
  int i;

  if (!space) {
    return ERROR;
  }

  if(!fprintf(stdout, "--> Space (Id: %ld; Name: %s, Illuminated: %d, Description: %s, Long description: %s)\n", space->id, space->name, space->illuminated, space->description, space->long_description)){
    return ERROR;
  }

  idaux = space_get_up(space);
  if (NO_ID != idaux) {
    fprintf(stdout, "---> Up link: %ld.\n", idaux);
  } else {
    fprintf(stdout, "---> No up link.\n");
  }

  idaux = space_get_down(space);
  if (NO_ID != idaux) {
    fprintf(stdout, "---> Down link: %ld.\n", idaux);
  } else {
    fprintf(stdout, "---> No down link.\n");
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
  for(i=0; i < IMG_NUM; i++){
    fprintf(stdout, "%s\n", space->image[i]);
  }

  return OK;
}

STATUS space_set_illuminated(Space* space, BOOL value){
  if (space == NULL){
    return ERROR;
  }
  space->illuminated = value;

  return OK;
}

BOOL space_get_illuminated(Space* space){
  if (space == NULL){
    return FALSE;
  }

  return space->illuminated;
}

STATUS space_set_up(Space* space, Id up){
  if (space == NULL || up == NO_ID){
    return ERROR;
  }
  space->up = up;

  return OK;
}

Id space_get_up(Space* space){
  if (space == NULL){
    return ERROR;
  }

  return space->up;
}

STATUS space_set_down(Space* space, Id down){
  if (space == NULL || down == NO_ID){
    return ERROR;
  }
  space->down = down;

  return OK;
}

Id space_get_down(Space* space){
  if (space == NULL){
    return ERROR;
  }

  return space->down;
}

STATUS space_set_long_description(Space* space, char* description) {
  if (!space || !description) {
    return ERROR;
  }

  if (!strncpy(space->long_description, description, MAX_DESC)) {
    return ERROR;
  }

  return OK;
}

const char * space_get_long_description(Space* space) {
  if (!space) {
    return NULL;
  }
  return space->long_description;
}
