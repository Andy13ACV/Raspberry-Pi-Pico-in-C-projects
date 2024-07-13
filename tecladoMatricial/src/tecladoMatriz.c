#include "tecladoMatriz.h"

// variable para el teclado
static matriz keypad;

// representación del teclado para mandar el valor
uint8_t caracteresMatriz[4][4] = {{'1', '2', '3', 'A'},
                                {'4', '5', '6', 'B'},
                                {'7', '8', '9', 'C'},
                                {'*', '0', '#', 'D'}};

void tecladoMatrizInit(uint8_t pinFilas[], uint8_t pinColumnas[]){
    //se asume que se configura para una matriz de 4x4 
    //por lo que se usan solo 8 pines


    // inicialización de las filas
    for(uint8_t j = 0 ; j < 4 ; j++){
        gpio_init(pinFilas[j]);
        gpio_set_dir(pinFilas[j], GPIO_OUT);
        keypad.filas[j] = pinFilas[j];
        gpio_put(pinFilas[j], 0);
    }

    // inicialización de las columnas
    for(uint8_t i = 0 ; i < 4 ; i++){
        gpio_init(pinColumnas[i]);
        gpio_set_dir(pinColumnas[i], GPIO_IN);
        gpio_pull_up(pinColumnas[i]);
        keypad.columnas[i] = pinColumnas[i];
    }

    // inicialización de las posiciones
    keypad.contador = 0;
    keypad.columnaCompletada = COLUMNA_NULL;
    keypad.filaCompletada = 0;
}

void barrido(){
    const uint8_t fila_1 = 0;
    const uint8_t fila_4 = 3;

    // realiza el barrido 
    for(uint8_t i = fila_1 ; i <= fila_4 ; i++){
        if(i == keypad.contador){
            gpio_put(keypad.filas[i], 0);
            keypad.filaCompletada = i;
        }else{
            gpio_put(keypad.filas[i], 1);
        }
    }

    // Cambia al siguiente pin
    if(keypad.contador >= fila_4){
        keypad.contador = fila_1;
    }else{
        keypad.contador++;
    }
}

uint8_t leeTeclado(){
    const uint8_t columna_1 = 0;
    const uint8_t columna_4 = 3;
    keypad.columnaCompletada = COLUMNA_NULL;

    // Lee las columnas
    for(uint8_t i = columna_1 ; i <= columna_4 ; i++){
        if(gpio_get(keypad.columnas[i]) == 0){
            sleep_ms(5);
            while(gpio_get(keypad.columnas[i]) == 0);
            sleep_ms(5);
            keypad.columnaCompletada = i;
            break;  
        }
    }

    // retorna el valor al principal
    if(keypad.columnaCompletada == COLUMNA_NULL){
        return COLUMNA_NULL;
    }else{    
        return caracteresMatriz[keypad.columnaCompletada][keypad.filaCompletada];
    }
}
