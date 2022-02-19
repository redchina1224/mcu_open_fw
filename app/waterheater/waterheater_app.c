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
#define			MACHINE_IDEL				1			//����
#define			MACHINE_WORK_TEMP				2			//��������ģʽ
#define			MACHINE_WORK_POWER		3
#define			MACHINE_SELF_CHECK	4			//�Լ�
#define			MACHINE_ERROR				200			//����

#define SET_TEMP_MAX 55
#define SET_TEMP_MIN 20


#define SET_POWER_MAX 52
#define SET_POWER_MIN 25



//----Ĭ��PWM�ٶ�
#define			PEM_DEFAULT_DATA			50			//Ĭ��PWM����
//----ˮ���ٶ�
#define			WATER_SPEED_LOW				9				//ˮ���ٶȹ���
//----���϶���
#define			ERROR_E1					0X01		//E1,©��
#define			ERROR_E2					0X02		//E2,ˮ������������
#define			ERROR_E3					0X04		//E3,����
#define			ERROR_E4					0X08		//E4,�¶ȴ���������


//----���ʱ��  80�� 1�ݱ�ʾ75W
const	unsigned char	cucv_power_Tab[81]=
{
	//0 --0W
	0,
	//01-10 75W-750W
	 5,7,9,11,12,14,15,16,17,18,
	//11-20 825W-1500W
	19,20,21,21,22,23,24,25,25,26,
	//21-30 1575W-2250W
	27,28,28,29,30,30,31,32,33,33,
	//31-40 2325W-3000W
	34,35,36,36,37,38,38,39,39,40,
	//41-50 3075W-3750W
	40,41,42,42,43,44,44,45,46,46,
	//51-60 3825W-4500W
	47,48,49,49,50,51,51,52,52,53,
	//61-70 4575W-5250W
	54,55,56,57,58,58,59,60,61,61,
	//71-80 5325W-6000W
	62,63,64,65,67,68,70,72,76,80,
};

unsigned char	gucv_work_temp;			//����Ŀ���¶�

unsigned char	gucv_set_temp;			//�����¶��趨
unsigned char gucv_set_power;		//���������趨

unsigned char gucv_set_mode;		//�ϵ�ģʽ�趨


unsigned char gucv_temp_display;		//������ʾ���¶�
unsigned char gucv_temp_display_down_delay;		//����»ز���ʱ


unsigned char setTemp_inSetting=0;//�¶��趨������־
unsigned char setPower_inSetting=0;//���������趨������־


unsigned	char	gucv_machine_status;			//����״̬
unsigned	char	gucv_machine_status_bak;		//����״̬,�ڱ����ָ��� �ָ�����״̬
unsigned	char	gucv_work_mode;			//����ģʽ״̬
bit gubv_displaytemp_lock_settemp=0;

bit gubv_setting_blink_disEn=0;//��˸ʱ�Ƿ���ʾ��Ϩ���ı�־
unsigned char gulv_setting_blinkmsec=0; //������˸ʱ�����
unsigned char gulv_setting_exitmsec=0; //���ó�ʱ�˳�ʱ�����



unsigned	char	gucv_error_status=0;				//����״̬
unsigned	char	gucv_error_delay_cnt=0;				//�����ӳٷ���


//----ˮ�¿���
unsigned	char	gucv_water_temp_con_step=0;			//ˮ�¿��Ʋ���
unsigned	char	gucv_kkg_temp_data=0;				//�ɿع����� �м������
unsigned	int		guiv_water_temp_wending_time=0;		//ˮ���ȶ�ʱ��



unsigned	int 	guiv_work_low_temp_count=0;			//ˮ��һֱû�дﵽ��ʱ
unsigned	int 	guiv_work_adj_time=0;				//����ʱ�����ɿع�������ʱ��
//unsigned	char 	gucv_work_kkg_drv_data=0;			//����ʱ�ɿع�����ʱ�� 0-100  һ��100��
unsigned	int		guiv_temp_display_time=0;			//��ʾ�¶Ȳ�����ʱ
unsigned	int		guiv_temp_display_data=0;			//��ʾ�¶Ȳ���ֵ


unsigned	long	lulv_out_power=0;							//��׼�������
unsigned	int		luiv_power_adj_time_1ms=0;		//��׼���ʵ������
unsigned	int		luiv_power_adj_time_1ms_2=0;	//���ݳ�ˮ�¶ȹ��ʵ������
unsigned	int		luiv_power_adj_data=0;				//���ʵ�����
unsigned	int		luiv_temp_adc_data=0;					//��Ҫ��ADCֵ
unsigned	int		luiv_water_speed_data=0;			//ˮ����С
unsigned	char	lucv_water_speed_high_power=0;//�ж�ˮ������Ĺ�������
unsigned	char	lucv_power_adj_jiange_time=0;	//���ݳ�ˮ�¶ȵ��ڹ��ʴ�С���ʱ�� ����
unsigned	int		luiv_temp_stop_change_time=0;	//�¶�ֹͣ�仯ʱ��
unsigned	int		luiv_old_temp=0;							//��һ�ε��¶�
bit lucv_now_adj_power=0;					//�Ѿ���������¶�


//unsigned	int	guiv_out_water_adc_data_ago=0;					//adc�Ա�
unsigned  int	guiv_set_temp_adc_data;			//



bit gbv_heat_start_working=0;

unsigned char eco_mode_delay=30;

unsigned int waterin_Temp_ad;
unsigned int waterout_Temp_ad;
unsigned int leakage_ad;


unsigned	int		guiv_out_water_adc_data=0;			//�ɼ����ĳ�ˮ��ADCֵ
//unsigned	int		guiv_in_water_adc_data; //�ɼ�����A��ˮ��ADCֵ

unsigned	char 	gucv_water_speed;				//ˮ���ٶ�

unsigned	char	gucv_real_temp;					//��ʵ�¶�
unsigned	char	gucv_in_water_temp;				//��ˮ���¶�



unsigned char adc_workcnt=0;
unsigned char mscx1_cnt=0;

bit zeroadjdir=0;

bit tempcico_nav=0;


bit Leakage_Error=0;
bit WaterOutNtc_Error=0;
bit WaterInNtc_Error=0;


