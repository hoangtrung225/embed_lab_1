/***************************************************************************
标题：	蜂鸣器实验-音乐程序
效果：	简单输出7个音符响声
工作于：LY5A-L2A开发板
作者：	林洋电子-单片机
客服QQ：52927029
邮箱：	52927029@qq.com
说明：	使用晶振12M
******************************************************************************/

//头文件:
#include "reg51.h"

//引脚定义:
sbit SPK  = P1^5;	//定义蜂鸣器

//数据定义:
code unsigned int lhj[]={//数组存放音符频率，两个字节组成一个音符数据
    0xf8,0x8b,        //1 do
    0xf9,0x5b,        //2 re
    0xfa,0x17,        //3 mi
    0xfa,0x6b,        //4 fa
    0xfb,0x07,        //5 suo
    0xfb,0x92,        //6 la
    0xfc,0x0d,        //7 xi
};
unsigned char ly_cc;	//用于数组索引

//函数定义:	
void init();		
void delay(unsigned int time); //延时子函时，

//主函数				
void main(void) 
{
	unsigned char i;
	init();
	while(1){//主程序循环 
		ly_cc=0;
		for(i=0;i<7;i++){		//循环7次输出音符do re mi fa suo la xi 
			TH0=lhj[ly_cc];
			TL0=lhj[ly_cc+1];			
			TR0=1;
			delay(50000);
			TR0=0;
			SPK=1;
			delay(30000);
			ly_cc+=2;			
		}
		delay(50000);
		delay(50000);
	}			
}

//初始化
void init()
{
	TMOD=0X01;
	EA=1;
	ET0=1;
	TR0=0;
}
//中断函数
void timer0() interrupt 1
{
	TH0=lhj[ly_cc];
	TL0=lhj[ly_cc+1];
	SPK=~SPK;
}
//延时子函数
void delay(unsigned int time)
{
	while(time--);
}
