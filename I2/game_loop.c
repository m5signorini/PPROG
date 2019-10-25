/**
 * @brief It defines the game loop
 *
 * @file game_loop.c
 * @author Martin Sanchez Signorini
 * @version 1.1
 * @date 08-10-2019
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graphic_engine.h"
#include "game_reader.h"

int main(int argc, char *argv[]) {
  Game* game = NULL;
  T_Command command = NO_CMD;
  Graphic_engine *gengine;
  FILE *pf = NULL;
  char log_file[50];

  if (argc < 4) {
    fprintf(stderr, "%s <game_data_file> -l <log_file>\n", argv[0]);
    return EXIT_FAILURE;
  }

  if (strcmp(argv[2], "-l") != 0){
    fprintf(stderr, "%s <game_data_file> -l <log_file>\n", argv[0]);
    return EXIT_FAILURE;
  }
  strcpy(log_file, argv[3]);

  pf = fopen(log_file, "w");

  if(pf == NULL){
  return EXIT_FAILURE;
  }
  game = game_reader_create_from_file(argv[1]);
  if (game == NULL) {
    fprintf(stderr, "Error while initializing game.\n"); return 1;
  }

  if ((gengine = graphic_engine_create()) == NULL) {
    fprintf(stderr, "Error while initializing graphic engine.\n");
    game_destroy(game); return 1;
  }

  while ( (command != EXIT) && !game_is_over(game) ) {
    graphic_engine_paint_game(gengine, game);
    command = get_user_input();
    if(command == NEXT){
      fprintf(pf, "next: OK\n");
    }
    if(command == BACK){
      fprintf(pf, "back: OK\n");
    }
    game_update(game, command);
  }


  game_destroy(game);
  graphic_engine_destroy(gengine);

  fclose(pf);
  return 0;
}
