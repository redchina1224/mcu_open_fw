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
#include "..\..\project.h"


extern void __CMS_GetTouchKeyValue(void);

bit T_1msCount_bit=0;

#if (BuzzerType==BuzzerType_TimerInv)
 unsigned char __buzzer_en=0;
 unsigned char *T_BuzzerEn=&__buzzer_en;
#endif

#ifdef RtcType
#if (RtcType==RtcType_TimerSoftRtc) 
 unsigned char T_125usCount=0;
 unsigned char __msCount=0;
 unsigned long __SecCount=Ft0Clk;
 unsigned char *T_msCount=&__msCount;
 unsigned long *T_SecCount=&__SecCount;
#endif
#endif


#ifdef CounterType
#if (CounterType==CounterType_SoftCounter) 

	#ifdef Counter_IO_Channel1
	bit __counter1_bit_status_ago;
  unsigned char __counter1_val=0;
  unsigned char __counter1filter=0;
  unsigned char __counter1_2_val=0; 
	unsigned char *T_Counter1_1sec=&__counter1_val;
	unsigned char *T_Counter1_250msec=&__counter1_2_val;
	
	#endif


#endif
#endif
 
 
 
#ifdef ZeroCrossType
	#if (ZeroCrossType==ZeroCrossType_Gpio) 
	bit zeroCrossError=0;
	bit __zerocross_bit_status_ago;
	bit triacOnEnable=0;
	unsigned char __zerocrossfilter=0;
	unsigned char zeroCrossPassCntMax;
	unsigned char zeroCrossPassCnt;
	unsigned char triacOn_CrossPass=40;

	#endif
#endif 
 
 
 
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


//��ƽ̨����������Ӧͷ�ļ�
#if ((DevPlatform==DevPlatform_CMSIDE_CASD))
	
