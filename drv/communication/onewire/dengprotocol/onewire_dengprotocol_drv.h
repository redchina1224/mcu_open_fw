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
#ifndef __ONEWIRE_DENG_PROTOCOL_DRV_H__
#define __ONEWIRE_DENG_PROTOCOL_DRV_H__

#define SEND_DATA_HIGH   	                ONEWIRE_DIO_H
#define SEND_DATA_LOW                       ONEWIRE_DIO_L
#define RECEIVE_DATA_READ                   ONEWIRE_DIO


#define SEND_DATA_COUNT                     1   //发送数据的次数。
#define RECEIVE_DATA_SIZE		            3	//接收数据大小。
#define SEND_DATA_SIZE                      3   //发送数据的大小。

#define SEND_BIT_WIDTH_TIME 			    20	//BIT总波时间。
#define SEND_LONG_WAVE_TIME 			    15	//长波时间。
#define SEND_MEDIUM_WAVE_TIME 		        10	//中波时间。
#define SEND_SHORT_WAVE_TIME 			    5	//短波时间。
#define SEND_DEAD_ZREA_TIME 			    100	//死区时间。

#define RECEIVE_TIME_OUT			        20	//最大波长时间。
#define RECEIVE_MAX_LONG_WAVE_TIME 	        17	//最大长波时间。
#define RECEIVE_MIN_LONG_WAVE_TIME 	        13	//最小长波时间。
#define RECEIVE_MAX_MEDIUM_WAVE_TIME 	    12	//最大中波时间。
#define RECEIVE_MIN_MEDIUM_WAVE_TIME 	    8	//最小中波时间。
#define RECEIVE_MAX_SHORT_WAVE_TIME         7	//最大短波时间。
#define RECEIVE_MIN_SHORT_WAVE_TIME         3	//最小短波时间。

extern volatile unsigned char send_data_flag; //发送标志位。
extern volatile unsigned char send_data_buff[SEND_DATA_SIZE]; //待发送的数据。

extern volatile unsigned char receive_data_flag; //接收标志位。
extern volatile unsigned char receive_data_buff[RECEIVE_DATA_SIZE]; //接收的数据

extern void send_mode(void);
extern void receive_mode(void);
extern void send_data(void);
extern void receive_data(void);
extern void comm_handle(void);


#endif
