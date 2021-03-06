/***************************************************************************
标题：	继电器启动
效果：	继电器动作
作者：	林洋电子-单片机
客服QQ：52927029
邮箱：	52927029@qq.com
******************************************************************************/

//头文件:
#include "reg51.h"

//IO引脚定义:
sbit JDQ=P1^4;    	//管脚定义 类似于起名字
					//用JDQ来代替P1.4控制继电器工作
//主函数，C语言的入口函数:			
void main(void) 
{
	JDQ=0;		//P1.4引脚控制三极管再由三极管控制继电器，
				//输出0三极管导通继电器得电吸合，输出1三极管截止继电器失电断开
	while(1){}	//主程序循环,即程序要停止在这里，很多初学者忘记了这点，只输入了上面一行，结果程序跑飞，找不出问题
}