void interrupt interrupt_Isr()
{
#ifdef Ft0Clk	
	if(ZD_T0IF_GRIGGER)
	{
	//---------------------------------------
		#ifndef ZD_TIMER0_LOAD_RELOAD
			ZD_TIMER0_LOAD += T0_Reload;		//���¸���ֵ���ڸ�ֵǰTimer0���м��������ڸû����ϼӳ�ֵ
		#endif
	//---------------------------------------

	//��ʱ��ʱ��ϵͳ-������TIMER0ʱ	
	#if (RtcType==RtcType_TimerSoftRtc) 
		#if(SoftRtcTimer==0)
			if(++T_125usCount>=80) 
			{ 
				T_125usCount=0; 
				if(++(*T_msCount)>=100) 
				{
					(*T_msCount)=0;
					(*T_SecCount)++;
					
					
				#ifdef CounterType
					#if (CounterType==CounterType_SoftCounter) 

						#ifdef Counter_IO_Channel1
						(*T_Counter1_1sec)=__counter1_val; __counter1_val=0;
						#endif

					#endif
				#endif

				}
				
				if((*T_msCount)%25==0)
				{
					(*T_Counter1_250msec)=__counter1_2_val; __counter1_2_val=0;
				}  
			}
			
			
			if(T_125usCount%8==0) T_1msCount_bit=1;
			
			
			#ifdef DisplayType
				#if (DisplayType==DisplayType_Dig8SoftLed) 
				zd_softled_run();
				#endif
			#endif

			#ifdef CounterType
				#if (CounterType==CounterType_SoftCounter) 

					#ifdef Counter_IO_Channel1
					if(Counter_IO_Channel1==0)
					{
						if(__counter1filter<20) __counter1filter++;
						else
						{
							if(__counter1_bit_status_ago==1)
							{
									 if(__counter1_val<250)	__counter1_val++;
									 if(__counter1_2_val<250) __counter1_2_val++;
								__counter1_bit_status_ago=0;
							}
						}
					}
					else
					{
						if(__counter1filter>0) __counter1filter--;
						else
						{
							
							__counter1_bit_status_ago=1;
						}
					}
					
					

					#endif


				#endif
			#endif

					
					
			#ifdef ZeroCrossType
				#if (ZeroCrossType==ZeroCrossType_Gpio) 

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
				
				
				if(__zerocross_bit_status_ago!=ZeroCross_IO_Channel)
				{
					if(0==__zerocross_bit_status_ago)
					{
						zeroCrossPassCntMax=zeroCrossPassCnt;
						zeroCrossPassCnt=0;
						Triac_IO_Ctrl(Triac_IO_OFF);
					}
					__zerocross_bit_status_ago=ZeroCross_IO_Channel;
				}
				else
				{
				if(zeroCrossPassCnt<150) zeroCrossPassCnt++; else zeroCrossError=1;
				//�ɿع����
				if(triacOnEnable==1&&zeroCrossPassCnt>triacOn_CrossPass)
					Triac_IO_Ctrl(Triac_IO_ON);
				}
				

					

				#endif
			#endif
				
					
			#if (McuType==McuType_CmsSemicon_CMS79F623)
			__CMS_GetTouchKeyValue();//�˺��������жϣ������ж�ɨ��ʱ�� 125us	
			#endif			
			
			
		#endif
	#endif
			

	//��ʱ����������-������TIMER0ʱ		
	#if (BuzzerType==BuzzerType_TimerInv)
		#if(BuzzeTimer==0)
			if((*T_BuzzerEn)!=0) Buzzer_IO_Channel=!Buzzer_IO_Channel; else Buzzer_IO_Ctrl(Buzzer_IO_OFF);
			//Buzzer_IO_Channel=!Buzzer_IO_Channel;
		#endif
	#endif

	
		ZD_T0IF_CLEAN;			//���жϱ�־λ
	}
#endif	
	

#ifdef Ft1Clk	
	if(TMR1IF)
	{
	//---------------------------------------
		TMR1L += T1L_Reload;
		TMR1H += T1H_Reload;			//���¸���ֵ���ڸ�ֵǰTimer1���м��������ڸû����ϼӳ�ֵ
								//�ڽ����жϵȹ�������ʵTime��һֱ�ڼ�����
	//---------------------------------------	
		
	
	//��ʱ��ʱ��ϵͳ-������TIMER1ʱ	
	#if (RtcType==RtcType_TimerSoftRtc) 
		#if(SoftRtcTimer==1)
			if(++T_125usCount>=80) 
			{ 
				T_125usCount=0; 
				if(++(*T_msCount)>=100) {(*T_msCount)=0;(*T_SecCount)++;}  
			}
			#ifdef DisplayType
				#if (DisplayType==DisplayType_Dig8SoftLed) 
				zd_softled_run();
				#endif
			#endif
		#endif
	#endif
		
	//��ʱ����������-������TIMER1ʱ		
	#if (BuzzerType==BuzzerType_TimerInv)
		#if(BuzzeTimer==1)
			if((*T_BuzzerEn)!=0) Buzzer_IO_Channel=!Buzzer_IO_Channel; else Buzzer_IO_Ctrl(Buzzer_IO_OFF);
		#endif
	#endif
	TMR1IF = 0;				//���жϱ�־λ
	}
#endif


#ifdef Ft2Clk	
	if(TMR2IF)
	{
	//��ʱ��ʱ��ϵͳ-������TIMER2ʱ	
	#if (RtcType==RtcType_TimerSoftRtc) 
		#if(SoftRtcTimer==2)
			if(++T_125usCount>=80) 
			{ 
				T_125usCount=0; 
				if(++(*T_msCount)>=100) {(*T_msCount)=0;(*T_SecCount)++;}  
			}
			#ifdef DisplayType
				#if (DisplayType==DisplayType_Dig8SoftLed) 
				zd_softled_run();
				#endif
			#endif
		#endif
	#endif
		
	//��ʱ����������-������TIMER2ʱ		
	#if (BuzzerType==BuzzerType_TimerInv)
		#if(BuzzeTimer==2)
			if((*T_BuzzerEn)!=0) Buzzer_IO_Channel=!Buzzer_IO_Channel; else Buzzer_IO_Ctrl(Buzzer_IO_OFF);
		#endif
	#endif
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







	if(INTF)
	{
		INTF = 0;			//���жϱ�־
	}
	if(RBIF)
	{
		RBIF = 0;			//���жϱ�־
	}
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

	//��ʱ��ʱ��ϵͳ-������TIMER0ʱ	
	#if (RtcType==RtcType_TimerSoftRtc) 
		#if(SoftRtcTimer==0)
			if(++T_125usCount>=80) 
			{ 
				T_125usCount=0; 
				if(++(*T_msCount)>=100) 
				{
					(*T_msCount)=0;
					(*T_SecCount)++;
					
					
					#ifdef CounterType
					#if (CounterType==CounterType_SoftCounter) 

						#ifdef Counter_IO_Channel1
						(*T_Counter1_1sec)=__counter1_val; __counter1_val=0;
						#endif

					#endif
				#endif

				}  
			}
			#ifdef DisplayType
				#if (DisplayType==DisplayType_Dig8SoftLed) 
				zd_softled_run();
				#endif
			#endif

			#ifdef CounterType
				#if (CounterType==CounterType_SoftCounter) 

					#ifdef Counter_IO_Channel1
					if(__counter1_bit_status_ago!=Counter_IO_Channel1)
					{
						if(0==__counter1_bit_status_ago&&__counter1_val<250) __counter1_val++;
						__counter1_bit_status_ago=Counter_IO_Channel1;
					}
					#endif


				#endif
			#endif

					
					
			#ifdef ZeroCrossType
				#if (ZeroCrossType==ZeroCrossType_Gpio) 

				//������������
				if(__zerocross_bit_status_ago!=ZeroCross_IO_Channel)
				{
					if(0==__zerocross_bit_status_ago)
					{
						zeroCrossPassCntMax=zeroCrossPassCnt;
						zeroCrossPassCnt=0;
						//Triac_IO_Ctrl(Triac_IO_OFF);
					}
					__zerocross_bit_status_ago=ZeroCross_IO_Channel;
				}
				else
				{
				if(zeroCrossPassCnt<250) zeroCrossPassCnt++; else zeroCrossError=1;
				//�ɿع����
				//if(triacOnEnable==1&&zeroCrossPassCnt>triacOn_CrossPass)
					//Triac_IO_Ctrl(Triac_IO_ON);
				}

					

				#endif
			#endif
				
				
			
		#endif
	#endif
			

	//��ʱ����������-������TIMER0ʱ		
	#if (BuzzerType==BuzzerType_TimerInv)
		#if(BuzzeTimer==0)
			if((*T_BuzzerEn)!=0) Buzzer_IO_Channel=!Buzzer_IO_Channel; else Buzzer_IO_Ctrl(Buzzer_IO_OFF);
			//Buzzer_IO_Channel=!Buzzer_IO_Channel;
		#endif
	#endif

	
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