unsigned char firsh_run_delay=0;


void saveTempSetVal(void)
{
	IapProgramByte(0x0000,gucv_set_temp);
	
}

void savePowerSetVal(void)
{
	IapProgramByte(0x0001,gucv_set_power);
}

void saveModeSetVal(void)
{
	IapProgramByte(0x0002,gucv_set_mode);
}






void cleanAllSetting(void)
{
setTemp_inSetting=0;
setPower_inSetting=0;
}


void goToModeError(void)
{
	//����Ϊ����ģʽ
	gucv_machine_status=MACHINE_ERROR;
	
	
	//�رտɿع����
	triacOnEnable=0;		//�ɿع����ʹ�ܽ�ֹ
	Triac_IO_Ctrl(Triac_IO_OFF);//�ɿع�����ر�
	
	//���ݻ���״̬
	gucv_machine_status_bak=gucv_machine_status;
	
	//����������ñ�־λ
	cleanAllSetting();
}



void goToModeIdle(void)
{
	gucv_machine_status_bak=gucv_machine_status;
	//����Ϊ����
	gucv_machine_status=MACHINE_IDEL;
	
	//��������򿪻�״̬
	if(gucv_set_mode!=gucv_machine_status)
	{
		gucv_set_mode=gucv_machine_status;
		saveModeSetVal();
	}
	
	//����ʾ
	Display_FixAll(0x00);

	//�ع���ָʾ��
	//WorkLed_IO_Ctrl(WorkLed_IO_OFF);
	
	//������������¶�����б���
	if(setTemp_inSetting!=0)  saveTempSetVal();
	//����������ù�������б���
	if(setPower_inSetting!=0) savePowerSetVal();
	//����������ñ�־λ
	cleanAllSetting();

}


void goToModeWork(void)
{
	//ͬ��һ����ʾ�¶���ʵ���¶�
	gucv_temp_display=gucv_real_temp;
	
	//����������ñ�־λ
	cleanAllSetting();
}

void setToModeWorkTemp(void)
{
	disPowerLevel(0);
					
	//����Ϊ����
	gucv_machine_status=MACHINE_WORK_TEMP;
	gucv_machine_status_bak=gucv_machine_status;
	//��������򿪻�״̬
	if(gucv_set_mode!=gucv_machine_status)
	{
		gucv_set_mode=gucv_machine_status;
		saveModeSetVal();
	}
	
	//����������ù�������б���
	if(setPower_inSetting!=0) 
	{
		savePowerSetVal();
		setPower_inSetting=0;
	}
		
}
void setToModeWorkPower(void)
{
	//����Ϊ����
	gucv_machine_status=MACHINE_WORK_POWER;
	gucv_machine_status_bak=gucv_machine_status;
	//��������򿪻�״̬
	if(gucv_set_mode!=gucv_machine_status)
	{
		gucv_set_mode=gucv_machine_status;
		saveModeSetVal();
	}
	
	//������������¶�����б���
	if(setTemp_inSetting!=0)
	{
		  saveTempSetVal();
		  setTemp_inSetting=0;
	}

		
}



void CheckSetTemp(unsigned char *setval)
{
	if((*setval)>SET_TEMP_MAX)
			(*setval)=SET_TEMP_MAX;
	else if((*setval)<SET_TEMP_MIN)
			(*setval)=SET_TEMP_MIN;	
}

void CheckSetPower(unsigned char *setval)
{
	if((*setval)!=25&&(*setval)!=34&&(*setval)!=52)
			(*setval)=25;

}

void CheckSetMode(unsigned char *setval)
{
	if((*setval)!=MACHINE_IDEL&&(*setval)!=MACHINE_WORK_TEMP&&(*setval)!=MACHINE_WORK_POWER)
			(*setval)=MACHINE_WORK_POWER;

}




void loadUserSetVal(void)
{
	//ȡ�������¶�
	gucv_set_temp=IapReadByte(0x00);//��ȡ�����¶�
	CheckSetTemp(&gucv_set_temp);//�����¶ȺϹ���

	//ȡ�����ƹ���
	gucv_set_power=IapReadByte(0x01);//ȡ�����ƹ���
	CheckSetPower(&gucv_set_power);//���ƹ��ʺϹ���
	
	//ȡ������ģʽ
	gucv_set_mode=IapReadByte(0x02);//ȡ������ģʽ
	CheckSetMode(&gucv_set_mode);//����ģʽ�Ϲ���
}



void DisplayBlink(unsigned char disnum)
{
		if(gulv_setting_blinkmsec>4)//��ǰʱ�����ǰ�����õ���˸����ʱ��󴥷�һ���л�
		{
			gulv_setting_blinkmsec=0;//��˸���500ms,�ڵ�ǰʱ���500ms���ٴ���
			if(gubv_setting_blink_disEn==0)//��˸ʱ�Ƿ���ʾ��Ϩ���ı�־
			{
				if(disnum>=200)
				{
					disError(disnum%10);
					zd_buzzer_beep(1,10,0);//����һ��(3x50ms)
				}
				else
					disTemp(disnum);//��ʾ��ֵ
				gubv_setting_blink_disEn=1;//��˸ʱ�Ƿ���ʾ��Ϩ���ı�־,��1���´��л�ΪϨ��
			}
			else
			{
				Display_FixAll(0x00);//Ϩ��,��ʾ�������0
				gubv_setting_blink_disEn=0;//��˸ʱ�Ƿ���ʾ��Ϩ���ı�־,��0���´��л�Ϊ��ʾ
			}
		}
		else if((mSec_x100_workbit)&&gulv_setting_blinkmsec<200)
		{
			gulv_setting_blinkmsec++;
		}
}

void DisplayBlink_Start(void)
{
	gulv_setting_blinkmsec=200;//������˸��ʱ,��0������ִ��һ���л�����
	gubv_setting_blink_disEn=0;//��˸ʱ�Ƿ���ʾ��Ϩ���ı�־,��0���´��л�Ϊ��ʾ
	gulv_setting_exitmsec=48; //��˸5�룬ʱ�����4.8�룬ʹ���һ��ΪϨ��״̬���������һ���ȵ��������л�;
	eco_mode_delay=31;
}



