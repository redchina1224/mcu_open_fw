#ifndef __SOFTRTC_DRV_H_
#define __SOFTRTC_DRV_H_



//extern unsigned int softrtctestv;
extern bit Sec_x1_workbit;
extern bit mSec_x500_flashbit;
extern bit mSec_x1000_workbit;
extern bit mSec_x500_workbit;
extern bit mSec_x250_workbit;
extern bit mSec_x100_workbit;
extern bit mSec_x50_workbit;
extern bit mSec_x10_workbit;

extern unsigned char Rtc_timeNow[3];

void SetUtcSecByHourMin(unsigned char hour,unsigned char min);

unsigned long GetUtcSecByHourMin(unsigned long hour,unsigned long min);

unsigned long GetUtcSec(void);

bit GetSecHalfBit(void);

void GetHourMinSec(unsigned char* timeval,unsigned long usec);

void zd_softrtcInit(void);

void zd_basetime_run(void);

void zd_basetime_clear(void);

unsigned long zd_getUtc_100mSec(void);

#endif

