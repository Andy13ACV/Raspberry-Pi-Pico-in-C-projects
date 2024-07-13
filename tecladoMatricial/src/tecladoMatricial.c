#include <stdio.h>
#include "pico/stdlib.h"
#include "tecladoMatriz.h"

int main()
{
    stdio_init_all();
    uint8_t filas[] = {2, 3, 4 ,5};
    uint8_t columnas[] = {6, 7, 8, 9};
    puts("Hello, world!");
    tecladoMatrizInit(filas, columnas);
    uint8_t valorTeclado = 0;
    while(1){
        barrido();
        sleep_ms(10);
        valorTeclado = leeTeclado();
        if(valorTeclado != COLUMNA_NULL){
            printf("%c \n", valorTeclado);
        }
        
    }

    return 0;
}