void ErrorCheck(void)
{
	if(Leakage_Error)//©�������Ӧ����
	{
		goToModeError();
	}
	else if(WaterInNtc_Error||WaterOutNtc_Error||gucv_real_temp>60)
	{
		if(mSec_x50_workbit)
		{
			if(gucv_error_delay_cnt<10) 
				gucv_error_delay_cnt++;
			else
				goToModeError();
		}
	}
	else
		gucv_error_delay_cnt=0;
	
}
/*
void DisplayNavCheck(void)
{
	if(Switch_IO_Channel==0)
	{
		if(gucv_display_nav_delay_cnt>0)
			gucv_display_nav_delay_cnt--;
		else
			displayNav=0;
	}
	else
	{
		if(gucv_display_nav_delay_cnt<50)
			gucv_display_nav_delay_cnt++;
		else
			displayNav=1;
	}
}
*/



void app_init(void)
{

	zd_systemInit();

	zd_softrtcInit();
	
	zd_key_init();
//	
	zd_buzzer_init();
//	
	zd_display_init();
	
	zd_adcInit();
//��ˮ�¶ȴ������ź�
	//zd_adcInit(WATERIN_AIN_Channel,waterin_callback);
//��ˮ�¶ȴ������ź�
	//zd_adcInit(WATEROUT_AIN_Channel,waterout_callback);
//©�����ź�
	//zd_adcInit(LEAKAGE_AIN_Channel,leakage_callback);

	
//����������ʱʹ�ã���δ��׼��	
	
	//���⴦��,�ý���WATERIN�Ų���������Ϊ����
	//ZD_PORT_INPUT_SET(ZD_PORT1_DIR,BIT3);
	
//������������
	Counter_IO_Input;
	T_Counter1_1sec=&gucv_water_speed;
	
//�����ź�
	ZeroCross_IO_Input;
	

//�ɿع�����
	Triac_IO_Output;
	Triac_IO_Ctrl(Triac_IO_OFF);
	
	//����ָʾ��
	//WorkLed_IO_Output;
	//WorkLed_IO_Ctrl(WorkLed_IO_OFF);
	
	//�㵹����
	//Switch_IO_Input;
	
	zd_buzzer_beep(1,10,0);//����һ��(3x50ms)
loadUserSetVal();
}



