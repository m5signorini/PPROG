/**
 * @brief Test for set module
 *
 * @file set_test.c
 * @author César Ramírez Mártinez
 * @version 1.1
 * @date 08-10-2019
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include "set.h"

int main(int argc, char *argv[]) {
  Set* set = NULL;
  Id id = 3, id2 = 4, aux;
  int pos, n_ele;

  fprintf(stderr, "Creating set\n");
  set = set_create();
  if (set == NULL) {
    fprintf(stderr, "Error creating set\n"); return 1;
  }
  fprintf(stderr, "Destroying set\n");
  set_destroy(set);

  fprintf(stderr, "Creating set again \n");
  set = set_create();
  if (set == NULL) {
    fprintf(stderr, "Error creating set\n"); return 1;
  }

  fprintf(stderr, "Adding id in the set");
  if((set_add_id(set, id) == ERROR)){
    fprintf(stderr, "Error adding id in the set");
    return 1;
  }
  if((set_print(set) == ERROR)){
    fprintf(stderr, "Error printing the set");
    return 1;
  }
  pos = set_has_id (set, id);

  if(pos > -1){
    fprintf(stderr, "The position of the id in the set is: %d\n", pos);
  }

  fprintf(stderr, "Adding id in the set");
  if((set_add_id(set, id2) == ERROR)){
    fprintf(stderr, "Error adding id in the set");
    return 1;
  }
  if((set_print(set) == ERROR)){
    fprintf(stderr, "Error printing the set");
    return 1;
  }

  fprintf(stderr, "Now we delete the last id added to the set");
  if(set_delete_id(set, id2) == ERROR){
    fprintf(stderr, "Error deleting id in the set");
    return 1;
  }
  if((set_print(set) == ERROR)){
    fprintf(stderr, "Error printing the set");
    return 1;
  }
  aux = set_get_id_at(set, 0);
  if(aux == NO_ID){
    fprintf(stderr, "No ID in that position.\n"); return 1;
  }

  fprintf(stderr, "The id stored in the first position of the set is: %ld\n", aux);
  n_ele = set_get_number_elements(set);
  if(n_ele == UNABLE){
    fprintf(stderr, "Error in fuvntion set_get_number_elements\n"); return 1;
  }

  fprintf(stderr, "Number of elements in the set: %d", n_ele);

  set_destroy(set);

  return 0;
}
