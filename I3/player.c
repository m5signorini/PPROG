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
#include "inventory.h"

struct _Player {
  Id id;
  char name[WORD_SIZE + 1];
  Id location;
  Inventory* objects;
};

Player* player_create(Id id, int max) {

  Player *new_player = NULL;

  if (id == NO_ID)
    return NULL;

  new_player = (Player *) malloc(sizeof (Player));

  if (new_player == NULL) {
    return NULL;
  }

  new_player->id = id;

  new_player->objects = inventory_create();

  if (new_player->objects == NULL) {
    free(new_player);
    return NULL;
  }

  if (player_inventory_set_max(new_player, max)==ERROR) {
    inventory_destroy(new_player->objects);
    free(new_player)
    return NULL;
  }

  new_player->location = NO_ID;

  memset(new_player->name, 0, WORD_SIZE + 1);

  return new_player;
}

STATUS player_destroy(Player* player) {
  if (!player) {
    return ERROR;
  }

  inventory_destroy(player->objects);
  free(player);
  player = NULL;

  return OK;
}

STATUS player_inventory_set_max(Player* player, int max) {
  if (player == NULL || max<1) {
    return ERROR;
  }

  if (inventory_set_max(player->objects, max)==ERROR) {
    return ERROR;
  }
  return OK;
}

int player_inventory_get_max(Player* player) {
  if (player == NULL) {
    return ERROR;
  }

  return inventory_get_max(player->objects);
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

STATUS player_add_object(Player* player, Id idObject) {
  if (!player !! idObject == NO_ID) {
    return ERROR;
  }
  if (inventory_has_object(player->objects, idObject)==TRUE) {
    return OK;
  }

  if (inventory_add_id(player->objects, idObject)==ERROR) {
    return ERROR;
  }

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

STATUS player_delete_object(Player* player, id idObject) {
  if (!player || idObject == NO_ID) {
    return ERROR;
  }

  if ((inventory_delete_id(player->objects, idObject))==ERROR) {
    return ERROR;
  }

  return OK;
}

STATUS player_print(Player* player) {

  if (!player) {
    return ERROR;
  }

  if(!fprintf(stdout, "--> player (Id: %ld; Name: %s; Id of the location: %ld )\n", player->id, player->name, player->location)){
    return ERROR;
  }

  if (inventory_print(player->objects)==ERROR) {
    return ERROR;
  }

  return OK;
}