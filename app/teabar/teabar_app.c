#include "..\com_include_app.h"
  

/*
#include "..\..\core\system_core.c" 
#include "..\..\core\adc_core.c" 
#include "..\..\drv\rtc\softrtc\softrtc_drv.c" 
#include "..\..\drv\display\softled\softled_drv.c" 
#include "..\..\drv\buzzer\buzzer\buzzer_drv.c" 
#include "..\..\drv\motor\stepmotor\stepMotor_drv.c" 
#include "..\..\drv\interrupt\interrupt_drv.c" 


#include "teabar_take_water_app.c"   
#include "teabar_boil_water_app.c"   
#include "teabar_warm_water_app.c"   

*/




//----����״̬����
#define			MACHINE_POWER_ON			0			//�ϵ�
#define			MACHINE_LOCK				1			//����
#define			MACHINE_IDEL				2			//����
#define			MACHINE_WORK				3			//��������ģʽ
#define			MACHINE_SELF_CHECK	4			//�Լ�
#define			MACHINE_ERROR				200			//����

//#define SET_TEMP_MAX 100
#define SET_TEMP_MIN 50

#define SET_BOILINGTEMP_MAX 100
#define SET_BOILINGTEMP_MIN 82

#define SET_WATERTIME_MAX 50
#define SET_WATERTIME_MIN 18

#define SET_WARMTIME_MAX 24
#define SET_WARMTIME_MIN 1


#define			BlinkTime 1
#define			BlinkTemp 2



unsigned long  TmpPidDisplay_LastSet_utcsec=0;
unsigned long  TmpPidDisplay_LastSet_msec=0;

unsigned long TempCheck30s_LastActive_utcsec=0;


//volatile unsigned char TempCheck30s_DataMax_ago=0;
unsigned char TempCheck30s_DataMax;
//unsigned char Rgb_Tmp_DataMin;
//unsigned char Rgb_Tmp_DataMax;

//��PID��ֵ����ʱ������������ڹرռ��ȵ���ǰ��������ֹ�¶ȹ���
unsigned long TempDiff_LastActive_utcsec=0;
unsigned long  DisplayTempDiff_LastSet_utcsec=0;
unsigned char gucv_real_tempC_falsify_target;
unsigned	char	gucv_real_tempC_falsify=0;
unsigned	char	gucv_real_tempF_falsify=0;

unsigned char PidTemp_DataDiff=0;
unsigned char PidTemp_DataNow=0;
unsigned char PidTemp_DataAgo=0;


unsigned char gucv_set_boilingtemp=100;	//�е��¶��趨ֵ
unsigned char gucv_set_temp=100;	//����Ŀ���¶��趨

unsigned char gucv_set_watertime=34;		//ȡˮʱ��
unsigned char gucv_set_warmtime=8;		//����ʱ��

unsigned long gulv_work_warmtime_sec;		//����ʱ��
unsigned char gucv_work_watertime;



unsigned	char	gucv_real_temp;					//��ʵ�¶�
unsigned char gucv_temp_display;		//������ʾ���¶�
unsigned char gucv_temp_display_down_delay;		//����»ز���ʱ

unsigned char setGetWaterTime_inSetting=0;//ȡˮʱ���趨������־
unsigned char setBoilingTemp_inSetting=0;//�е��¶��趨������־
unsigned char setKeepWarmTime_inSetting=0;//����ʱ���趨������־



unsigned	char	gucv_machine_status;			//����״̬


bit gubv_displaytemp_lock_settemp=0;

bit gubv_setting_blink_disEn=0;//��˸ʱ�Ƿ���ʾ��Ϩ���ı�־
unsigned long gulv_setting_blinkmsec=0; //������˸ʱ�����
unsigned long gulv_setting_exitmsec=0; //���ó�ʱ�˳�ʱ�����

unsigned long gulv_heatadj_nexttime_msec=0; //���ó�ʱ�˳�ʱ�����






unsigned char gucv_heat_start_delay=0;




bit gbv_heat_start_working=0;
bit gbv_pump_start_working=0;
bit gbv_pump_start_working_ago=0;

bit gbv_warm_start_working=0;
bit gbv_stepmotor_workover=0;


