#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void ayuda() {
  printf("El programa corre con las siguiente linea de comando\n\nAnalizaLaberinto [opcion] <in_File> [out_File]\n\n");
  printf("*[opcion]Este argumento es opcional e indicará información adicional que se quiere obtener al momento de ejecutar el programa.\nEn el caso de que este argumento se haya dado al momento de ejecutar el  programa,  podrá  tener  alguno  de  los  siguientes valores:\n\t*-s: Indica  que  se  desea  conocer  el  número total de  soluciones  posibles  (rutas  entre  la entrada y la salida).\n\t*-n: Con este argumento solo muestra el camino mas optimo\n\t*-h: Con esta opción únicamente se desplegará una ayuda en pantalla, indicando al usuario de qué  manera debe correr el programa así como cuáles son las opciones disponibles y qué es lo que hace cada una de ellas.  En el caso de que se dé esta opción no será necesario proporcionar ningún otro argumento\n");
  printf("*<in_File>: Será el nombre del archivo de texto que contenga el laberinto. Este argumento es obligatorio\n");
  printf("*[out_File]: Será el nombre del archivo de texto que contendrá la solución del laberinto, así como las estadísticas del análisis.\nEl  último argumento es opcional y en caso de que no sea pasado al momento de ejecutar el programa el nombre del archivo deberá ser resultados_laberinto.log\n\nGracias por su información y vuelva pronto.\n");
}

int comparar_argumentos(char **arg, int archivos) {
  if(archivos == 4 && strcmp(arg[1], "-n") == 0) {
    printf("Mostrar solo el mas optimo");
    return 1;
  } else if (archivos == 4 && strcmp(arg[1], "-s") == 0) {
    printf("Mostrar todos");
    return 2;
  } else {
    ayuda();
    return 0;
  }
}

void abrir_archivo(char *nombre_archivo) {
	FILE *archivo;
	char caracter;
	
	archivo = fopen(nombre_archivo,"r");
	
	if (archivo == NULL) {
    printf("\nError de apertura del archivo. \n\n");
  } else {
    printf("\nEl contenido del archivo de prueba es \n\n");
    while((caracter = fgetc(archivo)) != EOF) {
		  printf("%c",caracter);
      if(caracter == '@'){
        printf("Barrera");
      }else if(caracter == 'e' || caracter == 'E') {
        printf("Cominenzo");
      } else if(caracter == 's' || caracter == 'S') {
        printf("final");
      } else {
        printf("camino");
      }
	  }
  }
  fclose(archivo);
}