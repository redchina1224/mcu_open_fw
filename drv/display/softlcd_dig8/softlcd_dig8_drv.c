
#include "..\..\com_include_drv.h"

#ifdef DisplayType
#if ((DisplayType&DisplayType_SoftLcd)==DisplayType_SoftLcd) 
#ifdef DisplayTypeSoftLcdModel

#ifndef DisplaySoftLcdBrightMax
	#define	DisplaySoftLcdBrightMax 40
#endif 

unsigned char LcdDrvCaseSelect;
unsigned char *Lcd_WriteSegBuffer;
const unsigned char *Lcd_WriteComBuffer;
unsigned char LcdBrightSet=0;
unsigned char LcdBrightCnt;
unsigned char LcdComStatus=0;
//unsigned char LcdBlinkSegTempVal;
/*
//请根据需要修改LCD输出电流（0x00-100uA,0x01-200uA,0x02-400uA,0x03-800uA）
#define		LCD_CUR			0x03		//LCD输出电流选择（范围0x00~0x03）

//COM口
#define		COM0			RC0			//数据对应为DispData[0]
#define		COM1			RC1			//数据对应为DispData[1]
#define		COM2			RC2			//数据对应为DispData[2]
#define		COM3			RC3			//数据对应为DispData[3]
#define		COM4			RC4			//数据对应为DispData[3]
#define		COM5			RC5			//数据对应为DispData[3]

//SEG口(用户自行修改段位对应的IO口)
#define		SEGA			RA5			
#define		SEGB			RA4
#define		SEGC			RA3
#define		SEGD			RA2
#define		SEGE			RA1
#define		SEGF			RA0
#define		SEGG			RA6
#define		SEGDP			RA7


volatile unsigned char C_LCD_COM;		//置相应IO口输出态间接变量

#define		BSET(x,y)		x|=(1<<y)				//置1
#define		BCLR(x,y)		x&=~(1<<y)				//置0


//显示数据寄存器
unsigned char DispData[6]={0xff,0xff,0xff,0xff,0xff,0xff};			
unsigned char Dcount;			//用于循环显示数码管COM口


void zd_softlcd_run(void)
{
		if(++LcdBrightCnt>20)
	{
		LcdBrightCnt=0;
	BSET(C_LCD_COM,0);	//COM0
	BSET(C_LCD_COM,1);	//COM1
	BSET(C_LCD_COM,2);	//COM2
	BSET(C_LCD_COM,3);	//COM3
	BSET(C_LCD_COM,4);	//COM3
	BSET(C_LCD_COM,5);	//COM3

	LEDCON0 = 0B10000000;				//使能LCD模块
	LEDCON1 = LCD_CUR;					//设置LCD输出电流				
	TRISC = C_LCD_COM;					//先将相应的COM口置为输入态
	COMEN = C_LCD_COM;
	
	if(Dcount & 0x01)					//先将所有显示关闭
	{
		SEGA = 1;
		SEGB = 1;
		SEGC = 1;
		SEGD = 1;
		SEGE = 1;
		SEGF = 1;												
		SEGG = 1;
		SEGDP = 1;
	}
	else
	{
		SEGA = 0;
		SEGB = 0;
		SEGC = 0;
		SEGD = 0;
		SEGE = 0;
		SEGF = 0;												
		SEGG = 0;
		SEGDP = 0;	
	}	
	
	//循环点亮各个COM口
	switch(Dcount)	
	{
		case 0:
			COM0 = 0;
			COMEN = 0B00111110;		//使能对应COM口为LCD功能口
			TRISC = 0B00111110;		//设置COM0为输出态
			COM0 = 0;
			
			if(DispData[0] & 0x01)	{SEGA = 1;}
			if(DispData[0] & 0x02)	{SEGB = 1;}
			if(DispData[0] & 0x04)	{SEGC = 1;}
			if(DispData[0] & 0x08)	{SEGD = 1;}
			if(DispData[0] & 0x10)	{SEGE = 1;}
			if(DispData[0] & 0x20)	{SEGF = 1;}
			if(DispData[0] & 0x40)	{SEGG = 1;}
			if(DispData[0] & 0x80)	{SEGDP = 1;}
			break;
		case 1:
			COM0 = 1;
			COMEN = 0B00111110;		//使能对应COM口为LCD功能口
			TRISC = 0B00111110;		//设置COM0为输出态
			COM0 = 1;
			
			if(DispData[0] & 0x01)	{SEGA = 0;}
			if(DispData[0] & 0x02)	{SEGB = 0;}
			if(DispData[0] & 0x04)	{SEGC = 0;}
			if(DispData[0] & 0x08)	{SEGD = 0;}
			if(DispData[0] & 0x10)	{SEGE = 0;}
			if(DispData[0] & 0x20)	{SEGF = 0;}
			if(DispData[0] & 0x40)	{SEGG = 0;}
			if(DispData[0] & 0x80)	{SEGDP = 0;}																		 
			break;
		case 2:
			COM1 = 0;
			COMEN = 0B00111101;		//使能对应COM口为LCD功能口
			TRISC = 0B00111101;		//设置COM1为输出态
			COM1 = 0;
			
			if(DispData[1] & 0x01)	{SEGA = 1;}
			if(DispData[1] & 0x02)	{SEGB = 1;}
			if(DispData[1] & 0x04)	{SEGC = 1;}
			if(DispData[1] & 0x08)	{SEGD = 1;}
			if(DispData[1] & 0x10)	{SEGE = 1;}
			if(DispData[1] & 0x20)	{SEGF = 1;}
			if(DispData[1] & 0x40)	{SEGG = 1;}
			if(DispData[1] & 0x80)	{SEGDP = 1;}																			 
			break;
		case 3:
			COM1 = 1;
			COMEN = 0B00111101;		//使能对应COM口为LCD功能口
			TRISC = 0B00111101;		//设置COM1为输出态
			COM1 = 1;
			
			if(DispData[1] & 0x01)	{SEGA = 0;}
			if(DispData[1] & 0x02)	{SEGB = 0;}
			if(DispData[1] & 0x04)	{SEGC = 0;}
			if(DispData[1] & 0x08)	{SEGD = 0;}
			if(DispData[1] & 0x10)	{SEGE = 0;}
			if(DispData[1] & 0x20)	{SEGF = 0;}
			if(DispData[1] & 0x40)	{SEGG = 0;}
			if(DispData[1] & 0x80)	{SEGDP = 0;}																			 
			break;
		case 4:
			COM2 = 0;
			COMEN = 0B00111011;		//使能对应COM口为LCD功能口
			TRISC = 0B00111011;		//设置COM2为输出态
			COM2 = 0;
			
			if(DispData[2] & 0x01)	{SEGA = 1;}
			if(DispData[2] & 0x02)	{SEGB = 1;}
			if(DispData[2] & 0x04)	{SEGC = 1;}
			if(DispData[2] & 0x08)	{SEGD = 1;}
			if(DispData[2] & 0x10)	{SEGE = 1;}
			if(DispData[2] & 0x20)	{SEGF = 1;}
			if(DispData[2] & 0x40)	{SEGG = 1;}
			if(DispData[2] & 0x80)	{SEGDP = 1;}																		 
			break;
		case 5:
			COM2 = 1;
			COMEN = 0B00111011;		//使能对应COM口为LCD功能口
			TRISC = 0B00111011;		//设置COM2为输出态
			COM2 = 1;
			
			if(DispData[2] & 0x01)	{SEGA = 0;}
			if(DispData[2] & 0x02)	{SEGB = 0;}
			if(DispData[2] & 0x04)	{SEGC = 0;}
			if(DispData[2] & 0x08)	{SEGD = 0;}
			if(DispData[2] & 0x10)	{SEGE = 0;}
			if(DispData[2] & 0x20)	{SEGF = 0;}
			if(DispData[2] & 0x40)	{SEGG = 0;}
			if(DispData[2] & 0x80)	{SEGDP = 0;}
			break;	
		case 6:
			COM3 = 0;
			COMEN = 0B00110111;		//使能对应COM口为LCD功能口
			TRISC = 0B00110111;		//设置COM3为输出态
			COM3 = 0;
			
			if(DispData[3] & 0x01)	{SEGA = 1;}
			if(DispData[3] & 0x02)	{SEGB = 1;}
			if(DispData[3] & 0x04)	{SEGC = 1;}
			if(DispData[3] & 0x08)	{SEGD = 1;}
			if(DispData[3] & 0x10)	{SEGE = 1;}
			if(DispData[3] & 0x20)	{SEGF = 1;}
			if(DispData[3] & 0x40)	{SEGG = 1;}
			if(DispData[3] & 0x80)	{SEGDP = 1;}
			break;
		case 7:
			COM3 = 1;
			COMEN = 0B00110111;		//使能对应COM口为LCD功能口
			TRISC = 0B00110111;		//设置COM3为输出态
			COM3 = 1;
			
			if(DispData[3] & 0x01)	{SEGA = 0;}
			if(DispData[3] & 0x02)	{SEGB = 0;}
			if(DispData[3] & 0x04)	{SEGC = 0;}
			if(DispData[3] & 0x08)	{SEGD = 0;}
			if(DispData[3] & 0x10)	{SEGE = 0;}
			if(DispData[3] & 0x20)	{SEGF = 0;}
			if(DispData[3] & 0x40)	{SEGG = 0;}
			if(DispData[3] & 0x80)	{SEGDP = 0;}	
			break;
		case 8:
			COM4 = 0;
			COMEN = 0B00101111;		//使能对应COM口为LCD功能口
			TRISC = 0B00101111;		//设置COM3为输出态
			COM4 = 0;
			
			if(DispData[4] & 0x01)	{SEGA = 1;}
			if(DispData[4] & 0x02)	{SEGB = 1;}
			if(DispData[4] & 0x04)	{SEGC = 1;}
			if(DispData[4] & 0x08)	{SEGD = 1;}
			if(DispData[4] & 0x10)	{SEGE = 1;}
			if(DispData[4] & 0x20)	{SEGF = 1;}
			if(DispData[4] & 0x40)	{SEGG = 1;}
			if(DispData[4] & 0x80)	{SEGDP = 1;}
			break;
		case 9:
			COM4 = 1;
			COMEN = 0B00101111;		//使能对应COM口为LCD功能口
			TRISC = 0B00101111;		//设置COM3为输出态
			COM4 = 1;
			
			if(DispData[4] & 0x01)	{SEGA = 0;}
			if(DispData[4] & 0x02)	{SEGB = 0;}
			if(DispData[4] & 0x04)	{SEGC = 0;}
			if(DispData[4] & 0x08)	{SEGD = 0;}
			if(DispData[4] & 0x10)	{SEGE = 0;}
			if(DispData[4] & 0x20)	{SEGF = 0;}
			if(DispData[4] & 0x40)	{SEGG = 0;}
			if(DispData[4] & 0x80)	{SEGDP = 0;}	
			break;
		case 10:
			COM5 = 0;
			COMEN = 0B00011111;		//使能对应COM口为LCD功能口
			TRISC = 0B00011111;		//设置COM3为输出态
			COM5 = 0;
			
			if(DispData[5] & 0x01)	{SEGA = 1;}
			if(DispData[5] & 0x02)	{SEGB = 1;}
			if(DispData[5] & 0x04)	{SEGC = 1;}
			if(DispData[5] & 0x08)	{SEGD = 1;}
			if(DispData[5] & 0x10)	{SEGE = 1;}
			if(DispData[5] & 0x20)	{SEGF = 1;}
			if(DispData[5] & 0x40)	{SEGG = 1;}
			if(DispData[5] & 0x80)	{SEGDP = 1;}
			break;

		default:
			COM5 = 1;
			COMEN = 0B00011111;		//使能对应COM口为LCD功能口
			TRISC = 0B00011111;		//设置COM3为输出态
			COM5 = 1;
			
			if(DispData[5] & 0x01)	{SEGA = 0;}
			if(DispData[5] & 0x02)	{SEGB = 0;}
			if(DispData[5] & 0x04)	{SEGC = 0;}
			if(DispData[5] & 0x08)	{SEGD = 0;}
			if(DispData[5] & 0x10)	{SEGE = 0;}
			if(DispData[5] & 0x20)	{SEGF = 0;}
			if(DispData[5] & 0x40)	{SEGG = 0;}
			if(DispData[5] & 0x80)	{SEGDP = 0;}	

			break;
	}
	
	if(++Dcount >= 8)
	{
		Dcount = 0;
	}
	}
}
*/

