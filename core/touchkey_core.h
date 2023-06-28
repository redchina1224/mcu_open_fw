//******************************************************************************
//Copyright(C) 2020-2021 zhejiang zhida dianzikeji Co., Ltd
//�㽭�Ǵ���ӿƼ����޹�˾
//File name:      user_time.h
//Author:         zzg
//Version:        Ver0.1
//Date:           2021-4-25
//Description:    TIMEʱ�䴦��
//History:
//******************************************************************************
#ifndef __TOUCHKEY_CORE_H__
#define __TOUCHKEY_CORE_H__
#ifdef KeyType
#if((KeyType&KeyType_McuTouch)==KeyType_McuTouch)


//#if(McuType==McuType_CmsSemicon_CMS79F738)

//#elif(McuType==McuType_FremontMicroDevices_FT62F13)
//	#include "fmd\FT62F13X\Touch_Kscan_Library.h"
//#endif



/***********************************************************************************************
*������ 		: void mof_touchkeyInit(void)
*������������ 	: ��ʼ����������
*�������� 		: ��
*��������ֵ 	: ��
***********************************************************************************************/
void mof_touchkeyInit(void);


/***********************************************************************************************
*������ 		: unsigned long mof_touchkeyRead(void)
*������������ 	: ��ʼ����������
*�������� 		: unsigned long *keyval ������ֵ��ַָ��
*��������ֵ 	: unsigned char  ����ֵ״̬  1����ֵ�и���  0����ֵ�޸���
***********************************************************************************************/
unsigned char mof_touchkeyRead(unsigned long *keyval);

#endif  //#if((KeyType&KeyType_McuTouch)==KeyType_McuTouch)
#endif  //#ifdef KeyType
#endif  //#ifndef __TOUCHKEY_CORE_H__


/************************ (C) COPYRIGHT zhejiang zhida *****END OF FILE****/