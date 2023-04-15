//******************************************************************************
//Copyright(C) 2020-2021 zhejiang zhida dianzikeji Co., Ltd
//�㽭�Ǵ���ӿƼ����޹�˾
//File name:      buzz.h
//Author:         zzg
//Version:        Ver0.1
//Date:           2021-4-25
//Description:    �������
//History:
//******************************************************************************
#ifndef __MOTORSTEP_DRV_H__
#define __MOTORSTEP_DRV_H__
//�����ⲿ����******************************************************************


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
*������ 		: void zd_motorStep_isbusy(void)
*������������ 	: ��������æ��־λ
*�������� 		: �ޣ�
*��������ֵ 	: ��
***********************************************************************************************/
unsigned char mof_motorStep_isbusy(mof_motor_step_t *obj);

/***********************************************************************************************
*������ 		: void zd_motorStep_work(unsigned char dir,unsigned long stepCount,unsigned char speed)
*������������ 	: ������������������ã����ú��Զ���ʼ����
*�������� 		: dir=��������0=������ǰλ�ã�1=��ת��2=��ת
				  stepCount=Ҫ���������岽�� ,
				  speed=������ʱ��,ת�� (x50ms)
*��������ֵ 	: ��
***********************************************************************************************/
//void mof_motorStep_work(mof_motor_step_t *obj,signed int stepCount,unsigned char speed);
void mof_motorStep_work(unsigned char motor_n,signed int stepCount,unsigned char speed);

/***********************************************************************************************
*������ 			: void zd_buzzerRun(void)
*������������ 		: ��������Զ�����(�ٶȣ�������),��ÿ50ms����һ��
*�������� 			: ��
*��������ֵ 		: ��
***********************************************************************************************/
//void zd_motorStep_run(void);


/***********************************************************************************************
*������ 			: void zd_motorStep_init(void)
*������������ 		: ���������ʼ��
*�������� 			: ��
*��������ֵ 		: ��
***********************************************************************************************/
void mof_motorStep_init(void);

/***********************************************************************************************
*������ 		: void zd_motorStep_select(unsigned char stepcase)
*������������ 	: ��������λ
*�������� 		: stepcase=����������λ�ã�
*��������ֵ 	: ��
***********************************************************************************************/
void mof_motor_step_plus_in_isr(void);

#endif 


/************************ (C) COPYRIGHT zhejiang zhida *****END OF FILE****/