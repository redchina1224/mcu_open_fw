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

/***********************************************************************************************
*������ 		: Uart1Send(unsigned char writelength)
*������������ 	: ���ڷ�������
*�������� 		: unsigned char writelength�����������������ݵĳ���
*��������ֵ 	: ��
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
*������ 		: void UART1_TxIsr(unsigned char *TxReg)
*������������ 	: ���ڷ����жϷ������(����������������)
*�������� 		: unsigned char *RxReg������Ӳ�����ͻ����ַָ��
*��������ֵ 	: ��
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
				//������η��͵��ֽ���FF,�´�׷�ӷ���55
				if(S1WriteBuffer[S1WritePtr]==0xff) S1WriteAppendbytes=0x55;
				
				//���ͻ���������
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
*������ 		: void UART1_RxIsr(unsigned char *RxReg)
*������������ 	: ���ڽ����жϷ������(����������������)
*�������� 		: unsigned char *RxReg������Ӳ�����ջ����ַָ��
*��������ֵ 	: ��
***********************************************************************************************/
#define S1ReadCharNow S1ReadCharWindows[1]
#define S1ReadCharAgo S1ReadCharWindows[0]

//void UART1_RxIsr(unsigned char *RxReg)
void UART1_RxIsr(void)
{
	S1ReadTimeout=3;

	//�����ֽڵĽ��չ�������,���ڽ������ݺ��ж� ��FF,FF��   ��FF,55��
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

		//��ȡ֡����
		if(S1ReadPtr==0)
		{
			//�����CRCУ��,����Ϊ֡����2
			//S1ReadLength=S1ReadBuffer[0]+2;//�����ݳ���Ϊ����+У��͵ĳ���,������CRCУ������,ʵ�ʽ����������ڴ˻����ϼ�2

			//�������CRCУ��,����Ϊ֡��
			S1ReadLength=S1ReadBuffer[0];//�����ݳ���Ϊ����+У��͵ĳ���,������CRCУ������,ʵ�ʽ����������ڴ˻����ϼ�2
			
			
			S1ReadChecksumAdj=0;//��ʼ��У�������ֵ
		}
		else if(S1ReadCharAgo==0xff) //�ж�ǰһ��������FF
		{
			if(S1ReadCharNow==0x55)
			{
				if(S1ReadPtr<=(S1ReadBuffer[0])) S1ReadChecksumAdj-=0x55;//��ΪУ��Ͱ��������е�55,��Ҫ��������ֵ
				return;//����ǲ����55,���½�����ȥ�����55��������Ľ���ָ���ۼ�
			}
			else if(S1ReadCharNow==0xFF) //�����FF,��ʾ�����յ�����FF,���¿�ʼ����
			{
				S1Reading=1;
				S1ReadPtr=0;
				S1ReadCharAgo=0;
				S1ReadCharNow=0;
				return;//��������Ľ���ָ���ۼ�		
			}				
		}
	
		if(S1ReadPtr<(S1ReadLength)) S1ReadPtr++;
		else
		{		
			S1ReadBuffer[S1ReadBuffer[0]]+=S1ReadChecksumAdj;
			S1Reading=200; //�������,ֹͣ����,�ȴ���ѭ����������
		}

	}
	
}




/************************ (C) COPYRIGHT zhejiang zhida *****END OF FILE****/