#include <at89x52.h>

unsigned int count = 0;
unsigned int tmp = 0;
unsigned int tmp1 = 0;
unsigned int tmp2 = 0;
unsigned int tmp3 = 0;
unsigned int animIndex = 1;
unsigned int tmp4 = 0;
#define LED = P2;
void delay(int time)
{
	while(time--);
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
		allled();
		delay(20000);
		clearled();
		delay(20000);			
}

void secondAnim()
{
	int i = 0;
	tmp = 0;
	for(i=0;i<8;i++)
	{
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
	tmp1 = 0;
	for(i = 0; i < 8;i++)
	{
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
	tmp2 = 0;
	tmp3 = 0;
	for(i = 0; i < 8;i++)
	{
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

void main()
{
	int j;
	while(1)
	{
		for(j = 0; j < 20;j++)
		{
			if(j < 5)
			{
				firstAnim();
			}
			else if(j<10)
			{
				secondAnim();
			}
			else if(j<15)
			{
				thirdAnim();
			}
			else
			{
				forthAnim();
			}
		}
	}
}


