/***************************************************************************
���⣺	��ʱ���ж� 24Сʱʱ�ӳ���
Ч����	�������ʾ24Сʱ��ʱ��
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
unsigned char ly_tt=0;		//��Ϊ����ʱ����
unsigned char ly_miao=0;	//��
unsigned char ly_fen=25;	//��
unsigned char ly_shi=12;	//ʱ

//���Ŷ���:		
sbit SMG_q = P1^0;	//����������������ƽţ�ǧλ��
sbit SMG_b = P1^1;	//����������������ƽţ���λ��
sbit SMG_s = P1^2;	//����������������ƽţ�ʮλ��
sbit SMG_g = P1^3;	//����������������ƽţ���λ��

//��������:
void display(unsigned char shi,unsigned char fen);//������ʾ����������Ϊ��ʾʱ��
void delay(unsigned int timer); 
void init();					//���绯����

//��������C���Ե���ں���:	
void main()
{
	init();					//��ʼ���жϿ��ƼĴ���
	while(1){
		if(ly_tt==20){			//20*50msΪ1��
			ly_tt=0;
			ly_miao++;
			if(ly_miao==60){
				ly_miao=0;
				ly_fen++;
				if(ly_fen==60){	//��60����0
					ly_fen=0;
					ly_shi++;
					if(ly_shi==24)//��24Сʱ��0
						ly_shi=0;
				}
			}
		}
		display(ly_shi,ly_fen);		//��ʾ��������
		delay(100);
	}
}

//��ʼ������
void init()
{
	ly_tt=0;
	TMOD=0X01;		//���ö�ʱ��1Ϊģʽһ����16λ����ģʽ
	TH0=(65536-50000)/256;	//�������Ĵ�����ֵ��50����ʱ��
	TL0=(65536-50000)%256;
	EA=1;		//�������ж�
	ET0=1;		//������ʱ��0�ж�
	TR0=1;		//������ʱ��
}

//�жϺ���,�ؼ���"interrupt" �� ����C���Ե��жϺ�����ʾ����1��ʱ������0
void timer() interrupt 1
{
	TH0=(65536-50000)/256;	//���¸�ֵ
	TL0=(65536-50000)%256;
	ly_tt++;					//50�������
}

//��ʾ����������Ϊ��ʾ����
void display(unsigned char shi,unsigned char fen)
{
	P0=0XFF;			//	
	switch(l_posit){
	case 0:		//ѡ��ǧλ����ܣ��ر�����λ
		SMG_q=0;
		SMG_b=1;	
		SMG_s=1;		
		SMG_g=1;
		P0=table[shi/10];	//�����ʾ����
		break;
	case 1:		//ѡ���λ����ܣ��ر�����λ
		SMG_q=1;
		SMG_b=0;	
		SMG_s=1;		
		SMG_g=1;
		P0=table[shi%10];
		if(ly_tt>=10)
			P0&=0x7f;		//С�����԰����ʱ����˸
		break;
	case 2:		//ѡ��ʮλ����ܣ��ر�����λ
		SMG_q=1;
		SMG_b=1;	
		SMG_s=0;		
		SMG_g=1;
		P0=table[fen/10];
		break;
	case 3:		//ѡ���λ����ܣ��ر�����λ
		SMG_q=1;
		SMG_b=1;	
		SMG_s=1;		
		SMG_g=0;
		P0=table[fen%10];
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
