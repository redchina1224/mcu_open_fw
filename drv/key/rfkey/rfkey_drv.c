#include "..\..\com_include_drv.h"



unsigned long __ZD_RfKeyValue=0;

unsigned long gulv_Read_Data;
	
unsigned char ioL_timeout=0;		//IO�͵�ƽ��ʱ
unsigned char ioH_timeout=0;//IO�ߵ�ƽ��ʱ
unsigned char io_data_ago=0;		//IO��ƽ��ʷֵ

unsigned char bit_ioH_checktime=0;		//����λ�ж��ߵ�ƽʱ��ֵ
unsigned char bit_read_count=0;		//����λ����ֵ
//unsigned char test_bit_read_count=0;		//����λ�ж��ߵ�ƽʱ��ֵ


/***********************************************************************************************
*������ 		: void zd_touchkeyInit(void)
*������������ 	: ��ʼ��RFң�ذ���
*�������� 		: ��
*��������ֵ 	: ��
***********************************************************************************************/
void zd_rfkeyInit(void)
{
	#if (RfKeyType==RfKeyType_IoWidthCode)
		RFKEY_POWER_IO_Output;
		RFKEY_DATA_IO_Input;
		RFKEY_POWER_IO_Ctrl(RFKEY_POWER_IO_ON);
	#endif


}


/***********************************************************************************************
*������ 		: unsigned long zd_touchkeyRead(void)
*������������ 	: ��ȡRFң�ذ���ֵ
*�������� 		: unsigned long *keyval ������ֵ��ַָ��
*��������ֵ 	: unsigned char  ����ֵ״̬  1����ֵ�и���  0����ֵ�޸���
***********************************************************************************************/
unsigned char zd_rfkeyRead(unsigned long *keyval)
{
	if((*keyval)==__ZD_RfKeyValue)
	{
		return 0;
	}
	else
	{
		(*keyval)=__ZD_RfKeyValue;
		return 1;
	}
}

/***********************************************************************************************
*������ 		: void __ZD_GetRfKeyValue(void)
*������������ 	: �жϲɼ�RFң���ź�
*�������� 		: ��
*��������ֵ 	: ��
***********************************************************************************************/
void __ZD_GetRfKeyValue(void)
{

	if(RFKEY_DATA_IO_Channel==0)//�͵�ƽ
	{
		//�͵�ƽ��ʱ
		if(ioL_timeout<32)
		{
			ioL_timeout++;
			
			if(ioL_timeout>=32)
			{
				if(bit_read_count==25)
				{
					__ZD_RfKeyValue=gulv_Read_Data;
				}
				else
					__ZD_RfKeyValue=0;
				
				gulv_Read_Data=0;
				bit_read_count=0;
			}
		}
		else
		{
			return;
		}
		
		//�ߵ�ƽ��ʱ����
		ioH_timeout=0;
		
		//�͵�ƽ����
		if(io_data_ago==1)
		{
			io_data_ago=0;
			if(bit_ioH_checktime>=8)//λΪ1
			{
				gulv_Read_Data|=BIT0;
			}
			
			if(bit_read_count<32)
			{
				bit_read_count++;
			}
		}
	}
	else//�ߵ�ƽ
	{

		//�ߵ�ƽ��ʱ
		if(ioH_timeout<32)
		{
			ioH_timeout++;
			if(ioH_timeout>=32)
			{
				gulv_Read_Data=0;
				__ZD_RfKeyValue=0;
				bit_read_count=0;
			}
		}
		else
		{
			return;
		}
				
		//�͵�ƽ��ʱ����
		ioL_timeout=0;
		
		
		//�ߵ�ƽ����
		if(io_data_ago==0)
		{
			io_data_ago=1;
			bit_ioH_checktime=0;//�����ؿ�ʼ��Ϊ����λ1��0ʱ���ж�����ʼ��
			gulv_Read_Data<<=1;
		}
		else
			bit_ioH_checktime++;
	}
	
}

