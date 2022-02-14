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


unsigned char motorWorkEn=0;

unsigned char motorWorkDir=0;
unsigned char motorWorkStepSelectCase=0;
unsigned long motorWorkStep_cnt=0;
unsigned char motorWorkSpeed_x50ms_cnt;
unsigned char motorWorkSpeed_repeat;



/***********************************************************************************************
*函数名 		: void zd_motorStep_isbusy(void)
*函数功能描述 	: 步进驱动忙标志位
*函数参数 		: 无，
*函数返回值 	: 无
***********************************************************************************************/
unsigned char zd_motorStep_isbusy(void)
{
	return motorWorkEn;
}

/***********************************************************************************************
*函数名 		: void zd_motorStep_select(unsigned char stepcase)
*函数功能描述 	: 步进驱动位
*函数参数 		: stepcase=步进驱动步位置，
*函数返回值 	: 无
***********************************************************************************************/

void zd_motorStep_select(unsigned char stepcase)
{
	switch(stepcase)
	{
		case 1:
				MotorStepA_IO_Channel=MotorStep_IO_ON;
				MotorStepB_IO_Channel=MotorStep_IO_OFF;
				MotorStepD_IO_Channel=MotorStep_IO_OFF;
		break;
		case 2:
				MotorStepB_IO_Channel=MotorStep_IO_ON;
				MotorStepA_IO_Channel=MotorStep_IO_OFF;
				MotorStepC_IO_Channel=MotorStep_IO_OFF;
		break;
		case 3:
				MotorStepC_IO_Channel=MotorStep_IO_ON;
				MotorStepB_IO_Channel=MotorStep_IO_OFF;
				MotorStepD_IO_Channel=MotorStep_IO_OFF;
		break;
		case 4:
				MotorStepD_IO_Channel=MotorStep_IO_ON;
				MotorStepA_IO_Channel=MotorStep_IO_OFF;
				MotorStepC_IO_Channel=MotorStep_IO_OFF;
		break;
		
		default:
		MotorStepA_IO_Channel=MotorStep_IO_OFF;
		MotorStepB_IO_Channel=MotorStep_IO_OFF;
		MotorStepC_IO_Channel=MotorStep_IO_OFF;
		MotorStepD_IO_Channel=MotorStep_IO_OFF;
		break;

	}
	
}
/***********************************************************************************************
*函数名 		: void zd_motorStep_work(unsigned char dir,unsigned long stepCount,unsigned char speed)
*函数功能描述 	: 步进电机工作任务设置，设置后自动开始工作
*函数参数 		: dir=工作方向，0=锁定当前位置，1=正转，2=反转
				  stepCount=要工作的脉冲步数 ,
				  speed=脉冲间隔时间,转速 (x50ms)
*函数返回值 	: 无
***********************************************************************************************/
void zd_motorStep_work(unsigned char dir,unsigned long stepCount,unsigned char speed)
{
	motorWorkEn=1;
	motorWorkDir=dir;
	motorWorkStep_cnt=stepCount;
	motorWorkSpeed_repeat=speed;
	motorWorkSpeed_x50ms_cnt=0;
}


/***********************************************************************************************
*函数名 			: void zd_buzzerRun(void)
*函数功能描述 		: 步进电机自动控制(速度，脉冲数),需每50ms调用一次
*函数参数 			: 无
*函数返回值 		: 无
***********************************************************************************************/
void zd_motorStep_run(void)//每50ms调用一次
{
	if(motorWorkStep_cnt>0)
	{
		motorWorkEn=1;
		if(++motorWorkSpeed_x50ms_cnt>motorWorkSpeed_repeat)
		{
			motorWorkSpeed_x50ms_cnt=0;
			
			if(motorWorkDir==1)
			{
				if(motorWorkStepSelectCase<4) motorWorkStepSelectCase++; else motorWorkStepSelectCase=1;
			}
			else if(motorWorkDir==2)
			{
				if(motorWorkStepSelectCase>1) motorWorkStepSelectCase--; else motorWorkStepSelectCase=4;
			}
			
			zd_motorStep_select(motorWorkStepSelectCase);
			
			motorWorkStep_cnt--;

		}

	}
	else
	{
		motorWorkEn=0;
		zd_motorStep_select(0);
	}
}



/***********************************************************************************************
*函数名 			: void zd_motorStep_init(void)
*函数功能描述 		: 步进电机初始化
*函数参数 			: 无
*函数返回值 		: 无
***********************************************************************************************/
void zd_motorStep_init(void)
{
MotorStep_IO_Output;
motorWorkStep_cnt=0;
zd_motorStep_select(0);
}


#endif //#if (MotorType==MotorType_Step)
#endif //#ifdef MotorType

/************************ (C) COPYRIGHT zhejiang zhida *****END OF FILE****/