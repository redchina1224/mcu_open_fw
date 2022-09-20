//******************************************************************************
//Copyright(C) 2020-2021 zhejiang zhida dianzikeji Co., Ltd
//�㽭�Ǵ���ӿƼ����޹�˾
//File name:      function.h
//Author:         zzg
//Version:        Ver0.1
//Date:           2021-4-25
//Description:    ����
//History:
//******************************************************************************
#ifndef __APPSTDLIB_SETTING_DISPALY_BLINK_APP_H__
#define __APPSTDLIB_SETTING_DISPALY_BLINK_APP_H__
//******************************************************************

struct  zd_setting_display_blink_t {
	struct {
		unsigned char blinkDisplayEn:1;
		unsigned char inSetting1:1;
		unsigned char inSetting2:1;
		unsigned char inSetting3:1;	
		unsigned char inSetting4:1;
		unsigned char inSetting5:1;
		unsigned char inSetting6:1;
		unsigned char inSetting7:1;		
	}Bits;
unsigned char exitTimeOut_x100ms;
unsigned char blinkTimeOut_x100ms;
};



unsigned char settingDisplayBlink(struct  zd_setting_display_blink_t* setting );
void settingDisplayBlink_Start(struct  zd_setting_display_blink_t* setting,unsigned char exitTimeSet_x100ms);

#endif 



//ʹ��ʾ��
/*

			//�������ú������ù�����
			if(��������)
			{
				setting.Bits.inSetting1=1;
				settingDisplayBlink_Start(&setting,50);//��������̬,��ʱ�˳�ʱ������Ϊ50x100ms
			}


			//��ʾ�����볬ʱ�Զ�����
			if(setting.inSetting1!=0)//������״̬
			{
				if(100msִ��һ�α�־)
				{

					if(settingDisplayBlink(&setting))//Ϊ1ʱδ��ʱ��ʾ����
					{
						if(setting.blinkDisplayEn==1)//��˸ʱ�Ƿ���ʾ��Ϩ���ı�־
						{
							//��ʾ��������
						}
						else
						{			
							//��ʾϨ��
						}
					}
					else//Ϊ0ʱ������ʱ�䳬ʱ
					{
						//������������
					
						//������ñ�־λ
						setting.inSetting1=0;
					}
				}


			}
			else//��������״̬
			{
				//��ʾ������̬������
			}



*/










/************************ (C) COPYRIGHT zhejiang zhida *****END OF FILE****/