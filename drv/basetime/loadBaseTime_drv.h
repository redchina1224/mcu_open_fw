#ifndef __LOADBASETIME_BSP_H_
#define __LOADBASETIME_BSP_H_

	//载入蜂鸣系统接口
	#if (BaseTimeType==BaseTimeType_CoreTimer)	
		#include "coretimer\basetime_coretimer_drv.h"	
	#elif (BaseTimeType==BaseTimeType_Unkonw)
	
	#endif


#endif