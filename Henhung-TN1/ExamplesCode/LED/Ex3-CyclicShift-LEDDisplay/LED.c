/***************************************************************************
标题：	循环移位LED显示
效果：	循环移位LED显示
工作于：LY5A-L2A开发板
作者：	林洋电子-单片机
客服QQ：52927029
邮箱：	52927029@qq.com
******************************************************************************/

//头文件:
#include "reg51.h"

//函数声明:
void delay(unsigned char tmp);//延时子函数

//主函数，C语言的入口函数:	
void main(void)
{
	P2=0XFE;
	while(1){				//无限循环
		P2=(P2<<1)|(P2>>7);	//P2口值左循环移1位，也可利用函数库"intrins.h"中的_crol_(),
		delay(50);			//调用延时子函数，改变参数大小，调整变化速度
	}
}

//延时子函数
void delay(unsigned char tmp)//双重循环减，如改用INT型，将会达到更长的延时时间
{
	unsigned char j;
	while(tmp--){
		j=255;
		while(j--);
	}
}
