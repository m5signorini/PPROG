/**
* @brief It implements all the functions used to manage the inventory
*
* @file inventory.c
* @author César Ramírez Martínes
* @version 1.0
* @date 20-09-2019
* @copyright GNU Public License
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "set.h"
#include "inventory.h"


struct _Inventory {
  Set* ids;   /*!< memory direction of the set of the inventory */
  int max_inventory;   /*!<max number of elements an inventory is able to put up with */
};

Inventory* inventory_create() {
  Inventory* new_inventory = NULL;
  Set* ids = NULL;

  new_inventory = (Inventory*) malloc(sizeof(Inventory));
  if (new_inventory == NULL) {
    return NULL;
  }

  ids = set_create();

  if (ids == NULL){
    free(new_inventory);
    return NULL;
  }

  new_inventory->ids = ids;
  new_inventory->max_inventory = 0;

  return new_inventory;
}

STATUS inventory_destroy(Inventory* inventory) {
  if (!inventory) {
    return ERROR;
  }
  set_destroy(inventory->ids);
  free(inventory);

  return OK;
}

BOOL inventory_has_object(Inventory* inventory, Id id){
  if (inventory == NULL || id <= NO_ID){
    return TRUE;
  }
  int res = 0;
  res = set_has_id (inventory->ids, id);
  if ( res == UNABLE || res == ABLE_TO_ADD){
    return FALSE;
  }
  return TRUE;
}

STATUS inventory_add_id(Inventory* inventory, Id id) {
  if (!inventory || id <= NO_ID) {
    return ERROR;
  }
  if (inventory_has_object(inventory, id) == TRUE){
    return OK;
  }
  if (set_add_id(inventory->ids, id) == ERROR){
    return ERROR;
  }

  return OK;
}

int inventory_get_max(Inventory* inventory) {
  if (!inventory) {
    return ERROR;
  }

  return inventory->max_inventory;
}

STATUS inventory_set_max(Inventory* inventory, int max) {
  if (!inventory || max < 0) {
    return ERROR;
  }

  inventory->max_inventory = max;

  return OK;
}

int inventory_get_number_objects(Inventory* inventory) {
  if (!inventory) {
    return ERROR;
  }

  return set_get_number_elements(inventory->ids);
}

STATUS inventory_delete_id(Inventory* inventory, Id id) {
  if (!inventory || id <= NO_ID) {
    return ERROR;
  }
  if (inventory_has_object(inventory, id) == FALSE){
    return OK;
  }
  if (set_delete_id(inventory->ids, id) == ERROR){
    return ERROR;
  }

  return OK;
}

Id inventory_get_id_at(Inventory* inventory, int index) {
  if (!inventory || index < 0 || index > inventory->max_inventory) {
    return NO_ID;
  }

  return set_get_id_at(inventory->ids, index);
}

STATUS inventory_print(Inventory* inventory) {
  if (!inventory) {
    return ERROR;
  }

  if(!fprintf(stdout, "--> Inventory: \n")){
    return ERROR;
  }

  if (set_print(inventory->ids) == ERROR){
    return ERROR;
  }

  fprintf(stdout, "The maximum amount of objects you can carry is %d\n", inventory->max_inventory);
  return OK;
}
