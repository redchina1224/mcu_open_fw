#ifndef __LOADKEY_DRV_H_
#define __LOADKEY_DRV_H_

	//载入触摸按键系统接口
	#if ((KeyType&KeyType_Gpio)==KeyType_Gpio)

	#endif
	
	#if ((KeyType&KeyType_McuTouch)==KeyType_McuTouch)

	#endif
	
	#if ((KeyType&KeyType_IR)==KeyType_IR)
		//#include "irkey\irkey_drv.h"
	#endif
	
	#if ((KeyType&KeyType_RF)==KeyType_RF)
		#include "rfkey\rfkey_drv.h"
	#endif
		
		
	
	#if ((KeyType&KeyType_MultiChannel)==KeyType_MultiChannel)
		#include "key_Multichannel_drv.h"
	#else
		#include "key_drv.h"
	#endif
	


#endif