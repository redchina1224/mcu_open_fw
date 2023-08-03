//******************************************************************************
//Copyright(C) 2020-2021 zhejiang zhida dianzikeji Co., Ltd
//浙江智达电子科技有限公司
//File name:      variable.h
//Author:         zzg
//Version:        Ver0.1
//Date:           2021-4-25
//Description:    全局头文件调用/全局宏定义声明/全局变量声明
//History:
//******************************************************************************
#ifndef __TM1650_DRV_H__
#define __TM1650_DRV_H__

extern unsigned char *Tm1650_WriteBuffer;


void tm1650_init(void);
void tm1650_SendDataRun(void);
void tm1650_set_bright(unsigned char bright);


#endif