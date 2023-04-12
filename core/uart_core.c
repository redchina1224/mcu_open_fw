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




/************************ (C) COPYRIGHT zhejiang zhida *****END OF FILE****/