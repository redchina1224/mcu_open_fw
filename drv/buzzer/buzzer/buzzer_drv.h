//******************************************************************************
//Copyright(C) 2020-2021 zhejiang zhida dianzikeji Co., Ltd
//浙江智达电子科技有限公司
//File name:      buzz.h
//Author:         zzg
//Version:        Ver0.1
//Date:           2021-4-25
//Description:    蜂鸣器
//History:
//******************************************************************************
#ifndef __BUZZER_DRV_H__
#define __BUZZER_DRV_H__

/*
typedef struct {
unsigned char beepCnt;
unsigned char beepton_x50ms;
unsigned char beeptoff_x50ms;
} zd_buzzer_t;
*/



/***********************************************************************************************
*函数名 		: void zd_buzzer_beep(unsigned char beepCnt,unsigned char beepton_x50ms,unsigned char beeptoff_x50ms)
*函数功能描述 	: 蜂鸣器鸣响工作
*函数参数 		: beepCnt=蜂鸣次数，
				  beepton=鸣响的时长 (x50ms) ,
				  beeptoff=中间停止鸣响的时长 (x50ms)
*函数返回值 	: 无
***********************************************************************************************/
void zd_buzzer_beep(unsigned char beepCnt,unsigned char beepton_x50ms,unsigned char beeptoff_x50ms);



/***********************************************************************************************
*函数名 			: void zd_buzzerRun(void)
*函数功能描述 		: 蜂鸣器鸣响自动控制(鸣响时间，次数),需每50ms调用一次
*函数参数 			: 无
*函数返回值 		: 无
***********************************************************************************************/
void zd_buzzerRun(void);

/***********************************************************************************************
*函数名 			: void zd_buzzer_init(void)
*函数功能描述 		: 蜂鸣初始化
*函数参数 			: 无
*函数返回值 		: 无
***********************************************************************************************/
void zd_buzzer_init(void);


#endif 


/************************ (C) COPYRIGHT zhejiang zhida *****END OF FILE****/