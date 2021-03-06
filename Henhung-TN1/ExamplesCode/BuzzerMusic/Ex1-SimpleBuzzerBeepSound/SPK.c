/***************************************************************************
标题：	蜂鸣器实验
效果：	简单驱动蜂鸣器蜂鸟报警
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
	while(1){				//主程序循环 
		SPK=0;
		delay(50000);		//开启蜂鸣延时
		delay(50000);
		SPK=1;
		delay(50000);		//关闭蜂鸣延时
		delay(50000);
	}			
}

//延时子函数
void delay(unsigned int time)
{
	while(time--);
}

