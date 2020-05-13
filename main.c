#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "helpers/helper.h"

int main(int argc, char **argv) {
  if(comparar_argumentos(argv, argc) == 1) {
    crearMatriz(argv[2]);
  }
  return 0;
}