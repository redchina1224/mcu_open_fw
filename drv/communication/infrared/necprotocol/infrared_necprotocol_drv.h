//******************************************************************************
//Copyright(C) 2020-2021 zhejiang zhida dianzikeji Co., Ltd
//浙江智达电子科技有限公司
//File name:      variable.h
//Author:         zzg
//Version:        Ver0.1
//Date:           2021-4-25
//Description:    全局头文件调用/全局宏定义声明/全局变量声明
//History:
//******************************************************************************
#ifndef __INFRARED_NEC_PROTOCOL_DRV_H__
#define __INFRARED_NEC_PROTOCOL_DRV_H__

typedef struct
{
	unsigned char SendEnSw;
	unsigned char Busy;
	unsigned char ReadPtr;
	unsigned char WritePtr;
	unsigned char ReadLength;
	unsigned char ReadTimeout;
	unsigned char WriteLength;
	unsigned char Reading;
	unsigned char Reading_HighTimerCount;
	unsigned char Reading_LowTimerCount;
	unsigned char Reading_BaseTimerCount;	
	unsigned char Reading_BitCount;
	unsigned char Read_IO;
	unsigned char Read_IO_Last;	
	unsigned char Writing;
	unsigned char Writing_BaseTimerCount;
	unsigned char Writing_BitCount;
	unsigned char Write_IO;
	unsigned char *p_ReadBuffer;
	unsigned char *p_WriteBuffer;
} mof_fix_length_infrared_t;

#define IR_NEC_START_LOW_WIDTH_TIME 			    90	//BIT总波时间。
#define IR_NEC_START_HIGH_WIDTH_TIME 			    45	//BIT总波时间。
#define IR_NEC_REPEAT_HIGH_WIDTH_TIME 			  22	//BIT总波时间。

#define IR_NEC_DATA_SHORT_WIDTH_TIME 			    5	//BIT总波时间。
#define IR_NEC_DATA_LONG_WIDTH_TIME 			    17	//BIT总波时间。


#define IR_NEC_DATA_TIMEOUT_TIME 			    (IR_NEC_DATA_SHORT_WIDTH_TIME+IR_NEC_DATA_LONG_WIDTH_TIME)	//BIT总波时间。
#define IR_NEC_START_TIMEOUT_TIME 			  1200	//BIT总波时间。


#define SEND_BIT_WIDTH_TIME 			    20	//BIT总波时间。
#define SEND_LONG_WAVE_TIME 			    15	//长波时间。
#define SEND_MEDIUM_WAVE_TIME 		    10	//中波时间。
#define SEND_SHORT_WAVE_TIME 			    5	//短波时间。
#define SEND_DEAD_ZREA_TIME 			    100	//死区时间。

extern void infrared_fixed_length_in_isr(void);
extern void infrared_fixed_length_init(unsigned char i,unsigned char *sendbuf,unsigned char *recvbuf,unsigned char recv_len);
//extern void infrared_fixed_length_send(unsigned char i,unsigned char writelength);//,unsigned char readlength)

extern mof_fix_length_infrared_t xdata fixed_length_infrared_nec[1];

#endif


