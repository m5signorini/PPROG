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
    return NULL;
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

STATUS game_rules_open_even_links(GameRules* game_rules){
  if(game_rules == NULL){
    return NULL;
  }
  Link* link = NULL;
  int i = 0;

  while (link = game_get_link_at(game_rules->game, 2*i) != NULL){
       if (link_set_open(link, FALSE) == ERROR){
         return ERROR;
       }
      i++;
  }
  return OK;
}

STATUS game_rules_hide_objects(GameRules* game_rules){
  if(game_rules == NULL){
    return NULL;
  }
  Object* object = NULL;
  i = 0;

  while (object = game_get_object_at(game_rules->game, i) != NULL){
       if (object_set_hidden(link, TRUE) == ERROR){
         return ERROR;
       }
      i++;
  }
  return OK;
}

STATUS game_rules_main(GameRules* game_rules){
  if(game_rules == NULL){
    return NULL;
  }
  STATUS control;

  switch (game_rules->turn){
    case 1:
       control = game_rules_dark(game_rules);
       break;
    case 2:
      control = game_rules_open_even_links(game_rules);
      break;
    case 3:
      control = game_rules_hide_objects(game_rules);
      break;


  }
  return control;
}
