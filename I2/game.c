/**
 * @brief It implements the game interface and all the associated callbacks
 * for each command
 *
 * Modified the struct of game adding more objects, commands and a dice
 *
 * @file game.c
 * @author Martin Sanchez Signorini
 * @version 3.0
 * @date 30-10-2019
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"

#define N_CALLBACK 9
#define MAX_OBJECTS 50

struct _Game {
  Object* objects[MAX_OBJECTS + 1];
  Player* player;
  Space* spaces[MAX_SPACES + 1];
  Die* die;
  T_Command last_cmd;
  STATUS last_cmd_stat;
};

/**
   Define the function type for the callbacks
*/
typedef STATUS (*callback_fn)(Game* game);

/**
   List of callbacks for each command in the game
*/
STATUS game_callback_unknown(Game* game);
STATUS game_callback_exit(Game* game);
STATUS game_callback_next(Game* game);
STATUS game_callback_back(Game* game);
STATUS game_callback_right(Game* game);
STATUS game_callback_left(Game* game);
STATUS game_callback_take(Game* game);
STATUS game_callback_drop(Game* game);
STATUS game_callback_roll(Game* game);

static callback_fn game_callback_fn_list[N_CALLBACK]={
  game_callback_unknown,
  game_callback_exit,
  game_callback_next,
  game_callback_back,
  game_callback_right,
  game_callback_left,
  game_callback_take,
  game_callback_drop,
  game_callback_roll};


/**
   Game interface implementation
*/

Game* game_create() {
  int i;
  Game* game = NULL;

  game = (Game *) malloc(sizeof (Game));
  if(game == NULL) return NULL;

  /* Initial Set of the game*/
  for (i = 0; i < MAX_SPACES; i++) {
    game->spaces[i] = NULL;
  }

  for (i = 0; i < MAX_OBJECTS; i++) {
    game->objects[i] = NULL;
  }

  game->player = NULL;
  game->last_cmd = NO_CMD;
  game->die = NULL;
  game->last_cmd_stat = OK;

  return game;
}

STATUS game_destroy(Game* game) {
  if (game == NULL) return ERROR;
  int i = 0;

  for (i = 0; (i < MAX_SPACES) && (game->spaces[i] != NULL); i++) {
    space_destroy(game->spaces[i]);
  }

  for (i = 0; (i < MAX_OBJECTS) && (game->objects[i] != NULL); i++) {
    object_destroy(game->objects[i]);
  }

  player_destroy(game->player);
  die_destroy(game->die);
  free(game);

  return OK;
}

/**
    Space management
*/

STATUS game_add_space(Game* game, Space* space) {
  if (game == NULL || space == NULL) {
    return ERROR;
  }

  int i = 0;

  while ( (i < MAX_SPACES) && (game->spaces[i] != NULL)){
    i++;
  }

  if (i >= MAX_SPACES) {
    return ERROR;
  }

  game->spaces[i] = space;

  return OK;
}

Id game_get_space_id_at(Game* game, int position) {
  if (game == NULL || position < 0 || position >= MAX_SPACES) {
    return NO_ID;
  }

  return space_get_id(game->spaces[position]);
}

Space* game_get_space(Game* game, Id id){
  if(game == NULL) return NULL;
  int i = 0;

  if (id == NO_ID) {
    return NULL;
  }

  for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++) {
    if (id == space_get_id(game->spaces[i])){
      return game->spaces[i];
    }
  }
  return NULL;
}

/**
  Player Management
*/

STATUS game_set_player(Game* game, Player* player) {
  if (game == NULL || player == NULL) {
    return ERROR;
  }
  game->player = player;
  return OK;
}

Player* game_get_player(Game* game) {
  if(game == NULL) return NULL;
  return game->player;
}

/**
  Object Management
*/

STATUS game_add_object(Game* game, Object* obj) {
  if (game == NULL || obj == NULL ) {
    return ERROR;
  }

  int i = 0;

  while((i<MAX_OBJECTS) && game->objects[i] != NULL) {
    i++;
  }

  if(i>MAX_OBJECTS) {
    return ERROR;
  }

  game->objects[i] = obj;
  return OK;
}

Id game_get_object_id_at(Game* game, int position) {
  if(game == NULL || position < 0 || position > MAX_OBJECTS) {
    return NO_ID;
  }

  Object* obj = NULL;

  obj = game->objects[position];
  if(obj == NULL) return NO_ID;

  return object_get_id(obj);
}

Object* game_get_object(Game* game, Id id) {
  if(game == NULL) return NULL;
  int i = 0;

  if (id == NO_ID) {
    return NULL;
  }

  for (i = 0; i < MAX_OBJECTS && game->objects[i] != NULL; i++) {
    if (id == object_get_id(game->objects[i])){
      return game->objects[i];
    }
  }

  return NULL;
}

Id game_get_object_location(Game* game, Id obj) {
  if(game == NULL || obj == NO_ID) return NO_ID;
  int i;
  int j = 0;
  Id idaux = NO_ID;

  for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++) {
    j = 0;
    while((idaux = space_get_object(game->spaces[i], j++)) != NO_ID) {
      if (idaux == obj){
        return space_get_id(game->spaces[i]);
      }
    }
  }

  return NO_ID;
}

/**
  Die management
*/

Die* game_get_die(Game* game) {
  if(game == NULL) return NULL;
  return game->die;
}

STATUS game_set_die(Game* game, Die* die) {
  if(game == NULL || die == NULL) return ERROR;
  game->die = die;
  return OK;
}

