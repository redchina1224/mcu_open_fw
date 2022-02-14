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


unsigned char motorWorkEn=0;

unsigned char motorWorkDir=0;
unsigned char motorWorkStepSelectCase=0;
unsigned long motorWorkStep_cnt=0;
unsigned char motorWorkSpeed_x50ms_cnt;
unsigned char motorWorkSpeed_repeat;



/***********************************************************************************************
*������ 		: void zd_motorStep_isbusy(void)
*������������ 	: ��������æ��־λ
*�������� 		: �ޣ�
*��������ֵ 	: ��
***********************************************************************************************/
unsigned char zd_motorStep_isbusy(void)
{
	return motorWorkEn;
}

/***********************************************************************************************
*������ 		: void zd_motorStep_select(unsigned char stepcase)
*������������ 	: ��������λ
*�������� 		: stepcase=����������λ�ã�
*��������ֵ 	: ��
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
*������ 		: void zd_motorStep_work(unsigned char dir,unsigned long stepCount,unsigned char speed)
*������������ 	: ������������������ã����ú��Զ���ʼ����
*�������� 		: dir=��������0=������ǰλ�ã�1=��ת��2=��ת
				  stepCount=Ҫ���������岽�� ,
				  speed=������ʱ��,ת�� (x50ms)
*��������ֵ 	: ��
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
*������ 			: void zd_buzzerRun(void)
*������������ 		: ��������Զ�����(�ٶȣ�������),��ÿ50ms����һ��
*�������� 			: ��
*��������ֵ 		: ��
***********************************************************************************************/
void zd_motorStep_run(void)//ÿ50ms����һ��
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
*������ 			: void zd_motorStep_init(void)
*������������ 		: ���������ʼ��
*�������� 			: ��
*��������ֵ 		: ��
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