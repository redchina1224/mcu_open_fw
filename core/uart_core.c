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
#include "com_include_core.h"


//struct struct_uartdata uart1data;

bit S1_Busy=0;
unsigned char S1ReadCharWindows[2]={0,0};
unsigned char S1ReadPtr=0;
unsigned char S1WritePtr=0;
unsigned char S1ReadLength=0;
unsigned char S1ReadTimeout=0;
unsigned char S1WriteLength=0;
unsigned char S1WriteAppendbytes=0;
unsigned char S1Reading=0;
unsigned char S1Writing=0;
unsigned char *S1ReadBuffer;
unsigned char *S1WriteBuffer;
unsigned char S1ReadChecksumAdj=0;
unsigned char S1WriteChecksumAdj=0;


/***************************************************
*函数名 		: zd_adcChannleInit
*函数功能描述 	: ADC通道初始化
*函数参数 		: adcChannel:采集通道,*callback:采集周期完成后的回调函数
*函数返回值 	: 无
***************************************************/
unsigned char mof_UartInit(unsigned char uartNumber,unsigned char uartChannel,unsigned long baudrate)
{

	unsigned char cfgerr=1;
	switch(uartNumber)
	{
		#ifdef MOF_UART0_ENABLE 
		case 0:
			//配置UART时钟
			MOF_UART0_CLKSET(MOF_UART_CLKSET_DEFAULT);

			//配置UART时钟
			MOF_UART0_BAUDRATE(baudrate);

			//配置串口通道
			MOF_UART0_CH0_ENABLE; 
		
			//使能串口
			MOF_UART0_ENABLE;
			cfgerr=0; 
		break;
		#endif
		#ifdef MOF_UART1_ENABLE 
		case 1:
			//配置UART时钟
			MOF_UART1_CLKSET(MOF_UART_CLKSET_DEFAULT);

			//配置UART时钟
			MOF_UART1_BAUDRATE(baudrate);

			//配置串口通道
			#ifdef MOF_UART1_CH0_ENABLE
			if(uartChannel==0) MOF_UART1_CH0_ENABLE; 
			#endif
		
			//使能串口
			MOF_UART1_ENABLE;
			cfgerr=0; 
		break;
		#endif
		#ifdef MOF_UART2_ENABLE 
		case 2:
			//配置UART时钟
			MOF_UART2_CLKSET(MOF_UART_CLKSET_DEFAULT);

			//配置UART时钟
			MOF_UART2_BAUDRATE(baudrate);

			//配置串口通道
			MOF_UART2_CH0_ENABLE; 
		
			//使能串口
			MOF_UART2_ENABLE;
			cfgerr=0; 
		break;
		#endif

		default:break;
	}
	return cfgerr;

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
	S1Writing=0;
	//S1ReadLength=readlength;
	S1WriteLength=writelength;
	//S1ReadPtr=0;
	S1WritePtr=0;//S1WritePtr=1;
	MOF_UART1_TXBUF = 0xFF;//S1WriteBuffer[0];

}	


/***********************************************************************************************
*函数名 		: void UART1_TxIsr(unsigned char *TxReg)
*函数功能描述 	: 串口发送中断服务程序(用于数据连续发送)
*函数参数 		: unsigned char *RxReg：串口硬件发送缓存地址指针
*函数返回值 	: 无
***********************************************************************************************/
//void UART1_TxIsr(unsigned char *TxReg)
void UART1_TxIsr(void)
{
		if(S1Writing==0)
		{
			MOF_UART1_TXBUF=0xFF;

				S1WritePtr=0;
				S1Writing=1;
				S1WriteAppendbytes=0;
		}
		else if(S1Writing==1)
		{
			if(S1WriteAppendbytes!=0)
			{
				MOF_UART1_TXBUF=S1WriteAppendbytes;
				S1WriteAppendbytes=0;
			}
			else
			{
				//如果本次发送的字节是FF,下次追加发送55
				if(S1WriteBuffer[S1WritePtr]==0xff) S1WriteAppendbytes=0x55;
				
				//发送缓存区数据
				if(S1WritePtr<S1WriteLength)
				{
					//(*TxReg) = S1WriteBuffer[S1WritePtr];
					MOF_UART1_TXBUF = S1WriteBuffer[S1WritePtr];		
					S1WritePtr++;
				}
				else
				{
					S1_Busy=0;
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
#define S1ReadCharNow S1ReadCharWindows[1]
#define S1ReadCharAgo S1ReadCharWindows[0]

//void UART1_RxIsr(unsigned char *RxReg)
void UART1_RxIsr(void)
{
	S1ReadTimeout=3;

	//两个字节的接收滚动窗口,用于接收数据和判断 （FF,FF）   （FF,55）
	S1ReadCharAgo=S1ReadCharNow;
	S1ReadCharNow=MOF_UART1_RXBUF;
	
	if(S1Reading==0)
	{
		if(S1ReadCharNow==0xFF) 
		{
			if(S1ReadCharAgo==0xFF)
			{
				S1Reading=1;
				S1ReadPtr=0;
				S1ReadCharAgo=0;
				S1ReadCharNow=0;
			}
		}
	}
	else if(S1Reading==1)
	{
		//S1ReadBuffer[S1ReadPtr] = (*RxReg);
		S1ReadBuffer[S1ReadPtr] = S1ReadCharNow;

		//获取帧长度
		if(S1ReadPtr==0)
		{
			//如果带CRC校验,长度为帧长加2
			//S1ReadLength=S1ReadBuffer[0]+2;//此数据长度为数据+校验和的长度,不包含CRC校验数据,实际接收数据需在此基础上加2

			//如果不带CRC校验,长度为帧长
			S1ReadLength=S1ReadBuffer[0];//此数据长度为数据+校验和的长度,不包含CRC校验数据,实际接收数据需在此基础上加2
			
			
			S1ReadChecksumAdj=0;//初始化校验和修正值
		}
		else if(S1ReadCharAgo==0xff) //判定前一个数据是FF
		{
			if(S1ReadCharNow==0x55)
			{
				if(S1ReadPtr<=(S1ReadBuffer[0])) S1ReadChecksumAdj-=0x55;//因为校验和包含数据中的55,需要保留调整值
				return;//如果是插入的55,重新接收以去除这个55跳过后面的接收指针累加
			}
			else if(S1ReadCharNow==0xFF) //如果是FF,表示连续收到两个FF,重新开始接收
			{
				S1Reading=1;
				S1ReadPtr=0;
				S1ReadCharAgo=0;
				S1ReadCharNow=0;
				return;//跳过后面的接收指针累加		
			}				
		}
	
		if(S1ReadPtr<(S1ReadLength)) S1ReadPtr++;
		else
		{		
			S1ReadBuffer[S1ReadBuffer[0]]+=S1ReadChecksumAdj;
			S1Reading=200; //接收完成,停止接收,等待主循环处理数据
		}

	}
	
}




/************************ (C) COPYRIGHT zhejiang zhida *****END OF FILE****/