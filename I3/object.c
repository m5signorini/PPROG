/**
 * @brief It implements all the functions used to manage the objects
 *
 * @file object.c
 * @author César Ramírez Martínes
 * @version 1.0
 * @date 20-09-2019
 * @copyright GNU Public License
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "types.h"
#include "object.h"

struct _Object {
  Id id;
  char name[WORD_SIZE + 1];
  char description[MAX_DESC + 1]
};

Object* object_create(Id id) {

  Object *new_object = NULL;

  if (id == NO_ID)
    return NULL;

  new_object = (Object *) malloc(sizeof (Object));

  if (new_object == NULL) {
    return NULL;
  }
  new_object->id = id;
  memset(new_object->name, 0, WORD_SIZE + 1);
  memset(new_object->description, 0, MAX_DESC + 1);

  return new_object;
}

STATUS object_destroy(Object* object) {
  if (!object) {
    return ERROR;
  }

  free(object);
  object = NULL;

  return OK;
}

STATUS object_set_name(Object* object, char* name) {
  if (!object || !name) {
    return ERROR;
  }

  if (!strncpy(object->name, name, WORD_SIZE)) {
    return ERROR;
  }

  return OK;
}

STATUS object_set_description(Object* object, char* description) {
  if (!object || !description) {
    return ERROR;
  }

  if (!strncpy(object->description, description, MAX_DESC)) {
    return ERROR;
  }

  return OK;
}

Id object_get_id(Object* object) {
  if (!object) {
    return NO_ID;
  }
  return object->id;
}

const char * object_get_name(Object* object) {
  if (!object) {
    return NULL;
  }
  return object->name;
}

const char * object_get_description(Object* object) {
  if (!object) {
    return NULL;
  }
  return object->description;
}

STATUS object_print(Object* object) {

  if (!object) {
    return ERROR;
  }

  if(!fprintf(stdout, "--> Object (Id: %ld; Name: %s, Description: %s)\n", object->id, object->name, object->description)){
    return ERROR;
  }

  return OK;
}
