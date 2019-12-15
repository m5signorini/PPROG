/**
 * @brief It tests player module
 *
 * @file player_test.c
 * @author Gonzalo Martín
 * @version 2.0
 * @date 12-12-2019
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "player.h"
#include "object.h"
#include "player_test.h"
#include "test.h"

#define MAX_TESTS 12

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
        printf("Running all test for module Player:\n");
    } else {
        test = atoi(argv[1]);
        all = 0;
        printf("Running test %d:\t", test);
	if (test < 1 && test > MAX_TESTS) {
	  printf("Error: unknown test %d\t", test);
	  exit(EXIT_SUCCESS);
        }
    }


    if (all || test == 1) test_player_create();
    if (all || test == 2) test_player_set_name();
    if (all || test == 3) test_player_inventory_set_max();
    if (all || test == 4) test_player_set_location();
    if (all || test == 5) test_player_add_object();
    if (all || test == 6) test_player_delete_object();
    if (all || test == 7) test_player_get_name();
    if (all || test == 8) test_player_inventory_get_max();
    if (all || test == 9) test_player_get_location();
    if (all || test == 10) test_player_get_id();
    if (all || test == 11) test_player_get_object_at();
    if (all || test == 12) test_player_get_number_objects();

    PRINT_PASSED_PERCENTAGE;

    return 1;
}

void test_player_create() {
  int result = player_create(5)!=NULL ;
  PRINT_TEST_RESULT(result);
}

void test_player_set_name() {
    Player *p;
    p = player_create(5);
    PRINT_TEST_RESULT(player_set_name(p, "hola") == OK);
}

void test_player_inventory_set_max() {
  Player* p;
  p = player_create(5);
  PRINT_TEST_RESULT(player_inventory_set_max(p, 16));
}

void test_player_set_location() {
    Player *p;
    Id idLocation = 3;
    p = player_create(5);
    PRINT_TEST_RESULT(player_set_location(p, idLocation));
}

void test_player_add_object() {
  Player *p;
  Id idObject = 3;
  p = player_create(5);
  PRINT_TEST_RESULT(player_add_object(p, idObject));
}

void test_player_delete_object(){
  Player *p;
  Id idObject = 3;
  p = player_create(5);
  player_add_object(p, idObject);
  PRINT_TEST_RESULT(player_delete_object(p,idObject));
}

void test_player_get_name() {
    Player *p;
    p = player_create(1);
    player_set_name(p, "adios");
    PRINT_TEST_RESULT(strcmp(player_get_name(p), "adios") == 0);
}

void test_player_inventory_get_max() {
    Player *p = NULL;
    p = player_create(1);
    player_inventory_set_max(p, 9);
    PRINT_TEST_RESULT(player_inventory_get_max(p) == 9);
}

void test_player_get_location() {
    Player *p;
    p = player_create(1);
    player_set_location(p, 7);
    PRINT_TEST_RESULT(player_get_location(p) == 7);
}

void test_player_get_id() {
  Player *p;
  p = player_create(1);
  PRINT_TEST_RESULT(player_get_id(p) == 1);
}

void test_player_get_object_at() {
  Player *p;
  p = player_create(1);
  player_add_object(p, 2);
  PRINT_TEST_RESULT(player_get_object_at(p, 0) == 2);
}

void test_player_get_number_objects() {
  Player *p;
  p = player_create(1);
  player_add_object(p, 2);
  player_add_object(p, 3);
  PRINT_TEST_RESULT(player_get_number_objects(p) == 2);
}
