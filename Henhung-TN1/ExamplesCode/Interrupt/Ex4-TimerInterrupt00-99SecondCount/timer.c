/***************************************************************************
���⣺	��ʱ���ж������
Ч����	���������ȷ�������00-99
�����ڣ�LY5A-L2A������
���ߣ�	�������-��Ƭ��
�ͷ�QQ��52927029
���䣺	52927029@qq.com
˵����	��ʹ��12M����
******************************************************************************/

//ͷ�ļ�:
#include "reg51.h"

//��������:
code unsigned char table[]=
			{0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};
					//����������� 0-9 

unsigned char l_posit=0;	//��ʾλ��
int tt=0;	//��Ϊ����ʱ����
int watch_enable = 0 ;

//���Ŷ���:		
sbit SMG_q = P1^0;	//����������������ƽţ�ǧλ��
sbit SMG_b = P1^1;	//����������������ƽţ���λ��
sbit SMG_s = P1^2;	//����������������ƽţ�ʮλ��
sbit SMG_g = P1^3;	//����������������ƽţ���λ��

//��������:
void display(unsigned int da);//������ʾ����������Ϊ��ʾ����
void delay(unsigned int timer); 

void init();					//���绯����

//��������C���Ե���ں���:	
void main()
{
	unsigned char bb=0;		//��Ϊ��ʾ����
	init();					//��ʼ���жϿ��ƼĴ���
	while(1){
		while(watch_enable){
			if(tt > 9999){			//20*50MS��ʱʱ��Ϊ1��
				tt=0;
			}
			display(tt);		//��ʾ��������
			delay(100);
		}
		display(0);
		delay(100);
	}
}

//��ʼ������
void init()
{
	tt=0;
	TMOD=0X01;		//���ö�ʱ��1Ϊģʽһ����16λ����ģʽ
	TH0=(65536-10000)/256;	//�������Ĵ�����ֵ��50����ʱ��
	TL0=(65536-10000)%256;
	EA=1;		//�������ж�
	ET0=1;		//������ʱ��0�ж�
	TR0=1;		//������ʱ��0
	//enable external interupt
	EX0=1;
	IT0=0;
	EX1=1;
	IT1=0;

}

//�жϺ���,�ؼ���"interrupt" �� ����C���Ե��жϺ�����ʾ����1��ʱ������0
void timer() interrupt 1
{
	TH0=(65536-10000)/256;	//���¸�ֵ
	TL0=(65536-10000)%256;
	tt++;					//50�����1����20��Ϊһ��
}

//��ʾ����������Ϊ��ʾ����
void display(unsigned int da)
{
	P0=0XFF;			//
	da=da%10000;
	switch(l_posit){
	case 0:		//ѡ��ǧλ����ܣ��ر�����λ
		SMG_q=0;
		SMG_b=1;	
		SMG_s=1;		
		SMG_g=1;
		//P0=0xff;
		P0=table[da/1000];	//�����ʾ����
		break;
	case 1:		//ѡ���λ����ܣ��ر�����λ
		SMG_q=1;
		SMG_b=0;	
		SMG_s=1;		
		SMG_g=1;
		//P0=0xff;
		P0=table[da%1000/100] + 0x80;
		break;
	case 2:		//ѡ��ʮλ����ܣ��ر�����λ
		SMG_q=1;
		SMG_b=1;	
		SMG_s=0;		
		SMG_g=1;
		P0=table[da%100/10];
		break;
	case 3:		//ѡ���λ����ܣ��ر�����λ
		SMG_q=1;
		SMG_b=1;	
		SMG_s=1;		
		SMG_g=0;
		P0=table[da%10];
		break;
	}
	l_posit++;		//ÿ����һ�ν�������ʾһλ
	if(l_posit>3)
		l_posit=0;	
}
//��ʱ�Ӻ���,������ʱ
void delay(unsigned int timer){		
	while(timer--);
}

void interupt0_handler() interrupt 0
{
   watch_enable = 1;
}

void interupt1_handler() interrupt 2
{
   tt=0;
   watch_enable = 0;
}