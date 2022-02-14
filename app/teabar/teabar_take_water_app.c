#include "..\com_include_app.h"


bit gbv_take_water_working=0;
bit gbv_take_water_working_ago=0;
bit gbv_stepmotor_workover=0;


/***********************************************************************************************
*函数名 		: core_DelayUs(unsigned char dl_t)
*函数功能描述 	: 取水功能初始化
*函数参数 		: unsigned char dl_t：延时计数约等于空指令周期
*函数返回值 	: 无
***********************************************************************************************/
void take_water_init(void)
{
	Take_Water_Pump_IO_Output;
	Take_Water_Pump_IO_Ctrl(ake_Water_Pump_IO_OFF);
	zd_motorStep_init();
}


/***********************************************************************************************
*函数名 		: core_DelayUs(unsigned char dl_t)
*函数功能描述 	: 取水功能后台控制
*函数参数 		: unsigned char dl_t：延时计数约等于空指令周期
*函数返回值 	: 无
***********************************************************************************************/
void take_water_background_Run(void)
{

	//转向与取水工作
	if(gbv_take_water_working)
	{
		//取水开启时转向
		if(gbv_take_water_working_ago==0) 
		{
			gbv_stepmotor_workover=0;
			zd_motorStep_work(GET_WATER_SETP_MOTOR_START_DIR,GET_WATER_SETP_MOTOR_PLUS_COUNT,GET_WATER_SETP_MOTOR_PLUS_SPEED);
		}
		
		//转向结束后开始取水
		if(gbv_stepmotor_workover)
		{
			Pump_IO_Ctrl(Pump_IO_ON);
		}
		
	}
	else
	{
		//结束取水
		Pump_IO_Ctrl(Pump_IO_OFF);
		//取水结束时转向
		if(gbv_take_water_working_ago==1) 
		{
			gbv_stepmotor_workover=0;
			zd_motorStep_work(GET_WATER_SETP_MOTOR_END_DIR,GET_WATER_SETP_MOTOR_PLUS_COUNT,GET_WATER_SETP_MOTOR_PLUS_SPEED);
		}
	}
	
	//历史状态更新
	gbv_take_water_working_ago=gbv_take_water_working;
	
	//获取转向结束状态
	if(zd_motorStep_isbusy()==0)
		gbv_stepmotor_workover=1;
}