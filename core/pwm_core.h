//******************************************************************************
//Copyright(C) 2020-2021 zhejiang zhida dianzikeji Co., Ltd
//�㽭�Ǵ���ӿƼ����޹�˾
//File name:      adc_core.h
//Author:         zzg
//Version:        Ver0.1
//Date:           2021-4-25
//Description:    ADC�ɼ�
//History:
//******************************************************************************
#ifndef __ZDCORE_PWM_H__
#define __ZDCORE_PWM_H__


/***************************************************
*������ 		: zd_adcInit
*������������ 	: ADCͨ����ɼ���ʼ��
*�������� 		: adcChannel:�ɼ�ͨ��,*callback:�ɼ�������ɺ�Ļص�����
*��������ֵ 	: ��
***************************************************/
#ifdef MOF_PWM_SELECT
void mof_pwmInit(unsigned char pwm,unsigned char ch,unsigned long fclk);
#else
void mof_pwmInit(unsigned char ch,unsigned long fclk);
#endif


#endif
/************************ (C) COPYRIGHT zhejiang zhida *****END OF FILE****/