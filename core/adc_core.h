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
#ifndef __ZDCORE_ADC_H__
#define __ZDCORE_ADC_H__



extern bit adc_working;



/***************************************************
*������ 		: zd_adcInit
*������������ 	: ADCͨ����ɼ���ʼ��
*�������� 		: adcChannel:�ɼ�ͨ��,*callback:�ɼ�������ɺ�Ļص�����
*��������ֵ 	: ��
***************************************************/
void zd_adcInit(unsigned char adcChannel,void (*callback)(unsigned int));


/***************************************************
*������ 		: zd_getAdc_sync
*������������ 	: ADC�����첽��ѯ�ɼ�
*�������� 		: adcChannel:�ɼ�ͨ��,*adcValue:�ɼ��������ݵ�ָ��
*��������ֵ 	: uchar:�����ݸ���ʱ����1�����򷵻�0
***************************************************/
unsigned char zd_getAdc_sync(unsigned char adcChannel,unsigned int *adcValue);



/***************************************************
*������ 		: zd_getAdc_async
*������������ 	: ADC����ͬ���ȴ��ɼ�
*�������� 		: adcChannel:�ɼ�ͨ��,*adcValue:�ɼ��������ݵ�ָ��
*��������ֵ 	: uchar:�����ݸ���ʱ����1�����򷵻�0
***************************************************/
unsigned char zd_getAdc_async(unsigned char adcChannel,unsigned int *adcValue);
	

/***************************************************
*������ 		: zd_adcRun
*������������ 	: ADC��ͨ���첽��ѯ�����ɼ�����ͨ���ɼ����ڻص���
*�������� 		: ��
*��������ֵ 	: ��
***************************************************/
void zd_adcRun(void);



#endif 


/************************ (C) COPYRIGHT zhejiang zhida *****END OF FILE****/