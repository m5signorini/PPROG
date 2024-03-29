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

#define N_CALLBACK 11
#define MAX_OBJECTS 50
#define MAX_LINKS 4*(MAX_SPACES + 1)

struct _Game {
  Object* objects[MAX_OBJECTS + 1];   /*!< Array with the memory directions of the objects*/
  Player* player;   /*!< Memory direction of the player*/
  Space* spaces[MAX_SPACES + 1];    /*!< Array with the memory directions of the spaces*/
  Link* links[MAX_LINKS + 1];    /*!< Array with the memory directions of the links*/
  Die* die;    /*!< Memory direction of the die of the game*/
  T_Command last_cmd;     /*!< Last command of the game*/
  STATUS last_cmd_stat;   /*!< Result of the last command of the game*/
  char description[MAX_DESC + 1];   /*!< Description of the last thing inspected*/
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
STATUS game_callback_move(Game* game);
STATUS game_callback_take(Game* game);
STATUS game_callback_drop(Game* game);
STATUS game_callback_roll(Game* game);
STATUS game_callback_inspect(Game* game);

static callback_fn game_callback_fn_list[N_CALLBACK]={
  game_callback_unknown,
  game_callback_exit,
  game_callback_next,
  game_callback_back,
  game_callback_right,
  game_callback_left,
  game_callback_move,
  game_callback_take,
  game_callback_drop,
  game_callback_roll,
  game_callback_inspect
};


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

  for (i = 0; i < MAX_LINKS; i++) {
    game->links[i] = NULL;
  }

  game->player = NULL;
  game->last_cmd = NO_CMD;
  game->die = NULL;
  game->last_cmd_stat = OK;

  memset(game->description, 0, MAX_DESC + 1);

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

