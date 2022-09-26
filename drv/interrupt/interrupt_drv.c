 //******************************************************************************
//Copyright(C) 2020-2021 Zhejiang Zhida Electronic Technology Co., Ltd
//浙江智达电子科技有限公司
//File name:      interrupt_core.c
//Author:         zzg
//Version:        Ver0.1
//Date:           2021-4-25
//Description:    中断服务程序集合(所有与中断服务相关的统一放在这里)
//History:
//******************************************************************************
#include "..\com_include_drv.h"

//extern void __CMS_GetTouchKeyValue(void);





#ifdef Ft0Clk
#ifndef ZD_TIMER0_LOAD_RELOAD
 unsigned char T0L_Reload;
 unsigned char T0H_Reload;
#endif	
#endif

#ifdef Ft1Clk
#ifndef ZD_TIMER1_LOAD_RELOAD
 unsigned char T1L_Reload;
 unsigned char T1H_Reload;
#endif	
#endif

#ifdef Ft2Clk
#ifndef ZD_TIMER2_LOAD_RELOAD
 unsigned char T2L_Reload;
 unsigned char T2H_Reload;
#endif	
#endif


/*
void interrupt_SoftRtcConfig(unsigned char *T_ms,unsigned long *T_sec)
{
	T_msCount=T_ms;
	T_SecCount=T_sec;
}
*/

#ifdef PowerOffCheckType
#if (PowerOffCheckType==PowerOffCheckType_MCULVD)
bit M_PowerOff_bit=0;

#if (DevPlatform==DevPlatform_Keil_C51)
void powerofflvd_in_isr(void)
#else
inline void powerofflvd_in_isr(void)
#endif
{
	M_PowerOff_bit=1;
	ZD_GIE_DISABLE;
}
#endif
#endif

#ifdef BuzzerType
#if (BuzzerType==BuzzerType_TimerInv)

unsigned char __buzzer_en=0;
unsigned char *T_BuzzerEn=&__buzzer_en;

#if (DevPlatform==DevPlatform_Keil_C51)
void buzzer_in_isr(void)
#else
inline void buzzer_in_isr(void)
#endif
{
	if((*T_BuzzerEn)!=0) Buzzer_IO_Channel=!Buzzer_IO_Channel; else Buzzer_IO_Input;
	//Buzzer_IO_Output;
	//Buzzer_IO_Channel=!Buzzer_IO_Channel;
}

#endif
#endif


#ifdef RtcType
#if (RtcType==RtcType_TimerSoftRtc) 

bit T_500ms_bit=0;
bit T_1s_bit=0;
bit M_10ms_bit=0;
bit M_20ms_bit=0;
bit M_50ms_bit=0;
bit M_100ms_bit=0;
bit M_1s_bit=0;
 unsigned char __125usCount_0=0;
 unsigned char __125usCount=0;
 unsigned char __20msCount=0;
 unsigned char __100msCount=0; 
 //unsigned long __SecCount=0;
 //unsigned long *T_SecCount=&__SecCount;

#if (DevPlatform==DevPlatform_Keil_C51)
void softrtc_in_isr(void)
#else
inline void softrtc_in_isr(void)
#endif
{
#ifdef SoftRtcTimerBaseUs
#if (SoftRtcTimerBaseUs<10000)
	if(++__125usCount>=(10000/SoftRtcTimerBaseUs)) 
	{ 
		__125usCount=0; 
#endif
#endif
		M_20ms_bit=1;
		if(++__20msCount>=5) 
		{
			__20msCount=0;
			//M_50ms_bit=1;
			M_100ms_bit=1;
			
			if(++__100msCount>=10)
			{
				__100msCount=0;
				M_1s_bit=1;
				T_1s_bit=1;
				T_500ms_bit=1;
				//(*T_SecCount)++;
			}
			else if(__100msCount==5) 
				T_500ms_bit=1;

		}
		//else if(__20msCount==5)
		//	M_50ms_bit=1;
#ifdef SoftRtcTimerBaseUs			
#if (SoftRtcTimerBaseUs<10000)
	}
	//else if(T_125usCount==40)
	//	M_5ms_bit=1;
#endif
#endif

}
#endif
#endif





