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
#ifdef CommunicationTypeUartModel
#if ((CommunicationTypeUartModel&CommunicationType_Uart_Tuya)==CommunicationType_Uart_Tuya)

#define UART_TUYA_TXBUF UART_TXBUF_CH(UART_TUYA_PORT_NUM)
#define UART_TUYA_RXBUF UART_RXBUF_CH(UART_TUYA_PORT_NUM)

mof_tuya_uart_port_t xdata tuya_port;

void uart_tuya_init(unsigned char *txbuf,unsigned char *rxbuf)
{
	tuya_port.Busy=0;
	tuya_port.ReadCharWindows[0]=0;
	tuya_port.ReadCharWindows[1]=0;
	tuya_port.ReadPtr=0;
	tuya_port.WritePtr=0;
	tuya_port.ReadLength=0;
	tuya_port.ReadTimeout=0;
	tuya_port.WriteLength=0;
	tuya_port.WriteAppendbytes=0;
	tuya_port.Reading=0;
	tuya_port.Writing=0;
	tuya_port.p_ReadBuffer=rxbuf;
	tuya_port.p_WriteBuffer=txbuf;
	tuya_port.ReadChecksumAdj=0;
	tuya_port.WriteChecksumAdj=0;
}


void uart_tuya_send(unsigned char writelength)//,unsigned char readlength)
{
	tuya_port.Busy=1;
	tuya_port.Writing=0;
	//tuya_port.ReadLength=readlength;
	tuya_port.WriteLength=writelength;
	//tuya_port.ReadPtr=0;
	tuya_port.WritePtr=0;//S_WritePtr=1;
	UART_TUYA_TXBUF = 0x55;//S_WriteBuffer[0];

}	

/***********************************************************************************************
*函数名 		: void UART1_TxIsr(unsigned char *TxReg)
*函数功能描述 	: 串口发送中断服务程序(用于数据连续发送)
*函数参数 		: unsigned char *RxReg：串口硬件发送缓存地址指针
*函数返回值 	: 无
***********************************************************************************************/
//void UART1_TxIsr(unsigned char *TxReg)
void uart_tuya_tx_in_isr(void)
{
		if(tuya_port.Writing==0)
		{
			UART_TUYA_TXBUF=0xAA;

				tuya_port.WritePtr=0;
				tuya_port.Writing=1;
		}
		else if(tuya_port.Writing==1)
		{
				//发送缓存区数据
				if(tuya_port.WritePtr<tuya_port.WriteLength)
				{
					UART_TUYA_TXBUF = tuya_port.p_WriteBuffer[tuya_port.WritePtr];		
					tuya_port.WritePtr++;
				}
				else
				{
					tuya_port.Busy=0;
				}
		}

}

/***********************************************************************************************
*函数名 		: void UART1_RxIsr(unsigned char *RxReg)
*函数功能描述 	: 串口接收中断服务程序(用于数据连续接收)
*函数参数 		: unsigned char *RxReg：串口硬件接收缓存地址指针
*函数返回值 	: 无
***********************************************************************************************/
#define ReadCharNow tuya_port.ReadCharWindows[1]
#define ReadCharAgo tuya_port.ReadCharWindows[0]

void uart_tuya_rx_in_isr(void)
{

	//两个字节的接收滚动窗口,用于接收数据和判断 （55,AA）
	ReadCharAgo=ReadCharNow;
	ReadCharNow=UART_TUYA_RXBUF;

	if(tuya_port.Reading==200) return;

	tuya_port.ReadTimeout=3;
	
	if(tuya_port.Reading==0)
	{
		if(ReadCharNow==0xAA) 
		{
			if(ReadCharAgo==0x55)
			{
				tuya_port.Reading=1;
				tuya_port.ReadPtr=0;
				ReadCharAgo=0;
				ReadCharNow=0;
				//tuya_port.ReadChecksumAdj=(0x55+0xaa);//初始化校验和修正值
			}
		}
	}
	else if(tuya_port.Reading==1)
	{

		tuya_port.p_ReadBuffer[tuya_port.ReadPtr] = ReadCharNow;

		//获取协议版本帧长度
		if(tuya_port.ReadPtr<3) tuya_port.ReadPtr++;
		else if(tuya_port.ReadPtr==3)
		{
			tuya_port.ReadLength=((ReadCharAgo<<8)|(ReadCharNow))+5; //(1版本+1命令字+2数据长+N数据+1校验)
			tuya_port.Reading=2;
			tuya_port.ReadPtr=4;
		}
	}
	else if(tuya_port.Reading==2)
	{

		tuya_port.p_ReadBuffer[tuya_port.ReadPtr] = ReadCharNow;
		tuya_port.ReadPtr++;
		
		if(tuya_port.ReadPtr>=(tuya_port.ReadLength))
		{		
			tuya_port.Reading=200; //接收完成,停止接收,等待主循环处理数据
		}

	}
	
}

#endif
#endif