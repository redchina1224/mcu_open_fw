//******************************************************************************
//Copyright(C) 2020-2021 zhejiang zhida dianzikeji Co., Ltd
//�㽭�Ǵ���ӿƼ����޹�˾
//File name:      variable.h
//Author:         zzg
//Version:        Ver0.1
//Date:           2021-4-25
//Description:    ȫ��ͷ�ļ�����/ȫ�ֺ궨������/ȫ�ֱ�������
//History:
//******************************************************************************
#ifndef _VARIABLE_H__
#define _VARIABLE_H__
//����ͷ�ļ�********************************************************************

//�����궨��********************************************************************
//�����궨��********************************************************************
//TM1640����
#define CFG_DATA_CMD_SETTING    0x44
#define CFG_BRIGHTNESS          4
#define SET_DIN()   RC5=1		//RC5��DIN
#define CLR_DIN()   RC5=0
#define SET_SCLK()  RC4=1		//RC4��clk
#define CLR_SCLK()  RC4=0
#define INIT_TRIS() TRISC &= ~0x30		//����RC4 RC5Ϊ���
#define M_DISP_CTRL_SETTING(en) ((0x80 + CFG_BRIGHTNESS) | (en << 3))
//----�¶ȹ���ADֵ
#define			TEMP_HIGH					55			//�¶�  55��
#define			TEMP_OPEN					1000		//�¶ȿ�·
#define			TEMP_SHORT					10			//�¶ȶ�·
//----Ĭ��PWM�ٶ�
#define			PEM_DEFAULT_DATA			50			//Ĭ��PWM����
//----ˮ���ٶ�
#define			WATER_SPEED_LOW				9				//ˮ���ٶȹ���
//----���϶���
#define			ERROR_E1					0X01		//E1,©��
#define			ERROR_E2					0X02		//E2,ˮ������������
#define			ERROR_E3					0X04		//E3,����
#define			ERROR_E4					0X08		//E4,�¶ȴ���������
//----IO�ڶ���
#define			IO_BUZZ						RB5			//������
#define			IO_KKG						RA3			//�ɿع赼ͨ�ر�
#define			IO_HALL_WATER				RA2			//ˮ����С�������
#define			IO_RELAY					RC2			//�̵������,,
#define			IO_LEAKAGE_PRO				RC0			//©�籣������,
#define			IO_ZERO						RC3			//�����ź�����
#define			IO_IR						RB6			//��������
//----����״̬����
#define			MACHINE_POWER_ON			0			//�ϵ�
#define			MACHINE_IDEL				1			//����
#define			MACHINE_WORK				2			//��������ģʽ
#define			MACHINE_SELF_CHECK			3			//�Լ�
#define			MACHINE_ERROR				4			//����
//----����״̬����
#define			WORK_IDEL					0			//Ĭ�� ����ģʽ
#define			WORK_MODE_SHUSHI			1			//���� ����ģʽ
#define			WORK_MODE_ERTONG			2			//��ͯ ����ģʽ
#define			WORK_MODE_LAOREN			3			//���� ����ģʽ
#define			WORK_MODE_ZHINENG			4			//���� ����ģʽ
#define			WORK_MODE_CHUBAO			5			//���� ����ģʽ
#define			WORK_MODE_XIYI  			6			//ϴ�� ����ģʽ
//----�¶��趨
#define			TEMP_38TEMP					38			//38�Ⱥ��� ����
#define			TEMP_40TEMP					40			//38�Ⱥ��� ����
#define			TEMP_42TEMP					42			//42�Ⱥ��� ����
#define			TEMP_45TEMP					45			//38�Ⱥ��� ����
#define			TEMP_MINIMUM				30			//��С�¶�
#define			TEMP_MAXIMUM				52			//����¶�
//----����ֵ
#define			KEY_TEMP_38					0X00000020	//����38
#define			KEY_TEMP_40					0X00000001	//����40
#define			KEY_TEMP_42					0X00000002	//����42
#define			KEY_TEMP_45					0X00000008	//����45
#define			KEY_START					0X00000004	//����
#define			KEY_TEMP_DOWN				0X00000010	//�¶��½�
#define			KEY_MODE					0X00000080	//ģʽ�л�
#define			KEY_TEMP_UP					0X00000040	//�¶�����
#define			KEY_START_LONG				0X10000004	//������������
#define			KEY_LEARN_LONG				0X10000050	//�¶��������½�
//----����ɨ��ʱ��Ϊ1ms,
#define			KEY_DOWN_TIME				5			//�������¹���ʱ��
#define			KEY_UP_TIME					5			//����̧�����ʱ��
#define			KEY_LONG_TIME_CONTINUE		10			//��������������ʱ��
#define			KEY_ERROR_TIME				1000		//����һֱ���±���
#define			KEY_LONG_TIME				100		//1��,,
#define			KEY_LONG_TIME_3S			300		//3��,,
//�����ⲿ����********************************************************************
//----ˮ�¿���
extern	unsigned	char	gucv_water_temp_con_step;		//ˮ�¿��Ʋ���
extern	unsigned	char	gucv_kkg_temp_data;				//�ɿع����� �м������
extern	unsigned	int		guiv_water_temp_wending_time;	//ˮ���ȶ�ʱ��
//----ʱ�����
extern	unsigned	char	gucv_base_time_1ms;				//��׼ʱ��1ms
extern	unsigned	char	gucv_time_1ms;					//1ms
extern	unsigned	char	gucv_time_1ms_adc;				//1ms adcʹ��
extern	unsigned	char	gucv_time_1ms_CHECK_KEY;		//1ms �����⺯������ʹ��
extern	unsigned	char	gucv_time_500ms_flicker;		//500ms,0-1����״̬
extern	unsigned	char	gucv_time_1s;					//1S��ʱ
//----�������
extern	bit					gbv_kkg_out_en;					//�ɿع��������
extern	bit					gbv_arrive_set_temp;			//�ﵽ�趨�¶�
extern	bit					gbv_error_en;					//���Ա���
extern	unsigned	char	gucv_error_status;				//����״̬
extern	unsigned	char	gucv_machine_status;			//����״̬
extern	unsigned	char	gucv_machine_status_bak;		//����״̬,�ڱ����ָ��� �ָ�����״̬
extern	unsigned	char	gucv_work_status;				//����״̬ Ĭ������
extern	unsigned	char	gucv_power_status;				//����״̬
extern	unsigned	char	gucv_real_temp;					//��ʵ�¶�
extern	unsigned	char	gucv_in_water_temp;				//��ˮ���¶�
extern	unsigned	char	gucv_set_temp;					//�����¶�
extern	unsigned	int 	guiv_real_voltage;				//��ѹ
extern	unsigned	char 	gucv_water_pluse_count;			//ˮ��������
//extern	unsigned	char 	gucv_water_speed;				//ˮ���ٶ�
extern	unsigned	int 	guiv_water_led_pmd;				//ˮ��LED�����
extern	unsigned	int 	guiv_work_low_temp_count;		//ˮ��һֱû�дﵽ��ʱ
extern	unsigned	int 	guiv_work_adj_time;				//����ʱ�����ɿع�������ʱ��
extern	unsigned	char 	gucv_work_kkg_drv_data;			//����ʱ�ɿع�����ʱ�� 0-100  һ��100��
extern	unsigned	char 	gucv_voltage_collect_en_count;	//�ɼ���ѹ����,,�ڿ�����ʱ�� ��ѹ��ͻ�� ���ο����ɼ�
extern	unsigned	int		guiv_dis_power_status_time;		//�����趨���ʵ�λ
extern	unsigned	int		guiv_temp_display_time;			//��ʾ�¶Ȳ�����ʱ
extern	unsigned	int		guiv_temp_display_data;			//��ʾ�¶Ȳ���ֵ
extern	unsigned	int		guiv_learn_time;				//ѧϰʱ��

//----�Լ����

//----EEPROM���
extern	bit					gbv_write_en;					//�����¼����
extern	unsigned	char	eeprom_work_temp[3];			//����������¶�

//----���ʱ��  80�� 1�ݱ�ʾ75W
extern	const	unsigned char	cucv_power_Tab[81];

#endif 

/************************ (C) COPYRIGHT zhejiang zhida *****END OF FILE****/