bit gbv_pot_up=0;
bit gbv_temp_over=0;
bit gbv_tempntc_open=0;
bit gbv_tempntc_short=0;
unsigned char gucv_temp_over_filter_cnt=0;
unsigned char gucv_pot_up_filter_cnt=0;


unsigned int waterout_Temp_ad;


unsigned	int		guiv_leakage_adc_data=0;
unsigned	int		guiv_out_water_adc_data=0;			//�ɼ����ĳ�ˮ��ADCֵ
unsigned	int		guiv_in_water_adc_data; //�ɼ�����A��ˮ��ADCֵ


unsigned char adc_buzz_delay_cnt=0;







void saveBoilingTempSetVal(void)
{
	IapProgramByte(0x0000,gucv_set_boilingtemp);
	
}

void saveGetWaterTimeSetVal(void)
{
	IapProgramByte(0x0001,gucv_set_watertime);
}

void saveKeepWarmTimeSetVal(void)
{
	IapProgramByte(0x0002,gucv_set_warmtime);
}




void cleanAllSetting(void)
{
	setGetWaterTime_inSetting=0;//

	setKeepWarmTime_inSetting=0;//

	setBoilingTemp_inSetting=0;//
}



void goToModeLock(void)
{
	//����Ϊ����
	gucv_machine_status=MACHINE_LOCK;
	
	//����ʾ
	Display_FixAll(0x00);
	
	//���������־
	KeyQuickPressCount=0;
	zd_key_clear();//������а�����־λ	
	cleanAllSetting();//����������ñ�־λ
}

void goToModeIdle(void)
{
	//����Ϊ����
	gucv_machine_status=MACHINE_IDEL;
	
	//�趨�¶�����Ϊ�е��¶�
	gucv_set_temp=gucv_set_boilingtemp;
	
	//����ʾ
	Display_FixAll(0x00);
	
	//������Դָʾ��
	disKeyLed((keyled_dianyuan),1);
	
	//���������־
	KeyQuickPressCount=0;
	zd_key_clear();//������а�����־λ	
	cleanAllSetting();//����������ñ�־λ

}


void CheckSetValue(unsigned char *setval,unsigned char min,unsigned char max)
{
		if((*setval)>max)
			(*setval)=max;
	else if((*setval)<min)
			(*setval)=min;	
}

#define CheckSetBoilingTemp(x) CheckSetValue((x),SET_BOILINGTEMP_MIN,SET_BOILINGTEMP_MAX)
#define CheckSetTemp(x)  CheckSetValue((x),SET_TEMP_MIN,(gucv_set_boilingtemp))
#define CheckSetWarmTime(x) CheckSetValue((x),SET_WARMTIME_MIN,SET_WARMTIME_MAX)
#define CheckSetWaterTime(x) CheckSetValue((x),SET_WATERTIME_MIN,SET_WATERTIME_MAX)

#define AdjUpSetBoilingTemp(x) if((x)<SET_BOILINGTEMP_MAX) (x)++; else (x)=0;
#define AdjUpSetTemp(x) if((x)<gucv_set_boilingtemp) (x)+=5; else (x)=0;
#define AdjUpSetWarmTime(x) if((x)<SET_WARMTIME_MAX) (x)++; else (x)=0;
#define AdjUpSetWaterTime(x) if((x)<SET_WATERTIME_MAX) (x)++; else (x)=0;



/*
void CheckSetBoilingTemp(unsigned char *setval)
{
	if((*setval)>SET_BOILINGTEMP_MAX)
			(*setval)=SET_BOILINGTEMP_MAX;
	else if((*setval)<SET_BOILINGTEMP_MIN)
			(*setval)=SET_BOILINGTEMP_MIN;	
}

 

void CheckSetTemp(unsigned char *setval)
{
	if((*setval)>gucv_set_boilingtemp)
			(*setval)=gucv_set_boilingtemp;
	else if((*setval)<SET_TEMP_MIN)
			(*setval)=SET_TEMP_MIN;	
}


void CheckSetWarmTime(unsigned char *setval)
{
	if((*setval)!=35&&(*setval)!=45&&(*setval)!=55)
			(*setval)=35;

}

void CheckSetWaterTime(unsigned char *setval)
{
	if((*setval)!=MACHINE_IDEL&&(*setval)!=MACHINE_WORK)
			(*setval)=MACHINE_IDEL;

}

*/


