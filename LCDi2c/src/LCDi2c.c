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

int main(){
    stdio_init_all();

	uint8_t val = 0;
	LCDinit(I2C_PORT, I2C_SCL, I2C_SDA, I2C_VEL, I2C_DIR);
	enviaDato(':');
	enviaDato('D');
	sleep_ms(2000);
	limpiaLCD();
	enviaCadena("Hola mundo I2C");
	sleep_ms(2000);
	uint32_t contador = 0;
	dirDDRAM(0x40);
	enviaCadena("Cont: ");
	uint8_t posCont = posFinalLCD();

	uint8_t figura[] = {0b00001110,
						0b00010001,
						0b00011011,
						0b00010001,
						0b00010001,
						0b00011111,
						0b00010101,
						0b00000000
	};

	size_t tamFigura = sizeof(figura)/sizeof(figura[0]);

	if(caracterPersonalizado(0, figura, tamFigura) == 0){
		limpiaLCD();
	}
	dirDDRAM(15);
	enviaDato(0);
	
	while(1){
		dirDDRAM(posCont);
		imprimirInt(contador);
		contador++;	
		sleep_ms(500);
	}
    return 0;
}


