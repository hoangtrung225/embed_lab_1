#include <at89x52.h>

unsigned int count = 1;
unsigned int tmp = 0;
unsigned int tmp1 = 0;
unsigned int tmp2 = 0;
unsigned int tmp3 = 0;
unsigned int animIndex = 1;
unsigned int tmp4 = 0;
unsigned int changemode = 0;
sbit D1 = P1^0;	//Led 7-seg 1 anot 
sbit D2 = P1^1;	//Led 7-seg 2 anot
sbit D3 = P1^2;	//Led 7-seg 3 anot
sbit D4 = P1^3;	//Led 7-seg 4 anot
unsigned int seg_count[] = {0x40,0xF9,0x24,0x30,0x19,0x12,0x02,0xF8,0x00,0x10};
void delay(int time)
{
	changemode = 0;
	while(time--)
	{
		if(changemode > 0)
		{
			return;
		}
	};
}

void AddIndex();
void forthAnim();
void thirdAnim();
void secondAnim();
void allled()
{
	P2 = 0x00;
}

void clearled()
{
	P2 = 0xFF;
}

void firstAnim()
{
	changemode = 0;
	allled();
	delay(20000);
	clearled();
	delay(20000);			
}

void secondAnim()
{
	int i = 0;
	changemode = 0;
	tmp = 0;
	for(i=0;i<8;i++)
	{
		if(changemode > 0)
		{
			return;
		}
		if(tmp == 0)
		{
			tmp = 0x80;
		}
		P2 = ~tmp;
		tmp = tmp >> 1;
		delay(20000);
	}
}


void thirdAnim()
{
	int i;
	changemode = 0;
	tmp1 = 0;
	for(i = 0; i < 8;i++)
	{
		if(changemode > 0)
		{
			return;
		}
		if(tmp1 == 0)
		{
			tmp1 = 0x01;
		}
		P2 = ~tmp1;
		tmp1 = tmp1 << 1;
		delay(20000);
	}
}

void forthAnim()
{
	int i = 0;
	changemode = 0;
	tmp2 = 0;
	tmp3 = 0;
	for(i = 0; i < 8;i++)
	{
		if(changemode > 0)
		{
			return;
		}
		if(tmp2 == 0)
		{
			tmp2 = 0x01;
		}
		if(tmp3 == 0)
		{
			tmp3 = 0x80;
		}
		tmp4 = tmp2 | tmp3;
		P2 = ~tmp4;
		tmp3 = tmp3 >> 1;
		tmp2 = tmp2 << 1;
		delay(20000);
	}
}
void display7LED();
void up_interrupt() interrupt 2
{
	changemode = 1;
	count++;
	if(count == 5)
	{
		count = 1;
	}
	//delay(10000);
}

void down_interrupt() interrupt 0
{
	changemode = 1;
	count--;
	if(count == 0)
	{
		count = 4;
	}
	//delay(10000);
}

void display7LED()
{
	//P1 = 0xF7;
	P0 = seg_count[count];
}

void main()
{
	EA = 1;
	EX0 = 1;
	EX1 = 1;
	IT0 = 1;
	IT1 = 1;
	while(1)
	{
		switch(count)
		{
			case 1:
			{
				firstAnim();
				break;
			}
			case 2:
			{
				secondAnim();
				break;
			}
			case 3:
			{
				thirdAnim();
				break;
			}
			case 4:
			{
				forthAnim();
				break;
			}
		}
		D1 = D2 = D3 = 0;
		D4 = 1;
		P0 = seg_count[count];
	}
	
}