#ifndef __LOADDISPLAY_BSP_H_
#define __LOADDISPLAY_BSP_H_

	//������ʾϵͳ�ӿ�
	#if ((DisplayType== DisplayType_SoftLed_Dig8WithKeys))	
		#include "softled_dig8_withkeys\softled_dig8_withkeys_drv.h"
	#elif ((DisplayType&DisplayType_SoftLed_Bits)==DisplayType_SoftLed_Bits) 
		#include "softled_bits\softled_bits_drv.h"
	#elif ((DisplayType&DisplayType_SoftLed_Dig8)==DisplayType_SoftLed_Dig8) 
		#include "softled_dig8\softled_dig8_drv.h"
	#elif (DisplayType==DisplayType_Dig8IcLed_tm1628)
		#include "ic_led\tm1628\tm1628_drv.h"
	#elif (DisplayType==DisplayType_Dig8IcLcd_tm1621c)
		#include "ic_lcd\tm1621c\tm1621c_drv.h"
	#elif (DisplayType==DisplayType_Unkonw)
	
	#endif


#endif