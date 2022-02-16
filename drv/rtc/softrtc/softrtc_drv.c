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
unsigned int utcmsec=0;
//xdata unsigned long localsec=0;



bit mSec_x1000_workbit=0;
bit mSec_x500_workbit=0;
bit mSec_x100_workbit=0;
bit mSec_x50_workbit=0;
bit mSec_x10_workbit=0;
bit mSec_x5_workbit=0;
bit mSec_x3_workbit=0;
bit mSec_x1_workbit=0;

unsigned int mSec_x1_cnt=0;

unsigned long mSec_x100_utc=0;

unsigned char Rtc_timeNow[3]={0,0,0};


void zd_softrtcInit(void)
{
	//���ж�
	 ZD_GIE(ZD_GIE_DISABLE);  //�ж���������
	
	T_SecCount=&utcsec;
	T_msCount=&utcmsec;
	zd_timerInit(SoftRtcTimer,125); //��ʼ����ʱ��125us�ж�`

	 ZD_GIE(ZD_GIE_ENABLE); //�ж���������
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
	if(utcmsec<500) return 1; else return 0;
}


void GetHourMinSec(unsigned char* timeval,unsigned long usec)
{
	timeval[0]=(usec)%60;
	timeval[1]=(usec/60)%60;
	timeval[2]=(usec/3600)%24;
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
	
	if(T_1ms_bit)
	{
		if(++mSec_x1_cnt>1000)
		{
			 mSec_x1_cnt=0;	
			 mSec_x1000_workbit=1;
		}	
		
		if((mSec_x1_cnt%5)==0) 
		{
			mSec_x5_workbit=1;
			if((mSec_x1_cnt%10)==0) 
			{
				mSec_x10_workbit=1;	
				if((mSec_x1_cnt%50)==0)
				{ 
					mSec_x50_workbit=1;
					if((mSec_x1_cnt%100)==0)
					{ 
						mSec_x100_workbit=1;
						if((++mSec_x100_utc)>4294960000) mSec_x100_utc=0;
						if((mSec_x1_cnt%500)==0)
						{ 
							mSec_x500_workbit=1;
						}
					}	
				}
			}	
		}


		if((mSec_x1_cnt%3)==0) 
		{
			mSec_x3_workbit=1;
		}
					
		mSec_x1_workbit=1;			
		T_1ms_bit=0;
	}
	
}

void zd_basetime_clear(void)
{
	ZD_CLRWDT;
	
	if(mSec_x1000_workbit) mSec_x1000_workbit=0;

	if(mSec_x500_workbit) mSec_x500_workbit=0;

	if(mSec_x100_workbit) mSec_x100_workbit=0;
	
	if(mSec_x50_workbit) mSec_x50_workbit=0;

	if(mSec_x10_workbit) mSec_x10_workbit=0;
	
	if(mSec_x5_workbit) mSec_x5_workbit=0;
	
	if(mSec_x3_workbit) mSec_x3_workbit=0;

	if(mSec_x1_workbit) mSec_x1_workbit=0;
}


#endif
#endif