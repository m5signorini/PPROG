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
};

Object* object_create(Id id) {

  Object *newobject = NULL;

  if (id == NO_ID)
    return NULL;

  newobject = (Object *) malloc(sizeof (Object));

  if (newobject == NULL) {
    return NULL;
  }
  newobject->id = id;
  newobject->name[0] = '\0';

  return newobject;
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

  if (!strcpy(object->name, name)) {
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

STATUS object_print(Object* object) {

  if (!object) {
    return ERROR;
  }

  if(!fprintf(stdout, "--> Object (Id: %ld; Name: %s)\n", object->id, object->name)){
    return ERROR;
  }

  return OK;
}
