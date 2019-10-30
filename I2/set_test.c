/**
 * @brief Test for set module
 *
 * @file die_test.c
 * @author César Ramírez Mártinez
 * @version 1.1
 * @date 08-10-2019
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include "space.h"
#include "set.h"

int main(int argc, char *argv[]) {
  Set* set = NULL;
  Id id = 3, id2 = 4, aux;
  int pos;

  set = set_create();
  if (set == NULL) {
    fprintf(stderr, "Error creando set\n"); return 1;
  }

  if((set_add_id(set, id) == ERROR)){
    return 1;
  }
  if((set_print(set) == ERROR)){
    return 1;
  }
  pos = set_has_id (set, id);
  if(pos > -1){
    printf("The position of the id in the set is: %d", pos);
  }
  if((set_add_id(set, id2) == ERROR)){
    return 1;
  }
  if((set_print(set) == ERROR)){
    return 1;
  }
  printf("Now we delete the last id added to the set");
  if(set_delete_id(set, id2) == ERROR){
    return 1;
  }
  if((set_print(set) == ERROR)){
    return 1;
  }
  aux = set_get_id_at(set, 0);
  if(aux != NO_ID){
    printf("The id stored in the first position of the set is: %ld\n", aux);
  }
  set_destroy(set);

  return 0;
}
