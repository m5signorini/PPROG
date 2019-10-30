/**
* @brief It defines the game reader for reading data
*
* @file game_reader.c
* @author Martin Sanchez Signorini
* @version 3.0
* @date 30-10-2019
* @copyright GNU Public License
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game_reader.h"


/**
Private Functions Prototypes
*/

/**
* @brief Loads the spaces from a file to the game
*
* game_reader_load_spaces Given a file, it loads its data as spaces and adds them
* to the game
*
* @date 19/09/2019
* @author: Martin Sanchez Signorini
*
* @param game the game that will have its spaces loaded
* @param filename the name of the file from which we will load the spaces
* @return the status of the function for error management
*/
STATUS game_reader_load_spaces(Game* game, char* filename);

/**
* @brief Loads the objects from a file to the game
*
* game_reader_load_objects Given a file, it loads its data as objects and adds them
* to the game
*
* @date 25/10/2019
* @author: Martin Sanchez Signorini
*
* @param game the game that will have its objects loaded
* @param filename the name of the file from which we will load the objects
* @return the status of the function for error management
*/
STATUS game_reader_load_objects(Game* game, char* filename);


/**
Public functions
*/

Game* game_reader_create_from_file(char* filename) {
  if(filename == NULL) return NULL;
  
  Game* game = NULL;
  Player* player = NULL;
  Die* die = NULL;
  Id space_ini = NO_ID;
  
  game = game_create();
  if (game == NULL)
  return NULL;
  
  if (game_reader_load_spaces(game, filename) == ERROR) {
    game_destroy(game);
    return NULL;
  }
  
  if (game_reader_load_objects(game, filename) == ERROR) {
    game_destroy(game);
    return NULL;
  }
  
  player = player_create(1);
  if(player == NULL) {
    game_destroy(game);
    return NULL;
  }
  
  die = die_create(1, 1, 6);
  if(die == NULL) {
    player_destroy(player);
    game_destroy(game);
    return NULL;
  }
  
  space_ini = game_get_space_id_at(game, 0);
  player_set_name(player, "Player 1");
  game_set_die(game, die);
  
  /*Obtained the id of the initial space, we set the player in that space*/
  player_set_location(player,space_ini);
  game_set_player(game, player);
  
  return game;
}

/**
  Private Functions
*/

STATUS game_reader_load_spaces(Game* game, char* filename) {
  FILE* file = NULL;
  char line[WORD_SIZE] = "";
  char name[WORD_SIZE] = "";
  char* toks = NULL;
  Id id = NO_ID, north = NO_ID, east = NO_ID, south = NO_ID, west = NO_ID;
  Space* space = NULL;
  STATUS status = OK;
  char img_up[IMG_SIZE] = "";
  char img_mid[IMG_SIZE] = "";
  char img_down[IMG_SIZE] = "";
  
  if (!filename) {
    return ERROR;
  }
  
  file = fopen(filename, "r");
  if (file == NULL) {
    return ERROR;
  }
  
  while (fgets(line, WORD_SIZE, file)) {
    if (strncmp("#s:", line, 3) == 0) {
      toks = strtok(line + 3, "|");
      id = atol(toks);
      toks = strtok(NULL, "|");
      strcpy(name, toks);
      toks = strtok(NULL, "|");
      north = atol(toks);
      toks = strtok(NULL, "|");
      east = atol(toks);
      toks = strtok(NULL, "|");
      south = atol(toks);
      toks = strtok(NULL, "|");
      west = atol(toks);
      toks = strtok(NULL, "|");
      strncpy(img_up, toks, IMG_SIZE-1);
      toks = strtok(NULL, "|");
      strncpy(img_mid, toks, IMG_SIZE-1);
      toks = strtok(NULL, "|");
      strncpy(img_down, toks, IMG_SIZE-1);
      #ifdef DEBUG
      printf("Leido: %ld|%s|%ld|%ld|%ld|%ld|%s|%s|%s\n", id, name, north, east, south, west, img_up, img_mid, img_down);
      #endif
      space = space_create(id);
      if (space != NULL) {
        space_set_name(space, name);
        space_set_north(space, north);
        space_set_east(space, east);
        space_set_south(space, south);
        space_set_west(space, west);
        space_set_image_up(space, img_up);
        space_set_image_mid(space, img_mid);
        space_set_image_down(space, img_down);
        game_add_space(game, space);
      }
    }
  }
  
  if (ferror(file)) {
    status = ERROR;
  }
  
  fclose(file);
  
  return status;
}


STATUS game_reader_load_objects(Game* game, char*filename) {
  FILE* file = NULL;
  char line[WORD_SIZE] = "";
  char name[WORD_SIZE] = "";
  char* toks = NULL;
  STATUS status = OK;
  Id id = NO_ID;
  Id pos_ini = NO_ID;
  Object* obj = NULL;
  
  if (filename == NULL) {
    return ERROR;
  }
  
  file = fopen(filename, "r");
  if (file == NULL) {
    return ERROR;
  }
  
  while (fgets(line, WORD_SIZE, file)) {
    if (strncmp("#o:", line, 3) == 0) {
      toks = strtok(line + 3, "|");
      id = atol(toks);
      toks = strtok(NULL, "|");
      strcpy(name, toks);
      toks = strtok(NULL, "|");
      pos_ini = atol(toks);
      #ifdef DEBUG
      printf("Leido: %ld|%s|%ld\n", id, name, pos_ini);
      #endif
      obj = object_create(id);
      if (obj != NULL) {
        object_set_name(obj, name);
        if(space_add_object(game_get_space(game, pos_ini), id) == ERROR) {
          object_destroy(obj);
          return ERROR;
        }
        game_add_object(game, obj);
      }
    }
  }
  
  if (ferror(file)) {
    status = ERROR;
  }
  
  fclose(file);
  
  return status;
}
