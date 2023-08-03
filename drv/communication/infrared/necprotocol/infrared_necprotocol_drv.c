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

mof_fix_length_infrared_t xdata fixed_length_infrared_nec[1];
unsigned char xdata infrared_object_select=0;


/***********************************************************************************************
*������ 		: void infrared_fixed_length_in_isr(void)
*������������ 	: ����ͨѶ���Ͻ��շ������(���������������պͷ���)
*�������� 		: unsigned char *RxReg������Ӳ�����ջ����ַָ��
*��������ֵ 	: ��
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
*������ 		: void infrared_fixed_length_in_isr(void)
*������������ 	: ����ͨѶ���Ͻ��շ������(���������������պͷ���)
*�������� 		: unsigned char *RxReg������Ӳ�����ջ����ַָ��
*��������ֵ 	: ��
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
	
	//��λ���ձ���
	fixed_length_infrared_nec[i].ReadPtr=0;
	fixed_length_infrared_nec[i].Reading=0;
	fixed_length_infrared_nec[i].Reading_BitCount=0;	
	fixed_length_infrared_nec[i].ReadPtr=0;
}


/***********************************************************************************************
*������ 		: void infrared_fixed_length_in_isr(void)
*������������ 	: ����ͨѶ���Ͻ��շ������(���������������պͷ���)
*�������� 		: unsigned char *RxReg������Ӳ�����ջ����ַָ��
*��������ֵ 	: ��
***********************************************************************************************/
void infrared_fixed_length_in_isr(void)
{

infrared_object_select=0;
			//�л�Ϊ���벢���յ�ƽ
			INFRARED_DIO_IN;
			fixed_length_infrared_nec[infrared_object_select].Read_IO=INFRARED_DIO;

	
			//����λ��ʱ
			if(fixed_length_infrared_nec[infrared_object_select].Reading_BaseTimerCount<255) fixed_length_infrared_nec[infrared_object_select].Reading_BaseTimerCount++;
			
			//�ź��ش���
			if(fixed_length_infrared_nec[infrared_object_select].Read_IO_Last!=fixed_length_infrared_nec[infrared_object_select].Read_IO)
			{
				
				if(fixed_length_infrared_nec[infrared_object_select].Read_IO==1) //��ƽ������
				{
					//ȡ���͵�ƽʱ��
					fixed_length_infrared_nec[infrared_object_select].Reading_LowTimerCount=fixed_length_infrared_nec[infrared_object_select].Reading_BaseTimerCount;
					
					//if(fixed_length_infrared_nec[infrared_object_select].Reading_HighTimerCount>200) mof_buzzer_beep(1,2,3);	
				}
				else if(fixed_length_infrared_nec[infrared_object_select].Read_IO==0) //��ƽ�½���
				{
					//ȡ���ߵ�ƽʱ��
					fixed_length_infrared_nec[infrared_object_select].Reading_HighTimerCount=fixed_length_infrared_nec[infrared_object_select].Reading_BaseTimerCount;
				}
				else //�źŸ���
				{
					//��ƽ�仯��ʱʱ������
					fixed_length_infrared_nec[infrared_object_select].Reading_BaseTimerCount=0;
					return;
				}
				
				//
				fixed_length_infrared_nec[infrared_object_select].Read_IO_Last=fixed_length_infrared_nec[infrared_object_select].Read_IO;
				
				//��ƽ�仯��ʱʱ������
				fixed_length_infrared_nec[infrared_object_select].Reading_BaseTimerCount=0;
				
			}

			
			//���ǰһ�ν���δ����,ֹͣ�������⻺�������ƻ�
			if(fixed_length_infrared_nec[infrared_object_select].Reading==200) return;
			
//			//��������ѳ�ʱ,���¿�ʼ����
//			if(fixed_length_infrared_nec[infrared_object_select].ReadTimeout==0) fixed_length_infrared_nec[infrared_object_select].ReadPtr=0;

//			//���ý��ճ�ʱʱ��
//			fixed_length_infrared_nec[infrared_object_select].ReadTimeout=3;

			
			//��������
			switch(fixed_length_infrared_nec[infrared_object_select].Reading)
			{
					case 0://��⸴λ֡,1������λ��ȸߵ�ƽ(ʵ�ⲻ���˿��,��������֤),2������λ�͵�ƽ
					{


							fixed_length_infrared_nec[infrared_object_select].Reading++;
					}
					break;
					case 201:
					case 1://�����ʼ֡,�������λ��ȸߵ�ƽ,�������λ�͵�ƽ
					{
						if(fixed_length_infrared_nec[infrared_object_select].Reading_BaseTimerCount==0)
						{
								if(fixed_length_infrared_nec[infrared_object_select].Read_IO==0) //��ƽ�½���
								{
										if(
											((fixed_length_infrared_nec[infrared_object_select].Reading_HighTimerCount <= (IR_NEC_START_HIGH_WIDTH_TIME+5)) && (fixed_length_infrared_nec[infrared_object_select].Reading_HighTimerCount >= (IR_NEC_START_HIGH_WIDTH_TIME-5)))&&
											((fixed_length_infrared_nec[infrared_object_select].Reading_LowTimerCount <= (IR_NEC_START_LOW_WIDTH_TIME+5)) && (fixed_length_infrared_nec[infrared_object_select].Reading_LowTimerCount >= (IR_NEC_START_LOW_WIDTH_TIME-5)))
										)//����������ʼ֡����
										{
											fixed_length_infrared_nec[infrared_object_select].Reading=2;
											//mof_buzzer_beep(1,2,3);	
										}
										else if(
											((fixed_length_infrared_nec[infrared_object_select].Reading_HighTimerCount <= (IR_NEC_REPEAT_HIGH_WIDTH_TIME+5)) && (fixed_length_infrared_nec[infrared_object_select].Reading_HighTimerCount >= (IR_NEC_REPEAT_HIGH_WIDTH_TIME-5)))&&
											((fixed_length_infrared_nec[infrared_object_select].Reading_LowTimerCount <= (IR_NEC_START_LOW_WIDTH_TIME+5)) && (fixed_length_infrared_nec[infrared_object_select].Reading_LowTimerCount >= (IR_NEC_START_LOW_WIDTH_TIME-5)))
										)//�����ظ���ʼ֡����
										{
											fixed_length_infrared_nec[infrared_object_select].Reading=200;
											//mof_buzzer_beep(1,2,3);	
										}
										else
										{
											fixed_length_infrared_nec[infrared_object_select].Reading=0;
										}
								}
								else //��ƽ������
								{

								}
						}			
									
					}
					break;
					
					case 2://��������֡,��
					{

								if(fixed_length_infrared_nec[infrared_object_select].Reading_BaseTimerCount==0)
								{
									if(fixed_length_infrared_nec[infrared_object_select].Read_IO==0) //��ƽ�½���
									{
										if(\
											((fixed_length_infrared_nec[infrared_object_select].Reading_HighTimerCount <= (IR_NEC_DATA_SHORT_WIDTH_TIME+2)) && (fixed_length_infrared_nec[infrared_object_select].Reading_HighTimerCount >= (IR_NEC_DATA_SHORT_WIDTH_TIME-2)))&&\
											((fixed_length_infrared_nec[infrared_object_select].Reading_LowTimerCount <= (IR_NEC_DATA_SHORT_WIDTH_TIME+2)) && (fixed_length_infrared_nec[infrared_object_select].Reading_LowTimerCount >= (IR_NEC_DATA_SHORT_WIDTH_TIME-2)))\
										)//�����߼�0����֡����
										{
											fixed_length_infrared_nec[infrared_object_select].p_ReadBuffer[fixed_length_infrared_nec[infrared_object_select].ReadPtr]&=~0x80;
										}
										else if(\
											((fixed_length_infrared_nec[infrared_object_select].Reading_HighTimerCount <= (IR_NEC_DATA_LONG_WIDTH_TIME+2)) && (fixed_length_infrared_nec[infrared_object_select].Reading_HighTimerCount >= (IR_NEC_DATA_LONG_WIDTH_TIME-2)))&&\
											((fixed_length_infrared_nec[infrared_object_select].Reading_LowTimerCount <= (IR_NEC_DATA_SHORT_WIDTH_TIME+2)) && (fixed_length_infrared_nec[infrared_object_select].Reading_LowTimerCount >= (IR_NEC_DATA_SHORT_WIDTH_TIME-2)))\
										)//�����߼�1����֡����
										{
											fixed_length_infrared_nec[infrared_object_select].p_ReadBuffer[fixed_length_infrared_nec[infrared_object_select].ReadPtr]|=0x80;
										}
										else //����֡���մ���
										{
											fixed_length_infrared_nec[infrared_object_select].Reading=0xee;
										}
										
										//׼���´ν���
										fixed_length_infrared_nec[infrared_object_select].Reading_BitCount++;
										
										fixed_length_infrared_nec[infrared_object_select].Reading_HighTimerCount=0;
										fixed_length_infrared_nec[infrared_object_select].Reading_LowTimerCount=0;
										fixed_length_infrared_nec[infrared_object_select].Reading_BaseTimerCount=0;
											
										//׼��������һλ���¸��ֽ�
										if(fixed_length_infrared_nec[infrared_object_select].Reading_BitCount < 8) //δ������һ���ֽ�
										{
												fixed_length_infrared_nec[infrared_object_select].p_ReadBuffer[fixed_length_infrared_nec[infrared_object_select].ReadPtr] >>=1; //��λ�������������λ
										}
										else //�ѽ�����һ���ֽ�
										{
												fixed_length_infrared_nec[infrared_object_select].Reading_BitCount = 0;
											
												fixed_length_infrared_nec[infrared_object_select].ReadPtr++; //������һ���ֽ�

												//���ճ���ָ����������֡(һ��Ϊ���ջ�����������)
												if(fixed_length_infrared_nec[infrared_object_select].ReadPtr>=(fixed_length_infrared_nec[infrared_object_select].ReadLength)) 
												{		
													fixed_length_infrared_nec[infrared_object_select].Reading=200; //�������,ֹͣ����,�ȴ���ѭ����������
													//mof_buzzer_beep(1,2,3);	
												}		

										}
															
									}
									else //��ƽ������
									{

									}
									
								}
								else if(fixed_length_infrared_nec[infrared_object_select].Reading_BaseTimerCount>(IR_NEC_DATA_TIMEOUT_TIME)) //���ճ�ʱ
								{
									fixed_length_infrared_nec[infrared_object_select].Reading=0xee;
								}					
						
					}
					break;
					
					case 0xee://���մ���
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
