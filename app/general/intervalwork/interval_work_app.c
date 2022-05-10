//******************************************************************************
//Copyright(C) 2020-2021 zhejiang zhida dianzikeji Co., Ltd
//浙江智达电子科技有限公司
//File name:      setting_display_blink_app.c
//Author:         zzg
//Version:        Ver0.1
//Date:           2021-4-25
//Description:    设置间隔工作功能。
//History:
//******************************************************************************

#include "..\..\com_include_app.h"

void intervalWorkRun(struct  zd_interval_work_t* work)
{


		if(work->intervalTimeOut_x100ms>0) work->intervalTimeOut_x100ms--;//
		else
		{
			if(work->intervalWorkEn==0)//
			{

				work->intervalTimeOut_x100ms=work->intervalTimeOut_En_x100ms;

				work->intervalWorkEn=1;//
			}
			else
			{
				work->intervalTimeOut_x100ms=work->intervalTimeOut_Dis_x100ms;
				work->intervalWorkEn=0;//
			}

		}

}

void intervalWorkRun_Start(struct  zd_interval_work_t* work,unsigned int En_mSec,unsigned int Dis_mSec)
{
	work->intervalWorkEn=0;//单次闪烁计时,置0后，立即执行一次切换操作
	work->intervalTimeOut_x100ms=0;
	work->intervalTimeOut_En_x100ms=En_mSec;
	work->intervalTimeOut_Dis_x100ms=Dis_mSec;
}




