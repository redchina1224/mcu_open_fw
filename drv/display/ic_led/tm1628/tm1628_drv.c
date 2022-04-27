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
#if (DisplayType==DisplayType_Dig8IcLed_tm1628) 

#define tm1628_Delay core_DelayUs 

void SendData(unsigned char dat);


 unsigned char *Tm1628_WriteBuffer;
//******************************************************************************
//******************************************************************************


void TM1628_SendAddrData(unsigned char addr, unsigned char dat)
{
    SET_STB();
    tm1628_Delay(5);
    CLR_STB();
    SendData(addr);
    tm1628_Delay(5);
    SendData(dat);
    SET_STB();
    tm1628_Delay(5);
} // TM1668_SendAddrData(unsigned char, unsigned char)   





void TM1628_Switch(unsigned char flag)
{   
	CLR_STB();
    SendData((unsigned char)M_DISP_CTRL_SETTING(flag));
    SET_STB();
} 




void SendData(unsigned char dat)
{
    unsigned char i;

    CLR_SCLK();
    for (i = 0x01; i != 0x00; i <<= 1) 
		{                              
				tm1628_Delay(5);
				if (dat & i) {
						SET_DIO();
				}
				else {
						CLR_DIO();
				}
				SET_SCLK();
				tm1628_Delay(5);
				CLR_SCLK();
		}


}

void TM1628_Init()
{
    INIT_TRIS();
    SET_STB();
    tm1628_Delay(10);

    // 发送显示模式设置
    CLR_STB();
    SendData(CFG_DISP_MODE_SETTING);
    SET_STB();
    tm1628_Delay(5);
    // 发送数据命令设置 // 0x44为固定地址模式，0x40为自动地址增加模式  
    CLR_STB();
		tm1628_Delay(10);
    SendData(CFG_DATA_CMD_SETTING);
    SET_STB();
    tm1628_Delay(5);

    // 发送显示控制
    CLR_STB();
    SendData(M_DISP_CTRL_SETTING(1));
    SET_STB();
    tm1628_Delay(5); 

		//1628位段初始化。
		TM1628_SendAddrData(0xC0,Tm1628_WriteBuffer[5]);
		TM1628_SendAddrData(0xC1,(Tm1628_WriteBuffer[5]&0x03)|(Tm1628_WriteBuffer[5]<<2));
		TM1628_SendAddrData(0xC2,Tm1628_WriteBuffer[4]);
		TM1628_SendAddrData(0xC3,(Tm1628_WriteBuffer[4]&0x03)|(Tm1628_WriteBuffer[4]<<2));
		TM1628_SendAddrData(0xC4,Tm1628_WriteBuffer[3]);
		TM1628_SendAddrData(0xC5,(Tm1628_WriteBuffer[3]&0x03)|(Tm1628_WriteBuffer[3]<<2));		
		TM1628_SendAddrData(0xC6,Tm1628_WriteBuffer[2]);
		TM1628_SendAddrData(0xC7,(Tm1628_WriteBuffer[2]&0x03)|(Tm1628_WriteBuffer[2]<<2));
		TM1628_SendAddrData(0xC8,Tm1628_WriteBuffer[1]);
		TM1628_SendAddrData(0xC9,(Tm1628_WriteBuffer[1]&0x03)|(Tm1628_WriteBuffer[1]<<2));
		TM1628_SendAddrData(0xCA,Tm1628_WriteBuffer[0]);
		TM1628_SendAddrData(0xCB,(Tm1628_WriteBuffer[0]&0x03)|(Tm1628_WriteBuffer[0]<<2));
		//TM1628_SendAddrData(0xCC,0Xff);
		//TM1628_SendAddrData(0xCD,0Xff);
		//TM1628_SendAddrData(0xCE,0XFF);
		//TM1628_SendAddrData(0xCF,0XFF);
      
} // TM1668_Init()

#endif
#endif