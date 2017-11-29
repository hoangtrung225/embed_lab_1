/***************************************************************************
标题：	数码管的显示
效果：	显示00-99,动态显示+变化显示
工作于：LY5A-L2A开发板
作者：	林洋电子-单片机
客服QQ：52927029
邮箱：	52927029@qq.com
说明：	此例程将数码管显示内容用一个函数打包，要显示直接调用即可。
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
void display(unsigned char da);//定义显示函数，参数为显示内容，只显示两位数
void delay(void); 

//主函数，C语言的入口函数:			
void main(void)  
{
	unsigned char i=0;		//作为查表的索引号
	unsigned char ldata;	//变量用作0~99计数
	unsigned int j;			//此变量作为计数跳变刷新时间
	while(1)
	{	
		j=5000;			
		while(j--){		
			display(ldata);	//刷新5000次，约1秒，注：在C语言里是没有周期可计算的哦~~~
		}						
		if(ldata<99)
			ldata++;		//刷新完成约1秒，变量做加计数
		else
			ldata=0;
	}
}

//显示函数，参数为显示内容，只显示两位数
void display(unsigned char da)
{
	SMG_s=0;			//选择十位数码管
	P0=table[da/10];	//获取十位值，查表输出定义好的数码管段值与P0口，显示相应的0-9
	delay();			//延时
	P0=0XFF;			//清除数码管显示，因是共阳型，所以不是0
	SMG_s=1;			//关闭十位数码管

	SMG_g=0;			//选择个位数码管
	P0=table[da%10];	//获取个位值，查表输出定义好的数码管段值与P0口，显示相应的0-9
	delay();			//延时
	P0=0XFF;			//清除数码管显示，因是共阳型，所以不是0
	SMG_g=1;			//关闭个位数码管
}

//延时子函数,短暂延时
void delay(void){		
	unsigned char i=10;
	while(i--);
}
