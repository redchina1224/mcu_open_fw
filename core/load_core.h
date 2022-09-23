#ifndef __CORECONFIG_LOAD_H_
#define __CORECONFIG_LOAD_H_

//按芯片载入对应头文件 并定义标准化接口
#if ((McuType==McuType_CmsSemicon_CMS79F738)||(McuType==McuType_CmsSemicon_CMS79F726))

	//晶体时钟配置
	#define FocsClk 8000000

	#if ((McuType==McuType_CmsSemicon_CMS79F738))
	//IO定义标准化	
	#include "cms\cms_core.h"

	//触摸库宏定义
	//#include "cms\touch_79ft73x\CMS_CheckTouch_PT_79FT73xx_V1.08.h"

	#elif (McuType==McuType_CmsSemicon_CMS79F726)

	//IO定义标准化	
	#include "cms\cms79f726_core.h"

	//触摸库宏定义
	//#include "cms\touch_79ft72x\CMS_CheckTouch_PT_79F72x_V1.01.h"

	#endif
	
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

	
	//定时器0时钟配置
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


	//定时器2时钟配置
	#if ((ZD_TIMER2_CLKSET_DEFAULT&(BIT0|BIT1))==ZD_TIMER2_CLKSET_FSYS_DIV4_DIV1)
		#define Ft2Clk FsysClk/4/1
	#elif ((ZD_TIMER2_CLKSET_DEFAULT&(BIT0|BIT1))==ZD_TIMER2_CLKSET_FSYS_DIV4_DIV4)
		#define Ft2Clk FsysClk/4/4
	#elif ((ZD_TIMER2_CLKSET_DEFAULT&(BIT0|BIT1))==ZD_TIMER2_CLKSET_FSYS_DIV4_DIV16)
		#define Ft2Clk FsysClk/4/16
	#endif	



#elif (McuType==McuType_CmsSemicon_CMS89F2265B)
	//晶体时钟配置

	#ifndef FocsClk
		#define FocsClk 8000000
	#endif
	
	//IO定义标准化	
	#include "cms\cms89f2265b_core.h"
	
	//系统时钟
	#if (ZD_FSYS_CLKSET_DEFAULT==ZD_FSYS_CLKSET_FOSC_DIV1||ZD_FSYS_CLKSET_DEFAULT==ZD_FSYS_CLKSET_XT_DIV1)
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

#elif (McuType==McuType_CmsSemicon_CMS79F113)
	
	//晶体时钟配置
	#define FocsClk 16000000
	
	//IO定义标准化	
	#include "cms\cms79f133_core.h"
	
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


#elif (McuType==McuType_CmsSemicon_CMS80F252X)

	//晶体时钟配置
	#define FocsClk 48000000
	
	//IO定义标准化	
	#include "cms\cms80f_core.h"

	//系统时钟
	#if (ZD_FSYS_CLKSET_DEFAULT==ZD_FSYS_CLKSET_FOSC_DIV1)
		#define FsysClk FocsClk/1
	#elif (ZD_FSYS_CLKSET_DEFAULT==ZD_FSYS_CLKSET_FOSC_DIV2)
		#define FsysClk FocsClk/2
	#elif (ZD_FSYS_CLKSET_DEFAULT==ZD_FSYS_CLKSET_FOSC_DIV4)
		#define FsysClk FocsClk/4
	#elif (ZD_FSYS_CLKSET_DEFAULT==ZD_FSYS_CLKSET_FOSC_DIV8)
		#define FsysClk FocsClk/8
	#endif
	
	
	//定时器时钟配置
	#if (ZD_TIMER0_CLKSET_DEFAULT==ZD_TIMER0_CLKSET_FSYS)
		#if (ZD_TIMER0_CLKPSASET_DEFAULT==ZD_TIMER0_CLKPSASET_DIV4)
			#define Ft0Clk FsysClk/4
		#elif (ZD_TIMER0_CLKPSASET_DEFAULT==ZD_TIMER0_CLKPSASET_DIV12)
			#define Ft0Clk FsysClk/12
		#endif
	#endif	
#elif (McuType==McuType_CmsSemicon_CMS80F7518)

	//晶体时钟配置
	#define FocsClk 48000000
	
	//IO定义标准化	
	#include "cms\cms80f7518_core.h"

	//系统时钟

	
	
	//定时器时钟配置


#elif (McuType==McuType_SinOneChip_SC92F8463B)

	//晶体时钟配置
	#define FocsClk 24000000
	
	//底层调用
	#include <intrins.h>
	
	
	//IO定义标准化	
	#include "soc\touch_92f8x6xb\SC92F846XB_C.H"

	//IO定义标准化	
	#include "soc\soc_core.h"

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
	
