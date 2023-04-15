//******************************************************************************
//Copyright(C) 2020-2021 zhejiang zhida dianzikeji Co., Ltd
//浙江智达电子科技有限公司
//File name:      buzz.h
//Author:         zzg
//Version:        Ver0.1
//Date:           2021-4-25
//Description:    步进电机
//History:
//******************************************************************************
#ifndef __MOTORSTEP_DRV_H__
#define __MOTORSTEP_DRV_H__
//声明外部函数******************************************************************


typedef struct
{
unsigned char WorkEn;
signed int WorkStepCurrent;
signed int WorkStep_cnt;
unsigned char WorkSpeed_cnt;
unsigned char WorkSpeed;
unsigned char StepSelectCase;
//unsigned char Step_Case_Max;
//unsigned char *Step_List;
} mof_motor_step_t;



#ifdef MOTOR_STEP_TOTAL_NUM
	extern mof_motor_step_t MotorStep_Object[MOTOR_STEP_TOTAL_NUM];
#else
	extern mof_motor_step_t MotorStep_Object[1];
#endif



/***********************************************************************************************
*函数名 		: void zd_motorStep_isbusy(void)
*函数功能描述 	: 步进驱动忙标志位
*函数参数 		: 无，
*函数返回值 	: 无
***********************************************************************************************/
unsigned char mof_motorStep_isbusy(mof_motor_step_t *obj);

/***********************************************************************************************
*函数名 		: void zd_motorStep_work(unsigned char dir,unsigned long stepCount,unsigned char speed)
*函数功能描述 	: 步进电机工作任务设置，设置后自动开始工作
*函数参数 		: dir=工作方向，0=锁定当前位置，1=正转，2=反转
				  stepCount=要工作的脉冲步数 ,
				  speed=脉冲间隔时间,转速 (x50ms)
*函数返回值 	: 无
***********************************************************************************************/
//void mof_motorStep_work(mof_motor_step_t *obj,signed int stepCount,unsigned char speed);
void mof_motorStep_work(unsigned char motor_n,signed int stepCount,unsigned char speed);

/***********************************************************************************************
*函数名 			: void zd_buzzerRun(void)
*函数功能描述 		: 步进电机自动控制(速度，脉冲数),需每50ms调用一次
*函数参数 			: 无
*函数返回值 		: 无
***********************************************************************************************/
//void zd_motorStep_run(void);


/***********************************************************************************************
*函数名 			: void zd_motorStep_init(void)
*函数功能描述 		: 步进电机初始化
*函数参数 			: 无
*函数返回值 		: 无
***********************************************************************************************/
void mof_motorStep_init(void);

/***********************************************************************************************
*函数名 		: void zd_motorStep_select(unsigned char stepcase)
*函数功能描述 	: 步进驱动位
*函数参数 		: stepcase=步进驱动步位置，
*函数返回值 	: 无
***********************************************************************************************/
void mof_motor_step_plus_in_isr(void);

#endif 


/************************ (C) COPYRIGHT zhejiang zhida *****END OF FILE****/