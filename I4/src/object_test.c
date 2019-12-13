/**
 * @brief It tests object module
 *
 * @file space_test.c
 * @author Profesores Pprog
 * @version 2.0
 * @date 16-01-2015
 * @updated 19-01-2016
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "object.h"
#include "object_test.h"
#include "test.h"

#define MAX_TESTS 19

/**
 * @brief Funcion principal de pruebas para el modulo Object.
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
        printf("Running all test for module Object:\n");
    } else {
        test = atoi(argv[1]);
        all = 0;
        printf("Running test %d:\t", test);
	if (test < 1 && test > MAX_TESTS) {
	  printf("Error: unknown test %d\t", test);
	  exit(EXIT_SUCCESS);
        }
    }


    if (all || test == 1) test_object_create();
    if (all || test == 2) test_object_set_name();
    if (all || test == 3) test_object_set_description();
    if (all || test == 4) test_object_set_moved_description();
    if (all || test == 5) test_object_set_movable();
    if (all || test == 6) test_object_set_moved();
    if (all || test == 7) test_object_set_hidden();
    if (all || test == 8) test_object_set_illuminate();
    if (all || test == 9) test_object_set_turnedon();
    if (all || test == 10) test_object_set_open();
    if (all || test == 11) test_object_get_id();
    if (all || test == 12) test_object_get_name();
    if (all || test == 13) test_object_get_description();
    if (all || test == 14) test_object_get_open();
    if (all || test == 15) test_object_get_movable();
    if (all || test == 16) test_object_get_moved();
    if (all || test == 17) test_object_get_hidden();
    if (all || test == 18) test_object_get_illuminate();
    if (all || test == 19)test_object_get_turnedon();

    PRINT_PASSED_PERCENTAGE;

    return 1;
}

void test_object_create() {
  int result = (object_create(5)!=NULL);
  PRINT_TEST_RESULT(result);
}

void test_object_set_name() {
  Object *o;
  o = object_create(5);
  PRINT_TEST_RESULT(object_set_name(o, "hola") == OK);
}

void test_object_set_description() {
  Object *o;
  o = object_create(5);
  PRINT_TEST_RESULT(object_set_descritpion(o, "hola") == OK);
}

void test_object_set_moved_description() {
  Object *o;
  o = object_create(5);
  PRINT_TEST_RESULT(object_set_moved_descritpion(o, "moved") == OK);
}

void test_object_set_movable(){
  Object *o;
  o = object_create(5);
  PRINT_TEST_RESULT(object_set_movable(o, TRUE) == OK);
}

void test_object_set_moved(){
  Object *o;
  o = object_create(5);
  PRINT_TEST_RESULT(object_set_moved(o, TRUE) == OK);
}

void test_object_set_hidden(){
  Object *o;
  o = object_create(5);
  PRINT_TEST_RESULT(object_set_hidden(o, TRUE) == OK);
}

void test_object_set_illuminate(){
  Object *o;
  o = object_create(5);
  PRINT_TEST_RESULT(object_set_illuminate(o, TRUE) == OK);
}

void test_object_set_turnedon() {
  Object *o;
  o = object_create(5);
  PRINT_TEST_RESULT(object_set_turnedon(o, TRUE) == OK);
}

void test_object_set_open(){
  Object *o;
  o = object_create(5);
  PRINT_TEST_RESULT(object_set_open(o, 12) == OK);
}

void test_object_get_id() {
  Object *o;
  o = object_create(5);
  PRINT_TEST_RESULT(object_get_id(o) == 5);
}

void test_object_get_name() {
    Object *o;
    o = object_create(5);
    player_set_name(o, "hola");
    PRINT_TEST_RESULT(strcmp(object_get_name(o), "hola") == 0);
}

void test_object_get_description(){
  Object *o;
  o = object_create(5);
  player_set_description(o, "desc");
  PRINT_TEST_RESULT(strcmp(object_get_description(o), "desc") == 0);
}

void test_object_get_open(){
  Object *o;
  o = object_create(5);
  object_set_open(o, 12);
  PRINT_TEST_RESULT(object_get_open(o) == 12);
}

void test_object_get_movable() {
  Object *o;
  o = object_create(5);
  object_set_movable(o, FALSE);
  PRINT_TEST_RESULT(object_get_movable(o) == FALSE);
}

void test_object_get_moved() {
  Object *o;
  o = object_create(5);
  object_set_moved(o, FALSE);
  PRINT_TEST_RESULT(object_get_moved(o) == FALSE);
}

void test_object_get_hidden() {
  Object *o;
  o = object_create(5);
  object_set_hidden(o, FALSE);
  PRINT_TEST_RESULT(object_get_hidden(o) == FALSE);
}

void test_object_get_illuminate() {
  Object *o;
  o = object_create(5);
  object_set_illuminate(o, FALSE);
  PRINT_TEST_RESULT(object_get_illuminate(o) == FALSE);
}

void test_object_get_turnedon(){
  Object *o;
  o = object_create(5);
  object_set_turnedon(o, FALSE);
  PRINT_TEST_RESULT(object_get_turnedon(o) == FALSE);
}
