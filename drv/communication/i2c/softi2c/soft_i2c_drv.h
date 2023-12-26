#ifndef __SOFTI2C_DRV_H_
#define __SOFTI2C_DRV_H_
#ifdef CommunicationTypeI2cModel
#if ((CommunicationTypeI2cModel&CommunicationType_I2C_SoftI2C)==CommunicationType_I2C_SoftI2C)

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
#endif
#endif

