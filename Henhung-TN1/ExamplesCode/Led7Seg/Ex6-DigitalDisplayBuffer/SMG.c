/***************************************************************************
标题：	数码管的显示
效果：	显示1234,缓冲显示
工作于：LY5A-L2A开发板
作者：	林洋电子-单片机
客服QQ：52927029
邮箱：	52927029@qq.com
******************************************************************************/
//头文件:
#include "reg51.h"

//变量定义:
code unsigned char table[]=
			{0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};
					//表：共阳数码管 0-9 
unsigned char l_disbuff[4]={1,2,3,4,};//显示缓冲
unsigned char l_posit=0;	//显示位置

//引脚定义:		
sbit SMG_q = P1^0;	//定义数码管阳级控制脚（千位）
sbit SMG_b = P1^1;	//定义数码管阳级控制脚（百位）
sbit SMG_s = P1^2;	//定义数码管阳级控制脚（十位）
sbit SMG_g = P1^3;	//定义数码管阳级控制脚（个位）

//函数声明:
void delay(unsigned int timer); //延时子函时
void display();		//显示

//主函数，C语言的入口函数:		
void main(void)  
{
	unsigned int i=10000,j=1000;
	while(1)			//不停的循环扫描,不扫描则不显示或显示不正确，即为动态显示,
	{
		display();		//调用显示缓冲内容
		delay(10);
	}
}

//延时子函数,短暂延时
void delay(unsigned int timer){		
	while(timer--);
}

//显示函数，参数为显示内容
void display()
{
	P0=0XFF;			//
	switch(l_posit){
	case 0:		//选择千位数码管，关闭其它位
		SMG_q=0;
		SMG_b=1;	
		SMG_s=1;		
		SMG_g=1;
		P0=table[l_disbuff[0]];	//输出显示内容
		break;
	case 1:		//选择百位数码管，关闭其它位
		SMG_q=1;
		SMG_b=0;	
		SMG_s=1;		
		SMG_g=1;
		P0=table[l_disbuff[1]];
		break;
	case 2:		//选择十位数码管，关闭其它位
		SMG_q=1;
		SMG_b=1;	
		SMG_s=0;		
		SMG_g=1;
		P0=table[l_disbuff[2]];
		break;
	case 3:		//选择个位数码管，关闭其它位
		SMG_q=1;
		SMG_b=1;	
		SMG_s=1;		
		SMG_g=0;
		P0=table[l_disbuff[3]];
		break;
	}
	l_posit++;		//每调用一次将轮流显示一位
	if(l_posit>3)
		l_posit=0;	
}
