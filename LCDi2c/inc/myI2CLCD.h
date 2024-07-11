/** 
 * @file myI2CLCD.h
 * @brief Declaraciones y documentación para el manejo de una 
 * pantalla LCD 16x2 mediante I2C en RP2040.
 * @author Andy Alan CV.
 * 
*/

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"

/**
 * @brief Estructura que representa una pantalla LCD. 
 * 
 * Contiene la configuración del modulo I2C y contiene información que
 * puede ser relevante al momento de usar la LCD.
 * 
*/
typedef struct{
    i2c_inst_t *puertoI2C; /**< Puerto I2C.*/
    uint8_t backlight;
    uint8_t scl; /**< Pin scl.*/
    uint8_t sda; /**< Pin sda.*/
    uint8_t dirI2C; /**< Dirección de la pantalla I2C.*/
    uint16_t tiempo; /**< Tiempo que debe tomar la comunicación I2C.*/
    uint8_t posFinal; /**< Posición final del cursor de la pantalla LCD.*/
} lcd_t;


// LCD Configuración básica 4 bits
#define LCD_DATA 0x3C
#define SALUDO 0x03 
#define RETURN_HOME 0x02 
#define FUNCTION_SET 0x28 
#define DISPLAY_CONTROL_INIT 0x08 
#define DISPLAY_CONTROL 0x0C
#define ENTRY_MODE_SET 0x06 
#define CLEAR_DISPLAY 0x01 
#define DDRAM_ACCESS 0x80
#define MAX_NUM_LONG 32

// Comandos entry mode set
#define INCREMENTA_DDRAM 0x06
#define DECREMENTA_DDRAM 0x04
#define DESPLAZAMIENTO  0x05
#define NO_DESPLAZAMIENTO 0x04

// Comandos display control
#define PRENDER_PANTALLA 0x0C
#define APAGAR_PANTALLA 0x08
#define VISUALIZAR_CURSOR 0x0A
#define NO_VISUALIZAR_CURSOR 0x08
#define CURSOR_PARPADEO 0x09
#define CURSOR_PARPADEO_RECTANGULAR 0x08

// Comandos cursor and display shift 
#define DESPLAZAR_CURSOR_A_LA_DERECHA 0x18
#define DESPLAZAR_CURSOR_A_LA_IZQUIERDA 0x0A
#define APLICAR_A_TODA_LA_PANTALLA 0x10
#define APLICAR_A_CURSOR 0x10

// Comandos function set
#define DATOS_A_8_BITS 0x30
#define DATOS_A_4_BITS 0x20
#define LCD_2_LINEAS 0x28
#define LCD_1_LINEA 0x20
#define PUNTOS_5X10 0x14
#define PUNTOS_5X7 0x20

// Comando CGRAM
#define CGRAM_ACCESO 0x40

/**
 * @brief Inicializa la pantalla LCD
 *
 * Está función configura los pines y el puerto I2C para la comunicación
 * de la LCD, guarda los datos y iniciliza la LCD para su uso.
 * Ten en cuenta que se basa en la forma de 4 bits.
 * 
 * @param i2c Puntero a la estructura I2C que se va ocupar para la comunicación.
 * @param scl Pin SCL. 
 * @param sda Pin SDA.
 * @param veltrans Velocidad de transmisión para el I2C.
 * @param diri2c Dirección del módulo LCD para la comunicación I2C.
 * 
*/
void LCDinit(i2c_inst_t* i2c, uint8_t scl, uint8_t sda, uint16_t veltrans, uint8_t dirI2C);

/**
 * @brief Inicialización previa. 
 * 
 * Rutina que hace al LCD responder antes de realizar todo el
 * proceso de inicialización.
 * 
*/
static void saludo();

/**
 * @brief  Envía un comando a la LCD.
 * 
 * Esta función permite enviar un comando a la LCD para realizar una
 * acción determinada en paquetes de 4 bits.
 * 
 * @param dato Se envía la información necesaria para configurar la LCD.
 * 
*/
static void enviaCMD(char dato);

