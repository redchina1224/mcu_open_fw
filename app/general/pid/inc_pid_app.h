//******************************************************************************
//Copyright(C) 2020-2021 zhejiang zhida dianzikeji Co., Ltd
//浙江智达电子科技有限公司
//File name:      function.h
//Author:         zzg
//Version:        Ver0.1
//Date:           2021-4-25
//Description:    功能
//History:
//******************************************************************************
#ifndef __APPSTDLIB_INC_PID_H__
#define __APPSTDLIB_INC_PID_H__
//******************************************************************

struct  zd_incpid_t {
signed int error;
signed int error_last;
signed int error_prev;
signed int target;
signed int current;
signed int proportion;
signed int derivative;
signed int out;
};



void zd_incpid_init(struct zd_incpid_t *pid);
void zd_incpid_run(struct zd_incpid_t *pid);

#endif 


/************************ (C) COPYRIGHT zhejiang zhida *****END OF FILE****/