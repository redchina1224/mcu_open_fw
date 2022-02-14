//******************************************************************************
//Copyright(C) 2020-2021 zhejiang zhida dianzikeji Co., Ltd
//�㽭�Ǵ���ӿƼ����޹�˾
//File name:      variable.c
//Author:         zzg
//Version:        Ver0.1
//Date:           2021-4-25
//Description:    ȫ�ֱ�������
//History:
//******************************************************************************
//ͷ�ļ�************************************************************************
#include "variable.h"
//����**************************************************************************
//----ˮ�¿���
unsigned	char	gucv_water_temp_con_step=0;			//ˮ�¿��Ʋ���
unsigned	char	gucv_kkg_temp_data=0;				//�ɿع����� �м������
unsigned	int		guiv_water_temp_wending_time=0;		//ˮ���ȶ�ʱ��
//----ʱ�����
unsigned	char	gucv_base_time_1ms=0;				//��׼ʱ��1ms
unsigned	char	gucv_time_1ms=0;					//1ms
unsigned	char	gucv_time_1ms_adc=0;				//1ms adcʹ��
unsigned	char	gucv_time_1ms_CHECK_KEY=0;			//1ms �����⺯������ʹ��
unsigned	char	gucv_time_500ms_flicker=0;			//500ms,0-1����״̬
unsigned	char	gucv_time_1s=0;						//1S��ʱ
//----�������
bit					gbv_kkg_out_en=0;					//�ɿع��������
bit					gbv_arrive_set_temp=0;				//�ﵽ�趨�¶�
bit					gbv_error_en=0;						//���Ա���
unsigned	char	gucv_error_status=0;				//����״̬
unsigned	char	gucv_machine_status=0;				//����״̬
unsigned	char	gucv_machine_status_bak=0;			//����״̬,�ڱ����ָ��� �ָ�����״̬
unsigned	char	gucv_power_status=0;				//����״̬
unsigned	char	gucv_work_status=0;					//����״̬
unsigned	char	gucv_real_temp=25;					//��ʵ�¶�
unsigned	char	gucv_in_water_temp=25;				//��ˮ���¶�
unsigned	char	gucv_set_temp=0;					//�����¶�
unsigned	int 	guiv_real_voltage=0;				//��ѹ
unsigned	char 	gucv_water_pluse_count=0;			//ˮ��������
//unsigned	char 	gucv_water_speed=0;					//ˮ���ٶ�
unsigned	int 	guiv_water_led_pmd=0;				//ˮ��LED�����
unsigned	int 	guiv_work_low_temp_count=0;			//ˮ��һֱû�дﵽ��ʱ
unsigned	int 	guiv_work_adj_time=0;				//����ʱ�����ɿع�������ʱ��
unsigned	char 	gucv_work_kkg_drv_data=0;			//����ʱ�ɿع�����ʱ�� 0-100  һ��100��
unsigned	char 	gucv_voltage_collect_en_count=0;	//�ɼ���ѹ����,,�ڿ�����ʱ�� ��ѹ��ͻ�� ���ο����ɼ�
unsigned	int		guiv_dis_power_status_time=0;		//�����趨���ʵ�λ
unsigned	int		guiv_temp_display_time=0;			//��ʾ�¶Ȳ�����ʱ
unsigned	int		guiv_temp_display_data=0;			//��ʾ�¶Ȳ���ֵ
unsigned	int		guiv_learn_time=0;					//ѧϰʱ��



//----EEPROM���
bit					gbv_write_en=0;						//�����¼����
unsigned	char	eeprom_work_temp[3];				//����������¶�
//----��ʾ���

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
/************************ (C) COPYRIGHT zhejiang zhida *****END OF FILE****/

