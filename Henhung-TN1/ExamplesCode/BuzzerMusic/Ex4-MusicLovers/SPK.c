/***************************************************************************
标题：	蜂鸣器实验-音乐程序
效果：	播放音乐
工作于：LY5A-L2A开发板
作者：	林洋电子-单片机
客服QQ：52927029
邮箱：	52927029@qq.com
说明：	单片机用T0中断在IO口P1.5输出乐曲
        1.由于输出的是方波，比较难听:-)可以将波形细分用DA输出正弦波  
        2.由于T1频繁中断，任何其他中断发生都会是乐曲打顿，只适合试验    
		使用晶振12M
***************************************************************************/
#include "reg51.h"
#include <intrins.h>

#define  FREQ 12000000

//引脚定义:
sbit SPK  = P1^5;	//定义蜂鸣器

//数据定义：
//音乐编码,存储器定义
//音符码格式:| D7 |D6  D5  D4| D3 |D2  D1  D0|
//           |变调|      节拍|升降|     音符 |
//         |高4位=0时是功能码|根据低4位转换  |
unsigned char code music1[]={   //梁祝 
    0xcb,                       //示例:0xcb=11001011B,升半调/1/4拍,3Mi低音
    0x35,0x16,0xb9,0x12,0x96,0x99,0xa5,
    0xbd,0x99,0x96,0x15,0x13,0x15,0x62,
    0x32,0x13,0xa7,0x26,0x25,0x16,0xa9,0x22,
    0xa3,0xa9,0x96,0x15,0x16,0x99,0xe5,
    0xbb,0x15,0xa7,0xaa,0x96,0x99,0xd5,
    0x13,0x15,0x23,0x15,0x16,0x17,0x9a,0xd6,0x15,0x16,
    0xb9,0x12,0x25,0x23,0x23,0x22,0x13,0x12,0x21,0x96,0x15,
    0x43,0xc9,0x96,0x99,0x96,0x15,0x13,0x15,0x16,0x99,
    0xd5,                            
    0x00,                        //最后字节为功能码必须==0x00退出
};

unsigned char code music_l_tab[8]={0,1,2,3,4,6,8,16};//音乐节拍

unsigned char code music_freq_tab[64]={             //音符定时器值表
    0xff,0xea,                                      //0 休止符
    255-FREQ/24/131/256,     //256-FREQ/24/x/256    //1 do 高字节
    256-FREQ/24/131%256,     //256-FREQ/24/x%256    //1 do 低字节
    255-FREQ/24/147/256,256-FREQ/24/147%256,        //2 re
    255-FREQ/24/165/256,256-FREQ/24/165%256,        //3 mi
    255-FREQ/24/175/256,256-FREQ/24/175%256,        //4 fa
    255-FREQ/24/196/256,256-FREQ/24/196%256,        //5 suo
    255-FREQ/24/221/256,256-FREQ/24/221%256,        //6 la
    255-FREQ/24/248/256,256-FREQ/24/248%256,        //7 xi

    0xff,0xea,                                      //0 休止符
    255-FREQ/24/262/256,256-FREQ/24/262%256,        //1 do
    255-FREQ/24/294/256,256-FREQ/24/294%256,        //2 re
    255-FREQ/24/330/256,256-FREQ/24/330%256,        //3 mi
    255-FREQ/24/350/256,256-FREQ/24/350%256,        //4 fa
    255-FREQ/24/393/256,256-FREQ/24/393%256,        //5 suo
    255-FREQ/24/441/256,256-FREQ/24/441%256,        //6 la
    255-FREQ/24/495/256,256-FREQ/24/495%256,        //7 xi

    0xff,0xea,                                      //0 休止符
    255-FREQ/24/525/256,256-FREQ/24/525%256,        //1 do
    255-FREQ/24/589/256,256-FREQ/24/589%256,        //2 re
    255-FREQ/24/661/256,256-FREQ/24/661%256,        //3 mi
    255-FREQ/24/700/256,256-FREQ/24/700%256,        //4 fa
    255-FREQ/24/786/256,256-FREQ/24/786%256,        //5 suo
    255-FREQ/24/882/256,256-FREQ/24/882%256,        //6 la
    255-FREQ/24/990/256,256-FREQ/24/990%256,        //7 xi

    0xff,0xea,                                      //0 休止符
    255-FREQ/24/1049/256,256-FREQ/24/1049%256,      //1 do
    255-FREQ/24/1178/256,256-FREQ/24/1178%256,      //2 re
    255-FREQ/24/1322/256,256-FREQ/24/1322%256,      //3 mi
    255-FREQ/24/1400/256,256-FREQ/24/1400%256,      //4 fa
    255-FREQ/24/1572/256,256-FREQ/24/1572%256,      //5 suo
    255-FREQ/24/1665/256,256-FREQ/24/1665%256,      //6 la
    255-FREQ/24/1869/256,256-FREQ/24/1869%256,      //7 xi

};