#ifdef CounterType
#if (CounterType==CounterType_SoftCounter) 

#ifdef Counter_IO_Channel1

bit __counter1_bit_status_ago;
unsigned int __counter1_val=0;
unsigned char __counter1filter=0;
unsigned int *T_Counter1_1sec=&__counter1_val;
unsigned int *T_Counter1_Total=&__counter1_val;

void softcounter1_reset(void)
{
	ZD_GIE_DISABLE;
	(*T_Counter1_1sec)=0;
	(*T_Counter1_Total)=0;
	ZD_GIE_ENABLE;
}

#if (DevPlatform==DevPlatform_Keil_C51)
void softcounter1_in_isr(void)
#else
inline void softcounter1_in_isr(void)
#endif
{
		if(T_500ms_bit)//半秒周期,上升沿与下降沿都累加，所得累加值等同于1秒的值
		{
			(*T_Counter1_1sec)=__counter1_val; 
			(*T_Counter1_Total)+=__counter1_val;
			__counter1_val=0;
		}

		if(Counter_IO_Channel1==0)
		{
			if(__counter1filter<10) __counter1filter++;
			else
			{
				if(__counter1_bit_status_ago==1)//下降沿
				{
					if(__counter1_val<64999)	__counter1_val++;
					__counter1_bit_status_ago=0;
				}
			}
		}
		else
		{
			if(__counter1filter>0) __counter1filter--;
			else
			{ 
				if(__counter1_bit_status_ago==0)//上升沿
				{
					if(__counter1_val<64999)	__counter1_val++;
					__counter1_bit_status_ago=1;
				}
			}
		}
}
#endif //#ifdef Counter_IO_Channel1


#endif //#if (CounterType==CounterType_SoftCounter) 
#endif //#ifdef CounterType
			




#ifdef ZeroCrossType
	#if (ZeroCrossType==ZeroCrossType_Gpio) 
	bit zeroCrossError=0;
	bit __zerocross_bit_status_ago;
	bit triacOnEnable=0;
	unsigned char __zerocrossfilter=0;
	unsigned char zeroCrossPassCntMax;
	unsigned char zeroCrossPassCnt;
	unsigned char triacOn_CrossPass=40;

#if (DevPlatform==DevPlatform_Keil_C51)
void zerocross_in_isr(void)
#else
inline void zerocross_in_isr(void)
#endif
{
	//过零检测与清零
	/*
	if(ZeroCross_IO_Channel==0)
	{
		if(__zerocrossfilter<5) __zerocrossfilter++;
		else
		{
			if(__zerocross_bit_status_ago==1)
			{
				zeroCrossPassCntMax=zeroCrossPassCnt;
				zeroCrossPassCnt=5;
				//Triac_IO_Ctrl(Triac_IO_OFF);
				__zerocross_bit_status_ago=0;
			}
		
		}
	}
	else
	{
		if(__zerocrossfilter>0) __zerocrossfilter--;
		else
		{	
			if(zeroCrossPassCnt<150) zeroCrossPassCnt++; else zeroCrossError=1;
			//可控硅控制
			//if(triacOnEnable==1&&zeroCrossPassCnt>triacOn_CrossPass)
			//Triac_IO_Ctrl(Triac_IO_ON);
			__zerocross_bit_status_ago=1;
		}
	}
	
	*/
	
	//过零检测 100HZ--zeroCrossPassCnt最大值为80
	if(zeroCrossPassCnt<200) zeroCrossPassCnt++; else { zeroCrossError=1; zeroCrossPassCntMax=200;}
	
	if(__zerocross_bit_status_ago!=ZeroCross_IO_Channel)
	{
		if(0==__zerocross_bit_status_ago)
		{
			zeroCrossPassCntMax=zeroCrossPassCnt;
			zeroCrossPassCnt=0;
			__zerocross_bit_status_ago=1;
			Triac_IO_Ctrl(Triac_IO_OFF);
		}
		else
		{
			__zerocross_bit_status_ago=0;
		}
	}

	//可控硅控制
	if(triacOnEnable==1&&zeroCrossPassCnt>triacOn_CrossPass)
	{
		Triac_IO_Ctrl(Triac_IO_ON);
	}
	else
	{
		Triac_IO_Ctrl(Triac_IO_OFF);
	}

}

	#endif
