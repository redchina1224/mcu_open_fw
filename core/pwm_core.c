//******************************************************************************
//Copyright(C) 2020-2021 zhejiang zhida dianzikeji Co., Ltd
//浙江智达电子科技有限公司
//File name:      zd_adc.c
//Author:         zzg
//Version:        Ver0.1
//Date:           2021-4-25
//Description:    ADC采集
//History:
//******************************************************************************
//头文件************************************************************************
#include "com_include_core.h"



/***************************************************
*函数名 		: zd_adcChannleInit
*函数功能描述 	: ADC通道初始化
*函数参数 		: adcChannel:采集通道,*callback:采集周期完成后的回调函数
*函数返回值 	: 无
***************************************************/
unsigned char mof_pwmChannelInit(unsigned char pwmChannel)
{
	unsigned char cfgerr=1;
	switch(pwmChannel)
	{
		#ifdef MOF_PWM_CH0_ENABLE 
		case 0:MOF_PWM_CH0_ENABLE; cfgerr=0; break;
		#endif
		#ifdef MOF_PWM_CH1_ENABLE 
		case 1:MOF_PWM_CH1_ENABLE; cfgerr=0; break;
		#endif
		#ifdef MOF_PWM_CH2_ENABLE 		
		case 2:MOF_PWM_CH2_ENABLE; cfgerr=0; break;
		#endif
		#ifdef MOF_PWM_CH3_ENABLE 		
		case 3:MOF_PWM_CH3_ENABLE; cfgerr=0; break;
		#endif
		#ifdef MOF_PWM_CH4_ENABLE 		
		case 4:MOF_PWM_CH4_ENABLE; cfgerr=0; break;
		#endif
		#ifdef MOF_PWM_CH5_ENABLE 		
		case 5:MOF_PWM_CH5_ENABLE; cfgerr=0; break;
		#endif
		#ifdef MOF_PWM_CH6_ENABLE 		
		case 6:MOF_PWM_CH6_ENABLE; cfgerr=0; break;
		#endif
		#ifdef MOF_PWM_CH7_ENABLE 
		case 7:MOF_PWM_CH7_ENABLE; cfgerr=0; break;
		#endif
		#ifdef MOF_PWM_CH8_ENABLE 
		case 8:MOF_PWM_CH8_ENABLE; cfgerr=0; break;
		#endif
		#ifdef MOF_PWM_CH9_ENABLE 
		case 9:MOF_PWM_CH9_ENABLE; cfgerr=0; break;
		#endif
		#ifdef MOF_PWM_CH10_ENABLE 
		case 10:MOF_PWM_CH10_ENABLE; cfgerr=0; break;
		#endif
		#ifdef MOF_PWM_CH11_ENABLE 
		case 11:MOF_PWM_CH11_ENABLE; cfgerr=0; break;
		#endif
		#ifdef MOF_PWM_CH12_ENABLE 
		case 12:MOF_PWM_CH12_ENABLE; cfgerr=0; break;
		#endif		
		#ifdef MOF_PWM_CH13_ENABLE 
		case 13:MOF_PWM_CH13_ENABLE; cfgerr=0; break;
		#endif
		#ifdef MOF_PWM_CH14_ENABLE 
		case 14:MOF_PWM_CH14_ENABLE; cfgerr=0; break;
		#endif
		#ifdef MOF_PWM_CH15_ENABLE 
		case 15:MOF_PWM_CH15_ENABLE; cfgerr=0; break;
		#endif 
		#ifdef MOF_PWM_CH16_ENABLE 
		case 16:MOF_PWM_CH16_ENABLE; cfgerr=0; break;
		#endif 
		#ifdef MOF_PWM_CH17_ENABLE 
		case 17:MOF_PWM_CH17_ENABLE; cfgerr=0; break;
		#endif 
		#ifdef MOF_PWM_CH18_ENABLE 
		case 18:MOF_PWM_CH18_ENABLE; cfgerr=0; break;
		#endif 
		#ifdef MOF_PWM_CH19_ENABLE 
		case 19:MOF_PWM_CH19_ENABLE; cfgerr=0; break;
		#endif 
		#ifdef MOF_PWM_CH20_ENABLE 
		case 20:MOF_PWM_CH20_ENABLE; cfgerr=0; break;
		#endif 
		#ifdef MOF_PWM_CH21_ENABLE 
		case 21:MOF_PWM_CH21_ENABLE; cfgerr=0; break;
		#endif 
		#ifdef MOF_PWM_CH22_ENABLE 
		case 22:MOF_PWM_CH22_ENABLE; cfgerr=0; break;
		#endif 
		#ifdef MOF_PWM_CH23_ENABLE 
		case 23:MOF_PWM_CH23_ENABLE; cfgerr=0; break;
		#endif 
		#ifdef MOF_PWM_CH24_ENABLE 
		case 24:MOF_PWM_CH24_ENABLE; cfgerr=0; break;
		#endif 
		#ifdef MOF_PWM_CH25_ENABLE 
		case 25:MOF_PWM_CH25_ENABLE; cfgerr=0; break;
		#endif 

		default:break;
	}
	return cfgerr;
	
}

/***************************************************
*函数名 		: zd_adcInit
*函数功能描述 	: ADC通道与采集初始化
*函数参数 		: adcChannel:采集通道,*callback:采集周期完成后的回调函数
*函数返回值 	: 无
***************************************************/
#ifdef MOF_PWM_SELECT
void mof_pwmInit(unsigned char pwm,unsigned char ch,unsigned long fclk)
#else
void mof_pwmInit(unsigned char ch,unsigned long fclk)
#endif
{
	#ifdef MOF_PWM_SELECT

		//配置PWM时钟
		MOF_PWM_CLKSET(pwm,MOF_PWM_CLKSET_DEFAULT);
	
		MOF_PWM_SELECT(pwm);
	
		if(0==mof_pwmChannelInit(ch))	
		{
			
			//设置时钟周期
			MOF_PWM_CYCLE(pwm,fclk);
			//初始化占空比
			MOF_PWM_DUTY(pwm,0);
			//配置PWM开启
			MOF_PWM_INIT(pwm);
		}
	

	#else

		//配置ADC时钟
		MOF_PWM_CLKSET(MOF_PWM_CLKSET_DEFAULT);
		
		if(0==mof_pwmChannelInit(ch))	
		{
			//设置时钟周期
			MOF_PWM_CYCLE(fclk);
			//初始化占空比
			MOF_PWM_DUTY(0);
			//配置PWM开启
			MOF_PWM_INIT;
		}

	#endif

}



/************************ (C) COPYRIGHT zhejiang zhida *****END OF FILE****/