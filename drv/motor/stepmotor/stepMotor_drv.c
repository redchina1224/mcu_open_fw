//******************************************************************************
//Copyright(C) 2020-2021 zhejiang zhida dianzikeji Co., Ltd
//浙江智达电子科技有限公司
//File name:      buzz.c
//Author:         zzg
//Version:        Ver0.1
//Date:           2021-4-25
//Description:    蜂鸣器处理
//History:
//******************************************************************************
//头文件************************************************************************
#include "..\..\com_include_drv.h"
//函数定义***********************************************************************

#ifdef MotorType
#if (MotorType==MotorType_Step)

#define MotorStepPhase 4
#define MotorStepSubdiv 2
#define MotorStepTotal (MotorStepSubdiv*MotorStepPhase)

const unsigned char Motor_Step_Ctrl_List[MotorStepTotal]={(BIT0),(BIT0|BIT1),(BIT1),(BIT1|BIT2),(BIT2),(BIT2|BIT3),(BIT3),(BIT3|BIT0)};

unsigned char MotorStep_Select=0;

#ifdef MOTOR_STEP_TOTAL_NUM
	mof_motor_step_t MotorStep_Object[MOTOR_STEP_TOTAL_NUM];
#else
	mof_motor_step_t MotorStep_Object[1];
#endif


/***********************************************************************************************
*函数名 		: void zd_motorStep_isbusy(void)
*函数功能描述 	: 步进驱动忙标志位
*函数参数 		: 无，
*函数返回值 	: 无
***********************************************************************************************/
unsigned char mof_motorStep_isbusy(mof_motor_step_t *obj)
{
	return obj->WorkEn;
}

/***********************************************************************************************
*函数名 		: void zd_motorStep_select(unsigned char stepcase)
*函数功能描述 	: 步进驱动位
*函数参数 		: stepcase=步进驱动步位置，
*函数返回值 	: 无
***********************************************************************************************/
void mof_motor_step_plus_in_isr(void)
{
		if(MotorStep_Object[MotorStep_Select].WorkEn!=0)
		{
			if((++(MotorStep_Object[MotorStep_Select].WorkSpeed_cnt)>=MotorStep_Object[MotorStep_Select].WorkSpeed))
			{
				MotorStep_Object[MotorStep_Select].WorkSpeed_cnt=0;
				if(MotorStep_Object[MotorStep_Select].WorkSpeed>MotorStep_Object[MotorStep_Select].WorkSpeed_set) MotorStep_Object[MotorStep_Select].WorkSpeed--;
				
				if(MotorStep_Object[MotorStep_Select].WorkStep_cnt!=0)
				{
					if(MotorStep_Object[MotorStep_Select].WorkStep_cnt>0)
					{
						if(MotorStep_Object[MotorStep_Select].StepSelectCase<(MotorStepTotal-1)) MotorStep_Object[MotorStep_Select].StepSelectCase++; else MotorStep_Object[MotorStep_Select].StepSelectCase=0;
						MotorStep_Object[MotorStep_Select].WorkStep_cnt--;
						MotorStep_Object[MotorStep_Select].WorkStepCurrent++;
					}
					else if(MotorStep_Object[MotorStep_Select].WorkStep_cnt<0)
					{
						if(MotorStep_Object[MotorStep_Select].StepSelectCase>0) MotorStep_Object[MotorStep_Select].StepSelectCase--; else MotorStep_Object[MotorStep_Select].StepSelectCase=(MotorStepTotal-1);
						MotorStep_Object[MotorStep_Select].WorkStep_cnt++;
						MotorStep_Object[MotorStep_Select].WorkStepCurrent--;
					}
									
					//输出对应位
					if(MotorStep_Select==0)
					{
						MOTOR_STEP_CTRL(Motor_Step_Ctrl_List[MotorStep_Object[MotorStep_Select].StepSelectCase]);
					}
		#if(MOTOR_STEP_TOTAL_NUM>1)
					else if(MotorStep_Select==1)
					{
						MOTOR2_STEP_CTRL(Motor_Step_Ctrl_List[MotorStep_Object[MotorStep_Select].StepSelectCase]);
					}
		#endif

				}
				else
				{
					MotorStep_Object[MotorStep_Select].WorkEn=0;
				}
			}
		}
		else
		{
			
			//输出对应位
			if(MotorStep_Select==0)
			{
				//关闭输出,不需要锁定保持
				MOTOR_STEP_CTRL_OFF;
			}
#if(MOTOR_STEP_TOTAL_NUM>1)
			else if(MotorStep_Select==1)
			{
				//关闭输出,不需要锁定保持
				MOTOR2_STEP_CTRL_OFF;
			}
#endif
		}

		
	if(++MotorStep_Select>=MOTOR_STEP_TOTAL_NUM) MotorStep_Select=0;
}
/***********************************************************************************************
*函数名 		: void zd_motorStep_work(unsigned char dir,unsigned long stepCount,unsigned char speed)
*函数功能描述 	: 步进电机工作任务设置，设置后自动开始工作
*函数参数 		: dir=工作方向，0=锁定当前位置，1=正转，2=反转
				  stepCount=要工作的脉冲步数 ,
				  speed=脉冲间隔时间,转速 (x50ms)
*函数返回值 	: 无
***********************************************************************************************/
//void mof_motorStep_work(mof_motor_step_t *obj,signed long stepCount,unsigned char speed)
//{
//	obj->WorkStep_cnt=stepCount;
//	#if(MOTOR_STEP_TOTAL_NUM>1)
//		obj->WorkSpeed=speed/MOTOR_STEP_TOTAL_NUM;
//	#else
//		obj->WorkSpeed=speed;
//	#endif
//	
//}
void mof_motorStep_work(unsigned char motor_n,signed int stepCount,unsigned char speed)
{
	MotorStep_Object[motor_n].WorkEn=1;
	MotorStep_Object[motor_n].WorkStep_cnt=stepCount;
	#if(MOTOR_STEP_TOTAL_NUM>1)
		MotorStep_Object[motor_n].WorkSpeed_set=speed/MOTOR_STEP_TOTAL_NUM;
	#else
		MotorStep_Object[motor_n].WorkSpeed_set=speed;
	#endif
	
	MotorStep_Object[motor_n].WorkSpeed=(MOTORSTEP_SPEED_DEFAULT/MOTOR_STEP_TOTAL_NUM);
	//MotorStep_Object[motor_n].WorkSpeed=MotorStep_Object[motor_n].WorkSpeed_set;
	
}