unsigned char code music_frequp_tab[64]={           //升半音
    0xff,0xea,                                      //0 休止符
    255-FREQ/24/139/256,        //1 do 高字节 //255-FREQ/24/x/256
    256-FREQ/24/139%256,        //1 do 低字节 //256-FREQ/24/x%256
    255-FREQ/24/156/256,256-FREQ/24/156%256,        //2 re
    255-FREQ/24/175/256,256-FREQ/24/175%256,        //3 mi
    255-FREQ/24/185/256,256-FREQ/24/185%256,        //4 fa
    255-FREQ/24/208/256,256-FREQ/24/208%256,        //5 suo
    255-FREQ/24/234/256,256-FREQ/24/234%256,        //6 la
    255-FREQ/24/262/256,256-FREQ/24/262%256,        //7 xi

    0xff,0xea,                                      //0 休止符
    255-FREQ/24/278/256,256-FREQ/24/278%256,        //1 do
    255-FREQ/24/312/256,256-FREQ/24/312%256,        //2 re
    255-FREQ/24/350/256,256-FREQ/24/350%256,        //3 mi
    255-FREQ/24/371/256,256-FREQ/24/371%256,        //4 fa
    255-FREQ/24/416/256,256-FREQ/24/416%256,        //5 suo
    255-FREQ/24/467/256,256-FREQ/24/467%256,        //6 la
    255-FREQ/24/525/256,256-FREQ/24/525%256,        //7 xi

    0xff,0xea,                                      //0 休止符
    255-FREQ/24/556/256,256-FREQ/24/556%256,        //1 do
    255-FREQ/24/624/256,256-FREQ/24/624%256,        //2 re
    255-FREQ/24/700/256,256-FREQ/24/700%256,        //3 mi
    255-FREQ/24/742/256,256-FREQ/24/742%256,        //4 fa
    255-FREQ/24/833/256,256-FREQ/24/833%256,        //5 suo
    255-FREQ/24/935/256,256-FREQ/24/935%256,        //6 la
    255-FREQ/24/1049/256,256-FREQ/24/1049%256,      //7 xi

    0xff,0xea,                                      //0 休止符
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

//函数定义: 
void music_delay(unsigned char timer);   //音乐节拍延时
void music_play(unsigned char *pmsc); 	//播放音乐子程序


//主函数，C语言的入口函数:	
void main(void)
{
	TMOD=0x01;       //定时器模式
	EA=1;
	EX0=0;
	TR0=0;
	while(1)
    	music_play(music1);	//播放音乐
}
//---------------------------------------------------------------------------//
void music_int0 (void) interrupt 1 using 1    //定时中断1//
{
    SPK=~SPK;
    TH0=ly_TH0;
    TL0=ly_TL0;
}

//---------------------------------------------------------------------------//
void music_delay(unsigned char timer)     //延时 125*n 毫秒
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
void music_play(unsigned char *pmsc)   //音乐
{
    unsigned char music_freq=32;      //音高 
    unsigned char music_long;         //节拍延时
    unsigned char music_data=0;       //音符数据
    bit music_up=0;                   //升半音
    bit music_break=0;                //断奏
    ly_TH0=0xff;
    ly_TL0=0xea;                    //关输出(输出超声波)
    ET0=1;                            //开T1定时器中断
	TR0=1;
//---------------------------------------------------------
    while (*pmsc != 0x00)
        {
        music_data=*pmsc & 0x07;
        music_long=*pmsc>>4;
        //---------------------------------------------------------
        if (music_long != 0){          //是音符，非功能码
            if (*pmsc&0x80){           //需升降调
                if (((*pmsc) & 0x08) == 0)
                    {if(music_freq >= 16) music_freq -= 16;}   //音高下降 
                else
                    {if(music_freq < 48) music_freq += 16;}    //音高上升
             }
            //---------------------------------------------------------
            if (music_up==1){          //升半音
                ly_TH0=music_frequp_tab[(music_freq  + (music_data <<1))];
                ly_TL0=music_frequp_tab[(music_freq + (music_data <<1)+1)];
            }
            else{                      //不升半音
                ly_TH0=music_freq_tab[(music_freq + (music_data <<1))];
                ly_TL0=music_freq_tab[(music_freq + (music_data <<1)+ 1)];
            }
            //---------------------------------------------------------
            if (music_break){          //断奏
                music_delay(music_l_tab[music_long&0x07]-1);
                ly_TH0=0xff;
                ly_TL0=0xea;
                music_delay(1);
            }
            else                      //连奏
                music_delay(music_l_tab[music_long&0x07]);
        }
        //---------------------------------------------------------
        else                          //是功能码
            {
            switch(music_data){
            case 0x04:
            	music_up=0; break;      //不升半音                    
            case 0x05:
           		music_up=1; break;      //升半音                    
          	case 0x06:
       			music_break=0; break;   //断奏                    
   			case 0x07:
         		music_break=1;break;    //连奏                    
            }
        }
        //---------------------------------------------------------
        pmsc++;
    }
    ET0=0;                          //播放结束,关T1中断
	TR0=0;
    SPK=1;                       	//关输出
}
