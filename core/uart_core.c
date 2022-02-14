//******************************************************************************
//Copyright(C) 2020-2021 zhejiang zhida dianzikeji Co., Ltd
//浙江智达电子科技有限公司
//File name:      uart_core.c
//Author:         zzg
//Version:        Ver0.1
//Date:           2021-4-25
//Description:    UART标准API接口
//History:
//******************************************************************************
//头文件************************************************************************
#include "core.h"


//struct struct_uartdata uart1data;

bit S1_Busy=0;
unsigned char S1ReadStartChar=0;
unsigned char S1ReadPtr=0;
unsigned char S1WritePtr=0;
unsigned char S1ReadLength=0;
unsigned char S1ReadTimeout=0;
unsigned char S1WriteLength=0;
unsigned char S1Reading=0;
unsigned char *S1ReadBuffer;
unsigned char *S1WriteBuffer;



/***********************************************************************************************
*函数名 		: void Uart1Init(void)
*函数功能描述 	: 串口1初始化
*函数参数 		: 无
*函数返回值 	: 无
***********************************************************************************************/
void Uart1Init(void)		//9600bps@33.1776MHz
{


}

/***********************************************************************************************
*函数名 		: Uart1Send(unsigned char writelength)
*函数功能描述 	: 串口发送启动
*函数参数 		: unsigned char writelength：缓冲区填冲待发数据的长度
*函数返回值 	: 无
***********************************************************************************************/
void Uart1Send(unsigned char writelength)//,unsigned char readlength)
{
	S1_Busy=1;
	//S1Reading=2;
	//S1ReadLength=readlength;
	S1WriteLength=writelength;
	//S1ReadPtr=0;
	S1WritePtr=1;
	ZD_UART1_TXBUF = S1WriteBuffer[0];

}	


/***********************************************************************************************
*函数名 		: void UART1_TxIsr(unsigned char *TxReg)
*函数功能描述 	: 串口发送中断服务程序(用于数据连续发送)
*函数参数 		: unsigned char *RxReg：串口硬件发送缓存地址指针
*函数返回值 	: 无
***********************************************************************************************/
void UART1_TxIsr(unsigned char *TxReg)
{
	if(S1WritePtr<S1WriteLength)
	{
		(*TxReg) = S1WriteBuffer[S1WritePtr];
		S1WritePtr++;
	}
	else
	{
		S1_Busy=0;
	}
}

/***********************************************************************************************
*函数名 		: void UART1_RxIsr(unsigned char *RxReg)
*函数功能描述 	: 串口接收中断服务程序(用于数据连续接收)
*函数参数 		: unsigned char *RxReg：串口硬件接收缓存地址指针
*函数返回值 	: 无
***********************************************************************************************/
void UART1_RxIsr(unsigned char *RxReg)
{
	S1ReadTimeout=3;
	S1ReadBuffer[S1ReadPtr] = (*RxReg);
	if(S1ReadPtr<S1ReadLength) S1ReadPtr++;
	//if(S1ReadLength==S1ReadPtr&&2==S1Reading) S1Reading=1;
}




/************************ (C) COPYRIGHT zhejiang zhida *****END OF FILE****/