## Biblioteca LCD para usar con I2C

Está biblioteca tiene el objetivo de facilitar el uso de la LCD con el periferico I2C que contiene el Raspberry pico.
Debe habilitar el uso de las siguientes librerías para permitir el uso de la librería:

1. #include <stdio.h>
2. #include "pico/stdlib.h"
3. #include "hardware/i2c.h" 

Deberá añadir #include "myI2CLCD.h" para que funcione correctamente la biblioteca, anteriormente debió añadir el .c y .h en el CMakeLists.txt para evitar errores al compilar el proyecto, un ejemplo de posible configuración se presenta en la distribución del proyecto y en el CMakeLists.txt.
