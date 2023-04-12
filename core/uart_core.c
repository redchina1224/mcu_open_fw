//******************************************************************************
//Copyright(C) 2020-2021 zhejiang zhida dianzikeji Co., Ltd
//�㽭�Ǵ���ӿƼ����޹�˾
//File name:      uart_core.c
//Author:         zzg
//Version:        Ver0.1
//Date:           2021-4-25
//Description:    UART��׼API�ӿ�
//History:
//******************************************************************************
//ͷ�ļ�************************************************************************
#include "com_include_core.h"




/***************************************************
*������ 		: zd_adcChannleInit
*������������ 	: ADCͨ����ʼ��
*�������� 		: adcChannel:�ɼ�ͨ��,*callback:�ɼ�������ɺ�Ļص�����
*��������ֵ 	: ��
***************************************************/
unsigned char mof_UartInit(unsigned char uartNumber,unsigned char uartChannel,unsigned long baudrate)
{

	unsigned char cfgerr=1;
	switch(uartNumber)
	{
		#ifdef MOF_UART0_ENABLE 
		case 0:
			//����UARTʱ��
			MOF_UART0_CLKSET(MOF_UART_CLKSET_DEFAULT);

			//����UARTʱ��
			MOF_UART0_BAUDRATE(baudrate);

			//���ô���ͨ��
			MOF_UART0_CH0_ENABLE; 
		
			//ʹ�ܴ���
			MOF_UART0_ENABLE;
			cfgerr=0; 
		break;
		#endif
		#ifdef MOF_UART1_ENABLE 
		case 1:
			//����UARTʱ��
			MOF_UART1_CLKSET(MOF_UART_CLKSET_DEFAULT);

			//����UARTʱ��
			MOF_UART1_BAUDRATE(baudrate);

			//���ô���ͨ��
			#ifdef MOF_UART1_CH0_ENABLE
			if(uartChannel==0) MOF_UART1_CH0_ENABLE; 
			#endif
		
			//ʹ�ܴ���
			MOF_UART1_ENABLE;
			cfgerr=0; 
		break;
		#endif
		#ifdef MOF_UART2_ENABLE 
		case 2:
			//����UARTʱ��
			MOF_UART2_CLKSET(MOF_UART_CLKSET_DEFAULT);

			//����UARTʱ��
			MOF_UART2_BAUDRATE(baudrate);

			//���ô���ͨ��
			MOF_UART2_CH0_ENABLE; 
		
			//ʹ�ܴ���
			MOF_UART2_ENABLE;
			cfgerr=0; 
		break;
		#endif

		default:break;
	}
	return cfgerr;

}




/************************ (C) COPYRIGHT zhejiang zhida *****END OF FILE****/