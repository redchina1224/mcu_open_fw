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

volatile unsigned char comm_direction_flag = 0;//0:���գ�1�����͡�

volatile unsigned char send_data_flag = 0;//���ͱ�־λ��
volatile unsigned char send_data_buff[SEND_DATA_SIZE]; //�����͵����ݡ�

volatile unsigned char receive_data_flag = 0; //���ձ�־λ��
volatile unsigned char receive_data_buff[RECEIVE_DATA_SIZE]; //���յ�����

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

/*******************************************************************************
  * @brief   send_mode:���óɷ���ģʽ��
  * @param   �ޡ�
  * @retval  �ޡ�
  * @note    ��
*******************************************************************************/
void send_mode(void)
{
	P04F = 0x02;
	P04C = 0x00;
	
    comm_direction_flag = 1;
}

/*******************************************************************************
  * @brief   receive_mode:���óɽ���ģʽ��
  * @param   �ޡ�
  * @retval  �ޡ�
  * @note    ��
*******************************************************************************/
void receive_mode(void)
{
	P04F = 0x01;
	P04C = 0x00;
	
    comm_direction_flag = 0;
}


/*******************************************************************************
  * @brief   Comm_Send1:�������ݡ�
  * @param   �ޡ�
  * @retval  �ޡ�
  * @note    ���50us����һ�Σ�CPU��16MHz�������ִ��һ�Σ�ƽ��3.75us,���5us,��С3.125us��
*******************************************************************************/
void send_data(void)
{
    unsigned char i_t = 0;
    static 	unsigned char send_data_time = 0;//����ʱ�������
    static  unsigned char send_data_temp[SEND_DATA_SIZE + 1]; //�ݴ����ݡ�
    static	unsigned char send_data_bit_count = 0;//���㷢�͵�λ����
    static	unsigned char send_data_byte_count = 0;//���㷢�͵��ֽ�����
    static  unsigned char send_data_count = 0;//���㷢�͵Ĵ�����
    static 	unsigned char send_data_state = 0;
    
    send_data_time++;
    
    switch(send_data_state) 
    {
        case 0://����Ƿ��д������ݡ�
        {
            if(send_data_flag != 0)
            {
                //������ݡ�
                for(i_t = 0; i_t < SEND_DATA_SIZE; i_t++)
                    send_data_temp[i_t] = send_data_buff[i_t];
                
                //���У�����ݡ�
                send_data_temp[SEND_DATA_SIZE] = check_sum((unsigned char*)send_data_buff, SEND_DATA_SIZE);
                
                //��ʼ�������ݡ�
                SEND_DATA_HIGH;
                send_data_time = 0;
                send_data_state = 6;
            }
            else
            {
                SEND_DATA_LOW;
            }
        }
        break;
        
		
		
		case 6:
		{
			if(send_data_time > (SEND_BIT_WIDTH_TIME * 3 - 1))
            {
                SEND_DATA_HIGH;
                send_data_time = 0;
                send_data_state = 1;
            }
            else
            {
                if(send_data_time < SEND_BIT_WIDTH_TIME)
                    SEND_DATA_HIGH;
                else
                    SEND_DATA_LOW;
            }	
		}
		break;
		
        case 1://����ǰ���롣
        {
            if(send_data_time > (SEND_BIT_WIDTH_TIME - 1))
            {
                SEND_DATA_HIGH;
                send_data_time = 0;
                send_data_state = 2;
            }
            else
            {
                if(send_data_time < SEND_MEDIUM_WAVE_TIME)
                    SEND_DATA_HIGH;
                else
                    SEND_DATA_LOW;
            }
        }
        break;
        
        case 2://��������֡��
        {
            if(send_data_time > (SEND_BIT_WIDTH_TIME - 1))
            {
                send_data_time = 0;
                SEND_DATA_HIGH;
                
                send_data_temp[send_data_byte_count] >>= 1;
                send_data_bit_count++;
                
                if(send_data_bit_count >= 8)
                {
                    send_data_bit_count = 0;
                    send_data_byte_count++;
                    
                    if(send_data_byte_count >= SEND_DATA_SIZE + 1)
                    {
                        send_data_byte_count = 0;
                        send_data_state = 3;
                    }
                }
                
            }
            else
            {
                if(send_data_temp[send_data_byte_count] & 0x01)
                {
                    if(send_data_time < SEND_LONG_WAVE_TIME)
                        SEND_DATA_HIGH;
                    else
                        SEND_DATA_LOW;
                }
                else
                {
                    if(send_data_time < SEND_SHORT_WAVE_TIME)
                        SEND_DATA_HIGH;
                    else
                        SEND_DATA_LOW;
                }
            }
        }
        break;
        
        case 3://���ͽ�������
        {
            if(send_data_time > (SEND_BIT_WIDTH_TIME - 1))
            {
                SEND_DATA_LOW;
                send_data_time = 0;
                send_data_state = 4;
            }
            else
            {
                if(send_data_time < SEND_MEDIUM_WAVE_TIME)
                    SEND_DATA_HIGH;
                else
                    SEND_DATA_LOW;
            }
        }
        break;
        
        case 4://����������
        {
            if(send_data_time > SEND_DEAD_ZREA_TIME)
            {
                send_data_time = 0;
                
                send_data_count++;
                
                if(send_data_count >= SEND_DATA_COUNT)
                {
                    send_data_count = 0;
                    send_data_state = 5;
                }
                else
                {
                    send_data_state = 0;
                }
            }
            else
            {
                SEND_DATA_LOW;
            }
        }
        break;
        
        case 5://�������͡�
        {
            send_data_flag = 0;
            send_data_state = 0;
        }
        break;
        
        default:
        {
            send_data_state = 5;
        }
        break;
    }
}

