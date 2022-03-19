//******************************************************************************
//Copyright(C) 2020-2021 zhejiang zhida dianzikeji Co., Ltd
//�㽭�Ǵ���ӿƼ����޹�˾
//File name:      function.h
//Author:         zzg
//Version:        Ver0.1
//Date:           2021-4-25
//Description:    ����
//History:
//******************************************************************************
#ifndef __APPSTDLIB_POSITION_PID_H__
#define __APPSTDLIB_POSITION_PID_H__
//******************************************************************

struct  zd_pospid_t {
signed int error;
signed int error_last;
signed int error_prev;
signed int target;
signed int current;
signed int integral;
signed int derivative;
signed int out;
};



void zd_pospid_init(struct zd_pospid_t *pid);
void zd_pospid_run(struct zd_pospid_t *pid);

#endif 


/************************ (C) COPYRIGHT zhejiang zhida *****END OF FILE****/