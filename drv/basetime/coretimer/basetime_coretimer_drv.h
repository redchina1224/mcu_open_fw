#ifndef __BASETIMECORETIMER_DRV_H_
#define __BASETIMECORETIMER_DRV_H_


extern bit mSec_x500_flashbit=0;
extern bit mSec_x1000_workbit=0;
extern bit mSec_x500_workbit=0;
extern bit mSec_x100_workbit=0;


#if(BaseTimeTargetUs==10000)
extern bit mSec_x10_workbit=0;
#elif(BaseTimeTargetUs==20000)
extern bit mSec_x20_workbit=0;
#endif


void zd_basetime_init(void);

void zd_basetime_run(void);

#endif