/*****************************************************************************
*����			: void App_Run(void)	
*������������ 	: ǰ̨����������Ӧ��ģʽ�л�
*�������� 		: ��
*��������ֵ 	: ��
******************************************************************************/
void App_Run(void)
{
	
	
	if(eco_mode_delay>0)
	{
		if(eco_mode_delay>30)
		{
			zd_softled_set_bright(10);
			eco_mode_delay=30;
		}
		else if(mSec_x1000_workbit)
		{
			eco_mode_delay--;
			zd_softled_set_bright(eco_mode_delay);
		}
		
	}


	//����״̬
	switch(gucv_machine_status)
	{
		//�ϵ�
		case MACHINE_POWER_ON:
	
			//�ϵ�Ĭ��ȫ��
			//	WorkLed_IO_Ctrl(WorkLed_IO_ON);
			//�ϵ�1.5�����ʾ������������ֵ
			//if(zd_getUtc_100mSec()>15)
			disTemp(88);//��ʾ����
			
			//�ϵ�3������ǰ�α����״̬
			if(zd_getUtc_100mSec()>30)
			{
					//������һ�λ���״̬������������
					if(gucv_set_mode==MACHINE_IDEL)
					{
						goToModeIdle();//�������ģʽ
					}
					else if(gucv_set_mode==MACHINE_WORK_TEMP)
					{
						setToModeWorkTemp();
						goToModeWork();//������¹���ģʽ
					}
					else if(gucv_set_mode==MACHINE_WORK_POWER)
					{
						setToModeWorkPower();
						goToModeWork();//���뵵λ����ģʽ
					}
			}
			
		break;
		case MACHINE_IDEL:

			if(gucv_water_speed==0)
			{
				fixTemp(db_G);
			}
			else
				disTemp(gucv_water_speed);
							
			//��������
			if(mcuTouchKeys.UserKeyPressed_up||rfKeys.UserKeyPressed_up)//���������ɿ��󴥷�
			{
				if((mcuTouchKeys.UserKeyPressed_up==1&&mcuTouchKeys.UserKeyVal==KEYS_POWER_VALUE)||\
					(rfKeys.UserKeyPressed_up==1&&rfKeys.UserKeyVal==RFKEYS_POWERON_VALUE))
				{
					if(gucv_machine_status_bak==MACHINE_WORK_TEMP)
					{
						setToModeWorkTemp();
						goToModeWork();//������¹���ģʽ
					}
					else
					{
						setToModeWorkPower();
						goToModeWork();//���뵵λ����ģʽ
					}
						
					zd_buzzer_beep(1,3,0);//����һ��(3x50ms)
				}

				eco_mode_delay=31;
				zd_key_clear(&mcuTouchKeys);
				zd_key_clear(&rfKeys);//������а�����־λ
			}
		

			//������,����ڴ���״̬�Զ�ת�뱨��ģʽ
			ErrorCheck();
			
		break;

		case MACHINE_WORK_POWER:
		

			//��λָʾ��
			if(gucv_set_power==25)
				disPowerLevel(1);
			else if(gucv_set_power==34)
				disPowerLevel(2);
			else if(gucv_set_power==52)
				disPowerLevel(3);
			
			
			//
			
			if(setPower_inSetting!=0) //������״̬
			{
				if(gulv_setting_exitmsec>0)
				{
					 if(mSec_x100_workbit) gulv_setting_exitmsec--;
				}
				else//��ʱ�Զ������˳�
				{
					savePowerSetVal();//��������ֵ
					setPower_inSetting=0; //������ñ�־λ��ֹͣ��˸��ʾ
				}
			}
			
				
		//����
		case MACHINE_WORK_TEMP:


			//����ָʾ��

			if(gbv_heat_start_working==1)
			{
				if(mSec_x250_workbit==1)
				{
					tempcico_nav=~tempcico_nav;
					dispC(tempcico_nav);//������ָʾ
				}
			}
			else
			{
				dispC(1);
			}


			//�¶��趨��ʾ�뱣��
			if(setTemp_inSetting!=0) //������״̬
			{
				gubv_displaytemp_lock_settemp=0;
				DisplayBlink(gucv_set_temp);//��˸��ʾ�¶�ֵ
				if(gulv_setting_exitmsec>0)
				{
					 if(mSec_x100_workbit) gulv_setting_exitmsec--;
				}
				else//��ʱ�Զ������˳�
				{
					saveTempSetVal();//���������¶�ֵ
					setTemp_inSetting=0; //������ñ�־λ��ֹͣ��˸��ʾ
				}
			}
			else//��������״̬
			{

				//��ʾ�¶� 
				if(mSec_x100_workbit)
				{
					if(gucv_real_temp>(gucv_temp_display))
					{
						gucv_temp_display++;//���Ե����ز�0
						gucv_temp_display_down_delay=0;//�ز�������ʱ����
						//������Ե�����������5ʱֱ�Ӹ�ֵ
						if(gucv_real_temp>(gucv_temp_display+6))
							gucv_temp_display=gucv_real_temp;
					}
					else if(gucv_temp_display>(gucv_real_temp+1))
					{
						gucv_temp_display--;//���Ե����ز�1
						gucv_temp_display_down_delay=0;//�ز�������ʱ����
						//������Ե�����������5ʱֱ�Ӹ�ֵ
						if(gucv_temp_display>(gucv_real_temp+6))
							gucv_temp_display=gucv_real_temp;
					}

					
					//ʵ���¶����趨�¶ȸ��� ������ʾ�趨�¶�
					if((gucv_real_temp)>=(gucv_set_temp-4)&&(gucv_real_temp)<=(gucv_set_temp+4))
					{
						if(gubv_displaytemp_lock_settemp)
							gucv_temp_display=gucv_set_temp;
						else if((gucv_real_temp)>=(gucv_set_temp-1)&&(gucv_real_temp)<=(gucv_set_temp+1))
							gubv_displaytemp_lock_settemp=1;
					}
					else
						gubv_displaytemp_lock_settemp=0;

							
				}
				
				disTemp(gucv_temp_display);//��ʾ�¶�ֵ
				
				//disTemp(triacOn_CrossPass);
				//disTemp(zeroCrossPassCntMax);
				
				
//				if(mSec_x100_workbit)
//					disTemp(gucv_real_temp);//��ʾʵ���¶�ֵ
				
			}		
		
		
		
			//��������
			if(mcuTouchKeys.UserKeyPressed_up||rfKeys.UserKeyPressed_up)//���������ɿ��󴥷�
			{
				if((mcuTouchKeys.UserKeyPressed_up==1&&mcuTouchKeys.UserKeyVal==KEYS_POWER_VALUE)||(rfKeys.UserKeyPressed_up==1&&rfKeys.UserKeyVal==RFKEYS_POWEROFF_VALUE))
				{
					goToModeIdle();//�л��������ģʽ
					zd_buzzer_beep(1,3,0);//����һ��(3x50ms)
				}
				else if((mcuTouchKeys.UserKeyPressed_up==1&&mcuTouchKeys.UserKeyVal==KEYS_ADJUP_VALUE)||(rfKeys.UserKeyPressed_up==1&&rfKeys.UserKeyVal==RFKEYS_ADJUP_VALUE))
				{
					if(setTemp_inSetting!=0)//���¶��������ڽ���ʱ��Ч
					{
						if(gucv_set_temp<SET_TEMP_MAX) gucv_set_temp++;//�¶�����ֵ��1
						CheckSetTemp(&gucv_set_temp);//�¶�����ֵ�Ϲ���
						DisplayBlink_Start();//��˸��ʼ������,ÿ�ΰ��°�������˸�������״̬�����ⰴ���л�ʱ����
					}
					else//���¶�����δ����ʱ
					{
						setTemp_inSetting=1;//��ʼ�����¶�����״̬
						DisplayBlink_Start();//��˸��ʼ������,ÿ�ΰ��°�������˸�������״̬�����ⰴ���л�ʱ����
					}
					
					setToModeWorkTemp();
					
					zd_buzzer_beep(1,3,0);//����һ��(3x50ms)
					
				}
				else if((mcuTouchKeys.UserKeyPressed_up==1&&mcuTouchKeys.UserKeyVal==KEYS_ADJDOWN_VALUE)||(rfKeys.UserKeyPressed_up==1&&rfKeys.UserKeyVal==RFKEYS_ADJDOWN_VALUE))
				{
					if(setTemp_inSetting!=0)//���¶��������ڽ���ʱ��Ч
					{
						if(gucv_set_temp>SET_TEMP_MIN) gucv_set_temp--;//�¶�����ֵ��1
						CheckSetTemp(&gucv_set_temp);//�¶�����ֵ�Ϲ���
						DisplayBlink_Start();//��˸��ʼ������,ÿ�ΰ��°�������˸�������״̬�����ⰴ���л�ʱ����
					}
					else//���¶�����δ����ʱ
					{
						setTemp_inSetting=1;//��ʼ�����¶�����״̬
						DisplayBlink_Start();//��˸��ʼ������,ÿ�ΰ��°�������˸�������״̬�����ⰴ���л�ʱ����
					}
					
					setToModeWorkTemp();
					
					zd_buzzer_beep(1,3,0);//����һ��(3x50ms)
				}
				else if((mcuTouchKeys.UserKeyPressed_up==1&&mcuTouchKeys.UserKeyVal==KEYS_LEVEL_VALUE)||(rfKeys.UserKeyPressed_up==1&&rfKeys.UserKeyVal==RFKEYS_LEVEL_VALUE))
				{
					if(gucv_machine_status==MACHINE_WORK_POWER)
					{
						setPower_inSetting=1;
						gulv_setting_exitmsec=48;//���ó�ʱ�Զ�����
						
						if(gucv_set_power>=34) 
							gucv_set_power+=18;//����
						else
							gucv_set_power+=9;//����
							
						CheckSetPower(&gucv_set_power);//����ֵ�Ϲ��Լ��
					}
					else
						setToModeWorkPower();
						
					zd_buzzer_beep(1,3,0);//����һ��(3x50ms)
				}
				
				eco_mode_delay=31;
				zd_key_clear(&mcuTouchKeys);
				zd_key_clear(&rfKeys);//������а�����־λ
			}


			if((mcuTouchKeys.UserKeyLongPressed&&mcuTouchKeys.KeyLongPressCount>300)||(rfKeys.UserKeyLongPressed&&rfKeys.KeyLongPressCount>300))//���������ɿ��󴥷�
			{
				if(((mcuTouchKeys.UserKeyLongPressed==1&&mcuTouchKeys.KeyLongPressCount>300)&&mcuTouchKeys.UserKeyVal==KEYS_ADJUP_VALUE)||((rfKeys.UserKeyLongPressed==1&&rfKeys.KeyLongPressCount>300)&&rfKeys.UserKeyVal==RFKEYS_ADJUP_VALUE))
				{
					if(setTemp_inSetting!=0)//���¶��������ڽ���ʱ��Ч
					{
						if(mSec_x100_workbit)
						{
							if(mSec_x500_workbit)
							{
								if(gucv_set_temp<SET_TEMP_MAX) gucv_set_temp+=5;//�¶�����ֵ��1
								CheckSetTemp(&gucv_set_temp);//�¶�����ֵ�Ϲ���
								zd_buzzer_beep(1,3,0);//����һ��(3x50ms)
							}
							DisplayBlink_Start();//��˸��ʼ������,ÿ�ΰ��°�������˸�������״̬�����ⰴ���л�ʱ����
						}
					}
					else//���¶�����δ����ʱ
					{
						setTemp_inSetting=1;//��ʼ�����¶�����״̬
						DisplayBlink_Start();//��˸��ʼ������,ÿ�ΰ��°�������˸�������״̬�����ⰴ���л�ʱ����
						zd_buzzer_beep(1,3,0);//����һ��(3x50ms)
						setToModeWorkTemp();
					}
					
					
				}
				else if(((mcuTouchKeys.UserKeyLongPressed==1&&mcuTouchKeys.KeyLongPressCount>300)==1&&mcuTouchKeys.UserKeyVal==KEYS_ADJDOWN_VALUE)||((rfKeys.UserKeyLongPressed==1&&rfKeys.KeyLongPressCount>300)&&rfKeys.UserKeyVal==RFKEYS_ADJDOWN_VALUE))
				{
					if(setTemp_inSetting!=0)//���¶��������ڽ���ʱ��Ч
					{
						if(mSec_x100_workbit)
						{
							if(mSec_x500_workbit)
							{
								if(gucv_set_temp>SET_TEMP_MIN) gucv_set_temp-=5;//�¶�����ֵ��1
								CheckSetTemp(&gucv_set_temp);//�¶�����ֵ�Ϲ���
								zd_buzzer_beep(1,3,0);//����һ��(3x50ms)
							}
							DisplayBlink_Start();//��˸��ʼ������,ÿ�ΰ��°�������˸�������״̬�����ⰴ���л�ʱ����
						}
					}
					else//���¶�����δ����ʱ
					{
						setTemp_inSetting=1;//��ʼ�����¶�����״̬
						DisplayBlink_Start();//��˸��ʼ������,ÿ�ΰ��°�������˸�������״̬�����ⰴ���л�ʱ����
						zd_buzzer_beep(1,3,0);//����һ��(3x50ms)
						setToModeWorkTemp();
					}
					
					setToModeWorkTemp();
					
					
				}

				if(mcuTouchKeys.UserKeyPressed==0||rfKeys.UserKeyPressed==0)
				{
					//zd_key_clear(&mcuTouchKeys);
					//zd_key_clear(&rfKeys);//������а�����־λ
				}
			}
			
					
			//������,����ڴ���״̬�Զ�ת�뱨��ģʽ
			ErrorCheck();

			
		break;
		
		
		case MACHINE_ERROR:
			
			
			//WorkLed_IO_Ctrl(WorkLed_IO_OFF);//�ع���ָʾ��
							
			/*			
			if(Leakage_Error)//©�����
			{
				DisplayBlink(201);//��˸��ʾE1
				gucv_error_delay_cnt=10;
			}
			else */if(WaterInNtc_Error)//��ˮ������(ˮ��������)����
			{
				DisplayBlink(202);//��˸��ʾE2
				gucv_error_delay_cnt=10;
			}
			else if(WaterOutNtc_Error)//��ˮ����������
			{
				if(waterout_Temp_ad>3900)
					DisplayBlink(201);//��˸��ʾE1
				else if(waterout_Temp_ad<200)
					DisplayBlink(200);//��˸��ʾE0
					
				gucv_error_delay_cnt=10;
			}
			else if(gucv_real_temp>60)//���±���
			{
				DisplayBlink(203);//��˸��ʾE3
				gucv_error_delay_cnt=10;
			}
			else if(mSec_x50_workbit)
			{
				if(gucv_error_delay_cnt>0)//������ʱ�ָ�
					gucv_error_delay_cnt--;
				else
				{
					//������һ�λ���״̬������������
					if(gucv_set_mode==MACHINE_IDEL)
					{
						goToModeIdle();//�������ģʽ
					}
					else if(gucv_set_mode==MACHINE_WORK_TEMP)
					{
						setToModeWorkTemp();
						goToModeWork();//������¹���ģʽ
					}
					else if(gucv_set_mode==MACHINE_WORK_POWER)
					{
						setToModeWorkPower();
						goToModeWork();//���뵵λ����ģʽ
					}
					
				}

			}

					
		default:
			if(mcuTouchKeys.UserKeyPressed_up||rfKeys.UserKeyPressed_up)
			{
				eco_mode_delay=31;
				zd_key_clear(&mcuTouchKeys);
				zd_key_clear(&rfKeys);//������а�����־λ
			}
		break;
	}
	
}




