#ifndef __LOADDISPLAY_BSP_H_
#define __LOADDISPLAY_BSP_H_

	//载入显示系统接口
	#if ((DisplayType== DisplayType_Dig8SoftLed))	
		#include "softled\softled_drv.h"
	#elif ((DisplayType&DisplayType_SoftLed_Bits)==DisplayType_SoftLed_Bits) 
		#include "softled_bits\softled_bits_drv.h"
	#elif (DisplayType==DisplayType_Dig8IcLed_tm1628)
		#include "ic_led\tm1628\tm1628_drv.h"
	#elif (DisplayType==DisplayType_Unkonw)
	
	#endif


#endif