/***************************************************************************
标题：	键盘+蜂鸣器
效果：	按键扫描且有键按下发声
工作于：LY5A-L2A开发板
作者：	林洋电子-单片机
客服QQ：52927029
邮箱：	52927029@qq.com
******************************************************************************/

//头文件:
#include "reg51.h"

//变量定义:
unsigned char oldkey=0xff;	//保存按键接口状态

//引脚定义:
sbit SPK  = P1^5;	//定义蜂鸣器
sbit key1 = P3^7;	//定义按键1
sbit key2 = P3^6;	//定义按键2
sbit key3 = P3^5;	//定义按键3
sbit key4 = P3^4;	//定义按键4
sbit key5 = P3^3;	//定义按键5
sbit key6 = P3^2;	//定义按键6

//函数定义:			
void delay(unsigned int time); //延时子函时，
unsigned char ReadKey(void);	//读键值返回

//主函数，C语言的入口函数:					
void main(void) 
{
	while(1){				//主程序循环 
		ReadKey();	//调用键盘扫描，测试按键发声
	}			
}

//扫描键盘
unsigned char ReadKey(void)	
{
	unsigned char lkey=0;
	if((P3&0xfc)!=0xfc){	//检测所有按键是否有按键按下

		SPK=0;				//按键按下则蜂鸣器发声

		delay(100);			//有按键按下则延时一段时间，以消除按键拌动
		if(oldkey!=(P3&0xfc)){//检测按键未松开而且不是之前按下的按健就进入读键值，否则不作处理
			oldkey=P3&0xfc;		//保存当前状态，为下一次扫描做判断，请看上一行		
			if(key1==0)
				lkey=1;		//第一个键按下复值1
			else if(key2==0)
				lkey=2;		//第二个键按下复值2
			else if(key3==0)
				lkey=3;		//第三个键按下复值3
			else if(key4==0)
				lkey=4;		//第四个键按下复值4
			else if(key5==0)
				lkey=5;		//第五个键按下复值5
			else if(key6==0)
				lkey=6;		//第六个键按下复值6
		}
	}
	else{
		oldkey=0xfc;		//如果都没有按键按下，将复值初始状态

		SPK=1;				//无按键按下则退出蜂鸣
	}
	return lkey;
}

//延时子函数
void delay(unsigned int time)
{
	while(time--);
}
