//******************************************************************************
//Copyright(C) 2020-2021 zhejiang zhida dianzikeji Co., Ltd
//�㽭�Ǵ���ӿƼ����޹�˾
//File name:      function.c
//Author:         zzg
//Version:        Ver0.1
//Date:           2021-4-25
//Description:    ����
//History:
//******************************************************************************
//ͷ�ļ�************************************************************************
#include "variable.h"
//����**************************************************************************
/***********************************************
�������ƣ�sign_process
�������ܣ��źŴ���
��ڲ�������
���ڲ�������
��ע��
************************************************/
void sign_process(void)
{
	static unsigned	char lucv_warn_count=0;			//©���ʱ
	static unsigned	int	 luiv_1ms_count=0;			//ˮ������
		
	//----©����IO
	if(IO_LEAKAGE_PRO==0)
	{
		lucv_warn_count++;
		if(lucv_warn_count>=30)
		{
			lucv_warn_count=30;
			//����
			if(gbv_error_en==1)
			{
				//���ǵ�һ�α��� ��������
				if((gucv_error_status&ERROR_E1)!=ERROR_E1)
				{
					if(gucv_machine_status!=MACHINE_ERROR)//���ݻ���״̬
					{gucv_machine_status_bak=gucv_machine_status;}
					//��������һ��
					gucv_buzz_count=5;
					guiv_buzz_time_add=0;
				}
				//�л�������״̬
				gucv_error_status|=ERROR_E1;
				gucv_machine_status=MACHINE_ERROR;
			}
		}
	}
	else
	{
		lucv_warn_count=0;
	}
	
	//��׼1ms���ˮ��������
	luiv_1ms_count++;
	if(luiv_1ms_count>1000)
	{
		luiv_1ms_count=0;
		//----1S���һ��ˮ��������//���ˮ��������
		gucv_water_speed=gucv_water_pluse_count;
		gucv_water_pluse_count=0;
	}
}

