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

int main(int argc, char *argv[]) {
  if (argc < 3) {
    fprintf(stderr, "Use: %s <min> <max>\n", argv[0]);
    return 1;
  }

  Die* die = NULL;
  int min = atoi(argv[1]);
  int max = atoi(argv[2]);

  die = die_create(1, min, max);
  if (die == NULL) {
    fprintf(stderr, "Error creating die\n");
    return 1;
  }

  die_roll(die);
  if(die_print(die) == ERROR) {
    fprintf(stderr, "Error printing die\n");
    die_destroy(die);
    return 1;
  }
  
  die_roll(die);
  if(die_print(die) == ERROR) {
    fprintf(stderr, "Error printing die\n");
    die_destroy(die);
    return 1;
  }
  
  die_destroy(die);

  return 0;
}
