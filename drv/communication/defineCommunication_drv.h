#ifndef __DEFINECOMMUNICATION_DRV_H_
#define __DEFINECOMMUNICATION_DRV_H_

	//定义可选型号清单
	//定义可选型号清单
	#define CommunicationType_Unkonw 0

	#define CommunicationType_OneWire 0x010000
	#define CommunicationType_OneWire_DengProtocol (CommunicationType_OneWire +BIT0)

	#define CommunicationType_Infrared 0x080000
	#define CommunicationType_Infrared_NecProtocol (CommunicationType_Infrared +BIT0)

	#define CommunicationType_Uart 0x020000
	#define CommunicationType_Uart_PreambleCode (CommunicationType_Uart +BIT0)
	#define CommunicationType_Uart_FixedLength (CommunicationType_Uart +BIT1)
	#define CommunicationType_Uart_HaierUplus (CommunicationType_Uart +BIT7)

	#define CommunicationType_I2C 0x040000
	#define CommunicationType_I2C_SoftI2C (CommunicationType_I2C +BIT0)

#endif