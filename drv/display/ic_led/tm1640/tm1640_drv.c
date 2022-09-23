//******************************************************************************
//Copyright(C) 2020-2021 zhejiang zhida dianzikeji Co., Ltd
//浙江智达电子科技有限公司
//File name:      TM1640.c
//Author:         zzg
//Version:        Ver0.1
//Date:           2021-4-25
//Description:    tm1640驱动
//History:
//******************************************************************************
//头文件************************************************************************
#include "..\..\..\com_include_drv.h"
//******************************************************************************
#ifdef DisplayType
#if ((DisplayType&DisplayType_IcLed)==DisplayType_IcLed) 
#ifdef DisplayTypeIcLedModel
#if (DisplayTypeIcLedModel==DisplayType_IcLed_tm1640) 

#define tm1640_Delay core_DelayUs 

void tm1640_SendByte(unsigned char dat);


 unsigned char *tm1640_WriteBuffer;

 unsigned char sendSelectAddr=0;
 unsigned char sendSelectData=0;

//******************************************************************************
//******************************************************************************
#define tm1640_SendStart SET_SCLK();SET_DIO();tm1640_Delay(5);CLR_DIO();tm1640_Delay(5);CLR_SCLK();
#define tm1640_SendEnd CLR_SCLK();CLR_DIO();tm1640_Delay(5);SET_SCLK();tm1640_Delay(5);SET_DIO();

#define tm1640_SendCmd(cmd) tm1640_SendStart;tm1640_SendByte((cmd));tm1640_SendEnd;
#define tm1640_SendData(addr,dat) tm1640_SendStart;tm1640_SendByte((addr));tm1640_Delay(5);tm1640_SendByte((dat));tm1640_SendEnd;

/*
void tm1640_SendData(unsigned char addr, unsigned char dat)
{
    SET_STB(); tm1640_Delay(5); CLR_STB();
    SendData(addr);
    tm1640_Delay(5);
    SendData(dat);
    SET_STB();
    tm1640_Delay(5);
} // TM1668_SendAddrData(unsigned char, unsigned char)   
*/


void tm1640_BrightSet(unsigned char flag)
{   
	if(flag>0) flag=((flag-1)|0x88); else flag=0x80;
	tm1640_SendCmd(flag);
} 




void tm1640_SendByte(unsigned char dat)
{
    unsigned char i;

    CLR_SCLK();
    for (i = 0x01; i != 0x00; i <<= 1) 
		{                              
				tm1640_Delay(5);
				if (dat & i) {
						SET_DIO();
				}
				else {
						CLR_DIO();
				}
				SET_SCLK();
				tm1640_Delay(5);
				CLR_SCLK();
		}
}

void tm1640_Init()
{
    INIT_TRIS();

    //发送显示模式设置
		tm1640_SendCmd(CFG_DISP_MODE_SETTING);

    //发送数据命令设置 // 0x44为固定地址模式，0x40为自动地址增加模式  
		tm1640_SendCmd(CFG_DATA_CMD_SETTING);
	
		sendSelectAddr=0xC0;sendSelectData=0;
  
} // TM1640_Init()


void tm1640_SendDataRun(void)
{
		tm1640_SendData(sendSelectAddr,tm1640_WriteBuffer[sendSelectData]);
		if(sendSelectAddr<0xCF) {sendSelectAddr++; sendSelectData++;}else {sendSelectAddr=0xC0;sendSelectData=0;}

}

#endif
#endif
#endif
#endif