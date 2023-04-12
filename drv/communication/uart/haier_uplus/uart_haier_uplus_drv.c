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
*������ 		: void UART1_TxIsr(unsigned char *TxReg)
*������������ 	: ���ڷ����жϷ������(����������������)
*�������� 		: unsigned char *RxReg������Ӳ�����ͻ����ַָ��
*��������ֵ 	: ��
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
				//������η��͵��ֽ���FF,�´�׷�ӷ���55
				if(haier_uplus_port.S_WriteBuffer[haier_uplus_port.S_WritePtr]==0xff) haier_uplus_port.S_WriteAppendbytes=0x55;
				
				//���ͻ���������
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
*������ 		: void UART1_RxIsr(unsigned char *RxReg)
*������������ 	: ���ڽ����жϷ������(����������������)
*�������� 		: unsigned char *RxReg������Ӳ�����ջ����ַָ��
*��������ֵ 	: ��
***********************************************************************************************/
#define ReadCharNow haier_uplus_port.S_ReadCharWindows[1]
#define ReadCharAgo haier_uplus_port.S_ReadCharWindows[0]

void uart_haier_uplus_rx_in_isr(void)
{
	haier_uplus_port.S_ReadTimeout=3;

	//�����ֽڵĽ��չ�������,���ڽ������ݺ��ж� ��FF,FF��   ��FF,55��
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

		//��ȡ֡����
		if(haier_uplus_port.S_ReadPtr==0)
		{
			//�����CRCУ��,����Ϊ֡����2
			//haier_uplus_port.S_ReadLength=haier_uplus_port.S_ReadBuffer[0]+2;//�����ݳ���Ϊ����+У��͵ĳ���,������CRCУ������,ʵ�ʽ����������ڴ˻����ϼ�2

			//�������CRCУ��,����Ϊ֡��
			haier_uplus_port.S_ReadLength=haier_uplus_port.S_ReadBuffer[0];//�����ݳ���Ϊ����+У��͵ĳ���,������CRCУ������,ʵ�ʽ����������ڴ˻����ϼ�2
			
			
			haier_uplus_port.S_ReadChecksumAdj=0;//��ʼ��У�������ֵ
		}
		else if(ReadCharAgo==0xff) //�ж�ǰһ��������FF
		{
			if(ReadCharNow==0x55)
			{
				if(haier_uplus_port.S_ReadPtr<=(haier_uplus_port.S_ReadBuffer[0])) haier_uplus_port.S_ReadChecksumAdj-=0x55;//��ΪУ��Ͱ��������е�55,��Ҫ��������ֵ
				return;//����ǲ����55,���½�����ȥ�����55��������Ľ���ָ���ۼ�
			}
			else if(ReadCharNow==0xFF) //�����FF,��ʾ�����յ�����FF,���¿�ʼ����
			{
				haier_uplus_port.S_Reading=1;
				haier_uplus_port.S_ReadPtr=0;
				ReadCharAgo=0;
				ReadCharNow=0;
				return;//��������Ľ���ָ���ۼ�		
			}				
		}
	
		if(haier_uplus_port.S_ReadPtr<(haier_uplus_port.S_ReadLength)) haier_uplus_port.S_ReadPtr++;
		else
		{		
			haier_uplus_port.S_ReadBuffer[haier_uplus_port.S_ReadBuffer[0]]+=haier_uplus_port.S_ReadChecksumAdj;
			haier_uplus_port.S_Reading=200; //�������,ֹͣ����,�ȴ���ѭ����������
		}

	}
	
}