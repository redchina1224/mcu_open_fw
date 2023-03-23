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
#ifndef __USER_TIME_H__
#define __USER_TIME_H__
//声明外部函数******************************************************************


/***********************************************************************************************
*函数名 		: void zd_timerInit(unsigned char timerChannel)
*函数功能描述 	: 初始化定时器
*函数参数 		: unsigned char timerChannel:定时器号,
				  unsigned long _Us：定时器时间
*函数返回值 	: 无
***********************************************************************************************/
void mof_timerInit(unsigned char timerChannel);


#endif 


/************************ (C) COPYRIGHT zhejiang zhida *****END OF FILE****/