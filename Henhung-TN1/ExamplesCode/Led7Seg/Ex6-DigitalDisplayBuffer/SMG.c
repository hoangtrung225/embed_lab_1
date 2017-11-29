/***************************************************************************
���⣺	����ܵ���ʾ
Ч����	��ʾ1234,������ʾ
�����ڣ�LY5A-L2A������
���ߣ�	�������-��Ƭ��
�ͷ�QQ��52927029
���䣺	52927029@qq.com
******************************************************************************/
//ͷ�ļ�:
#include "reg51.h"

//��������:
code unsigned char table[]=
			{0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};
					//����������� 0-9 
unsigned char l_disbuff[4]={1,2,3,4,};//��ʾ����
unsigned char l_posit=0;	//��ʾλ��

//���Ŷ���:		
sbit SMG_q = P1^0;	//����������������ƽţ�ǧλ��
sbit SMG_b = P1^1;	//����������������ƽţ���λ��
sbit SMG_s = P1^2;	//����������������ƽţ�ʮλ��
sbit SMG_g = P1^3;	//����������������ƽţ���λ��

//��������:
void delay(unsigned int timer); //��ʱ�Ӻ�ʱ
void display();		//��ʾ

//��������C���Ե���ں���:		
void main(void)  
{
	unsigned int i=10000,j=1000;
	while(1)			//��ͣ��ѭ��ɨ��,��ɨ������ʾ����ʾ����ȷ����Ϊ��̬��ʾ,
	{
		display();		//������ʾ��������
		delay(10);
	}
}

//��ʱ�Ӻ���,������ʱ
void delay(unsigned int timer){		
	while(timer--);
}

//��ʾ����������Ϊ��ʾ����
void display()
{
	P0=0XFF;			//
	switch(l_posit){
	case 0:		//ѡ��ǧλ����ܣ��ر�����λ
		SMG_q=0;
		SMG_b=1;	
		SMG_s=1;		
		SMG_g=1;
		P0=table[l_disbuff[0]];	//�����ʾ����
		break;
	case 1:		//ѡ���λ����ܣ��ر�����λ
		SMG_q=1;
		SMG_b=0;	
		SMG_s=1;		
		SMG_g=1;
		P0=table[l_disbuff[1]];
		break;
	case 2:		//ѡ��ʮλ����ܣ��ر�����λ
		SMG_q=1;
		SMG_b=1;	
		SMG_s=0;		
		SMG_g=1;
		P0=table[l_disbuff[2]];
		break;
	case 3:		//ѡ���λ����ܣ��ر�����λ
		SMG_q=1;
		SMG_b=1;	
		SMG_s=1;		
		SMG_g=0;
		P0=table[l_disbuff[3]];
		break;
	}
	l_posit++;		//ÿ����һ�ν�������ʾһλ
	if(l_posit>3)
		l_posit=0;	
}
