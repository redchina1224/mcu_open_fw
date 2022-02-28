//******************************************************************************
//Copyright(C) 2020-2021 zhejiang zhida dianzikeji Co., Ltd
//�㽭�Ǵ���ӿƼ����޹�˾
//File name:      function.h
//Author:         zzg
//Version:        Ver0.1
//Date:           2021-4-25
//Description:    ����
//History:
//******************************************************************************
#ifndef __FUNCTION_WATERHEATER_H__
#define __FUNCTION_WATERHEATER_H__
//******************************************************************


//----����״̬����
#define			MACHINE_POWER_ON			0			//�ϵ�
#define			MACHINE_IDEL				1			//����
#define			MACHINE_WORK_TEMP				2			//��������ģʽ
#define			MACHINE_WORK_POWER		3
#define			MACHINE_SELF_CHECK	4			//�Լ�
#define			MACHINE_ERROR				200			//����


#include "position_pid_app.h"


struct zd_app_set_t {
unsigned char temp;//�¶��趨
unsigned char power;//�����趨
unsigned char mode;//�ϵ�ģʽ�趨
}


struct zd_app_work_t {
unsigned char intemp;//�¶��趨
unsigned char outtemp;//�¶��趨
unsigned int waterin_ad;
unsigned int waterout_ad;
unsigned char power;//�����趨
unsigned char mode;//�ϵ�ģʽ�趨
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