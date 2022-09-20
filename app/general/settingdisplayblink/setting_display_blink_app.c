//******************************************************************************
//Copyright(C) 2020-2021 zhejiang zhida dianzikeji Co., Ltd
//浙江智达电子科技有限公司
//File name:      setting_display_blink_app.c
//Author:         zzg
//Version:        Ver0.1
//Date:           2021-4-25
//Description:    设置闪烁显示与超时退出功能。
//History:
//******************************************************************************

#include "..\..\com_include_app.h"

unsigned char settingDisplayBlink(struct  zd_setting_display_blink_t* setting )
{

		if(setting->exitTimeOut_x100ms>0) setting->exitTimeOut_x100ms--;//超时自动退出
		else
		{
			return 0;
		}


		if(setting->blinkTimeOut_x100ms>0) setting->blinkTimeOut_x100ms--;//当前时间大于前次设置的闪烁结束时间后触发一次切换
		else
		{
			if(setting->Bits.blinkDisplayEn==0)//闪烁时是否显示或熄屏的标志
			{
				setting->Bits.blinkDisplayEn=1;//闪烁时是否显示或熄屏的标志,置1后，下次切换为熄屏
			}
			else
			{			
				setting->Bits.blinkDisplayEn=0;//闪烁时是否显示或熄屏的标志,置0后，下次切换为显示
			}
			setting->blinkTimeOut_x100ms=5;
		}



		return 1;





}

void settingDisplayBlink_Start(struct  zd_setting_display_blink_t* setting,unsigned char exitTimeSet_x100ms)
{
	setting->blinkTimeOut_x100ms=0;//单次闪烁计时,置0后，立即执行一次切换操作
	setting->Bits.blinkDisplayEn=0;//闪烁时是否显示或熄屏的标志,置0后，下次切换为显示
	setting->exitTimeOut_x100ms=exitTimeSet_x100ms-2; //闪烁5秒，时间采用4.8秒，使最后一次为熄灭状态，避免最后一次先点亮后再切换;
}




