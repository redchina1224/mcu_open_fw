#include "..\..\com_include_drv.h"

#ifdef RtcType
#if (RtcType==RtcType_TimerSoftRtc) 

//unsigned int utcmsec_ago=0;


//unsigned char msecRun_utc100msecAgo=0;
//unsigned char utc100msec=0;


//unsigned char minRun_Ago=0;
//unsigned char minRun=0;
//unsigned char minRunSecCnt=0;


//unsigned long secRun_utcsecAgo=0;
unsigned long utcsec=0;
unsigned char utc10msec=0;
//xdata unsigned long localsec=0;

//unsigned int softrtctestv=0;
bit mSec_x500_flashbit=0;
bit mSec_x1000_workbit=0;
bit mSec_x500_workbit=0;
bit mSec_x250_workbit=0;
bit mSec_x100_workbit=0;
bit mSec_x50_workbit=0;
bit mSec_x10_workbit=0;
//bit mSec_x5_workbit=0;
//bit mSec_x3_workbit=0;
//bit mSec_x1_workbit=0;

unsigned char mSec_x10_cnt=0;

unsigned long mSec_x100_utc=0;

unsigned char Rtc_timeNow[3]={0,0,0};


void zd_softrtcInit(void)
{
	//关中断
	 ZD_GIE_DISABLE;  //中断总允许开关
	
	T_SecCount=&utcsec;
	T_10msCount=&utc10msec;
	zd_timerInit(SoftRtcTimer,125); //初始化定时器125us中断`

	 ZD_GIE_ENABLE; //中断总允许开关
}

unsigned long GetUtcSec(void)
{
	return utcsec;
}

unsigned long zd_getUtc_100mSec(void)
{
	return mSec_x100_utc;
}


bit GetSecHalfBit(void)
{
	if(utc10msec<50) return 1; else return 0;
}


void GetHourMinSec(unsigned char* timeval,unsigned long usec)
{
	timeval[0]=(usec)%60;
	timeval[1]=(usec/60)%60;
	timeval[2]=(usec/3600)%24;
}

void SetUtcSecByHourMin(unsigned char hour,unsigned char min)
{
	TMR1IE=0;
	utcsec=((3600*(unsigned long)hour)+(60*(unsigned long)min));
	TMR1IE=1;
}
unsigned long GetUtcSecByHourMin(unsigned char hour,unsigned char min)
{
	return ((unsigned long)((3600*(unsigned long)hour)+(60*(unsigned long)min)));
}
/*
bit SecRunOnce(void)
{
	if(secRun_utcsecAgo!=utcsec)
	{
		secRun_utcsecAgo=utcsec;	
		//if(minRunSecCnt<59) {minRunSecCnt++;} else {minRunSecCnt=0;minRun++;}
		return 1;
	}
	return 0;
}
*/
//bit MinRunOnce(void)
//{
//	if(minRun_Ago!=minRun)
//	{
//		minRun_Ago=minRun;
//		return 1;
//	}
//	return 0;
//}


/*
bit mSec_x10_RunOnce(void)
{
	if(interrupt_10msec_ago!=interrupt_10msec)
	{
		interrupt_10msec_ago=interrupt_10msec;
		return 1;
	}
	return 0;
}
*/

void zd_basetime_run(void)
{
	ZD_CLRWDT;
	
	mSec_x1000_workbit=0;
	
	if(mSec_x500_workbit)
	{
		mSec_x500_workbit=0;
		mSec_x500_flashbit=~mSec_x500_flashbit;
	}

	mSec_x250_workbit=0;
	
	mSec_x100_workbit=0;
	
	mSec_x50_workbit=0;

	mSec_x10_workbit=0;
    
/*	if(M_1s_bit)
    {
         mSec_x1000_workbit=1;
         M_1s_bit=0;
    }
*/    
	if(M_10ms_bit)
	{	
		mSec_x10_workbit=1;	
				
		if(++mSec_x10_cnt>=100)
		{
			 mSec_x10_cnt=0;	
			 mSec_x1000_workbit=1;
		}
		
		if((mSec_x10_cnt%5)==0)
		{
			mSec_x50_workbit=1;
			if((mSec_x10_cnt%10)==0)
			{ 
				mSec_x100_workbit=1;
				if((++mSec_x100_utc)>4294960000) mSec_x100_utc=0;
				
				if(mSec_x10_cnt==0||mSec_x10_cnt==50)
				{
					 mSec_x250_workbit=1;
					 mSec_x500_workbit=1;
				}
			}
			
			if(mSec_x10_cnt==25||mSec_x10_cnt==75) mSec_x250_workbit=1;
		}
		
	


		
		M_10ms_bit=0;
	}
	
}

void zd_basetime_clear(void)
{
    /*
	ZD_CLRWDT;
	
	mSec_x1000_workbit=0;

	mSec_x500_workbit=0;

	mSec_x250_workbit=0;
	
	mSec_x100_workbit=0;
	
	mSec_x50_workbit=0;

	mSec_x10_workbit=0;
    */
	
}


#endif
#endif