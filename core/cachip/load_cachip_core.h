#ifndef __LOAD_CACHIP_CORE_H_
#define __LOAD_CACHIP_CORE_H_

//按芯片载入对应头文件 并定义标准化接口
#if (McuType==McuType_CaChip_CA51F003)

	#include "Device\CA51F003\ca51f003_core.h"

#elif (McuType==McuType_CaChip_CA51F3)

	#include "Device\CA51F3\ca51f3_core.h"

#elif (McuType==McuType_Unkonw)

#endif



#endif

