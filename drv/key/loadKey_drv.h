#ifndef __LOADKEY_DRV_H_
#define __LOADKEY_DRV_H_

	//���봥������ϵͳ�ӿ�
	#if (KeyType==KeyType_Gpio)	
		
	#elif (KeyType==KeyType_McuTouch)
		#include "key_drv.h"	

	#elif (KeyType==KeyType_Touch)

	#elif (KeyType==KeyType_IR)

	#elif (KeyType==KeyType_Unkonw)
	
	#endif


#endif