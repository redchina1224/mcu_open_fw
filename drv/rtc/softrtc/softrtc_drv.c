#include "..\..\com_include_drv.h"

#ifdef RtcType

unsigned long utcsec=0;

unsigned char Rtc_timeNow[3]={0,0,0};

bit rtc_halfsec_flashbit=0;
bit Sec_x1_workbit=0;

#if(RtcType==RtcType_TimerSoftRtc)
void zd_softrtc_init(void)
{
	//关中断
	ZD_GIE_DISABLE;  //中断总允许开关
	
	zd_timerInit(SoftRtcTimer); //初始化定时器125us中断`

	ZD_GIE_ENABLE; //中断总允许开关
}
#endif

unsigned long zd_getUtc_Sec(void)
{
	return utcsec;
}

bit GetSecHalfBit(void)
{
	return rtc_halfsec_flashbit;
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


void zd_softrtc_run(void)
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
	if(mSec_x1000_workbit)
	{
		Sec_x1_workbit=1;
		utcsec++;
	}
	if(mSec_x500_workbit)
	{
		rtc_halfsec_flashbit=~rtc_halfsec_flashbit;
	}
#endif

}


#endif