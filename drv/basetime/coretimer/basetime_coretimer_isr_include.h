#ifndef __BASETIMECORETIMER_ISR_INCLUDE_H_
#define __BASETIMECORETIMER_ISR_INCLUDE_H_

#ifdef BaseTimeType
#if (BaseTimeType==BaseTimeType_CoreTimer) 

#if(BaseTimeTargetUs==10000)
bit M_10ms_bit;
#elif(BaseTimeTargetUs==20000)
bit M_20ms_bit;
#endif

#endif
#endif

#endif