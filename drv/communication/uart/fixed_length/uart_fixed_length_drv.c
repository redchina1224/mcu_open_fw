//******************************************************************************
//Copyright(C) 2020-2021 zhejiang zhida dianzikeji Co., Ltd
//�㽭�Ǵ���ӿƼ����޹�˾
//File name:      TM1628.c
//Author:         zzg
//Version:        Ver0.1
//Date:           2021-4-25
//Description:    TM1628����
//History:
//******************************************************************************
//ͷ�ļ�************************************************************************
#include "..\..\..\com_include_drv.h"
//******************************************************************************


#define UART_FIXED_LENGTH_TXBUF UART_TXBUF_CH(UART_FIXED_LENGTH_PORT_NUM)
#define UART_FIXED_LENGTH_RXBUF UART_RXBUF_CH(UART_FIXED_LENGTH_PORT_NUM)

mof_fix_length_uart_port_t fixed_length_port;

void uart_fixed_length_init(unsigned char rxlen)
{
	fixed_length_port.Busy=0;
	fixed_length_port.ReadPtr=0;
	fixed_length_port.WritePtr=0;
	fixed_length_port.ReadLength=rxlen;
	fixed_length_port.ReadTimeout=0;
	fixed_length_port.WriteLength=0;
	fixed_length_port.Reading=0;
	fixed_length_port.Writing=0;
	fixed_length_port.p_ReadBuffer=0;
	fixed_length_port.p_WriteBuffer=0;
}


void uart_fixed_length_send(unsigned char writelength)//,unsigned char readlength)
{
	fixed_length_port.Busy=1;
	fixed_length_port.Writing=0;
	//fixed_length_port.ReadLength=readlength;
	fixed_length_port.WriteLength=writelength;
	fixed_length_port.ReadPtr=0;
	fixed_length_port.WritePtr=1;
	UART_FIXED_LENGTH_TXBUF = fixed_length_port.p_WriteBuffer[0];

}	

/***********************************************************************************************
*������ 		: void UART1_TxIsr(unsigned char *TxReg)
*������������ 	: ���ڷ����жϷ������(����������������)
*�������� 		: unsigned char *RxReg������Ӳ�����ͻ����ַָ��
*��������ֵ 	: ��
***********************************************************************************************/
//void UART1_TxIsr(unsigned char *TxReg)
void uart_fixed_length_tx_in_isr(void)
{
		//���ͻ���������
		if(fixed_length_port.WritePtr<fixed_length_port.WriteLength)
		{
			UART_FIXED_LENGTH_TXBUF = fixed_length_port.p_WriteBuffer[fixed_length_port.WritePtr];		
			fixed_length_port.WritePtr++;
		}
		else
		{
			fixed_length_port.Busy=0;
		}

}

/***********************************************************************************************
*������ 		: void UART1_RxIsr(unsigned char *RxReg)
*������������ 	: ���ڽ����жϷ������(����������������)
*�������� 		: unsigned char *RxReg������Ӳ�����ջ����ַָ��
*��������ֵ 	: ��
***********************************************************************************************/
void uart_fixed_length_rx_in_isr(void)
{
	//���ǰһ�ν���δ����,ֹͣ�������⻺�������ƻ�
	if(fixed_length_port.Reading==200) return;
	
	//��������ѳ�ʱ,���¿�ʼ����
	if(fixed_length_port.ReadTimeout==0) fixed_length_port.ReadPtr=0;

	//ȡ��������
	fixed_length_port.p_ReadBuffer[fixed_length_port.ReadPtr]=UART_FIXED_LENGTH_RXBUF;
	
	//����ָ�����Ⱥ����
	if(fixed_length_port.ReadPtr<(fixed_length_port.ReadLength)) fixed_length_port.ReadPtr++;
	else
	{		
		fixed_length_port.Reading=200; //�������,ֹͣ����,�ȴ���ѭ����������
	}
	
	//���ý��ճ�ʱʱ��
	fixed_length_port.ReadTimeout=3;	
}