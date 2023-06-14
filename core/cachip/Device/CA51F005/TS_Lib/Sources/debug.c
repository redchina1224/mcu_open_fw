#ifndef _I2C_C_
#define _I2C_C_

/*********************************************************************************************************************/
#include "ca51f_config.h"
#include "includes\CA51F005SFR.h"
#include "includes\CA51F005XSFR.h"
#include "includes\gpiodef.h"

#include "Library\Includes\system_clock.h"		
/*********************************************************************************************************************/
#include "TS_Lib\Includes\ts_configuration.h"
#include "TS_Lib\Includes\ts_def.h"
#include "TS_Lib\Includes\ts_api.h"
#include "TS_Lib\Includes\ts_service.h"		   
#if DEBUG
#include "Library\Includes\i2c.h"		
void I2C_ISR(void);
#endif
/*********************************************************************************************************************/
#if DEBUG
#define I2C_ADDR		0xCA
unsigned char xdata TouchDebugID = '3';
unsigned char rxOffset;
unsigned char regAddr;
bit iicReadMode;
extern TSState_T 	  				xdata 	TS_State_Debug;
extern unsigned char 				xdata 	Key_Cnt_Debug;
extern unsigned char 				xdata 	TS_CH_Debug[OPENED_TS_COUNT];	
extern unsigned int  				xdata 	TS_RefChBaseLineData;
extern unsigned int 				xdata 	TS_RefPostData;
extern unsigned long int   xdata 	KeysFlagSN_Debug;
code unsigned char *TS_INFO[]=
{
	&TouchDebugID,
	&TS_State_Debug,
	&Key_Cnt_Debug,
	&TS_RefChBaseLineData,
	&TS_RefPostData,
	&KeysFlagSN_Debug,
	&TS_BaseLineData[0],
#if TOUCH_SENSITIVITY_AUTO_BALANCE_EN
	&TS_PostData2[0],
#else
	&TS_PostData[0],
#endif
	&TSKey_FingerThd[0],
	&TS_CH_Debug[0],
};
unsigned char *pTS_Info;
void I2C_ISR(void)
{
	unsigned char Sta_Temp;
	TouchDebugID = '3';				
	Sta_Temp = I2CSTA;			
	if(Sta_Temp == 0x60)			   //接收到从机地址+写位
	{			
		rxOffset = 0xff;
		iicReadMode = 0;
		I2CCON |= AAK(1);			
	}
	else if(Sta_Temp == 0x80)			   
	{					
		if(iicReadMode)	 				//发送一字节数据
		{
			rxOffset++;
			I2CDAT = *(pTS_Info+rxOffset);			
		}
		else									//接收到一字节数据
		{				
			if(rxOffset == 0xff) 		//地址
			{
				regAddr=I2CDAT;	 
				pTS_Info = TS_INFO[regAddr];
				rxOffset=0;
				I2CCON |= AAK(1);
			}
			else				   		//数据
			{
				*(pTS_Info+rxOffset) = I2CDAT;
				rxOffset++;	
				I2CCON |= AAK(1);		
			}
		}	
	}
	else if(Sta_Temp==0xA8)				//接收到从机地址+读位，发送ACK信号
	{								
		I2CDAT = *(pTS_Info+rxOffset);
		iicReadMode = 1;
	}
	else if(Sta_Temp == 0x88)	
	{
	}
	I2CFLG  |= I2CF;
}
void Debug_init(void)
{
#ifdef  I2C_SELECT_P06_P07
	I2CIOS = 0;
	GPIO_Init(P06F,P06_I2C_SDA_SETTING | PU_EN);
	GPIO_Init(P07F,P07_I2C_SCL_SETTING | PU_EN);
#elif defined I2C_SELECT_P16_P02
	I2CIOS = 1;
	GPIO_Init(P16F,P16_I2C_SDA_SETTING | PU_EN);
	GPIO_Init(P02F,P02_I2C_SCL_SETTING | PU_EN);
#elif defined I2C_SELECT_P13_P14
	I2CIOS = 2;
	GPIO_Init(P13F,P13_I2C_SCL_SETTING | PU_EN);
	GPIO_Init(P14F,P14_I2C_SDA_SETTING | PU_EN);
#endif
	
	I2CCON = I2CE(1) | I2CIE(1) | STA(0) | STP(0)| CKHD(0) | AAK(1)| CBSE(0) | STFE(0);		
	I2CADR = (I2C_ADDR>>1);
	I2CCR = 0x20;
	
	INT6EN = 1;
	EXIP |= (1<<4);			//优先级设置为最高
}
void Debug_ParamLoad(void)
{
	unsigned char i;
	KeysFlagSN_Debug = (unsigned long int)KeysFlagSN;
	TS_State_Debug = TS_State;
	Key_Cnt_Debug = KEY_CH_COUNT;
	for(i = 0; i < KEY_CH_COUNT; i++)
	{
		TS_CH_Debug[i] = TS_CH[i];
	}
	TS_RefPostData  = TS_PostData[OPENED_TS_COUNT];	
	TS_RefChBaseLineData  = TS_RefPostData;	
}
#endif
#endif
