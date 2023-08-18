//******************************************************************************
//Copyright(C) 2020-2021 zhejiang zhida dianzikeji Co., Ltd
//浙江智达电子科技有限公司
//File name:      TM1628.c
//Author:         zzg
//Version:        Ver0.1
//Date:           2021-4-25
//Description:    TM1628驱动
//History:
//******************************************************************************
//头文件************************************************************************
#include "..\..\..\com_include_drv.h"
//******************************************************************************
#ifdef DisplayType
#if ((DisplayType&DisplayType_IcLed)==DisplayType_IcLed) 
#ifdef DisplayTypeIcLedModel
#if (DisplayTypeIcLedModel==DisplayType_IcLed_tm1650) 

#define tm1650_Delay core_DelayUs 

bit tm1650_SendByte(unsigned char dat);

unsigned char *Tm1650_WriteBuffer;
unsigned char BrightSet=0;
unsigned char sendcase=5;
//******************************************************************************
//******************************************************************************





void tm1650_SendStart(void)
{
  	//发送START命令
  TM1650_CLK_OUT; TM1650_DIO_OUT;
	TM1650_CLK_H;  tm1650_Delay (5); TM1650_DIO_H; tm1650_Delay (10); 
	TM1650_DIO_L;  tm1650_Delay (5); TM1650_CLK_L; tm1650_Delay (10);
}

void tm1650_SendEnd(void)
{
    //发END命令
	tm1650_Delay (10); TM1650_DIO_L; TM1650_CLK_L; tm1650_Delay (10); 
	TM1650_CLK_H;  tm1650_Delay (5); TM1650_DIO_H; tm1650_Delay (10);
}


bit tm1650_SendByte(unsigned char dat)	
{
    static bit ackbit=0;
	unsigned char j;
    

	//发送一个字节+接收1位ACK
	for(j=0;j<9;j++)
	{
		TM1650_CLK_L;//拉低时钟信号

        if(j<8)
        {
            tm1650_Delay (5);
			if((dat&0x80)==0X80)
				{TM1650_DIO_H;}
			else
				{TM1650_DIO_L;}	
			dat<<=1; 
		}
        else
        {
          TM1650_DIO_IN;
          TM1650_DIO_H;
          tm1650_Delay(5);
          ackbit=TM1650_DIO; //获取ACK
          TM1650_DIO_OUT;
		  TM1650_DIO_L;
		}

		tm1650_Delay(5);
		TM1650_CLK_H;//拉高时钟信号
		tm1650_Delay(5);
        TM1650_CLK_L;//拉低时钟信号
		tm1650_Delay(5);
	}
 
	return ackbit; //返回ACK
}



void tm1650_SendDataRun(void)	
{
	if(sendcase>3)
	{
		//发送START命令
		tm1650_SendStart();
		//发送
		tm1650_SendByte(0x48);
		tm1650_SendByte((BrightSet|0x01));
		//发END命令
		tm1650_SendEnd();
		sendcase=0;
	}
	else
	{
		//发送START命令
		tm1650_SendStart();
		//发送DIG0位数据
		tm1650_SendByte(0x68+(sendcase<<1));
		tm1650_SendByte(Tm1650_WriteBuffer[sendcase]);
		//发END命令
		tm1650_SendEnd();
		
		sendcase++;
	}
}


void tm1650_init(void)
{
	TM1650_CLK_OUT;
	TM1650_DIO_OUT;
//    Aip650_SendDisBuffer();
//	Aip650_SendStart();
//	Aip650_Delay(10);
//	Aip650_SendEnd();
}

void tm1650_set_bright(unsigned char bright)	
{
	if(bright>7) bright=0;
	BrightSet=bright<<4;
}


#endif
#endif
#endif
#endif


