#include <stdio.h>
#include "pico/stdlib.h"


#define entradas 0x7FF
#define pines 0x7F
#define activador 0x0F//0x780
#define ascending 11
#define descending 12
#define pause 13

void sevenSegments(uint8_t num, uint16_t pins, uint8_t enable);
void multiplexing(uint16_t num, uint16_t segments, uint16_t timems);
void gpioInit();

int main()
{
    stdio_init_all();
	gpioInit();
 
    uint16_t contador = 0;
    uint8_t menu = 2;
	while(1){
		if(gpio_get(ascending) == 1){
			menu = 0;
		}

		if(gpio_get(descending) == 1){
			menu = 1;
		}

		if(gpio_get(pause) == 1){
			menu = 2;
		}


		switch(menu){
			case 0:
			 if(contador == 9999){
			 	contador = 0;
			 }
			 contador++;
			break;

			case 1:
			 if(contador == 0){
			 	contador = 9999;
			 }
			 contador--;
			break;
		}

		multiplexing(contador, entradas, 1000);
		
	}
	
    return 0;
}

void gpioInit(){
	///////////// in ///////////////////////
	// buttons for control the 7 segments counter
	gpio_init(ascending);
	gpio_init(descending);
	gpio_init(pause);

	// gpio as in's
	gpio_set_dir(ascending, GPIO_IN);
	gpio_set_dir(descending, GPIO_IN);
	gpio_set_dir(pause, GPIO_IN);

	// pull down resistence
	gpio_pull_down(ascending);
	gpio_pull_down(descending);
	gpio_pull_down(pause);	

	///////////// out //////////////////////

	// 7 Segments and control any display 
	gpio_init_mask(entradas);
	// set pins as outs
	gpio_set_dir_out_masked(entradas);

	
}

void sevenSegments(uint8_t num, uint16_t pins, uint8_t enable){
	const uint32_t numbers[] = {0b0111111, // 0
							   0b0000110, // 1
							   0b1011011, // 2
							   0b1001111, // 3
							   0b1100110, // 4
							   0b1101101, // 5
							   0b1111101, // 6
							   0b0000111, // 7
							   0b1111111, // 8
							   0b1101111, // 9
							   0b0000000 // vacio
							   };
	if(num <= 9){
		gpio_put_masked(pins, (numbers[num] | (enable << 7)));
	}else{
		gpio_put_masked(pins, (numbers[10] | (enable << 7)));
	}	
}



void multiplexing(uint16_t num, uint16_t segments, uint16_t timems){
	/*
		Considering that only manage unsigned numbers
		maximum value can support is 9,999
	*/
	
	uint8_t ones = 0;
	uint8_t tens = 0;
	uint8_t hundreds = 0;
	uint8_t ones_thousands = 0;
	uint16_t times = 0;
	
	const uint16_t tempo = 4;
	uint8_t shift = 0;
	
	ones = num % 10;
	tens = num % 100/10;
	hundreds = num % 1000/100;
	ones_thousands = num % 10000/1000;

	times = timems/(tempo*4);

	for(uint8_t i = 0 ; i < times ; i++){
		shift = 1;
		sevenSegments(ones, segments, shift);
		sleep_ms(tempo);

		shift = 2;
		sevenSegments(tens, segments, shift);
		sleep_ms(tempo);

		shift = 4;
		sevenSegments(hundreds, segments, shift);
		sleep_ms(tempo);

		shift = 8;
		sevenSegments(ones_thousands, segments, shift);
		sleep_ms(tempo);		
	}	
}