  for (i = 0; (i < MAX_LINKS) && (game->links[i] != NULL); i++) {
    link_destroy(game->links[i]);
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

char* game_get_description(Game*game) {
  if (game == NULL) return NULL;

  return game->description;
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
    while((idaux = space_get_object_at(game->spaces[i], j++)) != NO_ID) {
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
Link Management
*/

STATUS game_add_link(Game* game, Link* link) {
  if (game == NULL || link == NULL) {
    return ERROR;
  }

  int i = 0;

  while ( (i < MAX_LINKS) && (game->links[i] != NULL)){
    i++;
  }

  if (i >= MAX_LINKS) {
    return ERROR;
  }

  game->links[i] = link;

  return OK;
}

Id game_get_link_id_at(Game* game, int position) {
  if (game == NULL || position < 0 || position >= MAX_LINKS) {
    return NO_ID;
  }

  return link_get_id(game->links[position]);
}

Link* game_get_link(Game* game, Id id) {
  if(game == NULL) return NULL;
  int i = 0;

  if (id == NO_ID) {
    return NULL;
  }

  for (i = 0; i < MAX_LINKS && game->links[i] != NULL; i++) {
    if (id == link_get_id(game->links[i])){
      return game->links[i];
    }
  }
  return NULL;
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
  if(game == NULL) return NO_CMD;
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
  if(game == NULL) {
    return ERROR;
  }

  return player_set_location(game->player, link_get_to(game_get_link(game, space_get_south(game_get_space(game, player_get_location(game->player)))), player_get_location(game_get_player(game))));
}

STATUS game_callback_back(Game* game) {
  if(game == NULL) {
    return ERROR;
  }

  return player_set_location(game->player, link_get_to(game_get_link(game, space_get_north(game_get_space(game, player_get_location(game->player)))), player_get_location(game_get_player(game))));
}

STATUS game_callback_right(Game* game){
  if(game == NULL) {
    return ERROR;
  }

  return player_set_location(game->player, link_get_to(game_get_link(game, space_get_east(game_get_space(game, player_get_location(game->player)))), player_get_location(game_get_player(game))));
}

STATUS game_callback_left(Game* game){
  if(game == NULL) {
    return ERROR;
  }

  return player_set_location(game->player, link_get_to(game_get_link(game, space_get_west(game_get_space(game, player_get_location(game->player)))), player_get_location(game_get_player(game))));
}

STATUS game_callback_move(Game* game) {
  char direction[WORD_SIZE + 1];

  if (!game) {
    return ERROR;
  }

  if(scanf("%s", direction) < 1) {
    return ERROR;
  }

  if (strcmp(direction, "north") == 0 || strcmp(direction, "n") == 0) {
    return game_callback_back(game);
  }
  else if (strcmp(direction, "south") == 0 || strcmp(direction, "s") == 0) {
    return game_callback_next(game);
  }
  else if (strcmp(direction, "east") == 0 || strcmp(direction, "e") == 0) {
    return game_callback_right(game);
  }
  else if (strcmp(direction, "west") == 0 || strcmp(direction, "w") == 0) {
    return game_callback_left(game);
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

  if(player_inventory_get_max(game_get_player(game)) == player_get_number_objects(game_get_player(game))) {
    return ERROR;
  }

  /*We obtain the space where the player is*/
  space_act = game_get_space(game, player_get_location(game_get_player(game)));

  while((obj_id = space_get_object_at(space_act, i++)) != NO_ID) {
    obj = game_get_object(game, obj_id);
    if(obj == NULL) {
      return ERROR;
    }

    if(strcmp(object_get_name(obj), name) == 0) {
      player_add_object(game_get_player(game), obj_id);
      space_delete_object(space_act, obj_id);
      return OK;
    }
  }
  return ERROR;
}

STATUS game_callback_drop(Game* game){
  if(game == NULL) return ERROR;

  Object *obj = NULL;
  Space* space_act = NULL;
  Id obj_id = NO_ID;
  Id space_id = NO_ID;
  char name[WORD_SIZE + 1];
  int i = 0;

  if(scanf("%s", name) < 1) {
    return ERROR;
  }

  /*We obtain the id of the space where the player is*/
  space_id = player_get_location(game_get_player(game));
  space_act = game_get_space(game, space_id);

  while((obj_id = player_get_object_at(game_get_player(game), i++)) != NO_ID) {
    obj = game_get_object(game, obj_id);
    if(obj == NULL) {
      return ERROR;
    }

    if(strcmp(object_get_name(obj), name) == 0) {
      player_delete_object(game_get_player(game), obj_id);
      space_add_object(space_act, obj_id);
      return OK;
    }
  }
  return ERROR;
}

STATUS game_callback_roll(Game* game) {
  if(game == NULL) return ERROR;
  die_roll(game_get_die(game));
  return OK;
}

STATUS game_callback_inspect(Game* game){
  if (game == NULL) {
    return ERROR;
  }

  Id obj_id = NO_ID;
  Space* space_act = NULL;
  Object* obj = NULL;
  char name[WORD_SIZE + 1];
  int i = 0;

  /* Scan the next string to get the name of the object, if none return ERROR*/
  if(scanf("%s", name) < 1) {
    return ERROR;
  }

  if(strcmp(name, "space") == 0 || strcmp(name, "s") == 0){
    space_act = game_get_space(game, player_get_location(game_get_player(game)));
    strcpy( game->description, space_get_description(space_act));
    return OK;
  }
  else {
    while((obj_id = player_get_object_at(game->player, i++)) != NO_ID) {
       obj = game_get_object(game, obj_id);
       if (strcmp(object_get_name(obj), name) == 0){
         strcpy(game->description, object_get_description(obj));
         return OK;
       }
     }
     i = 0;
     while((obj_id = space_get_object_at(game_get_space(game, player_get_location(game->player)), i++)) != NO_ID) {
       obj = game_get_object(game, obj_id);
       if (strcmp(object_get_name(obj), name) == 0){
         strcpy(game->description, object_get_description(obj));
         return OK;
       }
     }
   }
   return ERROR;
}
