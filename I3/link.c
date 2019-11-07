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

struct _Link {
  Id id;
  char name[WORD_SIZE + 1];
  Id from;
  Id to;
  BOOL abierto;
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
  new_link->from = NO_ID;
  new_link->to = NO_ID;
  new_link->abierto = TRUE;

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

STATUS link_set_from(Link* link, Id from) {
  if (!link || id == NO_ID) {
    return ERROR;
  }
  link->from = from;
  return OK;
}

Id link_get_from(Link* link) {
  if (!link) {
    return NO_ID;
  }
  return link->from;
}

STATUS link_set_to(Link* link, Id to) {
  if (!link || id == NO_ID) {
    return ERROR;
  }
  link->to = to;
  return OK;
}

Id link_get_to(Link* link) {
  if (!link) {
    return NO_ID;
  }
  return link->to;
}

STATUS link_set_abierto(Link* link, BOOL abierto) {
  if (!link) {
    return ERROR;
  }

  link->abierto = abierto;
  return OK;
}

BOOL link_get_abierto(Link* link) {
  if (!link) {
    return FALSE;
  }

  return link->abierto;
}

STATUS link_print(Link *link) {
  Id idaux = NO_ID;

  if (!link) {
    return ERROR;
  }

  if(!fprintf(stdout, "--> Link (Id: %ld; Name: %s)\n", link->id, link->name)){
    return ERROR;
  }

  idaux = link_get_from(link);
  if (NO_ID != idaux) {
    fprintf(stdout, "---> From link: %ld.\n", idaux);
  } else {
    fprintf(stdout, "---> No from link.\n");
  }

  idaux = link_get_to(link);
  if (NO_ID != idaux) {
    fprintf(stdout, "---> To link: %ld.\n", idaux);
  } else {
    fprintf(stdout, "---> No to link.\n");
  }

  if (link->abierto == TRUE) {
    fprintf(stdout, "---> Abierto: TRUE.\n");
  } else {
    fprintf(stdout, "---> Abierto: FALSE.\n");
  }

  return OK;
}