/**
 * @brief Envía un dato para imprimir en la LCD 
 * 
 * Esta función procesa el dato recibido para enviarlo en el formato de
 * 4 bits.
 * 
 * @param dato Se envía un caracter para imprimir en la LCD
 * 
*/
void enviaDato(char dato);

/**
 * @brief Envía una cadena para ser impresa en la LCD
 * 
 * Está función procesa la cadena para imprimirlo en la LCD, depende
 * la función enviaCMD para realizar la impresión de cada parte de la 
 * cadena.
 * 
 * @param dato Se envía una cadena para imprimirse en la LCD
 * 
*/
void enviaCadena(char *dato);

/**
 * @brief Limpia la pantalla LCD
 * 
 * Función que se encarga de realizar la limpieza de la pantalla LCD.
 * Tenga en cuenta que la DDRAM se pone en la posición inicial.
 * 
*/
void limpiaLCD();

/**
 * @brief Poner una dirección DDRAM en especifíco. 
 * 
 * Función que realiza el movimiento del cursor a una posición
 * deseada.
 * 
 * @param dir Dirección entre 0 a 0x20 y 0x40 a 0x68 para realizar el
 * posicionamiento del cursor.
 * 
*/
void dirDDRAM(uint8_t dir);

/**
 * @brief Obtiene la posición actual del cursor.
 * @return La posición actual del cursor en la pantalla LCD.
 * 
*/
uint8_t posFinalLCD();

/**
 * @brief Imprime un valor entero.
 * 
 * Función que convierte el valor entero en cadena para 
 * posteriormente imprimirlo en la LCD.
 * 
 * @param numInt Valor númerico de tipo entero.
 * 
*/
void imprimirInt(int numInt);

/**
 * @brief Imprime un valor flotante
 * 
 * Función que convierte el valor flotante en cadena para
 * posteriormente imprimirlo en la LCD.
 * 
 * @param numFloat Valor númerico de tipo flotante a convertir.
 * 
*/
void imprimirFloat(float numFloat);


/**
 * @brief Retorno a casa 
 * 
 * Función que regresa a la dirección DDRAM 0x00
 * 
*/
void retornoCasa();

/**
 * @brief  Ajuste de modo de entrada
 * 
 * Configuración de Entry Mode Set
 * 
 * @param comando funcionalidad a insertar
*/
void entryModeSet(uint8_t comando);

/**
 * @brief Control de pantalla
 * 
 * Configuración de Display Control
 * 
 * @param comando funcionalidad a insertar
*/
void displayControl(uint8_t comando);


/**
 * @brief Desplazamiento de cursor & pantalla 
 * 
 * Configuración de Cursor and Display Shift
 *  
 * @param comando funcionalidad a insertar
*/
void cursorDisplayShift(uint8_t comando);

/**
 * @brief Comando de ajuste de función 
 * 
 * Configuración de Funtion Set
 * 
 * @param comando funcionalidad a insertar
*/
void functionSet(uint8_t comando);

/**
 * @brief Ajuste de dirección de CGRAM
 * 
 * Configuración para insertar un icono personalizable
 * 
 * @param NoCGRAM Dirección de la CGRAM a grabar 
 * @param figura matriz que contiene la figura 
 * @param tamFigura tamaño de la matriz para verificar que su tamaño es correcto
*/
uint8_t caracterPersonalizado(uint8_t NoCGRAM, uint8_t *figura, size_t tamFigura);


/**
 * @brief Encender la backlight
 * 
 * Prender el backlight de la LCD
 * 
 */
void backlight_on();

/**
 * @brief Apagar la backlight
 * 
 * Apagar el backlight de la LCD
 * 
 */
void backlight_off();

/**
 * @brief Posicionar el cursor mediante coordenadas x, y.
 * 
 * @param x posición en x
 * @param y posición en y
 */
void cursorPosicion(uint8_t x, uint8_t y);