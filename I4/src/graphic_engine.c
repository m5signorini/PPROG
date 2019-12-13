/**
 * @brief It implements the graphic_engine
 *
 * @file graphic_engine.c
 * @author Martin Sanchez Signorini
 * @version 3.0
 * @date 30-10-2019
 * @copyright GNU Public License
 */

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "screen.h"
#include "graphic_engine.h"

#define MAX_LINE IMG_SIZE+3
/* Max length of the str temporal variable*/
#define STR_LEN 255

struct _Graphic_engine{
  Area *map, *descript, *banner, *help, *feedback;
};

/**
  Private Functions Prototypes
*/

/**
* @brief Displays the game objects
*
* graphic_engine_paint_objects prints on the screen the objects locations of the game
*
* @date 19/09/2019
* @author: Martin Sanchez Signorini
*
* @param ge the graphic engine
* @param game the game that the graphic engine is going to use
*/
void graphic_engine_paint_objects(Graphic_engine *ge, Game *game);

/**
* @brief Gets the string of objects in a space
*
* graphic_engine_get_object_str sets the obj_str to the objects in a space
* inserting up to MAX_LINE characters
*
* @date 25/10/2019
* @author: Martin Sanchez Signorini
*
* @param game the game that the graphic engine is going to use
* @param space_id the id of the space
* @param obj_str string of min size MAX_LINE that will store the objects names
* @return the status of the function for error management
*/
STATUS graphic_engine_get_object_str(Game* game, Id space_id, char* obj_str);

STATUS graphic_engine_paint_bot_border(Graphic_engine* ge);
STATUS graphic_engine_paint_visuals(Graphic_engine* ge, Space* space, char* obj);

/**
* @brief Displays the side links
*
* graphic_engine_paint_side_links prints on the screen the side links of the spaces of the game
*
* @date 19/09/2019
* @author: Martin Sanchez Signorini
*
* @param ge the graphic engine
* @param game the game that the graphic engine is going to use
* @param space the space the the function will paint its side links
* @param id_act to check if the space is where the player is located
* @return the status of the function for error management
*/
STATUS graphic_engine_paint_side_links(Game* game, Graphic_engine* ge, Space* space, Id id_act);

/**
* @brief Displays the top links
*
* graphic_engine_paint_top_link prints on the screen the upper link of the spaces of the game
*
* @date 19/09/2019
* @author: Martin Sanchez Signorini
*
* @param ge the graphic engine
* @param game the game that the graphic engine is going to use
* @param space the space the the function will paint its upper link
* @return the status of the function for error management
*/
STATUS graphic_engine_paint_top_link(Game* game, Graphic_engine* ge, Space* space);

/**
* @brief Displays the bottom links
*
* graphic_engine_paint_bot_link prints on the screen the bottom link of the spaces of the game
*
* @date 19/09/2019
* @author: Martin Sanchez Signorini
*
* @param ge the graphic engine
* @param game the game that the graphic engine is going to use
* @param space the space the the function will paint its bottom link
* @return the status of the function for error management
*/
STATUS graphic_engine_paint_bot_link(Game* game, Graphic_engine* ge, Space* space);
/**
  Public Functions
*/


Graphic_engine *graphic_engine_create(){
  static Graphic_engine *ge = NULL;

  if (ge)
    return ge;

  screen_init();
  ge = (Graphic_engine *) malloc(sizeof(Graphic_engine));

  ge->map      = screen_area_init( 1, 1, 48, 21);
  ge->descript = screen_area_init(50, 1, 29, 21);
  ge->banner   = screen_area_init(28,23, 23,  1);
  ge->help     = screen_area_init( 1,24, 78,  2);
  ge->feedback = screen_area_init( 1,27, 78,  3);

  return ge;
}

void graphic_engine_destroy(Graphic_engine *ge){
  if (!ge)
    return;

  screen_area_destroy(ge->map);
  screen_area_destroy(ge->descript);
  screen_area_destroy(ge->banner);
  screen_area_destroy(ge->help);
  screen_area_destroy(ge->feedback);

  screen_destroy();
  free(ge);
}

