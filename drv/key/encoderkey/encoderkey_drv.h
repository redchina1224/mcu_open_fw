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
#ifndef __ENCODERKEY_DRV_H__
#define __ENCODERKEY_DRV_H__


typedef struct
{
unsigned char key_cw_clr_flag;
unsigned char key_ccw_clr_flag;
unsigned char key_cw_user_data;
unsigned char key_ccw_user_data;
unsigned char key_cw_data;
unsigned char key_ccw_data;
unsigned char code_value;
unsigned char code_value_ago;
unsigned char code_value_serial;
	
} mof_encoder_key_t;

void mof_encoder_key_init(void);

void mof_encoder_key_in_isr(void);

void mof_encoder_key_read(void);

void mof_encoder_key_clear(void);
	
extern mof_encoder_key_t xdata encoder_key[ONEWIRE_DENG_TOTAL_NUM];
extern unsigned char xdata encoder_key_value;
extern unsigned char xdata encoder_key_data;

#endif 


/************************ (C) COPYRIGHT zhejiang zhida *****END OF FILE****/