/**
* @brief It defines the game loop
*
* @file game_loop.c
* @author Profesores PPROG
* @version 1.0
* @date 13-01-2015
* @copyright GNU Public License
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graphic_engine.h"
#include "game_management.h"
#include "command.h"

int main(int argc, char *argv[]){
  Game *game = NULL;
  T_Command command = NO_CMD;
  Graphic_engine *gengine;
  FILE* logfile;
  int log_flag = 0;
  STATUS status;
  int i;
  extern char *cmd_to_str[];

  if (argc < 2){
    fprintf(stderr, "Use: %s <game_data_file>\n", argv[0]); return 1;
  }

  if (argc > 2) {
    if (strcmp(argv[2], "-l")!=0 || !argv[3]) {
      fprintf(stderr, "Use: %s <game_data_file> -l <log_file>\n", argv[0]);
      return -1;
    }

    logfile = fopen(argv[3], "w");
    if (!logfile){
      return -1;
    }

    log_flag=1;
  }

  game=game_management_create_from_file(argv[1]);
  if (!game) {
    fprintf(stderr, "Error while initializing game.\n");
    if (log_flag == 1) fclose(logfile);
    return EXIT_FAILURE;
  }
  if ((gengine = graphic_engine_create()) == NULL){
    fprintf(stderr, "Error while initializing graphic engine.\n");
    game_destroy(game);
    if (log_flag == 1) fclose(logfile);
    return EXIT_FAILURE;
  }
  while ( (command != EXIT) && !game_is_over(game) ){
    graphic_engine_paint_game(gengine, game);
    command = command_get_user_input();
    status = game_update(game, command);

    if (log_flag==1) {
      for (i = -1; i < N_CMD; i++) {
        if (i == command) {
          if (status == OK){
            fprintf(logfile, "%s: OK\n", cmd_to_str[i-NO_CMD]);
          }
          else fprintf(logfile, "%s: ERROR\n", cmd_to_str[i-NO_CMD]);
        }
      }
    }
  }

  game_destroy(game);
  graphic_engine_destroy(gengine);
  if (log_flag == 1) fclose(logfile);
  return 0;
}
