/************************************************************************************************ 

*************************************************************************************************/
#include "com_include_core.h"

/***********************************************************************************************
*������ 		: core_DelayUs(unsigned char dl_t)
*������������ 	: �ں˶���ʱ
*�������� 		: unsigned char dl_t����ʱ����Լ���ڿ�ָ������
*��������ֵ 	: ��
***********************************************************************************************/
void core_DelayUs(unsigned char dl_t)
{
	unsigned char a;

	for(a=0;a<dl_t;a++)
	{
		
		ZD_NOP;
	}
}  


/***********************************************************************************************
*������ 		: void zd_systemInit(void)
*������������ 	: ��ʼ��ϵͳʱ��
*�������� 		: ��
*��������ֵ 	: ��
***********************************************************************************************/
void zd_systemInit(void)
{
	//�ر����ж�
	ZD_GIE_DISABLE;

	//BORĬ�ϴ���������


	//ϵͳʱ�ӳ�ʼ��
	ZD_FSYS_CLKSET(ZD_FSYS_CLKSET_DEFAULT);
	
	//�жϳ�ʼ������
	ZD_INTERRUPT_INIT;  					//�ݽ�ֹ�����ж�
	
	//�˿ڳ�ʼ��(Ĭ��ֵ)
	ZD_PORT_INIT;
}


/***********************************************************************************************
*������ 		: void zd_timerInit(unsigned char timerChannel)
*������������ 	: ��ʼ����ʱ��
*�������� 		: unsigned char timerChannel:��ʱ����,
				  unsigned long _Us����ʱ��ʱ��
*��������ֵ 	: ��
***********************************************************************************************/
void zd_timerInit(unsigned char timerChannel)
{
	unsigned char cfgerr=1;
	
	//������Ӧtimer��ʱ��
	switch(timerChannel)
	{
		case 0:
		#ifdef Ft0Clk

		#ifdef T0_RELOAD_DEFAULT
			#ifdef ZD_TIMER0_LOAD_RELOAD
				ZD_TIMER0_LOAD_RELOAD(T0_RELOAD_DEFAULT);		//���¸���ֵ
			#else
				T0L_Reload=T0_RELOAD_DEFAULT;
				T0H_Reload=T0_RELOAD_DEFAULT>>8;
			#endif	
			
		#endif
	
			ZD_TIMER0_INIT;

			ZD_T0IE_ENABLE;

			ZD_T0_ENABLE;
		
		 cfgerr=0; 
		#endif
		 break;
		case 1:
		#ifdef Ft1Clk

		#ifdef T1_RELOAD_DEFAULT
			#ifdef ZD_TIMER0_LOAD_RELOAD
				ZD_TIMER1_LOAD_RELOAD(T1_RELOAD_DEFAULT);		//���¸���ֵ
			#else
				T1L_Reload=T1_RELOAD_DEFAULT;
				T1H_Reload=T1_RELOAD_DEFAULT>>8;
			#endif	
			
		#endif
	
			ZD_TIMER1_INIT;

			ZD_T1IE_ENABLE;

			ZD_T1_ENABLE;

		//ZD_T1IE_ENABLE;
		//T1CON=0x31;
		
		 //T1H_Reload = (65536 - ((unsigned int)((_Us*1.0)*((Ft1Clk*1.0)/1000000))))>>8;
		 //T1L_Reload = (65536 - ((unsigned int)((_Us*1.0)*((Ft1Clk*1.0)/1000000))));
		 //ZD_TIMER1_INIT;
		 cfgerr=0; 
		#endif
		 break;
		case 2:
		#ifdef Ft2Clk

		#ifdef T2_RELOAD_DEFAULT
			#ifdef ZD_TIMER2_LOAD_RELOAD
				ZD_TIMER2_LOAD_RELOAD(T2_RELOAD_DEFAULT);		//���¸���ֵ
			#else
				..T2L_Reload=T2_RELOAD_DEFAULT;
				..T2H_Reload=T2_RELOAD_DEFAULT>>8;
			#endif	
			
			ZD_TIMER2_LOAD_SET(T2_RELOAD_DEFAULT);
		#endif
				 		
		 ZD_TIMER2_INIT;

		 ZD_TIMER2_CLKSET(ZD_TIMER2_CLKSET_DEFAULT);

		 ZD_T2IE_ENABLE;
		 
		 ZD_T2_ENABLE;
		 cfgerr=0; 
		#endif
		 break;

		default:break;
	}
	
	//�����ж�
	if(cfgerr==0)
	{

	
	}

}
/*
void zd_adcInit(unsigned char ch)
{
	//������Ӧ�˿�ΪADC����
	switch(ch)
	{
		#ifdef ZD_ADC_CH0_ENABLE 
		case 0:ZD_ADC_CH0_ENABLE; break;
		#endif
		case 1:ZD_ADC_CH1_ENABLE; break;
		case 2:ZD_ADC_CH2_ENABLE; break;
		case 3:ZD_ADC_CH3_ENABLE; break;
		case 4:ZD_ADC_CH4_ENABLE; break;
		case 5:ZD_ADC_CH5_ENABLE; break;
		case 6:ZD_ADC_CH6_ENABLE; break;
		case 7:ZD_ADC_CH7_ENABLE; break;
		case 8:ZD_ADC_CH8_ENABLE; break;
		case 9:ZD_ADC_CH9_ENABLE; break;
		case 10:ZD_ADC_CH10_ENABLE; break;
		case 11:ZD_ADC_CH11_ENABLE; break;
		case 12:ZD_ADC_CH12_ENABLE; break;
		case 13:ZD_ADC_CH13_ENABLE; break;
		#ifdef ZD_ADC_CH14_ENABLE 
		case 14:ZD_ADC_CH14_ENABLE; break;
		#endif
		#ifdef ZD_ADC_CH15_ENABLE 
		case 15:ZD_ADC_CH15_ENABLE; break;
		#endif 
		default:break;
	}
	
	//����ADCʱ��
	ZD_ADC_CLKSET(ZD_ADC_CLKSET_DEFAULT);
	//����ADC����
	ZD_ADC_INIT;

}

void zd_adcOff(void)
{
	
}

void zd_uartInit(void)
{
	
}


unsigned char zd_getadc_sync(unsigned char adcChannel,unsigned int *adcValue)
{
    if(0==ZD_ADC_ISBUSY)
    {
		if(adcChannel_sync==adcChannel)
		{
			*adcValue=(ZD_ADC_GETVAL); 
            adcChannel_sync=255;
            return 1;
		}
        adcChannel_sync=adcChannel;
  
		ZD_ADC_CH_SELECT(adcChannel);  	//���¼���ͨ��ֵ			

		
		core_DelayUs(40);                        	//͢ʱ�ȴ���ѹ�ȶ� Tst >10us
		ZD_ADC_START;//ADCON0 = ADCON0|0x02;             					//����ADC 
		
		core_DelayUs(2);

	}
    return 0;
} 

*/