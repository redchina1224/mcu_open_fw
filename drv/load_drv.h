#ifndef __LOADDRV_H_
#define __LOADDRV_H_

	//载入时钟计时系统
	#ifdef RtcType
	#include "rtc\loadRtc_drv.h" //载入时钟系统驱动接口信息
	#endif

	//载入NTC传感器系统
	#ifdef NtcType
		#include "ntc\loadNtcRes_drv.h"
		#include "ntc\ntc_sensor.h"
	#endif

	//载入显示系统
	#ifdef DisplayType
		#include "display\loadDisplay_drv.h" //载入显示系统驱动接口信息
	#endif
	
	
	//载入蜂鸣系统
	#ifdef BuzzerType
		#include "buzzer\loadBuzzer_drv.h" //载入显示系统驱动接口信息
	#endif


	//载入按键系统
	#ifdef KeyType
		#include "key\loadKey_drv.h" //载入显示系统驱动接口信息
	#endif


	//载入电机系统
	#ifdef MotorType
		#include "motor\loadMotor_drv.h" //载入显示系统驱动接口信息
	#endif

	#include "interrupt\interrupt_drv.h" //载入中断服务接口信息

#endif