void loadUserSetVal(void)
{
	//ȡ�طе��¶�
	gucv_set_boilingtemp=IapReadByte(0x00);//��ȡ�е��¶�
	CheckSetBoilingTemp(&gucv_set_boilingtemp);//����ֵ�Ϲ��Լ��

	//ȡ��ȡˮʱ��
	gucv_set_watertime=IapReadByte(0x01);//ȡ��ȡˮ
	CheckSetWaterTime(&gucv_set_watertime);//����ֵ�Ϲ��Լ��
	
	//ȡ�ر���ʱ��
	gucv_set_warmtime=IapReadByte(0x02);//ȡ�ر���ʱ��
	CheckSetWarmTime(&gucv_set_warmtime);//����ֵ�Ϲ��Լ��

}

void DisplayBlink(unsigned char distype,unsigned int disnum)
{
		if(gulv_setting_blinkmsec<=(zd_getUtc_100mSec()))//��ǰʱ�����ǰ�����õ���˸����ʱ��󴥷�һ���л�
		{
			gulv_setting_blinkmsec=zd_getUtc_100mSec()+5;//��˸���500ms,�ڵ�ǰʱ���500ms���ٴ���
			if(gubv_setting_blink_disEn==0)//��˸ʱ�Ƿ���ʾ��Ϩ���ı�־
			{
				if(distype==BlinkTemp)
					disTemp(disnum);//��ʾ��ֵ
				else if(distype==BlinkTime)
					disTime(disnum);//��ʾ��ֵ
					
					
				gubv_setting_blink_disEn=1;//��˸ʱ�Ƿ���ʾ��Ϩ���ı�־,��1���´��л�ΪϨ��
			}
			else
			{
				if(distype==0)
					Display_FixAll(0x00);//Ϩ��,��ʾ�������0
				else if(distype==BlinkTemp)
					Display_FixTemp(0x00);
				else if(distype==BlinkTime)
					Display_FixTime(0x00);
				
				gubv_setting_blink_disEn=0;//��˸ʱ�Ƿ���ʾ��Ϩ���ı�־,��0���´��л�Ϊ��ʾ
			}
		}
}

void DisplayBlink_Start(void)
{
	gulv_setting_blinkmsec=0;//������˸��ʱ,��0������ִ��һ���л�����
	gubv_setting_blink_disEn=0;//��˸ʱ�Ƿ���ʾ��Ϩ���ı�־,��0���´��л�Ϊ��ʾ
	gulv_setting_exitmsec=zd_getUtc_100mSec()+48; //��˸5�룬ʱ�����4.8�룬ʹ���һ��ΪϨ��״̬���������һ���ȵ��������л�;
}


void waterin_callback(unsigned int a)
{

}

void waterout_callback(unsigned int a)
{
	if(a>3900) gbv_tempntc_open=1; else if(a<3800) gbv_tempntc_open=0;
	if(a<720) gbv_tempntc_short=1; else if(a>820) gbv_tempntc_short=0;
	
	waterout_Temp_ad=(a)>>4;

}

void leakage_callback(unsigned int a)
{

}


void app_init(void)
{
	zd_systemInit();

	zd_softrtcInit();
	
	zd_key_init();
//	
	zd_buzzer_init();
//	
	zd_display_init();
	
	zd_motorStep_init();
//��ˮ�¶ȴ������ź�
	//zd_adcInit(WATERIN_AIN_Channel,waterin_callback);
//��ˮ�¶ȴ������ź�
	zd_adcInit(WATEROUT_AIN_Channel,waterout_callback);
//©�����ź�
	//zd_adcInit(LEAKAGE_AIN_Channel,leakage_callback);

	
//����������ʱʹ�ã���δ��׼��	
	
	
			//���ȼ̵���
		HotRelay_IO_Output;
		HotRelay_IO_Ctrl(HotRelay_IO_OFF);

		//���¼̵���
		WarmRelay_IO_Output;
		WarmRelay_IO_Ctrl(WarmRelay_IO_OFF);

		//ˮ��
		Pump_IO_Output;
		Pump_IO_Ctrl(Pump_IO_OFF);
				
	//���⴦��,�ý���WATERIN�Ų���������Ϊ����
	//ZD_PORT_INPUT_SET(ZD_PORT1_DIR,BIT3);

	//����洢���û�����
	loadUserSetVal();
	
	//�ϵ����һ��
	zd_buzzer_beep(1,3,0);//����һ��(3x50ms)
	
	
}