/*****************************************************************************
*����			: void water_temp_con_step0(void)	
*������������ 	
*�������� 		: ��
*��������ֵ 	: ��
******************************************************************************/

void water_temp_con_step0(void)
{
	
					//ˮ����С ֱ�ӽ�ȥ��һ��
					if(gucv_water_speed<=18)
					{
						gucv_water_temp_con_step=1;		//�����׼���ʼ���
						gucv_kkg_temp_data=0;
					}
					else
					{
						if(gucv_water_speed>=30)
						{
							luiv_water_speed_data=15;
						}
						else
						{
							luiv_water_speed_data=(unsigned char)(40-gucv_water_speed);
							if(luiv_water_speed_data<15)
							{
								luiv_water_speed_data=15;
							}
						}
					}
					
					//�����¶��ж��Ƿ���Ҫȫ���ʼ���
					if(gucv_set_temp>=(gucv_real_temp+luiv_water_speed_data))
					{
						gucv_kkg_temp_data=80;
					}
					else	if(gucv_set_temp<=(gucv_real_temp-12))
					{
						gucv_kkg_temp_data=0;
					}
					else
					{
						gucv_water_temp_con_step=1;		//�����׼���ʼ���
						gucv_kkg_temp_data=0;
					}
					
					//�����������ʱ��
					if(gucv_set_temp>=gucv_real_temp)
					{
						guiv_water_temp_wending_time=(unsigned char)(gucv_set_temp-gucv_real_temp);
					}
					else
					{
						guiv_water_temp_wending_time=((unsigned char)((gucv_real_temp-gucv_set_temp)>>1));
					}
					
					
					
					//�����100ms *15
					if(guiv_water_temp_wending_time>20)
					{
						guiv_water_temp_wending_time=20;
					}
					guiv_water_temp_wending_time=guiv_water_temp_wending_time*12;
					if(guiv_water_temp_wending_time<50)
					{
						guiv_water_temp_wending_time=50;
					}
					
					
					
					luiv_power_adj_data=100;					//���ʵ�����
					luiv_power_adj_time_1ms=0;				//����ʼ�����
					guiv_work_adj_time=0;							//��ʱ���� ���ʵ���  ��һ�ν�ȥ�͵���
					luiv_power_adj_time_1ms_2=0;			//���ݳ�ˮ�¶ȹ��ʵ������
					luiv_temp_stop_change_time=0;			//�¶�ֹͣ�仯ʱ��
					luiv_old_temp=0;									//��һ�ε��¶�
					lucv_now_adj_power=0;							//�Ѿ���������¶�
}



