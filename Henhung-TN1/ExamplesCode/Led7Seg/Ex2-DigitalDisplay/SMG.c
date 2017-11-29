/***************************************************************************
标题：	数码管的显示
效果：	静态显示一位数码管,显示0-9
工作于：LY5A-L2A开发板
作者：	林洋电子-单片机
客服QQ：52927029
邮箱：	52927029@qq.com
******************************************************************************/
//头文件:
#include "reg51.h"

//变量定义:
unsigned char table[]=
			{0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};
					//表：共阳数码管 0-9 
//引脚定义:		
sbit SMG_q = P1^0;	//定义数码管阳级控制脚（千位）
sbit SMG_b = P1^1;	//定义数码管阳级控制脚（百位）
sbit SMG_s = P1^2;	//定义数码管阳级控制脚（十位）
sbit SMG_g = P1^3;	//定义数码管阳级控制脚（个位）

//函数声明:
void delay(unsigned int d_time); //延时子函时，

//主函数，C语言的入口函数:		
void main(void)  
{
	unsigned char i;		//定义循环变量
	while(1)
	{
		SMG_q=0;			//选择千位数码管，这是静态显示，P0口输出显示，不需要刷新，也可选择百位、十位或个位;
							//也可两位或全部同时输出显示
		for(i=0;i<10;i++)	//循环显示0-9
		{		
			P0=table[i];	//查表输出数码管段值给P0口，显示相应的0-9
			delay(500);		//延时
		}
	}
}

//延时子函数,参数范围 0-65536
void delay(unsigned int tmp)
{
	unsigned char j;
	while(tmp--){		
		j=255;
		while(j--); 	    	
	}
}