void Error_Check(void)
{
			if(mSec_x50_workbit)
			{
				//���-��������·�¼�
				if(gbv_tempntc_open)
				{
					if(gbv_pot_up==0)
					{
						if(++gucv_pot_up_filter_cnt>5)
						{
							gbv_pot_up=1;
							gucv_pot_up_filter_cnt=0;
							zd_buzzer_beep(2,3,3);//��������(3x50ms)
						}
					}
					else
						gucv_pot_up_filter_cnt=0;
					
				}
				else
				{
					if(gbv_pot_up==1)
					{
						if(++gucv_pot_up_filter_cnt>10)
						{
							gbv_pot_up=0;
							gucv_pot_up_filter_cnt=0;
							zd_buzzer_beep(1,3,3);//����һ��(3x50ms)
						}
					}
					else
						gucv_pot_up_filter_cnt=0;
				}
				
				//����-��������·�¼�
				if(gbv_tempntc_short)
				{
					if(gbv_temp_over==0)
					{
						if(++gucv_temp_over_filter_cnt>20)
						{
							gbv_temp_over=1;
							zd_buzzer_beep(10,4,5);//����ʮ��(3x50ms)
						}
					}
				}
				else
					gucv_temp_over_filter_cnt=0;
			}
}

/*****************************************************************************
*����			: void App_Run(void)	
*������������ 	: ǰ̨����������Ӧ��ģʽ�л�
*�������� 		: ��
*��������ֵ 	: ��
******************************************************************************/
void App_Run(void)
{

	//����״̬
	switch(gucv_machine_status)
	{
		//�ϵ�
		case MACHINE_POWER_ON:

			//�ϵ�2������ǰ�α����״̬
			if(zd_getUtc_100mSec()>20)
			{
				//��������״̬
				goToModeLock();
			}
			
		break;
		case MACHINE_LOCK:
			if(GetSecHalfBit()) disKeyLed((keyled_dianyuan),1); else disKeyLed((keyled_dianyuan),0);
			
			//disTemp(KeyQuickPressCount);
			
			//ȡˮʱ���趨��ʾ
			if(setGetWaterTime_inSetting!=0)//������״̬
			{
				DisplayBlink(BlinkTime,gucv_set_watertime);
				if(gulv_setting_exitmsec<zd_getUtc_100mSec())//��ʱ�Զ������˳�
				{
					saveGetWaterTimeSetVal();
					setGetWaterTime_inSetting=0; //������ñ�־λ��ֹͣ��˸��ʾ
				}
			}
			//����ʱ���趨��ʾ
			else if(setKeepWarmTime_inSetting!=0)//������״̬
			{
				DisplayBlink(BlinkTime,gucv_set_warmtime);
				if(gulv_setting_exitmsec<zd_getUtc_100mSec())//��ʱ�Զ������˳�
				{
					saveKeepWarmTimeSetVal();
					setKeepWarmTime_inSetting=0; //������ñ�־λ��ֹͣ��˸��ʾ
				}
			}
			else//��������״̬
			{
				Display_FixTime(0x00);
			}


			//�е��¶��趨��ʾ
			if(setBoilingTemp_inSetting!=0)//������״̬
			{
				DisplayBlink(BlinkTemp,gucv_set_boilingtemp);
				if(gulv_setting_exitmsec<zd_getUtc_100mSec())//��ʱ�Զ������˳�
				{
					saveBoilingTempSetVal();
					setBoilingTemp_inSetting=0; //������ñ�־λ��ֹͣ��˸��ʾ
				}
			}
			else//��������״̬
			{//UserKeyVal
				Display_FixTemp(0x00);//disTemp(UserKeyVal);//(UserKeyVal);//Display_FixTemp(0x00);
			}
			
			

			
			
			
			
			if(UserKeyPressed_up)//���������ɿ��󴥷�
			{
				if(UserKeyVal==KEYS_DIANYUAN_VALUE)
				{
					if(setGetWaterTime_inSetting!=0||setKeepWarmTime_inSetting!=0||setBoilingTemp_inSetting!=0)//������ڽ����趨������Դ������ȷ��
					{
						
						if(setGetWaterTime_inSetting!=0)
						{
							//��������
							saveGetWaterTimeSetVal();
							setGetWaterTime_inSetting=0;//�˳�����
						}
						if(setKeepWarmTime_inSetting!=0)
						{
							//��������
							saveKeepWarmTimeSetVal();
							setKeepWarmTime_inSetting=0;//�˳�����
						}
						if(setBoilingTemp_inSetting!=0)
						{
							//��������
							saveBoilingTempSetVal();
							setBoilingTemp_inSetting=0;//�˳�����
						}
						
						KeyQuickPressCount=0;//�����������
					}				
					else if(KeyQuickPressCount>=2)//��Դ����������ﵽ2�λ����ϣ��������
					{
						goToModeIdle();
					}
					zd_buzzer_beep(1,2,0);//����һ��(3x50ms)
				}
				if(UserKeyVal==KEYS_QUSHI_VALUE)//����״̬�³���ȡˮ��5�룬����Ĭ��ȡˮʱ��
				{
					if(setGetWaterTime_inSetting!=0)
					{
						//if(gucv_set_watertime<gucv_set_boilingtemp) gucv_set_watertime++; else gucv_set_watertime=0;//ȡˮʱ��ֵ��1
						AdjUpSetWaterTime(gucv_set_watertime);
						
						CheckSetWaterTime(&gucv_set_watertime);//����ֵ�Ϲ��Լ��
						
						DisplayBlink_Start();//��˸��ʼ������,ÿ�ΰ��°�������˸�������״̬�����ⰴ���л�ʱ����
						
						zd_buzzer_beep(1,2,0);//����һ��(3x50ms)
					}
					
				}
				if(UserKeyVal==KEYS_BAOWEN_VALUE)
				{
					if(setKeepWarmTime_inSetting!=0)
					{
						AdjUpSetWarmTime(gucv_set_warmtime);//����ʱ��ֵ��1
						
						CheckSetWarmTime(&gucv_set_warmtime);//����ֵ�Ϲ��Լ��
						
						DisplayBlink_Start();//��˸��ʼ������,ÿ�ΰ��°�������˸�������״̬�����ⰴ���л�ʱ����
						
						zd_buzzer_beep(1,2,0);//����һ��(3x50ms)
					}
				}
				if(UserKeyVal==KEYS_JIARE_VALUE)
				{
					if(setBoilingTemp_inSetting!=0)
					{
						AdjUpSetBoilingTemp(gucv_set_boilingtemp);//ȡˮʱ��ֵ��1
						
						CheckSetBoilingTemp(&gucv_set_boilingtemp);//����ֵ�Ϲ��Լ��
						
						DisplayBlink_Start();//��˸��ʼ������,ÿ�ΰ��°�������˸�������״̬�����ⰴ���л�ʱ����
						
						zd_buzzer_beep(1,2,0);//����һ��(3x50ms)
					}
				}		
				
				
				
				zd_key_clear();//������а�����־λ
			}
			
			if(UserKeyLongPressed)//�������³���2��󴥷�
			{
				if(KeyLongPressCount>500)//�������³���5��
				{

					if(UserKeyVal==KEYS_QUSHI_VALUE)//����״̬�³���ȡˮ��5�룬����Ĭ��ȡˮʱ��
					{
						setGetWaterTime_inSetting=1;//��ʼ��������״̬
						DisplayBlink_Start();
						zd_buzzer_beep(1,2,0);//����һ��(3x50ms)
					}
					if(UserKeyVal==KEYS_BAOWEN_VALUE)
					{
						setKeepWarmTime_inSetting=1;//��ʼ��������״̬
						DisplayBlink_Start();
						zd_buzzer_beep(1,2,0);//����һ��(3x50ms)
					}
					if(UserKeyVal==KEYS_JIARE_VALUE)
					{
						setBoilingTemp_inSetting=1;//��ʼ��������״̬
						DisplayBlink_Start();
						zd_buzzer_beep(1,2,0);//����һ��(3x50ms)
					}
										
					zd_key_clear();
					
				}
				//else if(KeyLongPressCount>300)//�������³���3��
				//{}
				
			}
			
			
		break;
		case MACHINE_IDEL:
		
		//����
		case MACHINE_WORK:



			//�쳣���
			Error_Check();
			
			
			
			//Ŀ���¶��趨�����÷е��¶��趨��־
			if(setBoilingTemp_inSetting!=0)//������״̬
			{
				DisplayBlink(BlinkTemp,gucv_set_temp);
				if(gulv_setting_exitmsec<zd_getUtc_100mSec())//��ʱ�Զ������˳�
				{
					//saveTempSetVal();//���������¶�ֵ
					setBoilingTemp_inSetting=0; //������ñ�־λ��ֹͣ��˸��ʾ
					gbv_heat_start_working=1;//������ú�ʼ����
				}
			}
			else//��������״̬
			{
				if(gbv_temp_over)//��·-����
					disError(1);
				else if(gbv_pot_up)//��·-���
					disError(2);
				else
				{
					//��ʾ�¶� 
					if(mSec_x100_workbit)
					{
						if(gucv_real_temp>(gucv_temp_display))
						{
							gucv_temp_display++;//���Ե����ز�0
							gucv_temp_display_down_delay=0;//�ز�������ʱ����
							//������Ե�����������4ʱֱ�Ӹ�ֵ
							if(gucv_real_temp>(gucv_temp_display+4))
								gucv_temp_display=gucv_real_temp;
							
						}
						else if(gucv_temp_display>(gucv_real_temp+1))
						{
							gucv_temp_display--;//���Ե����ز�1
							gucv_temp_display_down_delay=0;//�ز�������ʱ����
							//������Ե�����������4ʱֱ�Ӹ�ֵ
							if(gucv_temp_display>(gucv_real_temp+4))
								gucv_temp_display=gucv_real_temp;
						}

						
						//ʵ���¶����趨�¶ȸ��� ������ʾ�趨�¶�
						if((gucv_real_temp)>=(gucv_set_temp-2)&&(gucv_real_temp)<=(gucv_set_temp+2))
						{
							if(gubv_displaytemp_lock_settemp)
								gucv_temp_display=gucv_set_temp;
							else if((gucv_real_temp)>=(gucv_set_temp-1)&&(gucv_real_temp)<=(gucv_set_temp+1))
								gubv_displaytemp_lock_settemp=1;
						}
						else
							gubv_displaytemp_lock_settemp=0;

						if(gucv_temp_display>100) gucv_temp_display=100;//��ֵ������100����	
					}
					
					
					disTemp(gucv_temp_display);//(gucv_real_temp);//(gucv_temp_display);
				}
			}			
			
			//�����¶�����ָʾ����ȹ���ָʾ
			disKeyLed((keyled_jiare),gbv_heat_start_working|setBoilingTemp_inSetting);

			
			//ȡˮʱ���빤��ָʾ
			if(gbv_pump_start_working)
			{
				disKeyLed((keyled_qushui),1);
				disTime(gucv_work_watertime);	
				if(gbv_stepmotor_workover&&mSec_x1000_workbit==1)
				{
					if(gucv_work_watertime>0) gucv_work_watertime--; else
					{
						 gbv_pump_start_working=0;
						 zd_buzzer_beep(1,2,0);//����һ��(3x50ms)
					}
				}
			}
			else
			{
				disKeyLed((keyled_qushui),0);
				Display_FixTime(0x00);
			}
			
			//���¹���ָʾ
			disKeyLed((keyled_baowen),gbv_warm_start_working);
			



			//����ʱ������������
			if(gbv_temp_over==1) break;



			if(UserKeyPressed_up)//���������ɿ��󴥷�
			{

				if(UserKeyVal==KEYS_DIANYUAN_VALUE)
				{
					goToModeLock();

				};
				if(UserKeyVal==KEYS_QUSHI_VALUE)
				{
					if(gbv_pump_start_working==1)
					{
						gbv_pump_start_working=0;
						KeyQuickPressCount=0;//�����������
					}
					else if(KeyQuickPressCount>=2)//��������ﵽ2�λ�����
					{
						gucv_work_watertime=gucv_set_watertime;
						gbv_pump_start_working=1;
					}
				}
				if(UserKeyVal==KEYS_BAOWEN_VALUE)
				{
					if(gbv_warm_start_working==1)
					{
						gbv_warm_start_working=0;
					}
					else
					{
						gulv_work_warmtime_sec=gucv_set_warmtime*3600;
						gbv_warm_start_working=1;
					}
				}
				if(UserKeyVal==KEYS_JIARE_VALUE)
				{
					if(setBoilingTemp_inSetting!=0)//�ڷе�����״̬(����)ʱ�����ȼ��������ڼ���Ŀ��ֵ
					{
						//if(gucv_set_temp<gucv_set_boilingtemp) gucv_set_temp+=5; else gucv_set_temp=0;//����Ŀ��ֵ��5
						AdjUpSetTemp(gucv_set_temp);
						
						CheckSetTemp(&gucv_set_temp);//����ֵ�Ϲ��Լ��
						
						DisplayBlink_Start();//��˸��ʼ������,ÿ�ΰ��°�������˸�������״̬�����ⰴ���л�ʱ����
						
					}
					else//���ڷе�����״̬ʱ�����ȼ����������͹رռ���
					{
						if(gbv_heat_start_working==1)
						{
							gbv_heat_start_working=0;
						}
						else
						{
							gbv_heat_start_working=1;
						}
					}

				}				
				zd_buzzer_beep(1,2,0);//����һ��(3x50ms)
				zd_key_clear();//������а�����־λ
			}
			
			
			if(UserKeyLongPressed)
			{
				if(KeyLongPressCount>300)
				{
					if(UserKeyVal==KEYS_JIARE_VALUE&&gbv_heat_start_working==0)//ֻ����δ��������ʱ�������ȼ����ܴ����е�����
					{
						setBoilingTemp_inSetting=1;//��ʼ��������״̬
						DisplayBlink_Start();
						zd_buzzer_beep(1,2,0);//����һ��(3x50ms)
					}
										
					zd_key_clear();
				}
			}
			
		break;


		default:
			if(UserKeyPressed_up||UserKeyLongPressed) zd_key_clear();//������а�����־λ
		break;
	}
	
}



