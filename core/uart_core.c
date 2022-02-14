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
#include "core.h"


//struct struct_uartdata uart1data;

bit S1_Busy=0;
unsigned char S1ReadStartChar=0;
unsigned char S1ReadPtr=0;
unsigned char S1WritePtr=0;
unsigned char S1ReadLength=0;
unsigned char S1ReadTimeout=0;
unsigned char S1WriteLength=0;
unsigned char S1Reading=0;
unsigned char *S1ReadBuffer;
unsigned char *S1WriteBuffer;



/***********************************************************************************************
*������ 		: void Uart1Init(void)
*������������ 	: ����1��ʼ��
*�������� 		: ��
*��������ֵ 	: ��
***********************************************************************************************/
void Uart1Init(void)		//9600bps@33.1776MHz
{


}

/***********************************************************************************************
*������ 		: Uart1Send(unsigned char writelength)
*������������ 	: ���ڷ�������
*�������� 		: unsigned char writelength�����������������ݵĳ���
*��������ֵ 	: ��
***********************************************************************************************/
void Uart1Send(unsigned char writelength)//,unsigned char readlength)
{
	S1_Busy=1;
	//S1Reading=2;
	//S1ReadLength=readlength;
	S1WriteLength=writelength;
	//S1ReadPtr=0;
	S1WritePtr=1;
	ZD_UART1_TXBUF = S1WriteBuffer[0];

}	


/***********************************************************************************************
*������ 		: void UART1_TxIsr(unsigned char *TxReg)
*������������ 	: ���ڷ����жϷ������(����������������)
*�������� 		: unsigned char *RxReg������Ӳ�����ͻ����ַָ��
*��������ֵ 	: ��
***********************************************************************************************/
void UART1_TxIsr(unsigned char *TxReg)
{
	if(S1WritePtr<S1WriteLength)
	{
		(*TxReg) = S1WriteBuffer[S1WritePtr];
		S1WritePtr++;
	}
	else
	{
		S1_Busy=0;
	}
}

/***********************************************************************************************
*������ 		: void UART1_RxIsr(unsigned char *RxReg)
*������������ 	: ���ڽ����жϷ������(����������������)
*�������� 		: unsigned char *RxReg������Ӳ�����ջ����ַָ��
*��������ֵ 	: ��
***********************************************************************************************/
void UART1_RxIsr(unsigned char *RxReg)
{
	S1ReadTimeout=3;
	S1ReadBuffer[S1ReadPtr] = (*RxReg);
	if(S1ReadPtr<S1ReadLength) S1ReadPtr++;
	//if(S1ReadLength==S1ReadPtr&&2==S1Reading) S1Reading=1;
}




/************************ (C) COPYRIGHT zhejiang zhida *****END OF FILE****/