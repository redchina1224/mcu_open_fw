#ifndef __LOADNTCRES_DRV_H_
#define __LOADNTCRES_DRV_H_

	//载入NTC参数
	#if ((NtcType== NtcType_10K_B3435))	
		#include "NTC_10K_B3435\Ntc_10K_B3435.h"	
	#elif (NtcType==NtcType_50K_B3950)
		#include "NTC_50K_B3950\Ntc_50K_B3950.h"
	#elif (NtcType==NtcType_100K_B3950)
		#include "NTC_100K_B3950\Ntc_100K_B3950.h"
	#elif (NtcType==NtcType_Unkonw)
	
	#endif


	//载入ADC数值计算值
	#include "ntc_adcval_calc.h"

#endif