//�ñ�׼���ȱȼ���  ��ʱX������΢��
void water_temp_con_step1(void)
{
					//----��׼���ʼ���
					luiv_power_adj_time_1ms++;
					if(luiv_power_adj_time_1ms>=10)
					{
						luiv_power_adj_time_1ms=0;
						//�����׼������� �ٷֱ� = ˮ����*�¶Ȳ�*0.11676
						if(gucv_set_temp>gucv_in_water_temp)		//����趨�¶ȴ��ڽ�ˮ�¶�
						{
							//----�����׼����
							{
								lulv_out_power=(unsigned char)(gucv_set_temp-gucv_in_water_temp);
								//�¶Ȳ���

								if(gucv_set_temp>50)
								{
									if(lulv_out_power>=2)
									{lulv_out_power=lulv_out_power-2;}
								}
								else	if(gucv_set_temp>46)
								{
									if(lulv_out_power>=2)
									{lulv_out_power=lulv_out_power-2;}
								}
								
								if(gucv_set_temp<43)
								{
									lulv_out_power=lulv_out_power+2;
								}
								
								//�����׼����
								lulv_out_power=lulv_out_power*(gucv_water_speed);
								lulv_out_power=lulv_out_power*20;
//								if(lulv_out_power>=9000)		//�ڹ���С��ʱ�� ���ѹ�ܸ�
//								{
//									lulv_out_power=lulv_out_power/guiv_real_voltage;
//								}
//								else
//								{
									lulv_out_power=lulv_out_power/220;
//								}
								
								//�����׼���ȹ���
								gucv_kkg_temp_data=lulv_out_power;
								
								//���ʹ�С ����
								if((gucv_kkg_temp_data<30)&&(gucv_water_speed>18))
								{
									gucv_kkg_temp_data=(unsigned char)(gucv_kkg_temp_data+5);
								}
								
								//ˮ����С ����
//								if(guiv_water_speed<16)
//								{
//									if(gucv_kkg_temp_data>6)
//									{
//										gucv_kkg_temp_data=gucv_kkg_temp_data-6;
//									}
//								}
								
								//44�ȵ�ʱ�� ����
								if((gucv_set_temp==44)&&(gucv_in_water_temp>=20)&&(gucv_water_speed>18))
								{
									gucv_kkg_temp_data=(unsigned char)(gucv_kkg_temp_data+4);
								}
								
								//45�ȵ�ʱ�� ����
								if((gucv_set_temp==45)&&(gucv_in_water_temp>=20)&&(gucv_water_speed>18))
								{
									gucv_kkg_temp_data=(unsigned char)(gucv_kkg_temp_data+4);
								}
								
								//46�ȵ�ʱ�� ����
								if((gucv_set_temp==46)&&(gucv_in_water_temp>=20)&&(gucv_water_speed>18))
								{
									gucv_kkg_temp_data=(unsigned char)(gucv_kkg_temp_data+4);
								}
								
								//47�ȵ�ʱ�� ����
								if((gucv_set_temp==47)&&(gucv_in_water_temp>=20)&&(gucv_water_speed>18))
								{
									gucv_kkg_temp_data=(unsigned char)(gucv_kkg_temp_data+4);
								}
								
								//48�ȵ�ʱ�� ����
								if((gucv_set_temp==48)&&(gucv_in_water_temp>=20)&&(gucv_water_speed>18))
								{
									gucv_kkg_temp_data=(unsigned char)(gucv_kkg_temp_data+5);
								}
								
								//49�ȵ�ʱ�� ����
								if((gucv_set_temp==49)&&(gucv_in_water_temp>=20)&&(gucv_water_speed>18))
								{
									gucv_kkg_temp_data=(unsigned char)(gucv_kkg_temp_data+5);
								}
								
								//50�ȵ�ʱ�� ����
								if((gucv_set_temp==50)&&(gucv_in_water_temp>=20)&&(gucv_water_speed>18))
								{
									gucv_kkg_temp_data=(unsigned char)(gucv_kkg_temp_data+6);
								}
								
								//51�ȵ�ʱ�� ����
								if((gucv_set_temp==51)&&(gucv_in_water_temp>=20)&&(gucv_water_speed>18))
								{
									gucv_kkg_temp_data=(unsigned char)(gucv_kkg_temp_data+6);
								}
								
								//52�ȵ�ʱ�� ����
								if((gucv_set_temp==52)&&(gucv_in_water_temp>=20)&&(gucv_water_speed>18))
								{
									gucv_kkg_temp_data=(unsigned char)(gucv_kkg_temp_data+7);
								}
							}
							
							
							//���¶ȿ�ס������ʱ��,,ֱ�ӽ��빦��ϸ��
							if(luiv_old_temp!=gucv_real_temp)
							{
								luiv_old_temp=gucv_real_temp;
								luiv_temp_stop_change_time=0;
							}
							
							//�¶��ޱ仯��ʱ
							luiv_temp_stop_change_time++;	//7���ޱ仯 ֱ�ӿ�ʼ�����¶�
							if(luiv_temp_stop_change_time>=70)
							{
								luiv_temp_stop_change_time=0;
								
								//7���ޱ仯 ֱ�ӿ�ʼ�����¶�
								if(lucv_now_adj_power==0)
								{
									lucv_now_adj_power=1;
									luiv_power_adj_time_1ms_2=guiv_water_temp_wending_time;
									guiv_work_adj_time=100;
								}
								
								//���¶ȿ�ס������ʱ��  ��������¶ȱ������¶ȵ� ���ʼ�1
								if(gucv_real_temp<(gucv_set_temp-2))
								{
									luiv_power_adj_data++;
								}
							}
							
							//��ˮX��� ���ݳ�ˮ�¶ȵ���
							luiv_power_adj_time_1ms_2++;
							if(luiv_power_adj_time_1ms_2>=guiv_water_temp_wending_time)
							{
								luiv_power_adj_time_1ms_2=guiv_water_temp_wending_time;
								
								//�������ʱ������
								if(gucv_water_speed>=20)
								{
									lucv_power_adj_jiange_time=50;
								}
								else
								{
									lucv_power_adj_jiange_time=gucv_water_speed;
									lucv_power_adj_jiange_time=(unsigned char)(20-lucv_power_adj_jiange_time);
									lucv_power_adj_jiange_time=(unsigned char)(lucv_power_adj_jiange_time*5);
									lucv_power_adj_jiange_time=(unsigned char)(lucv_power_adj_jiange_time+50);
								}
								
								//���ݳ�ˮ�¶ȵ�������
								guiv_work_adj_time++;
								if(guiv_work_adj_time>=lucv_power_adj_jiange_time)
								{
									guiv_work_adj_time=0;
									
									//�Ѿ������¶ȵ���
									lucv_now_adj_power=1;
									
									//�����¶�ADCֵ
									//lulv_water_temp_add=lulv_water_temp_add/luiv_water_temp_add_count;
									
									//��׼���������¶�ADCֵ
									luiv_temp_adc_data=((unsigned int)GetTempAdcVal((gucv_set_temp)))<<4;//ȡ���¶ȱ��е�ADCֵ,��Ϊ��8λ������Ҫ������λ
									
									//�¶Ȳ��� 42��С5  52��С20��  ���ձ�������
									/*
									if(gucv_set_temp==30)
									{luiv_temp_adc_data+=20;}									
									if(gucv_set_temp==31)
									{luiv_temp_adc_data+=12;}									
									if(gucv_set_temp==32)
									{luiv_temp_adc_data+=4;}									
									if(gucv_set_temp==33)
									{luiv_temp_adc_data-=4;}									
									if(gucv_set_temp==34)
									{luiv_temp_adc_data-=12;}									
									if(gucv_set_temp==35)
									{luiv_temp_adc_data-=20;}									
									if(gucv_set_temp==36)
									{luiv_temp_adc_data-=20;}									
									if(gucv_set_temp==37)
									{luiv_temp_adc_data-=20;}									
									if(gucv_set_temp==38)
									{luiv_temp_adc_data-=20;}									
									if(gucv_set_temp==39)
									{luiv_temp_adc_data-=20;}									
									if(gucv_set_temp==40)
									{luiv_temp_adc_data-=20;}									
									if(gucv_set_temp==41)
									{luiv_temp_adc_data-=24;}									
									if(gucv_set_temp==42)
									{luiv_temp_adc_data-=28;}
									if(gucv_set_temp==43)
									{luiv_temp_adc_data-=32;}
									if(gucv_set_temp==44)
									{luiv_temp_adc_data-=36;}
									if(gucv_set_temp==45)
									{luiv_temp_adc_data-=40;}
									if(gucv_set_temp==46)
									{luiv_temp_adc_data-=44;}
									if(gucv_set_temp==47)
									{luiv_temp_adc_data-=48;}
									if(gucv_set_temp==48)
									{luiv_temp_adc_data-=52;}
									if(gucv_set_temp==49)
									{luiv_temp_adc_data-=56;}
									if(gucv_set_temp==50)
									{luiv_temp_adc_data-=60;}
									if(gucv_set_temp==51)
									{luiv_temp_adc_data-=64;}
									if(gucv_set_temp==52)
									{luiv_temp_adc_data-=68;}
									*/
									
									//�¶ȸ� ADֵҪС ���ȱȼ���
									if(guiv_out_water_adc_data<(luiv_temp_adc_data-4))
									{
										if(luiv_power_adj_data>0)
										{
											luiv_power_adj_data--;
										}
										
										if(guiv_out_water_adc_data<(luiv_temp_adc_data-12))
										{
											if(luiv_power_adj_data>0)
											{
												luiv_power_adj_data--;
											}
										}
									}
									//�¶ȵ� ADֵҪ�� ���Ӽ��ȱ�
									if(guiv_out_water_adc_data>(luiv_temp_adc_data+4))
									{
										if(luiv_power_adj_data<200)
										{
											luiv_power_adj_data++;
										}
										
										if(guiv_out_water_adc_data>(luiv_temp_adc_data+12))
										{
											if(luiv_power_adj_data<200)
											{
												luiv_power_adj_data++;
											}
										}
									}
								}
							}
							
							//���������ӵ������
							if(luiv_power_adj_data>=100)
							{
								gucv_kkg_temp_data=gucv_kkg_temp_data+(luiv_power_adj_data-100);
							}
							else
							{
								if(gucv_kkg_temp_data>(100-luiv_power_adj_data))
								{
									gucv_kkg_temp_data=gucv_kkg_temp_data-(100-luiv_power_adj_data);
								}
								else
								{
									gucv_kkg_temp_data=0;
								}	
							}
						}
						else
						{
							gucv_kkg_temp_data=0;
						}
					}
}



