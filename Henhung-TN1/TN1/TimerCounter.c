#include <at89x52.h>

int count = 0;
int number = 0;
sbit D1 = P1^0;	//Led 7-seg 1 anot 
sbit D2 = P1^1;	//Led 7-seg 2 anot
sbit D3 = P1^2;	//Led 7-seg 3 anot
sbit D4 = P1^3;	//Led 7-seg 4 anot
int seg_count[] = {0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90};

void delay(unsigned int time)   
{	
	int i,j;
	for(i=0;i<255;i++)
		for(j=0;j<time;j++);
}

void timer_interrupt() interrupt TF0_VECTOR
{
	count++;
	if(count == 20) //20
	{
		count = 0;
		number++;
	}
	if(number == 100)
	{
		number = 0;
	}
}

void display(unsigned int number)
{
	D1 = D2 = D4 = 0;
	D3 = 1;
	P0 = 0xFF;
	P0 = seg_count[number / 10];
	delay(1);
	
	D1 = D2 = D3 = 0;
	D4 = 1;
	P0 = 0xFF;
	P0 = seg_count[number % 10];
	delay(1);
}

void setup_timer()
{
	TMOD = 0x01;
	ET0 = 1;
	TH0 = 0x3C;
	TL0 = 0xB0;
	TF0 = 0;
	TR0 = 1;
	while(TF0 == 0);
}

void main()
{
	D1 = D2 = 0;
	EA = 1;
	setup_timer();
	//TR0 = 1;
	while(1)
	{
		display(number);
	}
}