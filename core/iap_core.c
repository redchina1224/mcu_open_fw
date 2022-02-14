//******************************************************************************
//Copyright(C) 2020-2021 zhejiang zhida dianzikeji Co., Ltd
//�㽭�Ǵ���ӿƼ����޹�˾
//File name:      zd_adc.c
//Author:         zzg
//Version:        Ver0.1
//Date:           2021-4-25
//Description:    IAP����д��
//History:
//******************************************************************************
//ͷ�ļ�************************************************************************
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
	
	ZD_GIE(ZD_GIE_DISABLE);  //�ж���������
	
	
	ZD_IAP_DATAAREA_EEPROM;  //IAPArea=0x00��ѡ��ROM������  IAPArea=0x02��ѡ��EEPROM������

#if ((McuType==McuType_SinOneChip_SC92F8463B))
	dat = *(IapAddr+addr);//ZD_IAP_DATAREAD(addr); //��ȡ������
#else
	ZD_IAP_DATAREAD(addr);
	Iap_DelayUs(2);
	dat =ZD_IAP_DATA;
#endif
	

	
	
	ZD_IAP_END;      //MOVCָ��ROM
	
	
	ZD_GIE(ZD_GIE_ENABLE); //�ж���������
	
	
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
	
	//���ж�
	ZD_GIE(ZD_GIE_DISABLE);  //�ж���������
	
	ZD_IAP_WRITEDATA_SET(dat);      //д������Data
	
	ZD_IAP_WRITEADDR_SET(addr);  //д���ַ
	
	ZD_IAP_DATAAREA_EEPROM;  //IAPArea=0x00��ѡ��ROM������  IAPArea=0x02��ѡ��EEPROM������
	
	ZD_IAP_WRITE_START;

	Iap_DelayUs(8);
	
	ZD_IAP_END;      //MOVCָ��ROM

	ZD_GIE(ZD_GIE_ENABLE); //�ж���������
		
}

/*----------------------------
Erase one sector area
Input: addr (ISP/IAP/EEPROM address)
Output:-
----------------------------*/
//void IapEraseSector(WORD addr)
//{

//}

