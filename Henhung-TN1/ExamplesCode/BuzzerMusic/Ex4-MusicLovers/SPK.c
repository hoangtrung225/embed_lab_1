/***************************************************************************
���⣺	������ʵ��-���ֳ���
Ч����	��������
�����ڣ�LY5A-L2A������
���ߣ�	�������-��Ƭ��
�ͷ�QQ��52927029
���䣺	52927029@qq.com
˵����	��Ƭ����T0�ж���IO��P1.5�������
        1.����������Ƿ������Ƚ�����:-)���Խ�����ϸ����DA������Ҳ�  
        2.����T1Ƶ���жϣ��κ������жϷ���������������٣�ֻ�ʺ�����    
		ʹ�þ���12M
***************************************************************************/
#include "reg51.h"
#include <intrins.h>

#define  FREQ 12000000

//���Ŷ���:
sbit SPK  = P1^5;	//���������

//���ݶ��壺
//���ֱ���,�洢������
//�������ʽ:| D7 |D6  D5  D4| D3 |D2  D1  D0|
//           |���|      ����|����|     ���� |
//         |��4λ=0ʱ�ǹ�����|���ݵ�4λת��  |
unsigned char code music1[]={   //��ף 
    0xcb,                       //ʾ��:0xcb=11001011B,�����/1/4��,3Mi����
    0x35,0x16,0xb9,0x12,0x96,0x99,0xa5,
    0xbd,0x99,0x96,0x15,0x13,0x15,0x62,
    0x32,0x13,0xa7,0x26,0x25,0x16,0xa9,0x22,
    0xa3,0xa9,0x96,0x15,0x16,0x99,0xe5,
    0xbb,0x15,0xa7,0xaa,0x96,0x99,0xd5,
    0x13,0x15,0x23,0x15,0x16,0x17,0x9a,0xd6,0x15,0x16,
    0xb9,0x12,0x25,0x23,0x23,0x22,0x13,0x12,0x21,0x96,0x15,
    0x43,0xc9,0x96,0x99,0x96,0x15,0x13,0x15,0x16,0x99,
    0xd5,                            
    0x00,                        //����ֽ�Ϊ���������==0x00�˳�
};

unsigned char code music_l_tab[8]={0,1,2,3,4,6,8,16};//���ֽ���

unsigned char code music_freq_tab[64]={             //������ʱ��ֵ��
    0xff,0xea,                                      //0 ��ֹ��
    255-FREQ/24/131/256,     //256-FREQ/24/x/256    //1 do ���ֽ�
    256-FREQ/24/131%256,     //256-FREQ/24/x%256    //1 do ���ֽ�
    255-FREQ/24/147/256,256-FREQ/24/147%256,        //2 re
    255-FREQ/24/165/256,256-FREQ/24/165%256,        //3 mi
    255-FREQ/24/175/256,256-FREQ/24/175%256,        //4 fa
    255-FREQ/24/196/256,256-FREQ/24/196%256,        //5 suo
    255-FREQ/24/221/256,256-FREQ/24/221%256,        //6 la
    255-FREQ/24/248/256,256-FREQ/24/248%256,        //7 xi

    0xff,0xea,                                      //0 ��ֹ��
    255-FREQ/24/262/256,256-FREQ/24/262%256,        //1 do
    255-FREQ/24/294/256,256-FREQ/24/294%256,        //2 re
    255-FREQ/24/330/256,256-FREQ/24/330%256,        //3 mi
    255-FREQ/24/350/256,256-FREQ/24/350%256,        //4 fa
    255-FREQ/24/393/256,256-FREQ/24/393%256,        //5 suo
    255-FREQ/24/441/256,256-FREQ/24/441%256,        //6 la
    255-FREQ/24/495/256,256-FREQ/24/495%256,        //7 xi

    0xff,0xea,                                      //0 ��ֹ��
    255-FREQ/24/525/256,256-FREQ/24/525%256,        //1 do
    255-FREQ/24/589/256,256-FREQ/24/589%256,        //2 re
    255-FREQ/24/661/256,256-FREQ/24/661%256,        //3 mi
    255-FREQ/24/700/256,256-FREQ/24/700%256,        //4 fa
    255-FREQ/24/786/256,256-FREQ/24/786%256,        //5 suo
    255-FREQ/24/882/256,256-FREQ/24/882%256,        //6 la
    255-FREQ/24/990/256,256-FREQ/24/990%256,        //7 xi

    0xff,0xea,                                      //0 ��ֹ��
    255-FREQ/24/1049/256,256-FREQ/24/1049%256,      //1 do
    255-FREQ/24/1178/256,256-FREQ/24/1178%256,      //2 re
    255-FREQ/24/1322/256,256-FREQ/24/1322%256,      //3 mi
    255-FREQ/24/1400/256,256-FREQ/24/1400%256,      //4 fa
    255-FREQ/24/1572/256,256-FREQ/24/1572%256,      //5 suo
    255-FREQ/24/1665/256,256-FREQ/24/1665%256,      //6 la
    255-FREQ/24/1869/256,256-FREQ/24/1869%256,      //7 xi

};

