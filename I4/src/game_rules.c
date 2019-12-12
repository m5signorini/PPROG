/**
 * @brief It implements all the functions used to manage the rules of the game
 *
 * @file game_rules.c
 * @author Cesar Ramirez
 * @version 1.0
 * @date 27-09-2019
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"

#define DIE_MAX
#define DIE_MIN
#define TURNS /**/

struct _GameRules {
  Game* game;    /*!< Id of the space*/
  int turn;
};


GameRules* game_rules_create(Game* game) {
  if(game == NULL){
    return NULL;
  }

  GameRules *game_rules = NULL;

  game_rules = (GameRules*) malloc(sizeof(GameRules));

  if (game_rules == NULL) {
    return NULL;
  }

  game_rules->turn = 0;
  game_rules->game = game;

  return game_rules;
}

STATUS game_rules_destroy(GameRules* game_rules) {
  if (!game_rules) {
    return ERROR;
  }

  if(game_destroy(game_rules->game) == ERROR){
    return ERROR;
  }

  free(game_rules);
  game_rules = NULL;

  return OK;
}

STATUS game_rules_dark(GameRules* game_rules){
  if(game_rules == NULL){
    return ERROR;
  }
  Space* space = NULL;
  int i = 0;

  while (space = game_get_space_at(game_rules->game, i++) != NULL){
       if (space_set_illuminated(space, FALSE) == ERROR){
         return ERROR;
       }
  }
  return OK;
}

STATUS game_rules_clopen_links(GameRules* game_rules){
  if(game_rules == NULL){
    return ERROR;
  }
  Link* link = NULL;
  int i = 0;

  while (link = game_get_link_at(game_rules->game, i) != NULL){
       if(link_get_open(link) == TRUE){
         if (link_set_open(link, FALSE) == ERROR){
           return ERROR;
         }
       }
       else {
         if (link_set_open(link, TRUE) == ERROR){
           return ERROR;
         }
      i++;
    }
  }
  return OK;
}

STATUS game_rules_hide_objects(GameRules* game_rules){
  if(game_rules == NULL){
    return ERROR;
  }
  Object* object = NULL;
  int i = 0;

  while (object = game_get_object_at(game_rules->game, i) != NULL){
       if (object_set_hidden(link, TRUE) == ERROR){
         return ERROR;
       }
      i++;
  }
  return OK;
}

STATUS game_rules_drop_objects(GameRules* game_rules){
  if(game_rules == NULL){
    return ERROR;
  }

  Object* object = NULL;
  int i = 0;
  Id idObject;
  Player* player = game_get_player(game_rules->game);
  Id idSpace = player_get_location(player);
  Space* space = game_get_space(game_rules->game, idSpace);

  while (object = player_get_object_at(player, i) != NULL){
       if (idObject = object_get_id(object) == NO_ID){
         return ERROR;
       }
       if (space_add_object(space, idObject) == ERROR){
         return ERROR;
       }
      if (player_delete_object(player, idObject) == ERROR){
        return ERROR;
      }
      i++;
  }
  return OK;
}

STATUS game_rules_teleport(GameRules* game_rules){
  if(game_rules == NULL){
    return ERROR;
  }
  int i;
  int random;
  for (i = 0; i < MAX_SPACES; i++){
     if(game_get_space_id_at(game_rules->game, i) == NO_ID){
       break
     }
  }
  random = rand()/(RAND_MAX + 1.) * ((i - 1) + 1) + 1);

  Player* player = game_get_player(game_rules->game);
  Id idSpace = game_get_space_id_at(game_rules->game, random);

  if(player_set_location(player, idSpace) == NULL){
    return ERROR;
  }
  return OK;
}

STATUS

STATUS game_rules_main(GameRules* game_rules){
  if(game_rules == NULL){
    return ERROR;
  }
  STATUS control;

  switch (game_rules->turn){
    case 1:
       control = game_rules_dark(game_rules);
       break;
    case 2:
       control = game_rules_close_links(game_rules);
       break;
    case 3:
       control = game_rules_hide_objects(game_rules);
       break;
    case 4:
       control = game_rules_drop_objects(game_rules);
       break;
    case 5:
       control = game_rules_teleport(game_rules):
       break;
    case 6:
       control =
       break;

  }
  return control;
}
