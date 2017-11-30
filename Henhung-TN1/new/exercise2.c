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

void dislay(int number){
		SMG_q=0;		//选择千位数码管
		P0=table[number];	//查找"1"定义好的数码管段值与P0口输出，显示相应的1
		delay(10);		//加入短暂延时
		P0=0XFF;		//清除数码管显示，因是共阳型，所以不是0
		SMG_q=1;		//关闭千位数码管
}

void led_toggle(void){
	dislay(current_function);
	P2 = 0x00;
	delay(10);
	dislay(current_function);
	P2 = ~P2;
	delay(10);
}

void led_to_left(void){
	int i;
	tmp = 0x01;
	for(i = 0; i < 8; i++){
		dislay(current_function);
		P2 = ~tmp;
		delay(10);
		tmp = tmp << 1;
	}
}

void led_to_right(void){
	int i;
	tmp = 0x80;
	for(i = 0; i < 8; i++){
		dislay(current_function);
		P2 = ~tmp;
		delay(10);
		tmp = tmp >> 1;
	}
}

void led_to_parallel(void){
	int i;
	for(i = 0; i < 4; i++){
		dislay(current_function);
		P2 = ~p[i];
		delay(10);
	}
}


int main(void){
	reg_init();
	while(1){
		
		switch (current_function){
			case 1:
				led_toggle();
				break;
			case 2:
				led_to_left();
				break;
			case 3:
				led_to_right();
				break;
			case 4:
				led_to_parallel();
				break;
			}
	}
}

void interupt0_handler() interrupt 0
{	EA =0;
	if (current_function <= 1)
		current_function = 4;
	else
   		current_function = current_function - 1;
	delay(100);
	EA = 1;
}

void interupt1_handler() interrupt 2
{	EA =0;
	if (current_function >= 4)
		current_function = 1;
	else
   		current_function = current_function + 1;
	delay(100);
	EA = 1;
}

