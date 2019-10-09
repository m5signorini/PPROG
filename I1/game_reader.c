/**
 * @brief It defines the game reader for reading data
 *
 * @file game_reader.c
 * @author Martin Sanchez Signorini
 * @version 1.0
 * @date 19-09-2019
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
* @author: Instructors
*
* @param game the game that will have its spaces loaded
* @param filename the name of the file from which we will load the spaces
* @return the status of the function for error management
*/
STATUS game_reader_load_spaces(Game* game, char* filename);



/**
    Public functions
*/

Game* game_reader_create_from_file(char* filename) {
  if(filename == NULL) return NULL;

  Game* game = NULL;
  Player* player = NULL;
  Object* object = NULL;
  Id space_ini = NO_ID;

  game = game_create();
  if (game == NULL)
    return NULL;


  if (game_reader_load_spaces(game, filename) == ERROR) {
    game_destroy(game);
    return NULL;
  }

  player = player_create(1);
  if(player == NULL) {
    game_destroy(game);
    return NULL;
  }

  object = object_create(1);
  if(object == NULL) {
    player_destroy(player);
    game_destroy(game);
    return NULL;
  }

  space_ini = game_get_space_id_at(game, 0);
  
  /*Obtenida la id del espacio inicial, colocamos el objeto en ese espacio*/
  space_set_object(game_get_space(game,space_ini), object_get_id(object));
  /*Obtenida la id del espacio inicial, colocamos al jugador en ese espacio*/
  player_set_location(player,space_ini);
  
  game_set_player(game, player);
  game_set_object(game, object);
  
  return game;
}

STATUS game_reader_load_spaces(Game* game, char* filename) {
  FILE* file = NULL;
  char line[WORD_SIZE] = "";
  char name[WORD_SIZE] = "";
  char* toks = NULL;
  Id id = NO_ID, north = NO_ID, east = NO_ID, south = NO_ID, west = NO_ID;
  Space* space = NULL;
  STATUS status = OK;

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
      #ifdef DEBUG
      printf("Leido: %ld|%s|%ld|%ld|%ld|%ld\n", id, name, north, east, south, west);
      #endif
      space = space_create(id);
      if (space != NULL) {
        space_set_name(space, name);
        space_set_north(space, north);
        space_set_east(space, east);
        space_set_south(space, south);
        space_set_west(space, west);
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
