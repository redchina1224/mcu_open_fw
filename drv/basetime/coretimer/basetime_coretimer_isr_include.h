#ifndef __BASETIMECORETIMER_ISR_INCLUDE_H_
#define __BASETIMECORETIMER_ISR_INCLUDE_H_

#ifdef BaseTimeType
#if (BaseTimeType==BaseTimeType_CoreTimer) 

#if(BaseTimeTargetUs==10000)
extern bit M_10ms_bit;
#elif(BaseTimeTargetUs==20000)
extern bit M_20ms_bit;
#endif

#ifdef RtcType
#if (RtcType==RtcType_BaseTimeSoftRtc)
extern bit Rtc_1s_bit;
extern bit Rtc_500ms_bit;
#endif
#endif

#endif
#endif

#endif