//******************************************************************************
//Copyright(C) 2020-2021 zhejiang zhida dianzikeji Co., Ltd
//浙江智达电子科技有限公司
//File name:      variable.c
//Author:         zzg
//Version:        Ver0.1
//Date:           2021-4-25
//Description:    全局变量定义
//History:
//******************************************************************************
//头文件************************************************************************
#include "variable.h"
//变量**************************************************************************
//----水温控制
unsigned	char	gucv_water_temp_con_step=0;			//水温控制步骤
unsigned	char	gucv_kkg_temp_data=0;				//可控硅数据 中间计算用
unsigned	int		guiv_water_temp_wending_time=0;		//水温稳定时间
//----时间相关
unsigned	char	gucv_base_time_1ms=0;				//基准时间1ms
unsigned	char	gucv_time_1ms=0;					//1ms
unsigned	char	gucv_time_1ms_adc=0;				//1ms adc使用
unsigned	char	gucv_time_1ms_CHECK_KEY=0;			//1ms 按键库函数调用使用
unsigned	char	gucv_time_500ms_flicker=0;			//500ms,0-1两种状态
unsigned	char	gucv_time_1s=0;						//1S计时
//----工作相关
bit					gbv_kkg_out_en=0;					//可控硅输出允许
bit					gbv_arrive_set_temp=0;				//达到设定温度
bit					gbv_error_en=0;						//可以报警
unsigned	char	gucv_error_status=0;				//故障状态
unsigned	char	gucv_machine_status=0;				//机器状态
unsigned	char	gucv_machine_status_bak=0;			//机器状态,在报警恢复后 恢复机器状态
unsigned	char	gucv_power_status=0;				//功率状态
unsigned	char	gucv_work_status=0;					//工作状态
unsigned	char	gucv_real_temp=25;					//真实温度
unsigned	char	gucv_in_water_temp=25;				//进水口温度
unsigned	char	gucv_set_temp=0;					//设置温度
unsigned	int 	guiv_real_voltage=0;				//电压
unsigned	char 	gucv_water_pluse_count=0;			//水流脉冲数
//unsigned	char 	gucv_water_speed=0;					//水流速度
unsigned	int 	guiv_water_led_pmd=0;				//水流LED跑马灯
unsigned	int 	guiv_work_low_temp_count=0;			//水温一直没有达到计时
unsigned	int 	guiv_work_adj_time=0;				//工作时调整可控硅输出间隔时间
unsigned	char 	gucv_work_kkg_drv_data=0;			//工作时可控硅驱动时间 0-100  一共100级
unsigned	char 	gucv_voltage_collect_en_count=0;	//采集电压允许,,在开机的时候 电压会突变 屏蔽开机采集
unsigned	int		guiv_dis_power_status_time=0;		//正在设定功率档位
unsigned	int		guiv_temp_display_time=0;			//显示温度补偿计时
unsigned	int		guiv_temp_display_data=0;			//显示温度补偿值
unsigned	int		guiv_learn_time=0;					//学习时间



//----EEPROM相关
bit					gbv_write_en=0;						//允许记录数据
unsigned	char	eeprom_work_temp[3];				//保存的设置温度
//----显示相关

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
/************************ (C) COPYRIGHT zhejiang zhida *****END OF FILE****/

