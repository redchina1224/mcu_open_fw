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
#ifdef CommunicationTypeUartModel
#if ((CommunicationTypeUartModel&CommunicationType_Uart_MiHome)==CommunicationType_Uart_MiHome)

#define UART_MIHOME_TXBUF UART_TXBUF_CH(UART_MIHOME_PORT_NUM)
#define UART_MIHOME_RXBUF UART_RXBUF_CH(UART_MIHOME_PORT_NUM)

mof_granwin_mi_uart_port_t xdata mihome_port;

void uart_mihome_init(unsigned char *txbuf,unsigned char *rxbuf)
{
	mihome_port.Busy=0;
	mihome_port.ReadCharWindows[0]=0;
	mihome_port.ReadCharWindows[1]=0;
	mihome_port.ReadPtr=0;
	mihome_port.WritePtr=0;
	mihome_port.ReadLength=0;
	mihome_port.ReadTimeout=0;
	mihome_port.WriteLength=0;
	mihome_port.WriteAppendbytes=0;
	mihome_port.Reading=0;
	mihome_port.Writing=0;
	mihome_port.p_ReadBuffer=rxbuf;
	mihome_port.p_WriteBuffer=txbuf;
	mihome_port.ReadChecksumAdj=0;
	mihome_port.WriteChecksumAdj=0;
}


void uart_mihome_send(unsigned char writelength)//,unsigned char readlength)
{
	mihome_port.Busy=1;
	mihome_port.Writing=0;
	//mihome_port.ReadLength=readlength;
	mihome_port.WriteLength=writelength;
	//mihome_port.ReadPtr=0;
	mihome_port.WritePtr=0;//S_WritePtr=1;
	UART_MIHOME_TXBUF = 0x55;//S_WriteBuffer[0];

}	

/***********************************************************************************************
*������ 		: void UART1_TxIsr(unsigned char *TxReg)
*������������ 	: ���ڷ����жϷ������(����������������)
*�������� 		: unsigned char *RxReg������Ӳ�����ͻ����ַָ��
*��������ֵ 	: ��
***********************************************************************************************/
//void UART1_TxIsr(unsigned char *TxReg)
void uart_mihome_tx_in_isr(void)
{
		if(mihome_port.Writing==0)
		{
			UART_MIHOME_TXBUF=0xAA;

				mihome_port.WritePtr=0;
				mihome_port.Writing=1;
		}
		else if(mihome_port.Writing==1)
		{
				//���ͻ���������
				if(mihome_port.WritePtr<mihome_port.WriteLength)
				{
					UART_MIHOME_TXBUF = mihome_port.p_WriteBuffer[mihome_port.WritePtr];		
					mihome_port.WritePtr++;
				}
				else
				{
					mihome_port.Busy=0;
				}
		}
}

/***********************************************************************************************
*������ 		: void UART1_RxIsr(unsigned char *RxReg)
*������������ 	: ���ڽ����жϷ������(����������������)
*�������� 		: unsigned char *RxReg������Ӳ�����ջ����ַָ��
*��������ֵ 	: ��
***********************************************************************************************/
#define ReadCharNow mihome_port.ReadCharWindows[1]
#define ReadCharAgo mihome_port.ReadCharWindows[0]

void uart_mihome_rx_in_isr(void)
{

	//�����ֽڵĽ��չ�������,���ڽ������ݺ��ж� ��AA,55��
	ReadCharAgo=ReadCharNow;
	ReadCharNow=UART_MIHOME_RXBUF;

	if(mihome_port.Reading==200) return;

	mihome_port.ReadTimeout=3;
	
	if(mihome_port.Reading==0)
	{
		if(ReadCharNow==0x55) 
		{
			if(ReadCharAgo==0xAA)
			{
				mihome_port.Reading=1;
				mihome_port.ReadPtr=0;
				ReadCharAgo=0;
				ReadCharNow=0;
				//mihome_port.ReadChecksumAdj=(0x55+0xaa);//��ʼ��У�������ֵ
			}
		}
	}
	else if(mihome_port.Reading==1)
	{

		mihome_port.p_ReadBuffer[mihome_port.ReadPtr] = ReadCharNow;

		//��ȡЭ��汾֡����
		if(mihome_port.ReadPtr<2) mihome_port.ReadPtr++;
		else if(mihome_port.ReadPtr==2)
		{
			mihome_port.ReadLength=((ReadCharAgo<<8)|(ReadCharNow))+5; //(1������+2���ݳ�+N����+1У��+1��β)
			mihome_port.Reading=2;
			mihome_port.ReadPtr=3;
		}
	}
	else if(mihome_port.Reading==2)
	{

		mihome_port.p_ReadBuffer[mihome_port.ReadPtr] = ReadCharNow;
		mihome_port.ReadPtr++;
		
		if(mihome_port.ReadPtr>=(mihome_port.ReadLength))
		{		
			mihome_port.Reading=200; //�������,ֹͣ����,�ȴ���ѭ����������
		}

	}
	
}

#endif
#endif