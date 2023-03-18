#ifndef __DEFINEDISPLAY_BSP_H_
#define __DEFINEDISPLAY_BSP_H_

	//定义可选型号清单
	//定义可选型号清单
	#define DisplayType_Unkonw 0

	#define DisplayType_SoftLed 0x010000
	#define DisplayType_SoftLed_Dig8WithKeys (DisplayType_SoftLed+BIT0)
	#define DisplayType_SoftLed_Dig8_Bidir (DisplayType_SoftLed+BIT1)
	#define DisplayType_SoftLed_Dig8 (DisplayType_SoftLed+BIT2)
	#define DisplayType_SoftLed_Bits (DisplayType_SoftLed+BIT3)

	#define DisplayType_SoftLcd 0x020000
	#define DisplayType_SoftLcd_Dig8 (DisplayType_SoftLcd+BIT2)


	#define DisplayType_IcLed 0x040000
	#define DisplayType_IcLed_tm1628 (DisplayType_IcLed+BIT0)
	#define DisplayType_IcLed_tm1640 (DisplayType_IcLed+BIT1)
	#define DisplayType_IcLed_tm1650 (DisplayType_IcLed+BIT2)
	//#define DisplayType_Dig8IcLed_tm1628 (DisplayType_IcLed+BIT0)

	#define DisplayType_IcLcd 0x080000
	#define DisplayType_IcLcd_tm1621c (DisplayType_IcLcd+BIT0)
	//#define DisplayType_Dig8IcLcd_tm1621c (DisplayType_IcLcd+BIT0)

#endif