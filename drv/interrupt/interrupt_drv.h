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



#ifdef Uart0_Type
extern unsigned char * Uart0_TxBuff_P;
extern unsigned char * Uart0_RxBuff_P;

extern unsigned char Uart0_Comm_TimeOut_x10msec;
extern unsigned char Uart0_Recv_Byte_Length;
extern unsigned char Uart0_Recv_Over_Checking;

extern unsigned char Uart0_Sended_Byte_Length;
extern unsigned char Uart0_NeedSend_Byte_Length;
extern unsigned char Uart0_Send_Busy;

#endif

#ifdef Uart1_Type
extern unsigned char * Uart1_TxBuff_P;
extern unsigned char * Uart1_RxBuff_P;

extern unsigned char Uart1_Comm_TimeOut_x10msec;
extern unsigned char Uart1_Recv_Byte_Length;
extern unsigned char Uart1_Recv_Over_Checking;

extern unsigned char Uart1_Sended_Byte_Length;
extern unsigned char Uart1_NeedSend_Byte_Length;
extern unsigned char Uart1_Send_Busy;

#endif

#ifdef PowerOffCheckType
#if (PowerOffCheckType==PowerOffCheckType_MCULVD)
extern bit M_PowerOff_bit;
#endif
#endif


#ifdef BuzzerType
#if (BuzzerType==BuzzerType_TimerInv)
extern unsigned char *T_BuzzerEn;
#endif
#endif


#ifdef RtcType
#if (RtcType==RtcType_TimerSoftRtc) 
extern bit M_10ms_bit;
extern bit M_20ms_bit;
extern bit M_40ms_bit;
//extern bit M_50ms_bit;
extern bit M_100ms_bit;
extern bit M_1s_bit;
//extern unsigned long *T_SecCount;
#endif
#endif



#ifdef CounterType
#if (CounterType==CounterType_SoftCounter) 

	#ifdef Counter_IO_Channel1
	void softcounter1_reset(void);
	extern unsigned int *T_Counter1_1sec;
	extern unsigned int *T_Counter1_Total;
	#endif


	#ifdef Counter_IO_Channel2
	void softcounter2_reset(void);
	extern unsigned int *T_Counter2_1sec;
	extern unsigned int *T_Counter2_Total;
	#endif


#endif
#endif



#ifdef ZeroCrossType
	#if (ZeroCrossType==ZeroCrossType_Gpio) 
	extern unsigned char zeroCrossPassCntMax;
	extern unsigned char triacOn_CrossPass;
	extern bit triacOnEnable;
	extern bit zeroCrossError;
	#endif
#endif 



#ifdef Ft0Clk
extern unsigned char T0L_Reload;
extern unsigned char T0H_Reload;
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