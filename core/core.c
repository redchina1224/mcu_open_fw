/************************************************************************************************ 

*************************************************************************************************/
#include "..\..\project.h"

void core_DelayUs(unsigned char dl_t)
{
	unsigned char a;

	for(a=0;a<dl_t;a++)
	{
		
		ZD_NOP;
	}
}  

void zd_systemInit(void)
{
	//系统时钟初始化
	ZD_FSYS_CLKSET(ZD_FSYS_CLKSET_DEFAULT);
	
	//端口初始化(默认值)
	
}
/*
void zd_timer0Init(unsigned int _Us)
{
	T0_Reload= (	256 - ((unsigned int)	((_Us*1.0)*((Ft0Clk*1.0)/1000000))));
}
void zd_timer1Init(unsigned int _Ms)
{
	//TH0_Reload = (65536 - ((unsigned int)((_Us*1.0)*((Ft1Clk*1.0)/1000))))>>8;
	//TL0_Reload = (65536 - ((unsigned int)((_Us*1.0)*((Ft1Clk*1.0)/1000))));
}

void zd_timer0Init_ms(unsigned char us)
{
	OPTION_REG = 0xD8;		//Timer0使用内部时钟Focs/4，预分频比为1:2
	TMR0 = 0;				//赋予初始值
	//INTCON = 0xA0;			//允许所有未被屏蔽的中断、禁止外设中断，使能Timer0
	T0IE=1;
	GIE=1;
}

void zd_timer1Init(void)
{
	TMR1L = 0x20;			//赋初值
	TMR1H = 0x4E;
	TMR1IF = 0;				//清中断标志位
	TMR1IE = 1;				//允许Timer1中断	
	T1CON = 0x31;			//开启Timer1，使用内部时钟源Fosc，预分频比为1:8
	//INTCON = 0xC0;			//允许所有未被屏蔽的中断、外设中断
	PEIE=1;
	TMR1IE=1;
	GIE=1;
}
*/


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