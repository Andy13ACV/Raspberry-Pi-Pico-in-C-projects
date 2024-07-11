/**
 * @file myI2CLCD.C
 * @brief Funciones necesarias para realizar el control de la LCD.
 * @author Andy Alan CV. 
*/

#include "myI2CLCD.h"

// Estructura para almacenar datos importantes de la LCD.
static lcd_t myLCD;

void LCDinit(i2c_inst_t *i2c, uint8_t scl, uint8_t sda, uint16_t veltrans, uint8_t dirI2C){
    
    // Configuración del LCD por I2C.
    myLCD.puertoI2C = i2c;
    myLCD.scl = scl;
    myLCD.sda = sda;
    myLCD.dirI2C = dirI2C;
    myLCD.tiempo = veltrans;
    myLCD.posFinal = 0;
	myLCD.backlight = 0;

    // Configuración del puerto por I2.
    i2c_init(myLCD.puertoI2C, myLCD.tiempo*1000);
    gpio_set_function(myLCD.sda, GPIO_FUNC_I2C);
    gpio_set_function(myLCD.scl, GPIO_FUNC_I2C);
    gpio_pull_up(myLCD.sda);
    gpio_pull_up(myLCD.scl);

    // Configuración inicial del LCD para 4 bits;
	saludo();
	enviaCMD(FUNCTION_SET);
	enviaCMD(DISPLAY_CONTROL_INIT);
	enviaCMD(CLEAR_DISPLAY);
	enviaCMD(ENTRY_MODE_SET);
	enviaCMD(DISPLAY_CONTROL);
	enviaCMD(RETURN_HOME);	
}

static void saludo(){
	uint8_t saludo = 0x30;
    
    // Espera hasta que se estabilize la energía del LCD
	sleep_ms(100); 

    // Rutina para despertar a la LCD
	for(uint8_t i = 0 ; i < 3 ; i++){
		i2c_write_blocking(myLCD.puertoI2C, myLCD.dirI2C, &saludo, 1, false);
		saludo = 0x04 | saludo;
		i2c_write_blocking(myLCD.puertoI2C, myLCD.dirI2C, &saludo, 1, false);
		sleep_ms(3);
		saludo = 0x30;
		i2c_write_blocking(myLCD.puertoI2C, myLCD.dirI2C, &saludo, 1, false);
		sleep_ms(5);
	}
	saludo = 0x20;
	i2c_write_blocking(myLCD.puertoI2C, myLCD.dirI2C, &saludo, 1, false);
	saludo = 0x04 | saludo;
	i2c_write_blocking(myLCD.puertoI2C, myLCD.dirI2C, &saludo, 1, false);
	sleep_ms(3);
	saludo = 0x20;
	i2c_write_blocking(myLCD.puertoI2C, myLCD.dirI2C, &saludo, 1, false);
	sleep_ms(5);
	
}

static void enviaCMD(char dato){
	char cmdEnviado;
	const uint8_t mascara = 0xF0;
	// Enviar nibble alto 
	cmdEnviado = (dato & mascara) | myLCD.backlight;
	i2c_write_blocking(myLCD.puertoI2C, myLCD.dirI2C, &cmdEnviado, 1, false);
	cmdEnviado = 0x04 | cmdEnviado;
	i2c_write_blocking(myLCD.puertoI2C, myLCD.dirI2C, &cmdEnviado, 1, false);
	sleep_ms(3);
	cmdEnviado = 0xF0 & cmdEnviado | myLCD.backlight;
	i2c_write_blocking(myLCD.puertoI2C, myLCD.dirI2C, &cmdEnviado, 1, false);
	sleep_ms(10);

	// Enviar nibble bajo
	cmdEnviado = ((dato << 4) & mascara) | myLCD.backlight;
	i2c_write_blocking(myLCD.puertoI2C, myLCD.dirI2C, &cmdEnviado, 1, false);
	cmdEnviado = 0x04 | cmdEnviado;
	i2c_write_blocking(myLCD.puertoI2C, myLCD.dirI2C, &cmdEnviado, 1, false);
	sleep_ms(3);
	cmdEnviado = 0xF0 & cmdEnviado | myLCD.backlight;
	i2c_write_blocking(myLCD.puertoI2C, myLCD.dirI2C, &cmdEnviado, 1, false);
	sleep_ms(10);
}

