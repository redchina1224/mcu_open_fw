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

mof_fix_length_onewire_deng_t xdata fixed_length_onewire_deng[ONEWIRE_DENG_TOTAL_NUM];
unsigned char xdata onewire_object_select=0;

/*******************************************************************************
  * @brief   check_sum:和校验。
  * @param   Buf:需要校验的数据。
             len:数据长度。
  * @retval  unsigned char:校验和的值。
  * @note    无
*******************************************************************************/
static unsigned char check_sum(unsigned char* Buf, unsigned char len)
{
    unsigned char i_t = 0;
    unsigned char Sum = 0;

    for(i_t = 0; i_t < len; i_t++)
    {
        Sum += Buf[i_t];
    }

    return Sum;
}

/***********************************************************************************************
*函数名 		: void onewrite_fixed_length_in_isr(void)
*函数功能描述 	: 单线通讯邓氏接收服务程序(用于数据连续接收和发送)
*函数参数 		: unsigned char *RxReg：串口硬件接收缓存地址指针
*函数返回值 	: 无
***********************************************************************************************/
void onewrite_fixed_length_init(unsigned char i,unsigned char *sendbuf,unsigned char *recvbuf,unsigned char recv_len)
{
		fixed_length_onewire_deng[i].p_WriteBuffer=(sendbuf);
		fixed_length_onewire_deng[i].p_ReadBuffer=(recvbuf);
		fixed_length_onewire_deng[i].ReadLength=recv_len;
		fixed_length_onewire_deng[i].SendEnSw=0;
		fixed_length_onewire_deng[i].Reading=0;
		fixed_length_onewire_deng[i].Reading_BitCount=0;	
		fixed_length_onewire_deng[i].ReadPtr=0;
		fixed_length_onewire_deng[i].Reading_HighTimerCount=0;
		fixed_length_onewire_deng[i].Reading_LowTimerCount=0;
		fixed_length_onewire_deng[i].Reading_BaseTimerCount=0;
}



/***********************************************************************************************
*函数名 		: void onewrite_fixed_length_in_isr(void)
*函数功能描述 	: 单线通讯邓氏接收服务程序(用于数据连续接收和发送)
*函数参数 		: unsigned char *RxReg：串口硬件接收缓存地址指针
*函数返回值 	: 无
***********************************************************************************************/
void onewrite_fixed_length_send(unsigned char i,unsigned char writelength)//,unsigned char readlength)
{

	fixed_length_onewire_deng[i].Busy=1;	
	fixed_length_onewire_deng[i].Writing=1;
	fixed_length_onewire_deng[i].Writing_BitCount=0;
	//fixed_length_onewire_deng[i].ReadLength=readlength;
	fixed_length_onewire_deng[i].WriteLength=writelength;
	fixed_length_onewire_deng[i].WritePtr=0;
	fixed_length_onewire_deng[i].SendEnSw=1;
	
	//复位接收变量
	fixed_length_onewire_deng[i].ReadPtr=0;
	fixed_length_onewire_deng[i].Reading=0;
	fixed_length_onewire_deng[i].Reading_BitCount=0;	
	fixed_length_onewire_deng[i].ReadPtr=0;
}


