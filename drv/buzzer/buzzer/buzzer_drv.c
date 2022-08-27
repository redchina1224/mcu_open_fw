//******************************************************************************
//Copyright(C) 2020-2021 zhejiang zhida dianzikeji Co., Ltd
//浙江智达电子科技有限公司
//File name:      buzz.c
//Author:         zzg
//Version:        Ver0.1
//Date:           2021-4-25
//Description:    蜂鸣器处理
//History:
//******************************************************************************
//头文件************************************************************************
#include "..\..\com_include_drv.h"
//函数定义***********************************************************************

#ifdef BuzzerType

unsigned char beepEn=0;

unsigned char beeptime_cnt=0;
unsigned char beetontime;
unsigned char beetofftime;
unsigned char beetontime_repeat;
unsigned char beetofftime_repeat;


/***********************************************************************************************
*函数名 		: void zd_buzzer_beep(unsigned char beepCnt,unsigned char beepton_x50ms,unsigned char beeptoff_x50ms)
*函数功能描述 	: 蜂鸣器鸣响工作
*函数参数 		: beepCnt=蜂鸣次数，
				  beepton=鸣响的时长 (x50ms) ,
				  beeptoff=中间停止鸣响的时长 (x50ms)
*函数返回值 	: 无
***********************************************************************************************/
void zd_buzzer_beep(unsigned char beepCnt,unsigned char beepton_x50ms,unsigned char beeptoff_x50ms)
{
	beetontime_repeat=beepton_x50ms;
	beetofftime_repeat=beeptoff_x50ms;
	beetontime=beetontime_repeat;
	beeptime_cnt=beepCnt;
}


/***********************************************************************************************
*函数名 			: void zd_buzzerRun(void)
*函数功能描述 		: 蜂鸣器鸣响自动控制(鸣响时间，次数),需每50ms调用一次
*函数参数 			: 无
*函数返回值 		: 无
***********************************************************************************************/
void zd_buzzerRun(void)//每50ms调用一次
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
*函数名 			: void zd_buzzer_init(void)
*函数功能描述 		: 蜂鸣初始化
*函数参数 			: 无
*函数返回值 		: 无
***********************************************************************************************/
void zd_buzzer_init(void)
{
	
#if (BuzzerType==BuzzerType_Gpio)
	 Buzzer_IO_Output;
	 Buzzer_IO_Ctrl(Buzzer_IO_OFF);
#elif (BuzzerType==BuzzerType_TimerInv)
	//关中断
	ZD_GIE_DISABLE;  //中断总允许开关
   beepEn=0;
   T_BuzzerEn=&beepEn;
	 Buzzer_IO_Output;
	 Buzzer_IO_Ctrl(Buzzer_IO_OFF);
	 zd_timerInit(BuzzeTimer); //初始化定时器125us中断
	//开中断
	 ZD_GIE_ENABLE; //中断总允许开关
#elif (BuzzerType==BuzzerType_PWM)
	zd_pwmInit(Buzzer_PWM_Channel,4000);//配置蜂鸣器通道为4KHz
	zd_pwmDisable(Buzzer_PWM_Channel);//关闭输出
#endif
}




#endif //#ifdef BuzzerType

/************************ (C) COPYRIGHT zhejiang zhida *****END OF FILE****/