void graphic_engine_paint_game(Graphic_engine *ge, Game *game){
  Id id_act = NO_ID;
  Id id_back = NO_ID;
  Id id_next = NO_ID;

  Space* space_act = NULL;
  Space* space_back = NULL;
  Space* space_next = NULL;
  char obj[MAX_LINE+1];
  char str[STR_LEN];
  char tmp[STR_LEN];
  T_Command last_cmd = UNKNOWN;
  extern char *cmd_to_str[];
  extern char *short_cmd_to_str[];
  int i;


  /* Paint the in the map area */
  screen_area_clear(ge->map);
  /* Set id_act to the id of the space of the player */
  if ((id_act = player_get_location(game_get_player(game))) != NO_ID){
    space_act = game_get_space(game, id_act);
    id_back = link_get_to(game_get_link(game, space_get_north(space_act)), id_act);
    id_next = link_get_to(game_get_link(game, space_get_south(space_act)), id_act);
    space_back = game_get_space(game, id_back);
    space_next = game_get_space(game, id_next);


    if (id_back != NO_ID) {
      if(graphic_engine_get_object_str(game, id_back, obj) == ERROR) {
        return;
      }
      graphic_engine_paint_side_links(game, ge, space_back, id_act);
      graphic_engine_paint_visuals(ge, space_back, obj);
      graphic_engine_paint_bot_border(ge);
    }

    if (id_act != NO_ID) {
      if(graphic_engine_get_object_str(game, id_act, obj) == ERROR) {
        return;
      }
      graphic_engine_paint_top_link(game, ge, space_act);
      graphic_engine_paint_side_links(game, ge, space_act, id_act);
      graphic_engine_paint_visuals(ge, space_act, obj);
      graphic_engine_paint_bot_border(ge);
      graphic_engine_paint_bot_link(game, ge, space_act);
    }

    if (id_next != NO_ID) {
      if(graphic_engine_get_object_str(game, id_next, obj) == ERROR) {
        return;
      }
      graphic_engine_paint_side_links(game, ge, space_next, id_act);
      graphic_engine_paint_visuals(ge, space_next, obj);
    }
  }

  /* Paint the objects locations in the description area */
  graphic_engine_paint_objects(ge, game);

  /* Paint the in the banner area */
  screen_area_puts(ge->banner, " The game of the Goose ");

  /* Paint the in the help area */
  screen_area_clear(ge->help);
  sprintf(str, " The commands you can use are:");
  screen_area_puts(ge->help, str);
  sprintf(str, "    ");
  for(i = 2; i < N_CMD; i++) {
    if(i > 2) {
      strcat(str, ", ");
    }
    sprintf(tmp, "%s or %s", cmd_to_str[i], short_cmd_to_str[i]);
    strcat(str, tmp);
  }
  screen_area_puts(ge->help, str);

  /* Paint in the feedback area */
  last_cmd = game_get_last_command(game);
  sprintf(str, " %s:", cmd_to_str[last_cmd-NO_CMD]);
  if(game_get_last_command_stat(game) == OK) {
    strcat(str, "OK");
  }
  else {
    strcat(str, "ERROR");
  }
  screen_area_puts(ge->feedback, str);

  /* Dump to the terminal */
  screen_paint();
  printf("prompt:> ");
}


/**
  Private Functions
*/
STATUS graphic_engine_paint_visuals(Graphic_engine* ge, Space* space, char* obj) {
  int i, j;
  char str[STR_LEN];

  if(space_get_illuminated(space) != FALSE) {
    /* Space Image */
    for(i=0; i < IMG_NUM; i++) {
      sprintf(str, "        |  %s  |", space_get_image(space, i));
      screen_area_puts(ge->map, str);
    }
    /* Objects */
    sprintf(str, "        |%s|",obj);
    screen_area_puts(ge->map, str);
    return OK;
  }
  else {
    /* Dark Space */
    for(i=0; i < IMG_NUM+1; i++) {
      sprintf(str, "        |**");
      for(j=0; j < IMG_SIZE; j++) {
        strcat(str, "*");
      }
      strcat(str, "**|");
      screen_area_puts(ge->map, str);
    }
    return OK;
  }
  return ERROR;
}

void graphic_engine_paint_objects(Graphic_engine *ge, Game *game) {
  Id obj_id = NO_ID;
  Id obj_loc = NO_ID;
  char str[STR_LEN];
  int i = 0;

  /* Clear description area and start list of items*/
  screen_area_clear(ge->descript);
  sprintf(str, "  Object locations:");
  screen_area_puts(ge->descript, str);


  /* obj_id is the id of the object at index i */
  /* obj_loc is the location (space id) of the object i*/

  while((obj_id = game_get_object_id_at(game, i++)) != NO_ID) {
    obj_loc = game_get_object_location(game, obj_id);

    /* If the object is in a space */
    if(obj_loc != NO_ID) {
      sprintf(str, "    %s:%d", object_get_name(game_get_object(game, obj_id)),(int)obj_loc);
      screen_area_puts(ge->descript, str);
    }
  }

  /* Line jump */
  screen_area_puts(ge->descript, " ");

  /* Player object*/
  sprintf(str, "  %s Objects:", player_get_name(game_get_player(game)));
  screen_area_puts(ge->descript, str);

  i = 0;
  while((obj_id = player_get_object_at(game_get_player(game), i++)) != NO_ID) {
    sprintf(str, "    %s", object_get_name(game_get_object(game, obj_id)));
    screen_area_puts(ge->descript, str);
  }

  /* Line jump */
  screen_area_puts(ge->descript, " ");

  /* Print the last die */
  sprintf(str, "  Last die value: %d", die_get_last(game_get_die(game)));
  screen_area_puts(ge->descript, str);

  /* Print description */
  sprintf(str, "  Descriptions:");
  screen_area_puts(ge->descript, str);
  sprintf(str, "  %s", game_get_description(game));
  screen_area_puts(ge->descript, str);
}