/*****************************************************************************
*����			: void power_limit(void)
*������������ 	���ʵ�λ���ƹ���
*�������� 		: ��
*��������ֵ 	: ��
******************************************************************************/
void power_limit(void)
{
			switch(gucv_set_power)
			{
				
				//5500W
				case 55:
				{
					//���ȱ�����
					if(gucv_kkg_temp_data>=80)
					{
						gucv_kkg_temp_data=80;
					}
//					lucv_water_speed_high_power=78;
				}
				break;
								
				//4500W
				case 45:
				{
					//���ȱ�����
					if(gucv_kkg_temp_data>=58)
					{
						gucv_kkg_temp_data=58;
					}
//					lucv_water_speed_high_power=57;
				}
				break;
				
				case 35:
				{
					//���ȱ�����
					if(gucv_kkg_temp_data>=41)
					{
						gucv_kkg_temp_data=41;
					}
//					lucv_water_speed_high_power=40;
				}
				break;
				
				default:
				break;
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
		case MACHINE_WORK_TEMP:
			
//				//ˮ���ж�,�Ƿ�ʼ���ȹ����ж�
				if(gucv_water_speed>=WATER_SPEED_LOW)
				{
					if(gbv_heat_start_working==0)
					{
						if(firsh_run_delay<5)
						{
							if(mSec_x1000_workbit) firsh_run_delay++;
						}
						else
							gbv_heat_start_working=1;
						//guiv_out_water_adc_data_ago=guiv_out_water_adc_data;						
					}
				}
				else
				{
					gbv_heat_start_working=0;
					
					//�رտɿع����
					triacOnEnable=0;		//�ɿع����ʹ�ܽ�ֹ
					Triac_IO_Ctrl(Triac_IO_OFF);//�ɿع�����ر�

					//��λ��������
					gucv_kkg_temp_data=0;
					gucv_water_temp_con_step=0;		//���Ȳ�������

					
					break;//�˳�����ѭ��,��������ִ��
				}
		
		
		
			if(mSec_x10_workbit)
			{
								
				//���ȱȼ���
				switch(gucv_water_temp_con_step)
				{
					//�ж��¶Ȳ���Ƿ񵽴�10��
					case	0:
						water_temp_con_step0();
					break;
					
					//�ñ�׼���ȱȼ���  ��ʱX������΢��
					case	1:
						water_temp_con_step1();
					break;
					
					default:
						gucv_water_temp_con_step=0;
					break;
				}

				
				//�����ʵ�λ���ƹ���
				power_limit();
				
				
				//������ռ��ȱ�,,,
				if(gucv_kkg_temp_data>0)		//��Ҫ���ȵ�ʱ������,,,��ֹ10ms 80�����ݵ��ٽ�����һ��
				{	
					//�ɿع��������
					triacOn_CrossPass=(unsigned char)(80-cucv_power_Tab[gucv_kkg_temp_data]);
					triacOnEnable=1;	
				}
				else
				{
					triacOnEnable=0;	
				}	
			}
			break;


		//�Լ�
		case MACHINE_SELF_CHECK:

		break;

		
		default:
			//�رտɿع����
			triacOnEnable=0;		//�ɿع����ʹ�ܽ�ֹ
			Triac_IO_Ctrl(Triac_IO_OFF);//�ɿع�����ر�
		break;
	}
	
}




