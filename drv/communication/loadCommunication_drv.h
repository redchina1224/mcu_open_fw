#ifndef __LOADCOMMUNICATION_DRV_H_
#define __LOADCOMMUNICATION_DRV_H_

	//载入通讯接口

	#if ((CommunicationType&CommunicationType_OneWire)==CommunicationType_OneWire)
		#if ((CommunicationTypeOneWireModel&CommunicationType_OneWire_DengProtocol)==CommunicationType_OneWire_DengProtocol)	
			#include "onewire\dengprotocol\onewire_dengprotocol_drv.h"
		#endif
	#endif


	#if ((CommunicationType&CommunicationType_Infrared)==CommunicationType_Infrared)
		#if ((CommunicationTypeInfraredModel&CommunicationType_Infrared_NecProtocol)==CommunicationType_Infrared_NecProtocol)	
			#include "infrared\necprotocol\infrared_necprotocol_drv.h"
		#endif
	#endif


	#if ((CommunicationType&CommunicationType_Uart)==CommunicationType_Uart)
		#if ((CommunicationTypeUartModel&CommunicationType_Uart_PreambleCode)==CommunicationType_Uart_PreambleCode) 
			#include "uart\uart_precode_protocol_drv.h"
		#endif
		#if ((CommunicationTypeUartModel&CommunicationType_Uart_FixedLength)==CommunicationType_Uart_FixedLength) 
			#include "uart\fixed_length\uart_fixed_length_drv.h"
		#endif
		#if ((CommunicationTypeUartModel&CommunicationType_Uart_HaierUplus)==CommunicationType_Uart_HaierUplus)
			#include "uart\haier_uplus\uart_haier_uplus_drv.h"
		#endif
	#endif

	#if ((CommunicationType&CommunicationType_I2C)==CommunicationType_I2C)
		#if ((CommunicationTypeI2cModel&CommunicationType_I2C_SoftI2C)==CommunicationType_I2C_SoftI2C)	
			#include "i2c\softi2c\soft_i2c_drv.h"
		#endif
	#endif

#endif