void enviaDato(char dato){
	char enviarDato; 
	const uint8_t mascara = 0xF0;
	
	// enviar el nibble alto
	enviarDato = (dato & mascara) | myLCD.backlight;
	enviarDato |=  0x01;
	i2c_write_blocking(myLCD.puertoI2C, myLCD.dirI2C, &enviarDato, 1, false);
	enviarDato |= 0x04;
	i2c_write_blocking(myLCD.puertoI2C, myLCD.dirI2C, &enviarDato, 1, false);
	sleep_ms(3);
	enviarDato &= 0xFB | myLCD.backlight;
	i2c_write_blocking(myLCD.puertoI2C, myLCD.dirI2C, &enviarDato, 1, false);
	sleep_ms(10);
	
	// enviar el nibble bajo 
	enviarDato = ((dato << 4) & mascara) | myLCD.backlight;
	enviarDato |= 0x01;
	i2c_write_blocking(myLCD.puertoI2C, myLCD.dirI2C, &enviarDato, 1, false);
	sleep_ms(3);
	enviarDato |= 0x04;
	i2c_write_blocking(myLCD.puertoI2C, myLCD.dirI2C, &enviarDato, 1, false);
	sleep_ms(3);
	enviarDato &= 0xFB | myLCD.backlight;
	i2c_write_blocking(myLCD.puertoI2C, myLCD.dirI2C, &enviarDato, 1, false);	
	sleep_ms(10);
    
    // Guarda la siguiente posición de la LCD
    myLCD.posFinal++;
}

void enviaCadena(char *dato){
	// imprime cada caracter
	for(uint8_t i = 0 ; dato[i] != '\0' ; i++){
        // Si excede el espacio de la LCD corta
		if(i >= 0x67){
			break;
		}else{
			enviaDato(dato[i]);	
		}
	}
}

void limpiaLCD(){
	enviaCMD(CLEAR_DISPLAY);
    myLCD.posFinal = 0;
}

void dirDDRAM(uint8_t dir){
	// Permite cambiarse de posición usando las direcciones empleadas por el LCD
    const uint8_t PosicionInicial[] = {0x00, 0x40};
	const uint8_t PosicionFinal[] = {0x27, 0x67};
	uint8_t linea1 = (dir >= PosicionInicial[0] && dir <= PosicionFinal[0]);
    uint8_t linea2 = (dir >= PosicionInicial[1] && dir <= PosicionFinal[1]);
    uint8_t comando = 0x80;

    if(linea1 || linea2){
        comando |= dir;
        enviaCMD(comando);
        myLCD.posFinal = dir;
    }
    
}

uint8_t posFinalLCD(){
    return myLCD.posFinal;
}

void imprimirInt(int numInt){
    char buffer[MAX_NUM_LONG];
    sprintf(buffer, "%d", numInt);
    enviaCadena(buffer);
}

void imprimirFloat(float numFloat){
    char buffer[MAX_NUM_LONG];
    sprintf(buffer, "%4f", numFloat);
    enviaCadena(buffer);
}

void retornoCasa(){
    enviaCMD(RETURN_HOME);
}

void entryModeSet(uint8_t comando){
	// Valida si es la instrucción es de este tipo
    if(comando >= 0x04 && comando <= 0x07){
        enviaCMD(comando);
    }
}

void displayControl(uint8_t comando){
	// Valida si es la instrucción es de este tipo
    if(comando >= 0x08 && comando <= 0x0F){
        enviaCMD(comando);
    }
}

void cursorDisplayShift(uint8_t comando){
	// Valida si es la instrucción es de este tipo
    if(comando >= 0x10 && comando <= 0x1C){
        enviaCMD(comando);
    }
}

void functionSet(uint8_t comando){
	// Valida si es la instrucción es de este tipo
    if(comando >= 0x32 && comando <= 0x3C){
        enviaCMD(comando);
    }
}

uint8_t caracterPersonalizado(uint8_t NoCGRAM, uint8_t *figura, size_t tamFigura){
    const size_t tamMax = 8;
    const uint8_t elementos = 8;
    uint8_t compruebaNoCGRAM = (NoCGRAM >= 0 && NoCGRAM <= 16);

    if(compruebaNoCGRAM == 0){
        return 0;
    }

    if(tamFigura == tamMax){
        enviaCMD(CGRAM_ACCESO + (NoCGRAM*elementos));     
        sleep_ms(1);
        for(uint8_t i = 0 ; i < elementos ; i++){
            enviaDato(figura[i]);
            sleep_ms(1);
        }
		//sleep_ms(5);
        return 1;

    }else{
        return 0;
    }
    
}

void backlight_on(){
	// encender backlight
	const uint8_t enciende = 0x08;
	myLCD.backlight = enciende;
	i2c_write_blocking(myLCD.puertoI2C, myLCD.dirI2C, &enciende, 1, false);
}

void backlight_off(){
	// apagar backlight 
	const uint8_t apaga = 0x00;
	myLCD.backlight = apaga;
	i2c_write_blocking(myLCD.puertoI2C, myLCD.dirI2C, &apaga, 1, false);
}


void cursorPosicion(uint8_t x, uint8_t y){
	const uint8_t cursorInicio[] = {0x00, 0x40, 0x14, 0x54};
	const uint8_t comando = 0x80;

	// excede la posición en y o x
	if(y >= 4 || x >= 16){
		return;
	}

	// obten la posición 
	uint8_t posicionFinal = cursorInicio[y] + x;
	enviaCMD(comando | posicionFinal);
	myLCD.posFinal = posicionFinal;

}