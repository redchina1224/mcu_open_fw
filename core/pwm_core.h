//******************************************************************************
//Copyright(C) 2020-2021 zhejiang zhida dianzikeji Co., Ltd
//浙江智达电子科技有限公司
//File name:      adc_core.h
//Author:         zzg
//Version:        Ver0.1
//Date:           2021-4-25
//Description:    ADC采集
//History:
//******************************************************************************
#ifndef __ZDCORE_PWM_H__
#define __ZDCORE_PWM_H__


/***************************************************
*函数名 		: zd_adcInit
*函数功能描述 	: ADC通道与采集初始化
*函数参数 		: adcChannel:采集通道,*callback:采集周期完成后的回调函数
*函数返回值 	: 无
***************************************************/
#ifdef MOF_PWM_SELECT
void mof_pwmInit(unsigned char pwm,unsigned char ch,unsigned long fclk);
#else
void mof_pwmInit(unsigned char ch,unsigned long fclk);
#endif


#endif
/************************ (C) COPYRIGHT zhejiang zhida *****END OF FILE****/