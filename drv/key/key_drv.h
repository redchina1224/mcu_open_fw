//******************************************************************************
//Copyright(C) 2020-2021 zhejiang zhida dianzikeji Co., Ltd
//浙江智达电子科技有限公司
//File name:      key.h
//Author:         zzg
//Version:        Ver0.1
//Date:           2021-4-25
//Description:    按键
//History:
//******************************************************************************
#ifndef __KEY_DRV_H__
#define __KEY_DRV_H__

#ifdef KeyType
extern unsigned char KeyQuickPressCount;
extern unsigned int KeyLongPressCount;
extern unsigned long KeyVal;
extern unsigned long UserKeyVal;
extern bit UserKeyPressed;
extern bit UserKeyLongPressed;
extern bit UserKeyPressed_down;
extern bit UserKeyPressed_up;


//声明外部函数******************************************************************
void zd_key_init(void);
void zd_key_clear(void);
void zd_keyRun(void);

#endif


#endif 


/************************ (C) COPYRIGHT zhejiang zhida *****END OF FILE****/