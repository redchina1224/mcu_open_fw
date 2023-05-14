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

volatile unsigned char xdata comm_direction_flag = 0;//0:接收，1：发送。

volatile unsigned char xdata send_data_flag = 0;//发送标志位。
volatile unsigned char xdata send_data_buff[SEND_DATA_SIZE]; //待发送的数据。

volatile unsigned char xdata receive_data_flag = 0; //接收标志位。
volatile unsigned char xdata receive_data_buff[RECEIVE_DATA_SIZE]; //接收的数据



volatile unsigned char xdata comm2_direction_flag = 0;//0:接收，1：发送。

volatile unsigned char xdata send2_data_flag = 0; //发送标志位。
volatile unsigned char xdata send2_data_buff[SEND2_DATA_SIZE]; //待发送的数据。

volatile unsigned char xdata receive2_data_flag = 0; //接收标志位。
volatile unsigned char xdata receive2_data_buff[RECEIVE2_DATA_SIZE]; //接收的数据


		#define ONEWIRE_DIO_H ONEWIRE_DIO=1
		#define ONEWIRE_DIO_L ONEWIRE_DIO=0		
		#define ONEWIRE2_DIO_H ONEWIRE2_DIO=1
		#define ONEWIRE2_DIO_L ONEWIRE2_DIO=0		

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

/*******************************************************************************
  * @brief   send_mode:设置成发送模式。
  * @param   无。
  * @retval  无。
  * @note    无
*******************************************************************************/
void send_mode(void)
{
	//P33F = 0x02;
	//P33C = 0x00;
	ONEWIRE_DIO_OUT;
    comm_direction_flag = 1;
}

/*******************************************************************************
  * @brief   receive_mode:设置成接收模式。
  * @param   无。
  * @retval  无。
  * @note    无
*******************************************************************************/
void receive_mode(void)
{
//	P33F = 0x01;
//	P33C = 0x00;
	ONEWIRE_DIO_IN;
    comm_direction_flag = 0;
}


