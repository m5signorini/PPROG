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
#include "game_rules.h"

#define TURNS 5

struct _GameRules {
  Game* game; /*!< Game in which the  gam_rules will be applied*/
  int turn; /*!< Number that will decided with rule will be applied*/
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
  free(game_rules);
  return OK;
}

STATUS game_rules_dark(GameRules* game_rules){
  if(game_rules == NULL){
    return ERROR;
  }
  Space* space = NULL;
  int i = 0;

  while ((space = game_get_space_at(game_rules->game, i++)) != NULL){
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

  while ((link = game_get_link_at(game_rules->game, i)) != NULL){
    if(link_get_open(link) == TRUE){
      if (link_set_open(link, FALSE) == ERROR){
        return ERROR;
      }
    }
    else {
      if (link_set_open(link, TRUE) == ERROR){
        return ERROR;
      }
    }
    i++;
  }
  return OK;
}

STATUS game_rules_hide_objects(GameRules* game_rules){
  if(game_rules == NULL){
    return ERROR;
  }
  Object* object = NULL;
  int i = 0;

  while ((object = game_get_object_at(game_rules->game, i)) != NULL){
    if(object_get_hidden(object) == TRUE) {
      if (object_set_hidden(object, FALSE) == ERROR){
        return ERROR;
      }
    }
    else if(object_get_hidden(object) == FALSE) {
      if (object_set_hidden(object, TRUE) == ERROR){
        return ERROR;
      }
    }
    i++;
  }
  return OK;
}

STATUS game_rules_drop_objects(GameRules* game_rules){
  if(game_rules == NULL){
    return ERROR;
  }

  int i = 0;
  Id idObject;
  Player* player = game_get_player(game_rules->game);
  Id idSpace = player_get_location(player);
  Space* space = game_get_space(game_rules->game, idSpace);

  while ((idObject = player_get_object_at(player, i)) != NO_ID){
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
      break;
    }
  }
  random = (rand()/(RAND_MAX + 1.) * ((i - 1) + 1) + 1);

  Player* player = game_get_player(game_rules->game);
  Id idSpace = game_get_space_id_at(game_rules->game, random);

  if(player_set_location(player, idSpace) == ERROR){
    return ERROR;
  }
  return OK;
}

STATUS game_rules_rotation(GameRules* game_rules){
  if(game_rules == NULL){
    return ERROR;
  }
  Player* player = game_get_player(game_rules->game);
  Id idSpace = player_get_location(player);
  Space* space = game_get_space(game_rules->game, idSpace);
  Id northId, eastId, westId, southId;

  northId =  space_get_north(space);
  southId =  space_get_south(space);
  eastId =  space_get_east(space);
  westId =  space_get_west(space);

  space_set_north(space, westId);
  space_set_south(space, eastId);
  space_set_west(space, southId);
  space_set_east(space, northId);

  return OK;
}

STATUS game_rules_no_rule(GameRules* game_rules) {
  if(game_rules == NULL) {
    return ERROR;
  }
  return ERROR;
}

STATUS game_rules_main(GameRules* game_rules){
  if(game_rules == NULL){
    return ERROR;
  }
  STATUS control;
  int num;
  game_rules->turn = (game_rules->turn+1)%TURNS;

  #ifdef NO_RULES
  control = game_rules_no_rule(game_rules);
  return control;
  #endif

  if(game_rules->turn != 0) {
    return ERROR;
  }
  else {
    num = die_roll(game_get_die(game_rules->game));
  }

  switch (num){
    case 1:
    control = game_rules_dark(game_rules);
    dialogue_set_feedback(game_get_dialogue(game_rules->game), "Now all spaces are dark");
    break;
    case 2:
    control = game_rules_clopen_links(game_rules);
    dialogue_set_feedback(game_get_dialogue(game_rules->game), "What is closed, now is open and the other way around");
    break;
    case 3:
    control = game_rules_hide_objects(game_rules);
    dialogue_set_feedback(game_get_dialogue(game_rules->game), "What is hidden, now is visible and the other way around");
    break;
    case 4:
    control = game_rules_drop_objects(game_rules);
    dialogue_set_feedback(game_get_dialogue(game_rules->game), "All your items have fallen down");
    break;
    case 5:
    control = game_rules_teleport(game_rules);
    dialogue_set_feedback(game_get_dialogue(game_rules->game), "You've been teleported");
    break;
    case 6:
    control = game_rules_rotation(game_rules);
    dialogue_set_feedback(game_get_dialogue(game_rules->game), "This space has been rotated");
    break;
    default:
    control = game_rules_no_rule(game_rules);
    dialogue_set_feedback(game_get_dialogue(game_rules->game), "No rule applied");
    break;

  }
  return control;
}