#endif 

			
			
//按平台定义或载入对应头文件
#if ((DevPlatform==DevPlatform_CMSIDE_CASD))
	
void interrupt interrupt_Isr()
{
#ifdef PowerOffCheckType
#if (PowerOffCheckType==PowerOffCheckType_MCULVD)
	if(ZD_LVDIF_GRIGGER)
	{
		powerofflvd_in_isr();
		ZD_LVDIF_CLEAN;	//清中断标志位
	}	
#endif
#endif


	
#ifdef Ft0Clk	
	if(ZD_T0IF_GRIGGER)
	{
	//---------------------------------------
		#ifndef ZD_TIMER0_LOAD_RELOAD
			ZD_TIMER0_LOAD_ADD_SET(T0_RELOAD_DEFAULT);		//重新赋初值，在赋值前Timer0已有计数，故在该基础上加初值
		#endif
	//---------------------------------------

	if(++__125usCount_0>=80) 
	{ 
		__125usCount_0=0; 
		M_10ms_bit=1;
	}
	//定时器蜂鸣驱动
	#ifdef BuzzerType	
		#if (BuzzerType==BuzzerType_TimerInv)
			#if(BuzzeTimer==0)
				buzzer_in_isr();
			#endif
		#endif
	#endif	//#ifdef BuzzerType	

	//软件时钟系统
	#if (RtcType==RtcType_TimerSoftRtc) 
		#if(SoftRtcTimer==0)
			T_1s_bit=0;
			T_500ms_bit=0;
			softrtc_in_isr();//RTC时钟内联函数
		#endif //#if(SoftRtcTimer==0)
	#endif //#if (RtcType==RtcType_TimerSoftRtc) 

	//软件显示驱动			
	#ifdef DisplayType
		#if ((DisplayType&DisplayType_SoftLed)==DisplayType_SoftLed) 
			#ifdef DisplayTypeSoftLedModel
				#if(SoftLedTimer==0)
					zd_softled_run();//软件LED驱动函数
				#endif //#if(SoftLedTimer==0)
			#endif
		#endif
	#endif //#ifdef DisplayType

	//软件计数系统
	#ifdef CounterType
		#if (CounterType==CounterType_SoftCounter) 
			#if(SoftCounterTimer==0)
				#ifdef Counter_IO_Channel1
					softcounter1_in_isr();//softcount1软件计数器内联函数
					T_1s_bit=0;
					T_500ms_bit=0;
				#endif
			#endif //#if(SoftCounterTimer==0)
		#endif
	#endif //#ifdef CounterType

			
	//可控硅过零系统	
	#ifdef ZeroCrossType
		#if (ZeroCrossType==ZeroCrossType_Gpio) 
			#if(ZeroCrossTimer==0)
				zerocross_in_isr();//zerocross过零与可控硅驱动内联函数
			#endif //#if(ZeroCrossTimer==0)
		#endif
	#endif //#ifdef ZeroCrossType

	//按键系统
	#ifdef KeyType
		#if ((KeyType&KeyType_IR)==KeyType_IR)

		#endif
		
		#if ((KeyType&KeyType_RF)==KeyType_RF)
			__ZD_GetRfKeyValue();//射频遥控接收函数
		#endif					

		#if ((KeyType&KeyType_McuTouch)==KeyType_McuTouch)
			#if(McuTouchTimer==0)
				#if ((McuType&McuType_Mask)==McuType_CmsSemicon_CMS79F)
				__CMS_GetTouchKeyValue();//中微单片机触摸库函数,此函数放在中断,建议中断扫描时间 125us	
				#endif	
			#endif //#if(McuTouchTimer==0)		
		#endif //#if ((KeyType&KeyType_McuTouch)==KeyType_McuTouch)		
	#endif	//#ifdef KeyType	

	ZD_T0IF_CLEAN;			//清中断标志位
	}
#endif	//#ifdef Ft0Clk
	
/*
//#ifdef Ft1Clk	
	if(TMR1IF)
	{
	//---------------------------------------
	#ifndef ZD_TIMER1_LOAD_RELOAD
		ZD_TIMER1_LOAD_ADD_SET(T1_RELOAD_DEFAULT);
	#endif
	//---------------------------------------	

	//软件时钟系统
	#if (RtcType==RtcType_TimerSoftRtc) 
		#if(SoftRtcTimer==1)
			softrtc_in_isr();//RTC时钟内联函数
		#endif //#if(SoftRtcTimer==0)
	#endif //#if (RtcType==RtcType_TimerSoftRtc) 		
	
	TMR1IF = 0;				//清中断标志位
	}
//#endif
*/

#ifdef Ft2Clk	
	if(ZD_T2IF_GRIGGER)
	{
	//---------------------------------------
	#ifndef ZD_TIMER2_LOAD_RELOAD
		ZD_TIMER2_LOAD_ADD_SET(T2_RELOAD_DEFAULT);		//重新赋初值，在赋值前Timer0已有计数，故在该基础上加初值
	#endif
	
	
	//---------------------------------------
		
	//定时器蜂鸣驱动
	#ifdef BuzzerType	
		#if (BuzzerType==BuzzerType_TimerInv)
			#if(BuzzeTimer==2)
				buzzer_in_isr();
			#endif
		#endif
	#endif	//#ifdef BuzzerType	
	
	//软件时钟系统
	#if (RtcType==RtcType_TimerSoftRtc) 
		#if(SoftRtcTimer==2)
			softrtc_in_isr();//RTC时钟内联函数
		#endif //#if(SoftRtcTimer==0)
	#endif //#if (RtcType==RtcType_TimerSoftRtc) 

	//软件显示驱动			
	#ifdef DisplayType
		#if ((DisplayType&DisplayType_SoftLed)==DisplayType_SoftLed) 
			#ifdef DisplayTypeSoftLedModel
				#if(SoftLedTimer==2)
					zd_softled_run();//软件LED驱动函数
				#endif //#if(SoftLedTimer==0)
			#endif
		#endif
	#endif //#ifdef DisplayType

	//软件计数系统
	#ifdef CounterType
		#if (CounterType==CounterType_SoftCounter) 
			#if(SoftCounterTimer==2)
				#ifdef Counter_IO_Channel1
					softcounter1_in_isr();//softcount1软件计数器内联函数
				#endif
			#endif //#if(SoftCounterTimer==0)
		#endif
	#endif //#ifdef CounterType

			
	//可控硅过零系统	
	#ifdef ZeroCrossType
		#if (ZeroCrossType==ZeroCrossType_Gpio) 
			#if(ZeroCrossTimer==2)
				zerocross_in_isr();//zerocross过零与可控硅驱动内联函数
			#endif //#if(ZeroCrossTimer==0)
		#endif
	#endif //#ifdef ZeroCrossType

	//按键系统
	#ifdef KeyType
		#if ((KeyType&KeyType_IR)==KeyType_IR)

		#endif
		
		#if ((KeyType&KeyType_RF)==KeyType_RF)
			__ZD_GetRfKeyValue();//射频遥控接收函数
		#endif					

		#if ((KeyType&KeyType_McuTouch)==KeyType_McuTouch)
			#if(McuTouchTimer==2)
				#if ((McuType&McuType_Mask)==McuType_CmsSemicon_CMS79F)
				__CMS_GetTouchKeyValue();//中微单片机触摸库函数,此函数放在中断,建议中断扫描时间 125us	
				#endif	
			#endif //#if(McuTouchTimer==0)		
		#endif //#if ((KeyType&KeyType_McuTouch)==KeyType_McuTouch)		
	#endif	//#ifdef KeyType	


	ZD_T2IF_CLEAN;	//清中断标志位
		
	}
#endif
	
	
	#ifdef RC0IF	
	if(RC0IF)
	{	
		
	}
	#endif
	
	#ifdef RC1IF
	if(RC1IF)
	{	

	}
	#endif
	
	#ifdef RCIF	
	if(RCIF)
	{
		if(FERR)
		{
			RCREG;							//帧错误
			return;
		}
		
		UART1_RxIsr((&ZD_UART1_RXBUF));//将接收缓冲区内容读出
		
		if(OERR)							//如果有溢出错误
		{
			CREN = 0;						//清零CREN位可将OERR位清零
			CREN = 1;						//再次将CREN置一，以允许继续接收
		}
		RCIF=0;
	}
	#endif
	
	#ifdef TXIF
	if(TXIF)
	{
		UART1_TxIsr((&ZD_UART1_TXBUF))
		TXIF=0;
	}

	#endif





/*

	if(INTF)
	{
		INTF = 0;			//清中断标志
	}
	if(RBIF)
	{
		RBIF = 0;			//清中断标志
	}
	*/
}


