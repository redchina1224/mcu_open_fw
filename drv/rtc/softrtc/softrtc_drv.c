#include "..\..\com_include_drv.h"

#ifdef RtcType
#if (RtcType==RtcType_TimerSoftRtc) 

unsigned long utcsec=0;
unsigned long utc100msec=0;

unsigned char rtc10msec_cnt=0;

bit Sec_x1_workbit=0;
bit mSec_x500_flashbit=0;
//bit mSec_x250_flashbit=0;
bit mSec_x1000_workbit=0;
bit mSec_x500_workbit=0;
//bit mSec_x250_workbit=0;
bit mSec_x100_workbit=0;
bit mSec_x50_workbit=0;
//bit mSec_x40_workbit=0;
//bit mSec_x30_workbit=0;
bit mSec_x20_workbit=0;
bit mSec_x10_workbit=0;



//unsigned char mSec_x50_cnt=0;
unsigned char mSec_x100_cnt=0;

unsigned char Rtc_timeNow[3]={0,0,0};

void zd_softrtcInit(void)
{
	//关中断
	 ZD_GIE_DISABLE;  //中断总允许开关
	
	//T_SecCount=&utcsec;
	zd_timerInit(SoftRtcTimer); //初始化定时器125us中断`

	 ZD_GIE_ENABLE; //中断总允许开关
}

unsigned long zd_getUtc_Sec(void)
{
	return utcsec;
}

unsigned long zd_getUtc_100mSec(void)
{
	return utc100msec;
}


bit GetSecHalfBit(void)
{
	return mSec_x500_flashbit;
}


void GetHourMinSec(unsigned char* timeval,unsigned long usec)
{
	timeval[0]=(usec)%60;
	timeval[1]=(usec/60)%60;
	timeval[2]=(usec/3600)%24;
}

void SetUtcSecByHourMin(unsigned char hour,unsigned char min)
{
	//ZD_GIE_DISABLE;
	utcsec=((3600*(unsigned long)hour)+(60*(unsigned long)min));
	//ZD_GIE_ENABLE;
}

unsigned long GetUtcSecByHourMin(unsigned long hour,unsigned long min)
{
	return ((unsigned long)((3600*(unsigned long)hour)+(60*(unsigned long)min)));
}


void zd_basetime_run(void)
{
	//ZD_CLRWDT;

	Sec_x1_workbit=0;
		
	mSec_x1000_workbit=0;
	
	if(mSec_x500_workbit)
	{
		mSec_x500_workbit=0;
		mSec_x500_flashbit=~mSec_x500_flashbit;
	}
/*
	if(mSec_x250_workbit)
	{
		mSec_x250_workbit=0;
		mSec_x250_flashbit=~mSec_x250_flashbit;
	}
*/	

	mSec_x100_workbit=0;

	mSec_x50_workbit=0;
	mSec_x20_workbit=0;
	mSec_x10_workbit=0;
    

	if(M_10ms_bit)
	{	
		mSec_x10_workbit=1;	
		M_10ms_bit=0;
		if(++rtc10msec_cnt>=5) 
		{
			rtc10msec_cnt=0;
			mSec_x50_workbit=1;
		}
	}
	
	if(M_20ms_bit)
	{	
		mSec_x20_workbit=1;	
		M_20ms_bit=0;
	}

	if(M_100ms_bit)
	{	
		M_100ms_bit=0;
		mSec_x100_workbit=1;	
		
		utc100msec++;
		
		if(++mSec_x100_cnt>=10)
		{
			mSec_x100_cnt=0;	
			mSec_x500_workbit=1;
			mSec_x1000_workbit=1;
		}
		else if(mSec_x100_cnt==5)
		{
			mSec_x500_workbit=1;
		}
	}
	
	if(M_1s_bit)
    {
		M_1s_bit=0;
        Sec_x1_workbit=1;
		utcsec++;
    }
}

#endif
#endif