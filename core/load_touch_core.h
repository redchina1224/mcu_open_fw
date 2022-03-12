#ifndef __TOUCHCORECONFIG_LOAD_H_
#define __TOUCHCORECONFIG_LOAD_H_

//��оƬ�����Ӧͷ�ļ� �������׼���ӿ�
#if ((McuType==McuType_CmsSemicon_CMS79F738))


	//������
	#include "cms\touch_79ft73x\CMS_CheckTouch_PT_79FT73xx_V1.08.h"
	

#elif (McuType==McuType_SinOneChip_SC92F8463B)

	#include "soc\touch_92f8x6xb\SensorMethod.h"
	#include "soc\touch_92f8x6xb\S_TouchKeyCFG.h"
	
#elif (McuType==McuType_FremontMicroDevices_FT62F13)

	#include "fmd\FT62F13X\touch.h"

#elif (McuType==McuType_Unkonw)

#endif




	#include "touchkey_core.h"





#endif