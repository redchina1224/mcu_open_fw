#include "..\com_include_app.h"
  


void saveTempSetVal(void)
{
	IapProgramByte(0x0000,gucv_set_temp);
	
}

void savePowerSetVal(void)
{
	IapProgramByte(0x0001,gucv_set_power);
}

void saveModeSetVal(void)
{
	IapProgramByte(0x0002,gucv_set_mode);
}






void cleanAllSetting(void)
{
setTemp_inSetting=0;
setPower_inSetting=0;
}


void goToModeError(void)
{
	//设置为错误模式
	gucv_machine_status=MACHINE_ERROR;
	
	
	//关闭可控硅输出
	triacOnEnable=0;		//可控硅输出使能禁止
	Triac_IO_Ctrl(Triac_IO_OFF);//可控硅输出关闭
	
	//备份机器状态
	gucv_machine_status_bak=gucv_machine_status;
	
	//清除所有设置标志位
	cleanAllSetting();
}



void goToModeIdle(void)
{
	gucv_machine_status_bak=gucv_machine_status;
	//设置为待机
	gucv_machine_status=MACHINE_IDEL;
	
	//保存待机或开机状态
	if(gucv_set_mode!=gucv_machine_status)
	{
		gucv_set_mode=gucv_machine_status;
		saveModeSetVal();
	}
	
	//关显示
	Display_FixAll(0x00);

	//关工作指示灯
	//WorkLed_IO_Ctrl(WorkLed_IO_OFF);
	
	//如果正在设置温度则进行保存
	if(setTemp_inSetting!=0)  saveTempSetVal();
	//如果正在设置功率则进行保存
	if(setPower_inSetting!=0) savePowerSetVal();
	//清除所有设置标志位
	cleanAllSetting();

}


void goToModeWork(void)
{
	//同步一次显示温度与实际温度
	gucv_temp_display=gucv_real_temp;
	
	//清除所有设置标志位
	cleanAllSetting();
}

void setToModeWorkTemp(void)
{
	disPowerLevel(0);
					
	//设置为工作
	gucv_machine_status=MACHINE_WORK_TEMP;
	gucv_machine_status_bak=gucv_machine_status;
	//保存待机或开机状态
	if(gucv_set_mode!=gucv_machine_status)
	{
		gucv_set_mode=gucv_machine_status;
		saveModeSetVal();
	}
	
	//如果正在设置功率则进行保存
	if(setPower_inSetting!=0) 
	{
		savePowerSetVal();
		setPower_inSetting=0;
	}
		
}
void setToModeWorkPower(void)
{
	//设置为工作
	gucv_machine_status=MACHINE_WORK_POWER;
	gucv_machine_status_bak=gucv_machine_status;
	//保存待机或开机状态
	if(gucv_set_mode!=gucv_machine_status)
	{
		gucv_set_mode=gucv_machine_status;
		saveModeSetVal();
	}
	
	//如果正在设置温度则进行保存
	if(setTemp_inSetting!=0)
	{
		  saveTempSetVal();
		  setTemp_inSetting=0;
	}

		
}



void CheckSetTemp(unsigned char *setval)
{
	if((*setval)>SET_TEMP_MAX)
			(*setval)=SET_TEMP_MAX;
	else if((*setval)<SET_TEMP_MIN)
			(*setval)=SET_TEMP_MIN;	
}

void CheckSetPower(unsigned char *setval)
{
	if((*setval)!=25&&(*setval)!=34&&(*setval)!=52)
			(*setval)=25;

}

void CheckSetMode(unsigned char *setval)
{
	if((*setval)!=MACHINE_IDEL&&(*setval)!=MACHINE_WORK_TEMP&&(*setval)!=MACHINE_WORK_POWER)
			(*setval)=MACHINE_WORK_POWER;

}




void loadUserSetVal(void)
{
	//取回设置温度
	gucv_set_temp=IapReadByte(0x00);//读取设置温度
	CheckSetTemp(&gucv_set_temp);//设置温度合规检查

	//取回限制功率
	gucv_set_power=IapReadByte(0x01);//取回限制功率
	CheckSetPower(&gucv_set_power);//限制功率合规检查
	
	//取回设置模式
	gucv_set_mode=IapReadByte(0x02);//取回设置模式
	CheckSetMode(&gucv_set_mode);//设置模式合规检查
}




/*****************************************************************************
*函数			: void Background_Run(void)	
*函数功能描述 	: IO与负载后台自动处理
*函数参数 		: 无
*函数返回值 	: 无
******************************************************************************/
void app_init(void)
{


}





/*****************************************************************************
*函数			: void Background_Run(void)	
*函数功能描述 	: IO与负载后台自动处理
*函数参数 		: 无
*函数返回值 	: 无
******************************************************************************/
void app_run(void)
{


}
