 //******************************************************************************
//Copyright(C) 2020-2021 Zhejiang Zhida Electronic Technology Co., Ltd
//�㽭�Ǵ���ӿƼ����޹�˾
//File name:      interrupt_core.c
//Author:         zzg
//Version:        Ver0.1
//Date:           2021-4-25
//Description:    �жϷ�����򼯺�(�������жϷ�����ص�ͳһ��������)
//History:
//******************************************************************************
#include "..\com_include_drv.h"

//extern void __CMS_GetTouchKeyValue(void);





#ifdef Ft0Clk
 unsigned char T0_Reload;
#endif

#ifdef Ft1Clk
 unsigned char T1L_Reload;
 unsigned char T1H_Reload;
#endif

#ifdef Ft2Clk
 unsigned char T2L_Reload;
 unsigned char T2H_Reload;
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
inline void powerofflvd_in_isr(void)
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


//void buzzer_in_isr(void);
inline void buzzer_in_isr(void)
{
	if((*T_BuzzerEn)!=0) Buzzer_IO_Channel=!Buzzer_IO_Channel;// else Buzzer_IO_Ctrl(Buzzer_IO_OFF);
	//Buzzer_IO_Channel=!Buzzer_IO_Channel;
}

#endif
#endif


#ifdef RtcType
#if (RtcType==RtcType_TimerSoftRtc) 

bit T_500ms_bit=0;
bit T_1s_bit=0;

bit M_10ms_bit=0;
bit M_50ms_bit=0;
bit M_100ms_bit=0;
bit M_1s_bit=0;

 unsigned char __125usCount=0;
 unsigned char __10msCount=0;
 unsigned char __100msCount=0; 
 //unsigned long __SecCount=0;
 //unsigned long *T_SecCount=&__SecCount;


