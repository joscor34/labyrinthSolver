# Labyrinth Solver

Este programa elavorado en lenguaje C se encarga de resolver un laberintos indicados por el usuario

## Argumentos

El programa utiliza diferentes tipos de argumento:
  
- *-h* Para desplegar informacíon sobre los otros argumentos e información sobre el programa.

- *-s* Para mostrar todos los caminos posibles para completar el laberinto.
  
- *-n* Para mostrar el camino mas óptimo.

## Ejecución

Para ejecutar el programa ingresa el siguiente comando en tu consola:

``./executable.out <argumento> <archivo_entrada> <archivo_salida>``

## Archivos de entrada y de salida

Los archivos de entrada son aquellos que contienen el laberinto y tienen la extención __*.lab*__.

Por ejemplo __*example.lab*__

Contenido:

![Laberinto sin resolver](/assets/images/laberinto_sin_resolver.png "Laberinto sin resolver")

La **E** o **e** indican el inicio del laberinto y la **S** o **s** marca el final. Las **@** indican los limites y las paredes del laberinto.  

------  

Los archivos de salida se generan automáticamente por el programa, lo unico que se le tiene que asignar es el nombre y se guardan con la extención __*.sol*__ (En caso de no especificarlo el programa automaticamente lo pone).  

Por ejemplo **example_solved.sol**

Contenido:

![Laberinto resuelto](/assets/images/laberinto_resuelto.png "Laberinto resuelto")

En este caso las **X** marcán el camino mas óptimo.  

El tamaño del laberinto es de un mínimo de 15 columnas por 15 renglones y de un máximo de 50 columnas por 50 renglones.
