//******************************************************************************
//Copyright(C) 2020-2021 zhejiang zhida dianzikeji Co., Ltd
//浙江智达电子科技有限公司
//File name:      variable.h
//Author:         zzg
//Version:        Ver0.1
//Date:           2021-4-25
//Description:    全局头文件调用/全局宏定义声明/全局变量声明
//History:
//******************************************************************************
#ifndef _VARIABLE_H__
#define _VARIABLE_H__
//公共头文件********************************************************************

//公共宏定义********************************************************************
//公共宏定义********************************************************************
//TM1640定义
#define CFG_DATA_CMD_SETTING    0x44
#define CFG_BRIGHTNESS          4
#define SET_DIN()   RC5=1		//RC5是DIN
#define CLR_DIN()   RC5=0
#define SET_SCLK()  RC4=1		//RC4是clk
#define CLR_SCLK()  RC4=0
#define INIT_TRIS() TRISC &= ~0x30		//设置RC4 RC5为输出
#define M_DISP_CTRL_SETTING(en) ((0x80 + CFG_BRIGHTNESS) | (en << 3))
//----温度过高AD值
#define			TEMP_HIGH					55			//温度  55度
#define			TEMP_OPEN					1000		//温度开路
#define			TEMP_SHORT					10			//温度短路
//----默认PWM速度
#define			PEM_DEFAULT_DATA			50			//默认PWM数据
//----水流速度
#define			WATER_SPEED_LOW				9				//水流速度过慢
//----故障定义
#define			ERROR_E1					0X01		//E1,漏电
#define			ERROR_E2					0X02		//E2,水流传感器故障
#define			ERROR_E3					0X04		//E3,超温
#define			ERROR_E4					0X08		//E4,温度传感器故障
//----IO口定义
#define			IO_BUZZ						RB5			//蜂鸣器
#define			IO_KKG						RA3			//可控硅导通关闭
#define			IO_HALL_WATER				RA2			//水流大小霍尔检测
#define			IO_RELAY					RC2			//继电器输出,,
#define			IO_LEAKAGE_PRO				RC0			//漏电保护输入,
#define			IO_ZERO						RC3			//过零信号输入
#define			IO_IR						RB6			//红外输入
//----机器状态定义
#define			MACHINE_POWER_ON			0			//上电
#define			MACHINE_IDEL				1			//待机
#define			MACHINE_WORK				2			//正常工作模式
#define			MACHINE_SELF_CHECK			3			//自检
#define			MACHINE_ERROR				4			//故障
//----工作状态定义
#define			WORK_IDEL					0			//默认 工作模式
#define			WORK_MODE_SHUSHI			1			//舒适 工作模式
#define			WORK_MODE_ERTONG			2			//儿童 工作模式
#define			WORK_MODE_LAOREN			3			//老人 工作模式
#define			WORK_MODE_ZHINENG			4			//智能 工作模式
#define			WORK_MODE_CHUBAO			5			//厨宝 工作模式
#define			WORK_MODE_XIYI  			6			//洗衣 工作模式
//----温度设定
#define			TEMP_38TEMP					38			//38度恒温 工作
#define			TEMP_40TEMP					40			//38度恒温 工作
#define			TEMP_42TEMP					42			//42度恒温 工作
#define			TEMP_45TEMP					45			//38度恒温 工作
#define			TEMP_MINIMUM				30			//最小温度
#define			TEMP_MAXIMUM				52			//最大温度
//----按键值
#define			KEY_TEMP_38					0X00000020	//恒温38
#define			KEY_TEMP_40					0X00000001	//恒温40
#define			KEY_TEMP_42					0X00000002	//恒温42
#define			KEY_TEMP_45					0X00000008	//恒温45
#define			KEY_START					0X00000004	//开机
#define			KEY_TEMP_DOWN				0X00000010	//温度下降
#define			KEY_MODE					0X00000080	//模式切换
#define			KEY_TEMP_UP					0X00000040	//温度上升
#define			KEY_START_LONG				0X10000004	//开机按键长按
#define			KEY_LEARN_LONG				0X10000050	//温度上升和下降
//----按键扫描时间为1ms,
#define			KEY_DOWN_TIME				5			//按键按下过滤时间
#define			KEY_UP_TIME					5			//按键抬起过滤时间
#define			KEY_LONG_TIME_CONTINUE		10			//长按键连续触发时间
#define			KEY_ERROR_TIME				1000		//按键一直按下报警
#define			KEY_LONG_TIME				100		//1秒,,
#define			KEY_LONG_TIME_3S			300		//3秒,,
//申明外部变量********************************************************************
//----水温控制
extern	unsigned	char	gucv_water_temp_con_step;		//水温控制步骤
extern	unsigned	char	gucv_kkg_temp_data;				//可控硅数据 中间计算用
extern	unsigned	int		guiv_water_temp_wending_time;	//水温稳定时间
//----时间相关
extern	unsigned	char	gucv_base_time_1ms;				//基准时间1ms
extern	unsigned	char	gucv_time_1ms;					//1ms
extern	unsigned	char	gucv_time_1ms_adc;				//1ms adc使用
extern	unsigned	char	gucv_time_1ms_CHECK_KEY;		//1ms 按键库函数调用使用
extern	unsigned	char	gucv_time_500ms_flicker;		//500ms,0-1两种状态
extern	unsigned	char	gucv_time_1s;					//1S计时
//----工作相关
extern	bit					gbv_kkg_out_en;					//可控硅输出允许
extern	bit					gbv_arrive_set_temp;			//达到设定温度
extern	bit					gbv_error_en;					//可以报警
extern	unsigned	char	gucv_error_status;				//故障状态
extern	unsigned	char	gucv_machine_status;			//机器状态
extern	unsigned	char	gucv_machine_status_bak;		//机器状态,在报警恢复后 恢复机器状态
extern	unsigned	char	gucv_work_status;				//工作状态 默认智能
extern	unsigned	char	gucv_power_status;				//功率状态
extern	unsigned	char	gucv_real_temp;					//真实温度
extern	unsigned	char	gucv_in_water_temp;				//进水口温度
extern	unsigned	char	gucv_set_temp;					//设置温度
extern	unsigned	int 	guiv_real_voltage;				//电压
extern	unsigned	char 	gucv_water_pluse_count;			//水流脉冲数
//extern	unsigned	char 	gucv_water_speed;				//水流速度
extern	unsigned	int 	guiv_water_led_pmd;				//水流LED跑马灯
extern	unsigned	int 	guiv_work_low_temp_count;		//水温一直没有达到计时
extern	unsigned	int 	guiv_work_adj_time;				//工作时调整可控硅输出间隔时间
extern	unsigned	char 	gucv_work_kkg_drv_data;			//工作时可控硅驱动时间 0-100  一共100级
extern	unsigned	char 	gucv_voltage_collect_en_count;	//采集电压允许,,在开机的时候 电压会突变 屏蔽开机采集
extern	unsigned	int		guiv_dis_power_status_time;		//正在设定功率档位
extern	unsigned	int		guiv_temp_display_time;			//显示温度补偿计时
extern	unsigned	int		guiv_temp_display_data;			//显示温度补偿值
extern	unsigned	int		guiv_learn_time;				//学习时间

//----自检相关

//----EEPROM相关
extern	bit					gbv_write_en;					//允许记录数据
extern	unsigned	char	eeprom_work_temp[3];			//保存的设置温度

//----功率表格  80份 1份表示75W
extern	const	unsigned char	cucv_power_Tab[81];

#endif 

/************************ (C) COPYRIGHT zhejiang zhida *****END OF FILE****/




