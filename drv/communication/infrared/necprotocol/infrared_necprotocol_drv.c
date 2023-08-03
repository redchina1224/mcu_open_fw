//******************************************************************************
//Copyright(C) 2020-2021 zhejiang zhida dianzikeji Co., Ltd
//浙江智达电子科技有限公司
//File name:      TM1628.c
//Author:         zzg
//Version:        Ver0.1
//Date:           2021-4-25
//Description:    TM1628驱动
//History:
//******************************************************************************
//头文件************************************************************************
#include "..\..\..\com_include_drv.h"
//******************************************************************************

mof_fix_length_infrared_t xdata fixed_length_infrared_nec[1];
unsigned char xdata infrared_object_select=0;


/***********************************************************************************************
*函数名 		: void infrared_fixed_length_in_isr(void)
*函数功能描述 	: 单线通讯邓氏接收服务程序(用于数据连续接收和发送)
*函数参数 		: unsigned char *RxReg：串口硬件接收缓存地址指针
*函数返回值 	: 无
***********************************************************************************************/
void infrared_fixed_length_init(unsigned char i,unsigned char *sendbuf,unsigned char *recvbuf,unsigned char recv_len)
{
		fixed_length_infrared_nec[i].p_WriteBuffer=(sendbuf);
		fixed_length_infrared_nec[i].p_ReadBuffer=(recvbuf);
		fixed_length_infrared_nec[i].ReadLength=recv_len;
		fixed_length_infrared_nec[i].SendEnSw=0;
		fixed_length_infrared_nec[i].Reading=0;
		fixed_length_infrared_nec[i].Reading_BitCount=0;	
		fixed_length_infrared_nec[i].ReadPtr=0;
		fixed_length_infrared_nec[i].Reading_HighTimerCount=0;
		fixed_length_infrared_nec[i].Reading_LowTimerCount=0;
		fixed_length_infrared_nec[i].Reading_BaseTimerCount=0;
}



/***********************************************************************************************
*函数名 		: void infrared_fixed_length_in_isr(void)
*函数功能描述 	: 单线通讯邓氏接收服务程序(用于数据连续接收和发送)
*函数参数 		: unsigned char *RxReg：串口硬件接收缓存地址指针
*函数返回值 	: 无
***********************************************************************************************/
void infrared_fixed_length_send(unsigned char i,unsigned char writelength)//,unsigned char readlength)
{

	fixed_length_infrared_nec[i].Busy=1;	
	fixed_length_infrared_nec[i].Writing=1;
	fixed_length_infrared_nec[i].Writing_BitCount=0;
	//fixed_length_infrared_nec[i].ReadLength=readlength;
	fixed_length_infrared_nec[i].WriteLength=writelength;
	fixed_length_infrared_nec[i].WritePtr=0;
	fixed_length_infrared_nec[i].SendEnSw=1;
	
	//复位接收变量
	fixed_length_infrared_nec[i].ReadPtr=0;
	fixed_length_infrared_nec[i].Reading=0;
	fixed_length_infrared_nec[i].Reading_BitCount=0;	
	fixed_length_infrared_nec[i].ReadPtr=0;
}


