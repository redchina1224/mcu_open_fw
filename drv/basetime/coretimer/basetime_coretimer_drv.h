#ifndef __BASETIMECORETIMER_DRV_H_
#define __BASETIMECORETIMER_DRV_H_


extern bit mSec_x500_flashbit;
extern bit mSec_x1000_workbit;
extern bit mSec_x500_workbit;
extern bit mSec_x100_workbit;
extern bit mSec_x50_workbit;

#if(BaseTimeTargetUs==10000)
extern bit mSec_x10_workbit;
#elif(BaseTimeTargetUs==20000)
extern bit mSec_x20_workbit;
#endif


void zd_basetime_init(void);

void zd_basetime_run(void);

#endif

