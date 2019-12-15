/**
 * @brief It tests set module
 *
 * @file set_test.c
 * @author Cesar Ramirez
 * @version 2.0
 * @date 12-12-2019
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include "set.h"
#include "set_test.h"
#include "test.h"

#define MAX_TESTS 6

/**
 * @brief Funcion principal de pruebas para el modulo Set.
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
        printf("Running all test for module Set:\n");
    } else {
        test = atoi(argv[1]);
        all = 0;
        printf("Running test %d:\t", test);
	if (test < 1 && test > MAX_TESTS) {
	  printf("Error: unknown test %d\t", test);
	  exit(EXIT_SUCCESS);
        }
    }


    if (all || test == 1) test_set_create();
    if (all || test == 2) test_set_add_id();
    if (all || test == 3) test_set_has_id();
    if (all || test == 4) test_set_delete_id();
    if (all || test == 5) test_set_get_number_elements();
    if (all || test == 6) test_set_get_id_at();

    PRINT_PASSED_PERCENTAGE;

    return 1;
}


void test_set_create() {
  int result = (set_create()!=NULL);
  PRINT_TEST_RESULT(result);
}

void test_set_add_id() {
  Set* s;
  s = set_create();
  PRINT_TEST_RESULT(set_add_id(s, 3) == OK);
}

void test_set_has_id() {
  Set *s;
  s = set_create();
  set_add_id(s, 3);
  PRINT_TEST_RESULT(set_has_id(s, 3) == 0);
}

void test_set_delete_id() {
  Set *s;
  s = set_create();
  set_add_id(s, 3);
  PRINT_TEST_RESULT(set_delete_id(s, 3) == OK);
}

void test_set_get_number_elements() {
  Set *s;
  s = set_create();
  set_add_id(s, 3);
  set_add_id(s, 2);
  PRINT_TEST_RESULT(set_get_number_elements(s) == 2);
}

void test_set_get_id_at() {
  Set *s;
  s = set_create();
  set_add_id(s, 3);
  PRINT_TEST_RESULT(set_get_id_at(s, 0) == 3);
}