/***********************************************************************************************
*������ 				: function_process
*������������ 	: ��������
*�������� 			: ��
*��������ֵ 		: ��
***********************************************************************************************/
void	function_process(void)
{
	static	unsigned	long	lulv_out_power=0;							//��׼�������
	static	unsigned	int		luiv_power_adj_time_1ms=0;		//��׼���ʵ������
	static	unsigned	int		luiv_power_adj_time_1ms_2=0;	//���ݳ�ˮ�¶ȹ��ʵ������
	static	unsigned	int		luiv_power_adj_data=0;				//���ʵ�����
	static	unsigned	int		luiv_temp_adc_data=0;					//��Ҫ��ADCֵ
	static	unsigned	int		luiv_water_speed_data=0;			//ˮ����С
	static	unsigned	char	lucv_water_speed_high_power=0;//�ж�ˮ������Ĺ�������
	static	unsigned	char	lucv_power_adj_jiange_time=0;	//���ݳ�ˮ�¶ȵ��ڹ��ʴ�С���ʱ�� ����
	static	unsigned	int		luiv_E1_buzz_time=0;					//���ݳ�ˮ�¶ȵ��ڹ��ʴ�С���ʱ�� ����
	static	unsigned	int		luiv_temp_stop_change_time=0;	//�¶�ֹͣ�仯ʱ��
	static	unsigned	int		luiv_old_temp=0;							//��һ�ε��¶�
	static	unsigned	char	lucv_now_adj_power=0;					//�Ѿ���������¶�
	
	//����״̬
	switch(gucv_machine_status)
	{
		//�ϵ�
		case MACHINE_POWER_ON:
		{
			//3���������
			if(gucv_time_1s>=3)
			{
				gucv_machine_status=MACHINE_IDEL;
				//��������һ��
				gucv_buzz_count=1;
				guiv_buzz_time_add=0;
				
				//�����¼����
				gbv_write_en=1;	
				
				//������
				gbv_error_en=1;
			}
			//�ر����
			IO_RELAY=0;
			IO_KKG=1;
			gbv_kkg_out_en=0;						//�ɿع�����ر�
		}
		break;
		
		//����
		case MACHINE_IDEL:
		{
			//�ر����
			IO_RELAY=0;
			IO_KKG=1;
			gbv_kkg_out_en=0;						//�ɿع�����ر�
		}
		break;
		
		//����
		case MACHINE_WORK:
		{
			//���ȱȼ���
			switch(gucv_water_temp_con_step)
			{
				//�ж��¶Ȳ���Ƿ񵽴�10��
				case	0:
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
				break;
				
				//�ñ�׼���ȱȼ���  ��ʱX������΢��
				case	1:
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
								if(lulv_out_power>=9000)		//�ڹ���С��ʱ�� ���ѹ�ܸ�
								{
									lulv_out_power=lulv_out_power/guiv_real_voltage;
								}
								else
								{
									lulv_out_power=lulv_out_power/220;
								}
								
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
									luiv_temp_adc_data=cuiv_temp_Tab[gucv_set_temp];
									
									//�¶Ȳ��� 42��С5  52��С20��  ���ձ�������
									if(gucv_set_temp==42)
									{luiv_temp_adc_data+=6;}
									if(gucv_set_temp==43)
									{luiv_temp_adc_data+=7;}
									if(gucv_set_temp==44)
									{luiv_temp_adc_data+=8;}
									if(gucv_set_temp==45)
									{luiv_temp_adc_data+=9;}
									if(gucv_set_temp==46)
									{luiv_temp_adc_data+=10;}
									if(gucv_set_temp==47)
									{luiv_temp_adc_data+=11;}
									if(gucv_set_temp==48)
									{luiv_temp_adc_data+=12;}
									if(gucv_set_temp==49)
									{luiv_temp_adc_data+=13;}
									if(gucv_set_temp==50)
									{luiv_temp_adc_data+=14;}
									if(gucv_set_temp==51)
									{luiv_temp_adc_data+=15;}
									if(gucv_set_temp==52)
									{luiv_temp_adc_data+=20;}
									
									//�¶ȸ� ADֵҪС ���ȱȼ���
									if(guiv_out_water_adc_data<(luiv_temp_adc_data-8))
									{
										if(luiv_power_adj_data>0)
										{
											luiv_power_adj_data--;
										}
										
										if(guiv_out_water_adc_data<(luiv_temp_adc_data-25))
										{
											if(luiv_power_adj_data>0)
											{
												luiv_power_adj_data--;
											}
										}
									}
									//�¶ȵ� ADֵҪ�� ���Ӽ��ȱ�
									if(guiv_out_water_adc_data>(luiv_temp_adc_data+8))
									{
										if(luiv_power_adj_data<200)
										{
											luiv_power_adj_data++;
										}
										
										if(guiv_out_water_adc_data>(luiv_temp_adc_data+25))
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
				break;
				
				default:
					gucv_water_temp_con_step=0;
				break;
			}

			
			//��ˮ����С��ʱ�� �رռ��� �رռ̵���
			if(gucv_water_speed<WATER_SPEED_LOW)
			{
				gucv_kkg_temp_data=0;
				//�رռ̵���
				IO_RELAY=0;
				gbv_kkg_out_en=0;	
				gucv_water_temp_con_step=0;		//���Ȳ�������
			}
			else
			{
				//�򿪼̵���
				IO_RELAY=1;
			}
			
			//���ʵ�λ���ƹ���
			switch(gucv_power_status)
			{
				//7000W
				case 70:
				{
					//���ȱ�����
					if(gucv_kkg_temp_data>=80)
					{
						gucv_kkg_temp_data=80;
					}
					lucv_water_speed_high_power=78;
				}
				break;
				
				//6500W
				case 65:
				{
					//���ȱ�����
					if(gucv_kkg_temp_data>=66)
					{
						gucv_kkg_temp_data=66;
					}
					lucv_water_speed_high_power=65;
				}
				break;
				
				//6000W
				case 60:
				{
					//���ȱ�����
					if(gucv_kkg_temp_data>=59)
					{
						gucv_kkg_temp_data=59;
					}
					lucv_water_speed_high_power=58;
				}
				break;
				
				//5500W
				case 55:
				{
					//���ȱ�����
					if(gucv_kkg_temp_data>=55)
					{
						gucv_kkg_temp_data=55;
					}
					lucv_water_speed_high_power=54;
				}
				break;
				
				//5000W
				case 50:
				{
					//���ȱ�����
					if(gucv_kkg_temp_data>=50)
					{
						gucv_kkg_temp_data=50;
					}
					lucv_water_speed_high_power=49;
				}
				break;
				
				//4500W
				case 45:
				{
					//���ȱ�����
					if(gucv_kkg_temp_data>=47)
					{
						gucv_kkg_temp_data=47;
					}
					lucv_water_speed_high_power=46;
				}
				break;
				
				//4000W
				case 40:
				{
					//���ȱ�����
					if(gucv_kkg_temp_data>=43)
					{
						gucv_kkg_temp_data=43;
					}
					lucv_water_speed_high_power=42;
				}
				break;
				case 35:
				/*
				{
					//���ȱ�����
					if(gucv_kkg_temp_data>=XXX)
					{
						gucv_kkg_temp_data=XXX;
					}
					lucv_water_speed_high_power=XXX-1;
				}
				*/
				break;

				break;
				
				default:
				break;
			}
			
			//��ʱ�ۼ� ���30����һֱû�е��趨�¶� ��Ϊˮ����
			if((guiv_work_low_temp_count<3000)&&(gucv_kkg_temp_data>=lucv_water_speed_high_power))
			{
				if(guiv_work_low_temp_count<3000)
				{
					guiv_work_low_temp_count++;
				}
			}
			
			//�趨�¶ȵ��� ����ˮ��������
			if(gucv_real_temp>=(gucv_set_temp-2))
			{
				guiv_work_low_temp_count=0;//����ˮ�������ݼ�ʱ
			}
			
			//������ռ��ȱ�,,,
			if(gucv_kkg_temp_data>0)		//��Ҫ���ȵ�ʱ������,,,��ֹ10ms 80�����ݵ��ٽ�����һ��
			{	
				//�ɿع��������
				gucv_work_kkg_drv_data=(unsigned char)(80-cucv_power_Tab[gucv_kkg_temp_data]);
				gbv_kkg_out_en=1;	
			}
			else
			{
				gbv_kkg_out_en=0;	
			}	
		}
		break;
		
		
		//����
		case MACHINE_ERROR:
		{
			//�ر����
			IO_RELAY=0;
			IO_KKG=1;
			gbv_kkg_out_en=0;		//�ɿع�����ر�
			
			if(gucv_error_status==0)
			{
				gucv_machine_status=gucv_machine_status_bak;		//���ݻ���״̬
				if(gucv_machine_status==MACHINE_WORK)
				{
					//�����ʱ��
					gucv_work_kkg_drv_data=PEM_DEFAULT_DATA;
					gbv_kkg_out_en=0;						//�ɿع�����ر�
					guiv_work_low_temp_count=0;	//ˮ���������
					gucv_water_temp_con_step=0;	//���Ȳ�������	
					gbv_arrive_set_temp=0;			//�ﵽ�趨�¶�
					guiv_temp_display_time=0;		//�����ʾ�¶Ȳ�����ʱ������
					guiv_temp_display_data=0;		//�����ʾ�¶Ȳ�����ʱ������
				}
			}
		}
		break;
		
		//�Լ�
		case MACHINE_SELF_CHECK:
		{}
		break;
		
		default:
		break;
	}
}
/************************ (C) COPYRIGHT zhejiang zhida *****END OF FILE****/

