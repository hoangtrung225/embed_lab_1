/***************************************************************************
���⣺	���̳���+�������ʾ
Ч����	���°�������(���)�������ʾ����
�����ڣ�LY5A-L2A������
���ߣ�	�������-��Ƭ��
�ͷ�QQ��52927029
���䣺	52927029@qq.com
˵��:	������ֱ�Ӳ��÷�ʱɨ�跨�����������5���������ֱ����P13-P17���ţ��������Խ�0��ʽ��������������һ�Ž�GND
******************************************************************************/
//ͷ�ļ�:
#include "reg51.h"

//��������:
unsigned char oldkey=0xff;	//�������ӿ�״̬
//��������:
code unsigned char table[]=
			{0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};
					//����������� 0-9 

unsigned char l_posit=0;	//��ʾλ��
//���Ŷ���:	
sbit SMG_q = P1^0;	//����������������ƽţ�ǧλ��
sbit SMG_b = P1^1;	//����������������ƽţ���λ��
sbit SMG_s = P1^2;	//����������������ƽţ�ʮλ��
sbit SMG_g = P1^3;	//����������������ƽţ���λ��

sbit key1 = P3^7;	//���尴��1
sbit key2 = P3^6;	//���尴��2
sbit key3 = P3^5;	//���尴��3
sbit key4 = P3^4;	//���尴��4
sbit key5 = P3^3;	//���尴��5
sbit key6 = P3^2;	//���尴��6

//��������:
void display(unsigned int da);//������ʾ����������Ϊ��ʾ����
unsigned char ReadKey(void);	//����ֵ����
void delay(unsigned int timer); 

//��������C���Ե���ں���:	
void main(void)
{
	unsigned int ldata=0;		//��Ϊ��ʾ������
	unsigned char lold=1;		//��Ϊ�����ſ���ƾ֤��1Ϊ�ſ���0Ϊ����
	while(1){					//ѭ��ɨ�谴������ʾ
		switch(ReadKey()){		//��ȡ��ֵ��������Ӧ����
		case 1:ldata++;			//1����ʾ���ݼ�1
			break;
		case 2:ldata--;			//2����ʾ���ݼ�1
			break;
		case 3:ldata+=10;		//3����ʾ���ݼ�10
			break;
		case 4:ldata-=10;		//4����ʾ���ݼ�10
			break;
		case 5:ldata+=100;			//5����ʾ������0
			break;
		case 6:ldata-=100;		//6����ʾ�������
			break;
		}		
		display(ldata);		//��ʾ��Ӧ����ֵ�������ú�������ʽ������ʾ
		delay(100);
	}
}
unsigned char ReadKey(void)	//����ֵ
{
	unsigned char lkey=0;
	if((P3&0xfc)!=0xfc){	//������а����Ƿ��а�������	
		delay(10);			//�а�����������ʱһ��ʱ�䣬�����������趯
		if(oldkey!=(P3&0xfc)){//��ⰴ��δ�ɿ����Ҳ���֮ǰ���µİ����ͽ������ֵ������������
			oldkey=P3&0xfc;		//���浱ǰ״̬��Ϊ��һ��ɨ�����жϣ��뿴��һ��		
			if(key1==0)
				lkey=1;		//��һ�������¸�ֵ1
			else if(key2==0)
				lkey=2;		//�ڶ��������¸�ֵ2
			else if(key3==0)
				lkey=3;		//�����������¸�ֵ3
			else if(key4==0)
				lkey=4;		//���ĸ������¸�ֵ4
			else if(key5==0)
				lkey=5;		//����������¸�ֵ5
			else if(key6==0)
				lkey=6;		//�����������¸�ֵ6
		}
	}
	else{
		oldkey=0xfc;			//�����û�а������£�����ֵ��ʼ״̬
	}
	return lkey;
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
		P0=table[da/1000];	//�����ʾ����
		break;
	case 1:		//ѡ���λ����ܣ��ر�����λ
		SMG_q=1;
		SMG_b=0;	
		SMG_s=1;		
		SMG_g=1;
		P0=table[da%1000/100];
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

