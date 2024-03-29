/**
 * @brief It implements the game interface and all the associated callbacks
 * for each command
 *
 * @file game.c
 * @author Martin Sanchez Signorini
 * @version 2.0
 * @date 03-08-2019
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"


#define N_CALLBACK 6

struct _Game {
  Object* object;
  Player* player;
  Space* spaces[MAX_SPACES + 1];
  T_Command last_cmd;
};

/**
   Define the function type for the callbacks
*/
typedef void (*callback_fn)(Game* game);

/**
   List of callbacks for each command in the game
*/
void game_callback_unknown(Game* game);
void game_callback_exit(Game* game);
void game_callback_next(Game* game);
void game_callback_back(Game* game);
void game_callback_take(Game* game);
void game_callback_leave(Game* game);

static callback_fn game_callback_fn_list[N_CALLBACK]={
  game_callback_unknown,
  game_callback_exit,
  game_callback_next,
  game_callback_back,
  game_callback_take,
  game_callback_leave};


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

  game->player = NULL;
  game->object = NULL;
  game->last_cmd = NO_CMD;

  return game;
}

STATUS game_destroy(Game* game) {
  if (game == NULL) return ERROR;
  int i = 0;
  
  for (i = 0; (i < MAX_SPACES) && (game->spaces[i] != NULL); i++) {
    space_destroy(game->spaces[i]);
  }
  object_destroy(game->object);
  player_destroy(game->player);
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

STATUS game_set_object(Game* game, Object* obj) {
  if (game == NULL || obj == NULL ) {
    return ERROR;
  }
  game->object = obj;
  return OK;
}

Object* game_get_object(Game* game) {
  if(game == NULL) return NULL;
  return game->object;
}

Id game_get_object_location(Game* game) {
  if(game == NULL) return NO_ID;
  int i;

  for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++) {
    if (space_get_object(game->spaces[i])!=NO_ID){
      return space_get_id(game->spaces[i]);
    }
  }

  return NO_ID;
}

/**
  Command Management
*/

STATUS game_update(Game* game, T_Command cmd) {
  if(game == NULL) return ERROR;
  game->last_cmd = cmd;
  (*game_callback_fn_list[cmd])(game);
  return OK;
}

T_Command game_get_last_command(Game* game){
  return game->last_cmd;
}

void game_print_data(Game* game) {
  if(game == NULL) return;
  int i = 0;

  printf("\n\n-------------\n\n");

  printf("=> Spaces: \n");
  for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++) {
    space_print(game->spaces[i]);
  }

  object_print(game->object);
  player_print(game->player);
  printf("prompt:> ");
}

BOOL game_is_over(Game* game) {
  return FALSE;
}

/**
   Callbacks implementation for each action
*/

void game_callback_unknown(Game* game) {
}

void game_callback_exit(Game* game) {
}

void game_callback_next(Game* game) {
  if(game == NULL) return;
  int i = 0;
  Id current_id = NO_ID;
  Id space_id = NO_ID;

  space_id = player_get_location(game_get_player(game));
  if (space_id == NO_ID) {
    return;
  }

  for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++) {
    current_id = space_get_id(game->spaces[i]);
    if (current_id == space_id) {
      current_id = space_get_south(game->spaces[i]);
      if (current_id != NO_ID) {
         player_set_location(game->player, current_id);
      }
      return;
    }
  }
}

void game_callback_back(Game* game) {
  if(game == NULL) return;
  int i = 0;
  Id current_id = NO_ID;
  Id space_id = NO_ID;

  space_id = player_get_location(game_get_player(game));

  if (NO_ID == space_id) {
    return;
  }

  for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++) {
    current_id = space_get_id(game->spaces[i]);
    if (current_id == space_id) {
      current_id = space_get_north(game->spaces[i]);
      if (current_id != NO_ID) {
        player_set_location(game->player, current_id);
      }
      return;
    }
  }
}

void game_callback_take(Game* game){
  if(game == NULL) return;
  Id obj_id = NO_ID;
  Space* space_act = NULL;

  /*We obtain the space where the player is*/
  space_act = game_get_space(game, player_get_location(game_get_player(game)));

  /*We obtain the id of the object in said space*/
  obj_id = space_get_object(space_act);
  if(obj_id == NO_ID) return;
  
  /*We set the object in the player*/
  player_set_object(game_get_player(game), obj_id);

  /*We remove the object from the space*/
  space_set_object(space_act, NO_ID);
}

void game_callback_leave(Game* game){
  if(game == NULL) return;
  Id obj_id = NO_ID;
  Id space_id = NO_ID;

  /*We obtain the id of the space where the player is*/
  space_id = player_get_location(game_get_player(game));

  /*We obtain the id of the object*/
  obj_id = player_get_object(game_get_player(game));
  if(obj_id == NO_ID) return;

  /*We set the object in the space*/
  space_set_object(game_get_space(game, space_id), obj_id);

  /*We remove the object from the player*/
  player_set_object(game_get_player(game), NO_ID);
}
