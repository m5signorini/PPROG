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

int main() {
  Inventory *inventory = NULL;
  Id idaux = -1;
  int tamano = 10;

  printf("Creando inventory: \n");
  inventory = inventory_create();

  if(!inventory) {
    printf("Error al crear el inventory.");
    return -1;
  }

  printf("Añadiendo maximo: 10\n");
  if (inventory_set_max(inventory, tamano)==ERROR) {
    printf("Error al setear el máximo.");
    return -1;
  }

  printf("Añadiendo id: 1\n");
  if (inventory_add_id(inventory, 1)==ERROR) {
    printf("Error al añadir el id.");
    return -1;
  }

  printf("Comprobando el id 1\n");
  if (inventory_has_object(inventory, 1)==FALSE) {
    printf("El id 1 no se encuentra en el inventory.");
  }
  else {
      printf("El id 1 se encuentra en el inventory.\n");
  }

  printf("Id de la posición 0: ");
  idaux = inventory_get_id_at(inventory, 0);
  if (idaux==NO_ID) {
    printf("\nError al hallar el id de la posición 0.");
    return -1;
  }
  printf("%ld \n", idaux);

  printf("Imprimiendo: \n");
  if (inventory_print(inventory)==ERROR) {
    printf("Error al imprimir el inventory.");
    return -1;
  }

  printf("Eliminando el id 1: \n");
  if (inventory_delete_id(inventory, 1)==ERROR) {
    printf("Error al eliminar el id.");
    return -1;
  }

  printf("Comprobando el id 1\n");
  if (inventory_has_object(inventory, 1)==FALSE) {
    printf("El id 1 no se encuentra en el inventory.\n");
  }
  else {
      printf("El id 1 se encuentra en el inventory.\n");
  }

  printf("Imprimiendo de nuevo: \n");
  if (inventory_print(inventory)==ERROR) {
    printf("Error al imprimir el inventory.");
    return -1;
  }

  printf("Destruyendo inventory:\n");
  inventory_destroy(inventory);

  return -1;

}