/*****************************************************************************
*����			: void Background_Run(void)	
*������������ 	: IO�븺�غ�̨�Զ�����
*�������� 		: ��
*��������ֵ 	: ��
******************************************************************************/
void app_base_run(void)
{
	static unsigned char adcSelect;
	
	
	//ad�Զ����첽��ѯ�ɼ���ص�ִ��
	//zd_adcRun();

	//ad�ֶ��첽�ɼ�

	if(1==adcSelect)
	{
		if(zd_getAdc_async(WATERIN_AIN_Channel,&waterin_Temp_ad))
		{
			if(waterin_Temp_ad>3900||waterin_Temp_ad<200) WaterInNtc_Error=1; else
			{
				WaterInNtc_Error=0;
				waterin_Temp_ad>>=4;
				gucv_in_water_temp=CalcTmpC(waterin_Temp_ad,gucv_in_water_temp);
			}
			adcSelect++;
		}
	}
	else if(3==adcSelect)
	{
		if(zd_getAdc_async(WATEROUT_AIN_Channel,&waterout_Temp_ad))
		{
			if(waterout_Temp_ad>3900||waterout_Temp_ad<200) WaterOutNtc_Error=1; 
			else 
			{
				WaterOutNtc_Error=0;
				guiv_out_water_adc_data=waterout_Temp_ad;
				waterout_Temp_ad>>=4;
				gucv_real_temp=CalcTmpC(waterout_Temp_ad,gucv_real_temp);
			}
			adcSelect++;
		}
	}
	else
	{
		if(zd_getAdc_async(LEAKAGE_AIN_Channel,&leakage_ad))
		{
			if(leakage_ad>315) Leakage_Error=1;
			if(adcSelect<3) adcSelect++; else adcSelect=1;
		}
	}

	
	
	
	if(mSec_x50_workbit)//ÿ50ms����һ��
	{
		//���������������
		zd_buzzerRun();
	
		//gucv_real_temp=CalcTmpC(waterout_Temp_ad,gucv_real_temp);
	}
	

	if(mSec_x10_workbit)//ÿ10ms����һ��
	{
		//��΢����ȡֵ
		__CMS_CheckTouchKey();	//ɨ�谴��
		
		//����ɨ��,��������������־���ֵ��Ϣ
		zd_keyRun();
	}

}
