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


#define UART_UPLUS_TXBUF UART_TXBUF_CH(UART_UPLUS_PORT_NUM)
#define UART_UPLUS_RXBUF UART_RXBUF_CH(UART_UPLUS_PORT_NUM)

mof_haier_uplus_uart_port_t xdata haier_uplus_port;

void uart_haier_uplus_init(unsigned char *txbuf,unsigned char *rxbuf)
{
	haier_uplus_port.Busy=0;
	haier_uplus_port.ReadCharWindows[0]=0;
	haier_uplus_port.ReadCharWindows[1]=0;
	haier_uplus_port.ReadPtr=0;
	haier_uplus_port.WritePtr=0;
	haier_uplus_port.ReadLength=0;
	haier_uplus_port.ReadTimeout=0;
	haier_uplus_port.WriteLength=0;
	haier_uplus_port.WriteAppendbytes=0;
	haier_uplus_port.Reading=0;
	haier_uplus_port.Writing=0;
	haier_uplus_port.p_ReadBuffer=rxbuf;
	haier_uplus_port.p_WriteBuffer=txbuf;
	haier_uplus_port.ReadChecksumAdj=0;
	haier_uplus_port.WriteChecksumAdj=0;
}


void uart_haier_uplus_send(unsigned char writelength)//,unsigned char readlength)
{
	haier_uplus_port.Busy=1;
	haier_uplus_port.Writing=0;
	//haier_uplus_port.ReadLength=readlength;
	haier_uplus_port.WriteLength=writelength;
	//haier_uplus_port.ReadPtr=0;
	haier_uplus_port.WritePtr=0;//S_WritePtr=1;
	UART_UPLUS_TXBUF = 0xFF;//S_WriteBuffer[0];

}	

/***********************************************************************************************
*������ 		: void UART1_TxIsr(unsigned char *TxReg)
*������������ 	: ���ڷ����жϷ������(����������������)
*�������� 		: unsigned char *RxReg������Ӳ�����ͻ����ַָ��
*��������ֵ 	: ��
***********************************************************************************************/
//void UART1_TxIsr(unsigned char *TxReg)
void uart_haier_uplus_tx_in_isr(void)
{
		if(haier_uplus_port.Writing==0)
		{
			UART_UPLUS_TXBUF=0xFF;

				haier_uplus_port.WritePtr=0;
				haier_uplus_port.Writing=1;
				haier_uplus_port.WriteAppendbytes=0;
		}
		else if(haier_uplus_port.Writing==1)
		{
			if(haier_uplus_port.WriteAppendbytes!=0)
			{
				UART_UPLUS_TXBUF=haier_uplus_port.WriteAppendbytes;
				haier_uplus_port.WriteAppendbytes=0;
			}
			else
			{
				//������η��͵��ֽ���FF,�´�׷�ӷ���55
				if(haier_uplus_port.p_WriteBuffer[haier_uplus_port.WritePtr]==0xff) haier_uplus_port.WriteAppendbytes=0x55;
				
				//���ͻ���������
				if(haier_uplus_port.WritePtr<haier_uplus_port.WriteLength)
				{
					//(*TxReg) = haier_uplus_port.p_WriteBuffer[haier_uplus_port.WritePtr];
					UART_UPLUS_TXBUF = haier_uplus_port.p_WriteBuffer[haier_uplus_port.WritePtr];		
					haier_uplus_port.WritePtr++;
				}
				else
				{
					haier_uplus_port.Busy=0;
				}

			}
		}

}

/***********************************************************************************************
*������ 		: void UART1_RxIsr(unsigned char *RxReg)
*������������ 	: ���ڽ����жϷ������(����������������)
*�������� 		: unsigned char *RxReg������Ӳ�����ջ����ַָ��
*��������ֵ 	: ��
***********************************************************************************************/
#define ReadCharNow haier_uplus_port.ReadCharWindows[1]
#define ReadCharAgo haier_uplus_port.ReadCharWindows[0]

void uart_haier_uplus_rx_in_isr(void)
{
	haier_uplus_port.ReadTimeout=3;

	//�����ֽڵĽ��չ�������,���ڽ������ݺ��ж� ��FF,FF��   ��FF,55��
	ReadCharAgo=ReadCharNow;
	ReadCharNow=UART_UPLUS_RXBUF;
	
	if(haier_uplus_port.Reading==0)
	{
		if(ReadCharNow==0xFF) 
		{
			if(ReadCharAgo==0xFF)
			{
				haier_uplus_port.Reading=1;
				haier_uplus_port.ReadPtr=0;
				ReadCharAgo=0;
				ReadCharNow=0;
			}
		}
	}
	else if(haier_uplus_port.Reading==1)
	{
		//haier_uplus_port.p_ReadBuffer[haier_uplus_port.ReadPtr] = (*RxReg);
		haier_uplus_port.p_ReadBuffer[haier_uplus_port.ReadPtr] = ReadCharNow;

		//��ȡ֡����
		if(haier_uplus_port.ReadPtr==0)
		{
			//�����CRCУ��,����Ϊ֡����2
			//haier_uplus_port.ReadLength=haier_uplus_port.p_ReadBuffer[0]+2;//�����ݳ���Ϊ����+У��͵ĳ���,������CRCУ������,ʵ�ʽ����������ڴ˻����ϼ�2

			//�������CRCУ��,����Ϊ֡��
			haier_uplus_port.ReadLength=haier_uplus_port.p_ReadBuffer[0];//�����ݳ���Ϊ����+У��͵ĳ���,������CRCУ������,ʵ�ʽ����������ڴ˻����ϼ�2
			
			
			haier_uplus_port.ReadChecksumAdj=0;//��ʼ��У�������ֵ
		}
		else if(ReadCharAgo==0xff) //�ж�ǰһ��������FF
		{
			if(ReadCharNow==0x55)
			{
				if(haier_uplus_port.ReadPtr<=(haier_uplus_port.p_ReadBuffer[0])) haier_uplus_port.ReadChecksumAdj-=0x55;//��ΪУ��Ͱ��������е�55,��Ҫ��������ֵ
				return;//����ǲ����55,���½�����ȥ�����55��������Ľ���ָ���ۼ�
			}
			else if(ReadCharNow==0xFF) //�����FF,��ʾ�����յ�����FF,���¿�ʼ����
			{
				haier_uplus_port.Reading=1;
				haier_uplus_port.ReadPtr=0;
				ReadCharAgo=0;
				ReadCharNow=0;
				return;//��������Ľ���ָ���ۼ�		
			}				
		}
	
		if(haier_uplus_port.ReadPtr<(haier_uplus_port.ReadLength)) haier_uplus_port.ReadPtr++;
		else
		{		
			haier_uplus_port.p_ReadBuffer[haier_uplus_port.p_ReadBuffer[0]]+=haier_uplus_port.ReadChecksumAdj;
			haier_uplus_port.Reading=200; //�������,ֹͣ����,�ȴ���ѭ����������
		}

	}
	
}