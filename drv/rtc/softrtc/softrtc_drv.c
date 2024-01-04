#include "..\..\com_include_drv.h"

#ifdef RtcType

unsigned long utcsec=0;

unsigned char Rtc_timeNow[3]={0,0,0};

bit rtc_halfsec_flashbit=0;
bit Sec_x1_workbit=0;

#if(RtcType==RtcType_TimerSoftRtc)
void mof_softrtc_init(void)
{
	//关中断
	MOF_GIE_DISABLE;  //中断总允许开关
	
	mof_timerInit(SoftRtcTimer); //初始化定时器125us中断`

	MOF_GIE_ENABLE; //中断总允许开关
}
#endif

unsigned long mof_getUtc_Sec(void)
{
	return utcsec;
}

bit GetSecHalfBit(void)
{
	return rtc_halfsec_flashbit;
}

unsigned char CheckUtcSecNowWithinDayTimeInterval(unsigned long start,unsigned long end)
{
	unsigned long utcsec_inday=GetUtcSecByHourMin(Rtc_timeNow[2],Rtc_timeNow[1]);//(utcsec%(3600*24));
	
	if((start)>(end)) //起始时间比终止时间晚:如 20:00--8:00,21:00--19:00
	{
		if(utcsec_inday<(end)||utcsec_inday>(start)) return 1;
	}
	else if((start)<(end)) //起始时间比终止时间早:如 8:00--20:00
	{
		if(utcsec_inday<(end)&&utcsec_inday>(start)) return 2;
	}
	else //起始时间与终止时间相同,一直有效
	{
		return 3;
	}
	
	return 0;
}

void GetHourMinSecByUtcSec(unsigned char* timeval,unsigned long usec)
{
	timeval[0]=(usec)%60;
	timeval[1]=(usec/60)%60;
	timeval[2]=(usec/3600)%24;
}

void SetUtcSecByHourMin(unsigned char hour,unsigned char min)
{
	utcsec=((3600*(unsigned long)hour)+(60*(unsigned long)min));
}

unsigned long GetUtcSecByHourMin(unsigned long hour,unsigned long min)
{
	return ((unsigned long)((3600*(unsigned long)hour)+(60*(unsigned long)min)));
}


void mof_softrtc_run(void)
{
Sec_x1_workbit=0;
#if (RtcType==RtcType_TimerSoftRtc)	
	if(R_1s_bit)
	{
		Sec_x1_workbit=1;
		R_1s_bit=0;
		utcsec++;
	}

	if(R_500ms_bit)
	{
		R_500ms_bit=0;
		rtc_halfsec_flashbit=~rtc_halfsec_flashbit;
	}
#elif (RtcType==RtcType_BaseTimeSoftRtc)
	if(Rtc_1s_bit)
	{
		Rtc_1s_bit=0;
		Sec_x1_workbit=1;
		utcsec++;
	}
	
	if(Rtc_500ms_bit)
	{
		Rtc_500ms_bit=0;
		rtc_halfsec_flashbit=~rtc_halfsec_flashbit;
	}
#endif

}


#endif