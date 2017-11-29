/***************************************************************************
���⣺	���ڵ��Գ����жϷ���������
Ч����	���б����ӣ��򿪴��ڵ�����λ�����������ò�����2400���ٽ��з������ݣ��������ʾ��������
�����ڣ�LY5A-L2A������
���ߣ�	�������-��Ƭ��
�ͷ�QQ��52927029
���䣺	52927029@qq.com
******************************************************************************/

//ͷ�ļ�:
#include "reg51.h"

//��������:
unsigned char table[]=
			{0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0x88,0x83,0xc6,0xa1,0x86,0x8e};
			//������������� 0-9 a-f,ʮ��������ʾ	
unsigned char ldata=0;	//��Ϊ���ռ����͵����ݱ���
unsigned char oldkey=0xff;	//�������ӿ�״̬

//���Ŷ���:	
sbit SMG_q = P1^0;	//����������������ƽţ�ǧλ��
sbit SMG_b = P1^1;	//����������������ƽţ���λ��
sbit SMG_s = P1^2;	//����������������ƽţ�ʮλ��
sbit SMG_g = P1^3;	//����������������ƽţ���λ��

sbit SPK  = P1^5;	//���������
sbit key1 = P3^7;	//���尴��1
sbit key2 = P3^6;	//���尴��2
sbit key3 = P3^5;	//���尴��3
sbit key4 = P3^4;	//���尴��4
sbit key5 = P3^3;	//���尴��5
sbit key6 = P3^2;	//���尴��6

//��������:
unsigned char ReadKey(void);	//����ֵ����
void display(unsigned char da);//������ʾ����������Ϊ��ʾ���ݣ�ֻ��ʾ��λʮ������	
void delay(unsigned int timer);


//��������C���Ե���ں���:	
void main(void)  
{
	unsigned char lold=1;	//��Ϊ�����ſ���ƾ֤��1Ϊ�ſ���0Ϊ����

	EA=1;					//�������ж�	
	TMOD=0X20;				//���ö�ʱ��1Ϊģʽ2����Ϊ�����ʷ�����
	TL1=0xF3;				//2400�����ʵĳ�ֵ,����ʹ��12M���񣬳�ֵ=256-12000000/32/12/2400
	TH1=0xF3;				//
	TR1=1;					//���������ʷ���
	SCON=0x50;				//���ڷ�ʽ2
	ES=1;					//��ʼ�����ж�

	while(1){					//ѭ��ɨ�谴������ʾ
		switch(ReadKey()){		//��ȡ��ֵ��������Ӧ����
		case 1:ldata++;			//1����ʾ���ݼ�1
			break;
		case 2:ldata--;			//2����ʾ���ݼ�1
			break;
		case 3:ldata+=16;		//3����ʾ���ݼ�10
			break;
		case 4:ldata-=16;		//4����ʾ���ݼ�10
			break;
		case 5:ldata=0;			//5����ʾ������0
			break;
		case 6:
			SBUF=ldata;	//����ֱ�ӽ����ݷ��ͳ�ȥ
			while(!TI){}
			TI=0;   	//�ȴ�������Ϸ��ؼ������
			break;
		}		
		display(ldata);		//��ʾ��Ӧ����ֵ�������ú�������ʽ������ʾ
	}
}

//�����ж���ں���
void com_isr(void) interrupt 4
{	
	if(RI){					//�ǽ����жϴ���
		RI=0;				//���Ĵ�����λ�ȴ�������һ��
		ldata=SBUF;			//�����յ����ݴ��ڱ�����
	}
}

//ɨ�����
unsigned char ReadKey(void)	
{
	unsigned char lkey=0;
	if((P3&0xfc)!=0xfc){	//������а����Ƿ��а�������

		SPK=0;				//�������������������

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
		oldkey=0xfc;		//�����û�а������£�����ֵ��ʼ״̬

		SPK=1;				//�ް����������˳�����
	}
	return lkey;
}

void display(unsigned char da)
{
	SMG_b=0;			//ѡ���λ�����
	P0=table[da/16];	//����������õ�����ܶ�ֵ��P0�ڣ���ʾ��Ӧ��0-f
	delay(1);			//��ʱ
	P0=0XFF;			//����������ʾ�����ǹ����ͣ����Բ���0
	SMG_b=1;			//�رհ�λ�����

	SMG_s=0;			//ѡ��ʮλ�����
	P0=table[da%16];	//����������õ�����ܶ�ֵ��P0�ڣ���ʾ��Ӧ��0-f
	delay(1);			//��ʱ
	P0=0XFF;			//����������ʾ�����ǹ����ͣ����Բ���0
	SMG_s=1;			//�ر�ʮλ�����

	SMG_g=0;			//ѡ���λ����ܣ�
	P0=0x89;			//��ʾһ��"H",��ʾʮ��������ʾ
	delay(1);			//��ʱ
	P0=0XFF;			//����������ʾ�����ǹ����ͣ����Բ���0
	SMG_g=1;			//�رո�λ�����
}

//��ʱ�Ӻ���
void delay(unsigned int timer){		
	while(timer--);
}