#ifndef __TOUCHCORECONFIG_LOAD_H_
#define __TOUCHCORECONFIG_LOAD_H_

//按芯片载入对应头文件 并定义标准化接口
#if (((McuType&McuType_FacMask)==McuType_CmsSemicon))
	#include "cms\cms_touch_load_core.h"
//#elif (McuType==McuType_SinOneChip_SC92F8463B)

//	#include "soc\touch_92f8x6xb\SensorMethod.h"
//	#include "soc\touch_92f8x6xb\S_TouchKeyCFG.h"
//	
//#elif (McuType==McuType_FremontMicroDevices_FT62F13)

//	#include "fmd\FT62F13X\touch.h"

#elif (McuType==McuType_CaChip_CA51F3)
	#include "cachip\Device\CA51F3\TS_Lib\Includes\ts_def.h"	
	#include "cachip\Device\CA51F3\TS_Lib\Includes\ts_service.h"	
	#include "cachip\Device\CA51F3\TS_Lib\Includes\ts_api.h"
#elif (McuType==McuType_Unkonw)

#endif




	#include "touchkey_core.h"





#endif