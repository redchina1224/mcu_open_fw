#include "..\com_include_app.h"
  

/*
#include "..\..\core\system_core.c" 
#include "..\..\core\adc_core.c" 
#include "..\..\drv\rtc\softrtc\softrtc_drv.c" 
#include "..\..\drv\display\softled\softled_drv.c" 
#include "..\..\drv\buzzer\buzzer\buzzer_drv.c" 
#include "..\..\drv\motor\stepmotor\stepMotor_drv.c" 
#include "..\..\drv\interrupt\interrupt_drv.c" 


#include "teabar_take_water_app.c"   
#include "teabar_boil_water_app.c"   
#include "teabar_warm_water_app.c"   

*/


//----机器状态定义
#define			MACHINE_POWER_ON			0			//上电
#define			MACHINE_IDEL				1			//待机
#define			MACHINE_WORK_TEMP				2			//正常工作模式
#define			MACHINE_WORK_POWER		3
#define			MACHINE_SELF_CHECK	4			//自检
#define			MACHINE_ERROR				200			//故障

#define SET_TEMP_MAX 55
#define SET_TEMP_MIN 20


#define SET_POWER_MAX 52
#define SET_POWER_MIN 25



//----默认PWM速度
#define			PEM_DEFAULT_DATA			50			//默认PWM数据
//----水流速度
#define			WATER_SPEED_LOW				9				//水流速度过慢
//----故障定义
#define			ERROR_E1					0X01		//E1,漏电
#define			ERROR_E2					0X02		//E2,水流传感器故障
#define			ERROR_E3					0X04		//E3,超温
#define			ERROR_E4					0X08		//E4,温度传感器故障


//----功率表格  80份 1份表示75W
const	unsigned char	cucv_power_Tab[81]=
{
	//0 --0W
	0,
	//01-10 75W-750W
	 5,7,9,11,12,14,15,16,17,18,
	//11-20 825W-1500W
	19,20,21,21,22,23,24,25,25,26,
	//21-30 1575W-2250W
	27,28,28,29,30,30,31,32,33,33,
	//31-40 2325W-3000W
	34,35,36,36,37,38,38,39,39,40,
	//41-50 3075W-3750W
	40,41,42,42,43,44,44,45,46,46,
	//51-60 3825W-4500W
	47,48,49,49,50,51,51,52,52,53,
	//61-70 4575W-5250W
	54,55,56,57,58,58,59,60,61,61,
	//71-80 5325W-6000W
	62,63,64,65,67,68,70,72,76,80,
};

unsigned char	gucv_work_temp;			//控制目标温度

unsigned char	gucv_set_temp;			//控制温度设定
unsigned char gucv_set_power;		//功率限制设定

unsigned char gucv_set_mode;		//上电模式设定


unsigned char gucv_temp_display;		//用于显示的温度
unsigned char gucv_temp_display_down_delay;		//清除下回差延时


unsigned char setTemp_inSetting=0;//温度设定触发标志
unsigned char setPower_inSetting=0;//功率限制设定触发标志


unsigned	char	gucv_machine_status;			//机器状态
unsigned	char	gucv_machine_status_bak;		//机器状态,在报警恢复后 恢复机器状态
unsigned	char	gucv_work_mode;			//工作模式状态
bit gubv_displaytemp_lock_settemp=0;

bit gubv_setting_blink_disEn=0;//闪烁时是否显示或熄屏的标志
unsigned long gulv_setting_blinkmsec=0; //设置闪烁时间变量
unsigned long gulv_setting_exitmsec=0; //设置超时退出时间变量

unsigned long gulv_heatadj_nexttime_msec=0; //设置超时退出时间变量


unsigned	char	gucv_error_status=0;				//故障状态
unsigned	char	gucv_error_delay_cnt=0;				//故障延迟防抖

unsigned	char	gucv_display_nav_delay_cnt=0;				//倾倒显示切换延迟防抖

//----水温控制
unsigned	char	gucv_water_temp_con_step=0;			//水温控制步骤
unsigned	char	gucv_kkg_temp_data=0;				//可控硅数据 中间计算用
unsigned	int		guiv_water_temp_wending_time=0;		//水温稳定时间



unsigned	int 	guiv_work_low_temp_count=0;			//水温一直没有达到计时
unsigned	int 	guiv_work_adj_time=0;				//工作时调整可控硅输出间隔时间
//unsigned	char 	gucv_work_kkg_drv_data=0;			//工作时可控硅驱动时间 0-100  一共100级
unsigned	int		guiv_temp_display_time=0;			//显示温度补偿计时
unsigned	int		guiv_temp_display_data=0;			//显示温度补偿值


unsigned	long	lulv_out_power=0;							//标准输出功率
unsigned	int		luiv_power_adj_time_1ms=0;		//标准功率调整间隔
unsigned	int		luiv_power_adj_time_1ms_2=0;	//根据出水温度功率调整间隔
unsigned	int		luiv_power_adj_data=0;				//功率调整量
unsigned	int		luiv_temp_adc_data=0;					//需要的ADC值
unsigned	int		luiv_water_speed_data=0;			//水流大小
unsigned	char	lucv_water_speed_high_power=0;//判断水流过大的功率数据
unsigned	char	lucv_power_adj_jiange_time=0;	//根据出水温度调节功率大小间隔时间 设置
unsigned	int		luiv_E1_buzz_time=0;					//根据出水温度调节功率大小间隔时间 设置
unsigned	int		luiv_temp_stop_change_time=0;	//温度停止变化时间
unsigned	int		luiv_old_temp=0;							//上一次的温度
unsigned	char	lucv_now_adj_power=0;					//已经进入调整温度


unsigned	int	guiv_out_water_adc_data_ago=0;					//adc对比
unsigned  int	guiv_set_temp_adc_data;			//



bit gbv_heat_start_working=0;




unsigned char Bsp_timeNow[3]={0,0,0};


unsigned int waterin_Temp_ad;
unsigned int waterout_Temp_ad;
unsigned int leakage_ad;