/*****************************************************************************
*����			: void HeatTmpUpCheck(void)
*������������ 	: �����¶�������飨���ڼ���ԭ�����ɷ�������ǰ����
*�������� 		: ��
*��������ֵ 	: ��
******************************************************************************/
void HeatTmpUpCheck(void)
{
	
    //���ȼ̵�������ʱ
    if(gbv_heat_start_working)
    {
		//��������¶�����ֵ���ݶ�5�룩
        if(gucv_real_temp>PidTemp_DataNow)	{ PidTemp_DataNow=gucv_real_temp;  }
		
		if(GetUtcSec()>=TempDiff_LastActive_utcsec)
        {
            TempDiff_LastActive_utcsec=GetUtcSec()+5;
            
			//������ʷֵ�뵱ǰֵƫ��
			if(PidTemp_DataNow>PidTemp_DataAgo)
				PidTemp_DataDiff=PidTemp_DataNow-PidTemp_DataAgo;
            else
				PidTemp_DataDiff=0;

			//������ʷֵ
			PidTemp_DataAgo=PidTemp_DataNow;
            
			//�Ŵ�ƫ��ֵ���������Ŵ�
			PidTemp_DataDiff=PidTemp_DataDiff<<1;
            
            //��������ֵ��С�������ǰ8�ȹ�
            if(PidTemp_DataDiff>10) PidTemp_DataDiff=10;
		}


		//��ԭ��⴦��
		if(gucv_real_temp>(TempCheck30s_DataMax+1)||TempCheck30s_DataMax<82) //ˮ������2�Ȼ�ˮ�µ��ڸ�ԭ�е�ʱ����λ��ʱ
		{
            TempCheck30s_DataMax=gucv_real_temp;
			TempCheck30s_LastActive_utcsec=GetUtcSec();
		}
        else
        {
			if(GetUtcSec()>(TempCheck30s_LastActive_utcsec+30))  //��ԭ40�������¼��ȹ��̽���
			{
				gbv_heat_start_working=0;
			}
        }

		//ʵ���¶ȵ����趨�¶ȴ���
		if(gucv_real_temp>=gucv_set_temp) 
		{
			gbv_heat_start_working=0;
			zd_buzzer_beep(3,3,3);//��������(3x50ms)
		}



    }
    else//���ȼ̵���������ʱ
    {
		 TempCheck30s_DataMax=gucv_real_temp;//ÿ�μ��ȹرպ�����ֵ����λ��ԭ������
         PidTemp_DataNow=0; PidTemp_DataAgo=100;PidTemp_DataDiff=0;//ÿ�μ��ȹرպ�����ֵ����λ�¶�����������
		 TempCheck30s_LastActive_utcsec=GetUtcSec();//��ԭ���Ӽ���������ʼ��ʱ
         TempDiff_LastActive_utcsec=GetUtcSec();//�¶��������Ӽ���������ʼ
    }
    



}

