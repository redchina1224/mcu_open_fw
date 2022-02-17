//******************************************************************************
//Copyright(C) 2020-2021 zhejiang zhida dianzikeji Co., Ltd
//�㽭�Ǵ���ӿƼ����޹�˾
//File name:      zd_adc.c
//Author:         zzg
//Version:        Ver0.1
//Date:           2021-4-25
//Description:    ADC�ɼ�
//History:
//******************************************************************************
//ͷ�ļ�************************************************************************
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
 *	�������ƣ�DelayUs
 *	���ܣ�   ����ʱ���� --16M-2T--��ſ�1%����.
 *	���������Time ��ʱʱ�䳤�� ��ʱʱ��Time Us
 *	���ز������� 
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
*������ 		: zd_adcChannleInit
*������������ 	: ADCͨ����ʼ��
*�������� 		: adcChannel:�ɼ�ͨ��,*callback:�ɼ�������ɺ�Ļص�����
*��������ֵ 	: ��
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
*������ 		: zd_adcInit
*������������ 	: ADCͨ����ɼ���ʼ��
*�������� 		: adcChannel:�ɼ�ͨ��,*callback:�ɼ�������ɺ�Ļص�����
*��������ֵ 	: ��
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
	//������Ӧ�˿�ΪADC����
	if(0==zd_adcChannelInit(adcChannel))
#endif
#endif
	{
		//����ADCʱ��
		ZD_ADC_CLKSET(ZD_ADC_CLKSET_DEFAULT);
		//����ADC����
		ZD_ADC_INIT;
		
		#ifdef ADC_COLLECTION_CH_MAX
		#if(ADC_COLLECTION_CH_MAX>0)
		//����ѭ���ɼ�ͨ���б�
		adc_ch[adc_ch_select_max]=adcChannel; 
		//���òɼ�ͨ�����ڻص�����
		adc_ch_callback[adc_ch_select_max]=callback; 
		//ͨ������������ʶ��ɼ���ͨ��������
		adc_ch_select_max++;
		
		ZD_ADC_CH_SELECT(adcChannel);				//���¼���ͨ��ֵ
				
		#endif
		#endif
	}
}


/***************************************************
*������ 		: zd_getAdc_async
*������������ 	: ADC�����첽��ѯ�ɼ�
*�������� 		: adcChannel:�ɼ�ͨ��,*adcValue:�ɼ��������ݵ�ָ��
*��������ֵ 	: uchar:�����ݸ���ʱ����1�����򷵻�0
***************************************************/
unsigned char zd_getAdc_async(unsigned char adcChannel,unsigned int *adcValue)
{

	if(adc_working==0)
	{
		if(0!=zd_adcChannelInit(adcChannel)) return 0;
		adcChannel_sync=adcChannel;
		ZD_ADC_CH_SELECT(adcChannel);				//���¼���ͨ��ֵ
		Adc_DelayUs(40);                        	//͢ʱ�ȴ���ѹ�ȶ� Tst >10us
		ZD_ADC_START;             					//����ADC 
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
*������ 		: zd_getAdc_sync
*������������ 	: ADC����ͬ���ȴ��ɼ�
*�������� 		: adcChannel:�ɼ�ͨ��,*adcValue:�ɼ��������ݵ�ָ��
*��������ֵ 	: uchar:�����ݸ���ʱ����1�����򷵻�0
***************************************************/
unsigned char zd_getAdc_sync(unsigned char adcChannel,unsigned int *adcValue)
{
	unsigned char delay=100;

		if(0!=zd_adcChannelInit(adcChannel)) return 0;
		ZD_ADC_CH_SELECT(adcChannel);				//���¼���ͨ��ֵ
		Adc_DelayUs(40);                        	//͢ʱ�ȴ���ѹ�ȶ� Tst >10us
	
		ZD_ADC_START;             					//����ADC 

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
*������ 		: zd_adcRun
*������������ 	: ADC��ͨ���첽��ѯ�����ɼ�����ͨ���ɼ����ڻص���
*�������� 		: ��
*��������ֵ 	: ��
***************************************************/
#ifdef ADC_COLLECTION_CH_MAX
#if(ADC_COLLECTION_CH_MAX>0)
void zd_adcRun(void)
{
	if(0!=zd_getAdc_async(adc_ch[adc_ch_select],&(adc_value_list[adc_ch_select][adc_ch_collection_times])))  
	{
		if(++adc_ch_collection_times>=ADC_COLLECTION_LIST_TIMES) 
		{

			//�������ֵ������ƽ��ֵ
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
			//ͨ�����ڲɼ���ɻص�
			//if(adc_ch_callback[adc_ch_select]!=NULL)
				(*(adc_ch_callback[adc_ch_select]))((unsigned int)adc_value_sum);
			
			//��λ���ڲɼ���־
			adc_ch_collection_times=0;
			
			//�л���һͨ��
			if(++adc_ch_select>=adc_ch_select_max) adc_ch_select=0;
		}
	}
}
#endif
#endif

/************************ (C) COPYRIGHT zhejiang zhida *****END OF FILE****/