unsigned	int		guiv_out_water_adc_data=0;			//采集到的出水口ADC值
unsigned	int		guiv_in_water_adc_data; //采集到的A进水口ADC值

unsigned	char 	gucv_water_speed;				//水流速度

unsigned	char	gucv_real_temp;					//真实温度
unsigned	char	gucv_in_water_temp;				//进水口温度



unsigned char adc_workcnt=0;
unsigned char mscx1_cnt=0;

bit zeroadjdir=0;


bit Leakage_Error=0;
bit WaterOutNtc_Error=0;
bit WaterInNtc_Error=0;



void waterin_callback(unsigned int a)
{
	if(a>3900||a<200) WaterInNtc_Error=1; else WaterInNtc_Error=0;
	guiv_in_water_adc_data=a;
	waterin_Temp_ad=a>>4;
}

void waterout_callback(unsigned int a)
{
	if(a>3900||a<200) WaterOutNtc_Error=1; else WaterOutNtc_Error=0;
	guiv_out_water_adc_data=a;
	waterout_Temp_ad=a>>4;

}

void leakage_callback(unsigned int a)
{
	//if(a>10) Leakage_Error=1;

}




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

	//清除所有设置标志位
	cleanAllSetting();

}

void goToModeWorkTemp(void)
{
	//设置为工作
	gucv_machine_status=MACHINE_WORK_TEMP;

	//保存待机或开机状态
	if(gucv_set_mode!=gucv_machine_status)
	{
		gucv_set_mode=gucv_machine_status;
		saveModeSetVal();
	}
	
	//同步一次显示温度与实际温度
	gucv_temp_display=gucv_real_temp;

	//如果正在设置功率则进行保存
	if(setPower_inSetting!=0) savePowerSetVal();
	
	//清除所有设置标志位
	cleanAllSetting();
	
	
	
	//清零计时器,工作状态初始化
//	gucv_work_kkg_drv_data=PEM_DEFAULT_DATA;
//	triacOnEnable=0;						//可控硅输出关闭
//	guiv_work_low_temp_count=0;	//水流检测清零
//	gucv_water_temp_con_step=0;	//加热步骤清零	
//	gbv_arrive_set_temp=0;			//达到设定温度
//	guiv_temp_display_time=0;		//清除显示温度补偿计时和数据
//	guiv_temp_display_data=0;		//清除显示温度补偿计时和数据
	
	
	
}
void goToModeWorkPower(void)
{
	//设置为工作
	gucv_machine_status=MACHINE_WORK_POWER;

	//保存待机或开机状态
	if(gucv_set_mode!=gucv_machine_status)
	{
		gucv_set_mode=gucv_machine_status;
		saveModeSetVal();
	}
	
	//同步一次显示温度与实际温度
	gucv_temp_display=gucv_real_temp;

	//如果正在设置功率则进行保存
	if(setPower_inSetting!=0) savePowerSetVal();
	
	//清除所有设置标志位
	cleanAllSetting();
		
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
			(*setval)=MACHINE_IDEL;

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



void DisplayBlink(unsigned char disnum)
{
		if(gulv_setting_blinkmsec<=(zd_getUtc_100mSec()))//当前时间大于前次设置的闪烁结束时间后触发一次切换
		{
			gulv_setting_blinkmsec=zd_getUtc_100mSec()+5;//闪烁间隔500ms,在当前时间后500ms后再触发
			if(gubv_setting_blink_disEn==0)//闪烁时是否显示或熄屏的标志
			{
				if(disnum>200)
				{
					disError(disnum%10);
					zd_buzzer_beep(1,10,0);//蜂鸣一声(3x50ms)
				}
				else
					disTemp(disnum);//显示数值
				gubv_setting_blink_disEn=1;//闪烁时是否显示或熄屏的标志,置1后，下次切换为熄屏
			}
			else
			{
				Display_FixAll(0x00);//熄屏,显示缓存填充0
				gubv_setting_blink_disEn=0;//闪烁时是否显示或熄屏的标志,置0后，下次切换为显示
			}
		}
}

void DisplayBlink_Start(void)
{
	gulv_setting_blinkmsec=0;//单次闪烁计时,置0后，立即执行一次切换操作
	gubv_setting_blink_disEn=0;//闪烁时是否显示或熄屏的标志,置0后，下次切换为显示
	gulv_setting_exitmsec=zd_getUtc_100mSec()+48; //闪烁5秒，时间采用4.8秒，使最后一次为熄灭状态，避免最后一次先点亮后再切换;
}



void ErrorCheck(void)
{
	if(Leakage_Error)//漏电快速响应报警
	{
		goToModeError();
	}
	else if(WaterInNtc_Error||WaterOutNtc_Error||gucv_real_temp>55)
	{
		if(mSec_x50_workbit)
		{
			if(gucv_error_delay_cnt<10) 
				gucv_error_delay_cnt++;
			else
				goToModeError();
		}
	}
	else
		gucv_error_delay_cnt=0;
	
}
/*
void DisplayNavCheck(void)
{
	if(Switch_IO_Channel==0)
	{
		if(gucv_display_nav_delay_cnt>0)
			gucv_display_nav_delay_cnt--;
		else
			displayNav=0;
	}
	else
	{
		if(gucv_display_nav_delay_cnt<50)
			gucv_display_nav_delay_cnt++;
		else
			displayNav=1;
	}
}
*/



void app_init(void)
{

	zd_systemInit();

	zd_softrtcInit();
	
	zd_key_init();
//	
	zd_buzzer_init();
//	
	zd_display_init();
	
//进水温度传感器信号
	zd_adcInit(WATERIN_AIN_Channel,waterin_callback);
//出水温度传感器信号
	zd_adcInit(WATEROUT_AIN_Channel,waterout_callback);
//漏电检测信号
	zd_adcInit(LEAKAGE_AIN_Channel,leakage_callback);

	
//以下内容临时使用，暂未标准化	
	
	//特殊处理,该脚与WATERIN脚并接需设置为输入
	//ZD_PORT_INPUT_SET(ZD_PORT1_DIR,BIT3);
	
//流量脉冲输入
	Counter_IO_Input;
	T_Counter1_1sec=&gucv_water_speed;
	
//过零信号
	ZeroCross_IO_Input;
	

//可控硅驱动
	Triac_IO_Output;
	Triac_IO_Ctrl(Triac_IO_OFF);
	
	//工作指示灯
	//WorkLed_IO_Output;
	//WorkLed_IO_Ctrl(WorkLed_IO_OFF);
	
	//倾倒开关
	//Switch_IO_Input;
	
	zd_buzzer_beep(1,10,0);//蜂鸣一声(3x50ms)
loadUserSetVal();
}



/*****************************************************************************
*函数			: void App_Run(void)	
*函数功能描述 	: 前台操作交互响应与模式切换
*函数参数 		: 无
*函数返回值 	: 无
******************************************************************************/
void App_Run(void)
{
	//显示方向检查
	//if(mSec_x10_workbit) DisplayNavCheck();

	//机器状态
	switch(gucv_machine_status)
	{
		//上电
		case MACHINE_POWER_ON:
	
			//上电默认全显
			//	WorkLed_IO_Ctrl(WorkLed_IO_ON);
			//上电1.5秒后显示功率限制设置值
			if(zd_getUtc_100mSec()>15)
				disTemp(gucv_set_power);//显示功率
			
			//上电3秒后进入前次保存的状态
			if(zd_getUtc_100mSec()>30)
			{
					//进入上一次机器状态（待机或工作）
					if(gucv_set_mode==MACHINE_IDEL)
					{
						goToModeIdle();//进入待机模式
					}
					else if(gucv_set_mode==MACHINE_WORK_TEMP)
					{
						goToModeWorkTemp();//进入恒温工作模式
					}
					else if(gucv_set_mode==MACHINE_WORK_POWER)
					{
						goToModeWorkPower();//进入档位工作模式
					}
			}
			
		break;
		case MACHINE_IDEL:


			if(gucv_water_speed==0)
			{
			}
			else
				disTemp(gucv_water_speed);
			
			//按键处理
			if(UserKeyPressed_up)//按键按下松开后触发
			{
				if(UserKeyVal==KEYS_POWER_VALUE)
				{
					if(1)
						goToModeWorkTemp();//切换进入工作模式
					else
						goToModeWorkPower();
						
					zd_buzzer_beep(1,3,0);//蜂鸣一声(3x50ms)
				}
				else if(UserKeyVal==KEYS_ADJUP_VALUE)
				{
					if(setPower_inSetting!=0)//当功率设置正在进行时有效,否则按键无效
					{
						if(gucv_set_power<SET_POWER_MAX) gucv_set_power+=10;//功率限制值加10
						CheckSetPower(&gucv_set_temp);//设置值合规性检查
						
						DisplayBlink_Start();//闪烁初始化处理,每次按下按键后闪烁处理点亮状态，避免按键切换时黑屏
						
						zd_buzzer_beep(1,3,0);//蜂鸣一声(3x50ms)
					}

				}
				else if(UserKeyVal==KEYS_ADJDOWN_VALUE)
				{
					if(setPower_inSetting!=0)//当功率设置正在进行时有效,否则按键无效
					{
						if(gucv_set_power>SET_POWER_MIN) gucv_set_power-=10;//功率限制值减10
						CheckSetPower(&gucv_set_temp);//设置值合规性检查
						
						DisplayBlink_Start();//闪烁初始化处理,每次按下按键后闪烁处理点亮状态，避免按键切换时黑屏
						
						zd_buzzer_beep(1,3,0);//蜂鸣一声(3x50ms)
					}

				}
				zd_key_clear();//清除所有按键标志位
			}
		

			if(UserKeyLongPressed)//按键按下超过2秒后触发
			{
				if(KeyLongPressCount>300)//按键按下超过3秒
				{
				
					if(UserKeyVal==KEYS_POWER_VALUE)
					{
						setPower_inSetting=1;//开始进入功率设置状态
						DisplayBlink_Start();//闪烁初始化处理,每次按下按键后闪烁处理点亮状态，避免按键切换时黑屏
						zd_buzzer_beep(1,3,0);//蜂鸣一声(3x50ms)
					}
					
					zd_key_clear();//清除所有按键标志位

				}
			}
			
			//错误检查,如存在错误状态自动转入报警模式
			ErrorCheck();
			
		break;
		
		//工作
		case MACHINE_WORK_TEMP:

/*
			//工作指示灯
			if(gbv_heat_start_working)
				WorkLed_IO_Ctrl(WorkLed_IO_ON);//开工作指示灯
			else		
				WorkLed_IO_Ctrl(WorkLed_IO_OFF);//关工作指示灯
*/		
			//温度设定显示与保存
			if(setTemp_inSetting!=0) //在设置状态
			{
				gubv_displaytemp_lock_settemp=0;
				DisplayBlink(gucv_set_temp);//闪烁显示温度值
				if(gulv_setting_exitmsec<zd_getUtc_100mSec())//超时自动保存退出
				{
					saveTempSetVal();//保存设置温度值
					setTemp_inSetting=0; //清除设置标志位，停止闪烁显示
				}
			}
			else//不在设置状态
			{

				//显示温度 
				if(mSec_x100_workbit)
				{
					if(gucv_real_temp>(gucv_temp_display))
					{
						gucv_temp_display++;//线性调整回差0
						gucv_temp_display_down_delay=0;//回差消除延时清零
						//如果线性调整后误差大于5时直接赋值
						if(gucv_real_temp>(gucv_temp_display+6))
							gucv_temp_display=gucv_real_temp;
					}
					else if(gucv_temp_display>(gucv_real_temp+1))
					{
						gucv_temp_display--;//线性调整回差1
						gucv_temp_display_down_delay=0;//回差消除延时清零
						//如果线性调整后误差大于5时直接赋值
						if(gucv_temp_display>(gucv_real_temp+6))
							gucv_temp_display=gucv_real_temp;
					}

					
					//实际温度在设定温度附近 锁定显示设定温度
					if((gucv_real_temp)>=(gucv_set_temp-4)&&(gucv_real_temp)<=(gucv_set_temp+4))
					{
						if(gubv_displaytemp_lock_settemp)
							gucv_temp_display=gucv_set_temp;
						else if((gucv_real_temp)>=(gucv_set_temp-1)&&(gucv_real_temp)<=(gucv_set_temp+1))
							gubv_displaytemp_lock_settemp=1;
					}
					else
						gubv_displaytemp_lock_settemp=0;

							
				}
				
				disTemp(gucv_temp_display);//显示温度值
				
				//disTemp(triacOn_CrossPass);
				
				
//				if(mSec_x100_workbit)
//					disTemp(gucv_real_temp);//显示实际温度值
				
			}		
		
		
		
			//按键处理
			if(UserKeyPressed_up)//按键按下松开后触发
			{
				if(UserKeyVal==KEYS_POWER_VALUE)
				{
					goToModeIdle();//切换进入待机模式
					zd_buzzer_beep(1,3,0);//蜂鸣一声(3x50ms)
				}
				else if(UserKeyVal==KEYS_ADJUP_VALUE)
				{
					if(setTemp_inSetting!=0)//当温度设置正在进行时有效
					{
						if(gucv_set_temp<SET_TEMP_MAX) gucv_set_temp++;//温度设置值加1
						CheckSetTemp(&gucv_set_temp);//温度设置值合规检查
						DisplayBlink_Start();//闪烁初始化处理,每次按下按键后闪烁处理点亮状态，避免按键切换时黑屏
					}
					else//当温度设置未触发时
					{
						setTemp_inSetting=1;//开始进入温度设置状态
						DisplayBlink_Start();//闪烁初始化处理,每次按下按键后闪烁处理点亮状态，避免按键切换时黑屏
					}
					
					zd_buzzer_beep(1,3,0);//蜂鸣一声(3x50ms)
					
				}
				else if(UserKeyVal==KEYS_ADJDOWN_VALUE)
				{
					if(setTemp_inSetting!=0)//当温度设置正在进行时有效
					{
						if(gucv_set_temp>SET_TEMP_MIN) gucv_set_temp--;//温度设置值减1
						CheckSetTemp(&gucv_set_temp);//温度设置值合规检查
						DisplayBlink_Start();//闪烁初始化处理,每次按下按键后闪烁处理点亮状态，避免按键切换时黑屏
					}
					else//当温度设置未触发时
					{
						setTemp_inSetting=1;//开始进入温度设置状态
						DisplayBlink_Start();//闪烁初始化处理,每次按下按键后闪烁处理点亮状态，避免按键切换时黑屏
					}
					
					zd_buzzer_beep(1,3,0);//蜂鸣一声(3x50ms)
				}
				

				
				zd_key_clear();//清除所有按键标志位
			}
			
			
			
			if(UserKeyLongPressed)//按键按下超过2秒后触发
			{
				if(KeyLongPressCount>300)//按键按下超过3秒
				{
				zd_key_clear();//清除所有按键标志位
				}
			}

			
			//错误检查,如存在错误状态自动转入报警模式
			ErrorCheck();

			
		break;



		case MACHINE_WORK_POWER:
		
		
		
		
			//功率设置状态显示与保存
			if(setPower_inSetting!=0)//在设置状态
			{
					DisplayBlink(gucv_set_power);//闪烁显示当前功率设置值
				
					if(gulv_setting_exitmsec<zd_getUtc_100mSec())//超时自动保存退出
					{
						savePowerSetVal();//保存功率设置值
						setPower_inSetting=0;//结束功率设置
						goToModeIdle();//再初始化待机,简化执行熄屏等操作
					}
			}
			else
				disTemp(gucv_water_speed);
				
				
			//按键处理
			if(UserKeyPressed_up)//按键按下松开后触发
			{
				if(UserKeyVal==KEYS_POWER_VALUE)
				{
					goToModeIdle();//切换进入待机模式
					zd_buzzer_beep(1,3,0);//蜂鸣一声(3x50ms)
				}
				else if(UserKeyVal==KEYS_LEVEL_VALUE)
				{
					if(setTemp_inSetting!=0)//当温度设置正在进行时有效
					{
						if(gucv_set_temp<SET_TEMP_MAX) gucv_set_temp++;//温度设置值加1
						CheckSetTemp(&gucv_set_temp);//温度设置值合规检查
						DisplayBlink_Start();//闪烁初始化处理,每次按下按键后闪烁处理点亮状态，避免按键切换时黑屏
					}
					else//当温度设置未触发时
					{
						setTemp_inSetting=1;//开始进入温度设置状态
						DisplayBlink_Start();//闪烁初始化处理,每次按下按键后闪烁处理点亮状态，避免按键切换时黑屏
					}
					
					zd_buzzer_beep(1,3,0);//蜂鸣一声(3x50ms)
					
				}
				else if(UserKeyVal==KEYS_ADJDOWN_VALUE)
				{
					if(setTemp_inSetting!=0)//当温度设置正在进行时有效
					{
						if(gucv_set_temp>SET_TEMP_MIN) gucv_set_temp--;//温度设置值减1
						CheckSetTemp(&gucv_set_temp);//温度设置值合规检查
						DisplayBlink_Start();//闪烁初始化处理,每次按下按键后闪烁处理点亮状态，避免按键切换时黑屏
					}
					else//当温度设置未触发时
					{
						setTemp_inSetting=1;//开始进入温度设置状态
						DisplayBlink_Start();//闪烁初始化处理,每次按下按键后闪烁处理点亮状态，避免按键切换时黑屏
					}
					
					zd_buzzer_beep(1,3,0);//蜂鸣一声(3x50ms)
				}
				

				
				zd_key_clear();//清除所有按键标志位
			}
			
			
			
			if(UserKeyLongPressed)//按键按下超过2秒后触发
			{
				if(KeyLongPressCount>300)//按键按下超过3秒
				{
				zd_key_clear();//清除所有按键标志位
				}
			}

			
			//错误检查,如存在错误状态自动转入报警模式
			ErrorCheck();
		break;			
			
		
		case MACHINE_ERROR:
			
			
			//WorkLed_IO_Ctrl(WorkLed_IO_OFF);//关工作指示灯
							
							
			if(Leakage_Error)//漏电故障
			{
				DisplayBlink(201);//闪烁显示E1
				gucv_error_delay_cnt=10;
			}
			else if(WaterInNtc_Error)//进水传感器(水流传感器)故障
			{
				DisplayBlink(202);//闪烁显示E2
				gucv_error_delay_cnt=10;
			}
			else if(WaterOutNtc_Error)//出水传感器故障
			{
				DisplayBlink(204);//闪烁显示E4
				gucv_error_delay_cnt=10;
			}
			else if(gucv_real_temp>55)//超温报警
			{
				DisplayBlink(203);//闪烁显示E3
				gucv_error_delay_cnt=10;
			}
			else if(mSec_x50_workbit)
			{
				if(gucv_error_delay_cnt>0)//故障延时恢复
					gucv_error_delay_cnt--;
				else
				{
					//进入上一次机器状态（待机或工作）
					if(gucv_set_mode==MACHINE_IDEL)
					{
						goToModeIdle();//进入待机模式
					}
					else if(gucv_set_mode==MACHINE_WORK_TEMP)
					{
						goToModeWorkTemp();//进入工作模式
					}
					else if(gucv_set_mode==MACHINE_WORK_POWER)
					{
						goToModeWorkPower();//进入工作模式
					}
					
				}

			}

					
		default:
			if(UserKeyPressed_up||UserKeyLongPressed) zd_key_clear();//清除所有按键标志位
		break;
	}
	
}




/*****************************************************************************
*函数			: void water_temp_con_step0(void)	
*函数功能描述 	
*函数参数 		: 无
*函数返回值 	: 无
******************************************************************************/

void water_temp_con_step0(void)
{
	
					//水流过小 直接进去下一步
					if(gucv_water_speed<=18)
					{
						gucv_water_temp_con_step=1;		//进入标准功率加热
						gucv_kkg_temp_data=0;
					}
					else
					{
						if(gucv_water_speed>=30)
						{
							luiv_water_speed_data=15;
						}
						else
						{
							luiv_water_speed_data=(unsigned char)(40-gucv_water_speed);
							if(luiv_water_speed_data<15)
							{
								luiv_water_speed_data=15;
							}
						}
					}
					
					//根据温度判断是否需要全功率加热
					if(gucv_set_temp>=(gucv_real_temp+luiv_water_speed_data))
					{
						gucv_kkg_temp_data=80;
					}
					else	if(gucv_set_temp<=(gucv_real_temp-12))
					{
						gucv_kkg_temp_data=0;
					}
					else
					{
						gucv_water_temp_con_step=1;		//进入标准功率加热
						gucv_kkg_temp_data=0;
					}
					
					//计算所需调整时间
					if(gucv_set_temp>=gucv_real_temp)
					{
						guiv_water_temp_wending_time=(unsigned char)(gucv_set_temp-gucv_real_temp);
					}
					else
					{
						guiv_water_temp_wending_time=((unsigned char)((gucv_real_temp-gucv_set_temp)>>1));
					}
					
					
					
					//换算成100ms *15
					if(guiv_water_temp_wending_time>20)
					{
						guiv_water_temp_wending_time=20;
					}
					guiv_water_temp_wending_time=guiv_water_temp_wending_time*12;
					if(guiv_water_temp_wending_time<50)
					{
						guiv_water_temp_wending_time=50;
					}
					
					
					
					luiv_power_adj_data=100;					//功率调整量
					luiv_power_adj_time_1ms=0;				//额定功率计算间隔
					guiv_work_adj_time=0;							//计时清零 功率调整  第一次进去就调整
					luiv_power_adj_time_1ms_2=0;			//根据出水温度功率调整间隔
					luiv_temp_stop_change_time=0;			//温度停止变化时间
					luiv_old_temp=0;									//上一次的温度
					lucv_now_adj_power=0;							//已经进入调整温度
}



//用标准加热比加热  计时X秒后进入微调
void water_temp_con_step1(void)
{
					//----标准功率计算
					luiv_power_adj_time_1ms++;
					if(luiv_power_adj_time_1ms>=10)
					{
						luiv_power_adj_time_1ms=0;
						//计算标准输出功率 百分比 = 水流量*温度差*0.11676
						if(gucv_set_temp>gucv_in_water_temp)		//输出设定温度大于进水温度
						{
							//----计算标准功率
							{
								lulv_out_power=(unsigned char)(gucv_set_temp-gucv_in_water_temp);
								//温度补偿

								if(gucv_set_temp>50)
								{
									if(lulv_out_power>=2)
									{lulv_out_power=lulv_out_power-2;}
								}
								else	if(gucv_set_temp>46)
								{
									if(lulv_out_power>=2)
									{lulv_out_power=lulv_out_power-2;}
								}
								
								if(gucv_set_temp<43)
								{
									lulv_out_power=lulv_out_power+2;
								}
								
								//计算标准功率
								lulv_out_power=lulv_out_power*(gucv_water_speed);
								lulv_out_power=lulv_out_power*20;
//								if(lulv_out_power>=9000)		//在功率小的时候 虚电压很高
//								{
//									lulv_out_power=lulv_out_power/guiv_real_voltage;
//								}
//								else
//								{
									lulv_out_power=lulv_out_power/220;
//								}
								
								//输出标准加热功率
								gucv_kkg_temp_data=lulv_out_power;
								
								//功率过小 补偿
								if((gucv_kkg_temp_data<30)&&(gucv_water_speed>18))
								{
									gucv_kkg_temp_data=(unsigned char)(gucv_kkg_temp_data+5);
								}
								
								//水流过小 补偿
//								if(guiv_water_speed<16)
//								{
//									if(gucv_kkg_temp_data>6)
//									{
//										gucv_kkg_temp_data=gucv_kkg_temp_data-6;
//									}
//								}
								
								//44度的时候 补偿
								if((gucv_set_temp==44)&&(gucv_in_water_temp>=20)&&(gucv_water_speed>18))
								{
									gucv_kkg_temp_data=(unsigned char)(gucv_kkg_temp_data+4);
								}
								
								//45度的时候 补偿
								if((gucv_set_temp==45)&&(gucv_in_water_temp>=20)&&(gucv_water_speed>18))
								{
									gucv_kkg_temp_data=(unsigned char)(gucv_kkg_temp_data+4);
								}
								
								//46度的时候 补偿
								if((gucv_set_temp==46)&&(gucv_in_water_temp>=20)&&(gucv_water_speed>18))
								{
									gucv_kkg_temp_data=(unsigned char)(gucv_kkg_temp_data+4);
								}
								
								//47度的时候 补偿
								if((gucv_set_temp==47)&&(gucv_in_water_temp>=20)&&(gucv_water_speed>18))
								{
									gucv_kkg_temp_data=(unsigned char)(gucv_kkg_temp_data+4);
								}
								
								//48度的时候 补偿
								if((gucv_set_temp==48)&&(gucv_in_water_temp>=20)&&(gucv_water_speed>18))
								{
									gucv_kkg_temp_data=(unsigned char)(gucv_kkg_temp_data+5);
								}
								
								//49度的时候 补偿
								if((gucv_set_temp==49)&&(gucv_in_water_temp>=20)&&(gucv_water_speed>18))
								{
									gucv_kkg_temp_data=(unsigned char)(gucv_kkg_temp_data+5);
								}
								
								//50度的时候 补偿
								if((gucv_set_temp==50)&&(gucv_in_water_temp>=20)&&(gucv_water_speed>18))
								{
									gucv_kkg_temp_data=(unsigned char)(gucv_kkg_temp_data+6);
								}
								
								//51度的时候 补偿
								if((gucv_set_temp==51)&&(gucv_in_water_temp>=20)&&(gucv_water_speed>18))
								{
									gucv_kkg_temp_data=(unsigned char)(gucv_kkg_temp_data+6);
								}
								
								//52度的时候 补偿
								if((gucv_set_temp==52)&&(gucv_in_water_temp>=20)&&(gucv_water_speed>18))
								{
									gucv_kkg_temp_data=(unsigned char)(gucv_kkg_temp_data+7);
								}
							}
							
							
							//当温度卡住不动的时候,,直接进入功率细调
							if(luiv_old_temp!=gucv_real_temp)
							{
								luiv_old_temp=gucv_real_temp;
								luiv_temp_stop_change_time=0;
							}
							
							//温度无变化计时
							luiv_temp_stop_change_time++;	//7秒无变化 直接开始调节温度
							if(luiv_temp_stop_change_time>=70)
							{
								luiv_temp_stop_change_time=0;
								
								//7秒无变化 直接开始调节温度
								if(lucv_now_adj_power==0)
								{
									lucv_now_adj_power=1;
									luiv_power_adj_time_1ms_2=guiv_water_temp_wending_time;
									guiv_work_adj_time=100;
								}
								
								//当温度卡住不动的时候  如果真是温度比设置温度底 功率加1
								if(gucv_real_temp<(gucv_set_temp-2))
								{
									luiv_power_adj_data++;
								}
							}
							
							//流水X秒后 根据出水温度调节
							luiv_power_adj_time_1ms_2++;
							if(luiv_power_adj_time_1ms_2>=guiv_water_temp_wending_time)
							{
								luiv_power_adj_time_1ms_2=guiv_water_temp_wending_time;
								
								//调整间隔时间配置
								if(gucv_water_speed>=20)
								{
									lucv_power_adj_jiange_time=50;
								}
								else
								{
									lucv_power_adj_jiange_time=gucv_water_speed;
									lucv_power_adj_jiange_time=(unsigned char)(20-lucv_power_adj_jiange_time);
									lucv_power_adj_jiange_time=(unsigned char)(lucv_power_adj_jiange_time*5);
									lucv_power_adj_jiange_time=(unsigned char)(lucv_power_adj_jiange_time+50);
								}
								
								//根据出水温度调整功率
								guiv_work_adj_time++;
								if(guiv_work_adj_time>=lucv_power_adj_jiange_time)
								{
									guiv_work_adj_time=0;
									
									//已经进入温度调节
									lucv_now_adj_power=1;
									
									//计算温度ADC值
									//lulv_water_temp_add=lulv_water_temp_add/luiv_water_temp_add_count;
									
									//标准不补偿的温度ADC值
									luiv_temp_adc_data=((unsigned int)GetTempAdcVal((gucv_set_temp)))<<4;//取回温度表中的ADC值,因为是8位的所以要左移两位
									
									//温度补偿 42减小5  52减小20度  按照比例计算
									/*
									if(gucv_set_temp==30)
									{luiv_temp_adc_data+=20;}									
									if(gucv_set_temp==31)
									{luiv_temp_adc_data+=12;}									
									if(gucv_set_temp==32)
									{luiv_temp_adc_data+=4;}									
									if(gucv_set_temp==33)
									{luiv_temp_adc_data-=4;}									
									if(gucv_set_temp==34)
									{luiv_temp_adc_data-=12;}									
									if(gucv_set_temp==35)
									{luiv_temp_adc_data-=20;}									
									if(gucv_set_temp==36)
									{luiv_temp_adc_data-=20;}									
									if(gucv_set_temp==37)
									{luiv_temp_adc_data-=20;}									
									if(gucv_set_temp==38)
									{luiv_temp_adc_data-=20;}									
									if(gucv_set_temp==39)
									{luiv_temp_adc_data-=20;}									
									if(gucv_set_temp==40)
									{luiv_temp_adc_data-=20;}									
									if(gucv_set_temp==41)
									{luiv_temp_adc_data-=24;}									
									if(gucv_set_temp==42)
									{luiv_temp_adc_data-=28;}
									if(gucv_set_temp==43)
									{luiv_temp_adc_data-=32;}
									if(gucv_set_temp==44)
									{luiv_temp_adc_data-=36;}
									if(gucv_set_temp==45)
									{luiv_temp_adc_data-=40;}
									if(gucv_set_temp==46)
									{luiv_temp_adc_data-=44;}
									if(gucv_set_temp==47)
									{luiv_temp_adc_data-=48;}
									if(gucv_set_temp==48)
									{luiv_temp_adc_data-=52;}
									if(gucv_set_temp==49)
									{luiv_temp_adc_data-=56;}
									if(gucv_set_temp==50)
									{luiv_temp_adc_data-=60;}
									if(gucv_set_temp==51)
									{luiv_temp_adc_data-=64;}
									if(gucv_set_temp==52)
									{luiv_temp_adc_data-=68;}
									*/
									
									//温度高 AD值要小 加热比减少
									if(guiv_out_water_adc_data<(luiv_temp_adc_data-4))
									{
										if(luiv_power_adj_data>0)
										{
											luiv_power_adj_data--;
										}
										
										if(guiv_out_water_adc_data<(luiv_temp_adc_data-12))
										{
											if(luiv_power_adj_data>0)
											{
												luiv_power_adj_data--;
											}
										}
									}
									//温度低 AD值要大 增加加热比
									if(guiv_out_water_adc_data>(luiv_temp_adc_data+4))
									{
										if(luiv_power_adj_data<200)
										{
											luiv_power_adj_data++;
										}
										
										if(guiv_out_water_adc_data>(luiv_temp_adc_data+12))
										{
											if(luiv_power_adj_data<200)
											{
												luiv_power_adj_data++;
											}
										}
									}
								}
							}
							
							//调整量叠加到输出上
							if(luiv_power_adj_data>=100)
							{
								gucv_kkg_temp_data=gucv_kkg_temp_data+(luiv_power_adj_data-100);
							}
							else
							{
								if(gucv_kkg_temp_data>(100-luiv_power_adj_data))
								{
									gucv_kkg_temp_data=gucv_kkg_temp_data-(100-luiv_power_adj_data);
								}
								else
								{
									gucv_kkg_temp_data=0;
								}	
							}
						}
						else
						{
							gucv_kkg_temp_data=0;
						}
					}
}



/*****************************************************************************
*函数			: void power_limit(void)
*函数功能描述 	功率档位限制功率
*函数参数 		: 无
*函数返回值 	: 无
******************************************************************************/
void power_limit(void)
{
			switch(gucv_set_power)
			{
				
				//5500W
				case 55:
				{
					//加热比限制
					if(gucv_kkg_temp_data>=80)
					{
						gucv_kkg_temp_data=80;
					}
//					lucv_water_speed_high_power=78;
				}
				break;
								
				//4500W
				case 45:
				{
					//加热比限制
					if(gucv_kkg_temp_data>=58)
					{
						gucv_kkg_temp_data=58;
					}
//					lucv_water_speed_high_power=57;
				}
				break;
				
				case 35:
				{
					//加热比限制
					if(gucv_kkg_temp_data>=41)
					{
						gucv_kkg_temp_data=41;
					}
//					lucv_water_speed_high_power=40;
				}
				break;
				
				default:
				break;
			}
	
}



//30秒无法达到设定温度检测
//void temp_ctrl_30s_fail_check(void)
//{
//		//加热开度最大时
//		if((gucv_kkg_temp_data>=lucv_water_speed_high_power))
//		{
//			if(guiv_work_low_temp_count<3000)
//			{
//				guiv_work_low_temp_count++;
//			}
//		}
//		
//		//设定温度到了 清零水流大数据
//		if(gucv_real_temp>=(gucv_set_temp-2))
//		{
//			guiv_work_low_temp_count=0;//清零水流大数据计时
//		}
//}


//计算标准输出功率
void PowerStdCalc(void)
{
	//计算标准加热比
	lulv_out_power=(unsigned char)(gucv_set_temp-gucv_in_water_temp); //计算温升需求
	lulv_out_power=lulv_out_power*(gucv_water_speed);//合并温升与流量数据
	lulv_out_power=lulv_out_power*20;
	lulv_out_power=lulv_out_power/220;//合并电压数据
	
	//输出标准加热比
	if(lulv_out_power>255)
		gucv_kkg_temp_data=255;
	else
		gucv_kkg_temp_data=lulv_out_power;	
}


//计算功率调整值
void PowerAdjCalc(void)
{
	if(gulv_heatadj_nexttime_msec<zd_getUtc_100mSec())
	{
		guiv_set_temp_adc_data=((unsigned int)GetTempAdcVal(gucv_set_temp))<<4;//取回温度表中的ADC值,因为是8位的所以要左移4位
			
		if(guiv_set_temp_adc_data<guiv_out_water_adc_data)//(gucv_set_temp>gucv_real_temp)//低于设定温度
		{
			if(luiv_power_adj_data<200) luiv_power_adj_data++;

			if(guiv_out_water_adc_data<guiv_out_water_adc_data_ago)//当前ADC比前一次ADC要小,温度上升,方向正确
			{
				if((guiv_out_water_adc_data-guiv_set_temp_adc_data)<100&&(guiv_out_water_adc_data_ago-guiv_out_water_adc_data)>1)//当温度接近，并且上升率过大时时减小功率,防止升温太多
				{
					if(triacOn_CrossPass<70) triacOn_CrossPass++;//减小功率
					gulv_heatadj_nexttime_msec=zd_getUtc_100mSec()+10;
				}
			}								
			else//当前ADC比前一次ADC要大或相等,温度下降或不变化，方向错误
			{
				//if((guiv_out_water_adc_data-guiv_out_water_adc_data_ago)>1)
				{
					if(triacOn_CrossPass>0) triacOn_CrossPass--;//加大功率
					gulv_heatadj_nexttime_msec=zd_getUtc_100mSec()+2;
				}
			}
		}
		else if(guiv_set_temp_adc_data>guiv_out_water_adc_data)//(gucv_set_temp<gucv_real_temp)//高于设定温度
		{
			
			if(luiv_power_adj_data>0) luiv_power_adj_data--;
										
			if(guiv_out_water_adc_data>guiv_out_water_adc_data_ago)//当前ADC比前一次ADC要大,温度下降，方向正确
			{
				if((guiv_set_temp_adc_data-guiv_out_water_adc_data)<50&&(guiv_out_water_adc_data-guiv_out_water_adc_data_ago)>1)//当温度接近，并且下降率过大时时减小功率,防止下降太多
				{
					if(triacOn_CrossPass>0) triacOn_CrossPass--;//加大功率
					gulv_heatadj_nexttime_msec=zd_getUtc_100mSec()+10;
				}
			}								
			else//当前ADC比前一次ADC要小或相等,温度上升或不变化，方向错误
			{
				if(triacOn_CrossPass<70) triacOn_CrossPass++;//减小功率
				gulv_heatadj_nexttime_msec=zd_getUtc_100mSec()+2;
			}
		}
		
		guiv_out_water_adc_data_ago=guiv_out_water_adc_data;
		
	}
}


/*****************************************************************************
*函数			: void Background_Run(void)	
*函数功能描述 	: IO与负载后台自动处理
*函数参数 		: 无
*函数返回值 	: 无
******************************************************************************/
void Background_Run(void)
{
	
	//机器状态
	switch(gucv_machine_status)
	{

		
		//工作
		case MACHINE_WORK_TEMP:
			
//				//水流判定,是否开始加热工作判定
				if(gucv_water_speed>=WATER_SPEED_LOW)
				{
					if(gbv_heat_start_working==0)
					{
						gbv_heat_start_working=1;
						guiv_out_water_adc_data_ago=guiv_out_water_adc_data;						
					}
////////////////////////////////////////////////////////////////////////////////////////////////////////						
/*					
						
					//计算标准输出功率
					PowerStdCalc();
				
					//计算功率调整值
					PowerAdjCalc();

					//合并调整量与标准输出
					if(luiv_power_adj_data>=100)
					{
						gucv_kkg_temp_data=gucv_kkg_temp_data+(luiv_power_adj_data-100);
					}
					else
					{
						if(gucv_kkg_temp_data>(100-luiv_power_adj_data))
						{
							gucv_kkg_temp_data=gucv_kkg_temp_data-(100-luiv_power_adj_data);
						}
						else
						{
							gucv_kkg_temp_data=0;
						}	
					}
					
					
					//按功率档位限制功率
					power_limit();
					
					
					//输出最终加热比,,,
					if(gucv_kkg_temp_data>0)		//需要加热的时候才输出,,,防止10ms 80个数据的临界点加热一下
					{	
						//可控硅输出允许
						triacOn_CrossPass=(unsigned char)(80-cucv_power_Tab[gucv_kkg_temp_data]);
						triacOnEnable=1;	
					}
					else
					{
						triacOnEnable=0;	
					}	
	
					break;
*/					
/////////////////////////////////////////////////////////////////////////////////////////
				}
				else
				{
					gbv_heat_start_working=0;
					
					//关闭可控硅输出
					triacOnEnable=0;		//可控硅输出使能禁止
					Triac_IO_Ctrl(Triac_IO_OFF);//可控硅输出关闭

					//复位工作变量
					gucv_kkg_temp_data=0;
					gucv_water_temp_con_step=0;		//加热步骤清零

					
					break;//退出工作循环,不再往下执行
				}
		
		
		
			if(mSec_x10_workbit)
			{
								
				//加热比计算
				switch(gucv_water_temp_con_step)
				{
					//判断温度差距是否到达10度
					case	0:
						water_temp_con_step0();
					break;
					
					//用标准加热比加热  计时X秒后进入微调
					case	1:
						water_temp_con_step1();
					break;
					
					default:
						gucv_water_temp_con_step=0;
					break;
				}

				
				//按功率档位限制功率
				power_limit();
				
				
				//输出最终加热比,,,
				if(gucv_kkg_temp_data>0)		//需要加热的时候才输出,,,防止10ms 80个数据的临界点加热一下
				{	
					//可控硅输出允许
					triacOn_CrossPass=(unsigned char)(80-cucv_power_Tab[gucv_kkg_temp_data]);
					triacOnEnable=1;	
				}
				else
				{
					triacOnEnable=0;	
				}	
			}
			break;


		//自检
		case MACHINE_SELF_CHECK:

		break;

		
		default:
			//关闭可控硅输出
			triacOnEnable=0;		//可控硅输出使能禁止
			Triac_IO_Ctrl(Triac_IO_OFF);//可控硅输出关闭
		break;
	}
	
}




/*****************************************************************************
*函数			: void Background_Run(void)	
*函数功能描述 	: IO与负载后台自动处理
*函数参数 		: 无
*函数返回值 	: 无
******************************************************************************/



void app_base_run(void)
{
		if(mSec_x50_workbit)//每50ms调用一次
		{
			//蜂鸣器触发与控制
			zd_buzzerRun();
		
			//gucv_real_temp=CalcTmpC(waterout_Temp_ad,gucv_real_temp);
		}
		
		if(mSec_x100_workbit)//每100ms调用一次
		{


			
		}

		if(mSec_x10_workbit)//每10ms调用一次
		{
			//ad自动化轮询采集与回调执行

			zd_adcRun();


						
			//按键扫描,产生按键触发标志与键值信息
			zd_keyRun();
			
			//步进电机
			//zd_motorStep_run();

		}
	
		if(mSec_x5_workbit)
		{
			//中微触控取值
			__CMS_CheckTouchKey();	//扫描按键
			
			
		}
}
