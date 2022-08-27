//******************************************************************************
//Copyright(C) 2020-2021 zhejiang zhida dianzikeji Co., Ltd
//�㽭�Ǵ���ӿƼ����޹�˾
//File name:      buzz.c
//Author:         zzg
//Version:        Ver0.1
//Date:           2021-4-25
//Description:    ����������
//History:
//******************************************************************************
//ͷ�ļ�************************************************************************
#include "..\..\com_include_drv.h"
//��������***********************************************************************

#ifdef BuzzerType

unsigned char beepEn=0;

unsigned char beeptime_cnt=0;
unsigned char beetontime;
unsigned char beetofftime;
unsigned char beetontime_repeat;
unsigned char beetofftime_repeat;


/***********************************************************************************************
*������ 		: void zd_buzzer_beep(unsigned char beepCnt,unsigned char beepton_x50ms,unsigned char beeptoff_x50ms)
*������������ 	: ���������칤��
*�������� 		: beepCnt=����������
				  beepton=�����ʱ�� (x50ms) ,
				  beeptoff=�м�ֹͣ�����ʱ�� (x50ms)
*��������ֵ 	: ��
***********************************************************************************************/
void zd_buzzer_beep(unsigned char beepCnt,unsigned char beepton_x50ms,unsigned char beeptoff_x50ms)
{
	beetontime_repeat=beepton_x50ms;
	beetofftime_repeat=beeptoff_x50ms;
	beetontime=beetontime_repeat;
	beeptime_cnt=beepCnt;
}


/***********************************************************************************************
*������ 			: void zd_buzzerRun(void)
*������������ 		: �����������Զ�����(����ʱ�䣬����),��ÿ50ms����һ��
*�������� 			: ��
*��������ֵ 		: ��
***********************************************************************************************/
void zd_buzzerRun(void)//ÿ50ms����һ��
{
	if(beeptime_cnt>0)
	{
		if(beetontime>0)
		{
			beetontime--;
			beepEn=1;
			Buzzer_IO_Output;
			#if (BuzzerType==BuzzerType_Gpio)
				Buzzer_IO_Ctrl(Buzzer_IO_ON);
			#elif (BuzzerType==BuzzerType_PWM)
				zd_pwmEnable(Buzzer_PWM_Channel);
			#endif
			if(0==beetontime) 
			{
				beetofftime=beetofftime_repeat; 
				beeptime_cnt--;
				
				#if (BuzzerType==BuzzerType_Gpio)
					Buzzer_IO_Ctrl(Buzzer_IO_OFF);
				#elif (BuzzerType==BuzzerType_PWM)
					zd_pwmDisable(Buzzer_PWM_Channel);
				#endif
				
			}
			
		}
		else if(beetofftime>0)
		{
			beetofftime--;
			beepEn=0;
			Buzzer_IO_Input;
			if(0==beetofftime) beetontime=beetontime_repeat;
		}
	}
	else
	{
		beepEn=0;

		#if (BuzzerType==BuzzerType_Gpio)
			Buzzer_IO_Ctrl(Buzzer_IO_OFF);
		#else
			//Buzzer_IO_Input;
		#endif
	}
}



/***********************************************************************************************
*������ 			: void zd_buzzer_init(void)
*������������ 		: ������ʼ��
*�������� 			: ��
*��������ֵ 		: ��
***********************************************************************************************/
void zd_buzzer_init(void)
{
	
#if (BuzzerType==BuzzerType_Gpio)
	 Buzzer_IO_Output;
	 Buzzer_IO_Ctrl(Buzzer_IO_OFF);
#elif (BuzzerType==BuzzerType_TimerInv)
	//���ж�
	ZD_GIE_DISABLE;  //�ж���������
   beepEn=0;
   T_BuzzerEn=&beepEn;
	 Buzzer_IO_Output;
	 Buzzer_IO_Ctrl(Buzzer_IO_OFF);
	 zd_timerInit(BuzzeTimer); //��ʼ����ʱ��125us�ж�
	//���ж�
	 ZD_GIE_ENABLE; //�ж���������
#elif (BuzzerType==BuzzerType_PWM)
	zd_pwmInit(Buzzer_PWM_Channel,4000);//���÷�����ͨ��Ϊ4KHz
	zd_pwmDisable(Buzzer_PWM_Channel);//�ر����
#endif
}




#endif //#ifdef BuzzerType

/************************ (C) COPYRIGHT zhejiang zhida *****END OF FILE****/