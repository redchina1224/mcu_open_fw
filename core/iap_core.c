//******************************************************************************
//Copyright(C) 2020-2021 zhejiang zhida dianzikeji Co., Ltd
//浙江智达电子科技有限公司
//File name:      zd_adc.c
//Author:         zzg
//Version:        Ver0.1
//Date:           2021-4-25
//Description:    IAP数据写入
//History:
//******************************************************************************
//头文件************************************************************************
#include "com_include_core.h"

#define Iap_DelayUs core_DelayUs 


#if ((McuType==McuType_SinOneChip_SC92F8463B))
unsigned char code *IapAddr = 0x00;
#endif

/*----------------------------
Read one byte from ISP/IAP/EEPROM area
Input: addr (ISP/IAP/EEPROM address)
Output:Flash data
----------------------------*/
BYTE IapReadByte(WORD addr)
{
    BYTE dat;                       //Data buffer
	BYTE gie_buf=ZD_GIE;
	
	ZD_GIE_DISABLE;  //中断总允许开关
	
	
	ZD_IAP_DATAAREA_EEPROM;  //IAPArea=0x00：选择ROM区操作  IAPArea=0x02：选择EEPROM区操作

#if ((McuType==McuType_SinOneChip_SC92F8463B))
	dat = *(IapAddr+addr);//ZD_IAP_DATAREAD(addr); //读取的数据
#else
	ZD_IAP_DATAREAD(addr);
	Iap_DelayUs(2);
	dat =ZD_IAP_DATA;
#endif
	

	
	
	ZD_IAP_END;      //MOVC指向ROM
	
	
	if(gie_buf!=0) ZD_GIE_ENABLE; //中断总允许开关
	
	
    return dat;                     //Return Flash data
	
}

/*----------------------------
Program one byte to ISP/IAP/EEPROM area
Input: addr (ISP/IAP/EEPROM address)
       dat (ISP/IAP/EEPROM data)
Output:-
----------------------------*/
void IapProgramByte(WORD addr, BYTE dat)
{
	BYTE gie_buf=ZD_GIE;
	//关中断
	ZD_GIE_DISABLE;  //中断总允许开关
	
	ZD_IAP_WRITEDATA_SET(dat);      //写入数据Data
	
	ZD_IAP_WRITEADDR_SET(addr);  //写入地址
	
	ZD_IAP_DATAAREA_EEPROM;  //IAPArea=0x00：选择ROM区操作  IAPArea=0x02：选择EEPROM区操作
	
	ZD_IAP_WRITE_START;
	
	Iap_DelayUs(8);
	while(ZD_IAP_WRITE_NOT_OVER);
	
	ZD_IAP_END;      //MOVC指向ROM

	if(gie_buf!=0) ZD_GIE_ENABLE; //中断总允许开关
		
}

/*----------------------------
Erase one sector area
Input: addr (ISP/IAP/EEPROM address)
Output:-
----------------------------*/
//void IapEraseSector(WORD addr)
//{

//}