#elif (DevPlatform==DevPlatform_FMIDE)
unsigned char pageAuxTemp=0;
void interrupt ISR(void)
{   
pageAuxTemp=AUXPGE;
AUXPGE=0;
  //定时器0的中断处理**********************    
#ifdef Ft0Clk	
	if(ZD_T0IF_GRIGGER)
	{
		ZD_TIMER0_LOAD +=T0L_Reload;		//重新赋初值，在赋值前Timer0已有计数，故在该基础上加初值
        
	//定时器蜂鸣驱动-定义在TIMER0时	
	#ifdef BuzzerType	
		#if (BuzzerType==BuzzerType_TimerInv)
			#if(BuzzeTimer==0)
				buzzer_in_isr();
			#endif
		#endif
	#endif	//#ifdef BuzzerType	
	
	//定时器时间系统-定义在TIMER0时	
	#if (RtcType==RtcType_TimerSoftRtc) 
		#if(SoftRtcTimer==0)
		
			softrtc_in_isr();//RTC时钟内联函数
						
			#ifdef DisplayType
				#if ((DisplayType&DisplayType_SoftLed)==DisplayType_SoftLed) 
					#ifdef DisplayTypeSoftLedModel
						zd_softled_run();//软件LED驱动函数
					#endif
				#endif
			#endif //#ifdef DisplayType

			#ifdef CounterType
				#if (CounterType==CounterType_SoftCounter) 
					#ifdef Counter_IO_Channel1
					softcounter1_in_isr();//softcount1软件计数器内联函数
					#endif
				#endif
			#endif //#ifdef CounterType

					
					
			#ifdef ZeroCrossType
				#if (ZeroCrossType==ZeroCrossType_Gpio) 
					zerocross_in_isr();//zerocross过零与可控硅驱动内联函数
				#endif
			#endif //#ifdef ZeroCrossType

			#ifdef KeyType
				#if ((KeyType&KeyType_IR)==KeyType_IR)

				#endif
				
				#if ((KeyType&KeyType_RF)==KeyType_RF)
					__ZD_GetRfKeyValue();//射频遥控接收函数
				#endif					

				#if ((KeyType&KeyType_McuTouch)==KeyType_McuTouch)				
					#if (McuType==McuType_CmsSemicon_CMS79F738)
					__CMS_GetTouchKeyValue();//中微单片机触摸库函数,此函数放在中断,建议中断扫描时间 125us	
					#endif			
				#endif //#if ((KeyType&KeyType_McuTouch)==KeyType_McuTouch)		
			#endif	//#ifdef KeyType		
			T_1s_bit=0;
			T_500ms_bit=0;
		#endif //#if(SoftRtcTimer==0)
	#endif //#if (RtcType==RtcType_TimerSoftRtc) 
        
	ZD_T0IF_CLEAN;        

     }  
#endif	//#ifdef Ft0Clk

  //定时器1的中断处理**********************
	//if(TMR1IE && TMR1IF)
	//{

	//	ZD_T1IF_CLEAN;
	//} 	 
    
AUXPGE=pageAuxTemp;
} 

