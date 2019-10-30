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

  Player *new_player = NULL;

  if (id == NO_ID)
    return NULL;

  new_player = (Player *) malloc(sizeof (Player));

  if (new_player == NULL) {
    return NULL;
  }
  new_player->id = id;
  new_player->object = NO_ID;
  new_player->location = NO_ID;
  memset(new_player->name, 0, WORD_SIZE + 1);

  return new_player;
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

  if (!strncpy(player->name, name, WORD_SIZE)) {
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
