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
#define			MACHINE_LOCK				1			//待机
#define			MACHINE_IDEL				2			//待机
#define			MACHINE_WORK				3			//正常工作模式
#define			MACHINE_SELF_CHECK	4			//自检
#define			MACHINE_ERROR				200			//故障

//#define SET_TEMP_MAX 100
#define SET_TEMP_MIN 50

#define SET_BOILINGTEMP_MAX 100
#define SET_BOILINGTEMP_MIN 82

#define SET_WATERTIME_MAX 50
#define SET_WATERTIME_MIN 18

#define SET_WARMTIME_MAX 24
#define SET_WARMTIME_MIN 1


#define			BlinkTime 1
#define			BlinkTemp 2



unsigned long  TmpPidDisplay_LastSet_utcsec=0;
unsigned long  TmpPidDisplay_LastSet_msec=0;

unsigned long TempCheck30s_LastActive_utcsec=0;


//volatile unsigned char TempCheck30s_DataMax_ago=0;
unsigned char TempCheck30s_DataMax;
//unsigned char Rgb_Tmp_DataMin;
//unsigned char Rgb_Tmp_DataMax;

//简单PID差值（定时检测温升，用于关闭加热的提前量），防止温度过充
unsigned long TempDiff_LastActive_utcsec=0;
unsigned long  DisplayTempDiff_LastSet_utcsec=0;
unsigned char gucv_real_tempC_falsify_target;
unsigned	char	gucv_real_tempC_falsify=0;
unsigned	char	gucv_real_tempF_falsify=0;

unsigned char PidTemp_DataDiff=0;
unsigned char PidTemp_DataNow=0;
unsigned char PidTemp_DataAgo=0;


unsigned char gucv_set_boilingtemp=100;	//沸点温度设定值
unsigned char gucv_set_temp=100;	//加热目标温度设定

unsigned char gucv_set_watertime=34;		//取水时间
unsigned char gucv_set_warmtime=8;		//保温时间

unsigned long gulv_work_warmtime_sec;		//保温时间
unsigned char gucv_work_watertime;



unsigned	char	gucv_real_temp;					//真实温度
unsigned char gucv_temp_display;		//用于显示的温度
unsigned char gucv_temp_display_down_delay;		//清除下回差延时

unsigned char setGetWaterTime_inSetting=0;//取水时间设定触发标志
unsigned char setBoilingTemp_inSetting=0;//沸点温度设定触发标志
unsigned char setKeepWarmTime_inSetting=0;//保温时间设定触发标志



unsigned	char	gucv_machine_status;			//机器状态


bit gubv_displaytemp_lock_settemp=0;

bit gubv_setting_blink_disEn=0;//闪烁时是否显示或熄屏的标志
unsigned long gulv_setting_blinkmsec=0; //设置闪烁时间变量
unsigned long gulv_setting_exitmsec=0; //设置超时退出时间变量

unsigned long gulv_heatadj_nexttime_msec=0; //设置超时退出时间变量






unsigned char gucv_heat_start_delay=0;




bit gbv_heat_start_working=0;
bit gbv_pump_start_working=0;
bit gbv_pump_start_working_ago=0;

bit gbv_warm_start_working=0;
bit gbv_stepmotor_workover=0;


bit gbv_pot_up=0;
bit gbv_temp_over=0;
bit gbv_tempntc_open=0;
bit gbv_tempntc_short=0;
unsigned char gucv_temp_over_filter_cnt=0;
unsigned char gucv_pot_up_filter_cnt=0;


unsigned int waterout_Temp_ad;


unsigned	int		guiv_leakage_adc_data=0;
unsigned	int		guiv_out_water_adc_data=0;			//采集到的出水口ADC值
unsigned	int		guiv_in_water_adc_data; //采集到的A进水口ADC值


unsigned char adc_buzz_delay_cnt=0;







