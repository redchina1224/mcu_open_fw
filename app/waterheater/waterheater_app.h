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
#ifndef __FUNCTION_WATERHEATER_H__
#define __FUNCTION_WATERHEATER_H__
//******************************************************************


//----机器状态定义
#define			MACHINE_POWER_ON			0			//上电
#define			MACHINE_IDEL				1			//待机
#define			MACHINE_WORK_TEMP				2			//正常工作模式
#define			MACHINE_WORK_POWER		3
#define			MACHINE_SELF_CHECK	4			//自检
#define			MACHINE_ERROR				200			//故障


#include "position_pid_app.h"


struct zd_app_set_t {
unsigned char temp;//温度设定
unsigned char power;//功率设定
unsigned char mode;//上电模式设定
}


struct zd_app_work_t {
unsigned char intemp;//温度设定
unsigned char outtemp;//温度设定
unsigned int waterin_ad;
unsigned int waterout_ad;
unsigned char power;//功率设定
unsigned char mode;//上电模式设定
unsigned char water_speed;
}





struct  zd_app_t {
struct zd_app_set_t set;
struct zd_app_work_t work;
struct zd_pospid_t pid;
};





void app_init(void);
void App_Run(void);
void Background_Run(void);
void app_base_run(void);

#endif 


/************************ (C) COPYRIGHT zhejiang zhida *****END OF FILE****/