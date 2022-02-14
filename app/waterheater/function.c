//******************************************************************************
//Copyright(C) 2020-2021 zhejiang zhida dianzikeji Co., Ltd
//浙江智达电子科技有限公司
//File name:      function.c
//Author:         zzg
//Version:        Ver0.1
//Date:           2021-4-25
//Description:    功能
//History:
//******************************************************************************
//头文件************************************************************************
#include "variable.h"
//函数**************************************************************************
/***********************************************
函数名称：sign_process
函数功能：信号处理
入口参数：无
出口参数：无
备注：
************************************************/
void sign_process(void)
{
	static unsigned	char lucv_warn_count=0;			//漏电计时
	static unsigned	int	 luiv_1ms_count=0;			//水流计算
		
	//----漏电检测IO
	if(IO_LEAKAGE_PRO==0)
	{
		lucv_warn_count++;
		if(lucv_warn_count>=30)
		{
			lucv_warn_count=30;
			//报警
			if(gbv_error_en==1)
			{
				//不是第一次报警 蜂鸣器响
				if((gucv_error_status&ERROR_E1)!=ERROR_E1)
				{
					if(gucv_machine_status!=MACHINE_ERROR)//备份机器状态
					{gucv_machine_status_bak=gucv_machine_status;}
					//蜂鸣器叫一声
					gucv_buzz_count=5;
					guiv_buzz_time_add=0;
				}
				//切换到报警状态
				gucv_error_status|=ERROR_E1;
				gucv_machine_status=MACHINE_ERROR;
			}
		}
	}
	else
	{
		lucv_warn_count=0;
	}
	
	//精准1ms输出水流脉冲数
	luiv_1ms_count++;
	if(luiv_1ms_count>1000)
	{
		luiv_1ms_count=0;
		//----1S检测一次水流脉冲数//输出水流脉冲数
		gucv_water_speed=gucv_water_pluse_count;
		gucv_water_pluse_count=0;
	}
}

