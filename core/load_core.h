#ifndef __CORECONFIG_LOAD_H_
#define __CORECONFIG_LOAD_H_

//按芯片载入对应头文件 并定义标准化接口
#if((McuType&McuType_FacMask)==McuType_CaChip)

	//IO定义标准化	
	#include "cachip\load_cachip_core.h"

#elif (McuType==McuType_Unkonw)

#endif



#endif

