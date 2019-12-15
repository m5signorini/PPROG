/**
 * @brief Test for inventory module
 *
 * @file inventory_test.c
 * @author Cesar Ramirez
 * @version 1.1
 * @date 08-11-2019
 * @copyright GNU Public License
 */
#include <stdio.h>
#include <stdlib.h>
#include "inventory.h"
#include "test.h"
#include "inventory_test.h"

#define MAX_TESTS 10

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
        printf("Running all test for module Inventory:\n");
    } else {
        test = atoi(argv[1]);
        all = 0;
        printf("Running test %d:\t", test);
	if (test < 1 && test > MAX_TESTS) {
	  printf("Error: unknown test %d\t", test);
	  exit(EXIT_SUCCESS);
        }
    }


    if (all || test == 1) test_inventory_create();
    if (all || test == 2) test_inventory_print();
    if (all || test == 3) test_inventory_add_id();
    if (all || test == 4) test_inventory_destroy();
    if (all || test == 5) test_inventory_has_object();
    if (all || test == 6) test_inventory_set_max();
    if (all || test == 7) test_inventory_get_max();
    if (all || test == 8) test_inventory_delete_id();
    if (all || test == 9) test_inventory_get_id_at();
    if (all || test == 10) test_inventory_get_number_of_objects();


    PRINT_PASSED_PERCENTAGE;

    return 1;
}

void test_inventory_create() {
  Inventory* inventory;

  inventory = inventory_create();

  PRINT_TEST_RESULT(inventory !=NULL);
}

void test_inventory_print() {
  Inventory* inventory;
  inventory = inventory_create();

  PRINT_TEST_RESULT(inventory_print(inventory) == OK);
}

void test_inventory_add_id(){
  Inventory* inventory;
  inventory = inventory_create();

  PRINT_TEST_RESULT(inventory_add_id(inventory, 1) == OK);
}

void test_inventory_destroy() {
  Inventory* inventory;
  inventory = inventory_create();
  PRINT_TEST_RESULT(inventory_destroy(inventory) == OK);
}

void test_inventory_has_object() {
  Inventory* inventory;
  inventory = inventory_create();
  inventory_add_id(inventory, 1);
  PRINT_TEST_RESULT(inventory_has_object(inventory, 1) == TRUE);
}

void test_inventory_set_max() {
  Inventory* inventory;
  inventory = inventory_create();
  PRINT_TEST_RESULT(inventory_set_max(inventory, 5) == OK);
}

void test_inventory_get_max() {
  Inventory* inventory;
  inventory = inventory_create();
  inventory_set_max(inventory, 5);
  PRINT_TEST_RESULT(inventory_get_max(inventory) == 5);
}

void test_inventory_delete_id() {
  Inventory* inventory;
  inventory = inventory_create();
  inventory_set_max(inventory, 5);
  inventory_add_id(inventory, 5);
  PRINT_TEST_RESULT(inventory_delete_id(inventory, 5) == OK);
}

void test_inventory_get_id_at() {
  Inventory* inventory;
  inventory = inventory_create();
  inventory_set_max(inventory, 5);
  inventory_add_id(inventory, 5);
  PRINT_TEST_RESULT(inventory_get_id_at(inventory, 0) == 5);
}

void test_inventory_get_number_of_objects() {
  Inventory* inventory;
  inventory = inventory_create();
  inventory_set_max(inventory, 5);
  inventory_add_id(inventory, 5);
  inventory_add_id(inventory, 3);
  PRINT_TEST_RESULT(inventory_get_number_of_objects(inventory) == 2);
}
