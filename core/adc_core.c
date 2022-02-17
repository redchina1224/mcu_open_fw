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


bit adc_working=0;
unsigned char adcChannel_sync=255; 

#ifdef ADC_COLLECTION_CH_MAX
#if(ADC_COLLECTION_CH_MAX>0)
unsigned char adc_ch[ADC_COLLECTION_CH_MAX];
unsigned char adc_ch_select_max=0;
unsigned char adc_ch_select=0;
unsigned char adc_ch_collection_times=0;
unsigned int adc_value_list[ADC_COLLECTION_CH_MAX][ADC_COLLECTION_LIST_TIMES];
unsigned long adc_value_sum;
//unsigned int adc_value_agv;
//unsigned int adc_value_min;
//unsigned int adc_value_max;

void (*adc_ch_callback[ADC_COLLECTION_CH_MAX])(unsigned int);
#endif
#endif


/*------------------------------------------------- 
 *	函数名称：DelayUs
 *	功能：   短延时函数 --16M-2T--大概快1%左右.
 *	输入参数：Time 延时时间长度 延时时长Time Us
 *	返回参数：无 
 -------------------------------------------------*/
#define Adc_DelayUs core_DelayUs 
/*
void Adc_DelayUs(unsigned char Time)
{
	unsigned char a;

	for(a=0;a<Time;a++)
	{
		ZD_NOP;
	}
}  
*/

//void Adc_Enable(unsigned char ch)
//{	
////	ZD_ADC_INIT(ch);
//}


