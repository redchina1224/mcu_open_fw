//******************************************************************************
//Copyright(C) 2020-2021 zhejiang zhida dianzikeji Co., Ltd
//浙江智达电子科技有限公司
//File name:      TM1621c.c
//Author:         zzg
//Version:        Ver0.1
//Date:           2021-4-25
//Description:    TM1621c驱动
//History:
//******************************************************************************
//头文件************************************************************************
#include "..\..\..\com_include_drv.h"
//******************************************************************************
#ifdef DisplayType
#if (DisplayType==DisplayType_Dig8IcLcd_tm1621c) 

#define tm1621c_Delay core_DelayUs 


#define TM_WRITE 0x140

#define TM_CMD 0x800
#define TM_CMD_SYS_DIS (TM_CMD|0x00)
#define TM_CMD_SYS_EN (TM_CMD|0x02)
#define TM_CMD_LCD_OFF (TM_CMD|0x04)
#define TM_CMD_LCD_ON (TM_CMD|0x06)
#define TM_CMD_CLK_XTAL32K (TM_CMD|0x28)
#define TM_CMD_CLK_RC256K (TM_CMD|0x30)
#define TM_CMD_BAIS_1DIV2_4COM (TM_CMD|0x50)

/*
 const unsigned char Tm1621c_AddrList[9][2]={
	{0,1},
	{2,3},
	{4,5},
	{13,14},
	{15,16},
	{17,18},
	{19,26},
	{27,28},
	{29,30},	
 };
*/

 const unsigned char Tm1621c_AddrList[7][2]={
	{5,13},
	{14,15},
	{16,17},
	{18,19},
	{26,27},
	{28,29},
	{30,0},
 };

 unsigned char *Tm1621c_WriteBuffer;

 unsigned char sendSelectAddr=0;


//******************************************************************************
//******************************************************************************

void GpioSpiSendData(unsigned int data,unsigned char startbit,unsigned char bitlen)
{
	unsigned char i;
	unsigned int bitmask=(1<<startbit);
	
    for (i = 0; i<bitlen; i++) 
	{            
		Tm1621c_WRN_IO_Ctrl(0);        
		tm1621c_Delay(5);
		if (data &bitmask)
		{
			Tm1621c_DATA_IO_Ctrl(1);
		}
		else
		{
			Tm1621c_DATA_IO_Ctrl(0);
		}
		
		if(startbit==0)
			data>>=1;
		else
			data<<=1;
			
		tm1621c_Delay(5);
		Tm1621c_WRN_IO_Ctrl(1);
		tm1621c_Delay(5);
	}
}


#define SendCmd(x) GpioSpiSendData(x,11,12)
#define SendAddr(x) GpioSpiSendData(x,8,9)
#define SendData(x) GpioSpiSendData(x,0,4)


void TM1621C_SendAddrData(unsigned int addr, unsigned char dat)
{
    Tm1621c_CSN_IO_Ctrl(1);
    tm1621c_Delay(10);
    Tm1621c_CSN_IO_Ctrl(0);
	SendAddr((addr|TM_WRITE));
    tm1621c_Delay(5);
    SendData(dat);
    Tm1621c_CSN_IO_Ctrl(1);
    tm1621c_Delay(10);
} // TM1668_SendAddrData(unsigned char, unsigned char)   

void TM1621C_SendCommand(unsigned int cmd)
{
    Tm1621c_CSN_IO_Ctrl(0);
    tm1621c_Delay(10);
    SendCmd(cmd);
    Tm1621c_CSN_IO_Ctrl(1);
    tm1621c_Delay(10);
} // TM1668_SendAddrData(unsigned char, unsigned char)   



void TM1621C_Init(void)
{
    Tm1621c_IO_Init;
    Tm1621c_CSN_IO_Ctrl(1);
    tm1621c_Delay(10);


    //发送显示模式设置--偏压与COM
	TM1621C_SendCommand(TM_CMD_BAIS_1DIV2_4COM);
	
    //发送振荡器设置--打开振荡器
    TM1621C_SendCommand(TM_CMD_SYS_EN);
	
    //发送显示控制--开启和关闭
    TM1621C_SendCommand(TM_CMD_LCD_ON);

	//1628位段初始化。
	/*
	TM1621C_SendAddrData(Tm1621c_AddrList[0][0],Tm1621c_WriteBuffer[0]&0x0f);
	TM1621C_SendAddrData(Tm1621c_AddrList[0][1],(Tm1621c_WriteBuffer[0]>>4)&0x0f);
	
	TM1621C_SendAddrData(Tm1621c_AddrList[1][0],Tm1621c_WriteBuffer[1]&0x0f);
	TM1621C_SendAddrData(Tm1621c_AddrList[1][1],(Tm1621c_WriteBuffer[1]>>4)&0x0f);
	
	TM1621C_SendAddrData(Tm1621c_AddrList[2][0],Tm1621c_WriteBuffer[2]&0x0f);
	TM1621C_SendAddrData(Tm1621c_AddrList[2][1],(Tm1621c_WriteBuffer[2]>>4)&0x0f);
	
	TM1621C_SendAddrData(Tm1621c_AddrList[3][0],Tm1621c_WriteBuffer[3]&0x0f);
	TM1621C_SendAddrData(Tm1621c_AddrList[3][1],(Tm1621c_WriteBuffer[3]>>4)&0x0f);
	
	TM1621C_SendAddrData(Tm1621c_AddrList[4][0],Tm1621c_WriteBuffer[4]&0x0f);
	TM1621C_SendAddrData(Tm1621c_AddrList[4][1],(Tm1621c_WriteBuffer[4]>>4)&0x0f);
	
	TM1621C_SendAddrData(Tm1621c_AddrList[5][0],Tm1621c_WriteBuffer[5]&0x0f);
	TM1621C_SendAddrData(Tm1621c_AddrList[5][1],(Tm1621c_WriteBuffer[5]>>4)&0x0f);
	
	TM1621C_SendAddrData(Tm1621c_AddrList[6][0],Tm1621c_WriteBuffer[6]&0x0f);
	TM1621C_SendAddrData(Tm1621c_AddrList[6][1],(Tm1621c_WriteBuffer[6]>>4)&0x0f);
	
	TM1621C_SendAddrData(Tm1621c_AddrList[7][0],Tm1621c_WriteBuffer[7]&0x0f);
	TM1621C_SendAddrData(Tm1621c_AddrList[7][1],(Tm1621c_WriteBuffer[7]>>4)&0x0f);
	
	TM1621C_SendAddrData(Tm1621c_AddrList[8][0],Tm1621c_WriteBuffer[8]&0x0f);
	TM1621C_SendAddrData(Tm1621c_AddrList[8][1],(Tm1621c_WriteBuffer[8]>>4)&0x0f);
*/
      
} // TM1668_Init()


void TM1621C_SendDataRun(void)
{

	TM1621C_SendAddrData(Tm1621c_AddrList[sendSelectAddr][0],Tm1621c_WriteBuffer[sendSelectAddr]&0x0f);
	TM1621C_SendAddrData(Tm1621c_AddrList[sendSelectAddr][1],(Tm1621c_WriteBuffer[sendSelectAddr]>>4)&0x0f);	

	if(++sendSelectAddr>=DISPLAY_WR_BUFFER_LENGTH) sendSelectAddr=0;

}


#endif
#endif