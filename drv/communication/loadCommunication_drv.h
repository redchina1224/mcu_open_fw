#ifndef __LOADCOMMUNICATION_DRV_H_
#define __LOADCOMMUNICATION_DRV_H_

	//载入通讯接口

	#if ((CommunicationType&CommunicationType_OneWire)==CommunicationType_OneWire)
		#if ((CommunicationTypeOneWireModel&CommunicationType_OneWire_DengProtocol)==CommunicationType_OneWire_DengProtocol)	
			#include "onewire\dengprotocol\onewire_dengprotocol_drv.h"
		#endif
	#endif

	#if ((CommunicationType&CommunicationType_Uart)==CommunicationType_Uart)
		#if ((CommunicationTypeUartModel&CommunicationType_Uart_PreambleCode)==CommunicationType_Uart_PreambleCode) 
			#include "uart\uart_precode_protocol_drv.h"
		#elif ((CommunicationTypeUartModel&CommunicationType_Uart_FixLength )==CommunicationType_Uart_FixLength ) 
			#include "uart\haier_uplus\uart_fix_length_drv.h"
		#elif ((CommunicationTypeUartModel&CommunicationType_Uart_HaierUplus)==CommunicationType_Uart_HaierUplus)
			#include "uart\haier_uplus\uart_haier_uplus_drv.h"
		#endif
	#endif


#endif

