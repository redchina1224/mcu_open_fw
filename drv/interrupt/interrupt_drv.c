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

#ifdef Uart0_Type
unsigned char * Uart0_TxBuff_P;
unsigned char * Uart0_RxBuff_P;

unsigned char Uart0_Comm_TimeOut_x10msec=0;
unsigned char Uart0_Recv_Byte_Length=0;
unsigned char Uart0_Recv_Over_Checking=0;

unsigned char Uart0_Sended_Byte_Length=0;
unsigned char Uart0_NeedSend_Byte_Length=0;
unsigned char Uart0_Send_Busy=0;

#endif

#ifdef Uart1_Type
unsigned char * Uart1_TxBuff_P;
unsigned char * Uart1_RxBuff_P;

unsigned char Uart1_Comm_TimeOut_x10msec=0;
unsigned char Uart1_Recv_Byte_Length=0;
unsigned char Uart1_Recv_Over_Checking=0;

unsigned char Uart1_Sended_Byte_Length=0;
unsigned char Uart1_NeedSend_Byte_Length=0;
unsigned char Uart1_Send_Busy=0;

#endif

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




//嵌入基础时基内联函数
#ifdef BaseTimeType
	#include "..\basetime\coretimer\basetime_coretimer_isr_include.c"
#endif

//嵌入实时时钟内联函数
#ifdef RtcType
	#include "..\rtc\softrtc\softrtc_coretimer_isr_include.c"
#endif

//嵌入软件蜂鸣发生器内联函数
#ifdef BuzzerType
#if (BuzzerType==BuzzerType_TimerInv)
	#include "..\buzzer\buzzer\buzzer_timerinv_isr_include.c"
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
			if(__counter1filter<5) __counter1filter++;
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


#ifdef Counter_IO_Channel2
bit __counter2_bit_status_ago;
unsigned int __counter2_val=0;
unsigned char __counter2filter=0;
unsigned int *T_Counter2_1sec=&__counter2_val;
unsigned int *T_Counter2_Total=&__counter2_val;

void softcounter2_reset(void)
{
	ZD_GIE_DISABLE;
	(*T_Counter2_1sec)=0;
	(*T_Counter2_Total)=0;
	ZD_GIE_ENABLE;
}

#if (DevPlatform==DevPlatform_Keil_C51)
void softcounter2_in_isr(void)
#else
inline void softcounter2_in_isr(void)
#endif
{
		if(T_500ms_bit)//半秒周期,上升沿与下降沿都累加，所得累加值等同于1秒的值
		{
			(*T_Counter2_1sec)=__counter2_val; 
			(*T_Counter2_Total)+=__counter2_val;
			__counter2_val=0;
		}

		if(Counter_IO_Channel2==0)
		{
			if(__counter2filter<5) __counter2filter++;
			else
			{
				if(__counter2_bit_status_ago==1)//下降沿
				{
					if(__counter2_val<64999)	__counter2_val++;
					__counter2_bit_status_ago=0;
				}
			}
		}
		else
		{
			if(__counter2filter>0) __counter2filter--;
			else
			{ 
				if(__counter2_bit_status_ago==0)//上升沿
				{
					if(__counter2_val<64999)	__counter2_val++;
					__counter2_bit_status_ago=1;
				}
			}
		}
}

