/***************************************************************************
标题：	键盘程序+数码管显示
效果：	按下按键，加(或减)数码管显示内容
工作于：LY5A-L2A开发板
作者：	林洋电子-单片机
客服QQ：52927029
邮箱：	52927029@qq.com
说明:	本程序直接采用分时扫描法，本板设计了5个按键，分别接于P13-P17引脚，按键都以接0方式触发（即按键另一脚接GND
******************************************************************************/
//头文件:
#include "reg51.h"

//变量定义:
code unsigned char table[]=
			{0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};
					//表：共阳数码管 0-9 

unsigned char l_posit=0;	//显示位置

//引脚定义:	
sbit SMG_q = P1^0;	//定义数码管阳级控制脚（千位）
sbit SMG_b = P1^1;	//定义数码管阳级控制脚（百位）
sbit SMG_s = P1^2;	//定义数码管阳级控制脚（十位）
sbit SMG_g = P1^3;	//定义数码管阳级控制脚（个位）

sbit key1 = P3^7;	//定义按键1
sbit key2 = P3^6;	//定义按键2
sbit key3 = P3^5;	//定义按键3
sbit key4 = P3^4;	//定义按键4
sbit key5 = P3^3;	//定义按键5
sbit key6 = P3^2;	//定义按键6

//函数声明:
void display(unsigned int da);//定义显示函数，参数为显示内容
void delay(unsigned int timer); 

//主函数，C语言的入口函数:	
void main(void)
{
	unsigned char ldata=0;		//作为显示的数据
	unsigned char lold=1;		//作为按键放开的凭证，1为放开，0为按下
	while(1){				//循环扫描按键及显示
		if(key1==0){		//按键1按下
			if(lold){		//是否是刚按下,是执行，否则不执行
				ldata++;	//显示数据加1
				lold=0;		//处理完，将按键视为按下
			}
		}
		else if(key2==0){	//按键2按下
			if(lold){		//是否是刚按下,是执行，否则不执行
				ldata--;	//显示数据减1
				lold=0;		////处理完，将按键视为按下
			}
		}
		else if(key3==0){	//按键3按下
			if(lold){		//是否是刚按下,是执行，否则不执行
				ldata+=10;	//显示数据加1
				lold=0;		//处理完，将按键视为按下
			}
		}
		else if(key4==0){	//按键4按下
			if(lold){		//是否是刚按下,是执行，否则不执行
				ldata-=10;	//显示数据减10
				lold=0;		//处理完，将按键视为按下
			}
		}
		else if(key5==0){	//按键5按下
			if(lold){		//是否是刚按下,是执行，否则不执行
				ldata=0;	//清0
				lold=0;		//处理完，将按键视为按下
			}
		}
		else
			lold=1;			//如果都没有按键按下，将复值1

		display(ldata);		//显示相应的数值，这里用函数的形式调用显示
		delay(100);
	}
}
//显示函数，参数为显示内容
void display(unsigned int da)
{
	P0=0XFF;			//
	da=da%10000;
	switch(l_posit){
	case 0:		//选择千位数码管，关闭其它位
		SMG_q=0;
		SMG_b=1;	
		SMG_s=1;		
		SMG_g=1;
		P0=table[da/1000];	//输出显示内容
		break;
	case 1:		//选择百位数码管，关闭其它位
		SMG_q=1;
		SMG_b=0;	
		SMG_s=1;		
		SMG_g=1;
		P0=table[da%1000/100];
		break;
	case 2:		//选择十位数码管，关闭其它位
		SMG_q=1;
		SMG_b=1;	
		SMG_s=0;		
		SMG_g=1;
		P0=table[da%100/10];
		break;
	case 3:		//选择个位数码管，关闭其它位
		SMG_q=1;
		SMG_b=1;	
		SMG_s=1;		
		SMG_g=0;
		P0=table[da%10];
		break;
	}
	l_posit++;		//每调用一次将轮流显示一位
	if(l_posit>3)
		l_posit=0;	
}
//延时子函数,短暂延时
void delay(unsigned int timer){		
	while(timer--);
}
