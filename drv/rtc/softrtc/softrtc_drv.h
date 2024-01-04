#ifndef __SOFTRTC_DRV_H_
#define __SOFTRTC_DRV_H_

extern bit rtc_halfsec_flashbit;

extern bit Sec_x1_workbit;

extern unsigned char Rtc_timeNow[3];

void mof_softrtc_init(void);

unsigned long mof_getUtc_Sec(void);

bit GetSecHalfBit(void);

unsigned char CheckUtcSecNowWithinDayTimeInterval(unsigned long start,unsigned long end);
	
void GetHourMinSecByUtcSec(unsigned char* timeval,unsigned long usec);

void SetUtcSecByHourMin(unsigned char hour,unsigned char min);

unsigned long GetUtcSecByHourMin(unsigned long hour,unsigned long min);

void mof_softrtc_run(void);

#endif

