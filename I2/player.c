/**
 * @brief It implements all the functions used to manage the player
 *
 * @file player.c
 * @author César Ramírez Martínes
 * @version 1.0
 * @date 20-09-2019
 * @copyright GNU Public License
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "types.h"
#include "player.h"

struct _Player {
  Id id;
  char name[WORD_SIZE + 1];
  Id location;
  Id object;
};

Player* player_create(Id id) {

  Player *newplayer = NULL;

  if (id == NO_ID)
    return NULL;

  newplayer = (Player *) malloc(sizeof (Player));

  if (newplayer == NULL) {
    return NULL;
  }
  newplayer->id = id;
  newplayer->name[0] = '\0';
  newplayer->object = NO_ID;
  newplayer->location = NO_ID;

  return newplayer;
}

STATUS player_destroy(Player* player) {
  if (!player) {
    return ERROR;
  }

  free(player);
  player = NULL;

  return OK;
}

STATUS player_set_name(Player* player, char* name) {
  if (!player || !name) {
    return ERROR;
  }

  if (!strcpy(player->name, name)) {
    return ERROR;
  }

  return OK;
}

STATUS player_set_location(Player* player, Id idLocation) {
  if (!player || idLocation < 0) {
    return ERROR;
  }

  player->location = idLocation;

  return OK;
}

STATUS player_set_object(Player* player, Id idObject) {
  if (!player) {
    return ERROR;
  }

  player->object = idObject;
  return OK;
}

Id player_get_id(Player* player) {
  if (!player) {
    return NO_ID;
  }
  return player->id;
}

const char * player_get_name(Player* player) {
  if (!player) {
    return NULL;
  }
  return player->name;
}

Id player_get_location(Player* player) {
  if (!player) {
    return NO_ID;
  }
  return player->location;
}

Id player_get_object(Player* player) {
  if (!player) {
    return NO_ID;
  }
  return player->object;
}

STATUS player_print(Player* player) {

  if (!player) {
    return ERROR;
  }

  if(!fprintf(stdout, "--> player (Id: %ld; Name: %s; Id of the location: %ld, Id of the object: %ld )\n", player->id, player->name, player->location, player->object)){
    return ERROR;
  }

  return OK;
}
