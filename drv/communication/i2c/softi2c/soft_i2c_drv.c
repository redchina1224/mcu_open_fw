
#include "..\..\..\com_include_drv.h"


#define I2C_SDA_High()  SOFTI2C_SDA=1
#define I2C_SDA_Low()   SOFTI2C_SDA=0
#define I2C_SCL_High() SOFTI2C_SCL=1
#define I2C_SCL_Low() SOFTI2C_SCL=0

#define I2C_SDA_READ() SOFTI2C_SDA

void I2C_Init(void)
{
	SOFTI2C_SDA_OUT_OD;
	SOFTI2C_SCL_OUT_OD;
	SOFTI2C_SDA=1;
	SOFTI2C_SCL=1;
}


void I2C_Delay(void)
{
	
    int i;

    for (i=0; i<30; i++)
    {
        MOF_NOP;
        MOF_NOP;
        MOF_NOP;
        MOF_NOP;
    }
}


void I2C_Start(void)
{
    I2C_SDA_High();     //SDA=1
    I2C_SCL_High();     //SCL=1
    I2C_Delay();
    I2C_SDA_Low();
    I2C_Delay();
    I2C_SCL_Low();
    I2C_Delay();
}


void I2C_Stop(void)
{
    I2C_SDA_Low();
    I2C_SCL_High();
    I2C_Delay();
    I2C_SDA_High();
    I2C_Delay();
}


void I2C_SendByte(unsigned char dat)
{
    unsigned char i;
 
    /* 先发送高位字节 */
    for(i = 0 ; i < 8 ; i++)
    {
        if(dat & 0x80)
        {
            I2C_SDA_High();
        }
        else
        {
            I2C_SDA_Low();
        }
        I2C_Delay();
        I2C_SCL_High();
        I2C_Delay();
        I2C_SCL_Low();
        I2C_Delay();
 
        if(i == 7)
        {
            I2C_SDA_High();                     /* 释放SDA总线 */
        }
        dat <<= 1;                             /* 左移一位  */
 
        I2C_Delay();
    }
}


unsigned char I2C_ReadByte(void)
{
    unsigned char i;
    unsigned char value;
 
    /* 先读取最高位即bit7 */
    value = 0;
    for(i = 0 ; i < 8 ; i++)
    {
        value <<= 1;
        I2C_SCL_High();
        I2C_Delay();
        if(I2C_SDA_READ())
        {
            value++;
        }
        I2C_SCL_Low();
        I2C_Delay();
    }
 
    return value;
}


void I2C_Ack(void)
{
    I2C_SDA_Low();
    I2C_Delay();
    I2C_SCL_High();
    I2C_Delay();
    I2C_SCL_Low();
    I2C_Delay();
 
    I2C_SDA_High();
}

void I2C_NoAck(void)
{
    I2C_SDA_High();
    I2C_Delay();
    I2C_SCL_High();
    I2C_Delay();
    I2C_SCL_Low();
    I2C_Delay();
}


unsigned char I2C_WaitToAck(void)
{
    unsigned char redata;
 
    I2C_SDA_High();
    I2C_Delay();
    I2C_SCL_High();
    I2C_Delay();
 
    if(I2C_SDA_READ())
    {
        redata = 1;
    }
    else
    {
        redata = 0;
    }
    I2C_SCL_Low();
    I2C_Delay();
 
    return redata;
}  







