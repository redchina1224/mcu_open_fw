#include "..\com_include_app.h"


bit gbv_take_water_working=0;
bit gbv_take_water_working_ago=0;
bit gbv_stepmotor_workover=0;


/***********************************************************************************************
*������ 		: core_DelayUs(unsigned char dl_t)
*������������ 	: ȡˮ���ܳ�ʼ��
*�������� 		: unsigned char dl_t����ʱ����Լ���ڿ�ָ������
*��������ֵ 	: ��
***********************************************************************************************/
void take_water_init(void)
{
	Take_Water_Pump_IO_Output;
	Take_Water_Pump_IO_Ctrl(ake_Water_Pump_IO_OFF);
	zd_motorStep_init();
}


/***********************************************************************************************
*������ 		: core_DelayUs(unsigned char dl_t)
*������������ 	: ȡˮ���ܺ�̨����
*�������� 		: unsigned char dl_t����ʱ����Լ���ڿ�ָ������
*��������ֵ 	: ��
***********************************************************************************************/
void take_water_background_Run(void)
{

	//ת����ȡˮ����
	if(gbv_take_water_working)
	{
		//ȡˮ����ʱת��
		if(gbv_take_water_working_ago==0) 
		{
			gbv_stepmotor_workover=0;
			zd_motorStep_work(GET_WATER_SETP_MOTOR_START_DIR,GET_WATER_SETP_MOTOR_PLUS_COUNT,GET_WATER_SETP_MOTOR_PLUS_SPEED);
		}
		
		//ת�������ʼȡˮ
		if(gbv_stepmotor_workover)
		{
			Pump_IO_Ctrl(Pump_IO_ON);
		}
		
	}
	else
	{
		//����ȡˮ
		Pump_IO_Ctrl(Pump_IO_OFF);
		//ȡˮ����ʱת��
		if(gbv_take_water_working_ago==1) 
		{
			gbv_stepmotor_workover=0;
			zd_motorStep_work(GET_WATER_SETP_MOTOR_END_DIR,GET_WATER_SETP_MOTOR_PLUS_COUNT,GET_WATER_SETP_MOTOR_PLUS_SPEED);
		}
	}
	
	//��ʷ״̬����
	gbv_take_water_working_ago=gbv_take_water_working;
	
	//��ȡת�����״̬
	if(zd_motorStep_isbusy()==0)
		gbv_stepmotor_workover=1;
}