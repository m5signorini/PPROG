/**
 * @brief It implements all the functions used to manage the spaces of the game
 *
 * @file space.c
 * @author Profesores PPROG
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

struct _GameRules {
  Game* game;    /*!< Id of the space*/
  Die* die;   /*!< Name of the space */
};


GameRules* game_rules_create(Game* game) {

  GameRules *game_rules = NULL;
  Die* die = NULL;

  game_rules = (GameRules*) malloc(sizeof(GameRules));

  if (game_rules == NULL) {
    return NULL;
  }

  game = game_create();

  if (game == NULL) {
    free(game_rules);
    return NULL;
  }

  die = die_create(1, 1, 6);

  if(die == NULL) {
    game_destroy(game);
    free(game_rules);
    return NULL;
  }

  game_set_die(game_rules->game, die);

  game_rules->game = game;
  game_rules->die = die;

  return game_rules;
}

STATUS game_rules_destroy(GameRules* game_rules) {
  if (!game_rules) {
    return ERROR;
  }

  if(game_destroy(game_rules->game) == ERROR){
    return ERROR;
  }

  if(die_destroy(game_rules->die) == ERROR){
    return ERROR;
  }

  free(game_rules);
  game_rules = NULL;

  return OK;
}

STATUS game_rules_main(GameRules* game_rules){
  if(game_rules == NULL){
    return NULL;
  }
}
