#ifndef __LOAD_CACHIP_CORE_H_
#define __LOAD_CACHIP_CORE_H_

//按芯片载入对应头文件 并定义标准化接口
#if (McuType==McuType_CaChip_CA51F003)

	//晶体时钟配置
	#define FocsClk 32000000

	//IO定义标准化	
	#include "Device\CA51F003\ca51f003_core.h"

	//触摸库宏定义
	//#include "cms\touch_79ft72x\CMS_CheckTouch_PT_79F72x_V1.01.h"

	//系统时钟
	#define FsysClk (FocsClk/2)
	
	//定时器0时钟配置
	//#define Ft0Clk FsysClk/12
	//定时器1时钟配置
	//#define Ft1Clk FsysClk/12

	//定时器2时钟配置
	#define Ft2Clk (FsysClk/1)

#elif (McuType==McuType_CaChip_CA51F005)
	//晶体时钟配置
	#define FocsClk 24000000

	//IO定义标准化	
	#include "Device\CA51F005\ca51f005_core.h"

	//触摸库宏定义
	//#include "cms\touch_79ft72x\CMS_CheckTouch_PT_79F72x_V1.01.h"

	//系统时钟
	#define FsysClk (FocsClk/2)
	
	//定时器0时钟配置
	//#define Ft0Clk FsysClk/12
	//定时器1时钟配置
	//#define Ft1Clk FsysClk/12

	//定时器2时钟配置
	#define Ft2Clk (FsysClk/1)
#elif (McuType==McuType_CaChip_CA51F3)
	//晶体时钟配置
	#define FocsClk (3686400)

	//IO定义标准化	
	#include "Device\CA51F3\ca51f3_core.h"

	//触摸库宏定义
	//#include "cms\touch_79ft72x\CMS_CheckTouch_PT_79F72x_V1.01.h"

	//系统时钟
	#define FsysClk (FocsClk*MOF_FSYS_CLKPLL_MULTIPLE_DEFAULT)
	
	//定时器0时钟配置
	//#define Ft0Clk FsysClk/12
	//定时器1时钟配置
	//#define Ft1Clk FsysClk/12

	//定时器2时钟配置
	#define Ft2Clk (FsysClk/1)


#elif (McuType==McuType_Unkonw)

#endif



#endif

