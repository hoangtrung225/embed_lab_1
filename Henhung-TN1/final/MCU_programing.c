#include <at89x51.h>
sbit Led = P3^6;

void led_toggle(void);
void init_register(void);
void delay(void);
void matrix_led(void);

void main(void){
	init_register();
	matrix_led();
}

void init_register(void){
	EA = 1; //enable all interupt
	EX0 = 1; //enable external interrupt
	EX1 = 1;
	IT0 = 1; //interrupt type
	IT1 = 1;
}

void led_toggle(void){
	int i;
	Led = 0;
	for(i = 0; i < 20; i++){
		Led = ~Led;
		delay();
	}
}

void delay(void){
	int	i, j;
	for(i = 0; i < 100; i++)
		for(j = 0; j < 100; j++);
}

char segment_led[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F };
void led_segment(int number){
	P1 = segment_led[number];
	delay();
}

char matrix_number[] = {0xF8, 0x10, 0x20, 0x70, 0x08, 0x08, 0x08, 0xF0};
void matrix_led(void){
	int hang = 0x01;
	int i;
	for(i = 0; i < 8; i++){
		P0 = ~hang;
		P2 = matrix_number[i];
		delay();
		hang = hang << 1;	
	}
}
