//******************************************************************************
//Copyright(C) 2020-2021 zhejiang zhida dianzikeji Co., Ltd
//�㽭�Ǵ���ӿƼ����޹�˾
//File name:      TM1628.c
//Author:         zzg
//Version:        Ver0.1
//Date:           2021-4-25
//Description:    TM1628����
//History:
//******************************************************************************
//ͷ�ļ�************************************************************************
#include "..\..\..\com_include_drv.h"
//******************************************************************************

mof_fix_length_onewire_deng_t xdata fixed_length_onewire_deng[ONEWIRE_DENG_TOTAL_NUM];
unsigned char xdata onewire_object_select=0;

/*******************************************************************************
  * @brief   check_sum:��У�顣
  * @param   Buf:��ҪУ������ݡ�
             len:���ݳ��ȡ�
  * @retval  unsigned char:У��͵�ֵ��
  * @note    ��
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
*������ 		: void onewrite_fixed_length_in_isr(void)
*������������ 	: ����ͨѶ���Ͻ��շ������(���������������պͷ���)
*�������� 		: unsigned char *RxReg������Ӳ�����ջ����ַָ��
*��������ֵ 	: ��
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
*������ 		: void onewrite_fixed_length_in_isr(void)
*������������ 	: ����ͨѶ���Ͻ��շ������(���������������պͷ���)
*�������� 		: unsigned char *RxReg������Ӳ�����ջ����ַָ��
*��������ֵ 	: ��
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
	
	//��λ���ձ���
	fixed_length_onewire_deng[i].ReadPtr=0;
	fixed_length_onewire_deng[i].Reading=0;
	fixed_length_onewire_deng[i].Reading_BitCount=0;	
	fixed_length_onewire_deng[i].ReadPtr=0;
}


/***********************************************************************************************
*������ 		: void onewrite_fixed_length_in_isr(void)
*������������ 	: ����ͨѶ���Ͻ��շ������(���������������պͷ���)
*�������� 		: unsigned char *RxReg������Ӳ�����ջ����ַָ��
*��������ֵ 	: ��
***********************************************************************************************/
void onewrite_fixed_length_in_isr(void)
{
	for(onewire_object_select=0;onewire_object_select<(ONEWIRE_DENG_TOTAL_NUM);onewire_object_select++)
	{
		if(fixed_length_onewire_deng[onewire_object_select].SendEnSw!=0) //����
		{
			
			fixed_length_onewire_deng[onewire_object_select].Writing_BaseTimerCount++;

			//���ͻ���������
		
					switch(fixed_length_onewire_deng[onewire_object_select].Writing)
					{
						case 1: //���͸�λ֡,1������λ��ȸߵ�ƽ,2������λ�͵�ƽ
						{
								if(fixed_length_onewire_deng[onewire_object_select].Writing_BaseTimerCount < SEND_BIT_WIDTH_TIME) //1������λ��ȸߵ�ƽ
								{
										fixed_length_onewire_deng[onewire_object_select].Write_IO=1;
								}
								else if(fixed_length_onewire_deng[onewire_object_select].Writing_BaseTimerCount < (SEND_BIT_WIDTH_TIME * 3)) //2������λ�͵�ƽ
								{
										fixed_length_onewire_deng[onewire_object_select].Write_IO=0;
								}
								else //��λ֡�������
								{
									fixed_length_onewire_deng[onewire_object_select].Writing_BaseTimerCount = 0;
									
									fixed_length_onewire_deng[onewire_object_select].Writing++;
									
									fixed_length_onewire_deng[onewire_object_select].Write_IO=1;
								}

						}
						break;
					
						case 2://������ʼ֡�������֡��ͬ��,�������λ��ȸߵ�ƽ,�������λ�͵�ƽ
						{
							
								if(fixed_length_onewire_deng[onewire_object_select].Writing_BaseTimerCount < (SEND_BIT_WIDTH_TIME/2)) //�������λ��ȸߵ�ƽ
								{
										fixed_length_onewire_deng[onewire_object_select].Write_IO=1;
								}
								else if(fixed_length_onewire_deng[onewire_object_select].Writing_BaseTimerCount < (SEND_BIT_WIDTH_TIME)) //�������λ�͵�ƽ
								{
										fixed_length_onewire_deng[onewire_object_select].Write_IO=0;
								}
								else //��ʼ֡�������
								{
									fixed_length_onewire_deng[onewire_object_select].Writing_BaseTimerCount = 0;
									
									fixed_length_onewire_deng[onewire_object_select].Writing++;
									
									fixed_length_onewire_deng[onewire_object_select].Write_IO=1;
								}

						}
						break;
							
							case 3://��������֡,
							{
								
								if(fixed_length_onewire_deng[onewire_object_select].Writing_BaseTimerCount < (SEND_BIT_WIDTH_TIME)) //����һ������λδ���
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
								else //һ������λ�������
								{
									
									fixed_length_onewire_deng[onewire_object_select].Writing_BaseTimerCount = 0;
															
									fixed_length_onewire_deng[onewire_object_select].Write_IO=1;
											
									fixed_length_onewire_deng[onewire_object_select].Writing_BitCount++;
											
									if(fixed_length_onewire_deng[onewire_object_select].Writing_BitCount < 8) //δ������һ���ֽ�
									{
											fixed_length_onewire_deng[onewire_object_select].p_WriteBuffer[fixed_length_onewire_deng[onewire_object_select].WritePtr] >>= 1; //��λ�������������λ

									}
									else //�ѷ�����һ���ֽ�
									{
											fixed_length_onewire_deng[onewire_object_select].Writing_BitCount = 0;
										
											fixed_length_onewire_deng[onewire_object_select].WritePtr++; //������һ���ֽ�
											
											if(fixed_length_onewire_deng[onewire_object_select].WritePtr>=fixed_length_onewire_deng[onewire_object_select].WriteLength) //�������ݷ������
											{
												fixed_length_onewire_deng[onewire_object_select].Writing_BaseTimerCount = 0;
												
												fixed_length_onewire_deng[onewire_object_select].Writing++;
												
												fixed_length_onewire_deng[onewire_object_select].Write_IO=1;
											}

									}
											
								}
								
							}
							break;

						case 4://���ͽ���֡������ʼ֡��ͬ��,�������λ��ȸߵ�ƽ,�������λ�͵�ƽ
						{
							
								if(fixed_length_onewire_deng[onewire_object_select].Writing_BaseTimerCount < (SEND_BIT_WIDTH_TIME/2)) //�������λ��ȸߵ�ƽ
								{
										fixed_length_onewire_deng[onewire_object_select].Write_IO=1;
								}
								else if(fixed_length_onewire_deng[onewire_object_select].Writing_BaseTimerCount < (SEND_BIT_WIDTH_TIME)) //�������λ�͵�ƽ
								{
										fixed_length_onewire_deng[onewire_object_select].Write_IO=0;
								}
								else //��ʼ֡�������
								{
									fixed_length_onewire_deng[onewire_object_select].Writing_BaseTimerCount = 0;
									
									fixed_length_onewire_deng[onewire_object_select].Writing++;
									
									fixed_length_onewire_deng[onewire_object_select].Write_IO=0;
								}

						}
						break;        

							
	//					case 5://����������
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
							
							
						default: //��������
						{
							fixed_length_onewire_deng[onewire_object_select].Write_IO=0;
							fixed_length_onewire_deng[onewire_object_select].Busy=0;
							fixed_length_onewire_deng[onewire_object_select].SendEnSw=0;
							//mof_buzzer_beep(1,2,3);	
							//���ͽ����л�Ϊ����
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
					
					//�л�Ϊ��������͵�ƽ
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
		else //����
		{

			//�л�Ϊ���벢���յ�ƽ
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

	
			//����λ��ʱ
			if(fixed_length_onewire_deng[onewire_object_select].Reading_BaseTimerCount<255) fixed_length_onewire_deng[onewire_object_select].Reading_BaseTimerCount++;
			
			//�ź��ش���
			if(fixed_length_onewire_deng[onewire_object_select].Read_IO_Last!=fixed_length_onewire_deng[onewire_object_select].Read_IO)
			{
				
				if(fixed_length_onewire_deng[onewire_object_select].Read_IO==1) //��ƽ������
				{
					//ȡ���͵�ƽʱ��
					fixed_length_onewire_deng[onewire_object_select].Reading_LowTimerCount=fixed_length_onewire_deng[onewire_object_select].Reading_BaseTimerCount;
					
					//if(fixed_length_onewire_deng[onewire_object_select].Reading_HighTimerCount>200) mof_buzzer_beep(1,2,3);	
				}
				else if(fixed_length_onewire_deng[onewire_object_select].Read_IO==0) //��ƽ�½���
				{
					//ȡ���ߵ�ƽʱ��
					fixed_length_onewire_deng[onewire_object_select].Reading_HighTimerCount=fixed_length_onewire_deng[onewire_object_select].Reading_BaseTimerCount;
				}
				else //�źŸ���
				{
					//��ƽ�仯��ʱʱ������
					fixed_length_onewire_deng[onewire_object_select].Reading_BaseTimerCount=0;
					return;
				}
				
				//
				fixed_length_onewire_deng[onewire_object_select].Read_IO_Last=fixed_length_onewire_deng[onewire_object_select].Read_IO;
				
				//��ƽ�仯��ʱʱ������
				fixed_length_onewire_deng[onewire_object_select].Reading_BaseTimerCount=0;
				
			}

			
			//���ǰһ�ν���δ����,ֹͣ�������⻺�������ƻ�
			if(fixed_length_onewire_deng[onewire_object_select].Reading==200) return;
			
//			//��������ѳ�ʱ,���¿�ʼ����
//			if(fixed_length_onewire_deng[onewire_object_select].ReadTimeout==0) fixed_length_onewire_deng[onewire_object_select].ReadPtr=0;

//			//���ý��ճ�ʱʱ��
//			fixed_length_onewire_deng[onewire_object_select].ReadTimeout=3;

			
			//��������
			switch(fixed_length_onewire_deng[onewire_object_select].Reading)
			{
					case 0://��⸴λ֡,1������λ��ȸߵ�ƽ(ʵ�ⲻ���˿��,��������֤),2������λ�͵�ƽ
					{
//						if(fixed_length_onewire_deng[onewire_object_select].Reading_BaseTimerCount==0)
//						{
//								if(fixed_length_onewire_deng[onewire_object_select].Read_IO==1) //��ƽ������
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
//								else //��ƽ�½���
//								{

//								}
//						}

							fixed_length_onewire_deng[onewire_object_select].Reading++;
					}
					break;
					
					case 1://�����ʼ֡,�������λ��ȸߵ�ƽ,�������λ�͵�ƽ
					{
						if(fixed_length_onewire_deng[onewire_object_select].Reading_BaseTimerCount==0)
						{
								if(fixed_length_onewire_deng[onewire_object_select].Read_IO==1) //��ƽ������
								{
										if(
											((fixed_length_onewire_deng[onewire_object_select].Reading_HighTimerCount <= (SEND_MEDIUM_WAVE_TIME+2)) && (fixed_length_onewire_deng[onewire_object_select].Reading_HighTimerCount >= (SEND_MEDIUM_WAVE_TIME-2)))&&
											((fixed_length_onewire_deng[onewire_object_select].Reading_LowTimerCount <= (SEND_MEDIUM_WAVE_TIME+2)) && (fixed_length_onewire_deng[onewire_object_select].Reading_LowTimerCount >= (SEND_MEDIUM_WAVE_TIME-2)))
										)//������ʼ֡����
										{
											fixed_length_onewire_deng[onewire_object_select].Reading++;
											//mof_buzzer_beep(1,2,3);	
										}
										else
										{
											fixed_length_onewire_deng[onewire_object_select].Reading=0;
										}
								}
								else //��ƽ�½���
								{

								}
						}
						
									
					}
					break;
					
					case 2://��������֡,��
					{

								if(fixed_length_onewire_deng[onewire_object_select].Reading_BaseTimerCount==0)
								{
									if(fixed_length_onewire_deng[onewire_object_select].Read_IO==1) //��ƽ������
									{
										if(\
											((fixed_length_onewire_deng[onewire_object_select].Reading_HighTimerCount <= (SEND_SHORT_WAVE_TIME+2)) && (fixed_length_onewire_deng[onewire_object_select].Reading_HighTimerCount >= (SEND_SHORT_WAVE_TIME-2)))&&\
											((fixed_length_onewire_deng[onewire_object_select].Reading_LowTimerCount <= (SEND_LONG_WAVE_TIME+2)) && (fixed_length_onewire_deng[onewire_object_select].Reading_LowTimerCount >= (SEND_LONG_WAVE_TIME-2)))\
										)//�����߼�0����֡����
										{
											fixed_length_onewire_deng[onewire_object_select].p_ReadBuffer[fixed_length_onewire_deng[onewire_object_select].ReadPtr]&=~0x80;
										}
										else if(\
											((fixed_length_onewire_deng[onewire_object_select].Reading_HighTimerCount <= (SEND_LONG_WAVE_TIME+2)) && (fixed_length_onewire_deng[onewire_object_select].Reading_HighTimerCount >= (SEND_LONG_WAVE_TIME-2)))&&\
											((fixed_length_onewire_deng[onewire_object_select].Reading_LowTimerCount <= (SEND_SHORT_WAVE_TIME+2)) && (fixed_length_onewire_deng[onewire_object_select].Reading_LowTimerCount >= (SEND_SHORT_WAVE_TIME-2)))\
										)//�����߼�1����֡����
										{
											fixed_length_onewire_deng[onewire_object_select].p_ReadBuffer[fixed_length_onewire_deng[onewire_object_select].ReadPtr]|=0x80;
										}
										else //����֡���մ���
										{
											fixed_length_onewire_deng[onewire_object_select].Reading=0xee;
										}
										
										//׼���´ν���
										fixed_length_onewire_deng[onewire_object_select].Reading_BitCount++;
										
										fixed_length_onewire_deng[onewire_object_select].Reading_HighTimerCount=0;
										fixed_length_onewire_deng[onewire_object_select].Reading_LowTimerCount=0;
										fixed_length_onewire_deng[onewire_object_select].Reading_BaseTimerCount=0;
											
										//׼��������һλ���¸��ֽ�
										if(fixed_length_onewire_deng[onewire_object_select].Reading_BitCount < 8) //δ������һ���ֽ�
										{
												fixed_length_onewire_deng[onewire_object_select].p_ReadBuffer[fixed_length_onewire_deng[onewire_object_select].ReadPtr] >>=1; //��λ�������������λ
										}
										else //�ѽ�����һ���ֽ�
										{
												fixed_length_onewire_deng[onewire_object_select].Reading_BitCount = 0;
											
												fixed_length_onewire_deng[onewire_object_select].ReadPtr++; //������һ���ֽ�

												//���ճ���ָ����������֡(һ��Ϊ���ջ�����������)
												if(fixed_length_onewire_deng[onewire_object_select].ReadPtr>=(fixed_length_onewire_deng[onewire_object_select].ReadLength)) 
												{		
													fixed_length_onewire_deng[onewire_object_select].Reading=200; //�������,ֹͣ����,�ȴ���ѭ����������
												}		
							

										}
															
									}
									else //��ƽ�½���
									{
										if(\
											((fixed_length_onewire_deng[onewire_object_select].Reading_HighTimerCount <= (SEND_MEDIUM_WAVE_TIME+2)) && (fixed_length_onewire_deng[onewire_object_select].Reading_HighTimerCount >= (SEND_MEDIUM_WAVE_TIME-2)))\
										)//���Ͻ���֡����
										{
											fixed_length_onewire_deng[onewire_object_select].Reading=200; //�������,ֹͣ����,�ȴ���ѭ����������
										}
									}
									
								}
								else if(fixed_length_onewire_deng[onewire_object_select].Reading_BaseTimerCount>(SEND_BIT_WIDTH_TIME+SEND_BIT_WIDTH_TIME+SEND_BIT_WIDTH_TIME+2)) //���ճ�ʱ
								{
									fixed_length_onewire_deng[onewire_object_select].Reading=0xee;
								}					
						
					}
					break;
					
					case 0xee://���մ���
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
