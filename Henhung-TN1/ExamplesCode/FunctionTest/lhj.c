/***************************************************************************
标题：	板子测试自检测试程序
效果：	自检1、LED灯轮流点阵，2、数友管轮流点亮，3、蜂鸣器自检，4、继电器自检，5、按键测试，数码管显示输入值
工作于：LY5A-L2A开发板
作者：	林洋电子-单片机
客服QQ：52927029
邮箱：	52927029@qq.com
******************************************************************************/
#include "reg51.h"

//global variables:
code unsigned char table[]=
			{0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};
					//led 7-seg output data 0-9 

unsigned char l_posit=0;	//choose led 7-seg position	
unsigned char oldkey=0xff;	//push button data (release status)

//Define led 7-seg anot control (on/off):	
sbit SMG_q = P1^0;	//Led 7-seg 1 anot 
sbit SMG_b = P1^1;	//Led 7-seg 2 anot
sbit SMG_s = P1^2;	//Led 7-seg 3 anot
sbit SMG_g = P1^3;	//Led 7-seg 4 anot

//Buzzer (speaker) connects on P1^5 
sbit SPK  = P1^5;	//Buzzer on/off
//Relay connects on P1^4
sbit JDQ  = P1^4;	//Relay on/off

//Define 6 push buttons on Port P3
sbit key1 = P3^7;	//Push button 1
sbit key2 = P3^6;	//Push button 2
sbit key3 = P3^5;	//Push button 3
sbit key4 = P3^4;	//Push button 4
sbit key5 = P3^3;	//Push button 5
sbit key6 = P3^2;	//Push button 6
			
/***************/
//Delay 0-65536
void delay(unsigned int time)   
{							    
	while(time--);
}
/***************/
/* Display led 7 segment
Port P0 connects 4 led 7 segment (LED 4*8)
P0^0->P0^7 = ABCDEFGH
P1^0->P1^3 = Anot 1->4
*/
void display(unsigned int da)
{
	P0=0XFF;			//Port 0 data off
	da=da%10000;	 	//output data for led 7-seg (4-digits)
	switch(l_posit){
	case 0:		//choose led 7-seg 1
		SMG_q=0;
		SMG_b=1;	
		SMG_s=1;		
		SMG_g=1;
		P0=table[da/1000];	//Chu so hang nghin
		break;
	case 1:		//choose led 7-seg 2
		SMG_q=1;
		SMG_b=0;	
		SMG_s=1;		
		SMG_g=1;
		P0=table[da%1000/100]; //Chu so hang tram
		break;
	case 2:		//choose led 7-seg 3
		SMG_q=1;
		SMG_b=1;	
		SMG_s=0;		
		SMG_g=1;
		P0=table[da%100/10];  //Chu so hang chuc
		break;
	case 3:		//choose led 7-seg 4
		SMG_q=1;
		SMG_b=1;	
		SMG_s=1;		
		SMG_g=0;
		P0=table[da%10];	 //Chu so hang don vi
		break;
	}
	l_posit++;		//turn around
	if(l_posit>3)
		l_posit=0;	
}
//Read buttons 1-> 6 on P3
unsigned char ReadKey(void)	
{
	unsigned char lkey=0;
	if((P3&0xfc)!=0xfc){	//if any buttons pressed

		SPK=0;				//turn on buzzer

		delay(10);			//delay for buzzer pusle
		if(oldkey!=(P3&0xfc)){//if any buttons pressed
			oldkey=P3&0xfc;		//update buttons values		
			if(key1==0)
				lkey=1;		//press button 1
			else if(key2==0)
				lkey=2;		//press button 2
			else if(key3==0)
				lkey=3;		//press button 3
			else if(key4==0)
				lkey=4;		//press button 4
			else if(key5==0)
				lkey=5;		//press button 5
			else if(key6==0)
				lkey=6;		//press button 6
		}
	}
	else{
		oldkey=0xfc;		//default data of buttons port

		SPK=1;				//turn off buzzer
	}
	return lkey;
}

//Chuong trinh chinh				
void main(void) 
{
	unsigned int ldata=1234;		//led-7seg 4 digits data 
	unsigned char i;
		for(i=0;i<8;i++){
			P2<<=1;		//shift left all leds		
			delay(50000);
		}
		P2=0xff;		//all LED off
		
		P0=0;			//Port 0 connect LCD
		SMG_g=0;		//turn on leg 7-seg 4
		delay(50000);
		SMG_g=1;		//turn off leg 7-seg 4

		SMG_s=0;		//turn on leg 7-seg 3
		delay(50000);
		SMG_s=1;		//turn off leg 7-seg 3

		SMG_b=0;		//turn on leg 7-seg 2
		delay(50000);
		SMG_b=1;		//turn off leg 7-seg 2

		SMG_q=0;		//turn on leg 7-seg 1
		delay(50000);
		SMG_q=1;		////turn off leg 7-seg 1
		
		SPK=0;			//buzzer on
		delay(50000);
		SPK=1;			//buzzer off

		JDQ=0;			//relay on
		delay(50000);
		JDQ=1;			//relay off
	
	while(1){					//loop forever
		
		//P2 = 0x55;				//8 leds on Port 2
		switch(ReadKey()){		//Polling push buttons
		case 1:ldata++;			//button 1 pressed
			break;
		case 2:ldata--;			//button 2 pressed
			break;
		case 3:ldata+=10;		//button 3 pressed
			break;
		case 4:ldata-=10;		//button 4 pressed
			break;
		case 5:ldata+=100;		//button 5 pressed
			break;
		case 6:ldata-=100;		//button 6 pressed
			break;
		}		
		display(ldata);		//display 4 digits led 7-seg
		delay(100);

	}
}
