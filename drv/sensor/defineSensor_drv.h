#ifndef __DEFINE_SENSOR_DRV_H_
#define __DEFINE_SENSOR_DRV_H_

	//定义可选型号清单
	#define SensorType_Unkonw 0

	#define SensorType_Temperature 0x010000
	#define SensorType_Temperature_Ntc (SensorType_Temperature + BIT0)

	#define SensorType_Humidity 0x020000
	#define SensorType_Humidity_Res (SensorType_Humidity + BIT0)

	#define SensorType_Temperature_Humidity 0x040000
	#define SensorType_Temperature_Humidity_Aht10 (SensorType_Temperature_Humidity + BIT0)

#endif