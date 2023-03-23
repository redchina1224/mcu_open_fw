#ifdef BaseTimeType
#if (BaseTimeType==BaseTimeType_CoreTimer) 

bit T_500ms_bit=0;
bit T_1s_bit=0;

//bit M_1s_bit=0;
#if(BaseTimeTargetUs==10000)
bit M_10ms_bit=0;
#elif(BaseTimeTargetUs==20000)
bit M_20ms_bit=0;
#endif

unsigned char __basetimeIsrCount=0;
unsigned char __msCount=0;


#if (DevPlatform==DevPlatform_Keil_C51)
void basetime_in_isr(void)
#else
inline void basetime_in_isr(void)
#endif
{

T_500ms_bit=0;
T_1s_bit=0;

#ifdef BaseTimeCoreTimerBaseUs
#if (BaseTimeCoreTimerBaseUs<BaseTimeTargetUs)
	if(++__basetimeIsrCount>=(BaseTimeTargetUs/BaseTimeCoreTimerBaseUs)) 
	{ 
		__basetimeIsrCount=0; 
#endif
#endif

#if(BaseTimeTargetUs==10000)
M_10ms_bit=1;
#elif(BaseTimeTargetUs==20000)
M_20ms_bit=1;
#endif
		if(++__msCount>=(1000000/BaseTimeTargetUs)) 
		{
			__msCount=0;

			//M_1s_bit=1;

			T_1s_bit=1;
			T_500ms_bit=1;
		}
		else if(__msCount==(500000/BaseTimeTargetUs))
		{
			T_500ms_bit=1;
		}
#ifdef BaseTimeCoreTimerBaseUs
#if (BaseTimeCoreTimerBaseUs<BaseTimeTargetUs)
	}
#endif
#endif
T_500ms_bit=1;
}



#endif
#endif