## Teclado matricial 4x4 
Está biblioteca tiene el objetivo de facilitar el uso de un teclado matricial 4x4, mediante un barrido, por lo que no se usan interrupciones para generar la localización del botón pulsado.

Favor de incluir las siguientes bibliotecas para su correcto funcionamiento:
1. #include <stdio.h>
2. #include "pico/stdlib.h"

Deberá añadir #include #include "tecladoMatriz.h" para que funcione correctamente la biblioteca, anteriormente debió añadir el .c y .h en el CMakeLists.txt para evitar errores al compilar el proyecto, un ejemplo de posible configuración se presenta en la distribución del proyecto y en el CMakeLists.txt.
