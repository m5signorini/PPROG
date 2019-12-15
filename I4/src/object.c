/**
 * @brief It implements all the functions used to manage the objects
 *
 * @file object.c
 * @author César Ramírez Martínez
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
  Id id;    /*!< Id of the object*/
  char name[WORD_SIZE + 1];   /*!< Name of the object */
  char description[MAX_DESC + 1];  /*!< Description of the object */
  char moved_description[MAX_DESC + 1];
  Id open;
  BOOL movable;
  BOOL moved;
  BOOL hidden;
  BOOL illuminate;
  BOOL turnedon;
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
  memset(new_object->moved_description, 0, MAX_DESC + 1);
  new_object->open = NO_ID;
  new_object->movable = FALSE;
  new_object->moved = FALSE;
  new_object->hidden = FALSE;
  new_object->illuminate = FALSE;
  new_object->turnedon = FALSE;

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

STATUS object_set_moved_description(Object* object, char* description) {
  if (!object || !description) {
    return ERROR;
  }

  if (!strncpy(object->moved_description, description, MAX_DESC)) {
    return ERROR;
  }

  return OK;
}

STATUS object_set_open(Object* object, Id open) {
  if (!object || open == NO_ID) {
    return ERROR;
  }
  object->open = open;

  return OK;
}

STATUS object_set_movable(Object* object, BOOL movable) {
  if (!object) {
    return ERROR;
  }
  object->movable = movable;

  return OK;
}

STATUS object_set_moved(Object* object, BOOL moved) {
  if (!object) {
    return ERROR;
  }
  object->moved = moved;

  return OK;
}

STATUS object_set_hidden(Object* object, BOOL hidden) {
  if (!object) {
    return ERROR;
  }
  object->hidden = hidden;

  return OK;
}

STATUS object_set_illuminate(Object* object, BOOL illuminate) {
  if (!object) {
    return ERROR;
  }
  object->illuminate = illuminate;

  return OK;
}

STATUS object_set_turnedon(Object* object, BOOL turnedon) {
  if (!object) {
    return ERROR;
  }
  object->turnedon = turnedon;

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
  if (object->moved == FALSE) {
    return object->description;
  }
  return object->moved_description;
}

Id object_get_open(Object* object) {
  if (!object) {
    return NO_ID;
  }
  return object->open;
}

BOOL object_get_movable(Object* object) {
  if (!object) {
    return FALSE;
  }
  return object->movable;
}

BOOL object_get_moved(Object* object) {
  if (!object) {
    return FALSE;
  }
  return object->moved;
}

BOOL object_get_hidden(Object* object) {
  if (!object) {
    return FALSE;
  }
  return object->hidden;
}

BOOL object_get_illuminate(Object* object) {
  if (!object) {
    return FALSE;
  }
  return object->illuminate;
}

BOOL object_get_turnedon(Object* object) {
  if (!object) {
    return FALSE;
  }
  return object->turnedon;
}

const char * object_get_default_description(Object* object) {
    if(object == NULL) return NULL;
    return object->moved_description;
}

const char * object_get_moved_description(Object* object) {
    if(object == NULL) return NULL;
    return object->description;
}


STATUS object_print(Object* object) {

  if (!object) {
    return ERROR;
  }

  if(!fprintf(stdout, "--> Object (Id: %ld; Name: %s, Description: %s, Moved descrption: %s)\n", object->id, object->name, object->description, object->moved_description)){
    return ERROR;
  }

  return OK;
}
