/**
 * @brief Test for dialogue module
 *
 * @file dialogue_test.c
 * @author Gonzalo Martín
 * @version 1.1
 * @date 13-12-2019
 */
#include <stdio.h>
#include "dialogue.h"

#define MAX_TESTS 13

/**
 * @brief Funcion principal de pruebas para el modulo Space.
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
        printf("Running all test for module Dialogue:\n");
    } else {
        test = atoi(argv[1]);
        all = 0;
        printf("Running test %d:\t", test);
	if (test < 1 && test > MAX_TESTS) {
	  printf("Error: unknown test %d\t", test);
	  exit(EXIT_SUCCESS);
        }
    }


    if (all || test == 1) test_dialogue_create();
    if (all || test == 2) test_dialogue_destroy();
    if (all || test == 3) test_dialogue_set_last_cmd();
    if (all || test == 4) test_dialogue_set_last_status();
    if (all || test == 5) test_dialogue_set_direction();
    if (all || test == 6) test_dialogue_set_feedback();
    if (all || test == 7) test_dialogue_set_description();
    if (all || test == 8) test_dialogue_get_last_cmd();
    if (all || test == 9) test_dialogue_get_last_status();
    if (all || test == 10) test_dialogue_get_direction();
    if (all || test == 11) test_dialogue_get_feedback();
    if (all || test == 12) test_dialogue_get_description();
    if (all || test == 13) test_dialogue_produce();


    PRINT_PASSED_PERCENTAGE;

    return 1;
}

void test_dialogue_create() {
  dialogue = dialogue_create();

  PRINT_TEST_RESULT(link !=NULL);
}

void test_dialogue_destroy() {
  dialogue = dialogue_create();

  PRINT_TEST_RESULT(dialogue_destroy(dialogue) == OK);
}

void test_dialogue_set_last_cmd() {
  dialogue = dialogue_create();

  PRINT_TEST_RESULT(dialogue_set_last_cmd(dialogue, NEXT) == OK);
}

void test_dialogue_set_last_status() {
  dialogue = dialogue_create();

  PRINT_TEST_RESULT(dialogue_set_last_status(dialogue, OK) == OK);
}

void test_dialogue_set_direction() {
  dialogue = dialogue_create();

  PRINT_TEST_RESULT(dialogue_set_direction(dialogue, N) == OK);
}

void test_dialogue_set_feedback() {
  dialogue = dialogue_create();

  PRINT_TEST_RESULT(dialogue_set_feedback(dialogue, "Hello") == OK);
}

void test_dialogue_set_description() {
  dialogue = dialogue_create();

  PRINT_TEST_RESULT(dialogue_set_description(dialogue, "Description") == OK);
}

void test_dialogue_get_last_cmd() {
  dialogue = dialogue_create();
  dialogue_set_last_cmd(dialogue, NEXT);

  PRINT_TEST_RESULT(dialogue_get_last_cmd(dialogue) == NEXT);
}

void test_dialogue_get_last_status() {
  dialogue = dialogue_create();
  dialogue_set_last_status(dialogue, OK);

  PRINT_TEST_RESULT(dialogue_get_last_status(dialogue) == OK);
}

void test_dialogue_get_direction() {
  dialogue = dialogue_create();
  dialogue_set_direction(dialogue, N);

  PRINT_TEST_RESULT(dialogue_get_direction(dialogue) == N);
}

void test_dialogue_get_feedback() {
  dialogue = dialogue_create();
  dialogue_set_feedback(dialogue, "Hello");

  PRINT_TEST_RESULT(strcmp(dialogue_get_feedback(dialogue), "Hello")==0);
}

void test_dialogue_get_description() {
  dialogue = dialogue_create();
  dialogue_set_description(dialogue, "Description");

  PRINT_TEST_RESULT(strcmp(dialogue_get_description(dialogue), "Description")==0);
}

void test_dialogue_produce() {
  dialogue = dialogue_create();
  dialogue_set_last_status(dialogue, OK);
  dialogue_set_last_cmd(dialogue, NEXT);

  PRINT_TEST_RESULT(dialogue_produce(TURNON, OK, dialogue) == OK);
}
