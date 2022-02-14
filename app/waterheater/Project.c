#include ".\CTK_Library\Config.h"

/****************************************************************/
//函数名：void Project(void)
//功  能：项目项目功能函数
//参  数：无
//返回值：无
/****************************************************************/
void Project(void)//范例
{
	
	time_process();					//时基处理
	
	//1ms执行程序
	if(gucv_time_1ms>0)
	{
		gucv_time_1ms--;
		updatadisbuff();			//刷新显示缓存
		buzzer_process();			//蜂鸣器处理
		function_process();		//工作控制
		key_process();				//按键处理
		key_scan();						//按键扫描
		adc_process();				//ADC采集处理
	}
}