/***********************************************************************************************
*函数名 				: function_process
*函数功能描述 	: 工作处理
*函数参数 			: 无
*函数返回值 		: 无
***********************************************************************************************/
void	function_process(void)
{
	static	unsigned	long	lulv_out_power=0;							//标准输出功率
	static	unsigned	int		luiv_power_adj_time_1ms=0;		//标准功率调整间隔
	static	unsigned	int		luiv_power_adj_time_1ms_2=0;	//根据出水温度功率调整间隔
	static	unsigned	int		luiv_power_adj_data=0;				//功率调整量
	static	unsigned	int		luiv_temp_adc_data=0;					//需要的ADC值
	static	unsigned	int		luiv_water_speed_data=0;			//水流大小
	static	unsigned	char	lucv_water_speed_high_power=0;//判断水流过大的功率数据
	static	unsigned	char	lucv_power_adj_jiange_time=0;	//根据出水温度调节功率大小间隔时间 设置
	static	unsigned	int		luiv_E1_buzz_time=0;					//根据出水温度调节功率大小间隔时间 设置
	static	unsigned	int		luiv_temp_stop_change_time=0;	//温度停止变化时间
	static	unsigned	int		luiv_old_temp=0;							//上一次的温度
	static	unsigned	char	lucv_now_adj_power=0;					//已经进入调整温度
	
	//机器状态
	switch(gucv_machine_status)
	{
		//上电
		case MACHINE_POWER_ON:
		{
			//3秒后进入待机
			if(gucv_time_1s>=3)
			{
				gucv_machine_status=MACHINE_IDEL;
				//蜂鸣器叫一声
				gucv_buzz_count=1;
				guiv_buzz_time_add=0;
				
				//允许记录数据
				gbv_write_en=1;	
				
				//允许报警
				gbv_error_en=1;
			}
			//关闭输出
			IO_RELAY=0;
			IO_KKG=1;
			gbv_kkg_out_en=0;						//可控硅输出关闭
		}
		break;
		
		//待机
		case MACHINE_IDEL:
		{
			//关闭输出
			IO_RELAY=0;
			IO_KKG=1;
			gbv_kkg_out_en=0;						//可控硅输出关闭
		}
		break;
		
		//工作
		case MACHINE_WORK:
		{
			//加热比计算
			switch(gucv_water_temp_con_step)
			{
				//判断温度差距是否到达10度
				case	0:
				{
					//水流过小 直接进去下一步
					if(gucv_water_speed<=18)
					{
						gucv_water_temp_con_step=1;		//进入标准功率加热
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
					
					//根据温度判断是否需要全功率加热
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
						gucv_water_temp_con_step=1;		//进入标准功率加热
						gucv_kkg_temp_data=0;
					}
					
					//计算所需调整时间
					if(gucv_set_temp>=gucv_real_temp)
					{
						guiv_water_temp_wending_time=(unsigned char)(gucv_set_temp-gucv_real_temp);
					}
					else
					{
						guiv_water_temp_wending_time=((unsigned char)((gucv_real_temp-gucv_set_temp)>>1));
					}
					
					//换算成100ms *15
					if(guiv_water_temp_wending_time>20)
					{
						guiv_water_temp_wending_time=20;
					}
					guiv_water_temp_wending_time=guiv_water_temp_wending_time*12;
					if(guiv_water_temp_wending_time<50)
					{
						guiv_water_temp_wending_time=50;
					}
					luiv_power_adj_data=100;					//功率调整量
					luiv_power_adj_time_1ms=0;				//额定功率计算间隔
					guiv_work_adj_time=0;							//计时清零 功率调整  第一次进去就调整
					luiv_power_adj_time_1ms_2=0;			//根据出水温度功率调整间隔
					luiv_temp_stop_change_time=0;			//温度停止变化时间
					luiv_old_temp=0;									//上一次的温度
					lucv_now_adj_power=0;							//已经进入调整温度
				}
				break;
				
				//用标准加热比加热  计时X秒后进入微调
				case	1:
				{
					//----标准功率计算
					luiv_power_adj_time_1ms++;
					if(luiv_power_adj_time_1ms>=10)
					{
						luiv_power_adj_time_1ms=0;
						//计算标准输出功率 百分比 = 水流量*温度差*0.11676
						if(gucv_set_temp>gucv_in_water_temp)		//输出设定温度大于进水温度
						{
							//----计算标准功率
							{
								lulv_out_power=(unsigned char)(gucv_set_temp-gucv_in_water_temp);
								//温度补偿
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
								
								//计算标准功率
								lulv_out_power=lulv_out_power*(gucv_water_speed);
								lulv_out_power=lulv_out_power*20;
								if(lulv_out_power>=9000)		//在功率小的时候 虚电压很高
								{
									lulv_out_power=lulv_out_power/guiv_real_voltage;
								}
								else
								{
									lulv_out_power=lulv_out_power/220;
								}
								
								//输出标准加热功率
								gucv_kkg_temp_data=lulv_out_power;
								
								//功率过小 补偿
								if((gucv_kkg_temp_data<30)&&(gucv_water_speed>18))
								{
									gucv_kkg_temp_data=(unsigned char)(gucv_kkg_temp_data+5);
								}
								
								//水流过小 补偿
//								if(guiv_water_speed<16)
//								{
//									if(gucv_kkg_temp_data>6)
//									{
//										gucv_kkg_temp_data=gucv_kkg_temp_data-6;
//									}
//								}
								
								//44度的时候 补偿
								if((gucv_set_temp==44)&&(gucv_in_water_temp>=20)&&(gucv_water_speed>18))
								{
									gucv_kkg_temp_data=(unsigned char)(gucv_kkg_temp_data+4);
								}
								
								//45度的时候 补偿
								if((gucv_set_temp==45)&&(gucv_in_water_temp>=20)&&(gucv_water_speed>18))
								{
									gucv_kkg_temp_data=(unsigned char)(gucv_kkg_temp_data+4);
								}
								
								//46度的时候 补偿
								if((gucv_set_temp==46)&&(gucv_in_water_temp>=20)&&(gucv_water_speed>18))
								{
									gucv_kkg_temp_data=(unsigned char)(gucv_kkg_temp_data+4);
								}
								
								//47度的时候 补偿
								if((gucv_set_temp==47)&&(gucv_in_water_temp>=20)&&(gucv_water_speed>18))
								{
									gucv_kkg_temp_data=(unsigned char)(gucv_kkg_temp_data+4);
								}
								
								//48度的时候 补偿
								if((gucv_set_temp==48)&&(gucv_in_water_temp>=20)&&(gucv_water_speed>18))
								{
									gucv_kkg_temp_data=(unsigned char)(gucv_kkg_temp_data+5);
								}
								
								//49度的时候 补偿
								if((gucv_set_temp==49)&&(gucv_in_water_temp>=20)&&(gucv_water_speed>18))
								{
									gucv_kkg_temp_data=(unsigned char)(gucv_kkg_temp_data+5);
								}
								
								//50度的时候 补偿
								if((gucv_set_temp==50)&&(gucv_in_water_temp>=20)&&(gucv_water_speed>18))
								{
									gucv_kkg_temp_data=(unsigned char)(gucv_kkg_temp_data+6);
								}
								
								//51度的时候 补偿
								if((gucv_set_temp==51)&&(gucv_in_water_temp>=20)&&(gucv_water_speed>18))
								{
									gucv_kkg_temp_data=(unsigned char)(gucv_kkg_temp_data+6);
								}
								
								//52度的时候 补偿
								if((gucv_set_temp==52)&&(gucv_in_water_temp>=20)&&(gucv_water_speed>18))
								{
									gucv_kkg_temp_data=(unsigned char)(gucv_kkg_temp_data+7);
								}
							}
							
							
							//当温度卡住不动的时候,,直接进入功率细调
							if(luiv_old_temp!=gucv_real_temp)
							{
								luiv_old_temp=gucv_real_temp;
								luiv_temp_stop_change_time=0;
							}
							
							//温度无变化计时
							luiv_temp_stop_change_time++;	//7秒无变化 直接开始调节温度
							if(luiv_temp_stop_change_time>=70)
							{
								luiv_temp_stop_change_time=0;
								
								//7秒无变化 直接开始调节温度
								if(lucv_now_adj_power==0)
								{
									lucv_now_adj_power=1;
									luiv_power_adj_time_1ms_2=guiv_water_temp_wending_time;
									guiv_work_adj_time=100;
								}
								
								//当温度卡住不动的时候  如果真是温度比设置温度底 功率加1
								if(gucv_real_temp<(gucv_set_temp-2))
								{
									luiv_power_adj_data++;
								}
							}
							
							//流水X秒后 根据出水温度调节
							luiv_power_adj_time_1ms_2++;
							if(luiv_power_adj_time_1ms_2>=guiv_water_temp_wending_time)
							{
								luiv_power_adj_time_1ms_2=guiv_water_temp_wending_time;
								
								//调整间隔时间配置
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
								
								//根据出水温度调整功率
								guiv_work_adj_time++;
								if(guiv_work_adj_time>=lucv_power_adj_jiange_time)
								{
									guiv_work_adj_time=0;
									
									//已经进入温度调节
									lucv_now_adj_power=1;
									
									//计算温度ADC值
									//lulv_water_temp_add=lulv_water_temp_add/luiv_water_temp_add_count;
									
									//标准不补偿的温度ADC值
									luiv_temp_adc_data=cuiv_temp_Tab[gucv_set_temp];
									
									//温度补偿 42减小5  52减小20度  按照比例计算
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
									
									//温度高 AD值要小 加热比减少
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
									//温度低 AD值要大 增加加热比
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
							
							//调整量叠加到输出上
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

			
			//在水流过小的时候 关闭加热 关闭继电器
			if(gucv_water_speed<WATER_SPEED_LOW)
			{
				gucv_kkg_temp_data=0;
				//关闭继电器
				IO_RELAY=0;
				gbv_kkg_out_en=0;	
				gucv_water_temp_con_step=0;		//加热步骤清零
			}
			else
			{
				//打开继电器
				IO_RELAY=1;
			}
			
			//功率档位限制功率
			switch(gucv_power_status)
			{
				//7000W
				case 70:
				{
					//加热比限制
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
					//加热比限制
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
					//加热比限制
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
					//加热比限制
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
					//加热比限制
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
					//加热比限制
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
					//加热比限制
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
					//加热比限制
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
			
			//计时累加 如果30秒内一直没有到设定温度 认为水流大
			if((guiv_work_low_temp_count<3000)&&(gucv_kkg_temp_data>=lucv_water_speed_high_power))
			{
				if(guiv_work_low_temp_count<3000)
				{
					guiv_work_low_temp_count++;
				}
			}
			
			//设定温度到了 清零水流大数据
			if(gucv_real_temp>=(gucv_set_temp-2))
			{
				guiv_work_low_temp_count=0;//清零水流大数据计时
			}
			
			//输出最终加热比,,,
			if(gucv_kkg_temp_data>0)		//需要加热的时候才输出,,,防止10ms 80个数据的临界点加热一下
			{	
				//可控硅输出允许
				gucv_work_kkg_drv_data=(unsigned char)(80-cucv_power_Tab[gucv_kkg_temp_data]);
				gbv_kkg_out_en=1;	
			}
			else
			{
				gbv_kkg_out_en=0;	
			}	
		}
		break;
		
		
		//故障
		case MACHINE_ERROR:
		{
			//关闭输出
			IO_RELAY=0;
			IO_KKG=1;
			gbv_kkg_out_en=0;		//可控硅输出关闭
			
			if(gucv_error_status==0)
			{
				gucv_machine_status=gucv_machine_status_bak;		//备份机器状态
				if(gucv_machine_status==MACHINE_WORK)
				{
					//清零计时器
					gucv_work_kkg_drv_data=PEM_DEFAULT_DATA;
					gbv_kkg_out_en=0;						//可控硅输出关闭
					guiv_work_low_temp_count=0;	//水流检测清零
					gucv_water_temp_con_step=0;	//加热步骤清零	
					gbv_arrive_set_temp=0;			//达到设定温度
					guiv_temp_display_time=0;		//清除显示温度补偿计时和数据
					guiv_temp_display_data=0;		//清除显示温度补偿计时和数据
				}
			}
		}
		break;
		
		//自检
		case MACHINE_SELF_CHECK:
		{}
		break;
		
		default:
		break;
	}
}
/************************ (C) COPYRIGHT zhejiang zhida *****END OF FILE****/