/**
  Command Management
*/

STATUS game_update(Game* game, T_Command cmd) {
  if(game == NULL) return ERROR;
  game->last_cmd = cmd;
  game->last_cmd_stat = (*game_callback_fn_list[cmd])(game);
  return game->last_cmd_stat;
}

T_Command game_get_last_command(Game* game) {
  if(game == NULL) return ERROR;
  return game->last_cmd;
}

STATUS game_get_last_command_stat(Game* game) {
  if(game == NULL) return ERROR;
  return game->last_cmd_stat;
}

void game_print_data(Game* game) {
  if(game == NULL) return;
  int i = 0;

  printf("\n\n-------------\n\n");

  printf("=> Spaces: \n");
  for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++) {
    space_print(game->spaces[i]);
  }

  for (i = 0; i < MAX_OBJECTS && game->objects[i] != NULL; i++) {
    object_print(game->objects[i]);
  }

  player_print(game->player);
  printf("prompt:> ");
}

BOOL game_is_over(Game* game) {
  return FALSE;
}

/**
   Callbacks implementation for each action
*/

STATUS game_callback_unknown(Game* game) {
  return ERROR;
}

STATUS game_callback_exit(Game* game) {
  return OK;
}

STATUS game_callback_next(Game* game) {
  if(game == NULL) return ERROR;
  int i = 0;
  Id current_id = NO_ID;
  Id space_id = NO_ID;

  space_id = player_get_location(game_get_player(game));
  if (space_id == NO_ID) {
    return ERROR;
  }

  for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++) {
    current_id = space_get_id(game->spaces[i]);
    if (current_id == space_id) {
      current_id = space_get_south(game->spaces[i]);
      if (current_id != NO_ID) {
         player_set_location(game->player, current_id);
         return OK;
      }
      return ERROR;
    }
  }
  return ERROR;
}

STATUS game_callback_back(Game* game) {
  if(game == NULL) return ERROR;
  int i = 0;
  Id current_id = NO_ID;
  Id space_id = NO_ID;

  space_id = player_get_location(game_get_player(game));

  if (NO_ID == space_id) {
    return ERROR;
  }

  for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++) {
    current_id = space_get_id(game->spaces[i]);
    if (current_id == space_id) {
      current_id = space_get_north(game->spaces[i]);
      if (current_id != NO_ID) {
        player_set_location(game->player, current_id);
        return OK;
      }
      return ERROR;
    }
  }
  return ERROR;
}

STATUS game_callback_right(Game* game){
  if(game == NULL) return ERROR;
  int i = 0;
  Id current_id = NO_ID;
  Id space_id = NO_ID;

  space_id = player_get_location(game_get_player(game));
  if (space_id == NO_ID) {
    return ERROR;
  }

  for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++) {
    current_id = space_get_id(game->spaces[i]);
    if (current_id == space_id) {
      current_id = space_get_east(game->spaces[i]);
      if (current_id != NO_ID) {
         player_set_location(game->player, current_id);
         return OK;
      }
      return ERROR;
    }
  }
  return ERROR;
}

STATUS game_callback_left(Game* game){
  if(game == NULL) return ERROR;
  int i = 0;
  Id current_id = NO_ID;
  Id space_id = NO_ID;

  space_id = player_get_location(game_get_player(game));
  if (space_id == NO_ID) {
    return ERROR;
  }

  for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++) {
    current_id = space_get_id(game->spaces[i]);
    if (current_id == space_id) {
      current_id = space_get_west(game->spaces[i]);
      if (current_id != NO_ID) {
         player_set_location(game->player, current_id);
         return OK;
      }
      return ERROR;
    }
  }
  return ERROR;
}

STATUS game_callback_take(Game* game){
  if(game == NULL) return ERROR;

  Id obj_id = NO_ID;
  Space* space_act = NULL;
  Object* obj = NULL;
  char name[WORD_SIZE + 1];
  int i = 0;

  /* Scan the next string to get the name of the object, if none return ERROR*/
  if(scanf("%s", name) < 1) {
    return ERROR;
  }

  if(player_get_object(game_get_player(game)) != NO_ID) {
    return ERROR;
  }

  /*We obtain the space where the player is*/
  space_act = game_get_space(game, player_get_location(game_get_player(game)));

  while((obj_id = space_get_object(space_act, i++)) != NO_ID) {
    obj = game_get_object(game, obj_id);
    if(obj == NULL) {
      return ERROR;
    }

    if(strcmp(object_get_name(obj), name) == 0) {
      player_set_object(game_get_player(game), obj_id);
      space_delete_object(space_act, obj_id);
      return OK;
    }
  }
  return ERROR;
}

STATUS game_callback_drop(Game* game){
  if(game == NULL) return ERROR;

  Id obj_id = NO_ID;
  Id space_id = NO_ID;

  /*We obtain the id of the space where the player is*/
  space_id = player_get_location(game_get_player(game));

  /*We obtain the id of the object*/
  obj_id = player_get_object(game_get_player(game));
  if(obj_id == NO_ID) return ERROR;

  /*We set the object in the space*/
  space_add_object(game_get_space(game, space_id), obj_id);

  /*We remove the object from the player*/
  player_set_object(game_get_player(game), NO_ID);

  return OK;
}

STATUS game_callback_roll(Game* game) {
  if(game == NULL) return ERROR;
  die_roll(game_get_die(game));
  return OK;
}