#endif //#ifdef Counter_IO_Channel2


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
			//zeroCrossPassCntMax=zeroCrossPassCnt;
			zeroCrossPassCnt=0;
			Triac_IO_Ctrl(Triac_IO_OFF);
			
			__zerocross_bit_status_ago=1;
		}
		else
		{
			zeroCrossPassCntMax=zeroCrossPassCnt;
			zeroCrossPassCnt=6;
			Triac_IO_Ctrl(Triac_IO_OFF);
			
			__zerocross_bit_status_ago=0;
		}
	}

	//可控硅控制
	if(triacOnEnable==1&&zeroCrossPassCnt>triacOn_CrossPass&&zeroCrossPassCnt<(triacOn_CrossPass+10))
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

	//定时器蜂鸣驱动
	#ifdef BuzzerType	
		#if (BuzzerType==BuzzerType_TimerInv)
			#if(BuzzeTimer==0)
				buzzer_in_isr();
			#endif
		#endif
	#endif	//#ifdef BuzzerType	


	//软件时基系统
	#if (BaseTimeType==BaseTimeType_CoreTimer) 
		#if(BaseTime_CoreTimer==0)
			basetime_in_isr();//时基内联函数
		#endif //#if(BaseTime_CoreTimer==0)
	#endif //#if (BaseTimeType==BaseTimeType_CoreTimer) 
	
	
	//软件时钟系统
	#if (RtcType==RtcType_TimerSoftRtc) 
		#if(SoftRtcTimer==0)
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
		
		#if ((DisplayType&DisplayType_SoftLcd)==DisplayType_SoftLcd) 
			#ifdef DisplayTypeSoftLcdModel
				#if(SoftLcdTimer==0)
					zd_softlcd_run();//软件LCD驱动函数
				#endif //#if(SoftLcdTimer==0)
			#endif
		#endif
		
	#endif //#ifdef DisplayType

	//软件计数系统
	#ifdef CounterType
		#if (CounterType==CounterType_SoftCounter) 
			#if(SoftCounterTimer==0)
			
				#ifdef Counter_IO_Channel1
					softcounter1_in_isr();//softcount1软件计数器内联函数
				#endif
				
				#ifdef Counter_IO_Channel2
					softcounter2_in_isr();//softcount2软件计数器内联函数
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
	

#ifdef Ft1Clk	
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
#endif


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

	//软件时基系统
	#if (BaseTimeType==BaseTimeType_CoreTimer) 
		#if(BaseTime_CoreTimer==2)
			basetime_in_isr();//时基内联函数
		#endif //#if(BaseTime_CoreTimer==0)
	#endif //#if (BaseTimeType==BaseTimeType_CoreTimer) 
	
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
	
#ifdef Uart0_Type
	if(TX0IE&&TX0IF)
	{
		if(++Uart0_Sended_Byte_Length<Uart0_NeedSend_Byte_Length)
		{
			if(Uart0_Sended_Byte_Length<=(Uart0_SendBuffLength-1)) { TXREG0=Uart0_TxBuff_P[Uart0_Sended_Byte_Length]; }
		}
		else
		{
			Uart0_Send_Busy=0;
			Uart0_NeedSend_Byte_Length=0;
			TX0IE=0;
		}
	}
	
	if(RC0IF)
	{	
		if(Uart0_Recv_Over_Checking==0)//前次接收未处理完成时,不再接收接数据,以保护数据缓存
		{
			if(Uart0_Comm_TimeOut_x10msec==0||Uart0_RxBuff_P[0]!=ModebusSlaveDeviceID ) Uart0_Recv_Byte_Length=0;//超时或者设备地址不匹配时，从头开始接收
			if(Uart0_Recv_Byte_Length<(Uart0_RecvBuffLength-1)) { Uart0_RxBuff_P[Uart0_Recv_Byte_Length] = RCREG0; Uart0_Recv_Byte_Length++; } //接收数据,超过缓冲区长度后不再接收
			Uart0_Comm_TimeOut_x10msec=Uart0RecvTimeOut10ms; //重设接收超时时间
		}
		else
		{
			 RCREG0;
		}
	}
#endif

