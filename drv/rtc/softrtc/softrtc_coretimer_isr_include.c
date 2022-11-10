#ifdef RtcType
#if (RtcType==RtcType_TimerSoftRtc) 

bit R_500ms_bit=0;
bit R_1s_bit=0;

unsigned char __softrtcIsrCount=0;

unsigned char __softrtc_msCount=0;

#if (DevPlatform==DevPlatform_Keil_C51)
void softrtc_in_isr(void)
#else
inline void softrtc_in_isr(void)
#endif
{
#ifdef SoftRtcCoreTimerBaseUs
#if (SoftRtcCoreTimerBaseUs<SoftRtcTargetUs)
	if(++__softrtcIsrCount>=(SoftRtcTargetUs/SoftRtcCoreTimerBaseUs)) 
	{ 
		__softrtcIsrCount=0; 

		if(++__softrtc_msCount>=(1000000/SoftRtcTargetUs)) 
		{
			__softrtc_msCount=0;

			R_1s_bit=1;
			R_500ms_bit=1;
		}
		else if(__softrtc_msCount==(500000/SoftRtcTargetUs))
		{
			R_500ms_bit=1;
		}
	}
#else
	if(++__softrtc_msCount>=(1000000/SoftRtcTargetUs)) 
	{
		__softrtc_msCount=0;

		R_1s_bit=1;
		R_500ms_bit=1;
	}
	else if(__softrtc_msCount==(500000/SoftRtcTargetUs))
	{
		R_500ms_bit=1;
	}
#endif
#endif

}

#endif
#endif
