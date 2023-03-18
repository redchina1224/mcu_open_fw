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
#ifdef ADC_COLLECTION_CH_MAX
#if(ADC_COLLECTION_CH_MAX>0)
void mof_adcInit(unsigned char adcChannel,void (*callback)(unsigned int));
#endif
#else
void mof_adcInit(void);
#endif


/***************************************************
*������ 		: zd_getAdc_async_reset
*������������ 	: ADC�����첽��ѯ�ɼ�����,���ڲɼ���������ֹ��,
				  �´����²ɼ������Ƿ��ش����ֵ,���ڶ�ͬһͨ����������ʱʹ��,
				  ��ͨ��ѭ������ʱ��ֱ���л���һ��ͨ��
*�������� 		: ��
*��������ֵ 	: ��
***************************************************/
void mof_getAdc_async_reset(void);

/***************************************************
*������ 		: zd_getAdc_async
*������������ 	: ADC�����첽��ѯ�ɼ�
*�������� 		: adcChannel:�ɼ�ͨ��,*adcValue:�ɼ��������ݵ�ָ��
*��������ֵ 	: uchar:�����ݸ���ʱ����1�����򷵻�0
***************************************************/
unsigned char mof_getAdc_async(unsigned char adcChannel,unsigned int *adcValue);



/***************************************************
*������ 		: zd_getAdc_sync
*������������ 	: ADC����ͬ���ȴ��ɼ�
*�������� 		: adcChannel:�ɼ�ͨ��,*adcValue:�ɼ��������ݵ�ָ��
*��������ֵ 	: uchar:�����ݸ���ʱ����1�����򷵻�0
***************************************************/
unsigned char zd_getAdc_sync(unsigned char adcChannel,unsigned int *adcValue);
	

/***************************************************
*������ 		: zd_adcRun
*������������ 	: ADC��ͨ���첽��ѯ�����ɼ�����ͨ���ɼ����ڻص���
*�������� 		: ��
*��������ֵ 	: ��
***************************************************/
#ifdef ADC_COLLECTION_CH_MAX
#if(ADC_COLLECTION_CH_MAX>0)
void zd_adcRun(void);
#endif
#endif



#endif 


/************************ (C) COPYRIGHT zhejiang zhida *****END OF FILE****/