/***********************************************************************************************
*函数名 			: void zd_buzzerRun(void)
*函数功能描述 		: 步进电机自动控制(速度，脉冲数),需每50ms调用一次
*函数参数 			: 无
*函数返回值 		: 无
***********************************************************************************************/
void zd_motorStep_run(void)//每50ms调用一次
{
//	if(motorWorkStep_cnt!=0)
//	{
//		motorWorkEn=1;
//		if(++motorWorkSpeed_cnt>motorWorkSpeed)
//		{
//			motorWorkSpeed_cnt=0;
//			
//			if(motorWorkDir==1)
//			{
//				if(motorStepSelectCase<4) motorStepSelectCase++; else motorStepSelectCase=1;
//			}
//			else if(motorWorkDir==2)
//			{
//				if(motorStepSelectCase>1) motorStepSelectCase--; else motorStepSelectCase=4;
//			}
//			
//			zd_motorStep_select(motorStepSelectCase);
//			
//			motorWorkStep_cnt--;

//		}

//	}
//	else
//	{
//		motorWorkEn=0;
//		zd_motorStep_select(0);
//	}
}


/***********************************************************************************************
*函数名 			: void zd_motorStep_init(void)
*函数功能描述 		: 步进电机初始化
*函数参数 			: 无
*函数返回值 		: 无
***********************************************************************************************/
void mof_motorStep_init(void)
{
	unsigned char i;
MOTOR_STEP_IO_OUTPUT;
#if (MOTOR_STEP_TOTAL_NUM>1)
	MOTOR2_STEP_IO_OUTPUT;
#endif
	for(i=0;i<MOTOR_STEP_TOTAL_NUM;i++)
	{
		MotorStep_Object[i].WorkEn=0;
		MotorStep_Object[i].WorkStep_cnt=0;
		MotorStep_Object[i].WorkStepCurrent=0;
		MotorStep_Object[i].WorkSpeed_cnt=0;
		MotorStep_Object[i].WorkSpeed_set=MOTORSTEP_SPEED_DEFAULT/MOTOR_STEP_TOTAL_NUM;
		MotorStep_Object[i].WorkSpeed=MOTORSTEP_SPEED_DEFAULT/MOTOR_STEP_TOTAL_NUM;
		MotorStep_Object[i].StepSelectCase=0;
		//MotorStep_Object[i].Step_Case_Max=(MotorStepTotal-1);
	}
}


#endif //#if (MotorType==MotorType_Step)
#endif //#ifdef MotorType

/************************ (C) COPYRIGHT zhejiang zhida *****END OF FILE****/