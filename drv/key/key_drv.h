//******************************************************************************
//Copyright(C) 2020-2021 zhejiang zhida dianzikeji Co., Ltd
//�㽭�Ǵ���ӿƼ����޹�˾
//File name:      key.h
//Author:         zzg
//Version:        Ver0.1
//Date:           2021-4-25
//Description:    ����
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


//�����ⲿ����******************************************************************
void zd_key_init(void);
void zd_key_clear(void);
void zd_keyRun(void);

#endif


#endif 


/************************ (C) COPYRIGHT zhejiang zhida *****END OF FILE****/