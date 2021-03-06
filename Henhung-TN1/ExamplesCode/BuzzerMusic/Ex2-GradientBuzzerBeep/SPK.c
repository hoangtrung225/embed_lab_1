/***************************************************************************
标题：	蜂鸣器实验
效果：	影片里可以听到的定时弹快要爆炸时定时器发出的声音
工作于：LY5A-L2A开发板
作者：	林洋电子-单片机
客服QQ：52927029
邮箱：	52927029@qq.com
******************************************************************************/

//头文件:
#include "reg51.h"

//引脚定义:
sbit SPK  = P1^5;	//定义蜂鸣器

//函数定义:			
void delay(unsigned int time); //延时子函时，

//主函数，C语言的入口函数:					
void main(void) 
{
	unsigned int tt;		//作为延时量
	unsigned char i;	

	while(1){				//主程序循环 
		tt=60000;		
		for(i=0;i<30;i++){	//循环30次输出，时间从长渐变到短
			SPK=0;
			delay(tt);
			SPK=1;
			delay(tt);
			tt-=2000;		//每循环一次时间量减2000
		}
		SPK=1;				//关闭蜂响器，
		delay(50000);		//等待一会再开始循环
		delay(50000);
		delay(50000);
	}			
}

//延时子函数
void delay(unsigned int time)
{
	while(time--);
}

