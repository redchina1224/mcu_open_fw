//******************************************************************************
//Copyright(C) 2020-2021 zhejiang zhida dianzikeji Co., Ltd
//�㽭�Ǵ���ӿƼ����޹�˾
//File name:      user_time.c
//Author:         zzg
//Version:        Ver0.1
//Date:           2021-4-25
//Description:    TIMEʱ�䴦��
//History:
//******************************************************************************
//ͷ�ļ�************************************************************************
#include "core.h"


/***********************************************************************************************
*������ 		: void zd_timerInit(unsigned char timerChannel)
*������������ 	: ��ʼ����ʱ��
*�������� 		: unsigned char timerChannel:��ʱ����,
				  unsigned long _Us����ʱ��ʱ��
*��������ֵ 	: ��
***********************************************************************************************/
void zd_timerInit(unsigned char timerChannel,unsigned long _Us)
{
	unsigned char cfgerr=1;
	
	//������Ӧtimer��ʱ��
	switch(timerChannel)
	{
		case 0:
		#ifdef Ft0Clk
		 T0_Reload=(	256 - ((unsigned char)	((_Us*1.0)*((Ft0Clk*1.0)/1000000))));
		
		#ifdef ZD_TIMER0_LOAD_RELOAD
			ZD_TIMER0_LOAD_RELOAD = T0_Reload;		//���¸���ֵ
		#endif		
		
		 ZD_TIMER0_LOAD = T0_Reload;
		
		 ZD_TIMER0_INIT;

		 ZD_T0IE(ZD_T0IE_ENABLE);
		
		 cfgerr=0; 
		#endif
		 break;
		case 1:
		#ifdef Ft1Clk
		 T1H_Reload = (65536 - ((unsigned int)((_Us*1.0)*((Ft1Clk*1.0)/1000000))))>>8;
		 T1L_Reload = (65536 - ((unsigned int)((_Us*1.0)*((Ft1Clk*1.0)/1000000))));
		 ZD_TIMER1_INIT;
		 cfgerr=0; 
		#endif
		 break;
		case 2:
		#ifdef Ft2Clk
		 T2H_Reload = (65536 - ((unsigned int)((_Us*1.0)*((Ft1Clk*1.0)/1000000))))>>8;
		 T2L_Reload = (65536 - ((unsigned int)((_Us*1.0)*((Ft1Clk*1.0)/1000000))));
		 ZD_TIMER2_INIT;
		 cfgerr=0; 
		#endif
		 break;

		default:break;
	}
	
	//�����ж�
	if(cfgerr==0)
	{

	
	}


}

/************************ (C) COPYRIGHT zhejiang zhida *****END OF FILE****/