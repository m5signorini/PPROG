/**
 * @brief It implements all the functions used to manage the links between spaces of the game
 *
 * @file link.c
 * @author Félix Estaún
 * @version 1.0
 * @date 07-11-2019
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "link.h"

struct _Link {
  Id id;    /*!< Id of the link*/
  char name[WORD_SIZE + 1];   /*!< Name of the link*/
  Id spaces[2];   /*!< Id of the spaces connected by the link*/
  BOOL open;    /*!< Status of the link (open or closed)*/
};

Link* link_create(Id id) {
  Link *new_link = NULL;

  if (id == NO_ID){
    return NULL;
  }

  new_link = (Link*)malloc(sizeof(Link));
  if (new_link == NULL) {
    return NULL;
  }

  new_link->id = id;
  new_link->spaces[0] = NO_ID;
  new_link->spaces[1] = NO_ID;
  new_link->open = TRUE;

  memset(new_link->name, 0, WORD_SIZE + 1);

  return new_link;
}

STATUS link_destroy(Link* link) {
  if (!link) {
    return ERROR;
  }

  free(link);
  link = NULL;

  return OK;
}

Id link_get_id(Link* link) {
  if (!link) {
    return NO_ID;
  }
  return link->id;
}

STATUS link_set_name(Link* link, char* name) {
  if (!link || !name) {
    return ERROR;
  }

  if (!strncpy(link->name, name, WORD_SIZE)) {
    return ERROR;
  }

  return OK;
}

const char * link_get_name(Link* link) {
  if (!link) {
    return NULL;
  }
  return link->name;
}

STATUS link_set_space1(Link* link, Id id) {
  if (!link || id == NO_ID) {
    return ERROR;
  }
  link->spaces[0] = id;
  return OK;
}

Id link_get_space1(Link* link) {
  if (!link) {
    return NO_ID;
  }
  return link->spaces[0];
}

STATUS link_set_space2(Link* link, Id id) {
  if (!link || id == NO_ID) {
    return ERROR;
  }
  link->spaces[1] = id;
  return OK;
}

Id link_get_space2(Link* link) {
  if (!link) {
    return NO_ID;
  }
  return link->spaces[1];
}

STATUS link_set_open(Link* link, BOOL open) {
  if (!link) {
    return ERROR;
  }

  link->open = open;
  return OK;
}

BOOL link_get_open(Link* link) {
  if (!link) {
    return FALSE;
  }

  return link->open;
}

Id link_get_to(Link* link, Id current_id) {
  if (!link || current_id == NO_ID) {
    return NO_ID;
  }

  if (link->spaces[0] == current_id) {
    return link->spaces[1];
  }
  else if (link->spaces[1] == current_id) {
    return link->spaces[0];
  }

  else return NO_ID;
}

STATUS link_print(Link *link) {
  Id idaux = NO_ID;

  if (!link) {
    return ERROR;
  }

  if(!fprintf(stdout, "--> Link (Id: %ld; Name: %s)\n", link->id, link->name)){
    return ERROR;
  }

  idaux = link_get_space1(link);
  if (NO_ID != idaux) {
    fprintf(stdout, "---> Space 1: %ld.\n", idaux);
  } else {
    fprintf(stdout, "---> No space1 in link.\n");
  }

  idaux = link_get_space2(link);
  if (NO_ID != idaux) {
    fprintf(stdout, "---> Space 2: %ld.\n", idaux);
  } else {
    fprintf(stdout, "---> No space2 in link.\n");
  }

  if (link->open == TRUE) {
    fprintf(stdout, "---> Open: TRUE.\n");
  } else {
    fprintf(stdout, "---> Open: FALSE.\n");
  }

  return OK;
}
