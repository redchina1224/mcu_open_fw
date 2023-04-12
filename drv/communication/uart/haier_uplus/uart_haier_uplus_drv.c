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


#define UART_UPLUS_TXBUF UART_TXBUF_CH(UART_UPLUS_PORT_NUM)
#define UART_UPLUS_RXBUF UART_RXBUF_CH(UART_UPLUS_PORT_NUM)

mof_haier_uplus_uart_port_t haier_uplus_port;

void uart_haier_uplus_init()
{
	haier_uplus_port.S_Busy=0;
	haier_uplus_port.S_ReadCharWindows[0]=0;
	haier_uplus_port.S_ReadCharWindows[1]=0;
	haier_uplus_port.S_ReadPtr=0;
	haier_uplus_port.S_WritePtr=0;
	haier_uplus_port.S_ReadLength=0;
	haier_uplus_port.S_ReadTimeout=0;
	haier_uplus_port.S_WriteLength=0;
	haier_uplus_port.S_WriteAppendbytes=0;
	haier_uplus_port.S_Reading=0;
	haier_uplus_port.S_Writing=0;
	haier_uplus_port.S_ReadBuffer=0;
	haier_uplus_port.S_WriteBuffer=0;
	haier_uplus_port.S_ReadChecksumAdj=0;
	haier_uplus_port.S_WriteChecksumAdj=0;
}


void uart_haier_uplus_send(unsigned char writelength)//,unsigned char readlength)
{
	haier_uplus_port.S_Busy=1;
	haier_uplus_port.S_Writing=0;
	//haier_uplus_port.S_ReadLength=readlength;
	haier_uplus_port.S_WriteLength=writelength;
	//haier_uplus_port.S_ReadPtr=0;
	haier_uplus_port.S_WritePtr=0;//S_WritePtr=1;
	UART_UPLUS_TXBUF = 0xFF;//S_WriteBuffer[0];

}	

/***********************************************************************************************
*函数名 		: void UART1_TxIsr(unsigned char *TxReg)
*函数功能描述 	: 串口发送中断服务程序(用于数据连续发送)
*函数参数 		: unsigned char *RxReg：串口硬件发送缓存地址指针
*函数返回值 	: 无
***********************************************************************************************/
//void UART1_TxIsr(unsigned char *TxReg)
void uart_haier_uplus_tx_in_isr(void)
{
		if(haier_uplus_port.S_Writing==0)
		{
			UART_UPLUS_TXBUF=0xFF;

				haier_uplus_port.S_WritePtr=0;
				haier_uplus_port.S_Writing=1;
				haier_uplus_port.S_WriteAppendbytes=0;
		}
		else if(haier_uplus_port.S_Writing==1)
		{
			if(haier_uplus_port.S_WriteAppendbytes!=0)
			{
				UART_UPLUS_TXBUF=haier_uplus_port.S_WriteAppendbytes;
				haier_uplus_port.S_WriteAppendbytes=0;
			}
			else
			{
				//如果本次发送的字节是FF,下次追加发送55
				if(haier_uplus_port.S_WriteBuffer[haier_uplus_port.S_WritePtr]==0xff) haier_uplus_port.S_WriteAppendbytes=0x55;
				
				//发送缓存区数据
				if(haier_uplus_port.S_WritePtr<haier_uplus_port.S_WriteLength)
				{
					//(*TxReg) = haier_uplus_port.S_WriteBuffer[haier_uplus_port.S_WritePtr];
					UART_UPLUS_TXBUF = haier_uplus_port.S_WriteBuffer[haier_uplus_port.S_WritePtr];		
					haier_uplus_port.S_WritePtr++;
				}
				else
				{
					haier_uplus_port.S_Busy=0;
				}

			}
		}

}

/***********************************************************************************************
*函数名 		: void UART1_RxIsr(unsigned char *RxReg)
*函数功能描述 	: 串口接收中断服务程序(用于数据连续接收)
*函数参数 		: unsigned char *RxReg：串口硬件接收缓存地址指针
*函数返回值 	: 无
***********************************************************************************************/
#define ReadCharNow haier_uplus_port.S_ReadCharWindows[1]
#define ReadCharAgo haier_uplus_port.S_ReadCharWindows[0]

void uart_haier_uplus_rx_in_isr(void)
{
	haier_uplus_port.S_ReadTimeout=3;

	//两个字节的接收滚动窗口,用于接收数据和判断 （FF,FF）   （FF,55）
	ReadCharAgo=ReadCharNow;
	ReadCharNow=UART_UPLUS_RXBUF;
	
	if(haier_uplus_port.S_Reading==0)
	{
		if(ReadCharNow==0xFF) 
		{
			if(ReadCharAgo==0xFF)
			{
				haier_uplus_port.S_Reading=1;
				haier_uplus_port.S_ReadPtr=0;
				ReadCharAgo=0;
				ReadCharNow=0;
			}
		}
	}
	else if(haier_uplus_port.S_Reading==1)
	{
		//haier_uplus_port.S_ReadBuffer[haier_uplus_port.S_ReadPtr] = (*RxReg);
		haier_uplus_port.S_ReadBuffer[haier_uplus_port.S_ReadPtr] = ReadCharNow;

		//获取帧长度
		if(haier_uplus_port.S_ReadPtr==0)
		{
			//如果带CRC校验,长度为帧长加2
			//haier_uplus_port.S_ReadLength=haier_uplus_port.S_ReadBuffer[0]+2;//此数据长度为数据+校验和的长度,不包含CRC校验数据,实际接收数据需在此基础上加2

			//如果不带CRC校验,长度为帧长
			haier_uplus_port.S_ReadLength=haier_uplus_port.S_ReadBuffer[0];//此数据长度为数据+校验和的长度,不包含CRC校验数据,实际接收数据需在此基础上加2
			
			
			haier_uplus_port.S_ReadChecksumAdj=0;//初始化校验和修正值
		}
		else if(ReadCharAgo==0xff) //判定前一个数据是FF
		{
			if(ReadCharNow==0x55)
			{
				if(haier_uplus_port.S_ReadPtr<=(haier_uplus_port.S_ReadBuffer[0])) haier_uplus_port.S_ReadChecksumAdj-=0x55;//因为校验和包含数据中的55,需要保留调整值
				return;//如果是插入的55,重新接收以去除这个55跳过后面的接收指针累加
			}
			else if(ReadCharNow==0xFF) //如果是FF,表示连续收到两个FF,重新开始接收
			{
				haier_uplus_port.S_Reading=1;
				haier_uplus_port.S_ReadPtr=0;
				ReadCharAgo=0;
				ReadCharNow=0;
				return;//跳过后面的接收指针累加		
			}				
		}
	
		if(haier_uplus_port.S_ReadPtr<(haier_uplus_port.S_ReadLength)) haier_uplus_port.S_ReadPtr++;
		else
		{		
			haier_uplus_port.S_ReadBuffer[haier_uplus_port.S_ReadBuffer[0]]+=haier_uplus_port.S_ReadChecksumAdj;
			haier_uplus_port.S_Reading=200; //接收完成,停止接收,等待主循环处理数据
		}

	}
	
}