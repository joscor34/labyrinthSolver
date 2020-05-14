#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "helpers/helper.h"

int main(int argc, char **argv)
{
   int opc=0;
   char **Laberinto;
   char **resuelto;
   int filas=0, columnas=0;
   int X=0, Y=0;
   int cantidadsoluciones=0;
   int tiempo=0;
   int pasosoptimos=1000001;
   //validacion del nombre del archivo
   opc=validar(argc,argv);
   if(opc>0){
   //se lee el archivo
    strcat(argv[opc], ".txt");
    leer(argv[opc], Laberinto, &filas, &columnas, &opc);
   }
   if(opc>0)
     {
       //se ingresa el laberinto y se resuelve
       Laberinto=valab(argv[opc],filas,columnas,&X, &Y, &opc);
       resuelto=valab(argv[opc],filas,columnas,&X, &Y, &opc);
     }
   if(opc>0)
     {
       system("clear");
       printf("Aqui esta el laberinto\n");
       //se imprime el laberinto
       imprimir(Laberinto, filas, columnas);
       printf("Pulse enter para empezar");
       getchar();
       //se resuelve el laberinto
       resolver(Laberinto,X,Y,filas, columnas, &cantidadsoluciones, &tiempo, &pasosoptimos, resuelto);
       system("clear");
       printf("Este es el laberinto resulto\n");
       //se imprime el laberinto
       imprimir(resuelto, filas, columnas);
       printf("Metiendo resultado en el archivo...\n");
       //se meten los datos al archivo
       meter(resuelto, filas,columnas, tiempo, cantidadsoluciones, pasosoptimos, argc, argv,argv[opc]);
       printf("Se han guardado los datos\n");
       printf("Gracias por usar el sisitema de resolver laberintos de Lalo y David\n");
       //se eliminan los laberintos
       elimina(Laberinto, filas);
       elimina(resuelto, filas);
     }
   else if(opc==-2)
     {
       elimina(Laberinto, filas);
       elimina(resuelto, filas);
     } else
     {
       ayuda();
     }
     


   return 0;
}