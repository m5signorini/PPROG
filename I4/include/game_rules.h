/**
 * @brief It defines a space
 *
 * Added descriptions
 *
 * @file space.h
 * @author Profesores PPROG
 * @version 2.0
 * @date 13-01-2015
 * @copyright GNU Public License
 */

#ifndef GAME_RULES_H
#define GAME_RULES_H

#include "types.h"
#include "game.h"
#include "die.h"

#define N_RULES 17

typedef struct _GameRules GameRules;

GameRules* game_rules_create();
STATUS game_rules_destroy(GameRules* game_rules);

STATUS game_rules_dark(GameRules* game_rules);
STATUS game_rules_clopen_links(GameRules* game_rules);
STATUS game_rules_hide_objects(GameRules* game_rules);
STATUS game_rules_drop_objects(GameRules* game_rules);
STATUS game_rules_teleport(GameRules* game_rules):
STATUS game_rules_main(GameRules* game_rules);


#endif
