#include "reg51.h"
unsigned char table[]=
			{0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};
unsigned char p[] = {0x81, 0x42, 0x24, 0x18};
int i, j, tmp;
int current_function  = 4;
sbit SMG_q = P1^0;
void reg_init(void){
	SMG_q=0;
	EA =1;
	EX0 = 1;
	IT0 = 0;
	EX1 = 1;
	IT1 = 0;
}

void delay(int time){
	int i;
	for(i = 0; i < 255; i++)
		for(j = 0; j < time; j++);
}


void led_toggle(void){
	P2 = 0x00;
	delay(10);
	P2 = ~P2;
	delay(10);
}

void led_to_left(void){
	int i;
	tmp = 0x01;
	for(i = 0; i < 8; i++){
		P2 = ~tmp;
		delay(10);
		tmp = tmp << 1;
	}
}

void led_to_right(void){
	int i;
	tmp = 0x80;
	for(i = 0; i < 8; i++){
		P2 = ~tmp;
		delay(10);
		tmp = tmp >> 1;
	}
}

void led_to_parallel(void){
	int i;
	for(i = 0; i < 4; i++){
		P2 = ~p[i];
		delay(10);
	}
}


int main(void){
	int i;
	reg_init();
	while(1){
		
		for(i = 0; i < 5; i++){
			led_toggle();
		}
		for(i = 0; i < 5; i++){
			led_to_left();
		}
		for(i = 0; i < 5; i++){
			led_to_right();
		}
		for(i = 0; i < 5; i++){
			led_to_parallel();
		}
	}
}



