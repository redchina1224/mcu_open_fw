/************************************************************************************************ 

*************************************************************************************************/
#include "com_include_core.h"

/***********************************************************************************************
*函数名 		: core_DelayUs(unsigned char dl_t)
*函数功能描述 	: 内核短延时
*函数参数 		: unsigned char dl_t：延时计数约等于空指令周期
*函数返回值 	: 无
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
*函数名 		: void zd_systemInit(void)
*函数功能描述 	: 初始化系统时钟
*函数参数 		: 无
*函数返回值 	: 无
***********************************************************************************************/
void zd_systemInit(void)
{
	//关闭总中断
	ZD_GIE_DISABLE;

	//BOR默认打开无需配置


	//系统时钟初始化
	ZD_FSYS_CLKSET(ZD_FSYS_CLKSET_DEFAULT);
	
	//中断初始化清零
	ZD_INTERRUPT_INIT;  					//暂禁止所有中断
	
	//端口初始化(默认值)
	ZD_PORT_INIT;
}


/***********************************************************************************************
*函数名 		: void zd_timerInit(unsigned char timerChannel)
*函数功能描述 	: 初始化定时器
*函数参数 		: unsigned char timerChannel:定时器号,
				  unsigned long _Us：定时器时间
*函数返回值 	: 无
***********************************************************************************************/
void zd_timerInit(unsigned char timerChannel)
{
	unsigned char cfgerr=1;
	
	//配置相应timer定时器
	switch(timerChannel)
	{
		case 0:
		#ifdef Ft0Clk

		#ifdef T0_RELOAD_DEFAULT
			#ifdef ZD_TIMER0_LOAD_RELOAD
				ZD_TIMER0_LOAD_RELOAD(T0_RELOAD_DEFAULT);		//重新赋初值
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
				ZD_TIMER1_LOAD_RELOAD(T1_RELOAD_DEFAULT);		//重新赋初值
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
				ZD_TIMER2_LOAD_RELOAD(T2_RELOAD_DEFAULT);		//重新赋初值
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
	
	//配置中断
	if(cfgerr==0)
	{

	
	}

}
/*
void zd_adcInit(unsigned char ch)
{
	//配置相应端口为ADC输入
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
	
	//配置ADC时钟
	ZD_ADC_CLKSET(ZD_ADC_CLKSET_DEFAULT);
	//配置ADC开启
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
  
		ZD_ADC_CH_SELECT(adcChannel);  	//重新加载通道值			

		
		core_DelayUs(40);                        	//廷时等待电压稳定 Tst >10us
		ZD_ADC_START;//ADCON0 = ADCON0|0x02;             					//启动ADC 
		
		core_DelayUs(2);

	}
    return 0;
} 

*/