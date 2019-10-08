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
#include "graphic_engine.h"
#include "game_reader.h"

int main(int argc, char *argv[]) {
  Game* game = NULL;
  T_Command command = NO_CMD;
  Graphic_engine *gengine;

  if (argc < 2) {
    fprintf(stderr, "Use: %s <game_data_file>\n", argv[0]); return 1;
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
    game_update(game, command);
	}

  game_destroy(game);
	graphic_engine_destroy(gengine);

  return 0;
}