void saveBoilingTempSetVal(void)
{
	IapProgramByte(0x0000,gucv_set_boilingtemp);
	
}

void saveGetWaterTimeSetVal(void)
{
	IapProgramByte(0x0001,gucv_set_watertime);
}

void saveKeepWarmTimeSetVal(void)
{
	IapProgramByte(0x0002,gucv_set_warmtime);
}




void cleanAllSetting(void)
{
	setGetWaterTime_inSetting=0;//

	setKeepWarmTime_inSetting=0;//

	setBoilingTemp_inSetting=0;//
}



void goToModeLock(void)
{
	//设置为锁定
	gucv_machine_status=MACHINE_LOCK;
	
	//关显示
	Display_FixAll(0x00);
	
	//清除按键标志
	KeyQuickPressCount=0;
	zd_key_clear();//清除所有按键标志位	
	cleanAllSetting();//清除所有设置标志位
}

void goToModeIdle(void)
{
	//设置为待机
	gucv_machine_status=MACHINE_IDEL;
	
	//设定温度设置为沸点温度
	gucv_set_temp=gucv_set_boilingtemp;
	
	//关显示
	Display_FixAll(0x00);
	
	//点亮电源指示灯
	disKeyLed((keyled_dianyuan),1);
	
	//清除按键标志
	KeyQuickPressCount=0;
	zd_key_clear();//清除所有按键标志位	
	cleanAllSetting();//清除所有设置标志位

}


void CheckSetValue(unsigned char *setval,unsigned char min,unsigned char max)
{
		if((*setval)>max)
			(*setval)=max;
	else if((*setval)<min)
			(*setval)=min;	
}

#define CheckSetBoilingTemp(x) CheckSetValue((x),SET_BOILINGTEMP_MIN,SET_BOILINGTEMP_MAX)
#define CheckSetTemp(x)  CheckSetValue((x),SET_TEMP_MIN,(gucv_set_boilingtemp))
#define CheckSetWarmTime(x) CheckSetValue((x),SET_WARMTIME_MIN,SET_WARMTIME_MAX)
#define CheckSetWaterTime(x) CheckSetValue((x),SET_WATERTIME_MIN,SET_WATERTIME_MAX)

#define AdjUpSetBoilingTemp(x) if((x)<SET_BOILINGTEMP_MAX) (x)++; else (x)=0;
#define AdjUpSetTemp(x) if((x)<gucv_set_boilingtemp) (x)+=5; else (x)=0;
#define AdjUpSetWarmTime(x) if((x)<SET_WARMTIME_MAX) (x)++; else (x)=0;
#define AdjUpSetWaterTime(x) if((x)<SET_WATERTIME_MAX) (x)++; else (x)=0;



/*
void CheckSetBoilingTemp(unsigned char *setval)
{
	if((*setval)>SET_BOILINGTEMP_MAX)
			(*setval)=SET_BOILINGTEMP_MAX;
	else if((*setval)<SET_BOILINGTEMP_MIN)
			(*setval)=SET_BOILINGTEMP_MIN;	
}

 

void CheckSetTemp(unsigned char *setval)
{
	if((*setval)>gucv_set_boilingtemp)
			(*setval)=gucv_set_boilingtemp;
	else if((*setval)<SET_TEMP_MIN)
			(*setval)=SET_TEMP_MIN;	
}


void CheckSetWarmTime(unsigned char *setval)
{
	if((*setval)!=35&&(*setval)!=45&&(*setval)!=55)
			(*setval)=35;

}

void CheckSetWaterTime(unsigned char *setval)
{
	if((*setval)!=MACHINE_IDEL&&(*setval)!=MACHINE_WORK)
			(*setval)=MACHINE_IDEL;

}

*/


