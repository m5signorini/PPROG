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

STATUS game_loop_command(T_Command command, STATUS stat, FILE* filename);

int main(int argc, char *argv[]) {
  Game* game = NULL;
  T_Command command = NO_CMD;
  Graphic_engine *gengine;
  STATUS stat;
  FILE *filename = NULL;

   if (argc < 4) {
     fprintf(stderr, "ERROR, USE : %s <game_data_file> -l <log_file>\n", argv[0]);
     return EXIT_FAILURE;
   }

   if (strcmp(argv[2], "-l") != 0 || argv[3] == NULL){
      fprintf(stderr, " ERROR, USE : %s <game_data_file> -l <log_file>\n", argv[0]);
      return EXIT_FAILURE;
   }

   filename = fopen(argv[3], "w");
   if(filename == NULL){
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
    stat = game_update(game, command);
    game_loop_command(command, stat, filename);
  }

  game_destroy(game);
  graphic_engine_destroy(gengine);

  return 0;
}

STATUS game_loop_command(T_Command command, STATUS stat, FILE* filename){
  if(command == NEXT){
    if(stat == OK){
      if(fprintf(filename, "next: OK\n") < 0){
        return ERROR;
      }
    } else{
      if(fprintf(filename, "next: ERROR\n") < 0){
        return ERROR;
      }
    }
    return OK;
  }
  if(command == BACK){
    if(stat == OK){
      if(fprintf(filename, "back: OK\n") < 0){
        return ERROR;
      }
    } else{
      if(fprintf(filename, "back: ERROR\n") < 0){
        return ERROR;
      }
    }
    return OK;
  }
  if(command == RIGHT){
    if(stat == OK){
      if(fprintf(filename, "right: OK\n") < 0){
        return ERROR;
      }
    } else{
      if(fprintf(filename, "right: ERROR\n") < 0){
        return ERROR;
      }
    }
    return OK;
  }
  if(command == LEFT){
    if(stat == OK){
      if(fprintf(filename, "left: OK\n") < 0){
        return ERROR;
      }
    } else{
      if(fprintf(filename, "left: ERROR\n") < 0){
        return ERROR;
      }
    }
    return OK;
  }
  if(command == TAKE){
    if(stat == OK){
      if(fprintf(filename, "take: OK\n") < 0){
        return ERROR;
      }
    } else{
      if(fprintf(filename, "take: ERROR\n") < 0){
        return ERROR;
      }
    }
    return OK;
  }
  if(command == DROP){
    if(stat == OK){
      if(fprintf(filename, "drop: OK\n") < 0){
        return ERROR;
      }
    } else{
      if(fprintf(filename, "drop: ERROR\n") < 0){
        return ERROR;
      }
    }
    return OK;
  }
  if(command == ROLL){
    if(stat == OK){
      if(fprintf(filename, "roll: OK\n") < 0){
        return ERROR;
      }
    } else{
      if(fprintf(filename, "roll: ERROR\n") < 0){
        return ERROR;
      }
    }
    return OK;
  }
return ERROR;
}