/***********************************************************************************************
*函数名 		: void infrared_fixed_length_in_isr(void)
*函数功能描述 	: 单线通讯邓氏接收服务程序(用于数据连续接收和发送)
*函数参数 		: unsigned char *RxReg：串口硬件接收缓存地址指针
*函数返回值 	: 无
***********************************************************************************************/
void infrared_fixed_length_in_isr(void)
{

infrared_object_select=0;
			//切换为输入并接收电平
			INFRARED_DIO_IN;
			fixed_length_infrared_nec[infrared_object_select].Read_IO=INFRARED_DIO;

	
			//数据位计时
			if(fixed_length_infrared_nec[infrared_object_select].Reading_BaseTimerCount<255) fixed_length_infrared_nec[infrared_object_select].Reading_BaseTimerCount++;
			
			//信号沿处理
			if(fixed_length_infrared_nec[infrared_object_select].Read_IO_Last!=fixed_length_infrared_nec[infrared_object_select].Read_IO)
			{
				
				if(fixed_length_infrared_nec[infrared_object_select].Read_IO==1) //电平上升沿
				{
					//取出低电平时间
					fixed_length_infrared_nec[infrared_object_select].Reading_LowTimerCount=fixed_length_infrared_nec[infrared_object_select].Reading_BaseTimerCount;
					
					//if(fixed_length_infrared_nec[infrared_object_select].Reading_HighTimerCount>200) mof_buzzer_beep(1,2,3);	
				}
				else if(fixed_length_infrared_nec[infrared_object_select].Read_IO==0) //电平下降沿
				{
					//取出高电平时间
					fixed_length_infrared_nec[infrared_object_select].Reading_HighTimerCount=fixed_length_infrared_nec[infrared_object_select].Reading_BaseTimerCount;
				}
				else //信号干扰
				{
					//电平变化计时时基清零
					fixed_length_infrared_nec[infrared_object_select].Reading_BaseTimerCount=0;
					return;
				}
				
				//
				fixed_length_infrared_nec[infrared_object_select].Read_IO_Last=fixed_length_infrared_nec[infrared_object_select].Read_IO;
				
				//电平变化计时时基清零
				fixed_length_infrared_nec[infrared_object_select].Reading_BaseTimerCount=0;
				
			}

			
			//如果前一次接收未处理,停止接收以免缓存区被破坏
			if(fixed_length_infrared_nec[infrared_object_select].Reading==200) return;
			
//			//如果接收已超时,重新开始接收
//			if(fixed_length_infrared_nec[infrared_object_select].ReadTimeout==0) fixed_length_infrared_nec[infrared_object_select].ReadPtr=0;

//			//设置接收超时时间
//			fixed_length_infrared_nec[infrared_object_select].ReadTimeout=3;

			
			//接收流程
			switch(fixed_length_infrared_nec[infrared_object_select].Reading)
			{
					case 0://检测复位帧,1个数据位宽度高电平(实测不到此宽度,待后期验证),2个数据位低电平
					{


							fixed_length_infrared_nec[infrared_object_select].Reading++;
					}
					break;
					case 201:
					case 1://检测起始帧,半个数据位宽度高电平,半个数据位低电平
					{
						if(fixed_length_infrared_nec[infrared_object_select].Reading_BaseTimerCount==0)
						{
								if(fixed_length_infrared_nec[infrared_object_select].Read_IO==0) //电平下降沿
								{
										if(
											((fixed_length_infrared_nec[infrared_object_select].Reading_HighTimerCount <= (IR_NEC_START_HIGH_WIDTH_TIME+5)) && (fixed_length_infrared_nec[infrared_object_select].Reading_HighTimerCount >= (IR_NEC_START_HIGH_WIDTH_TIME-5)))&&
											((fixed_length_infrared_nec[infrared_object_select].Reading_LowTimerCount <= (IR_NEC_START_LOW_WIDTH_TIME+5)) && (fixed_length_infrared_nec[infrared_object_select].Reading_LowTimerCount >= (IR_NEC_START_LOW_WIDTH_TIME-5)))
										)//符合数据起始帧特性
										{
											fixed_length_infrared_nec[infrared_object_select].Reading=2;
											//mof_buzzer_beep(1,2,3);	
										}
										else if(
											((fixed_length_infrared_nec[infrared_object_select].Reading_HighTimerCount <= (IR_NEC_REPEAT_HIGH_WIDTH_TIME+5)) && (fixed_length_infrared_nec[infrared_object_select].Reading_HighTimerCount >= (IR_NEC_REPEAT_HIGH_WIDTH_TIME-5)))&&
											((fixed_length_infrared_nec[infrared_object_select].Reading_LowTimerCount <= (IR_NEC_START_LOW_WIDTH_TIME+5)) && (fixed_length_infrared_nec[infrared_object_select].Reading_LowTimerCount >= (IR_NEC_START_LOW_WIDTH_TIME-5)))
										)//符合重复起始帧特性
										{
											fixed_length_infrared_nec[infrared_object_select].Reading=200;
											//mof_buzzer_beep(1,2,3);	
										}
										else
										{
											fixed_length_infrared_nec[infrared_object_select].Reading=0;
										}
								}
								else //电平上升沿
								{

								}
						}			
									
					}
					break;
					
					case 2://接收数据帧,。
					{

								if(fixed_length_infrared_nec[infrared_object_select].Reading_BaseTimerCount==0)
								{
									if(fixed_length_infrared_nec[infrared_object_select].Read_IO==0) //电平下降沿
									{
										if(\
											((fixed_length_infrared_nec[infrared_object_select].Reading_HighTimerCount <= (IR_NEC_DATA_SHORT_WIDTH_TIME+2)) && (fixed_length_infrared_nec[infrared_object_select].Reading_HighTimerCount >= (IR_NEC_DATA_SHORT_WIDTH_TIME-2)))&&\
											((fixed_length_infrared_nec[infrared_object_select].Reading_LowTimerCount <= (IR_NEC_DATA_SHORT_WIDTH_TIME+2)) && (fixed_length_infrared_nec[infrared_object_select].Reading_LowTimerCount >= (IR_NEC_DATA_SHORT_WIDTH_TIME-2)))\
										)//符合逻辑0数据帧特性
										{
											fixed_length_infrared_nec[infrared_object_select].p_ReadBuffer[fixed_length_infrared_nec[infrared_object_select].ReadPtr]&=~0x80;
										}
										else if(\
											((fixed_length_infrared_nec[infrared_object_select].Reading_HighTimerCount <= (IR_NEC_DATA_LONG_WIDTH_TIME+2)) && (fixed_length_infrared_nec[infrared_object_select].Reading_HighTimerCount >= (IR_NEC_DATA_LONG_WIDTH_TIME-2)))&&\
											((fixed_length_infrared_nec[infrared_object_select].Reading_LowTimerCount <= (IR_NEC_DATA_SHORT_WIDTH_TIME+2)) && (fixed_length_infrared_nec[infrared_object_select].Reading_LowTimerCount >= (IR_NEC_DATA_SHORT_WIDTH_TIME-2)))\
										)//符合逻辑1数据帧特性
										{
											fixed_length_infrared_nec[infrared_object_select].p_ReadBuffer[fixed_length_infrared_nec[infrared_object_select].ReadPtr]|=0x80;
										}
										else //数据帧接收错误
										{
											fixed_length_infrared_nec[infrared_object_select].Reading=0xee;
										}
										
										//准备下次接收
										fixed_length_infrared_nec[infrared_object_select].Reading_BitCount++;
										
										fixed_length_infrared_nec[infrared_object_select].Reading_HighTimerCount=0;
										fixed_length_infrared_nec[infrared_object_select].Reading_LowTimerCount=0;
										fixed_length_infrared_nec[infrared_object_select].Reading_BaseTimerCount=0;
											
										//准备接收下一位或下个字节
										if(fixed_length_infrared_nec[infrared_object_select].Reading_BitCount < 8) //未接收完一个字节
										{
												fixed_length_infrared_nec[infrared_object_select].p_ReadBuffer[fixed_length_infrared_nec[infrared_object_select].ReadPtr] >>=1; //移位后继续接收数据位
										}
										else //已接收完一个字节
										{
												fixed_length_infrared_nec[infrared_object_select].Reading_BitCount = 0;
											
												fixed_length_infrared_nec[infrared_object_select].ReadPtr++; //接收下一个字节

												//接收超过指定长度数据帧(一般为接收缓冲区的上限)
												if(fixed_length_infrared_nec[infrared_object_select].ReadPtr>=(fixed_length_infrared_nec[infrared_object_select].ReadLength)) 
												{		
													fixed_length_infrared_nec[infrared_object_select].Reading=200; //接收完成,停止接收,等待主循环处理数据
													//mof_buzzer_beep(1,2,3);	
												}		

										}
															
									}
									else //电平上升沿
									{

									}
									
								}
								else if(fixed_length_infrared_nec[infrared_object_select].Reading_BaseTimerCount>(IR_NEC_DATA_TIMEOUT_TIME)) //接收超时
								{
									fixed_length_infrared_nec[infrared_object_select].Reading=0xee;
								}					
						
					}
					break;
					
					case 0xee://接收错误
					default: 
					{
							fixed_length_infrared_nec[infrared_object_select].Reading=0;
							fixed_length_infrared_nec[infrared_object_select].Reading_BitCount=0;	
							fixed_length_infrared_nec[infrared_object_select].ReadPtr=0;
							fixed_length_infrared_nec[infrared_object_select].Reading_HighTimerCount=0;
							fixed_length_infrared_nec[infrared_object_select].Reading_LowTimerCount=0;
							fixed_length_infrared_nec[infrared_object_select].Reading_BaseTimerCount=0;
					}
					break;
			}
				
}