//在bsp_run中调用，或在中断中调用
void zd_softlcd_run(void)	
{
	LcdBrightCnt++;
	if(LcdBrightCnt>30)
	{
		LcdBrightCnt=0;

	Lcd_IO_COM_INPUT;
	
	if(LcdComStatus==0)
	{
		LcdComStatus=1;

		Lcd_IO_SEG_SET_ALL;

		Lcd_IO_COM_SET(Lcd_WriteComBuffer[LcdDrvCaseSelect]);

		Lcd_IO_SEG_CLR(Lcd_WriteSegBuffer[LcdDrvCaseSelect]);	


		if(++LcdDrvCaseSelect>=DisplaySoftLcdBufferLength) LcdDrvCaseSelect=0;	
	}
	else if(LcdComStatus==1)
	{
		LcdComStatus=0;

		Lcd_IO_SEG_CLR_ALL;

		Lcd_IO_COM_CLR(Lcd_WriteComBuffer[LcdDrvCaseSelect]);	
		
		Lcd_IO_SEG_SET(Lcd_WriteSegBuffer[LcdDrvCaseSelect]);	
	}
}
}


void zd_softlcd_init(void)
{
	LEDCON0 = 0B10000000;				//使能LCD模块
	LEDCON1 = 0x03;//LCD_CUR;					//设置LCD输出电流				
	Lcd_IO_COM_INPUT;
	Lcd_IO_SEG_OUTPUT;
	LcdDrvCaseSelect=0;	
}



#endif
#endif
#endif
