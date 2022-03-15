#ifndef __SENSOR_DRV_H_
#define __SENSOR_DRV_H_

struct  zd_sensor_t {
 unsigned char SensorStatus;
 unsigned char TriggerFilterCnt;
 unsigned char TriggerStatus;
};

void zd_sensorCheck(struct zd_sensor_t* sen,unsigned char chkmax,unsigned char chkmin);

#endif