/*****************************************************************************
*����			: void Background_Run(void)	
*������������ 	: IO�븺�غ�̨�Զ�����
*�������� 		: ��
*��������ֵ 	: ��
******************************************************************************/
void Background_Run(void)
{
	
	//����״̬
	switch(gucv_machine_status)
	{

		//����
		case MACHINE_IDEL:	
		//����
		case MACHINE_WORK:


			//����-�ر����й���
			if(gbv_temp_over==1)
			{
				gbv_heat_start_working=0;
				gbv_pump_start_working=0;
				gbv_warm_start_working=0;
				break;
			}
		
			//�������-�ؼ������ˮ
			if(gbv_pot_up==1)
			{
				gbv_heat_start_working=0;
				gbv_pump_start_working=0;
			}

			//�����������
			HeatTmpUpCheck();
						
			//���ȹ���
			if(gbv_heat_start_working)
			{
				if(gucv_heat_start_delay<2)//��ʱ3������
				{
					if(mSec_x1000_workbit==1) gucv_heat_start_delay++;
				}
				else
					HotRelay_IO_Ctrl(HotRelay_IO_ON);
			}
			else
			{
				if(gucv_heat_start_delay!=0)
				{
					gucv_heat_start_delay=0;
					gucv_set_temp=gucv_set_boilingtemp; //ÿ��ͣ�����趨�¶����¸�ֵ�е��¶�
		
				}
				HotRelay_IO_Ctrl(HotRelay_IO_OFF);
			}
			
			//ת����ȡˮ����
			if(gbv_pump_start_working)
			{
				//ȡˮ����ʱת��
				if(gbv_pump_start_working_ago==0) 
				{
					gbv_stepmotor_workover=0;
					zd_motorStep_work(2,1000,0);
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
				if(gbv_pump_start_working_ago==1) 
				{
					gbv_stepmotor_workover=0;
					zd_motorStep_work(1,1000,0);
				}
			}
			
			//��ʷ״̬����
			gbv_pump_start_working_ago=gbv_pump_start_working;
			
			//��ȡת�����״̬
			if(zd_motorStep_isbusy()==0)
				gbv_stepmotor_workover=1;
			

			
			//���¹���
			if(gbv_warm_start_working)
			{
				if(gulv_work_warmtime_sec>0)
				{
					if(mSec_x1000_workbit==1)
					 gulv_work_warmtime_sec--; 
				}
				else
				{
					 gbv_warm_start_working=0;
					 zd_buzzer_beep(1,2,0);//����һ��(3x50ms)
				}
				WarmRelay_IO_Ctrl(WarmRelay_IO_ON);	
			}
			else
			{
				WarmRelay_IO_Ctrl(WarmRelay_IO_OFF);	
			}


		break;		
		default:

		break;
	}
	
}


void app_base_run(void)
{
		if(mSec_x50_workbit)//ÿ50ms����һ��
		{
			//���������������
			zd_buzzerRun();
		
			gucv_real_temp=CalcTmpC(waterout_Temp_ad,gucv_real_temp);
		}
		
		if(mSec_x100_workbit)//ÿ100ms����һ��
		{


			
		}

		if(mSec_x10_workbit)//ÿ10ms����һ��
		{
			//ad�Զ�����ѯ�ɼ���ص�ִ��
			if((*T_BuzzerEn)!=0)
				adc_buzz_delay_cnt=5;
			else if(adc_buzz_delay_cnt>0)
				adc_buzz_delay_cnt--;
			else zd_adcRun();


			//��΢����ȡֵ
			__CMS_CheckTouchKey();	//ɨ�谴��
									
			//����ɨ��,��������������־���ֵ��Ϣ
			zd_keyRun();
			
			//�������
			zd_motorStep_run();

		}
	

}
