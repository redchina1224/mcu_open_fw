#ifndef __MODBUSLAVE_H_
#define __MODBUSLAVE_H_

#include<Bsp.h>

extern bit ComError;
extern xdata unsigned char ComLedFlashDelay;

bit Wifi_ModbusBusy(void);

void ModbusSlaveInit(void);

bit Wifi_ModbusSlaveTask(void);

#ifdef BoardTypeB
bit Main_ModbusSlaveTask(void);
bit Device_ModbusSlaveTask(void);
#endif

void ModbusMasterSend(unsigned char reg);

#endif