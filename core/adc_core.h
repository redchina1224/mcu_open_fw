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
#ifndef __ZDCORE_ADC_H__
#define __ZDCORE_ADC_H__



extern bit adc_working;



/***************************************************
*函数名 		: zd_adcInit
*函数功能描述 	: ADC通道与采集初始化
*函数参数 		: adcChannel:采集通道,*callback:采集周期完成后的回调函数
*函数返回值 	: 无
***************************************************/
#ifdef ADC_COLLECTION_CH_MAX
#if(ADC_COLLECTION_CH_MAX>0)
void mof_adcInit(unsigned char adcChannel,void (*callback)(unsigned int));
#endif
#else
void mof_adcInit(void);
#endif


/***************************************************
*函数名 		: zd_getAdc_async_reset
*函数功能描述 	: ADC数据异步轮询采集重置,用于采集非正常中止后,
				  下次重新采集而不是返回错误的值,仅在对同一通道持续采样时使用,
				  多通道循环采样时可直接切换下一个通道
*函数参数 		: 无
*函数返回值 	: 无
***************************************************/
void mof_getAdc_async_reset(void);

/***************************************************
*函数名 		: zd_getAdc_async
*函数功能描述 	: ADC数据异步轮询采集
*函数参数 		: adcChannel:采集通道,*adcValue:采集后存放数据的指针
*函数返回值 	: uchar:当数据更新时返回1，否则返回0
***************************************************/
unsigned char mof_getAdc_async(unsigned char adcChannel,unsigned int *adcValue);



/***************************************************
*函数名 		: zd_getAdc_sync
*函数功能描述 	: ADC数据同步等待采集
*函数参数 		: adcChannel:采集通道,*adcValue:采集后存放数据的指针
*函数返回值 	: uchar:当数据更新时返回1，否则返回0
***************************************************/
unsigned char zd_getAdc_sync(unsigned char adcChannel,unsigned int *adcValue);
	

/***************************************************
*函数名 		: zd_adcRun
*函数功能描述 	: ADC多通道异步轮询批量采集（含通道采集周期回调）
*函数参数 		: 无
*函数返回值 	: 无
***************************************************/
#ifdef ADC_COLLECTION_CH_MAX
#if(ADC_COLLECTION_CH_MAX>0)
void zd_adcRun(void);
#endif
#endif



#endif 


/************************ (C) COPYRIGHT zhejiang zhida *****END OF FILE****/