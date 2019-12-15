/**
* @brief Test for link module
*
* @file link_test.c
* @author Gonzalo Martín
* @version 1.1
* @date 13-12-2019
*/
#include <stdio.h>
#include <stdlib.h>
#include "link.h"
#include "test.h"
#include "link_test.h"

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
    printf("Running all test for module Link:\n");
  } else {
    test = atoi(argv[1]);
    all = 0;
    printf("Running test %d:\t", test);
    if (test < 1 && test > MAX_TESTS) {
      printf("Error: unknown test %d\t", test);
      exit(EXIT_SUCCESS);
    }
  }


  if (all || test == 1) test_link_create();
  if (all || test == 2) test_link_print();
  if (all || test == 3) test_link_get_id();
  if (all || test == 4) test_link_destroy();
  if (all || test == 5) test_link_set_name();
  if (all || test == 6) test_link_get_name();
  if (all || test == 7) test_link_set_space1();
  if (all || test == 8) test_link_get_space1();
  if (all || test == 9) test_link_set_space2();
  if (all || test == 10) test_link_get_space2();
  if (all || test == 11) test_link_set_open();
  if (all || test == 12) test_link_get_open();
  if (all || test == 13) test_link_get_to();


  PRINT_PASSED_PERCENTAGE;

  return 1;
}

void test_link_create() {
  Link* link;
  link = link_create(1);

  PRINT_TEST_RESULT(link !=NULL);
}

void test_link_print() {
  Link* link;
  link = link_create(1);

  PRINT_TEST_RESULT(link_print(link) == OK);
}

void test_link_get_id(){
  Link* link;
  link = link_create(1);

  PRINT_TEST_RESULT(link_get_id(link) == 1);
}

void test_link_destroy() {
  Link* link;
  link = link_create(1);
  PRINT_TEST_RESULT(link_destroy(link) == OK);
}

void test_link_set_name() {
  Link* link;
  link = link_create(1);
  PRINT_TEST_RESULT(link_set_name(link, "link") == OK);
}

void test_link_get_name() {
  Link* link;
  link = link_create(1);
  link_set_name(link, "link");
  PRINT_TEST_RESULT(link_get_name(link) == "link");
}

void test_link_set_space1() {
  Link* link;
  link = link_create(1);
  PRINT_TEST_RESULT(link_set_space1(link, 1) == OK);
}

void test_link_get_space1() {
  Link* link;
  link = link_create(1);
  link_set_space1(link, 1);
  PRINT_TEST_RESULT(link_get_space1(link) == 1);
}

void test_link_set_space2() {
  Link* link;
  link = link_create(1);
  PRINT_TEST_RESULT(link_set_space2(link, 1) == OK);
}

void test_link_get_space2() {
  Link* link;
  link = link_create(1);
  link_set_space2(link, 1);
  PRINT_TEST_RESULT(link_get_space2(link) == 1);
}

void test_link_set_open() {
  Link* link;
  link = link_create(1);
  PRINT_TEST_RESULT(link_set_open(link, TRUE) == OK);
}

void test_link_get_open() {
  Link* link;
  link = link_create(1);
  link_set_open(link, TRUE);
  PRINT_TEST_RESULT(link_get_open(link) == TRUE);
}

void test_link_get_to() {
  Link* link;
  link = link_create(1);
  link_set_space1(link, 2);
  link_set_space2(link, 5);
  PRINT_TEST_RESULT(link_get_to(link, 2) == 5);
}
