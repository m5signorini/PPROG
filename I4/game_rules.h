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

typedef struct _GameRules GameRules;

GameRules* game_rules_create();
STATUS game_rules_destroy(GameRules* game_rules);

#endif
