#include "..\..\com_include_drv.h"

#ifdef BaseTimeType
#if (BaseTimeType==BaseTimeType_CoreTimer) 

unsigned char basetime_msec_cnt=0;
unsigned char basetime_100msec_cnt=0;

bit mSec_x500_flashbit=0;
bit mSec_x1000_workbit=0;
bit mSec_x500_workbit=0;
bit mSec_x100_workbit=0;


#if(BaseTimeTargetUs==10000)
bit mSec_x10_workbit=0;
#elif(BaseTimeTargetUs==20000)
bit mSec_x20_workbit=0;
#endif


void zd_basetime_init(void)
{
	//关中断
	ZD_GIE_DISABLE;  //中断总允许开关
	
	zd_timerInit(BaseTime_CoreTimer); //初始化定时器125us中断`

	ZD_GIE_ENABLE; //中断总允许开关
}

void zd_basetime_run(void)
{
	//ZD_CLRWDT;
		
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

    

#if(BaseTimeTargetUs==10000)

	mSec_x10_workbit=0;

	if(M_10ms_bit)
	{	
		mSec_x10_workbit=1;	
		M_10ms_bit=0;

		if(++basetime_msec_cnt>=10) 
		{
			basetime_msec_cnt=0;

			mSec_x100_workbit=1;
			
			if(++basetime_100msec_cnt>=10)
			{
				basetime_100msec_cnt=0;
				mSec_x1000_workbit=1;
				mSec_x500_workbit=1;
			}
			else if(basetime_100msec_cnt==5) 
				mSec_x500_workbit=1;
		}
	}

#elif(BaseTimeTargetUs==20000)

	mSec_x20_workbit=0;

	if(M_20ms_bit)
	{	
		mSec_x20_workbit=1;	
		M_20ms_bit=0;

		if(++basetime_msec_cnt>=5) 
		{
			basetime_msec_cnt=0;

			mSec_x100_workbit=1;
			
			if(++basetime_100msec_cnt>=10)
			{
				basetime_100msec_cnt=0;
				mSec_x1000_workbit=1;
				mSec_x500_workbit=1;
			}
			else if(basetime_100msec_cnt==5) 
				mSec_x500_workbit=1;
		}
	}

#endif

}

#endif
#endif