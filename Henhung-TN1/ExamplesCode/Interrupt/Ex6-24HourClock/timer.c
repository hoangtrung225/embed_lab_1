/***************************************************************************
标题：	定时器中断 24小时时钟程序
效果：	数码管显示24小时制时钟
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
unsigned char ly_tt=0;		//作为计数时间量
unsigned char ly_miao=0;	//秒
unsigned char ly_fen=25;	//分
unsigned char ly_shi=12;	//时

//引脚定义:		
sbit SMG_q = P1^0;	//定义数码管阳级控制脚（千位）
sbit SMG_b = P1^1;	//定义数码管阳级控制脚（百位）
sbit SMG_s = P1^2;	//定义数码管阳级控制脚（十位）
sbit SMG_g = P1^3;	//定义数码管阳级控制脚（个位）

//函数声明:
void display(unsigned char shi,unsigned char fen);//定义显示函数，参数为显示时分
void delay(unsigned int timer); 
void init();					//初如化函数

//主函数，C语言的入口函数:	
void main()
{
	init();					//初始化中断控制寄存器
	while(1){
		if(ly_tt==20){			//20*50ms为1秒
			ly_tt=0;
			ly_miao++;
			if(ly_miao==60){
				ly_miao=0;
				ly_fen++;
				if(ly_fen==60){	//满60分清0
					ly_fen=0;
					ly_shi++;
					if(ly_shi==24)//满24小时清0
						ly_shi=0;
				}
			}
		}
		display(ly_shi,ly_fen);		//显示变量内容
		delay(100);
	}
}

//初始化函数
void init()
{
	ly_tt=0;
	TMOD=0X01;		//设置定时器1为模式一，即16位计算模式
	TH0=(65536-50000)/256;	//给计数寄存器赋值，50毫秒时间
	TL0=(65536-50000)%256;
	EA=1;		//开启总中断
	ET0=1;		//开启定时器0中断
	TR0=1;		//启动定时器
}

//中断函数,关键字"interrupt" ， 这是C语言的中断函数表示法，1表时定地器0
void timer() interrupt 1
{
	TH0=(65536-50000)/256;	//重新赋值
	TL0=(65536-50000)%256;
	ly_tt++;					//50毫秒计数
}

//显示函数，参数为显示内容
void display(unsigned char shi,unsigned char fen)
{
	P0=0XFF;			//	
	switch(l_posit){
	case 0:		//选择千位数码管，关闭其它位
		SMG_q=0;
		SMG_b=1;	
		SMG_s=1;		
		SMG_g=1;
		P0=table[shi/10];	//输出显示内容
		break;
	case 1:		//选择百位数码管，关闭其它位
		SMG_q=1;
		SMG_b=0;	
		SMG_s=1;		
		SMG_g=1;
		P0=table[shi%10];
		if(ly_tt>=10)
			P0&=0x7f;		//小数点以半秒的时间闪烁
		break;
	case 2:		//选择十位数码管，关闭其它位
		SMG_q=1;
		SMG_b=1;	
		SMG_s=0;		
		SMG_g=1;
		P0=table[fen/10];
		break;
	case 3:		//选择个位数码管，关闭其它位
		SMG_q=1;
		SMG_b=1;	
		SMG_s=1;		
		SMG_g=0;
		P0=table[fen%10];
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
