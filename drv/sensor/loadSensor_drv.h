#ifndef __LOADSENSOR_DRV_H_
#define __LOADSENSOR_DRV_H_

	//载入传感器检测接口
//	#if ((SensorType&SensorType_Temperature)==SensorType_Temperature)

//	#endif

//	#if ((SensorType&SensorType_Humidity)==SensorType_Humidity)

//	#endif

	#if ((SensorType&SensorType_Temperature_Humidity)==SensorType_Temperature_Humidity)
		#if ((SensorType_Temperature_Humidity_Model&SensorType_Temperature_Humidity_Aht10)==SensorType_Temperature_Humidity_Aht10)	
			#include "temperature_humidity\aht10\sensor_aht10_drv.h"
		#endif
	#endif

#endif