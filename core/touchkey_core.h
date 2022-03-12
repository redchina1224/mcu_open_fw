//******************************************************************************
//Copyright(C) 2020-2021 zhejiang zhida dianzikeji Co., Ltd
//浙江智达电子科技有限公司
//File name:      user_time.h
//Author:         zzg
//Version:        Ver0.1
//Date:           2021-4-25
//Description:    TIME时间处理
//History:
//******************************************************************************
#ifndef __TOUCHKEY_CORE_H__
#define __TOUCHKEY_CORE_H__
#ifdef KeyType
#if((KeyType&KeyType_McuTouch)==KeyType_McuTouch)


#if(McuType==McuType_CmsSemicon_CMS79F738)

#elif(McuType==McuType_FremontMicroDevices_FT62F13)
	#include "fmd\FT62F13X\Touch_Kscan_Library.h"
#endif



/***********************************************************************************************
*函数名 		: void zd_touchkeyInit(void)
*函数功能描述 	: 初始化触摸按键
*函数参数 		: 无
*函数返回值 	: 无
***********************************************************************************************/
void zd_touchkeyInit(void);


/***********************************************************************************************
*函数名 		: unsigned long zd_touchkeyRead(void)
*函数功能描述 	: 初始化触摸按键
*函数参数 		: unsigned long *keyval ：按键值地址指针
*函数返回值 	: unsigned char  按键值状态  1：键值有更新  0：键值无更新
***********************************************************************************************/
unsigned char zd_touchkeyRead(unsigned long *keyval);

#endif  //#if((KeyType&KeyType_McuTouch)==KeyType_McuTouch)
#endif  //#ifdef KeyType
#endif  //#ifndef __TOUCHKEY_CORE_H__


/************************ (C) COPYRIGHT zhejiang zhida *****END OF FILE****/