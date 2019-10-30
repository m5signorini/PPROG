/**
 * @brief It defines the game loop and the log functionality
 *
 * @file game_loop.c
 * @author Cesar Ramirez
 * @version 2.0
 * @date 29-10-2019
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graphic_engine.h"
#include "game_reader.h"

/**
 * @brief Stores the commands executed in the log file
 *
 * game_loop_command writes in the log file the results from each command
 *
 * @date 29/10/2019
 * @author: Cesar Ramirez
 *
 * @param command the executed command
 * @param stat the value of the command (ERROR or OK)
 * @param filename a pointer to the log file
 * @return the status of the function for error management
 */
STATUS game_loop_command(T_Command command, STATUS stat, FILE * filename);

int main(int argc, char * argv[]) {
  Game * game = NULL;
  T_Command command = NO_CMD;
  Graphic_engine * gengine;
  STATUS stat;
  FILE * filename = NULL;

  if (argc < 4) {
    fprintf(stderr, "Error, use : %s <game_data_file> -l <log_file>\n", argv[0]);
    return EXIT_FAILURE;
  }

  if (strcmp(argv[2], "-l") != 0 || argv[3] == NULL) {
    fprintf(stderr, "Error, use : %s <game_data_file> -l <log_file>\n", argv[0]);
    return EXIT_FAILURE;
  }

  filename = fopen(argv[3], "w");
  if (filename == NULL) {
    return EXIT_FAILURE;
  }

  game = game_reader_create_from_file(argv[1]);
  if (game == NULL) {
    fprintf(stderr, "Error while initializing game.\n");
    fclose(filename);
    return EXIT_FAILURE;
  }

  if ((gengine = graphic_engine_create()) == NULL) {
    fprintf(stderr, "Error while initializing graphic engine.\n");
    fclose(filename);
    game_destroy(game);
    return EXIT_FAILURE;
  }

  while ((command != EXIT) && !game_is_over(game)) {
    graphic_engine_paint_game(gengine, game);
    command = get_user_input();
    stat = game_update(game, command);
    if (game_loop_command(command, stat, filename) == ERROR) {
      fprintf(stderr, "Error while writing log file.\n");
      fclose(filename);
      game_destroy(game);
      graphic_engine_destroy(gengine);
      return EXIT_FAILURE;
    }
  }

  game_destroy(game);
  graphic_engine_destroy(gengine);
  fclose(filename);

  return 0;
}

STATUS game_loop_command(T_Command command, STATUS stat, FILE * filename) {
  if (command == NEXT) {
    if (stat == OK) {
      if (fprintf(filename, "next: OK\n") < 0) {
        return ERROR;
      }
    } else {
      if (fprintf(filename, "next: ERROR\n") < 0) {
        return ERROR;
      }
    }
    return OK;
  }
  if (command == BACK) {
    if (stat == OK) {
      if (fprintf(filename, "back: OK\n") < 0) {
        return ERROR;
      }
    } else {
      if (fprintf(filename, "back: ERROR\n") < 0) {
        return ERROR;
      }
    }
    return OK;
  }
  if (command == RIGHT) {
    if (stat == OK) {
      if (fprintf(filename, "right: OK\n") < 0) {
        return ERROR;
      }
    } else {
      if (fprintf(filename, "right: ERROR\n") < 0) {
        return ERROR;
      }
    }
    return OK;
  }
  if (command == LEFT) {
    if (stat == OK) {
      if (fprintf(filename, "left: OK\n") < 0) {
        return ERROR;
      }
    } else {
      if (fprintf(filename, "left: ERROR\n") < 0) {
        return ERROR;
      }
    }
    return OK;
  }
  if (command == TAKE) {
    if (stat == OK) {
      if (fprintf(filename, "take: OK\n") < 0) {
        return ERROR;
      }
    } else {
      if (fprintf(filename, "take: ERROR\n") < 0) {
        return ERROR;
      }
    }
    return OK;
  }
  if (command == DROP) {
    if (stat == OK) {
      if (fprintf(filename, "drop: OK\n") < 0) {
        return ERROR;
      }
    } else {
      if (fprintf(filename, "drop: ERROR\n") < 0) {
        return ERROR;
      }
    }
    return OK;
  }
  if (command == ROLL) {
    if (stat == OK) {
      if (fprintf(filename, "roll: OK\n") < 0) {
        return ERROR;
      }
    } else {
      if (fprintf(filename, "roll: ERROR\n") < 0) {
        return ERROR;
      }
    }
    return OK;
  }
  if (command == UNKNOWM) {
    if (stat == OK) {
      if (fprintf(filename, "unknown: OK\n") < 0) {
        return ERROR;
      }
    } else {
      if (fprintf(filename, "unknown: ERROR\n") < 0) {
        return ERROR;
      }
    }
    return OK;
  }
  return ERROR;
}
