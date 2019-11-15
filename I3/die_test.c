#include <stdio.h>
#include "die.h"

int main() {
  Die *dado = NULL;

  printf("Creando dado 1-6:\n");
  dado = die_create(01, 1, 6);

  if(!dado) {
    printf("Error al crear el dado.");
    return -1;
  }
  die_print(dado);

  printf("Tirando dado 1-6: %d\n", die_roll(dado));
  die_print(dado);

  printf("Tirando dado 1-6: %d\n", die_roll(dado));
  die_print(dado);

  printf("Destruyendo dado 1-6:\n");
  die_destroy(dado);

  printf("Creando dado 18-20:\n");
  dado = die_create(01, 18, 20);

  if(!dado) {
    printf("Error al crear el dado.");
    return -1;
  }
  die_print(dado);

  printf("Tirando dado 18-20: %d\n", die_roll(dado));
  die_print(dado);

  printf("Tirando dado 18-20: %d\n", die_roll(dado));
  die_print(dado);

  printf("Destruyendo dado 18-20:\n");
  die_destroy(dado);

  return 1;
}
