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


#define UART_FIXED_LENGTH_TXBUF UART_TXBUF_CH(UART_FIXED_LENGTH_PORT_NUM)
#define UART_FIXED_LENGTH_RXBUF UART_RXBUF_CH(UART_FIXED_LENGTH_PORT_NUM)

mof_fix_length_uart_port_t fixed_length_port;

#ifdef UART_FIXED_LENGTH_RX_LENGTH
void uart_fixed_length_init(unsigned char *txbuf,unsigned char *rxbuf)
#else
void uart_fixed_length_init(unsigned char *txbuf,unsigned char *rxbuf,unsigned char rxlen)
#endif
{
	fixed_length_port.Busy=0;
	fixed_length_port.ReadPtr=0;
	fixed_length_port.WritePtr=0;
	
#ifdef UART_FIXED_LENGTH_RX_LENGTH
	fixed_length_port.ReadLength=0;
#else
	fixed_length_port.ReadLength=rxlen;
#endif

	fixed_length_port.ReadTimeout=0;
	fixed_length_port.WriteLength=0;
	fixed_length_port.Reading=0;
	fixed_length_port.Writing=0;
	fixed_length_port.p_ReadBuffer=rxbuf;
	fixed_length_port.p_WriteBuffer=txbuf;
}

#ifdef UART_FIXED_LENGTH_RX_LENGTH
void uart_fixed_length_send(unsigned char writelength)//,unsigned char readlength)
#else
void uart_fixed_length_send(unsigned char writelength,unsigned char readlength)
#endif
{
	fixed_length_port.Busy=1;
	fixed_length_port.Writing=0;
	//fixed_length_port.ReadLength=readlength;
	fixed_length_port.WriteLength=writelength;
	fixed_length_port.ReadPtr=0;
	fixed_length_port.WritePtr=0;
	UART_FIXED_LENGTH_TXBUF = fixed_length_port.p_WriteBuffer[0];

}	

void uart_fixed_length_read_reset(void)
{
			fixed_length_port.ReadPtr=0;
			fixed_length_port.ReadTimeout=0;
			fixed_length_port.Reading=0;
}

unsigned char uart_fixed_length_ReadOverCheck(void)
{
	if(mSec_x100_workbit&&fixed_length_port.ReadTimeout>0) fixed_length_port.ReadTimeout--;
	if(200==fixed_length_port.Reading)
	{
	#ifdef UART_FIXED_LENGTH_RX_LENGTH
		if(fixed_length_port.ReadPtr==UART_FIXED_LENGTH_RX_LENGTH) //必需大于4个字节才有效
	#else
		if(fixed_length_port.ReadPtr==fixed_length_port.ReadLength) //必需大于4个字节才有效
	#endif
		{
			fixed_length_port.ReadLength=fixed_length_port.ReadPtr;
			return 1;
		}
		else //接收帧头失败或者未达到指定接收长度
		{
			//恢复并重新开始接收数据
			fixed_length_port.ReadPtr=0;
			fixed_length_port.ReadTimeout=0;
			fixed_length_port.Reading=0;
		}
	}
	
	return 0;
}


/***********************************************************************************************
*函数名 		: void UART1_TxIsr(unsigned char *TxReg)
*函数功能描述 	: 串口发送中断服务程序(用于数据连续发送)
*函数参数 		: unsigned char *RxReg：串口硬件发送缓存地址指针
*函数返回值 	: 无
***********************************************************************************************/
//void UART1_TxIsr(unsigned char *TxReg)
void uart_fixed_length_tx_in_isr(void)
{
		//发送缓存区数据
		if(++fixed_length_port.WritePtr<fixed_length_port.WriteLength)
		{
			UART_FIXED_LENGTH_TXBUF = fixed_length_port.p_WriteBuffer[fixed_length_port.WritePtr];		
		}
		else
		{
			fixed_length_port.Busy=0;
		}

}

/***********************************************************************************************
*函数名 		: void UART1_RxIsr(unsigned char *RxReg)
*函数功能描述 	: 串口接收中断服务程序(用于数据连续接收)
*函数参数 		: unsigned char *RxReg：串口硬件接收缓存地址指针
*函数返回值 	: 无
***********************************************************************************************/
void uart_fixed_length_rx_in_isr(void)
{

	//如果前一次接收未处理,停止接收以免缓存区被破坏
	if(fixed_length_port.Reading==200) return;
	
	//如果接收已超时,重新开始接收
	if(fixed_length_port.ReadTimeout==0) fixed_length_port.ReadPtr=0;

	//取接收数据
	fixed_length_port.p_ReadBuffer[fixed_length_port.ReadPtr]=UART_FIXED_LENGTH_RXBUF;
	
	//接收指定长度后结束
	#ifdef UART_FIXED_LENGTH_RX_LENGTH
	if(++fixed_length_port.ReadPtr>=(UART_FIXED_LENGTH_RX_LENGTH)) 
	#else
	if(++fixed_length_port.ReadPtr>=(fixed_length_port.ReadLength)) 
	#endif
	{		
		fixed_length_port.Reading=200; //接收完成,停止接收,等待主循环处理数据
	}
	
	//设置接收超时时间
	fixed_length_port.ReadTimeout=3;	
}