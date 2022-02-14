#ifndef __CORECONFIG_H_
#define __CORECONFIG_H_

#include "defineStd_core.h" //标准化定义
#include "defineDevplatform_core.h" //开发平台清单
#include "defineMcutype_core.h"  //MCU型号清单


//定义开发平台编译器
#define DevPlatform DevPlatform_CMSIDE_CASD
//#define DevPlatform DevPlatform_Keil_C51


//定义MCU型号
#define McuType McuType_CmsSemicon_CMS79F623
//#define McuType McuType_SinOneChip_SC92F8463B



//按芯片载入对应头文件 并定义标准化接口
#if ((McuType==McuType_CmsSemicon_CMS79F623))

	//晶体时钟配置
	#define FocsClk 8000000
	
	//IO定义标准化	
	#include "cms\cms_core.h"

	#include "cms\touch_79ft73x\CMS_CheckTouch_PT_79FT73xx_V1.08.h"


	
	//系统时钟
	#if (ZD_FSYS_CLKSET_DEFAULT==ZD_FSYS_CLKSET_FOSC_DIV1)
		#define FsysClk FocsClk/1
	#elif (ZD_FSYS_CLKSET_DEFAULT==ZD_FSYS_CLKSET_FOSC_DIV2)
		#define FsysClk FocsClk/2
	#elif (ZD_FSYS_CLKSET_DEFAULT==ZD_FSYS_CLKSET_FOSC_DIV4)
		#define FsysClk FocsClk/4
	#elif (ZD_FSYS_CLKSET_DEFAULT==ZD_FSYS_CLKSET_FOSC_DIV8)
		#define FsysClk FocsClk/8
	#elif (ZD_FSYS_CLKSET_DEFAULT==ZD_FSYS_CLKSET_FOSC_DIV16)
		#define FsysClk FocsClk/16
	#elif (ZD_FSYS_CLKSET_DEFAULT==ZD_FSYS_CLKSET_FOSC_DIV32)
		#define FsysClk FocsClk/32
	#elif (ZD_FSYS_CLKSET_DEFAULT==ZD_FSYS_CLKSET_FOSC_DIV64)
		#define FsysClk FocsClk/64		
	#elif (ZD_FSYS_CLKSET_DEFAULT==ZD_FSYS_CLKSET_LFINTOSC_32KHZ)
		#define FsysClk 32000
	#endif

	
	//定时器时钟配置
	#if (ZD_TIMER0_CLKSET_DEFAULT==ZD_TIMER0_CLKSET_FSYS_DIV4)
	
		#if (ZD_TIMER0_CLKPSASET_DEFAULT==ZD_TIMER0_CLKPSASET_NONE)
			#define Ft0Clk FsysClk/4
		#elif (ZD_TIMER0_CLKPSASET_DEFAULT==ZD_TIMER0_CLKPSASET_DIV2)
			#define Ft0Clk FsysClk/4/2
		#elif (ZD_TIMER0_CLKPSASET_DEFAULT==ZD_TIMER0_CLKPSASET_DIV4)
			#define Ft0Clk FsysClk/4/4
		#elif (ZD_TIMER0_CLKPSASET_DEFAULT==ZD_TIMER0_CLKPSASET_DIV8)
			#define Ft0Clk FsysClk/4/8
		#elif (ZD_TIMER0_CLKPSASET_DEFAULT==ZD_TIMER0_CLKPSASET_DIV16)
			#define Ft0Clk FsysClk/4/16
		#elif (ZD_TIMER0_CLKPSASET_DEFAULT==ZD_TIMER0_CLKPSASET_DIV32)
			#define Ft0Clk FsysClk/4/32
		#elif (ZD_TIMER0_CLKPSASET_DEFAULT==ZD_TIMER0_CLKPSASET_DIV64)
			#define Ft0Clk FsysClk/4/64
		#elif (ZD_TIMER0_CLKPSASET_DEFAULT==ZD_TIMER0_CLKPSASET_DIV128)
			#define Ft0Clk FsysClk/4/128
		#elif (ZD_TIMER0_CLKPSASET_DEFAULT==ZD_TIMER0_CLKPSASET_DIV256)
			#define Ft0Clk FsysClk/4/256
		#endif
		
	#endif		
	

#elif (McuType==McuType_SinOneChip_SC92F8463B)

	//晶体时钟配置
	#define FocsClk 24000000
	
	//底层调用
	#include <intrins.h>
	
	
	//IO定义标准化	
	#include "soc\touch_92f8x6xb\SC92F846XB_C.H"

	//IO定义标准化	
	#include "soc\soc_core.h"

	#include "soc\touch_92f8x6xb\SensorMethod.h"
	#include "soc\touch_92f8x6xb\S_TouchKeyCFG.h"

	//系统时钟
	#if (ZD_FSYS_CLKSET_DEFAULT==ZD_FSYS_CLKSET_FOSC_DIV1)
		#define FsysClk FocsClk/1
	#elif (ZD_FSYS_CLKSET_DEFAULT==ZD_FSYS_CLKSET_FOSC_DIV2)
		#define FsysClk FocsClk/2
	#elif (ZD_FSYS_CLKSET_DEFAULT==ZD_FSYS_CLKSET_FOSC_DIV4)
		#define FsysClk FocsClk/4
	#elif (ZD_FSYS_CLKSET_DEFAULT==ZD_FSYS_CLKSET_FOSC_DIV12)
		#define FsysClk FocsClk/12
	#endif
	
	
	//定时器时钟配置
	#if (ZD_TIMER0_CLKSET_DEFAULT==ZD_TIMER0_CLKSET_FSYS)
		#if (ZD_TIMER0_CLKPSASET_DEFAULT==ZD_TIMER0_CLKPSASET_DIV1)
			#define Ft0Clk FsysClk/1
		#elif (ZD_TIMER0_CLKPSASET_DEFAULT==ZD_TIMER0_CLKPSASET_DIV12)
			#define Ft0Clk FsysClk/12
		#endif
	#endif	
	

#elif (McuType==McuType_Unkonw)

#endif










#endif