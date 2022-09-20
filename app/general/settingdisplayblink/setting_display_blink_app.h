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
#ifndef __APPSTDLIB_SETTING_DISPALY_BLINK_APP_H__
#define __APPSTDLIB_SETTING_DISPALY_BLINK_APP_H__
//******************************************************************

struct  zd_setting_display_blink_t {
	struct {
		unsigned char blinkDisplayEn:1;
		unsigned char inSetting1:1;
		unsigned char inSetting2:1;
		unsigned char inSetting3:1;	
		unsigned char inSetting4:1;
		unsigned char inSetting5:1;
		unsigned char inSetting6:1;
		unsigned char inSetting7:1;		
	}Bits;
unsigned char exitTimeOut_x100ms;
unsigned char blinkTimeOut_x100ms;
};



unsigned char settingDisplayBlink(struct  zd_setting_display_blink_t* setting );
void settingDisplayBlink_Start(struct  zd_setting_display_blink_t* setting,unsigned char exitTimeSet_x100ms);

#endif 



//使用示例
/*

			//触发设置和在设置过程中
			if(按键触发)
			{
				setting.Bits.inSetting1=1;
				settingDisplayBlink_Start(&setting,50);//进入设置态,超时退出时间设置为50x100ms
			}


			//显示内容与超时自动保存
			if(setting.inSetting1!=0)//在设置状态
			{
				if(100ms执行一次标志)
				{

					if(settingDisplayBlink(&setting))//为1时未超时显示内容
					{
						if(setting.blinkDisplayEn==1)//闪烁时是否显示或熄屏的标志
						{
							//显示设置内容
						}
						else
						{			
							//显示熄屏
						}
					}
					else//为0时，设置时间超时
					{
						//保存设置数据
					
						//清除设置标志位
						setting.inSetting1=0;
					}
				}


			}
			else//不在设置状态
			{
				//显示非设置态的内容
			}



*/










/************************ (C) COPYRIGHT zhejiang zhida *****END OF FILE****/