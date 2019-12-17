#include <stdio.h>
#include <stdlib.h>
#include "game_management_test.h"
#include "test.h"
#include "game_management.h"

#define MAX_TESTS 3

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

    test_game_management_create_from_file(argv[1]);
    test_game_management_save(argv[1]);
    test_game_management_load_from_file(argv[1]);
    PRINT_PASSED_PERCENTAGE;

    return 1;
}


void test_game_management_create_from_file(char* filename) {
  Game* game;
  game = game_management_create_from_file(filename);
  PRINT_TEST_RESULT(game!=NULL);
}

void test_game_management_save(char* filename){
    Game* game;
    game = game_management_create_from_file(filename);
    PRINT_TEST_RESULT(game_management_save(game, filename) == OK);
}

void test_game_management_load_from_file(char* filename){
    Game* game;
    game = game_management_create_from_file(filename);
    game_clear(game);
    PRINT_TEST_RESULT(game_management_load_from_file(game, filename) == game);
}
