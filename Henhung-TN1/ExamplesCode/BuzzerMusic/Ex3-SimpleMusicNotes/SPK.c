/***************************************************************************
���⣺	������ʵ��-���ֳ���
Ч����	�����7����������
�����ڣ�LY5A-L2A������
���ߣ�	�������-��Ƭ��
�ͷ�QQ��52927029
���䣺	52927029@qq.com
˵����	ʹ�þ���12M
******************************************************************************/

//ͷ�ļ�:
#include "reg51.h"

//���Ŷ���:
sbit SPK  = P1^5;	//���������

//���ݶ���:
code unsigned int lhj[]={//����������Ƶ�ʣ������ֽ����һ����������
    0xf8,0x8b,        //1 do
    0xf9,0x5b,        //2 re
    0xfa,0x17,        //3 mi
    0xfa,0x6b,        //4 fa
    0xfb,0x07,        //5 suo
    0xfb,0x92,        //6 la
    0xfc,0x0d,        //7 xi
};
unsigned char ly_cc;	//������������

//��������:	
void init();		
void delay(unsigned int time); //��ʱ�Ӻ�ʱ��

//������				
void main(void) 
{
	unsigned char i;
	init();
	while(1){//������ѭ�� 
		ly_cc=0;
		for(i=0;i<7;i++){		//ѭ��7���������do re mi fa suo la xi 
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

//��ʼ��
void init()
{
	TMOD=0X01;
	EA=1;
	ET0=1;
	TR0=0;
}
//�жϺ���
void timer0() interrupt 1
{
	TH0=lhj[ly_cc];
	TL0=lhj[ly_cc+1];
	SPK=~SPK;
}
//��ʱ�Ӻ���
void delay(unsigned int time)
{
	while(time--);
}
