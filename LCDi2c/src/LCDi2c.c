#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "myI2CLCD.h"


// I2C defines
// This example will use I2C0 on GPIO8 (SDA) and GPIO9 (SCL) running at 400KHz.
// Pins can be changed, see the GPIO function select table in the datasheet for information on GPIO assignments
#define I2C_PORT i2c0
#define I2C_SDA 0
#define I2C_SCL 1
#define I2C_DIR 0x27 //   modulo i2c complete Nxp 0x20
#define I2C_VEL 400

void caracteresESP();

int main(){
    stdio_init_all();

	uint8_t val = 0;
	LCDinit(I2C_PORT, I2C_SCL, I2C_SDA, I2C_VEL, I2C_DIR);
	caracteresESP();
	limpiaLCD();
	backlight_on();
	enviaCadena("Figuras ");
	enviaDato(':');
	enviaDato('D');
	cursorPosicion(0, 1);
	
	for(uint8_t j = 0 ; j < 8 ; j++){
		enviaDato(j);
	}

	sleep_ms(10000);
	limpiaLCD();
	enviaCadena("Hola mundo I2C");
	sleep_ms(2000);
	uint32_t contador = 0;
	dirDDRAM(0x40);
	enviaCadena("Cont: ");
	uint8_t posCont = posFinalLCD();

	dirDDRAM(15);
	enviaDato(0);
	//backlight_off();

	cursorPosicion(11, 1);
	enviaDato(1);

	while(1){
		dirDDRAM(posCont);
		imprimirInt(contador);
		contador++;	
		sleep_ms(500);
	}
    return 0;
}


void caracteresESP(){
	uint8_t fantasma[] = {0b00001110,
	    					  0b00010001,
	    					  0b00011011,
	    					  0b00010001,
	    					  0b00010001,
	    					  0b00011111,
	    					  0b00010101,
	    					  0b00000000
	      	};

	size_t tamFigura = sizeof(fantasma)/sizeof(fantasma[0]);

	if(caracterPersonalizado(0, fantasma, tamFigura) == 0){
		limpiaLCD();
	}

	uint8_t sonrisa[] = {0x00, 0x00, 0x0A, 0x00, 0x11, 0x0E, 0x00, 0x00};

	tamFigura = sizeof(sonrisa)/sizeof(sonrisa[0]);

		if(caracterPersonalizado(1, sonrisa, tamFigura) == 0){
			limpiaLCD();
		}

	uint8_t corazon[] = {0x00, 0x00, 0x0A, 0x15, 0x11, 0x0E, 0x04, 0x00};
	tamFigura = sizeof(corazon)/sizeof(corazon[0]);

			if(caracterPersonalizado(2, corazon, tamFigura) == 0){
				limpiaLCD();
			}


	uint8_t campana[] = {0x00, 0x04, 0x0E, 0x0E, 0x0E, 0x1F, 0x04, 0x00};
	tamFigura = sizeof(campana)/sizeof(campana[0]);

			if(caracterPersonalizado(3, campana, tamFigura) == 0){
				limpiaLCD();
			}


	uint8_t man[] = {0x04, 0x0a, 0x0e, 0x15, 0x0e, 0x04, 0x0a, 0x11};
	tamFigura = sizeof(man)/sizeof(man[0]);

			if(caracterPersonalizado(4, man, tamFigura) == 0){
				limpiaLCD();
			}


	uint8_t cuadricula[] = {0x15, 0x0a, 0x15, 0x0a, 0x15, 0x0a, 0x15, 0x0a};
	tamFigura = sizeof(cuadricula)/sizeof(cuadricula[0]);

			if(caracterPersonalizado(5, cuadricula, tamFigura) == 0){
				limpiaLCD();
			}

	uint8_t blue[] = {0x04, 0x16, 0x0d, 0x06, 0x06, 0x0d, 0x16, 0x04};
	tamFigura = sizeof(blue)/sizeof(blue[0]);

			if(caracterPersonalizado(6, blue, tamFigura) == 0){
				limpiaLCD();
			}

	uint8_t signal[] = {0x00, 0x00, 0x08, 0x14, 0x08, 0x0c, 0x0e, 0x0f};
	tamFigura = sizeof(signal)/sizeof(signal[0]);

			if(caracterPersonalizado(7, signal, tamFigura) == 0){
				limpiaLCD();
			}

}