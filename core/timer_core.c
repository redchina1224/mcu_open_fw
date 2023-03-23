//******************************************************************************
//Copyright(C) 2020-2021 zhejiang zhida dianzikeji Co., Ltd
//浙江智达电子科技有限公司
//File name:      user_time.c
//Author:         zzg
//Version:        Ver0.1
//Date:           2021-4-25
//Description:    TIME时间处理
//History:
//******************************************************************************
//头文件************************************************************************
#include "com_include_core.h"


/***********************************************************************************************
*函数名 		: void zd_timerInit(unsigned char timerChannel)
*函数功能描述 	: 初始化定时器
*函数参数 		: unsigned char timerChannel:定时器号,
				  unsigned long _Us：定时器时间
*函数返回值 	: 无
***********************************************************************************************/
void mof_timerInit(unsigned char timerChannel)
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
			#ifdef MOF_TIMER2_LOAD_RELOAD
				MOF_TIMER2_LOAD_RELOAD(T2_RELOAD_DEFAULT);		//重新赋初值
			#else
				..T2L_Reload=T2_RELOAD_DEFAULT;
				..T2H_Reload=T2_RELOAD_DEFAULT>>8;
			#endif	
			
			MOF_TIMER2_LOAD_SET(T2_RELOAD_DEFAULT);
		#endif
				 		
		 MOF_TIMER2_INIT;

		 //ZD_TIMER2_CLKSET(ZD_TIMER2_CLKSET_DEFAULT);

		 MOF_T2IE_ENABLE;
		 
		 MOF_T2_ENABLE;

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

/************************ (C) COPYRIGHT zhejiang zhida *****END OF FILE****/