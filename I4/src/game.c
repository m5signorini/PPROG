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

#define N_CALLBACK 18
#define MAX_OBJECTS 50
#define MAX_LINKS 4*(MAX_SPACES + 1)

struct _Game {
  Object* objects[MAX_OBJECTS + 1];   /*!< Array with the memory directions of the objects*/
  Player* player;   /*!< Memory direction of the player*/
  Space* spaces[MAX_SPACES + 1];    /*!< Array with the memory directions of the spaces*/
  Link* links[MAX_LINKS + 1];    /*!< Array with the memory directions of the links*/
  Die* die;    /*!< Memory direction of the die of the game*/
  Dialogue* dialogue;     /*!< Dialogue module of the game*/
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
STATUS game_callback_up(Game* game);
STATUS game_callback_down(Game* game);
STATUS game_callback_move(Game* game);
STATUS game_callback_take(Game* game);
STATUS game_callback_drop(Game* game);
STATUS game_callback_roll(Game* game);
STATUS game_callback_inspect(Game* game);
STATUS game_callback_turnon(Game* game);
STATUS game_callback_turnoff(Game* game);
STATUS game_callback_open(Game* game);
STATUS game_callback_save(Game* game);
STATUS game_callback_load(Game* game);

static callback_fn game_callback_fn_list[N_CALLBACK]={
  game_callback_unknown,
  game_callback_exit,
  game_callback_next,
  game_callback_back,
  game_callback_right,
  game_callback_left,
  game_callback_up,
  game_callback_down,
  game_callback_move,
  game_callback_take,
  game_callback_drop,
  game_callback_roll,
  game_callback_inspect,
  game_callback_turnon,
  game_callback_turnoff
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
  game->dialogue = dialogue_create();
  if(game->dialogue == NULL) {
    game_destroy(game);
    return NULL;
  }

  memset(game->description, 0, MAX_DESC + 1);

  return game;
}

STATUS game_clear(Game* game) {
  if (game == NULL) return ERROR;
  int i = 0;

  for (i = 0; (i < MAX_SPACES) && (game->spaces[i] != NULL); i++) {
    space_destroy(game->spaces[i]);
    game->spaces[i] = NULL;
  }

  for (i = 0; (i < MAX_OBJECTS) && (game->objects[i] != NULL); i++) {
    object_destroy(game->objects[i]);
    game->objects[i] = NULL;
  }

  for (i = 0; (i < MAX_LINKS) && (game->links[i] != NULL); i++) {
    link_destroy(game->links[i]);
    game->links[i] = NULL;
  }
  player_destroy(game->player);
  game->player = NULL;
  die_destroy(game->die);
  game->die = NULL;
  dialogue_destroy(game->dialogue);
  game ->dialogue = NULL;
  return OK;
}


STATUS game_destroy(Game* game) {
  if (!game) {
    return ERROR;
  }

  game_clear(game);
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

Space* game_get_space_at(Game* game, int index){
  if(game == NULL || index < 0 || index > MAX_SPACES) return NULL;

  return game->spaces[index];
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

Object* game_get_object_at(Game* game, int index) {
  if(game == NULL || index < 0 || index > MAX_OBJECTS) return NULL;

  return game->objects[index];
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

Object* game_get_object_by_name(Game* game, char* name, Space* space) {
  if(game == NULL || name == NULL) return NULL;

  Object* obj = NULL;
  int i = 0;

  while(i <= MAX_SPACES && game->objects[i] != NULL) {
    obj = game->objects[i];
    if(strcmp(object_get_name(obj), name) == 0) {
      return obj;
    }
    i++;
  }

  return NULL;
}

Object* game_get_object_by_name_in_player(Game* game, char* name, Player* player) {
  if(game == NULL || name == NULL) return NULL;

  Object* obj = NULL;
  Id obj_id = NO_ID;
  int i = 0;

  /* Get all objects with the player until finding one with the matching name*/
  /* Note this is faster than first finding the object in the game and then checking the player has it*/
  while ((obj_id = player_get_object_at(game->player, i++)) != NO_ID) {
    obj = game_get_object(game, obj_id);
    if(obj == NULL) {
      return ERROR;
    }
    if (strcmp(object_get_name(obj), name) == 0) {
      return obj;
    }
  }

  return NULL;
}

Object* game_get_object_by_name_in_space(Game* game, char* name, Space* space) {
  if(game == NULL || name == NULL) return NULL;

  Object* obj = NULL;
  Id obj_id = NO_ID;
  int i = 0;

  /* Get all objects within the space until finding one with the matching name*/
  while((obj_id = space_get_object_at(space, i++)) != NO_ID) {
    obj = game_get_object(game, obj_id);
    if(obj == NULL) {
      return ERROR;
    }
    if(strcmp(object_get_name(obj), name) == 0) {
      return obj;
    }
  }
  return NULL;
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

Link* game_get_link_at(Game* game, int position) {
  if(game == NULL || position < 0 || position >= MAX_LINKS) return NULL;

  return  game->links[position];
}

/**
Dialogue Management
*/

Dialogue* game_get_dialogue(Game* game) {
  if(game == NULL) return NULL;
  return game->dialogue;
}

/**
Command Management
*/

STATUS game_update(Game* game, T_Command cmd) {
  if(game == NULL) return ERROR;
  game->last_cmd = cmd;
  game->last_cmd_stat = (*game_callback_fn_list[cmd])(game);
  dialogue_produce(game->last_cmd, game->last_cmd_stat, game->dialogue);
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
  Space* space_next = NULL;
  Id player_location = player_get_location(game->player);
  Space* space_act = game_get_space(game, player_location);
  Id link_id = space_get_south(space_act);
  Link* link = game_get_link(game, link_id);
  Id dest = link_get_to(link, player_location);
  if(link_get_open(link) == FALSE) {
    return ERROR;
  }
  space_next = game_get_space(game, dest);
  dialogue_set_direction(game->dialogue, S);
  /*Check if there is still a light source*/
  game_check_light_space(game, space_act);
  game_check_light_space(game, space_next);
  game_check_light_player(game, space_next);
  return player_set_location(game->player, dest);
}

STATUS game_callback_back(Game* game) {
  if(game == NULL) {
    return ERROR;
  }
  Space* space_next = NULL;
  Id player_location = player_get_location(game->player);
  Space* space_act = game_get_space(game, player_location);
  Id link_id = space_get_north(space_act);
  Link* link = game_get_link(game, link_id);
  Id dest = link_get_to(link, player_location);
  if(link_get_open(link) == FALSE) {
    return ERROR;
  }
  space_next = game_get_space(game, dest);
  dialogue_set_direction(game->dialogue, N);
  /*Check if there is still a light source*/
  game_check_light_space(game, space_act);
  game_check_light_space(game, space_next);
  game_check_light_player(game, space_next);
  return player_set_location(game->player, dest);
}

STATUS game_callback_right(Game* game){
  if(game == NULL) {
    return ERROR;
  }
  Space* space_next = NULL;
  Id player_location = player_get_location(game->player);
  Space* space_act = game_get_space(game, player_location);
  Id link_id = space_get_east(space_act);
  Link* link = game_get_link(game, link_id);
  Id dest = link_get_to(link, player_location);
  if(link_get_open(link) == FALSE) {
    return ERROR;
  }
  space_next = game_get_space(game, dest);
  dialogue_set_direction(game->dialogue, E);
  /*Check if there is still a light source*/
  game_check_light_space(game, space_act);
  game_check_light_space(game, space_next);
  game_check_light_player(game, space_next);
  return player_set_location(game->player, dest);
}

STATUS game_callback_left(Game* game){
  if(game == NULL) {
    return ERROR;
  }
  Space* space_next = NULL;
  Id player_location = player_get_location(game->player);
  Space* space_act = game_get_space(game, player_location);
  Id link_id = space_get_west(space_act);
  Link* link = game_get_link(game, link_id);
  Id dest = link_get_to(link, player_location);
  if(link_get_open(link) == FALSE) {
    return ERROR;
  }
  space_next = game_get_space(game, dest);
  dialogue_set_direction(game->dialogue, W);
  /*Check if there is still a light source*/
  game_check_light_space(game, space_act);
  game_check_light_space(game, space_next);
  game_check_light_player(game, space_next);
  return player_set_location(game->player, dest);
  //return player_set_location(game->player, link_get_to(game_get_link(game, space_get_west(game_get_space(game, player_get_location(game->player)))), player_get_location(game_get_player(game))));
}

STATUS game_callback_up(Game* game){
  if(game == NULL) {
    return ERROR;
  }
  Space* space_next = NULL;
  Id player_location = player_get_location(game->player);
  Space* space_act = game_get_space(game, player_location);
  Id link_id = space_get_up(space_act);
  Link* link = game_get_link(game, link_id);
  Id dest = link_get_to(link, player_location);
  if(link_get_open(link) == FALSE) {
    return ERROR;
  }
  space_next = game_get_space(game, dest);
  dialogue_set_direction(game->dialogue, U);
  /*Check if there is still a light source*/
  game_check_light_space(game, space_act);
  game_check_light_space(game, space_next);
  game_check_light_player(game, space_next);
  return player_set_location(game->player, dest);
}

STATUS game_callback_down(Game* game){
  if(game == NULL) {
    return ERROR;
  }
  Space* space_next = NULL;
  Id player_location = player_get_location(game->player);
  Space* space_act = game_get_space(game, player_location);
  Id link_id = space_get_down(space_act);
  Link* link = game_get_link(game, link_id);
  Id dest = link_get_to(link, player_location);
  if(link_get_open(link) == FALSE) {
    return ERROR;
  }
  space_next = game_get_space(game, dest);
  dialogue_set_direction(game->dialogue, D);
  /*Check if there is still a light source*/
  game_check_light_space(game, space_act);
  game_check_light_space(game, space_next);
  game_check_light_player(game, space_next);
  return player_set_location(game->player, dest);
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
  else if (strcmp(direction, "up") == 0 || strcmp(direction, "u") == 0) {
    return game_callback_up(game);
  }
  else if (strcmp(direction, "down") == 0 || strcmp(direction, "d") == 0) {
    return game_callback_down(game);
  }
  return ERROR;
}

STATUS game_callback_take(Game* game){
  if(game == NULL) return ERROR;

  Id obj_id = NO_ID;
  Space* space_act = NULL;
  Object* obj = NULL;
  char name[WORD_SIZE + 1];

  /* Scan the next string to get the name of the object, if none return ERROR*/
  if(scanf("%s", name) < 1) {
    return ERROR;
  }

  if(player_inventory_get_max(game_get_player(game)) == player_get_number_objects(game_get_player(game))) {
    return ERROR;
  }

  /*We obtain the space where the player is*/
  space_act = game_get_space(game, player_get_location(game_get_player(game)));

  /*Look for a matching object in the space*/
  obj = game_get_object_by_name_in_space(game, name, space_act);
  if(obj == NULL) {
    return ERROR;
  }
  obj_id = object_get_id(obj);
  player_add_object(game_get_player(game), obj_id);
  space_delete_object(space_act, obj_id);
  return OK;
}

STATUS game_callback_drop(Game* game){
  if(game == NULL) return ERROR;

  Object *obj = NULL;
  Space* space_act = NULL;
  Id obj_id = NO_ID;
  Id space_id = NO_ID;
  char name[WORD_SIZE + 1];

  if(scanf("%s", name) < 1) {
    return ERROR;
  }

  /*We obtain the id of the space where the player is*/
  space_id = player_get_location(game_get_player(game));
  space_act = game_get_space(game, space_id);

  /*Look for a matching item in the inventory of player*/
  obj = game_get_object_by_name_in_player(game, name, game->player);
  if(obj == NULL) {
    return ERROR;
  }
  obj_id = object_get_id(obj);
  player_delete_object(game_get_player(game), obj_id);
  space_add_object(space_act, obj_id);
  return OK;
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

  Space* space_act = NULL;
  Object* obj = NULL;
  char name[WORD_SIZE + 1];

  /* Scan the next string to get the name of the object, if none return ERROR*/
  if(scanf("%s", name) < 1) {
    return ERROR;
  }
  space_act = game_get_space(game, player_get_location(game_get_player(game)));

  if(strcmp(name, "space") == 0 || strcmp(name, "s") == 0){
    /* Inspect space */
    if (space_get_illuminated(space_act)==FALSE) {
      strcpy(game->description, "\0");
      return OK;
    }
    strcpy(game->description, space_get_description(space_act));
    dialogue_set_description(game->dialogue, space_get_long_description(space_act));
    return OK;
  }
  else {
    /* Inspect object */
    /* Look for matching object in the player */
    obj = game_get_object_by_name_in_player(game, name, game->player);
    if(obj != NULL) {
      /* Object with the player */
      strcpy(game->description, object_get_description(obj));
      return OK;
    }

     /* Look for matching object in the space */
     obj = game_get_object_by_name_in_space(game, name, space_act);
     if(obj != NULL) {
       /* Object in the space */
       if(space_get_illuminated(space_act) == TRUE){
         strcpy(game->description, object_get_description(obj));
         dialogue_set_description(game->dialogue, object_get_description(obj));
         return OK;
       }
       else {
         strcpy(game->description, "It's too dark");
         dialogue_set_description(game->dialogue, "\0");
         return OK;
       }
     }
   }
   return ERROR;
}

STATUS game_callback_turnon(Game* game) {
  char name[WORD_SIZE+1];
  Object *obj = NULL;
  Space *space_act = NULL;

  if (game==NULL) {
    return ERROR;
  }

  /* Scan the next string to get the name of the object, if none return ERROR*/
  if(scanf("%s", name) < 1) {
    return ERROR;
  }

  space_act = game_get_space(game, player_get_location(game_get_player(game)));

  /* Look for object in the player*/
  obj = game_get_object_by_name_in_player(game, name, game->player);
  if(obj != NULL) {
    if (object_get_illuminate(obj)==FALSE) {
      return ERROR;
    }
    object_set_turnedon(obj, TRUE);
    space_set_illuminated(space_act, TRUE);
    return OK;
  }

  /* Look for object in the space */
  obj = game_get_object_by_name_in_space(game, name, space_act);
  if(obj != NULL) {
    if (object_get_illuminate(obj)==FALSE) {
      return ERROR;
    }
    object_set_turnedon(obj, TRUE);
    space_set_illuminated(space_act, TRUE);
    return OK;
  }
  return ERROR;
}

STATUS game_callback_turnoff(Game* game) {
  char name[WORD_SIZE+1];
  Object *obj = NULL;
  Space *space_act = NULL;

  if (game==NULL) {
    return ERROR;
  }

  /* Scan the next string to get the name of the object, if none return ERROR*/
  if(scanf("%s", name) < 1) {
    return ERROR;
  }

  space_act = game_get_space(game, player_get_location(game_get_player(game)));

  /* Look for object in the player*/
  obj = game_get_object_by_name_in_player(game, name, game->player);
  if(obj != NULL) {
    if (object_get_illuminate(obj)==FALSE) {
      return ERROR;
    }
    object_set_turnedon(obj, FALSE);
    /*Check if there is still a light source*/
    game_check_light_space(game, space_act);
    space_set_illuminated(space_act, FALSE);
    return OK;
  }

  /* Look for object in the space */
  obj = game_get_object_by_name_in_space(game, name, space_act);
  if(obj != NULL) {
    if (object_get_illuminate(obj)==FALSE) {
      return ERROR;
    }
    object_set_turnedon(obj, FALSE);
    /*Check if there is still a light source*/
    game_check_light_space(game, space_act);
    space_set_illuminated(space_act, FALSE);
    return OK;
  }
  return ERROR;
}

STATUS game_callback_open(Game* game) {
  char link_name[WORD_SIZE+1];
  char obj_name[WORD_SIZE+1];
  Id link_id = NO_ID;
  Object *obj = NULL;
  Space *space_act = NULL;

  if (game==NULL) {
    return ERROR;
  }

  if(scanf("%s with %s", link_name, obj_name) < 1) {
    return ERROR;
  }

  space_act = game_get_space(game, player_get_location(game->player));

  /* Look for object in the player*/
  obj = game_get_object_by_name_in_player(game, obj_name, game->player);
  if(obj == NULL) {
    return ERROR;
  }

  link_id = space_get_north(space_act);
  if (object_get_open(obj)==link_id && link_id!=NO_ID) {
    link_set_open(game_get_link(game, link_id), TRUE);
    return OK;
  }

  link_id = space_get_south(space_act);
  if (object_get_open(obj)==link_id && link_id!=NO_ID) {
    link_set_open(game_get_link(game, link_id), TRUE);
    return OK;
  }

  link_id = space_get_east(space_act);
  if (object_get_open(obj)==link_id && link_id!=NO_ID) {
    link_set_open(game_get_link(game, link_id), TRUE);
    return OK;
  }

  link_id = space_get_west(space_act);
  if (object_get_open(obj)==link_id && link_id!=NO_ID) {
    link_set_open(game_get_link(game, link_id), TRUE);
    return OK;
  }

  link_id = space_get_up(space_act);
  if (object_get_open(obj)==link_id && link_id!=NO_ID) {
    link_set_open(game_get_link(game, link_id), TRUE);
    return OK;
  }

  link_id = space_get_down(space_act);
  if (object_get_open(obj)==link_id && link_id!=NO_ID) {
    link_set_open(game_get_link(game, link_id), TRUE);
    return OK;
  }

  return ERROR;
}

STATUS game_callback_save(Game* game) {
  char savefile[WORD_SIZE+1];

  if (game==NULL) {
    return ERROR;
  }

  if(scanf("%s", savefile) < 1) {
    return ERROR;
  }

  return game_management_save(game, savefile);
}

STATUS game_callback_load(Game* game) {
  char savefile[WORD_SIZE+1];

  if (game==NULL) {
    return ERROR;
  }

  if(scanf("%s", savefile) < 1) {
    return ERROR;
  }

  game_clear(game);

  game = game_management_load_from_file(game, savefile);

  if (!game) {
    return ERROR;
  }

  return OK;
}

/**/
STATUS game_check_light_space(Game* game, Space* space) {
  if(game == NULL || space == NULL) return ERROR;
  int i = 0;
  Object* obj = NULL;

  while((obj = game_get_object(game, space_get_object_at(space, i++))) != NULL) {
    if(object_get_illuminate(obj) == TRUE && object_get_turnedon(obj) == TRUE) {
      space_set_illuminated(space, TRUE);
      return OK;
    }
  }
  space_set_illuminated(space, FALSE);
  return ERROR;
}

STATUS game_check_light_player(Game* game, Space* space) {
  if(game == NULL || space == NULL) return ERROR;
  int i = 0;
  Object* obj = NULL;

  while((obj = game_get_object(game, player_get_object_at(game->player, i++))) != NULL) {
    if(object_get_illuminate(obj) == TRUE && object_get_turnedon(obj) == TRUE) {
      space_set_illuminated(space, TRUE);
      return OK;
    }
  }
  return ERROR;
}