/*******************************************************************************
  * @brief   Comm_Send1:发送数据。
  * @param   无。
  * @retval  无。
  * @note    间隔50us调用一次，CPU在16MHz的情况下执行一次，平均3.75us,最大5us,最小3.125us。
*******************************************************************************/
void send_data(void)
{
    unsigned char i_t = 0;
    static 	unsigned char send_data_time = 0;//发送时间计数。
    static  unsigned char send_data_temp[SEND_DATA_SIZE + 1]; //暂存数据。
    static	unsigned char send_data_bit_count = 0;//计算发送的位数。
    static	unsigned char send_data_byte_count = 0;//计算发送的字节数。
    static  unsigned char send_data_count = 0;//计算发送的次数。
    static 	unsigned char send_data_state = 0;
    
    send_data_time++;
    
    switch(send_data_state) 
    {
        case 0://检测是否有待发数据。
        {
            if(send_data_flag != 0)
            {
                //添加数据。
                for(i_t = 0; i_t < SEND_DATA_SIZE; i_t++)
                    send_data_temp[i_t] = send_data_buff[i_t];
                
                //添加校验数据。
                send_data_temp[SEND_DATA_SIZE] = check_sum((unsigned char*)send_data_buff, SEND_DATA_SIZE);
                
                //开始发送数据。
                SEND_DATA_HIGH;
                send_data_time = 0;
                send_data_state = 1;
            }
            else
            {
                SEND_DATA_LOW;
            }
        }
        break;
        
        case 1://发送前导码。
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
        
        case 2://发送数据帧。
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
        
        case 3://发送结束符。
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
        
        case 4://发送死区。
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
        
        case 5://结束发送。
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
  * @brief   receive_data:接收数据。
  * @param   无。
  * @retval  无。
  * @note    间隔50us调用一次,CPU在16MHz的情况下执行一次，平均3.5us,最大7.5us,最小3.125us。。
*******************************************************************************/
void receive_data(void)
{
    unsigned char i_t = 0;
    static 	unsigned char high_count = 0, low_count = 0;//高低电平计数。
    static 	unsigned char high_flag = 0,  low_flag  = 0;//高低电平种类。       
    static  unsigned char receive_data_time = 0;//接收时间计数。
    static  unsigned char receive_data_temp[RECEIVE_DATA_SIZE + 1]; //暂存数据。
    static  unsigned char receive_data_frame_flag = 0;//
    static 	unsigned char receive_data_bit_flag = 0;//数据位的种类。
    static	unsigned char receive_data_byte_count = 0;//计算接收的位数。
    static	unsigned char receive_data_bit_count = 0;//计算接收的字节数。
    static 	unsigned char receive_data_state = 0;
    
    receive_data_time++;
    
    switch(receive_data_state)
    {
        case 0://循环检测高电平。
        {
            if((RECEIVE_DATA_READ != 0) && (RECEIVE_DATA_READ != 0))
            {
                receive_data_time = 0;
                receive_data_state = 1;
            }
        }
        break;
        
        case 1://检测高电平种类。
        {
            if(receive_data_time > RECEIVE_TIME_OUT)
            {
                receive_data_state = 6;//接收错误。这句话可以选择不要。
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
                //检测中。
            }
                
        }
        break;
        
        case 2://检测低电平种类。
        {
            if(receive_data_time > RECEIVE_TIME_OUT)
            {
                receive_data_state = 6;//接收错误。句话可以选择不要。
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
                //检测中。
            }
        }
        break;
        
        case 3://分析接收一位数据。
        {
            if((high_flag == 1) && (low_flag == 3))
            {
                receive_data_bit_flag = 1;
                receive_data_state = 4;
            }
            else if(((high_flag == 2) || (high_flag == 1)) && (low_flag == 2))
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

        case 4://分析接收有效数据。
        {
            if(receive_data_frame_flag == 0)//检测起始帧。
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
            else if(receive_data_frame_flag == 1)//接收数据
            {
                if(receive_data_bit_flag != 0x02)
                {
                    if(receive_data_bit_flag == 0x01)//低电平。
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
            else if(receive_data_frame_flag == 2)//校验数据。
            {
                if(check_sum((unsigned char*)receive_data_temp, RECEIVE_DATA_SIZE) == receive_data_temp[RECEIVE_DATA_SIZE])
                    receive_data_state = 5;
                else
                    receive_data_state = 6;
            }
            else
            {
                //预留。
            }
        }
        break;
        
        case 5://接收数据成功，重新开始接收。
        {
            
            for(i_t = 0; i_t < RECEIVE_DATA_SIZE; i_t++)
                receive_data_buff[i_t] = receive_data_temp[i_t];
                        
            receive_data_flag = 1;//加收成功。

            receive_data_frame_flag = 0;//帧状态。
            receive_data_byte_count = 0;//数据帧位数。
            receive_data_bit_count = 0;//数据帧字节数

            receive_data_state = 0;
        }
        break;

        case 6://接收数据错误，重新开始接收。
        {
            receive_data_frame_flag = 0;//帧状态。
            receive_data_byte_count = 0;//数据帧位数。
            receive_data_bit_count = 0;//数据帧字节数

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
  * @brief   send2_mode:设置成发送模式。
  * @param   无。
  * @retval  无。
  * @note    在浴霸三线线供电和通信中，发射模式时，发射口设置推挽输出低电平。
*******************************************************************************/
void send2_mode(void)
{
	ONEWIRE2_DIO_OUT;
    comm2_direction_flag = 1;
}

/*******************************************************************************
  * @brief   receive2_mode:设置成接收模式。
  * @param   无。
  * @retval  无。
  * @note    在浴霸三线线供电和通信中，接收模式时，接收口设置为浮空输入。
*******************************************************************************/
void receive2_mode(void)
{
	ONEWIRE2_DIO_IN;
    comm2_direction_flag = 0;
}


/*******************************************************************************
  * @brief   Comm_Send:发送数据。
  * @param   无。
  * @retval  无。
  * @note    间隔50us调用一次，CPU在16MHz的情况下执行一次，平均3.75us,最大5us,最小3.125us。
*******************************************************************************/
void send2_data(void)
{
    unsigned char i_t = 0;
    static 	unsigned char xdata send2_data_time = 0;//发送时间计数。
    static  unsigned char xdata send2_data_temp[SEND2_DATA_SIZE + 1]; //暂存数据。
    static	unsigned char xdata send2_data_bit_count = 0;//计算发送的位数。
    static	unsigned char xdata send2_data_byte_count = 0;//计算发送的字节数。
    static  unsigned char xdata send2_data_count = 0;//计算发送的次数。
    static 	unsigned char xdata send2_data_state = 0;
    
    send2_data_time++;
    
    switch(send2_data_state) 
    {
        case 0://检测是否有待发数据。
        {
            if(send2_data_flag != 0)
            {
                //添加数据。
                for(i_t = 0; i_t < SEND2_DATA_SIZE; i_t++)
                    send2_data_temp[i_t] = send2_data_buff[i_t];
                
                //添加校验数据。
                send2_data_temp[SEND2_DATA_SIZE] = check_sum((unsigned char xdata*)send2_data_buff, SEND2_DATA_SIZE);
                
                //开始发送数据。
                SEND2_DATA_LOW;
                send2_data_time = 0;
                send2_data_state = 1;
            }
            else
            {
                SEND2_DATA_LOW;
            }
        }
        break;
        
        case 1://发送数据前，发送一段低电平。
        {
            if(send2_data_time > (SEND2_DEAD_ZREA_TIME - 1))
            {
                //开始发送数据。
                SEND2_DATA_HIGH;
                send2_data_time = 0;
                send2_data_state = 2;
            }
            else
            {
                SEND2_DATA_LOW;
            }
        }
        break;
        
        case 2://发送前导码。
        {
            if(send2_data_time > (SEND2_BIT_WIDTH_TIME - 1))
            {
                SEND2_DATA_HIGH;
                send2_data_time = 0;
                send2_data_state = 3;
            }
            else
            {
                if(send2_data_time < SEND2_MEDIUM_WAVE_TIME)
                    SEND2_DATA_HIGH;
                else
                    SEND2_DATA_LOW;
            }
        }
        break;
        
        case 3://发送数据帧。
        {
            if(send2_data_time > (SEND2_BIT_WIDTH_TIME - 1))
            {
                send2_data_time = 0;
                SEND2_DATA_HIGH;
                
                send2_data_temp[send2_data_byte_count] >>= 1;
                send2_data_bit_count++;
                
                if(send2_data_bit_count >= 8)
                {
                    send2_data_bit_count = 0;
                    send2_data_byte_count++;
                    
                    if(send2_data_byte_count >= SEND2_DATA_SIZE + 1)
                    {
                        send2_data_byte_count = 0;
                        send2_data_state = 4;
                    }
                }
            }
            else
            {
                if(send2_data_temp[send2_data_byte_count] & 0x01)
                {
                    if(send2_data_time < SEND2_LONG_WAVE_TIME)
                        SEND2_DATA_HIGH;
                    else
                        SEND2_DATA_LOW;
                }
                else
                {
                    if(send2_data_time < SEND2_SHORT_WAVE_TIME)
                        SEND2_DATA_HIGH;
                    else
                        SEND2_DATA_LOW;
                }
            }
        }
        break;
        
        case 4://发送结束符。
        {
            if(send2_data_time > (SEND2_BIT_WIDTH_TIME - 1))
            {
                SEND2_DATA_LOW;
                send2_data_time = 0;
                send2_data_state = 5;
            }
            else
            {
                if(send2_data_time < SEND2_MEDIUM_WAVE_TIME)
                    SEND2_DATA_HIGH;
                else
                    SEND2_DATA_LOW;
            }
        }
        break;
        
        case 5://发送死区。
        {
            if(send2_data_time > SEND2_DEAD_ZREA_TIME)
            {
                send2_data_time = 0;
                
                send2_data_count++;
                
                if(send2_data_count >= SEND2_DATA_COUNT)
                {
                    send2_data_count = 0;
                    send2_data_state = 6;
                }
                else
                {
                    send2_data_state = 0;
                }
            }
            else
            {
                SEND2_DATA_LOW;
            }
        }
        break;
        
        case 6://结束发送。
        {
            send2_data_flag = 0;
            send2_data_state = 0;
        }
        break;
        
        default:
        {
            send2_data_state = 0;
        }
        break;
    }
}

/*******************************************************************************
  * @brief   receive2_data:接收数据。
  * @param   无。
  * @retval  无。
  * @note    间隔50us调用一次,CPU在16MHz的情况下执行一次，平均3.5us,最大7.5us,最小3.125us。。
*******************************************************************************/
void receive2_data(void)
{
    unsigned char xdata i_t = 0;
    static 	unsigned char xdata high_count = 0, low_count = 0;//高低电平计数。
    static 	unsigned char xdata high_flag = 0,  low_flag  = 0;//高低电平种类。       
    static  unsigned char xdata receive2_data_time = 0;//接收时间计数。
    static  unsigned char xdata receive2_data_temp[RECEIVE2_DATA_SIZE + 1]; //暂存数据。
    static  unsigned char xdata receive2_data_frame_flag = 0;//
    static 	unsigned char xdata receive2_data_bit_flag = 0;//数据位的种类。
    static	unsigned char xdata receive2_data_byte_count = 0;//计算接收的位数。
    static	unsigned char xdata receive2_data_bit_count = 0;//计算接收的字节数。
    static 	unsigned char xdata receive2_data_state = 0;
    
    receive2_data_time++;
    
    switch(receive2_data_state)
    {
        case 0://循环检测高电平。
        {
            if((RECEIVE2_DATA_READ != 0) && (RECEIVE2_DATA_READ != 0))
            {
                receive2_data_time = 0;
                receive2_data_state = 1;
            }
        }
        break;
        
        case 1://检测高电平种类。
        {
            if(receive2_data_time > RECEIVE2_TIME_OUT)
            {
                receive2_data_state = 6;//接收错误。
            }
            else if((RECEIVE2_DATA_READ == 0) && (RECEIVE2_DATA_READ == 0))
            {
                high_count = receive2_data_time;
                receive2_data_time = 0;
                
                if((high_count <= RECEIVE2_MAX_SHORT_WAVE_TIME) && (high_count >= RECEIVE2_MIN_SHORT_WAVE_TIME))
                    high_flag = 1;
                else if((high_count <= RECEIVE2_MAX_MEDIUM_WAVE_TIME) && (high_count >= RECEIVE2_MIN_MEDIUM_WAVE_TIME))
                    high_flag = 2;
                else if((high_count <= RECEIVE2_MAX_LONG_WAVE_TIME) && (high_count >= RECEIVE2_MIN_LONG_WAVE_TIME))
                    high_flag = 3;
                else
                    high_flag = 0;

                receive2_data_state = 2;
            }
            else
            {
                //检测中。
            }
                
        }
        break;
        
        case 2://检测低电平种类。
        {
            if(receive2_data_time > RECEIVE2_TIME_OUT)
            {
                receive2_data_state = 6;//接收错误。
            }
            else if((RECEIVE2_DATA_READ != 0) && (RECEIVE2_DATA_READ != 0))
            {
                low_count = receive2_data_time;
                receive2_data_time = 0;
                
                if((low_count <= RECEIVE2_MAX_SHORT_WAVE_TIME) && (low_count >= RECEIVE2_MIN_SHORT_WAVE_TIME))
                    low_flag = 1;
                else if((low_count <= RECEIVE2_MAX_MEDIUM_WAVE_TIME) && (low_count >= RECEIVE2_MIN_MEDIUM_WAVE_TIME))
                    low_flag = 2;
                else if((low_count <= RECEIVE2_MAX_LONG_WAVE_TIME) && (low_count >= RECEIVE2_MIN_LONG_WAVE_TIME))
                    low_flag = 3;
                else
                    low_flag = 0;

                receive2_data_state = 3;
            }
            else
            {
                //检测中。
            }
        }
        break;
        
        case 3://分析接收一位数据。
        {
            if((high_flag == 1) && (low_flag == 3))
            {
                receive2_data_bit_flag = 1;
                receive2_data_state = 4;
            }
            else if((high_flag == 2) && (low_flag == 2))
            {
                receive2_data_bit_flag = 2;
                receive2_data_state = 4;
            }
            else if((high_flag == 3) && (low_flag == 1))
            {
                receive2_data_bit_flag = 3;
                receive2_data_state = 4;
            }
            else
            {
                receive2_data_bit_flag = 0;
                receive2_data_state = 6;
            }
        }
        break;

        case 4://分析接收有效数据。
        {
            if(receive2_data_frame_flag == 0)//检测起始帧。
            {
                if(receive2_data_bit_flag == 2)
                {
                    receive2_data_frame_flag = 1;
                    receive2_data_state = 1;
                }
                else
                {
                    receive2_data_state = 6;
                }
            }
            else if(receive2_data_frame_flag == 1)//接收数据
            {
                if(receive2_data_bit_flag != 0x02)
                {
                    if(receive2_data_bit_flag == 0x01)//低电平。
                    {
                        receive2_data_temp[receive2_data_byte_count] &= ~(1 << receive2_data_bit_count++);
                    }
                    else
                    {
                        receive2_data_temp[receive2_data_byte_count] |= (1 << receive2_data_bit_count++);
                    }

                    if(receive2_data_bit_count == 8)
                    {
                        receive2_data_bit_count = 0;
                        receive2_data_byte_count++;

                        if(receive2_data_byte_count == RECEIVE2_DATA_SIZE + 1)
                        {
                            receive2_data_byte_count = 0;

                            receive2_data_frame_flag = 2;
                        }
                        else
                        {
                            receive2_data_state = 1;
                        }
                    }
                    else
                    {
                        receive2_data_state = 1;
                    }
                }
                else
                {
                    receive2_data_state = 6;
                }
            }
            else if(receive2_data_frame_flag == 2)//校验数据。
            {
                if(check_sum((unsigned char xdata*)receive2_data_temp, RECEIVE2_DATA_SIZE) == receive2_data_temp[RECEIVE2_DATA_SIZE])
                    receive2_data_state = 5;
                else
                    receive2_data_state = 6;
            }
            else
            {
                //预留。
            }
        }
        break;
        
        case 5://接收数据成功，重新开始接收。
        {
            
            for(i_t = 0; i_t < RECEIVE2_DATA_SIZE; i_t++)
                receive2_data_buff[i_t] = receive2_data_temp[i_t];
                        
            receive2_data_flag = 1;//加收成功。

            receive2_data_frame_flag = 0;//帧状态。
            receive2_data_byte_count = 0;//数据帧位数。
            receive2_data_bit_count = 0;//数据帧字节数

            receive2_data_state = 0;
        }
        break;

        case 6://接收数据错误，重新开始接收。
        {
            receive2_data_frame_flag = 0;//帧状态。
            receive2_data_byte_count = 0;//数据帧位数。
            receive2_data_bit_count = 0;//数据帧字节数

            receive2_data_state = 0;
        }
        break;
        
        default:
        {
            receive2_data_state = 6;
        }
        break;
    }
}


/*******************************************************************************
  * @brief   comm_handle:处理接收和发送。
  * @param   无。
  * @retval  无。
  * @note    间隔50us调用一次。
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
		
		
    if(comm2_direction_flag)
    {
        send2_data();
    }
    else
    {
        receive2_data();
    }
}
