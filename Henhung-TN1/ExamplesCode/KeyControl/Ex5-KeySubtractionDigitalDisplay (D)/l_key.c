/***************************************************************************
标题：	键盘程序+数码管显示
效果：	按下按键，加(或减)数码管显示内容
工作于：LY5A-L2A开发板
作者：	林洋电子-单片机
客服QQ：52927029
邮箱：	52927029@qq.com
说明:	本程序直接采用分时扫描法，本板设计了5个按键，分别接于P13-P17引脚，按键都以接0方式触发（即按键另一脚接GND
******************************************************************************/
//头文件:
#include "reg51.h"

//变量定义:
unsigned char oldkey=0xff;	//保按键接口状态
//变量定义:
code unsigned char table[]=
			{0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};
					//表：共阳数码管 0-9 

unsigned char l_posit=0;	//显示位置
//引脚定义:	
sbit SMG_q = P1^0;	//定义数码管阳级控制脚（千位）
sbit SMG_b = P1^1;	//定义数码管阳级控制脚（百位）
sbit SMG_s = P1^2;	//定义数码管阳级控制脚（十位）
sbit SMG_g = P1^3;	//定义数码管阳级控制脚（个位）

sbit key1 = P3^7;	//定义按键1
sbit key2 = P3^6;	//定义按键2
sbit key3 = P3^5;	//定义按键3
sbit key4 = P3^4;	//定义按键4
sbit key5 = P3^3;	//定义按键5
sbit key6 = P3^2;	//定义按键6

//函数声明:
void display(unsigned int da);//定义显示函数，参数为显示内容
unsigned char ReadKey(void);	//读键值返回
void delay(unsigned int timer); 

//主函数，C语言的入口函数:	
void main(void)
{
	unsigned int ldata=0;		//作为显示的数据
	unsigned char lold=1;		//作为按键放开的凭证，1为放开，0为按下
	while(1){					//循环扫描按键及显示
		switch(ReadKey()){		//读取键值做以下相应处理
		case 1:ldata++;			//1键显示内容加1
			break;
		case 2:ldata--;			//2键显示内容减1
			break;
		case 3:ldata+=10;		//3键显示内容加10
			break;
		case 4:ldata-=10;		//4键显示内容减10
			break;
		case 5:ldata+=100;			//5键显示内容清0
			break;
		case 6:ldata-=100;		//6键显示内容最大
			break;
		}		
		display(ldata);		//显示相应的数值，这里用函数的形式调用显示
		delay(100);
	}
}
unsigned char ReadKey(void)	//读键值
{
	unsigned char lkey=0;
	if((P3&0xfc)!=0xfc){	//检测所有按键是否有按键按下	
		delay(10);			//有按键按下则延时一段时间，以消除按键拌动
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
		oldkey=0xfc;			//如果都没有按键按下，将复值初始状态
	}
	return lkey;
}

//显示函数，参数为显示内容
void display(unsigned int da)
{
	P0=0XFF;			//
	da=da%10000;
	switch(l_posit){
	case 0:		//选择千位数码管，关闭其它位
		SMG_q=0;
		SMG_b=1;	
		SMG_s=1;		
		SMG_g=1;
		P0=table[da/1000];	//输出显示内容
		break;
	case 1:		//选择百位数码管，关闭其它位
		SMG_q=1;
		SMG_b=0;	
		SMG_s=1;		
		SMG_g=1;
		P0=table[da%1000/100];
		break;
	case 2:		//选择十位数码管，关闭其它位
		SMG_q=1;
		SMG_b=1;	
		SMG_s=0;		
		SMG_g=1;
		P0=table[da%100/10];
		break;
	case 3:		//选择个位数码管，关闭其它位
		SMG_q=1;
		SMG_b=1;	
		SMG_s=1;		
		SMG_g=0;
		P0=table[da%10];
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

