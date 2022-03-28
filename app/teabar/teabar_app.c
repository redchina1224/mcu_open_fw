#include "..\com_include_app.h"
  
#define PlateauCheckSet_TempStart 82
#define PlateauCheckSet_TempDiff 2
#define PlateauCheckSet_TimeOutSec 30



/*****************************************************************************
*����		: void PlateauCheck(void)
*������������ 	: ��ԭ��飨���ڼ���ԭģʽ����ÿ�����һ��
*�������� 	: ��
*��������ֵ 	: ��
******************************************************************************/
unsigned char PlateauCheck_PerSecond(unsigned char lucv_real_temp,unsigned char lucv_CheckEn)
{
	static unsigned char lucv_TempCheck_Max
	static unsigned char lucv_TempCheck_TimeSec
	
    //����ʱʹ�ܼ��
    if(lucv_CheckEn!=0)
    {

		//��ԭ��⴦��
		if(lucv_real_temp>=lucv_TempCheck_Max||lucv_TempCheck_Max<PlateauCheck_Temp) //ˮ������2�Ȼ�ˮ�µ��ڸ�ԭ�е�ʱ����λ��ʱ
		{
            		lucv_TempCheck_Max=lucv_real_temp+PlateauCheck_TempDiff;
			lucv_TempCheck_TimeSec=0;
		}
        	else if(++lucv_TempCheck_TimeSec>PlateauCheckSet_TimeOutSec)
        	{
			lucv_TempCheck_TimeSec=PlateauCheckSet_TimeOutSec;
			return 1; //������ԭʱ����1
        	}

    }
    else//�ǹ���ʱ��λ�������
    {
		 lucv_TempCheck_Max=0;//ÿ�μ��ȹرպ󣬸�λ��ԭ������
		 lucv_TempCheck_TimeSec=0;//��ԭ���Ӽ���������ʼ��ʱ,�ǹ���ģʽ����
    }
    

    return 0;

}