#elif (DevPlatform==DevPlatform_Keil_C51)


void timer0_Isr() interrupt 1
{
#ifdef Ft0Clk	

	//---------------------------------------
		#ifndef ZD_TIMER0_LOAD_RELOAD
			//ZD_TIMER0_LOAD += T0_Reload;		//重新赋初值，在赋值前Timer0已有计数，故在该基础上加初值
		#endif
	//---------------------------------------


	//定时器蜂鸣驱动
	#ifdef BuzzerType	
		#if (BuzzerType==BuzzerType_TimerInv)
			#if(BuzzeTimer==0)
				buzzer_in_isr();
			#endif
		#endif
	#endif	//#ifdef BuzzerType	

	//软件时钟系统
	#if (RtcType==RtcType_TimerSoftRtc) 
		#if(SoftRtcTimer==0)
			T_1s_bit=0;
			T_500ms_bit=0;
			softrtc_in_isr();//RTC时钟内联函数
		#endif //#if(SoftRtcTimer==0)
	#endif //#if (RtcType==RtcType_TimerSoftRtc) 

	//软件显示驱动			
	#ifdef DisplayType
		#if ((DisplayType&DisplayType_SoftLed)==DisplayType_SoftLed) 
			#ifdef DisplayTypeSoftLedModel
				#if(SoftLedTimer==0)
					zd_softled_run();//软件LED驱动函数
				#endif //#if(SoftLedTimer==0)
			#endif
		#endif
	#endif //#ifdef DisplayType

	//软件计数系统
	#ifdef CounterType
		#if (CounterType==CounterType_SoftCounter) 
			#if(SoftCounterTimer==0)
				#ifdef Counter_IO_Channel1
					softcounter1_in_isr();//softcount1软件计数器内联函数
					T_1s_bit=0;
					T_500ms_bit=0;
				#endif
			#endif //#if(SoftCounterTimer==0)
		#endif
	#endif //#ifdef CounterType

			
	//可控硅过零系统	
	#ifdef ZeroCrossType
		#if (ZeroCrossType==ZeroCrossType_Gpio) 
			#if(ZeroCrossTimer==0)
				zerocross_in_isr();//zerocross过零与可控硅驱动内联函数
			#endif //#if(ZeroCrossTimer==0)
		#endif
	#endif //#ifdef ZeroCrossType

	//按键系统
	#ifdef KeyType
		#if ((KeyType&KeyType_IR)==KeyType_IR)

		#endif
		
		#if ((KeyType&KeyType_RF)==KeyType_RF)
			__ZD_GetRfKeyValue();//射频遥控接收函数
		#endif					

		#if ((KeyType&KeyType_McuTouch)==KeyType_McuTouch)
			#if(McuTouchTimer==0)
				#if ((McuType&McuType_Mask)==McuType_CmsSemicon_CMS79F)
				//__CMS_GetTouchKeyValue();//中微单片机触摸库函数,此函数放在中断,建议中断扫描时间 125us	
				#endif	
			#endif //#if(McuTouchTimer==0)		
		#endif //#if ((KeyType&KeyType_McuTouch)==KeyType_McuTouch)		
	#endif	//#ifdef KeyType	

	ZD_T0IF_CLEAN;			//清中断标志位
	}
#endif	//#ifdef Ft0Clk

}

void timer1_Isr() interrupt 3
{

}

void timer2_Isr() interrupt 12
{
    //AUXINTIF &= ~T2IF; //清中断标志
}


void timer3_Isr() interrupt 19
{
  //AUXINTIF &= ~T3IF; //清中断标志

}

void timer4_Isr() interrupt 20
{
	//AUXINTIF &= ~T4IF; //清中断标志

}


#elif (DevPlatform==DevPlatform_Unkonw)


#endif






