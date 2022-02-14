#ifndef __LOADRTC_BSP_H_
#define __LOADRTC_BSP_H_

	//载入蜂鸣系统接口
	#if (RtcType==RtcType_TimerSoftRtc)	
		#include "softrtc\softrtc_drv.h"	
	#elif (RtcType==RtcType_Unkonw)
	
	#endif


#endif