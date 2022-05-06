//******************************************************************************
//Copyright(C) 2020-2021 zhejiang zhida dianzikeji Co., Ltd
//�㽭�Ǵ���ӿƼ����޹�˾
//File name:      touchkey_core.c
//Author:         zzg
//Version:        Ver0.1
//Date:           2021-4-25
//Description:    ����������׼�ӿ�
//History:
//******************************************************************************
//ͷ�ļ�************************************************************************
#include "com_include_core.h"


#ifdef KeyType
#if ((KeyType&KeyType_McuTouch)==KeyType_McuTouch)




#if (McuType==McuType_CmsSemicon_CMS79F738)
	#include "cms\touch_79ft73x\Touch_Kscan_Library.c"
#elif(McuType==McuType_FremontMicroDevices_FT62F13)
	#include "fmd\FT62F13X\Touch_Kscan_Library.c"
#endif





/***********************************************************************************************
*������ 		: void zd_touchkeyInit(void)
*������������ 	: ��ʼ����������
*�������� 		: ��
*��������ֵ 	: ��
***********************************************************************************************/
void zd_touchkeyInit(void)
{
	#if (McuType==McuType_SinOneChip_SC92F8463B)
		//��Ԫ΢���ذ�����ʼ��
		TouchKeyInit();	
	#elif (McuType==McuType_FremontMicroDevices_FT62F13)
		//��â΢���ذ�����ʼ��
    TOUCH_INITIAL();       //��ʼ��TOUCH�������
    Touch_init();             //��ȡ��ʼֵ

	#endif

}


/***********************************************************************************************
*������ 		: unsigned long zd_touchkeyRead(void)
*������������ 	: ��ʼ����������
*�������� 		: unsigned long *keyval ������ֵ��ַָ��
*��������ֵ 	: unsigned char  ����ֵ״̬  1����ֵ�и���  0����ֵ�޸���
***********************************************************************************************/
unsigned char zd_touchkeyRead(unsigned long *keyval)
{

		#if (McuType==McuType_SinOneChip_SC92F8463B)
		//��Ԫ΢����ȡֵ
		if(SOCAPI_TouchKeyStatus&0x80)	    //��Ҫ����2:  ������ɨ��һ�ֱ�־���Ƿ����TouchKeyScan()һ��Ҫ���ݴ˱�־λ�����
		 {	   																	
			SOCAPI_TouchKeyStatus &= 0x7f;	//��Ҫ����3: �����־λ�� ��Ҫ�ⲿ�����													    
			(*keyval) = TouchKeyScan();//�������ݴ�����   
			
			TouchKeyRestart();				//������һ��ת��		
			return 1;
		}
        #elif (McuType==McuType_FremontMicroDevices_FT62F13)
		//if(StartTouchTime >= (2500/SCANNINGTIME/TouchCount))//ɨ��ʱ�� ����ɨ�����ڼ�������������.  
		{
			//StartTouchTime=0;
			(*keyval)=TouchKeyScan();
            return 1;
		}
		#elif (McuType==McuType_CmsSemicon_CMS79F738)

		
		(*keyval)=_CMS_KeyFlag[2];
		(*keyval)<<=8;
		(*keyval)|=_CMS_KeyFlag[1];
		(*keyval)<<=8;
		(*keyval)|=_CMS_KeyFlag[0];
		
		//(*keyval)=(unsigned long)(_CMS_KeyFlag[0]);
		return 1;
		#endif
		
return 0;
}



#endif
#endif

/************************ (C) COPYRIGHT zhejiang zhida *****END OF FILE****/