void loadUserSetVal(void)
{
	//取回沸点温度
	gucv_set_boilingtemp=IapReadByte(0x00);//读取沸点温度
	CheckSetBoilingTemp(&gucv_set_boilingtemp);//设置值合规性检查

	//取回取水时间
	gucv_set_watertime=IapReadByte(0x01);//取回取水
	CheckSetWaterTime(&gucv_set_watertime);//设置值合规性检查
	
	//取回保温时间
	gucv_set_warmtime=IapReadByte(0x02);//取回保温时间
	CheckSetWarmTime(&gucv_set_warmtime);//设置值合规性检查

}

void DisplayBlink(unsigned char distype,unsigned int disnum)
{
		if(gulv_setting_blinkmsec<=(zd_getUtc_100mSec()))//当前时间大于前次设置的闪烁结束时间后触发一次切换
		{
			gulv_setting_blinkmsec=zd_getUtc_100mSec()+5;//闪烁间隔500ms,在当前时间后500ms后再触发
			if(gubv_setting_blink_disEn==0)//闪烁时是否显示或熄屏的标志
			{
				if(distype==BlinkTemp)
					disTemp(disnum);//显示数值
				else if(distype==BlinkTime)
					disTime(disnum);//显示数值
					
					
				gubv_setting_blink_disEn=1;//闪烁时是否显示或熄屏的标志,置1后，下次切换为熄屏
			}
			else
			{
				if(distype==0)
					Display_FixAll(0x00);//熄屏,显示缓存填充0
				else if(distype==BlinkTemp)
					Display_FixTemp(0x00);
				else if(distype==BlinkTime)
					Display_FixTime(0x00);
				
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


void waterin_callback(unsigned int a)
{

}

void waterout_callback(unsigned int a)
{
	if(a>3900) gbv_tempntc_open=1; else if(a<3800) gbv_tempntc_open=0;
	if(a<720) gbv_tempntc_short=1; else if(a>820) gbv_tempntc_short=0;
	
	waterout_Temp_ad=(a)>>4;

}

void leakage_callback(unsigned int a)
{

}


void app_init(void)
{
	zd_systemInit();

	zd_softrtcInit();
	
	zd_key_init();
//	
	zd_buzzer_init();
//	
	zd_display_init();
	
	zd_motorStep_init();
//进水温度传感器信号
	//zd_adcInit(WATERIN_AIN_Channel,waterin_callback);
//出水温度传感器信号
	zd_adcInit(WATEROUT_AIN_Channel,waterout_callback);
//漏电检测信号
	//zd_adcInit(LEAKAGE_AIN_Channel,leakage_callback);

	
//以下内容临时使用，暂未标准化	
	
	
			//加热继电器
		HotRelay_IO_Output;
		HotRelay_IO_Ctrl(HotRelay_IO_OFF);

		//保温继电器
		WarmRelay_IO_Output;
		WarmRelay_IO_Ctrl(WarmRelay_IO_OFF);

		//水泵
		Pump_IO_Output;
		Pump_IO_Ctrl(Pump_IO_OFF);
				
	//特殊处理,该脚与WATERIN脚并接需设置为输入
	//ZD_PORT_INPUT_SET(ZD_PORT1_DIR,BIT3);

	//载入存储的用户数据
	loadUserSetVal();
	
	//上电蜂鸣一声
	zd_buzzer_beep(1,3,0);//蜂鸣一声(3x50ms)
	
	
}


void Error_Check(void)
{
			if(mSec_x50_workbit)
			{
				//提壶-传感器开路事件
				if(gbv_tempntc_open)
				{
					if(gbv_pot_up==0)
					{
						if(++gucv_pot_up_filter_cnt>5)
						{
							gbv_pot_up=1;
							gucv_pot_up_filter_cnt=0;
							zd_buzzer_beep(2,3,3);//蜂鸣两声(3x50ms)
						}
					}
					else
						gucv_pot_up_filter_cnt=0;
					
				}
				else
				{
					if(gbv_pot_up==1)
					{
						if(++gucv_pot_up_filter_cnt>10)
						{
							gbv_pot_up=0;
							gucv_pot_up_filter_cnt=0;
							zd_buzzer_beep(1,3,3);//蜂鸣一声(3x50ms)
						}
					}
					else
						gucv_pot_up_filter_cnt=0;
				}
				
				//超温-传感器短路事件
				if(gbv_tempntc_short)
				{
					if(gbv_temp_over==0)
					{
						if(++gucv_temp_over_filter_cnt>20)
						{
							gbv_temp_over=1;
							zd_buzzer_beep(10,4,5);//蜂鸣十声(3x50ms)
						}
					}
				}
				else
					gucv_temp_over_filter_cnt=0;
			}
}

/*****************************************************************************
*函数			: void App_Run(void)	
*函数功能描述 	: 前台操作交互响应与模式切换
*函数参数 		: 无
*函数返回值 	: 无
******************************************************************************/
void App_Run(void)
{

	//机器状态
	switch(gucv_machine_status)
	{
		//上电
		case MACHINE_POWER_ON:

			//上电2秒后进入前次保存的状态
			if(zd_getUtc_100mSec()>20)
			{
				//进入锁定状态
				goToModeLock();
			}
			
		break;
		case MACHINE_LOCK:
			if(GetSecHalfBit()) disKeyLed((keyled_dianyuan),1); else disKeyLed((keyled_dianyuan),0);
			
			//disTemp(KeyQuickPressCount);
			
			//取水时间设定显示
			if(setGetWaterTime_inSetting!=0)//在设置状态
			{
				DisplayBlink(BlinkTime,gucv_set_watertime);
				if(gulv_setting_exitmsec<zd_getUtc_100mSec())//超时自动保存退出
				{
					saveGetWaterTimeSetVal();
					setGetWaterTime_inSetting=0; //清除设置标志位，停止闪烁显示
				}
			}
			//保温时间设定显示
			else if(setKeepWarmTime_inSetting!=0)//在设置状态
			{
				DisplayBlink(BlinkTime,gucv_set_warmtime);
				if(gulv_setting_exitmsec<zd_getUtc_100mSec())//超时自动保存退出
				{
					saveKeepWarmTimeSetVal();
					setKeepWarmTime_inSetting=0; //清除设置标志位，停止闪烁显示
				}
			}
			else//不在设置状态
			{
				Display_FixTime(0x00);
			}


			//沸点温度设定显示
			if(setBoilingTemp_inSetting!=0)//在设置状态
			{
				DisplayBlink(BlinkTemp,gucv_set_boilingtemp);
				if(gulv_setting_exitmsec<zd_getUtc_100mSec())//超时自动保存退出
				{
					saveBoilingTempSetVal();
					setBoilingTemp_inSetting=0; //清除设置标志位，停止闪烁显示
				}
			}
			else//不在设置状态
			{//UserKeyVal
				Display_FixTemp(0x00);//disTemp(UserKeyVal);//(UserKeyVal);//Display_FixTemp(0x00);
			}
			
			

			
			
			
			
			if(UserKeyPressed_up)//按键按下松开后触发
			{
				if(UserKeyVal==KEYS_DIANYUAN_VALUE)
				{
					if(setGetWaterTime_inSetting!=0||setKeepWarmTime_inSetting!=0||setBoilingTemp_inSetting!=0)//如果正在进行设定，按电源键进行确认
					{
						
						if(setGetWaterTime_inSetting!=0)
						{
							//保存数据
							saveGetWaterTimeSetVal();
							setGetWaterTime_inSetting=0;//退出设置
						}
						if(setKeepWarmTime_inSetting!=0)
						{
							//保存数据
							saveKeepWarmTimeSetVal();
							setKeepWarmTime_inSetting=0;//退出设置
						}
						if(setBoilingTemp_inSetting!=0)
						{
							//保存数据
							saveBoilingTempSetVal();
							setBoilingTemp_inSetting=0;//退出设置
						}
						
						KeyQuickPressCount=0;//按键多击清零
					}				
					else if(KeyQuickPressCount>=2)//电源键按键多击达到2次或以上，进入待机
					{
						goToModeIdle();
					}
					zd_buzzer_beep(1,2,0);//蜂鸣一声(3x50ms)
				}
				if(UserKeyVal==KEYS_QUSHI_VALUE)//锁定状态下长按取水键5秒，调节默认取水时间
				{
					if(setGetWaterTime_inSetting!=0)
					{
						//if(gucv_set_watertime<gucv_set_boilingtemp) gucv_set_watertime++; else gucv_set_watertime=0;//取水时间值加1
						AdjUpSetWaterTime(gucv_set_watertime);
						
						CheckSetWaterTime(&gucv_set_watertime);//设置值合规性检查
						
						DisplayBlink_Start();//闪烁初始化处理,每次按下按键后闪烁处理点亮状态，避免按键切换时黑屏
						
						zd_buzzer_beep(1,2,0);//蜂鸣一声(3x50ms)
					}
					
				}
				if(UserKeyVal==KEYS_BAOWEN_VALUE)
				{
					if(setKeepWarmTime_inSetting!=0)
					{
						AdjUpSetWarmTime(gucv_set_warmtime);//保温时间值加1
						
						CheckSetWarmTime(&gucv_set_warmtime);//设置值合规性检查
						
						DisplayBlink_Start();//闪烁初始化处理,每次按下按键后闪烁处理点亮状态，避免按键切换时黑屏
						
						zd_buzzer_beep(1,2,0);//蜂鸣一声(3x50ms)
					}
				}
				if(UserKeyVal==KEYS_JIARE_VALUE)
				{
					if(setBoilingTemp_inSetting!=0)
					{
						AdjUpSetBoilingTemp(gucv_set_boilingtemp);//取水时间值加1
						
						CheckSetBoilingTemp(&gucv_set_boilingtemp);//设置值合规性检查
						
						DisplayBlink_Start();//闪烁初始化处理,每次按下按键后闪烁处理点亮状态，避免按键切换时黑屏
						
						zd_buzzer_beep(1,2,0);//蜂鸣一声(3x50ms)
					}
				}		
				
				
				
				zd_key_clear();//清除所有按键标志位
			}
			
			if(UserKeyLongPressed)//按键按下超过2秒后触发
			{
				if(KeyLongPressCount>500)//按键按下超过5秒
				{

					if(UserKeyVal==KEYS_QUSHI_VALUE)//锁定状态下长按取水键5秒，调节默认取水时间
					{
						setGetWaterTime_inSetting=1;//开始进入设置状态
						DisplayBlink_Start();
						zd_buzzer_beep(1,2,0);//蜂鸣一声(3x50ms)
					}
					if(UserKeyVal==KEYS_BAOWEN_VALUE)
					{
						setKeepWarmTime_inSetting=1;//开始进入设置状态
						DisplayBlink_Start();
						zd_buzzer_beep(1,2,0);//蜂鸣一声(3x50ms)
					}
					if(UserKeyVal==KEYS_JIARE_VALUE)
					{
						setBoilingTemp_inSetting=1;//开始进入设置状态
						DisplayBlink_Start();
						zd_buzzer_beep(1,2,0);//蜂鸣一声(3x50ms)
					}
										
					zd_key_clear();
					
				}
				//else if(KeyLongPressCount>300)//按键按下超过3秒
				//{}
				
			}
			
			
		break;
		case MACHINE_IDEL:
		
		//工作
		case MACHINE_WORK:



			//异常检测
			Error_Check();
			
			
			
			//目标温度设定，借用沸点温度设定标志
			if(setBoilingTemp_inSetting!=0)//在设置状态
			{
				DisplayBlink(BlinkTemp,gucv_set_temp);
				if(gulv_setting_exitmsec<zd_getUtc_100mSec())//超时自动保存退出
				{
					//saveTempSetVal();//保存设置温度值
					setBoilingTemp_inSetting=0; //清除设置标志位，停止闪烁显示
					gbv_heat_start_working=1;//完成设置后开始加热
				}
			}
			else//不在设置状态
			{
				if(gbv_temp_over)//短路-超温
					disError(1);
				else if(gbv_pot_up)//开路-提壶
					disError(2);
				else
				{
					//显示温度 
					if(mSec_x100_workbit)
					{
						if(gucv_real_temp>(gucv_temp_display))
						{
							gucv_temp_display++;//线性调整回差0
							gucv_temp_display_down_delay=0;//回差消除延时清零
							//如果线性调整后误差大于4时直接赋值
							if(gucv_real_temp>(gucv_temp_display+4))
								gucv_temp_display=gucv_real_temp;
							
						}
						else if(gucv_temp_display>(gucv_real_temp+1))
						{
							gucv_temp_display--;//线性调整回差1
							gucv_temp_display_down_delay=0;//回差消除延时清零
							//如果线性调整后误差大于4时直接赋值
							if(gucv_temp_display>(gucv_real_temp+4))
								gucv_temp_display=gucv_real_temp;
						}

						
						//实际温度在设定温度附近 锁定显示设定温度
						if((gucv_real_temp)>=(gucv_set_temp-2)&&(gucv_real_temp)<=(gucv_set_temp+2))
						{
							if(gubv_displaytemp_lock_settemp)
								gucv_temp_display=gucv_set_temp;
							else if((gucv_real_temp)>=(gucv_set_temp-1)&&(gucv_real_temp)<=(gucv_set_temp+1))
								gubv_displaytemp_lock_settemp=1;
						}
						else
							gubv_displaytemp_lock_settemp=0;

						if(gucv_temp_display>100) gucv_temp_display=100;//数值限制在100以内	
					}
					
					
					disTemp(gucv_temp_display);//(gucv_real_temp);//(gucv_temp_display);
				}
			}			
			
			//加热温度设置指示与加热工作指示
			disKeyLed((keyled_jiare),gbv_heat_start_working|setBoilingTemp_inSetting);

			
			//取水时间与工作指示
			if(gbv_pump_start_working)
			{
				disKeyLed((keyled_qushui),1);
				disTime(gucv_work_watertime);	
				if(gbv_stepmotor_workover&&mSec_x1000_workbit==1)
				{
					if(gucv_work_watertime>0) gucv_work_watertime--; else
					{
						 gbv_pump_start_working=0;
						 zd_buzzer_beep(1,2,0);//蜂鸣一声(3x50ms)
					}
				}
			}
			else
			{
				disKeyLed((keyled_qushui),0);
				Display_FixTime(0x00);
			}
			
			//保温工作指示
			disKeyLed((keyled_baowen),gbv_warm_start_working);
			



			//超温时跳过按键处理
			if(gbv_temp_over==1) break;



			if(UserKeyPressed_up)//按键按下松开后触发
			{

				if(UserKeyVal==KEYS_DIANYUAN_VALUE)
				{
					goToModeLock();

				};
				if(UserKeyVal==KEYS_QUSHI_VALUE)
				{
					if(gbv_pump_start_working==1)
					{
						gbv_pump_start_working=0;
						KeyQuickPressCount=0;//按键多击清零
					}
					else if(KeyQuickPressCount>=2)//按键多击达到2次或以上
					{
						gucv_work_watertime=gucv_set_watertime;
						gbv_pump_start_working=1;
					}
				}
				if(UserKeyVal==KEYS_BAOWEN_VALUE)
				{
					if(gbv_warm_start_working==1)
					{
						gbv_warm_start_working=0;
					}
					else
					{
						gulv_work_warmtime_sec=gucv_set_warmtime*3600;
						gbv_warm_start_working=1;
					}
				}
				if(UserKeyVal==KEYS_JIARE_VALUE)
				{
					if(setBoilingTemp_inSetting!=0)//在沸点设置状态(借用)时，加热键用来调节加热目标值
					{
						//if(gucv_set_temp<gucv_set_boilingtemp) gucv_set_temp+=5; else gucv_set_temp=0;//加热目标值加5
						AdjUpSetTemp(gucv_set_temp);
						
						CheckSetTemp(&gucv_set_temp);//设置值合规性检查
						
						DisplayBlink_Start();//闪烁初始化处理,每次按下按键后闪烁处理点亮状态，避免按键切换时黑屏
						
					}
					else//不在沸点设置状态时，加热键用来开启和关闭加热
					{
						if(gbv_heat_start_working==1)
						{
							gbv_heat_start_working=0;
						}
						else
						{
							gbv_heat_start_working=1;
						}
					}

				}				
				zd_buzzer_beep(1,2,0);//蜂鸣一声(3x50ms)
				zd_key_clear();//清除所有按键标志位
			}
			
			
			if(UserKeyLongPressed)
			{
				if(KeyLongPressCount>300)
				{
					if(UserKeyVal==KEYS_JIARE_VALUE&&gbv_heat_start_working==0)//只有在未开启加热时长按加热键才能触发沸点设置
					{
						setBoilingTemp_inSetting=1;//开始进入设置状态
						DisplayBlink_Start();
						zd_buzzer_beep(1,2,0);//蜂鸣一声(3x50ms)
					}
										
					zd_key_clear();
				}
			}
			
		break;


		default:
			if(UserKeyPressed_up||UserKeyLongPressed) zd_key_clear();//清除所有按键标志位
		break;
	}
	
}



/*****************************************************************************
*函数			: void HeatTmpUpCheck(void)
*函数功能描述 	: 加热温度上升检查（用于检查高原和生成防过充提前量）
*函数参数 		: 无
*函数返回值 	: 无
******************************************************************************/
void HeatTmpUpCheck(void)
{
	
    //加热继电器吸合时
    if(gbv_heat_start_working)
    {
		//计算简易温度修正值（暂定5秒）
        if(gucv_real_temp>PidTemp_DataNow)	{ PidTemp_DataNow=gucv_real_temp;  }
		
		if(GetUtcSec()>=TempDiff_LastActive_utcsec)
        {
            TempDiff_LastActive_utcsec=GetUtcSec()+5;
            
			//计算历史值与当前值偏差
			if(PidTemp_DataNow>PidTemp_DataAgo)
				PidTemp_DataDiff=PidTemp_DataNow-PidTemp_DataAgo;
            else
				PidTemp_DataDiff=0;

			//更新历史值
			PidTemp_DataAgo=PidTemp_DataNow;
            
			//放大偏差值（按倍数放大）
			PidTemp_DataDiff=PidTemp_DataDiff<<1;
            
            //限制修正值大小，最大提前8度关
            if(PidTemp_DataDiff>10) PidTemp_DataDiff=10;
		}


		//高原检测处理
		if(gucv_real_temp>(TempCheck30s_DataMax+1)||TempCheck30s_DataMax<82) //水温上升2度或水温低于高原沸点时，复位计时
		{
            TempCheck30s_DataMax=gucv_real_temp;
			TempCheck30s_LastActive_utcsec=GetUtcSec();
		}
        else
        {
			if(GetUtcSec()>(TempCheck30s_LastActive_utcsec+30))  //高原40秒无升温加热过程结束
			{
				gbv_heat_start_working=0;
			}
        }

		//实际温度到达设定温度处理
		if(gucv_real_temp>=gucv_set_temp) 
		{
			gbv_heat_start_working=0;
			zd_buzzer_beep(3,3,3);//蜂鸣三声(3x50ms)
		}



    }
    else//加热继电器不吸合时
    {
		 TempCheck30s_DataMax=gucv_real_temp;//每次加热关闭后重新值，复位高原检测变量
         PidTemp_DataNow=0; PidTemp_DataAgo=100;PidTemp_DataDiff=0;//每次加热关闭后重新值，复位温度修正检测变量
		 TempCheck30s_LastActive_utcsec=GetUtcSec();//高原检测从加热启动开始计时
         TempDiff_LastActive_utcsec=GetUtcSec();//温度修正检测从加热启动开始
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

		//空闲
		case MACHINE_IDEL:	
		//工作
		case MACHINE_WORK:


			//超温-关闭所有功能
			if(gbv_temp_over==1)
			{
				gbv_heat_start_working=0;
				gbv_pump_start_working=0;
				gbv_warm_start_working=0;
				break;
			}
		
			//提壶操作-关加热与抽水
			if(gbv_pot_up==1)
			{
				gbv_heat_start_working=0;
				gbv_pump_start_working=0;
			}

			//加热上升检查
			HeatTmpUpCheck();
						
			//加热工作
			if(gbv_heat_start_working)
			{
				if(gucv_heat_start_delay<2)//延时3秒启动
				{
					if(mSec_x1000_workbit==1) gucv_heat_start_delay++;
				}
				else
					HotRelay_IO_Ctrl(HotRelay_IO_ON);
			}
			else
			{
				if(gucv_heat_start_delay!=0)
				{
					gucv_heat_start_delay=0;
					gucv_set_temp=gucv_set_boilingtemp; //每次停机后设定温度重新赋值沸点温度
		
				}
				HotRelay_IO_Ctrl(HotRelay_IO_OFF);
			}
			
			//转向与取水工作
			if(gbv_pump_start_working)
			{
				//取水开启时转向
				if(gbv_pump_start_working_ago==0) 
				{
					gbv_stepmotor_workover=0;
					zd_motorStep_work(2,1000,0);
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
				if(gbv_pump_start_working_ago==1) 
				{
					gbv_stepmotor_workover=0;
					zd_motorStep_work(1,1000,0);
				}
			}
			
			//历史状态更新
			gbv_pump_start_working_ago=gbv_pump_start_working;
			
			//获取转向结束状态
			if(zd_motorStep_isbusy()==0)
				gbv_stepmotor_workover=1;
			

			
			//保温工作
			if(gbv_warm_start_working)
			{
				if(gulv_work_warmtime_sec>0)
				{
					if(mSec_x1000_workbit==1)
					 gulv_work_warmtime_sec--; 
				}
				else
				{
					 gbv_warm_start_working=0;
					 zd_buzzer_beep(1,2,0);//蜂鸣一声(3x50ms)
				}
				WarmRelay_IO_Ctrl(WarmRelay_IO_ON);	
			}
			else
			{
				WarmRelay_IO_Ctrl(WarmRelay_IO_OFF);	
			}


		break;		
		default:

		break;
	}
	
}


void app_base_run(void)
{
		if(mSec_x50_workbit)//每50ms调用一次
		{
			//蜂鸣器触发与控制
			zd_buzzerRun();
		
			gucv_real_temp=CalcTmpC(waterout_Temp_ad,gucv_real_temp);
		}
		
		if(mSec_x100_workbit)//每100ms调用一次
		{


			
		}

		if(mSec_x10_workbit)//每10ms调用一次
		{
			//ad自动化轮询采集与回调执行
			if((*T_BuzzerEn)!=0)
				adc_buzz_delay_cnt=5;
			else if(adc_buzz_delay_cnt>0)
				adc_buzz_delay_cnt--;
			else zd_adcRun();


			//中微触控取值
			__CMS_CheckTouchKey();	//扫描按键
									
			//按键扫描,产生按键触发标志与键值信息
			zd_keyRun();
			
			//步进电机
			zd_motorStep_run();

		}
	

}
