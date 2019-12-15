/**
 * @brief It tests game module
 *
 * @file game_test.c
 * @author Gonzalo Martín
 * @version 2.0
 * @date 12-12-2019
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "player.h"
#include "die.h"
#include "space.h"
#include "object.h"
#include "game_test.h"
#include "game.h"
#include "test.h"

#define MAX_TESTS 18

/**
 * @brief Funcion principal de pruebas para el modulo Player.
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
        printf("Running all test for module Game:\n");
    } else {
        test = atoi(argv[1]);
        all = 0;
        printf("Running test %d:\t", test);
	if (test < 1 && test > MAX_TESTS) {
	  printf("Error: unknown test %d\t", test);
	  exit(EXIT_SUCCESS);
        }
    }


    if (all || test == 1) test_game_create();
    if (all || test == 2) test_game_update();
    if (all || test == 3) test_game_add_space();
    if (all || test == 4) test_game_get_space();
    if (all || test == 5) test_game_get_space_id_at();
    if (all || test == 6) test_game_get_space_at();
    if (all || test == 7) test_game_set_player();
    if (all || test == 8) test_game_get_player();
    if (all || test == 9) test_game_add_object();
    if (all || test == 9) test_game_get_object();
    if (all || test == 10) test_game_get_object_id_at();
    if (all || test == 11) test_game_get_object_at();
    if (all || test == 12) test_game_get_object_location();
    if (all || test == 13) test_game_set_die();
    if (all || test == 14) test_game_get_die();
    if (all || test == 15) test_game_add_link();
    if (all || test == 16) test_game_get_link();
    if (all || test == 17) test_game_get_link_id_at();
    if (all || test == 18) test_game_get_link_at();

    PRINT_PASSED_PERCENTAGE;

    return 1;
}

void test_game_create() {
  int result = game_create()!=NULL ;
  PRINT_TEST_RESULT(result);
}

void test_game_update() {
    Game *g;
    T_Command command = TURNON;
    g = game_create();
    PRINT_TEST_RESULT(game_update(g, command) == OK);
}

void test_game_add_space() {
  Space* s;
  Game *g;
  g = game_create();
  s = space_create(5);
  PRINT_TEST_RESULT(game_add_space(g, s) == OK);
}

void test_game_get_space() {
  Space* s;
  Game *g;
  g = game_create();
  s = space_create(5);
  game_add_space(g, s);
  PRINT_TEST_RESULT(game_get_space(g, 0) == s);
}

void test_game_get_space_id_at() {
  Space* s;
  Game *g;
  g = game_create();
  s = space_create(5);
  game_add_space(g, s);
  PRINT_TEST_RESULT(game_get_space_id_at(g, 0) == 5);
}

void test_game_get_space_at() {
  Space* s;
  Game *g;
  g = game_create();
  s = space_create(5);
  game_add_space(g, s);
  PRINT_TEST_RESULT(game_get_space_at(g, 0) == s);
}

void test_game_set_player() {
  Player* p;
  Game *g;
  g = game_create();
  p = player_create(1);
  PRINT_TEST_RESULT(game_set_player(g, p) == OK);
}

void test_game_get_player() {
  Player* p;
  Game *g;
  g = game_create();
  p = player_create(1);
  game_set_player(g, p);
  PRINT_TEST_RESULT(game_get_player(g) == p);
}

void test_game_add_object() {
  Game *g;
  Object *o;
  g = game_create();
  o = object_create(1);
  PRINT_TEST_RESULT(game_add_object(g, o) == OK);
}

void test_game_get_object_id_at() {
  Game *g;
  Object *o;
  g = game_create();
  o = object_create(1);
  game_add_object(g, o);
  PRINT_TEST_RESULT(game_get_object_id_at(g, 0) == 1);
}

void test_game_get_object_at() {
  Game *g;
  Object *o;
  g = game_create();
  o = object_create(1);
  game_add_object(g, o);
  PRINT_TEST_RESULT(game_get_object_at(g, 0) == o);
}

void test_game_get_object_location() {
  Game *g;
  Object *o;
  g = game_create();
  o = object_create(1);
  game_add_object(g, o);
  PRINT_TEST_RESULT(game_get_object_location(g, 1) == 0);
}

void test_game_set_die() {
  Game *g;
  Die *d;
  g = game_create();
  d = die_create(1, 1 ,6);
  PRINT_TEST_RESULT(game_set_die(g, d) == OK);
}

void test_game_get_die(){
  Game *g;
  Die *d;
  g = game_create();
  d = die_create(1, 1 ,6);
  game_set_die(g, d);
  PRINT_TEST_RESULT(game_get_die(g) == d);
}

void test_game_add_link() {
  Game *g;
  Link *l;
  g = game_create();
  l = link_create(1);
  PRINT_TEST_RESULT(game_add_link(g, l) ==  OK);
}

void test_game_get_link() {
  Game *g;
  Link *l;
  g = game_create();
  l = link_create(1);
  game_add_link(g, l);
  PRINT_TEST_RESULT(game_get_link(g, 1) ==  l);
}

void test_game_get_link_id_at() {
  Game *g;
  Link *l;
  g = game_create();
  l = link_create(1);
  game_add_link(g, l);
  PRINT_TEST_RESULT(game_get_link_id_at(g, 0) ==  1);
}

void test_game_get_link_at() {
  Game *g;
  Link *l;
  g = game_create();
  l = link_create(1);
  game_add_link(g, l);
  PRINT_TEST_RESULT(game_get_link_at(g, 0) ==  l);
}
