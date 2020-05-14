#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

int validar(int canti, char **arg);
void leer(char nombre[], char **lab, int *fil, int *col, int *opc);
char** valab(char nombre[], int fil, int col, int *x, int *y, int *opc);
void imprimir(char** lab, int fil, int col);
void resolver(char *Laberi[], int x, int y, int filas, int col, int *cantsol, int *tiempo, int *optimo, char *oplab[]);
int cuentapasos(char *lab[], int fil, int col);
void meter(char** lab, int fil, int col,int tiempo, int solu, int pasos, int canti, char **arg,char nombrearchi[]);
void elimina(char** lab, int fil);
void ayuda(void);

//función de validar el nombre del archivo ejecutable
int validar(int canti, char **arg){
   if (canti==2)
    {
      if(strcmp(arg[1],"-h")==0)
{
 ayuda();
 return -1;
}
      else if (strcmp(arg[1],"-n")==0)
{
  //si no se ingreso de una buena manera el ejecutable, mostrara este mensaje
 printf("Por favor, escriba la informacion bien\n");
 ayuda();
 return -1;
}
      else
 return 1;
    }
    //se vuelve a validar la cantidad de palabras ingresadas desde la linea de comandos(3)
  else if (canti==3)
    {
      if(strcmp(arg[1],"-pasos")==0)
return 2;
      else if(strcmp(arg[1],"-h")==0)
{
 ayuda();
 return -1;
}
      else
return 1;
    }
    //se vuelve a validar de cantidad de palabras ingresadas desde la linea de comandos (4)
  else if(canti==4)
    {
      if(strcmp(arg[1],"-pasos")==0)
return 2;
      else if(strcmp(arg[1],"-h")==0)
{
 ayuda();
 return -1;
}
      else
{
      printf("Escriba bien la informacion del ejecutable\n");
      ayuda();
      return -1;
}
    }
  else
    {
      printf("Escriba bien la informacion del ejecutable\n");
      ayuda();
      return -1;
    }
}
//función de leer el archivo
void leer(char nombre[], char **lab, int *fil, int *col, int *opc)
{
  FILE *archivo;
  char linea[101];
  //se abre el archivo
  archivo=fopen(nombre,"rt");
  //se verifica que haya algún contenido
  if(archivo==NULL)
    {
      printf("No se encontró el archivo\n");
      (*opc)=-1;
    }
  else
    {
      //se lee el archivo y después se cierra
      fscanf(archivo,"filas: %d columnas: %d\n", fil, col);
      fclose(archivo);
    }
}
//funcion de validar el laberinto
char** valab(char nombre[], int fil, int col, int *x, int *y, int *opc)
{

  int i, j;
  char** lab;
  FILE* archivo;
  int cantE=0,cantS=0;
  char linea[102];
  //se abre el archivo
  archivo=fopen(nombre, "rt");
  fgets(linea, 102, archivo);
  //se crea la memoria para el archivo
  lab = (char **)malloc(8*fil);
  //se recorre el archivo para verificar las filas y las columnas
  for(i=0;i<fil;i++)
    {
      lab[i]=(char *)malloc(1*(col+1));
      fgets(linea, 102, archivo);
      linea[strlen(linea)-1]='\0';
      strcpy(lab[i], linea);
    }
  for(i=0;i<fil;i++)
    {
      for(j=0;j<col;j++)
{
  //en el archivo se busca la entrada que está dada por una 'E' y se coloca en sus coordenadas
 if(lab[i][j]=='E')
   {
     (*x)=i;
     (*y)=j;
     cantE++;
   }
   //se hace lo mismo con la salida que está dada por una 'S'
 else if(lab[i][j]=='S')
 //por cada salida que encuentre va a sumar una nueva salida
   cantS++;
 else if((lab[i][j]!='X')&&(lab[i][j]!=' '))
   {
     (*opc)=-2;
     //si no está bien escrito el laberinto, no se podrá ejecutar
     printf("Algo paso y no pudo ejecutar\n");
   }
}
    }
  if((cantE!=1)&&(cantS!=1))
    {
      (*opc)=-2;
      printf("Algo paso y no se pudo ejecutar\n");
    }
  fclose(archivo);
  return lab;
}
//función de imprimir el archivo
void imprimir(char** lab,int fil, int col)
{
  int i, j;
  for(i=0;i<fil;i++)
    {
      //se recorre todo el archivo y se va imprimiendo caracter por caracter
      puts(lab[i]);
    }
}
//funcion de eliminar el archivo
void elimina(char** lab, int fil)
{
  int i;
  for(i=0;i<fil;i++)
    {
      //de igual manera se va a recorrer todo el archivo y lo elimina de caracter por caracter
      free(lab[i]);
    }
  free(lab);
}
//función de resolver el laberinto
void resolver(char *lab[], int x, int y, int filas, int col, int *cantsol, int *tiempo, int *optimo, char *oplab[])
{
  int i;
  int pasos;
  int aprov=0;
  int haysolucion=0;
  //comando de tiempo
  (*tiempo)++;
  usleep(300000);
  //se limpia primero la pantalla para poder resolverlo
  system("clear");
  printf("Resolviendo laberinto...\n");
  //va a ir imprimiendo el recorrido del laberinto por un puntador que es '-'
  if(lab[x][y]!='E')
    lab[x][y]='-';
    //se imprime cómo lo va recorriendo
  imprimir(lab, filas, col);
  if(x!=0)
    {
      //se van a ir buscando las salidas en las columnas
      if(lab[x-1][y]=='S')
aprov=1;
    }
    //se van a ir buscando las salidas en las filas
  if(x!=(filas-1))
    {
      if(lab[x+1][y]=='S')
aprov=1;
    }
  if(y!=0)
    {
      if(lab[x][y-1]=='S')
aprov=1;
    }
  if(y!=(col-1))
    {
      if(lab[x][y+1]=='S')
aprov=1;
    }
  if(aprov==1)
    {
      //después de recorrer el laberinto, se van a ir contando los pasos con la función
      pasos=cuentapasos(lab, filas, col);
      pasos++;
      (*cantsol)++;
      if(pasos<(*optimo))
{
 (*optimo)=pasos;
 for(i=0;i<filas;i++)
 //se copian los valores a un nuevo arreglo donde ahora está el laberinto resuelto
   strcpy(oplab[i], lab[i]);
}
    }
  else
    {
      //se busca la salida más óptima
      if(x!=0)
{
  //aquí inicia la recursion hacia el oeste
 if(lab[x-1][y]==' ')
   resolver(lab, x-1, y, filas, col, cantsol, tiempo, optimo, oplab);
}
      if(x!=(filas-1))
{
  //recurión hacia el este
 if(lab[x+1][y]==' ')
   resolver(lab, x+1, y, filas, col, cantsol, tiempo, optimo, oplab);
}
      if(y!=0)
{
  //recursión hacia el sur
 if(lab[x][y-1]==' ')
   resolver(lab, x, y-1, filas, col, cantsol, tiempo, optimo, oplab);
}
      if(y!=(col-1))
{
  //recursión hacia el norte
 if(lab[x][y+1]==' ')
   resolver(lab, x, y+1, filas, col, cantsol, tiempo, optimo, oplab);
}
    }

  lab[x][y]=' ';

}
//función de contar los pasos hacia la solución del laberinto
int cuentapasos(char *lab[], int fil, int col)
{
  int num=0;
  int i, j;
  //se recorre de nueva manera el laberinto
  for(i=0; i<fil;i++)
    {
      for(j=0;j<col;j++)
{
  //cada vez que aparezca un puntero lo va a ir sumando con un contador
 if(lab[i][j]=='-')
   num++;
}
    }
  return num;
}
//función de meter los datos al archivo junto con el laberinto
void meter(char** lab, int fil,int col, int tiempo, int solu, int pasos, int canti, char **arg,char nombrearchi[])
{
  char nombre[50];
  int i;
  FILE *archivo;
  int habin=0;
  //se valida de nuevo las palabras ingresadas desde la linea de comandos (2)
  if(canti==2)
  //se copia el nombre del ejecutable a una variable 'nombre'
    strcpy(nombre,"resultados_laberinto.log");
      //se valida de nuevo las palabras ingresadas desde la linea de comandos (3)
  else if(canti==3)
    {
      if(strcmp(arg[1],"-pasos")==0)
{
 habin=1;
 strcpy(nombre,"resultados_laberinto.log");
}
      else
strcmp(nombre,arg[2]);
    }
  else if(canti==4)
    {
      habin=1;
      strcpy(nombre, arg[3]);
    }
  else
    strcpy(nombre,"resueltolab.txt");
//se abre el archivo
  archivo=fopen(nombre,"wt");

  fprintf(archivo,"Este es el resultado del laberinto sacado de: %s\n", nombrearchi);
  //se aplican los comandos para que nos brinde la hora exaxta del día
  fprintf(archivo,"Este es el resultado\n");
  //se recorre el archivo y se imprime en éste
  for(i=0;i<fil;i++)
    fprintf(archivo,"%s\n", lab[i]);
  fprintf(archivo,"La cantidad de pasos es de: %d\n", cuentapasos(lab, fil, col)+1);
  if(habin==1)
    fprintf(archivo,"Hubo %d soluciones\n", solu);
  float tiemporeal;
  //se divide el tiempo entre 3 para que sea un poco más exacto
  tiemporeal=tiempo/3;
  fprintf(archivo,"Se tardo %.3f de segundos", tiemporeal);
  //se cierra el archivo
  fclose(archivo);
}
//función de ayuda
void ayuda(void)
{
  //se imprime la manera en la que el el programa va funcionar y si se tiene dudas, están los opciones para ver sus ejecuciones
  printf("El programa corre con las siguiente linea de comando\n\nAnalizaLaberinto [opcion] <in_File> [out_File]\n\n");
  printf("*[opcion]Este argumento es opcional e indicara informacion adicional que se quiere obtener al momento de ejecutar el programa.\nEn el caso de que este argumento se haya dado al momento de ejecutar el  programa,  podra  tener  alguno  de  los  siguientes valores:\n\t*-pasos: Indica  que  se  desea  conocer  el  numero total de  soluciones  posibles  (rutas  entre  la entrada y la salida).\n\t*-h: Con esta opción unicamente se desplegara una ayuda en pantalla, indicando al usuario de que  manera debe correr el programa asi como cuales son las opciones disponibles y que es lo que hace cada una de ellas.  En el caso de que se de esta opcion no sera necesario proporcionar ningun otro argumento\n");
  printf("*<in_File>: Sera el nombre del archivo de texto que contenga el laberinto. Este argumento es obligatorio\n");
  printf("*[out_File]: Sera el nombre del archivo de texto que contendra la solución del laberinto, asi como las estadisticas del analisis.\nEl  ultimo argumento es opcional y en caso de que no sea pasado al momento de ejecutar el programa el nombre del archivo debera ser resultados_laberinto.log\n\nGracias por su informacion y vuelva pronto.\n");
}
    