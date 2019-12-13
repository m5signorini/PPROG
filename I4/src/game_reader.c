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
* @brief Loads the players from a file to the game
*
* game_reader_load_players Given a file, it loads its data as players and adds them
* to the game
*
* @date 25/10/2019
* @author: Martin Sanchez Signorini
*
* @param game the game that will have its players loaded
* @param filename the name of the file from which we will load the players
* @return the status of the function for error management
*/
STATUS game_reader_load_players(Game* game, char* filename);

/**
* @brief Loads the links between spaces from a file to the game
*
* game_reader_load_links Given a file, it loads its data as links and adds them
* to the game
*
* @date 19/09/2019
* @author: Félix Estaún
*
* @param game the game that will have its links loaded
* @param filename the name of the file from which we will load the links
* @return the status of the function for error management
*/
STATUS game_reader_load_links(Game* game, char* filename);

/**
Public functions
*/

Game* game_reader_create_from_file(char* filename) {
  if(filename == NULL) return NULL;

  Game* game = NULL;
  Die* die = NULL;

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

  if (game_reader_load_players(game, filename) == ERROR) {
    game_destroy(game);
    return NULL;
  }

  if (game_reader_load_links(game, filename) == ERROR) {
    game_destroy(game);
    return NULL;
  }

  die = die_create(1, 1, 6);
  if(die == NULL) {
    game_destroy(game);
    return NULL;
  }

  game_set_die(game, die);

  return game;
}

/**
  Private Functions
*/

