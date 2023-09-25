//******************************************************************************
//Copyright(C) 2020-2021 zhejiang zhida dianzikeji Co., Ltd
//�㽭�Ǵ���ӿƼ����޹�˾
//File name:      buzz.c
//Author:         zzg
//Version:        Ver0.1
//Date:           2021-4-25
//Description:    ����������
//History:
//******************************************************************************
//ͷ�ļ�************************************************************************
#include "..\..\com_include_drv.h"
//��������***********************************************************************

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
*������ 		: void zd_motorStep_isbusy(void)
*������������ 	: ��������æ��־λ
*�������� 		: �ޣ�
*��������ֵ 	: ��
***********************************************************************************************/
unsigned char mof_motorStep_isbusy(mof_motor_step_t *obj)
{
	return obj->WorkEn;
}

/***********************************************************************************************
*������ 		: void zd_motorStep_select(unsigned char stepcase)
*������������ 	: ��������λ
*�������� 		: stepcase=����������λ�ã�
*��������ֵ 	: ��
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
									
					//�����Ӧλ
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
			
			//�����Ӧλ
			if(MotorStep_Select==0)
			{
				//�ر����,����Ҫ��������
				MOTOR_STEP_CTRL_OFF;
			}
#if(MOTOR_STEP_TOTAL_NUM>1)
			else if(MotorStep_Select==1)
			{
				//�ر����,����Ҫ��������
				MOTOR2_STEP_CTRL_OFF;
			}
#endif
		}

		
	if(++MotorStep_Select>=MOTOR_STEP_TOTAL_NUM) MotorStep_Select=0;
}
/***********************************************************************************************
*������ 		: void zd_motorStep_work(unsigned char dir,unsigned long stepCount,unsigned char speed)
*������������ 	: ������������������ã����ú��Զ���ʼ����
*�������� 		: dir=��������0=������ǰλ�ã�1=��ת��2=��ת
				  stepCount=Ҫ���������岽�� ,
				  speed=������ʱ��,ת�� (x50ms)
*��������ֵ 	: ��
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
*������ 			: void zd_buzzerRun(void)
*������������ 		: ��������Զ�����(�ٶȣ�������),��ÿ50ms����һ��
*�������� 			: ��
*��������ֵ 		: ��
***********************************************************************************************/
void zd_motorStep_run(void)//ÿ50ms����һ��
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
*������ 			: void zd_motorStep_init(void)
*������������ 		: ���������ʼ��
*�������� 			: ��
*��������ֵ 		: ��
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