unsigned char code music_frequp_tab[64]={           //������
    0xff,0xea,                                      //0 ��ֹ��
    255-FREQ/24/139/256,        //1 do ���ֽ� //255-FREQ/24/x/256
    256-FREQ/24/139%256,        //1 do ���ֽ� //256-FREQ/24/x%256
    255-FREQ/24/156/256,256-FREQ/24/156%256,        //2 re
    255-FREQ/24/175/256,256-FREQ/24/175%256,        //3 mi
    255-FREQ/24/185/256,256-FREQ/24/185%256,        //4 fa
    255-FREQ/24/208/256,256-FREQ/24/208%256,        //5 suo
    255-FREQ/24/234/256,256-FREQ/24/234%256,        //6 la
    255-FREQ/24/262/256,256-FREQ/24/262%256,        //7 xi

    0xff,0xea,                                      //0 ��ֹ��
    255-FREQ/24/278/256,256-FREQ/24/278%256,        //1 do
    255-FREQ/24/312/256,256-FREQ/24/312%256,        //2 re
    255-FREQ/24/350/256,256-FREQ/24/350%256,        //3 mi
    255-FREQ/24/371/256,256-FREQ/24/371%256,        //4 fa
    255-FREQ/24/416/256,256-FREQ/24/416%256,        //5 suo
    255-FREQ/24/467/256,256-FREQ/24/467%256,        //6 la
    255-FREQ/24/525/256,256-FREQ/24/525%256,        //7 xi

    0xff,0xea,                                      //0 ��ֹ��
    255-FREQ/24/556/256,256-FREQ/24/556%256,        //1 do
    255-FREQ/24/624/256,256-FREQ/24/624%256,        //2 re
    255-FREQ/24/700/256,256-FREQ/24/700%256,        //3 mi
    255-FREQ/24/742/256,256-FREQ/24/742%256,        //4 fa
    255-FREQ/24/833/256,256-FREQ/24/833%256,        //5 suo
    255-FREQ/24/935/256,256-FREQ/24/935%256,        //6 la
    255-FREQ/24/1049/256,256-FREQ/24/1049%256,      //7 xi

    0xff,0xea,                                      //0 ��ֹ��
    255-FREQ/24/1112/256,256-FREQ/24/1112%256,      //1 do
    255-FREQ/24/1248/256,256-FREQ/24/1248%256,      //2 re
    255-FREQ/24/1400/256,256-FREQ/24/1400%256,      //3 mi
    255-FREQ/24/1484/256,256-FREQ/24/1484%256,      //4 fa
    255-FREQ/24/1618/256,256-FREQ/24/1618%256,      //5 suo
    255-FREQ/24/1764/256,256-FREQ/24/1764%256,      //6 la
    255-FREQ/24/1968/256,256-FREQ/24/1968%256,      //7 xi
};
unsigned char ly_TH0;
unsigned char ly_TL0;

//��������: 
void music_delay(unsigned char timer);   //���ֽ�����ʱ
void music_play(unsigned char *pmsc); 	//���������ӳ���


//��������C���Ե���ں���:	
void main(void)
{
	TMOD=0x01;       //��ʱ��ģʽ
	EA=1;
	EX0=0;
	TR0=0;
	while(1)
    	music_play(music1);	//��������
}
//---------------------------------------------------------------------------//
void music_int0 (void) interrupt 1 using 1    //��ʱ�ж�1//
{
    SPK=~SPK;
    TH0=ly_TH0;
    TL0=ly_TL0;
}

//---------------------------------------------------------------------------//
void music_delay(unsigned char timer)     //��ʱ 125*n ����
{
    unsigned char i=125,j;
    do{
        do{
            for(j=0; j<230; j++)
		    	_nop_();
      }while(--i);
    }while(--timer);
}

//---------------------------------------------------------------------------//
void music_play(unsigned char *pmsc)   //����
{
    unsigned char music_freq=32;      //���� 
    unsigned char music_long;         //������ʱ
    unsigned char music_data=0;       //��������
    bit music_up=0;                   //������
    bit music_break=0;                //����
    ly_TH0=0xff;
    ly_TL0=0xea;                    //�����(���������)
    ET0=1;                            //��T1��ʱ���ж�
	TR0=1;
//---------------------------------------------------------
    while (*pmsc != 0x00)
        {
        music_data=*pmsc & 0x07;
        music_long=*pmsc>>4;
        //---------------------------------------------------------
        if (music_long != 0){          //���������ǹ�����
            if (*pmsc&0x80){           //��������
                if (((*pmsc) & 0x08) == 0)
                    {if(music_freq >= 16) music_freq -= 16;}   //�����½� 
                else
                    {if(music_freq < 48) music_freq += 16;}    //��������
             }
            //---------------------------------------------------------
            if (music_up==1){          //������
                ly_TH0=music_frequp_tab[(music_freq  + (music_data <<1))];
                ly_TL0=music_frequp_tab[(music_freq + (music_data <<1)+1)];
            }
            else{                      //��������
                ly_TH0=music_freq_tab[(music_freq + (music_data <<1))];
                ly_TL0=music_freq_tab[(music_freq + (music_data <<1)+ 1)];
            }
            //---------------------------------------------------------
            if (music_break){          //����
                music_delay(music_l_tab[music_long&0x07]-1);
                ly_TH0=0xff;
                ly_TL0=0xea;
                music_delay(1);
            }
            else                      //����
                music_delay(music_l_tab[music_long&0x07]);
        }
        //---------------------------------------------------------
        else                          //�ǹ�����
            {
            switch(music_data){
            case 0x04:
            	music_up=0; break;      //��������                    
            case 0x05:
           		music_up=1; break;      //������                    
          	case 0x06:
       			music_break=0; break;   //����                    
   			case 0x07:
         		music_break=1;break;    //����                    
            }
        }
        //---------------------------------------------------------
        pmsc++;
    }
    ET0=0;                          //���Ž���,��T1�ж�
	TR0=0;
    SPK=1;                       	//�����
}