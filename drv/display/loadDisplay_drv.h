#ifndef __LOADDISPLAY_BSP_H_
#define __LOADDISPLAY_BSP_H_

	//载入显示系统接口
/*
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
*/
	//载入显示系统接口
	#if ((DisplayType&DisplayType_SoftLed)==DisplayType_SoftLed)
		#if ((DisplayTypeSoftLedModel&DisplayType_SoftLed_Dig8WithKeys)== DisplayType_SoftLed_Dig8WithKeys)	
			#include "softled_dig8_withkeys\softled_dig8_withkeys_drv.h"
		#elif ((DisplayTypeSoftLedModel&DisplayType_SoftLed_Dig8_Bidir)==DisplayType_SoftLed_Dig8_Bidir) 
			#include "softled_dig8_bidir\softled_dig8_bidir_drv.h"
		#elif ((DisplayTypeSoftLedModel&DisplayType_SoftLed_Bits)==DisplayType_SoftLed_Bits) 
			#include "softled_bits\softled_bits_drv.h"
		#elif ((DisplayTypeSoftLedModel&DisplayType_SoftLed_Dig8)==DisplayType_SoftLed_Dig8) 
			#include "softled_dig8\softled_dig8_drv.h"
		#endif
	#endif


	#if ((DisplayType&DisplayType_IcLed)==DisplayType_IcLed)
		#if ((DisplayTypeIcLedModel&DisplayType_IcLed_tm1640)== DisplayType_IcLed_tm1640)
			#include "ic_led\tm1640\tm1640_drv.h"
		#elif ((DisplayTypeIcLedModel&DisplayType_IcLed_tm1628)== DisplayType_IcLed_tm1628)
			#include "ic_led\tm1628\tm1628_drv.h"
		#endif
	#endif


	#if ((DisplayType&DisplayType_IcLcd)==DisplayType_IcLcd)
		#if ((DisplayTypeIcLcdModel&DisplayType_IcLcd_tm1621c)== DisplayType_IcLcd_tm1621c)	
			#include "ic_lcd\tm1621c\tm1621c_drv.h"
		#endif
	#endif

#endif