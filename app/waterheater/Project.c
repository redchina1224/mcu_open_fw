#include ".\CTK_Library\Config.h"

/****************************************************************/
//��������void Project(void)
//��  �ܣ���Ŀ��Ŀ���ܺ���
//��  ������
//����ֵ����
/****************************************************************/
void Project(void)//����
{
	
	time_process();					//ʱ������
	
	//1msִ�г���
	if(gucv_time_1ms>0)
	{
		gucv_time_1ms--;
		updatadisbuff();			//ˢ����ʾ����
		buzzer_process();			//����������
		function_process();		//��������
		key_process();				//��������
		key_scan();						//����ɨ��
		adc_process();				//ADC�ɼ�����
	}
}