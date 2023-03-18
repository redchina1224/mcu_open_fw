#ifndef __CORECONFIG_LOAD_H_
#define __CORECONFIG_LOAD_H_

//按芯片载入对应头文件 并定义标准化接口
#if((McuType&McuType_FacMask)==McuType_CaChip)

	//晶体时钟配置
	//#define FocsClk 16000000

	//IO定义标准化	
	#include "cachip\load_cachip_core.h"

	//触摸库宏定义
	//#include "cms\touch_79ft72x\CMS_CheckTouch_PT_79F72x_V1.01.h"


	
	//系统时钟
	
	//定时器0时钟配置

	//定时器1时钟配置
	//#define Ft1Clk FsysClk/4/1

	//定时器2时钟配置


#elif (McuType==McuType_Unkonw)

#endif



#endif

