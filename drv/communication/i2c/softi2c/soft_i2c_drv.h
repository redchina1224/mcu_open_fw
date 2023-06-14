#ifndef __SOFTI2C_DRV_H_
#define __SOFTI2C_DRV_H_

void I2C_Init(void);
void I2C_Start(void);
void I2C_Stop(void);
void I2C_SendByte(unsigned char dat);
unsigned char I2C_ReadByte(void);
void I2C_Ack(void);
void I2C_NoAck(void);
unsigned char I2C_WaitToAck(void);
void I2C_Delay(void);

#endif

