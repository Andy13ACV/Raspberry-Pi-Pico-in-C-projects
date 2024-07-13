/**
 * @file tecladoMatriz.h
 * @brief Declaraciones y documentación para el manejo de un
 * teclado matricial 4x4.
 * @author Andy Alan CV.
 * 
 */
#include <stdint.h>
#include <stdio.h>
#include "pico/stdlib.h"

/**
 * @brief Estructura que representa al teclado matricial.
 * 
 * Contiene la configuración de los pines, fila y columna
 * en la que se localiza.
 */


typedef struct{
    uint8_t filas[4]; /**< Pines de las filas */
    uint8_t columnas[4]; /**< Pines de las columnas */
    uint8_t contador; /**< Mantiene el conteo del barrido*/
    uint8_t filaCompletada; /**< Posición de la fila */
    uint8_t columnaCompletada;/**< Posición de la columna */
}matriz;

// No se ha oprimido un botón
#define COLUMNA_NULL 4

/**
 * @brief Inicializa el teclado matricial
 * 
 * Está función configura los pines para manejar un teclado matricial
 * 4x4.
 * 
 * @param pinFilas Pines donde se encuentran las filas
 * @param pinColumnas Pines donde se encuentran las columnas
 */
void tecladoMatrizInit(uint8_t pinFilas[], uint8_t pinColumnas[]);

/**
 * @brief Barrido de la matriz
 * 
 * Realiza el barrido de la matriz antes de revisar si se ha pulsado 
 * un botón.
 * 
 */
void barrido();

/**
 * @brief Lee el teclado
 * 
 * Busca si se ha pulsado un botón, para mandar el valor en unsigned
 * char, en caso contrario se manda un COLUMNA_NULL.
 * 
 */
uint8_t leeTeclado();
