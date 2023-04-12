#ifndef __DEFINECOMMUNICATION_DRV_H_
#define __DEFINECOMMUNICATION_DRV_H_

	//定义可选型号清单
	//定义可选型号清单
	#define CommunicationType_Unkonw 0

	#define CommunicationType_OneWire 0x010000
	#define CommunicationType_OneWire_DengProtocol (CommunicationType_OneWire +BIT0)

	#define CommunicationType_Uart 0x020000
	#define CommunicationType_Uart_PreambleCode (CommunicationType_Uart +BIT0)
	#define CommunicationType_Uart_FixLength (CommunicationType_Uart +BIT1)

	#define CommunicationType_Uart_HaierUplus (CommunicationType_Uart +BIT7)

#endif