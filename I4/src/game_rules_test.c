/**
* @brief It tests game_rules module
*
* @file game_rules_test.c
* @author Cesar Ramirez
* @version 2.0
* @date 12-12-2019
* @copyright GNU Public License
*/

#include <stdio.h>
#include <stdlib.h>
#include "game_rules_test.h"
#include "test.h"
#include "game_rules.h"
#include "game.h"

#define MAX_TESTS 7

/**
* @brief Funcion principal de pruebas para el modulo Game Rules.
*
* Dos modos de ejecucion:
*   1.-Si se ejecuta sin parametros se ejecutan todas las pruebas
*   2.-Si se ejecuta con un numero entre 1 y el numero de pruebas solo ejecuta
*      la prueba indicada
*
*/
int main(int argc, char** argv) {

  int test = 0;
  int all = 1;

  if (argc < 2) {
    printf("Running all test for module Game Rules:\n");
  } else {
    test = atoi(argv[1]);
    all = 0;
    printf("Running test %d:\t", test);
    if (test < 1 && test > MAX_TESTS) {
      printf("Error: unknown test %d\t", test);
      exit(EXIT_SUCCESS);
    }
  }


  if (all || test == 1) test_game_rules_create();
  if (all || test == 2) test_game_rules_dark();
  if (all || test == 3) test_game_rules_clopen_links();
  if (all || test == 4) test_game_rules_hide_objects();
  if (all || test == 5) test_game_rules_rotation();
  if (all || test == 6) test_game_rules_teleport();
  if (all || test == 7) test_game_rules_drop_objects();

  PRINT_PASSED_PERCENTAGE;

  return 1;
}


void test_game_rules_create() {
  Game* game = game_create();
  int result = (game_rules_create(game)!=NULL);
  PRINT_TEST_RESULT(result);
}

void test_game_rules_dark() {
  Game* game = game_create();
  GameRules* game_rules = game_rules_create(game);
  PRINT_TEST_RESULT(game_rules_dark(game_rules) == OK);
}

void test_game_rules_clopen_links() {
  Game* game = game_create();
  GameRules* game_rules = game_rules_create(game);
  PRINT_TEST_RESULT(game_rules_clopen_links(game_rules) == OK);
}

void test_game_rules_hide_objects() {
  Game* game = game_create();
  GameRules* game_rules = game_rules_create(game);
  PRINT_TEST_RESULT(game_rules_hide_objects(game_rules) == OK);
}

void test_game_rules_rotation() {
  Game* game = game_create();
  GameRules* game_rules = game_rules_create(game);
  PRINT_TEST_RESULT(game_rules_rotation(game_rules) == OK);
}

void test_game_rules_teleport() {
  Game* game = game_create();
  Space* s1 = space_create(1);
  Space* s2 = space_create(2);
  Player* p = player_create(1);
  game_set_player(game,p);
  game_add_space(game,s1);
  game_add_space(game,s2);
  GameRules* game_rules = game_rules_create(game);
  PRINT_TEST_RESULT(game_rules_teleport(game_rules) == OK);
}

void test_game_rules_drop_objects() {
  Game* game = game_create();
  GameRules* game_rules = game_rules_create(game);
  PRINT_TEST_RESULT(game_rules_drop_objects(game_rules) == OK);
}