/***********************************************************************************************
*函数名 		: void onewrite_fixed_length_in_isr(void)
*函数功能描述 	: 单线通讯邓氏接收服务程序(用于数据连续接收和发送)
*函数参数 		: unsigned char *RxReg：串口硬件接收缓存地址指针
*函数返回值 	: 无
***********************************************************************************************/
void onewrite_fixed_length_in_isr(void)
{
	for(onewire_object_select=0;onewire_object_select<(ONEWIRE_DENG_TOTAL_NUM);onewire_object_select++)
	{
		if(fixed_length_onewire_deng[onewire_object_select].SendEnSw!=0) //发送
		{
			
			fixed_length_onewire_deng[onewire_object_select].Writing_BaseTimerCount++;

			//发送缓存区数据
		
					switch(fixed_length_onewire_deng[onewire_object_select].Writing)
					{
						case 1: //发送复位帧,1个数据位宽度高电平,2个数据位低电平
						{
								if(fixed_length_onewire_deng[onewire_object_select].Writing_BaseTimerCount < SEND_BIT_WIDTH_TIME) //1个数据位宽度高电平
								{
										fixed_length_onewire_deng[onewire_object_select].Write_IO=1;
								}
								else if(fixed_length_onewire_deng[onewire_object_select].Writing_BaseTimerCount < (SEND_BIT_WIDTH_TIME * 3)) //2个数据位低电平
								{
										fixed_length_onewire_deng[onewire_object_select].Write_IO=0;
								}
								else //复位帧发送完成
								{
									fixed_length_onewire_deng[onewire_object_select].Writing_BaseTimerCount = 0;
									
									fixed_length_onewire_deng[onewire_object_select].Writing++;
									
									fixed_length_onewire_deng[onewire_object_select].Write_IO=1;
								}

						}
						break;
					
						case 2://发送起始帧（与结束帧相同）,半个数据位宽度高电平,半个数据位低电平
						{
							
								if(fixed_length_onewire_deng[onewire_object_select].Writing_BaseTimerCount < (SEND_BIT_WIDTH_TIME/2)) //半个数据位宽度高电平
								{
										fixed_length_onewire_deng[onewire_object_select].Write_IO=1;
								}
								else if(fixed_length_onewire_deng[onewire_object_select].Writing_BaseTimerCount < (SEND_BIT_WIDTH_TIME)) //半个数据位低电平
								{
										fixed_length_onewire_deng[onewire_object_select].Write_IO=0;
								}
								else //起始帧发送完成
								{
									fixed_length_onewire_deng[onewire_object_select].Writing_BaseTimerCount = 0;
									
									fixed_length_onewire_deng[onewire_object_select].Writing++;
									
									fixed_length_onewire_deng[onewire_object_select].Write_IO=1;
								}

						}
						break;
							
							case 3://发送数据帧,
							{
								
								if(fixed_length_onewire_deng[onewire_object_select].Writing_BaseTimerCount < (SEND_BIT_WIDTH_TIME)) //发送一个数据位未完成
								{
											if(fixed_length_onewire_deng[onewire_object_select].p_WriteBuffer[fixed_length_onewire_deng[onewire_object_select].WritePtr] & 0x01)
											{
													if(fixed_length_onewire_deng[onewire_object_select].Writing_BaseTimerCount < SEND_LONG_WAVE_TIME)
															fixed_length_onewire_deng[onewire_object_select].Write_IO=1;
													else
															fixed_length_onewire_deng[onewire_object_select].Write_IO=0;
											}
											else
											{
													if(fixed_length_onewire_deng[onewire_object_select].Writing_BaseTimerCount < SEND_SHORT_WAVE_TIME)
															fixed_length_onewire_deng[onewire_object_select].Write_IO=1;
													else
															fixed_length_onewire_deng[onewire_object_select].Write_IO=0;
											}
								}
								else //一个数据位发送完成
								{
									
									fixed_length_onewire_deng[onewire_object_select].Writing_BaseTimerCount = 0;
															
									fixed_length_onewire_deng[onewire_object_select].Write_IO=1;
											
									fixed_length_onewire_deng[onewire_object_select].Writing_BitCount++;
											
									if(fixed_length_onewire_deng[onewire_object_select].Writing_BitCount < 8) //未发送完一个字节
									{
											fixed_length_onewire_deng[onewire_object_select].p_WriteBuffer[fixed_length_onewire_deng[onewire_object_select].WritePtr] >>= 1; //移位后继续发送数据位

									}
									else //已发送完一个字节
									{
											fixed_length_onewire_deng[onewire_object_select].Writing_BitCount = 0;
										
											fixed_length_onewire_deng[onewire_object_select].WritePtr++; //发送下一个字节
											
											if(fixed_length_onewire_deng[onewire_object_select].WritePtr>=fixed_length_onewire_deng[onewire_object_select].WriteLength) //所有数据发送完成
											{
												fixed_length_onewire_deng[onewire_object_select].Writing_BaseTimerCount = 0;
												
												fixed_length_onewire_deng[onewire_object_select].Writing++;
												
												fixed_length_onewire_deng[onewire_object_select].Write_IO=1;
											}

									}
											
								}
								
							}
							break;

						case 4://发送结束帧（与起始帧相同）,半个数据位宽度高电平,半个数据位低电平
						{
							
								if(fixed_length_onewire_deng[onewire_object_select].Writing_BaseTimerCount < (SEND_BIT_WIDTH_TIME/2)) //半个数据位宽度高电平
								{
										fixed_length_onewire_deng[onewire_object_select].Write_IO=1;
								}
								else if(fixed_length_onewire_deng[onewire_object_select].Writing_BaseTimerCount < (SEND_BIT_WIDTH_TIME)) //半个数据位低电平
								{
										fixed_length_onewire_deng[onewire_object_select].Write_IO=0;
								}
								else //起始帧发送完成
								{
									fixed_length_onewire_deng[onewire_object_select].Writing_BaseTimerCount = 0;
									
									fixed_length_onewire_deng[onewire_object_select].Writing++;
									
									fixed_length_onewire_deng[onewire_object_select].Write_IO=0;
								}

						}
						break;        

							
	//					case 5://发送死区。
	//					{
	//							if(fixed_length_onewire_deng[onewire_object_select].Writing_BaseTimerCount > SEND_DEAD_ZREA_TIME)
	//							{
	//								fixed_length_onewire_deng[onewire_object_select].Writing_BaseTimerCount = 0;
	//								
	//								fixed_length_onewire_deng[onewire_object_select].Writing++;
	//								
	//								fixed_length_onewire_deng[onewire_object_select].Write_IO=0;
	//							}
	//							else
	//							{
	//								fixed_length_onewire_deng[onewire_object_select].Write_IO=0;
	//							}
	//					}
	//					break;
							
							
						default: //结束发送
						{
							fixed_length_onewire_deng[onewire_object_select].Write_IO=0;
							fixed_length_onewire_deng[onewire_object_select].Busy=0;
							fixed_length_onewire_deng[onewire_object_select].SendEnSw=0;
							//mof_buzzer_beep(1,2,3);	
							//发送结束切换为输入
							if(onewire_object_select==0)
							{
								ONEWIRE_DIO_IN;
							}
		#if (ONEWIRE_DENG_TOTAL_NUM>1)
							else if(onewire_object_select==1)
							{
								ONEWIRE2_DIO_IN;
							}	
		#endif

						}
						break;
					}
					
					//切换为输出并发送电平
					if(fixed_length_onewire_deng[onewire_object_select].SendEnSw)
					{
						if(onewire_object_select==0)
						{
							ONEWIRE_DIO=fixed_length_onewire_deng[onewire_object_select].Write_IO;
							ONEWIRE_DIO_OUT;
						}
		#if (ONEWIRE_DENG_TOTAL_NUM>1)
						else if(onewire_object_select==1)
						{
							ONEWIRE2_DIO=fixed_length_onewire_deng[onewire_object_select].Write_IO;
							ONEWIRE2_DIO_OUT;
						}
		#endif

					}

					
		}
		else //接收
		{

			//切换为输入并接收电平
			if(onewire_object_select==0)
			{
				ONEWIRE_DIO_IN;
				fixed_length_onewire_deng[onewire_object_select].Read_IO=ONEWIRE_DIO;
			}
#if (ONEWIRE_DENG_TOTAL_NUM>1)
			else if(onewire_object_select==1)
			{
				ONEWIRE2_DIO_IN;
				fixed_length_onewire_deng[onewire_object_select].Read_IO=ONEWIRE2_DIO;
			}
#endif

	
			//数据位计时
			if(fixed_length_onewire_deng[onewire_object_select].Reading_BaseTimerCount<255) fixed_length_onewire_deng[onewire_object_select].Reading_BaseTimerCount++;
			
			//信号沿处理
			if(fixed_length_onewire_deng[onewire_object_select].Read_IO_Last!=fixed_length_onewire_deng[onewire_object_select].Read_IO)
			{
				
				if(fixed_length_onewire_deng[onewire_object_select].Read_IO==1) //电平上升沿
				{
					//取出低电平时间
					fixed_length_onewire_deng[onewire_object_select].Reading_LowTimerCount=fixed_length_onewire_deng[onewire_object_select].Reading_BaseTimerCount;
					
					//if(fixed_length_onewire_deng[onewire_object_select].Reading_HighTimerCount>200) mof_buzzer_beep(1,2,3);	
				}
				else if(fixed_length_onewire_deng[onewire_object_select].Read_IO==0) //电平下降沿
				{
					//取出高电平时间
					fixed_length_onewire_deng[onewire_object_select].Reading_HighTimerCount=fixed_length_onewire_deng[onewire_object_select].Reading_BaseTimerCount;
				}
				else //信号干扰
				{
					//电平变化计时时基清零
					fixed_length_onewire_deng[onewire_object_select].Reading_BaseTimerCount=0;
					return;
				}
				
				//
				fixed_length_onewire_deng[onewire_object_select].Read_IO_Last=fixed_length_onewire_deng[onewire_object_select].Read_IO;
				
				//电平变化计时时基清零
				fixed_length_onewire_deng[onewire_object_select].Reading_BaseTimerCount=0;
				
			}

			
			//如果前一次接收未处理,停止接收以免缓存区被破坏
			if(fixed_length_onewire_deng[onewire_object_select].Reading==200) return;
			
//			//如果接收已超时,重新开始接收
//			if(fixed_length_onewire_deng[onewire_object_select].ReadTimeout==0) fixed_length_onewire_deng[onewire_object_select].ReadPtr=0;

//			//设置接收超时时间
//			fixed_length_onewire_deng[onewire_object_select].ReadTimeout=3;

			
			//接收流程
			switch(fixed_length_onewire_deng[onewire_object_select].Reading)
			{
					case 0://检测复位帧,1个数据位宽度高电平(实测不到此宽度,待后期验证),2个数据位低电平
					{
//						if(fixed_length_onewire_deng[onewire_object_select].Reading_BaseTimerCount==0)
//						{
//								if(fixed_length_onewire_deng[onewire_object_select].Read_IO==1) //电平上升沿
//								{
//										if(
//											fixed_length_onewire_deng[onewire_object_select].Reading_HighTimerCount>=(10)&&fixed_length_onewire_deng[onewire_object_select].Reading_HighTimerCount<=(22)&&
//											fixed_length_onewire_deng[onewire_object_select].Reading_LowTimerCount>=(SEND_BIT_WIDTH_TIME+SEND_BIT_WIDTH_TIME-2)&&fixed_length_onewire_deng[onewire_object_select].Reading_LowTimerCount<=(SEND_BIT_WIDTH_TIME+SEND_BIT_WIDTH_TIME+2)
//										)
//										{
//											fixed_length_onewire_deng[onewire_object_select].Reading++;
//											//mof_buzzer_beep(1,2,3);	
//										}
//										else
//										{
//											fixed_length_onewire_deng[onewire_object_select].Reading=0;
//										}

//								}
//								else //电平下降沿
//								{

//								}
//						}

							fixed_length_onewire_deng[onewire_object_select].Reading++;
					}
					break;
					
					case 1://检测起始帧,半个数据位宽度高电平,半个数据位低电平
					{
						if(fixed_length_onewire_deng[onewire_object_select].Reading_BaseTimerCount==0)
						{
								if(fixed_length_onewire_deng[onewire_object_select].Read_IO==1) //电平上升沿
								{
										if(
											((fixed_length_onewire_deng[onewire_object_select].Reading_HighTimerCount <= (SEND_MEDIUM_WAVE_TIME+2)) && (fixed_length_onewire_deng[onewire_object_select].Reading_HighTimerCount >= (SEND_MEDIUM_WAVE_TIME-2)))&&
											((fixed_length_onewire_deng[onewire_object_select].Reading_LowTimerCount <= (SEND_MEDIUM_WAVE_TIME+2)) && (fixed_length_onewire_deng[onewire_object_select].Reading_LowTimerCount >= (SEND_MEDIUM_WAVE_TIME-2)))
										)//符合起始帧特性
										{
											fixed_length_onewire_deng[onewire_object_select].Reading++;
											//mof_buzzer_beep(1,2,3);	
										}
										else
										{
											fixed_length_onewire_deng[onewire_object_select].Reading=0;
										}
								}
								else //电平下降沿
								{

								}
						}
						
									
					}
					break;
					
					case 2://接收数据帧,。
					{

								if(fixed_length_onewire_deng[onewire_object_select].Reading_BaseTimerCount==0)
								{
									if(fixed_length_onewire_deng[onewire_object_select].Read_IO==1) //电平上升沿
									{
										if(\
											((fixed_length_onewire_deng[onewire_object_select].Reading_HighTimerCount <= (SEND_SHORT_WAVE_TIME+2)) && (fixed_length_onewire_deng[onewire_object_select].Reading_HighTimerCount >= (SEND_SHORT_WAVE_TIME-2)))&&\
											((fixed_length_onewire_deng[onewire_object_select].Reading_LowTimerCount <= (SEND_LONG_WAVE_TIME+2)) && (fixed_length_onewire_deng[onewire_object_select].Reading_LowTimerCount >= (SEND_LONG_WAVE_TIME-2)))\
										)//符合逻辑0数据帧特性
										{
											fixed_length_onewire_deng[onewire_object_select].p_ReadBuffer[fixed_length_onewire_deng[onewire_object_select].ReadPtr]&=~0x80;
										}
										else if(\
											((fixed_length_onewire_deng[onewire_object_select].Reading_HighTimerCount <= (SEND_LONG_WAVE_TIME+2)) && (fixed_length_onewire_deng[onewire_object_select].Reading_HighTimerCount >= (SEND_LONG_WAVE_TIME-2)))&&\
											((fixed_length_onewire_deng[onewire_object_select].Reading_LowTimerCount <= (SEND_SHORT_WAVE_TIME+2)) && (fixed_length_onewire_deng[onewire_object_select].Reading_LowTimerCount >= (SEND_SHORT_WAVE_TIME-2)))\
										)//符合逻辑1数据帧特性
										{
											fixed_length_onewire_deng[onewire_object_select].p_ReadBuffer[fixed_length_onewire_deng[onewire_object_select].ReadPtr]|=0x80;
										}
										else //数据帧接收错误
										{
											fixed_length_onewire_deng[onewire_object_select].Reading=0xee;
										}
										
										//准备下次接收
										fixed_length_onewire_deng[onewire_object_select].Reading_BitCount++;
										
										fixed_length_onewire_deng[onewire_object_select].Reading_HighTimerCount=0;
										fixed_length_onewire_deng[onewire_object_select].Reading_LowTimerCount=0;
										fixed_length_onewire_deng[onewire_object_select].Reading_BaseTimerCount=0;
											
										//准备接收下一位或下个字节
										if(fixed_length_onewire_deng[onewire_object_select].Reading_BitCount < 8) //未接收完一个字节
										{
												fixed_length_onewire_deng[onewire_object_select].p_ReadBuffer[fixed_length_onewire_deng[onewire_object_select].ReadPtr] >>=1; //移位后继续接收数据位
										}
										else //已接收完一个字节
										{
												fixed_length_onewire_deng[onewire_object_select].Reading_BitCount = 0;
											
												fixed_length_onewire_deng[onewire_object_select].ReadPtr++; //接收下一个字节

												//接收超过指定长度数据帧(一般为接收缓冲区的上限)
												if(fixed_length_onewire_deng[onewire_object_select].ReadPtr>=(fixed_length_onewire_deng[onewire_object_select].ReadLength)) 
												{		
													fixed_length_onewire_deng[onewire_object_select].Reading=200; //接收完成,停止接收,等待主循环处理数据
												}		
							

										}
															
									}
									else //电平下降沿
									{
										if(\
											((fixed_length_onewire_deng[onewire_object_select].Reading_HighTimerCount <= (SEND_MEDIUM_WAVE_TIME+2)) && (fixed_length_onewire_deng[onewire_object_select].Reading_HighTimerCount >= (SEND_MEDIUM_WAVE_TIME-2)))\
										)//符合结束帧特性
										{
											fixed_length_onewire_deng[onewire_object_select].Reading=200; //接收完成,停止接收,等待主循环处理数据
										}
									}
									
								}
								else if(fixed_length_onewire_deng[onewire_object_select].Reading_BaseTimerCount>(SEND_BIT_WIDTH_TIME+SEND_BIT_WIDTH_TIME+SEND_BIT_WIDTH_TIME+2)) //接收超时
								{
									fixed_length_onewire_deng[onewire_object_select].Reading=0xee;
								}					
						
					}
					break;
					
					case 0xee://接收错误
					default: 
					{
							fixed_length_onewire_deng[onewire_object_select].Reading=0;
							fixed_length_onewire_deng[onewire_object_select].Reading_BitCount=0;	
							fixed_length_onewire_deng[onewire_object_select].ReadPtr=0;
							fixed_length_onewire_deng[onewire_object_select].Reading_HighTimerCount=0;
							fixed_length_onewire_deng[onewire_object_select].Reading_LowTimerCount=0;
							fixed_length_onewire_deng[onewire_object_select].Reading_BaseTimerCount=0;
					}
					break;
			}
			
		}
		

	}

	
}
