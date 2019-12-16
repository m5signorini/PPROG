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
/**
* @brief Creates a game_rules
*
* game_rules_create creates a new game_rules
*
* @date 15/12/2019
* @author: César Ramírez Martínez
*
* @return the game_rules created
*/

STATUS game_rules_destroy(GameRules* game_rules);
/**
* @brief Destroy the structure game_rules
*
* game_rules_destroy destroys the game rules
*
* @date 15/12/2019
* @author: César Ramírez Martínez
*
* @param game_rules the game_rules that will be deleted
* @return OK or ERROR for error management
*/

STATUS game_rules_dark(GameRules* game_rules);
/**
* @brief Turn all the lights where the player is placed off
*
* game_rules_dark first rule of the game rules
*
* @date 15/12/2019
* @author: César Ramírez Martínez
*
* @param game_rules the game_rules that will be used
* @return OK or ERROR for error management
*/

STATUS game_rules_teleport(GameRules* game_rules);
/**
* @brief Teleports the player to a random space
*
* game_rules_teleport second rule of the game rules
*
* @date 15/12/2019
* @author: César Ramírez Martínez
*
* @param game_rules the game_rules that will be used
* @return OK or ERROR for error management
*/

STATUS game_rules_clopen_links(GameRules* game_rules);
/**
* @brief This rule closes all the open links and closes all the open ones
*
* game_rules_teleport third rule of the game rules
*
* @date 15/12/2019
* @author: César Ramírez Martínez
*
* @param game_rules the game_rules that will be used
* @return OK or ERROR for error management
*/

STATUS game_rules_hide_objects(GameRules* game_rules);
/**
* @brief This rule hides all the objects of the game
*
* game_rules_hide_objects fourth rule of the game rules
*
* @date 15/12/2019
* @author: César Ramírez Martínez
*
* @param game_rules the game_rules that will be used
* @return OK or ERROR for error management
*/

STATUS game_rules_rotation(GameRules* game_rules);
/**
* @brief This rule drops the item of the player
*
* game_rules_drop_objects makes the player to drop his items
*
* @date 15/12/2019
* @author: César Ramírez Martínez
*
* @param game_rules the game_rules that will be used
* @return OK or ERROR for error management
*/

STATUS game_rules_drop_objects(GameRules* game_rules);

/**
* @brief This rule does nothing
*
* game_rules_no_rule doesnt do anything
*
* @date 15/12/2019
* @author: César Ramírez Martínez
*
* @param game_rules the game_rules that will be used
* @return OK or ERROR for error management
*/

STATUS game_rules_no_rule(GameRules* game_rules);

/**
* @brief This rule drops all the objects that the player is carrying in the actual space
*
* game_rules_rotation sixth rule of the game rules
*
* @date 15/12/2019
* @author: César Ramírez Martínez
*
* @param game_rules the game_rules that will be used
* @return OK or ERROR for error management
*/

STATUS game_rules_main(GameRules* game_rules);
/**
* @brief This function will decide which of the previous rules will be applied according to a
*         certain number stored in the game_rules structure
*
* game_rules_main main function of game rules
*
* @date 15/12/2019
* @author: César Ramírez Martínez
*
* @param game_rules the game_rules that will be used
* @return OK or ERROR for error management
*/

#endif