/***************************************************
*函数名 		: zd_adcChannleInit
*函数功能描述 	: ADC通道初始化
*函数参数 		: adcChannel:采集通道,*callback:采集周期完成后的回调函数
*函数返回值 	: 无
***************************************************/
unsigned char zd_adcChannelInit(unsigned char adcChannel)
{
	unsigned char cfgerr=1;
	switch(adcChannel)
	{
		#ifdef ZD_ADC_CH0_ENABLE 
		case 0:ZD_ADC_CH0_ENABLE; cfgerr=0; break;
		#endif
		#ifdef ZD_ADC_CH1_ENABLE 
		case 1:ZD_ADC_CH1_ENABLE; cfgerr=0; break;
		#endif
		#ifdef ZD_ADC_CH2_ENABLE 		
		case 2:ZD_ADC_CH2_ENABLE; cfgerr=0; break;
		#endif
		#ifdef ZD_ADC_CH3_ENABLE 		
		case 3:ZD_ADC_CH3_ENABLE; cfgerr=0; break;
		#endif
		#ifdef ZD_ADC_CH4_ENABLE 		
		case 4:ZD_ADC_CH4_ENABLE; cfgerr=0; break;
		#endif
		#ifdef ZD_ADC_CH5_ENABLE 		
		case 5:ZD_ADC_CH5_ENABLE; cfgerr=0; break;
		#endif
		#ifdef ZD_ADC_CH6_ENABLE 		
		case 6:ZD_ADC_CH6_ENABLE; cfgerr=0; break;
		#endif
		#ifdef ZD_ADC_CH7_ENABLE 
		case 7:ZD_ADC_CH7_ENABLE; cfgerr=0; break;
		#endif
		#ifdef ZD_ADC_CH8_ENABLE 
		case 8:ZD_ADC_CH8_ENABLE; cfgerr=0; break;
		#endif
		#ifdef ZD_ADC_CH9_ENABLE 
		case 9:ZD_ADC_CH9_ENABLE; cfgerr=0; break;
		#endif
		#ifdef ZD_ADC_CH10_ENABLE 
		case 10:ZD_ADC_CH10_ENABLE; cfgerr=0; break;
		#endif
		#ifdef ZD_ADC_CH11_ENABLE 
		case 11:ZD_ADC_CH11_ENABLE; cfgerr=0; break;
		#endif
		#ifdef ZD_ADC_CH12_ENABLE 
		case 12:ZD_ADC_CH12_ENABLE; cfgerr=0; break;
		#endif		
		#ifdef ZD_ADC_CH13_ENABLE 
		case 13:ZD_ADC_CH13_ENABLE; cfgerr=0; break;
		#endif
		#ifdef ZD_ADC_CH14_ENABLE 
		case 14:ZD_ADC_CH14_ENABLE; cfgerr=0; break;
		#endif
		#ifdef ZD_ADC_CH15_ENABLE 
		case 15:ZD_ADC_CH15_ENABLE; cfgerr=0; break;
		#endif 
		#ifdef ZD_ADC_CH16_ENABLE 
		case 16:ZD_ADC_CH16_ENABLE; cfgerr=0; break;
		#endif 
		#ifdef ZD_ADC_CH17_ENABLE 
		case 17:ZD_ADC_CH17_ENABLE; cfgerr=0; break;
		#endif 
		#ifdef ZD_ADC_CH18_ENABLE 
		case 18:ZD_ADC_CH18_ENABLE; cfgerr=0; break;
		#endif 
		#ifdef ZD_ADC_CH19_ENABLE 
		case 19:ZD_ADC_CH19_ENABLE; cfgerr=0; break;
		#endif 
		#ifdef ZD_ADC_CH20_ENABLE 
		case 20:ZD_ADC_CH20_ENABLE; cfgerr=0; break;
		#endif 
		#ifdef ZD_ADC_CH21_ENABLE 
		case 21:ZD_ADC_CH21_ENABLE; cfgerr=0; break;
		#endif 
		#ifdef ZD_ADC_CH22_ENABLE 
		case 22:ZD_ADC_CH22_ENABLE; cfgerr=0; break;
		#endif 
		#ifdef ZD_ADC_CH23_ENABLE 
		case 23:ZD_ADC_CH23_ENABLE; cfgerr=0; break;
		#endif 
		#ifdef ZD_ADC_CH24_ENABLE 
		case 24:ZD_ADC_CH24_ENABLE; cfgerr=0; break;
		#endif 
		#ifdef ZD_ADC_CH25_ENABLE 
		case 25:ZD_ADC_CH25_ENABLE; cfgerr=0; break;
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
#ifdef ADC_COLLECTION_CH_MAX
#if(ADC_COLLECTION_CH_MAX>0)
void zd_adcInit(unsigned char adcChannel,void (*callback)(unsigned int))
#endif
#else
void zd_adcInit(void)
#endif
{

#ifdef ADC_COLLECTION_CH_MAX
#if(ADC_COLLECTION_CH_MAX>0)
	//配置相应端口为ADC输入
	if(0==zd_adcChannelInit(adcChannel))
#endif
#endif
	{
		//配置ADC时钟
		ZD_ADC_CLKSET(ZD_ADC_CLKSET_DEFAULT);
		//配置ADC开启
		ZD_ADC_INIT;
		
		#ifdef ADC_COLLECTION_CH_MAX
		#if(ADC_COLLECTION_CH_MAX>0)
		//配置循环采集通道列表
		adc_ch[adc_ch_select_max]=adcChannel; 
		//配置采集通道周期回调函数
		adc_ch_callback[adc_ch_select_max]=callback; 
		//通道数递增（标识需采集的通道总数）
		adc_ch_select_max++;
		
		ZD_ADC_CH_SELECT(adcChannel);				//重新加载通道值
				
		#endif
		#endif
	}
}


/***************************************************
*函数名 		: zd_getAdc_async
*函数功能描述 	: ADC数据异步轮询采集
*函数参数 		: adcChannel:采集通道,*adcValue:采集后存放数据的指针
*函数返回值 	: uchar:当数据更新时返回1，否则返回0
***************************************************/
unsigned char zd_getAdc_async(unsigned char adcChannel,unsigned int *adcValue)
{

	if(adc_working==0)
	{
		if(0!=zd_adcChannelInit(adcChannel)) return 0;
		adcChannel_sync=adcChannel;
		ZD_ADC_CH_SELECT(adcChannel);				//重新加载通道值
		Adc_DelayUs(40);                        	//廷时等待电压稳定 Tst >10us
		ZD_ADC_START;             					//启动ADC 
		adc_working=1;
	}
	else if((ZD_ADC_ISNOTBUSY))
	{
		if(adcChannel_sync==adcChannel)
		{
			*adcValue=(unsigned int)(ZD_ADC_GETVAL); 
			adcChannel_sync=255;
			adc_working=0;
			return 1;
		}

		adc_working=0;
	}
	
    return 0;
} 

/***************************************************
*函数名 		: zd_getAdc_sync
*函数功能描述 	: ADC数据同步等待采集
*函数参数 		: adcChannel:采集通道,*adcValue:采集后存放数据的指针
*函数返回值 	: uchar:当数据更新时返回1，否则返回0
***************************************************/
unsigned char zd_getAdc_sync(unsigned char adcChannel,unsigned int *adcValue)
{
	unsigned char delay=100;

		if(0!=zd_adcChannelInit(adcChannel)) return 0;
		ZD_ADC_CH_SELECT(adcChannel);				//重新加载通道值
		Adc_DelayUs(40);                        	//廷时等待电压稳定 Tst >10us
	
		ZD_ADC_START;             					//启动ADC 

		//while((ZD_ADC_ISNOTBUSY))
		//{
		//	if(delay>0) delay--; else return 0;
		//}	
		
		while((ZD_ADC_ISBUSY))
		{
			if(delay>0) delay--; else return 0;
		}
	
	
		*adcValue=(unsigned int)(ZD_ADC_GETVAL); 

    return 1;
} 



/***************************************************
*函数名 		: zd_adcRun
*函数功能描述 	: ADC多通道异步轮询批量采集（含通道采集周期回调）
*函数参数 		: 无
*函数返回值 	: 无
***************************************************/
#ifdef ADC_COLLECTION_CH_MAX
#if(ADC_COLLECTION_CH_MAX>0)
void zd_adcRun(void)
{
	if(0!=zd_getAdc_async(adc_ch[adc_ch_select],&(adc_value_list[adc_ch_select][adc_ch_collection_times])))  
	{
		if(++adc_ch_collection_times>=ADC_COLLECTION_LIST_TIMES) 
		{

			//求和周期值并计算平均值
			#if(ADC_COLLECTION_LIST_TIMES>1)
			adc_value_sum=0;
			for(adc_ch_collection_times=0;adc_ch_collection_times<ADC_COLLECTION_LIST_TIMES;adc_ch_collection_times++)
			{
				adc_value_sum+=adc_value_list[adc_ch_select][adc_ch_collection_times];
			}
			adc_value_sum=adc_value_sum/ADC_COLLECTION_LIST_TIMES;
			#else
				adc_value_sum=adc_value_list[adc_ch_select][adc_ch_collection_times];
			#endif
			//通道周期采集完成回调
			//if(adc_ch_callback[adc_ch_select]!=NULL)
				(*(adc_ch_callback[adc_ch_select]))((unsigned int)adc_value_sum);
			
			//复位周期采集标志
			adc_ch_collection_times=0;
			
			//切换下一通道
			if(++adc_ch_select>=adc_ch_select_max) adc_ch_select=0;
		}
	}
}
#endif
#endif

/************************ (C) COPYRIGHT zhejiang zhida *****END OF FILE****/