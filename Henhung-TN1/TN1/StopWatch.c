#include <at89x52.h>

int count = 0;
int number = 0;
sbit D1 = P1^0;	//Led 7-seg 1 anot 
sbit D2 = P1^1;	//Led 7-seg 2 anot
sbit D3 = P1^2;	//Led 7-seg 3 anot
sbit D4 = P1^3;	//Led 7-seg 4 anot
int seg_count[] = {0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90};
int seg_dot_count[] = {0x40,0x79,0x24,0x30,0x19,0x12,0x02,0x78,0x00,0x10};
void delay(unsigned int time)   
{	
	int i,j;
	for(i=0;i<255;i++)
		for(j=0;j<time;j++);
}

void timer_interrupt() interrupt TF0_VECTOR
{
	count++;
	if(count == 10000) //20
	{
		count = 0;
	}
}

void button_start() interrupt IE0_VECTOR
{
	TR0 = 1;
}

void button_stop() interrupt IE1_VECTOR
{
	TR0 = 0;
}

void display(unsigned int number)
{	
	D1 = D2 = D3 = 0;
	D4 = 1;
	P0 = 0xFF;
	P0 = seg_count[number % 10];
	delay(1);
	
	number = number/10;
	D1 = D2 = D4 = 0;
	D3 = 1;
	P0 = 0xFF;
	P0 = seg_count[number % 10];
	delay(1);
	
	number = number / 10;
	D1 = D3 = D4 = 0;
	D2 = 1;
	P0 = 0xFF;
	P0 = seg_dot_count[number % 10];
	delay(1);
	
	number = number / 10;
	D2 = D3 = D4 = 0;
	D1 = 1;
	P0 = 0xFF;
	P0 = seg_count[number];
	delay(1);
}

void setup_interrupt()
{
	EX0 = 1;
	IT0 = 1;
	EX1 = 1;
	IT1 = 1;
}

void setup_timer()
{
	TMOD = 0x01;
	ET0 = 1;
	TH0 = 0xD8; //10ms
	TL0 = 0xF0;
	TF0 = 0;
	TR0 = 1;
	while(TF0 == 0);
}

void main()
{
	EA = 1;
	setup_timer();
	setup_interrupt();
	while(1)
	{
		display(count);
	}
}