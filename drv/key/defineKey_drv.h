#ifndef __DEFINEKEY_BSP_H_
#define __DEFINEKEY_BSP_H_

	//定义可选蜂鸣器清单
	#define KeyType_Unkonw 0
	#define KeyType_Gpio BIT0 //直接IO
	#define KeyType_McuTouch BIT1 //触摸按键
	#define KeyType_Touch BIT2 //触摸按键
	#define KeyType_IR BIT3 //红外编码
	#define KeyType_RF BIT4 //红外编码
	#define KeyType_SoftLedWithGpio BIT5 //与软件LED驱动共用的直接IO

	#define KeyType_USER BIT24

	#define KeyType_MultiChannel BIT31 //多通道使能

#endif