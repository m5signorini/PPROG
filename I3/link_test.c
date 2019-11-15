#include <stdio.h>
#include "link.h"

int main() {
  Link *link = NULL;
  Id idaux = -1;
  char str[100];

  printf("Creando link con id 14:\n");
  link = link_create(14);

  if(!link) {
    printf("Error al crear el link.");
    return -1;
  }


  idaux = link_get_id(link);
  printf("Id del link (link_get_id): %ld\n", idaux);

  printf("Añadiendo nombre: enlace\n");
  sprintf(str, "enlace");
  if (link_set_name(link, str)==ERROR){
    printf("Error al setear el nombre.");
    return -1;
  }

  printf("Imprimiendo nombre: %s\n", link_get_name(link));

  printf("Añadiendo espacio 1 con Id 4\n");
  if (link_set_space1(link, 4)==ERROR){
    printf("Error al setear el espacio 1.");
    return -1;
  }

  printf("Imprimiendo Id del espacio 1: %ld\n", link_get_space1(link));

  printf("Añadiendo espacio 2 con Id 8\n");
  if (link_set_space2(link, 8)==ERROR){
    printf("Error al setear el espacio 2.");
    return -1;
  }

  printf("Imprimiendo Id del espacio 2: %ld\n", link_get_space2(link));

  printf("Seteando open: TRUE\n");
  if (link_set_open(link, TRUE)==ERROR){
    printf("Error al setear open.");
    return -1;
  }

  link_print(link);

  printf("Probando link_get_to, abriendo link desde el espacio con id 4: %ld\n", link_get_to(link, 4));
  printf("Probando link_get_to, abriendo link desde el espacio con id 8: %ld\n", link_get_to(link, 8));



  printf("Destruyendo link:\n");
  link_destroy(link);

  return 1;
}