#elif (McuType==McuType_FremontMicroDevices_FT62F13||McuType==McuType_FremontMicroDevices_FT61F13)
	//晶体时钟配置
	#define FocsClk 16000000
	
	//IO定义标准化	
	#include "fmd\fmd_core.h"

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
	#endif

	//定时器时钟配置,时钟源为指令时钟,时钟周期为2T
	#if (ZD_TIMER0_CLKSET_DEFAULT==ZD_TIMER0_CLKSET_FSYS)
		#if (ZD_TIMER0_CLKPSASET_DEFAULT==ZD_TIMER0_CLKPSASET_DIV1)
			#define Ft0Clk FsysClk/2/1
		#elif (ZD_TIMER0_CLKPSASET_DEFAULT==ZD_TIMER0_CLKPSASET_DIV2)
			#define Ft0Clk FsysClk/2/2
		#elif (ZD_TIMER0_CLKPSASET_DEFAULT==ZD_TIMER0_CLKPSASET_DIV4)
			#define Ft0Clk FsysClk/2/4
		#elif (ZD_TIMER0_CLKPSASET_DEFAULT==ZD_TIMER0_CLKPSASET_DIV8)
			#define Ft0Clk FsysClk/2/8
		#elif (ZD_TIMER0_CLKPSASET_DEFAULT==ZD_TIMER0_CLKPSASET_DIV16)
			#define Ft0Clk FsysClk/2/16
		#elif (ZD_TIMER0_CLKPSASET_DEFAULT==ZD_TIMER0_CLKPSASET_DIV32)
			#define Ft0Clk FsysClk/2/32
		#elif (ZD_TIMER0_CLKPSASET_DEFAULT==ZD_TIMER0_CLKPSASET_DIV64)
			#define Ft0Clk FsysClk/2/64
		#elif (ZD_TIMER0_CLKPSASET_DEFAULT==ZD_TIMER0_CLKPSASET_DIV128)
			#define Ft0Clk FsysClk/2/128
		#elif (ZD_TIMER0_CLKPSASET_DEFAULT==ZD_TIMER0_CLKPSASET_DIV256)
			#define Ft0Clk FsysClk/2/256
		#endif

	#endif	



#elif (McuType==McuType_HD_HD68651)

	//晶体时钟配置
	#define FocsClk 16000000
	
	//IO定义标准化	
	#include "hd\hd_core.h"

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
	#endif

	//定时器时钟配置,时钟源为指令时钟,时钟周期为2T
	#if (ZD_TIMER0_CLKSET_DEFAULT==ZD_TIMER0_CLKSET_FSYS)
		#if (ZD_TIMER0_CLKPSASET_DEFAULT==ZD_TIMER0_CLKPSASET_DIV1)
			#define Ft0Clk FsysClk/2/1
		#elif (ZD_TIMER0_CLKPSASET_DEFAULT==ZD_TIMER0_CLKPSASET_DIV2)
			#define Ft0Clk FsysClk/2/2
		#elif (ZD_TIMER0_CLKPSASET_DEFAULT==ZD_TIMER0_CLKPSASET_DIV4)
			#define Ft0Clk FsysClk/2/4
		#elif (ZD_TIMER0_CLKPSASET_DEFAULT==ZD_TIMER0_CLKPSASET_DIV8)
			#define Ft0Clk FsysClk/2/8
		#elif (ZD_TIMER0_CLKPSASET_DEFAULT==ZD_TIMER0_CLKPSASET_DIV16)
			#define Ft0Clk FsysClk/2/16
		#elif (ZD_TIMER0_CLKPSASET_DEFAULT==ZD_TIMER0_CLKPSASET_DIV32)
			#define Ft0Clk FsysClk/2/32
		#elif (ZD_TIMER0_CLKPSASET_DEFAULT==ZD_TIMER0_CLKPSASET_DIV64)
			#define Ft0Clk FsysClk/2/64
		#elif (ZD_TIMER0_CLKPSASET_DEFAULT==ZD_TIMER0_CLKPSASET_DIV128)
			#define Ft0Clk FsysClk/2/128
		#elif (ZD_TIMER0_CLKPSASET_DEFAULT==ZD_TIMER0_CLKPSASET_DIV256)
			#define Ft0Clk FsysClk/2/256
		#endif

	#endif	

#elif (McuType==McuType_BydMicro_BF7512)

	//晶体时钟配置
	#define FocsClk 48000000
	
	//IO定义标准化	
	#include "byd\byd_core.h"

	//系统时钟
	#if (ZD_FSYS_CLKSET_DEFAULT==ZD_FSYS_CLKSET_FOSC_DIV2_DIV2)
		#define FsysClk FocsClk/4
	#elif (ZD_FSYS_CLKSET_DEFAULT==ZD_FSYS_CLKSET_FOSC_DIV2_DIV4)
		#define FsysClk FocsClk/8
	#elif (ZD_FSYS_CLKSET_DEFAULT==ZD_FSYS_CLKSET_FOSC_DIV2_DIV6)
		#define FsysClk FocsClk/12
	#elif (ZD_FSYS_CLKSET_DEFAULT==ZD_FSYS_CLKSET_FOSC_DIV2_DIV24)
		#define FsysClk FocsClk/48
	#endif


#elif (McuType==McuType_Unkonw)

#endif










#endif