/*******************************************************************************
  * @brief   receive_data:�������ݡ�
  * @param   �ޡ�
  * @retval  �ޡ�
  * @note    ���50us����һ��,CPU��16MHz�������ִ��һ�Σ�ƽ��3.5us,���7.5us,��С3.125us����
*******************************************************************************/
void receive_data(void)
{
    unsigned char i_t = 0;
    static 	unsigned char high_count = 0, low_count = 0;//�ߵ͵�ƽ������
    static 	unsigned char high_flag = 0,  low_flag  = 0;//�ߵ͵�ƽ���ࡣ       
    static  unsigned char receive_data_time = 0;//����ʱ�������
    static  unsigned char receive_data_temp[RECEIVE_DATA_SIZE + 1]; //�ݴ����ݡ�
    static  unsigned char receive_data_frame_flag = 0;//
    static 	unsigned char receive_data_bit_flag = 0;//����λ�����ࡣ
    static	unsigned char receive_data_byte_count = 0;//������յ�λ����
    static	unsigned char receive_data_bit_count = 0;//������յ��ֽ�����
    static 	unsigned char receive_data_state = 0;
    
    receive_data_time++;
    
    switch(receive_data_state)
    {
        case 0://ѭ�����ߵ�ƽ��
        {
            if((RECEIVE_DATA_READ != 0) && (RECEIVE_DATA_READ != 0))
            {
                receive_data_time = 0;
                receive_data_state = 1;
            }
        }
        break;
        
        case 1://���ߵ�ƽ���ࡣ
        {
            if(receive_data_time > RECEIVE_TIME_OUT)
            {
                receive_data_state = 6;//���մ���
            }
            else if((RECEIVE_DATA_READ == 0) && (RECEIVE_DATA_READ == 0))
            {
                high_count = receive_data_time;
                receive_data_time = 0;
                
                if((high_count <= RECEIVE_MAX_SHORT_WAVE_TIME) && (high_count >= RECEIVE_MIN_SHORT_WAVE_TIME))
                    high_flag = 1;
                else if((high_count <= RECEIVE_MAX_MEDIUM_WAVE_TIME) && (high_count >= RECEIVE_MIN_MEDIUM_WAVE_TIME))
                    high_flag = 2;
                else if((high_count <= RECEIVE_MAX_LONG_WAVE_TIME) && (high_count >= RECEIVE_MIN_LONG_WAVE_TIME))
                    high_flag = 3;
                else
                    high_flag = 0;

                receive_data_state = 2;
            }
            else
            {
                //����С�
            }
                
        }
        break;
        
        case 2://���͵�ƽ���ࡣ
        {
            if(receive_data_time > RECEIVE_TIME_OUT)
            {
                receive_data_state = 6;//���մ���
            }
            else if((RECEIVE_DATA_READ != 0) && (RECEIVE_DATA_READ != 0))
            {
                low_count = receive_data_time;
                receive_data_time = 0;
                
                if((low_count <= RECEIVE_MAX_SHORT_WAVE_TIME) && (low_count >= RECEIVE_MIN_SHORT_WAVE_TIME))
                    low_flag = 1;
                else if((low_count <= RECEIVE_MAX_MEDIUM_WAVE_TIME) && (low_count >= RECEIVE_MIN_MEDIUM_WAVE_TIME))
                    low_flag = 2;
                else if((low_count <= RECEIVE_MAX_LONG_WAVE_TIME) && (low_count >= RECEIVE_MIN_LONG_WAVE_TIME))
                    low_flag = 3;
                else
                    low_flag = 0;

                receive_data_state = 3;
            }
            else
            {
                //����С�
            }
        }
        break;
        
        case 3://��������һλ���ݡ�
        {
            if((high_flag == 1) && (low_flag == 3))
            {
                receive_data_bit_flag = 1;
                receive_data_state = 4;
            }
            else if((high_flag == 2) && (low_flag == 2))
            {
                receive_data_bit_flag = 2;
                receive_data_state = 4;
            }
            else if((high_flag == 3) && (low_flag == 1))
            {
                receive_data_bit_flag = 3;
                receive_data_state = 4;
            }
            else
            {
                receive_data_bit_flag = 0;
                receive_data_state = 6;
            }
        }
        break;

        case 4://����������Ч���ݡ�
        {
            if(receive_data_frame_flag == 0)//�����ʼ֡��
            {
                if(receive_data_bit_flag == 2)
                {
                    receive_data_frame_flag = 1;
                    receive_data_state = 1;
                }
                else
                {
                    receive_data_state = 6;
                }
            }
            else if(receive_data_frame_flag == 1)//��������
            {
                if(receive_data_bit_flag != 0x02)
                {
                    if(receive_data_bit_flag == 0x01)//�͵�ƽ��
                    {
                        receive_data_temp[receive_data_byte_count] &= ~(1 << receive_data_bit_count++);
                    }
                    else
                    {
                        receive_data_temp[receive_data_byte_count] |= (1 << receive_data_bit_count++);
                    }

                    if(receive_data_bit_count == 8)
                    {
                        receive_data_bit_count = 0;
                        receive_data_byte_count++;

                        if(receive_data_byte_count == RECEIVE_DATA_SIZE + 1)
                        {
                            receive_data_byte_count = 0;

                            receive_data_frame_flag = 2;
                        }
                        else
                        {
                            receive_data_state = 1;
                        }
                    }
                    else
                    {
                        receive_data_state = 1;
                    }
                }
                else
                {
                    receive_data_state = 6;
                }
            }
            else if(receive_data_frame_flag == 2)//У�����ݡ�
            {
                if(check_sum((unsigned char*)receive_data_temp, RECEIVE_DATA_SIZE) == receive_data_temp[RECEIVE_DATA_SIZE])
                    receive_data_state = 5;
                else
                    receive_data_state = 6;
            }
            else
            {
                //Ԥ����
            }
        }
        break;
        
        case 5://�������ݳɹ������¿�ʼ���ա�
        {
            
            for(i_t = 0; i_t < RECEIVE_DATA_SIZE; i_t++)
                receive_data_buff[i_t] = receive_data_temp[i_t];
                        
            receive_data_flag = 1;//���ճɹ���

            receive_data_frame_flag = 0;//֡״̬��
            receive_data_byte_count = 0;//����֡λ����
            receive_data_bit_count = 0;//����֡�ֽ���

            receive_data_state = 0;
        }
        break;

        case 6://�������ݴ������¿�ʼ���ա�
        {
            receive_data_frame_flag = 0;//֡״̬��
            receive_data_byte_count = 0;//����֡λ����
            receive_data_bit_count = 0;//����֡�ֽ���

            receive_data_state = 0;
        }
        break;
        
        default:
        {
            receive_data_state = 6;
        }
        break;
    }
}

/*******************************************************************************
  * @brief   comm_handle:������պͷ��͡�
  * @param   �ޡ�
  * @retval  �ޡ�
  * @note    ���50us����һ�Ρ�
*******************************************************************************/
void comm_handle(void)
{
    if(comm_direction_flag)
    {
        send_data();
    }
    else
    {
        receive_data();
    }
}