STATUS game_reader_load_spaces(Game* game, char* filename) {
  FILE* file = NULL;
  char line[WORD_SIZE] = "";
  char name[WORD_SIZE] = "";
  char desc[MAX_DESC + 1] = "";
  char ldesc[MAX_DESC + 1] = "";
  char* toks = NULL;
  Id id = NO_ID, north = NO_ID, east = NO_ID, south = NO_ID, west = NO_ID;
  Space* space = NULL;
  STATUS status = OK;
  char img[IMG_NUM][IMG_SIZE];
  int i = 0, j;
  BOOL illuminate = TRUE;

  memset(img, 0, IMG_NUM*IMG_SIZE);
  memset(desc, 0, MAX_DESC + 1);
  memset(ldesc, 0, MAX_DESC + 1);


  if (!filename) {
    return ERROR;
  }

  file = fopen(filename, "r");
  if (file == NULL) {
    return ERROR;
  }

  while (fgets(line, WORD_SIZE, file)) {
    if (strncmp("#s:", line, 3) == 0) {
      memset(desc, ' ', 1);
      memset(ldesc, ' ', 1);
      for (j=0; j<IMG_NUM; j++) {
        memset(img[j], ' ', IMG_SIZE-1);
      }

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
      if(toks != NULL) {
        illuminate = (BOOL)atol(toks);
      }
      for(i = 0; i < IMG_NUM; i++) {
        toks = strtok(NULL, "|");
        if(toks != NULL && strchr(toks, '\n') == NULL) {
          strncpy(img[i], toks, IMG_SIZE-1);
        }
      }
      toks = strtok(NULL, "|");
      if(toks != NULL && strcmp(toks, "\r\n") != 0) {
        strncpy(desc, toks, MAX_DESC);
      }

      #ifdef DEBUG
      printf("Leido: %ld|%s|%ld|%ld|%ld|%ld|%s|", id, name, north, east, south, west, desc);
      for(i = 0; i < IMG_NUM; i++) {
        printf("%s|", img[i]);
      }
      printf("\n");
      #endif
      space = space_create(id);
      if (space != NULL) {
        space_set_name(space, name);
        space_set_north(space, north);
        space_set_east(space, east);
        space_set_south(space, south);
        space_set_west(space, west);
        for(i=0; i < IMG_NUM; i++) {
          space_set_image(space, img[i], i);
        }
        space_set_description(space, desc);
        space_set_illuminated(space, illuminate);
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
  char desc[MAX_DESC+1] = "";
  char* toks = NULL;
  STATUS status = OK;
  Id id = NO_ID;
  Id pos_ini = NO_ID;
  Id open = NO_ID;
  BOOL movable = FALSE;
  BOOL hidden = FALSE;
  BOOL illuminate = FALSE;
  Object* obj = NULL;

  memset(desc, 0, MAX_DESC+1);

  if (filename == NULL) {
    return ERROR;
  }

  file = fopen(filename, "r");
  if (file == NULL) {
    return ERROR;
  }

  while (fgets(line, WORD_SIZE, file)) {
    if (strncmp("#o:", line, 3) == 0) {
      memset(desc, ' ', 1);
      toks = strtok(line + 3, "|");
      id = atol(toks);
      toks = strtok(NULL, "|");
      strcpy(name, toks);
      toks = strtok(NULL, "|");
      pos_ini = atol(toks);
      toks = strtok(NULL, "|");
      strcpy(desc, toks);
      toks = strtok(NULL, "|");
      if(toks != NULL) {
        open = atol(toks);
      }
      toks = strtok(NULL, "|");
      if(toks != NULL) {
        movable = (BOOL)atol(toks);
      }
      toks = strtok(NULL, "|");
      if(toks != NULL) {
        hidden = (BOOL)atol(toks);
      }
      toks = strtok(NULL, "|");
      if(toks != NULL) {
        illuminate = (BOOL)atol(toks);
      }
      #ifdef DEBUG
      printf("Leido: %ld|%s|%ld|%s|%ld|%d|%d|%d|\n", id, name, pos_ini, desc, open, movable, hidden, illuminate);
      #endif
      obj = object_create(id);
      if(obj != NULL) {
        if(object_set_name(obj, name) == ERROR) {
          object_destroy(obj);
          return ERROR;
        }
        if(object_set_description(obj, desc) == ERROR) {
          object_destroy(obj);
          return ERROR;
        }
        if(object_set_open(obj, open) == ERROR) {
          object_destroy(obj);
          return ERROR;
        }
        if(object_set_movable(obj, movable) == ERROR) {
          object_destroy(obj);
          return ERROR;
        }
        if(object_set_hidden(obj, hidden) == ERROR) {
          object_destroy(obj);
          return ERROR;
        }
        if(object_set_illuminate(obj, illuminate) == ERROR) {
          object_destroy(obj);
          return ERROR;
        }
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

STATUS game_reader_load_players(Game* game, char* filename) {
  FILE* file = NULL;
  char line[WORD_SIZE] = "";
  char name[WORD_SIZE] = "";
  char* toks = NULL;
  STATUS status = OK;
  Id id = NO_ID;
  Id pos_ini = NO_ID;
  int inv_max = 0;
  Player* player = NULL;

  if (filename == NULL) {
    return ERROR;
  }

  file = fopen(filename, "r");
  if (file == NULL) {
    return ERROR;
  }

  while (fgets(line, WORD_SIZE, file)) {
    if (strncmp("#p:", line, 3) == 0) {
      toks = strtok(line + 3, "|");
      id = atol(toks);
      toks = strtok(NULL, "|");
      strcpy(name, toks);
      toks = strtok(NULL, "|");
      pos_ini = atol(toks);
      toks = strtok(NULL, "|");
      inv_max = atol(toks);
      #ifdef DEBUG
      printf("Leido: %ld|%s|%ld|%d\n", id, name, pos_ini, inv_max);
      #endif
      player = player_create(id);
      if (player != NULL) {
        if(player_set_name(player, name) == ERROR) {
          player_destroy(player);
          return ERROR;
        }
        if(player_inventory_set_max(player, inv_max) == ERROR) {
          player_destroy(player);
          return ERROR;
        }
        if(player_set_location(player, pos_ini) == ERROR) {
          player_destroy(player);
          return ERROR;
        }
        game_set_player(game, player);
      }
    }
  }

  if (ferror(file)) {
    status = ERROR;
  }

  fclose(file);

  return status;
}

STATUS game_reader_load_links(Game* game, char* filename) {
  FILE* file = NULL;
  char line[WORD_SIZE] = "";
  char name[WORD_SIZE] = "";
  char* toks = NULL;
  Id id = NO_ID, space1 = NO_ID, space2 = NO_ID;
  BOOL open = FALSE;
  Link* link = NULL;
  STATUS status = OK;

  if (!filename) {
    return ERROR;
  }

  file = fopen(filename, "r");
  if (file == NULL) {
    return ERROR;
  }

  while (fgets(line, WORD_SIZE, file)) {
    if (strncmp("#l:", line, 3) == 0) {
      toks = strtok(line + 3, "|");
      id = atol(toks);
      toks = strtok(NULL, "|");
      strcpy(name, toks);
      toks = strtok(NULL, "|");
      space1 = atol(toks);
      toks = strtok(NULL, "|");
      space2 = atol(toks);
      toks = strtok(NULL, "|");
      if (atoi(toks)==1) {
        open = FALSE;
      }
      else if (atoi(toks)==0) {
        open = TRUE;
      }
      else {
        fclose(file);
        return ERROR;
      }

      #ifdef DEBUG
      printf("Leido: %ld|%s|%ld|%ld|%s\n", id, name, space1, space2, toks);
      #endif
      link = link_create(id);
      if (link != NULL) {
        link_set_name(link, name);
        link_set_space1(link, space1);
        link_set_space2(link, space2);
        link_set_open(link, open);
        game_add_link(game, link);
      }
    }
  }

  if (ferror(file)) {
    status = ERROR;
  }

  fclose(file);

  return status;
}