//void softrtc_in_isr(void);
inline void softrtc_in_isr(void)
{
	if(++__125usCount>=80) 
	{ 
		__125usCount=0; 
		M_10ms_bit=1;
		if(++__10msCount>=10) 
		{
			__10msCount=0;
			
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
		else if(__10msCount==5)
			M_50ms_bit=1;

	}
	//else if(T_125usCount==40)
	//	M_5ms_bit=1;
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

//void softcounter1_in_isr(void);
inline void softcounter1_in_isr(void)
{
		if(T_500ms_bit)//��������,���������½��ض��ۼӣ������ۼ�ֵ��ͬ��1���ֵ
		{
			(*T_Counter1_1sec)=__counter1_val; 
			(*T_Counter1_Total)+=__counter1_val;
			__counter1_val=0;
		}

		if(Counter_IO_Channel1==0)
		{
			if(__counter1filter<20) __counter1filter++;
			else
			{
				if(__counter1_bit_status_ago==1)//�½���
				{
					if(__counter1_val<60000)	__counter1_val++;
					__counter1_bit_status_ago=0;
				}
			}
		}
		else
		{
			if(__counter1filter>0) __counter1filter--;
			else
			{ 
				if(__counter1_bit_status_ago==0)//������
				{
					if(__counter1_val<60000)	__counter1_val++;
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


//void zerocross_in_isr(void);
inline void zerocross_in_isr(void)
{
	//������������
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
			//�ɿع����
			//if(triacOnEnable==1&&zeroCrossPassCnt>triacOn_CrossPass)
			//Triac_IO_Ctrl(Triac_IO_ON);
			__zerocross_bit_status_ago=1;
		}
	}
	
	*/
	
	//������ 100HZ--zeroCrossPassCnt���ֵΪ80
	if(zeroCrossPassCnt<200) zeroCrossPassCnt++; else { zeroCrossError=1; zeroCrossPassCnt=0;}
	
	if(__zerocross_bit_status_ago!=ZeroCross_IO_Channel)
	{
		if(0==__zerocross_bit_status_ago)
		{
			//if(++__zerocrossfilter>4)
			{
				zeroCrossPassCntMax=zeroCrossPassCnt;
				zeroCrossPassCnt=0;
				Triac_IO_Ctrl(Triac_IO_OFF);
				__zerocross_bit_status_ago=1;
				//__zerocrossfilter=0;
			}
		}
		else
		{
			__zerocross_bit_status_ago=0;
			//__zerocrossfilter=0;
		}
	}

	//�ɿع����
	if(triacOnEnable==1)
	{
		if(zeroCrossPassCnt>triacOn_CrossPass)
		{
			Triac_IO_Ctrl(Triac_IO_ON);
		}
	}
	else
		Triac_IO_Ctrl(Triac_IO_OFF);

}

	#endif
#endif 

			
			
//��ƽ̨����������Ӧͷ�ļ�
#if ((DevPlatform==DevPlatform_CMSIDE_CASD))
	
void interrupt interrupt_Isr()
{
#ifdef PowerOffCheckType
#if (PowerOffCheckType==PowerOffCheckType_MCULVD)
	if(ZD_LVDIF_GRIGGER)
	{
		powerofflvd_in_isr();
		ZD_LVDIF_CLEAN;	//���жϱ�־λ
	}	
#endif
#endif


	
#ifdef Ft0Clk	
	if(ZD_T0IF_GRIGGER)
	{
	//---------------------------------------
		#ifndef ZD_TIMER0_LOAD_RELOAD
			ZD_TIMER0_LOAD += T0_Reload;		//���¸���ֵ���ڸ�ֵǰTimer0���м��������ڸû����ϼӳ�ֵ
		#endif
	//---------------------------------------


	//��ʱ����������-������TIMER0ʱ	
	#ifdef BuzzerType	
		#if (BuzzerType==BuzzerType_TimerInv)
			#if(BuzzeTimer==0)
				buzzer_in_isr();
			#endif
		#endif
	#endif	//#ifdef BuzzerType	
	
	//��ʱ��ʱ��ϵͳ-������TIMER0ʱ	
	#if (RtcType==RtcType_TimerSoftRtc) 
		#if(SoftRtcTimer==0)

			softrtc_in_isr();//RTCʱ����������
						
			#ifdef DisplayType
				#if ((DisplayType&DisplayType_SoftLed)==DisplayType_SoftLed) 
					#ifdef DisplayTypeSoftLedModel
						zd_softled_run();//���LED��������
					#endif
				#endif
			#endif //#ifdef DisplayType

			#ifdef CounterType
				#if (CounterType==CounterType_SoftCounter) 
					#ifdef Counter_IO_Channel1
					softcounter1_in_isr();//softcount1�����������������
					#endif
				#endif
			#endif //#ifdef CounterType

					
					
			#ifdef ZeroCrossType
				#if (ZeroCrossType==ZeroCrossType_Gpio) 
					zerocross_in_isr();//zerocross������ɿع�������������
				#endif
			#endif //#ifdef ZeroCrossType

			#ifdef KeyType
				#if ((KeyType&KeyType_IR)==KeyType_IR)

				#endif
				
				#if ((KeyType&KeyType_RF)==KeyType_RF)
					__ZD_GetRfKeyValue();//��Ƶң�ؽ��պ���
				#endif					

				#if ((KeyType&KeyType_McuTouch)==KeyType_McuTouch)				
					#if (McuType==McuType_CmsSemicon_CMS79F738)
					__CMS_GetTouchKeyValue();//��΢��Ƭ�������⺯��,�˺��������ж�,�����ж�ɨ��ʱ�� 125us	
					#endif			
				#endif //#if ((KeyType&KeyType_McuTouch)==KeyType_McuTouch)		
			#endif	//#ifdef KeyType		
			T_1s_bit=0;
			T_500ms_bit=0;
		#endif //#if(SoftRtcTimer==0)
	#endif //#if (RtcType==RtcType_TimerSoftRtc) 
			



	
		ZD_T0IF_CLEAN;			//���жϱ�־λ
	}
#endif	//#ifdef Ft0Clk
	

#ifdef Ft1Clk	
	if(TMR1IF)
	{
	//---------------------------------------
		TMR1L += T1L_Reload;
		TMR1H += T1H_Reload;			//���¸���ֵ���ڸ�ֵǰTimer1���м��������ڸû����ϼӳ�ֵ
								//�ڽ����жϵȹ�������ʵTime��һֱ�ڼ�����
	//---------------------------------------	
		
	

	TMR1IF = 0;				//���жϱ�־λ
	}
#endif


#ifdef Ft2Clk	
	if(TMR2IF)
	{




	TMR2IF = 0;	//���жϱ�־λ
		
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
			RCREG;							//֡����
			return;
		}
		
		UART1_RxIsr((&ZD_UART1_RXBUF));//�����ջ��������ݶ���
		
		if(OERR)							//������������
		{
			CREN = 0;						//����CRENλ�ɽ�OERRλ����
			CREN = 1;						//�ٴν�CREN��һ���������������
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
		INTF = 0;			//���жϱ�־
	}
	if(RBIF)
	{
		RBIF = 0;			//���жϱ�־
	}
	*/
}


#elif (DevPlatform==DevPlatform_FMIDE)
void interrupt ISR(void)
{ 
  //��ʱ��0���жϴ���**********************    
#ifdef Ft0Clk	
	if(ZD_T0IF_GRIGGER)
	{
	ZD_TIMER0_LOAD +=T0_Reload;		//���¸���ֵ���ڸ�ֵǰTimer0���м��������ڸû����ϼӳ�ֵ
        
	//��ʱ����������-������TIMER0ʱ	
	#ifdef BuzzerType	
		#if (BuzzerType==BuzzerType_TimerInv)
			#if(BuzzeTimer==0)
				buzzer_in_isr();
			#endif
		#endif
	#endif	//#ifdef BuzzerType	
	
	//��ʱ��ʱ��ϵͳ-������TIMER0ʱ	
	#if (RtcType==RtcType_TimerSoftRtc) 
		#if(SoftRtcTimer==0)
		
			softrtc_in_isr();//RTCʱ����������
						
			#ifdef DisplayType
				#if ((DisplayType&DisplayType_SoftLed)==DisplayType_SoftLed) 
					#ifdef DisplayTypeSoftLedModel
						zd_softled_run();//���LED��������
					#endif
				#endif
			#endif //#ifdef DisplayType

			#ifdef CounterType
				#if (CounterType==CounterType_SoftCounter) 
					#ifdef Counter_IO_Channel1
					softcounter1_in_isr();//softcount1�����������������
					#endif
				#endif
			#endif //#ifdef CounterType

					
					
			#ifdef ZeroCrossType
				#if (ZeroCrossType==ZeroCrossType_Gpio) 
					zerocross_in_isr();//zerocross������ɿع�������������
				#endif
			#endif //#ifdef ZeroCrossType

			#ifdef KeyType
				#if ((KeyType&KeyType_IR)==KeyType_IR)

				#endif
				
				#if ((KeyType&KeyType_RF)==KeyType_RF)
					__ZD_GetRfKeyValue();//��Ƶң�ؽ��պ���
				#endif					

				#if ((KeyType&KeyType_McuTouch)==KeyType_McuTouch)				
					#if (McuType==McuType_CmsSemicon_CMS79F738)
					__CMS_GetTouchKeyValue();//��΢��Ƭ�������⺯��,�˺��������ж�,�����ж�ɨ��ʱ�� 125us	
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

  //��ʱ��1���жϴ���**********************
	//if(TMR1IE && TMR1IF)
	//{

	//	ZD_T1IF_CLEAN;
	//} 	 
    
} 

#elif (DevPlatform==DevPlatform_Keil_C51)


void timer0_Isr() interrupt 1
{
#ifdef Ft0Clk	

	//---------------------------------------
		#ifndef ZD_TIMER0_LOAD_RELOAD
			ZD_TIMER0_LOAD += T0_Reload;		//���¸���ֵ���ڸ�ֵǰTimer0���м��������ڸû����ϼӳ�ֵ
		#endif
	//---------------------------------------

	//��ʱ����������-������TIMER0ʱ	
	#ifdef BuzzerType	
		#if (BuzzerType==BuzzerType_TimerInv)
			#if(BuzzeTimer==0)
				buzzer_in_isr();
			#endif
		#endif
	#endif	//#ifdef BuzzerType	
	
	//��ʱ��ʱ��ϵͳ-������TIMER0ʱ	
	#if (RtcType==RtcType_TimerSoftRtc) 
		#if(SoftRtcTimer==0)
		
			softrtc_in_isr();//RTCʱ����������
						
			#ifdef DisplayType
				#if (DisplayType==DisplayType_Dig8SoftLed) 
				zd_softled_run();//���LED��������
				#endif
			#endif //#ifdef DisplayType

			#ifdef CounterType
				#if (CounterType==CounterType_SoftCounter) 
					#ifdef Counter_IO_Channel1
					softcounter1_in_isr();//softcount1�����������������
					#endif
				#endif
			#endif //#ifdef CounterType

					
					
			#ifdef ZeroCrossType
				#if (ZeroCrossType==ZeroCrossType_Gpio) 
					zerocross_in_isr();//zerocross������ɿع�������������
				#endif
			#endif //#ifdef ZeroCrossType

			#ifdef KeyType
				#if ((KeyType&KeyType_IR)==KeyType_IR)

				#endif
				
				#if ((KeyType&KeyType_RF)==KeyType_RF)
					__ZD_GetRfKeyValue();//��Ƶң�ؽ��պ���
				#endif					

				#if ((KeyType&KeyType_McuTouch)==KeyType_McuTouch)				

				#endif //#if ((KeyType&KeyType_McuTouch)==KeyType_McuTouch)		
			#endif	//#ifdef KeyType		
			T_1s_bit=0;
		#endif //#if(SoftRtcTimer==0)
	#endif //#if (RtcType==RtcType_TimerSoftRtc) 

	
		ZD_T0IF_CLEAN;			//���жϱ�־λ

#endif	
}

void timer1_Isr() interrupt 3
{

}

void timer2_Isr() interrupt 12
{
    //AUXINTIF &= ~T2IF; //���жϱ�־
}


void timer3_Isr() interrupt 19
{
  //AUXINTIF &= ~T3IF; //���жϱ�־

}

void timer4_Isr() interrupt 20
{
	//AUXINTIF &= ~T4IF; //���жϱ�־

}


#elif (DevPlatform==DevPlatform_Unkonw)


#endif






