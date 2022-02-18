#ifndef __SOFTRTC_DRV_H_
#define __SOFTRTC_DRV_H_



//extern unsigned int softrtctestv;
extern bit mSec_x1000_workbit;
extern bit mSec_x500_workbit;
extern bit mSec_x250_workbit;
extern bit mSec_x100_workbit;
extern bit mSec_x50_workbit;
extern bit mSec_x10_workbit;

unsigned long GetUtcSec(void);

bit GetSecHalfBit(void);

void GetHourMinSec(unsigned char* timeval,unsigned long usec);

void zd_softrtcInit(void);

void zd_basetime_run(void);

void zd_basetime_clear(void);

unsigned long zd_getUtc_100mSec(void);

#endif

