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
#if (DisplayTypeIcLedModel==DisplayType_IcLed_tm1628) 

#define tm1628_Delay core_DelayUs 

void tm1628_SendByte(unsigned char dat);


 unsigned char *Tm1628_WriteBuffer;

 unsigned char sendSelectAddr=0;
 unsigned char sendSelectData=0;

//******************************************************************************
//******************************************************************************
#define tm1628_SendStart SET_STB();tm1628_Delay(5);CLR_STB();
#define tm1628_SendEnd SET_STB();

#define tm1628_SendCmd(cmd) tm1628_SendStart;tm1628_SendByte((cmd));tm1628_SendEnd;
#define tm1628_SendData(addr,data) tm1628_SendStart;tm1628_SendByte((addr));tm1628_Delay(5);tm1628_SendByte((data));tm1628_SendEnd;

/*
void tm1628_SendData(unsigned char addr, unsigned char dat)
{
    SET_STB(); tm1628_Delay(5); CLR_STB();
    SendData(addr);
    tm1628_Delay(5);
    SendData(dat);
    SET_STB();
    tm1628_Delay(5);
} // TM1668_SendAddrData(unsigned char, unsigned char)   
*/


void tm1628_BrightSet(unsigned char flag)
{   
	if(flag>0) flag=((flag-1)|0x88); else flag=0x80;
	tm1628_SendCmd(flag);
} 




void tm1628_SendByte(unsigned char dat)
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

void tm1628_Init()
{
    INIT_TRIS();

    //发送显示模式设置
	tm1628_SendCmd(CFG_DISP_MODE_SETTING);

    //发送数据命令设置 // 0x44为固定地址模式，0x40为自动地址增加模式  
	tm1628_SendCmd(CFG_DATA_CMD_SETTING);
  
} // TM1668_Init()


void tm1628_SendDataRun(void)
{
		if(sendSelectAddr>0xC0) {sendSelectAddr--; sendSelectData++;}else {sendSelectAddr=0xcb;sendSelectData=0;}
		tm1628_SendData(sendSelectAddr,(Tm1628_WriteBuffer[sendSelectData]&0x03)|(Tm1628_WriteBuffer[sendSelectData]<<2));
		sendSelectAddr--;
		tm1628_SendData(sendSelectAddr,Tm1628_WriteBuffer[sendSelectData]);

}

#endif
#endif
#endif
#endif