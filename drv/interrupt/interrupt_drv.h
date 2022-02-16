//******************************************************************************
//Copyright(C) 2020-2021 zhejiang zhida dianzikeji Co., Ltd
//浙江智达电子科技有限公司
//File name:      interrupt_core.h
//Author:         zzg
//Version:        Ver0.1
//Date:           2021-4-25
//Description:    中断处理
//History:
//******************************************************************************
#ifndef __INTERRUPT_CORE_H__
#define __INTERRUPT_CORE_H__

//#include "..\bsp\bsp.h"

//声明外部变量******************************************************************


#ifdef BuzzerType
#if (BuzzerType==BuzzerType_TimerInv)
extern unsigned char *T_BuzzerEn;
#endif
#endif


#ifdef RtcType
#if (RtcType==RtcType_TimerSoftRtc) 
extern bit T_1ms_bit;
extern unsigned int *T_msCount;
extern unsigned long *T_SecCount;
#endif
#endif



#ifdef CounterType
#if (CounterType==CounterType_SoftCounter) 

	#ifdef Counter_IO_Channel1
	extern unsigned char *T_Counter1_1sec;
	#endif


#endif
#endif



#ifdef ZeroCrossType
	#if (ZeroCrossType==ZeroCrossType_Gpio) 
	extern unsigned char zeroCrossPassCntMax;
	extern unsigned char triacOn_CrossPass;
	extern bit triacOnEnable;
	#endif
#endif 



#ifdef Ft0Clk
extern unsigned char T0_Reload;
#endif

#ifdef Ft1Clk
extern unsigned char T1L_Reload;
extern unsigned char T1H_Reload;
#endif

#ifdef Ft2Clk
extern unsigned char T2L_Reload;
extern unsigned char T2H_Reload;
#endif






//声明外部函数******************************************************************


#endif 


/************************ (C) COPYRIGHT zhejiang zhida *****END OF FILE****/