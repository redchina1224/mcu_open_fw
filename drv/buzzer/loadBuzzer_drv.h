#ifndef __LOADBUZZER_BSP_H_
#define __LOADBUZZER_BSP_H_

	//载入蜂鸣系统接口
	#if ((BuzzerType==BuzzerType_Gpio)||(BuzzerType==BuzzerType_PWM)||(BuzzerType==BuzzerType_TimerInv))	
		#include "buzzer\buzzer_drv.h"	
	#elif (BuzzerType==BuzzerType_Unkonw)
	
	#endif


#endif