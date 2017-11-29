/***************************************************************************
标题：	定时器中断秒计数
效果：	数码管做精确的秒计数00-99
工作于：LY5A-L2A开发板
作者：	林洋电子-单片机
客服QQ：52927029
邮箱：	52927029@qq.com
说明：	板使用12M晶振
******************************************************************************/

//头文件:
#include "reg51.h"

//变量定义:
code unsigned char table[]=
			{0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};
					//表：共阳数码管 0-9 

unsigned char l_posit=0;	//显示位置
int tt=0;	//作为计数时间量
int watch_enable = 0 ;

//引脚定义:		
sbit SMG_q = P1^0;	//定义数码管阳级控制脚（千位）
sbit SMG_b = P1^1;	//定义数码管阳级控制脚（百位）
sbit SMG_s = P1^2;	//定义数码管阳级控制脚（十位）
sbit SMG_g = P1^3;	//定义数码管阳级控制脚（个位）

//函数声明:
void display(unsigned int da);//定义显示函数，参数为显示内容
void delay(unsigned int timer); 

void init();					//初如化函数

//主函数，C语言的入口函数:	
void main()
{
	unsigned char bb=0;		//作为显示变量
	init();					//初始化中断控制寄存器
	while(1){
		while(watch_enable){
			if(tt > 9999){			//20*50MS定时时间为1秒
				tt=0;
			}
			display(tt);		//显示变量内容
			delay(100);
		}
		display(0);
		delay(100);
	}
}

//初始化函数
void init()
{
	tt=0;
	TMOD=0X01;		//设置定时器1为模式一，即16位计算模式
	TH0=(65536-10000)/256;	//给计数寄存器赋值，50毫秒时间
	TL0=(65536-10000)%256;
	EA=1;		//开启总中断
	ET0=1;		//开启定时器0中断
	TR0=1;		//启定定时器0
	//enable external interupt
	EX0=1;
	IT0=0;
	EX1=1;
	IT1=0;

}

//中断函数,关键字"interrupt" ， 这是C语言的中断函数表示法，1表时定地器0
void timer() interrupt 1
{
	TH0=(65536-10000)/256;	//重新赋值
	TL0=(65536-10000)%256;
	tt++;					//50毫秒加1，加20次为一秒
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
		//P0=0xff;
		P0=table[da/1000];	//输出显示内容
		break;
	case 1:		//选择百位数码管，关闭其它位
		SMG_q=1;
		SMG_b=0;	
		SMG_s=1;		
		SMG_g=1;
		//P0=0xff;
		P0=table[da%1000/100] + 0x80;
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

void interupt0_handler() interrupt 0
{
   watch_enable = 1;
}

void interupt1_handler() interrupt 2
{
   tt=0;
   watch_enable = 0;
}