STATUS graphic_engine_paint_bot_border(Graphic_engine* ge) {
  if(ge == NULL) return ERROR;
  char str[STR_LEN] = "      ";
  int i;

  strcat(str, "  +");
  for(i=0; i < IMG_SIZE + 3; i++) {
    strcat(str, "-");
  }
  strcat(str, "+  ");
  screen_area_puts(ge->map, str);

  return OK;
}

STATUS graphic_engine_paint_side_links(Game* game, Graphic_engine* ge, Space* space, Id id_act)  {
  if(space == NULL) return ERROR;
  Id link_id = NO_ID;
  Id space_id = NO_ID;
  char str[STR_LEN];
  char temp[STR_LEN];
  char aux[STR_LEN];
  int i;
  memset(str, 0, STR_LEN);

  /* PRINT - LINK */
  if((link_id = space_get_west(space)) != NO_ID) {
    sprintf(temp, "    %2d", (int)link_id);
    strcat(str, temp);
  }
  else {
    sprintf(temp, "      ");
    strcat(str, temp);
  }

  strcat(str, "  +");
  for(i=0; i < IMG_SIZE + 3; i++) {
    strcat(str, "-");
  }
  strcat(str, "+  ");

  if((link_id = space_get_east(space)) != NO_ID) {
    sprintf(temp, "%2d", (int)link_id);
    strcat(str, temp);
  }
  screen_area_puts(ge->map, str);

  /* PRINT ARROWS - SPACE */
  memset(str, 0 , STR_LEN);
  if((space_id = link_get_to(game_get_link(game, space_get_west(space)), space_get_id(space))) != NO_ID) {
    sprintf(temp, " %2d <--", (int)space_id);
    strcat(str, temp);
  }
  else {
    sprintf(temp, "       ");
    strcat(str, temp);
  }

  /* Print space depending if the player is in there */
  if(space_get_id(space) == id_act) {
    sprintf(temp, " |8D");
    for(i=0; i < IMG_SIZE-1; i++) {
      strcat(temp, " ");
    }
    sprintf(aux, "%2d| ",(int) space_get_id(space));
    strcat(str, temp);
    strcat(str, aux);
  }
  else {
    sprintf(temp, " |  ");
    for(i=0; i < IMG_SIZE-1; i++) {
      strcat(temp, " ");
    }
    sprintf(aux, "%2d| ",(int) space_get_id(space));
    strcat(str, temp);
    strcat(str, aux);
  }

  if((space_id = link_get_to(game_get_link(game, space_get_east(space)), space_get_id(space))) != NO_ID) {
    sprintf(temp, " --> %2d", (int)space_id);
    strcat(str, temp);
  }

  screen_area_puts(ge->map, str);
  return OK;
}

STATUS graphic_engine_paint_top_link(Game* game, Graphic_engine* ge, Space* space) {
  if(space == NULL) return ERROR;
  Id link_id = NO_ID;
  char str[STR_LEN] = "    ";
  char temp[STR_LEN];
  int i;

  if((link_id = space_get_north(space)) != NO_ID) {
    for(i = 0; i<IMG_SIZE; i++) {
      strcat(str, " ");
    }
    sprintf(temp, "^ %d", (int)link_id);
    strcat(str, temp);
  }

  screen_area_puts(ge->map, str);
  return OK;
}

STATUS graphic_engine_paint_bot_link(Game* game, Graphic_engine* ge, Space* space) {
  if(space == NULL) return ERROR;
  Id link_id = NO_ID;
  char str[STR_LEN] = "    ";
  char temp[STR_LEN];
  int i;

  if((link_id = space_get_south(space)) != NO_ID) {
    for(i = 0; i<IMG_SIZE; i++) {
      strcat(str, " ");
    }
    sprintf(temp, "v %d", (int)link_id);
    strcat(str, temp);
  }

  screen_area_puts(ge->map, str);
  return OK;
}

STATUS graphic_engine_get_object_str(Game *game, Id space_id, char* obj_str) {
  if(game == NULL || space_id == NO_ID || obj_str == NULL) return ERROR;
  /* k is the number of non-null chars that can be in obj_str which size must be at least MAX_LINE + 1*/
  int k = MAX_LINE;
  int i = 0;
  Id obj_id = NO_ID;
  Object *obj = NULL;
  Space *space = NULL;

  memset(obj_str, 0, MAX_LINE+1);

  space = game_get_space(game, space_id);
  if(space == NULL) return ERROR;

  /* While there is objects in the space and enough space in the string */
  while ((obj_id = space_get_object_at(space, i++)) != NO_ID && k > 0) {
    /* Add a comma if there are at least 2 objects*/
    if(i > 1) {
      strcat(obj_str, ",");
      k--;
    }

    obj = game_get_object(game, obj_id);
    if(obj == NULL || object_get_name(obj) == NULL) return ERROR;

    /* Concat the name to the string up to k chars and remove its length from k */
    strncat(obj_str, object_get_name(obj), k);
    k -= strlen(object_get_name(obj));
  }

  /* We put spaces after the objects while there is enough space in the string*/
  while(k > 0) {
    obj_str[MAX_LINE - k] = ' ';
    k--;
  }

  /* Null terminate for the string */
  obj_str[MAX_LINE] = '\0';

  return OK;
}
