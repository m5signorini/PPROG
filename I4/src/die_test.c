/**
 * @brief Test for die module
 *
 * @file die_test.c
 * @author Martin Sanchez Signorini
 * @version 3.0
 * @date 08-10-2019
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include "die.h"
#include "die_test.h"
#include "test.h"

#define MAX_TESTS 5

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
        printf("Running all test for module Die:\n");
    } else {
        test = atoi(argv[1]);
        all = 0;
        printf("Running test %d:\t", test);
	if (test < 1 && test > MAX_TESTS) {
	  printf("Error: unknown test %d\t", test);
	  exit(EXIT_SUCCESS);
        }
    }


    if (all || test == 1) test_die_create();
    if (all || test == 2) test_die_print();
    if (all || test == 3) test_die_roll();
    if (all || test == 4) test_die_destroy();
    if (all || test == 5) test_die_get_last();


    PRINT_PASSED_PERCENTAGE;

    return 1;
}

void test_die_create() {
  Die* die;
  die = die_create(1, 1, 6);

  PRINT_TEST_RESULT(die !=NULL);
}

void test_die_print() {
  Die* die;
  die = die_create(1, 1, 6);

  PRINT_TEST_RESULT(die_print(die) == OK);
}

void test_die_roll(){
  Die* die;
  die = die_create(1, 1, 6);

  PRINT_TEST_RESULT(die_roll(die) >0 && die_roll(die) <7);
}

void test_die_destroy() {
    Die* die;
    die = die_create(1, 1, 6);
    PRINT_TEST_RESULT(die_destroy(die) == OK);
}

void test_die_get_last() {
    Die* die;
    die = die_create(1, 1, 6);
    die_roll(die);
    PRINT_TEST_RESULT(die_get_last(die) >0 && die_get_last(die) <7);
}
