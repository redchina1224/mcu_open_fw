#ifndef __SENSOR_AHT10_DRV_H__
#define __SENSOR_AHT10_DRV_H__

typedef struct
{
unsigned int temperature;
unsigned int humidity;
unsigned long ahtUtcSec;
} mof_sensor_aht10_t;

extern mof_sensor_aht10_t sensor_aht10;

void mof_sensor_aht10_Init(void);
unsigned char mof_sensor_aht10_Read_CTdata(void);

#endif