#ifdef Uart1_Type
	if(TX1IE&&TX1IF)
	{
		if(++Uart1_Sended_Byte_Length<Uart1_NeedSend_Byte_Length)
		{
			if(Uart1_Sended_Byte_Length<=(Uart1_SendBuffLength-1)) { TXREG1=Uart1_TxBuff_P[Uart1_Sended_Byte_Length]; }
		}
		else
		{
			Uart1_Send_Busy=0;
			Uart1_NeedSend_Byte_Length=0;
			TX1IE=0;
		}
	}
	
	if(RC1IF)
	{	
		if(Uart1_Recv_Over_Checking==0)//前次接收未处理完成时,不再接收接数据,以保护数据缓存
		{
			if(Uart1_Comm_TimeOut_x10msec==0||Uart1_RxBuff_P[0]!=ModebusSlaveDeviceID ) Uart1_Recv_Byte_Length=0;//超时或者设备地址不匹配时，从头开始接收
			if(Uart1_Recv_Byte_Length<(Uart1_RecvBuffLength-1)) { Uart1_RxBuff_P[Uart1_Recv_Byte_Length] = RCREG1; Uart1_Recv_Byte_Length++; } //接收数据,超过缓冲区长度后不再接收
			Uart1_Comm_TimeOut_x10msec=Uart1RecvTimeOut10ms; //重设接收超时时间
		}
		else
		{
			 RCREG1;
		}
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



	ZD_T0IF_CLEAN;			//清中断标志位

#endif	//#ifdef Ft0Clk

}

void timer1_Isr() interrupt 3
{

}

void timer2_Isr() interrupt 5
{
#ifdef Ft2Clk	
	if(MOF_T2IF_GRIGGER)
	{
		//通讯系统
		comm_handle();
		
		//软件时基系统
		#if (BaseTimeType==BaseTimeType_CoreTimer) 
			#if(BaseTime_CoreTimer==2)
				basetime_in_isr();//时基内联函数
			#endif //#if(BaseTime_CoreTimer==0)
		#endif //#if (BaseTimeType==BaseTimeType_CoreTimer) 
/*
		//步进电机脉冲输出
		if(++step_isr_count>step_motor_rate)
		{
			step_motor_pulse();
			step_isr_count=0;
		}
*/
	MOF_T2IF_CLEAN;	//清中断标志位
		
	}
#endif
	
	if(T2MOD & BIT5)		  //定时器2重载中断
	{
		T2MOD |= BIT5;
		
	}
}


void timer3_Isr() interrupt 19
{
  //AUXINTIF &= ~T3IF; //清中断标志

}

void timer4_Isr() interrupt 20
{
	//AUXINTIF &= ~T4IF; //清中断标志

}


void UART1_ISR (void) interrupt 6	
{
	if(MOF_UART1_RXIF_GRIGGER)
	{
		MOF_UART1_RXIF_CLEAN;			 

		#if ((CommunicationType&CommunicationType_Uart)==CommunicationType_Uart)
		
			#if((CommunicationTypeUartModel&CommunicationType_Uart_HaierUplus)==CommunicationType_Uart_HaierUplus)
				#if (UART_UPLUS_PORT_NUM==1)
					uart_haier_uplus_rx_in_isr();
				#endif
			#elif ((CommunicationTypeUartModel&CommunicationType_Uart_FixedLength)==CommunicationType_Uart_FixedLength)
				#if (UART_FIXED_LENGTH_PORT_NUM==1)
					uart_fixed_length_rx_in_isr();
				#endif
			#endif
		
		#endif
	}
	
	
	if(MOF_UART1_TXIF_GRIGGER)
	{
		MOF_UART1_TXIF_CLEAN;	

		#if ((CommunicationType&CommunicationType_Uart)==CommunicationType_Uart)
		
			#if((CommunicationTypeUartModel&CommunicationType_Uart_HaierUplus)==CommunicationType_Uart_HaierUplus)
				#if (UART_UPLUS_PORT_NUM==1)
					uart_haier_uplus_tx_in_isr();
				#endif
			#elif ((CommunicationTypeUartModel&CommunicationType_Uart_FixedLength)==CommunicationType_Uart_FixedLength)
				#if (UART_FIXED_LENGTH_PORT_NUM==1)
					uart_fixed_length_tx_in_isr();
				#endif
			#endif
		
		#endif
	}
}


#elif (DevPlatform==DevPlatform_Unkonw)


#endif






