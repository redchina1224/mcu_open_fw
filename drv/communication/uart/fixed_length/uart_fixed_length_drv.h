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
#ifndef __UART_FIX_LENGTH_PROTOCOL_DRV_H__
#define __UART_FIX_LENGTH_PROTOCOL_DRV_H__

typedef struct
{
unsigned char Busy;
unsigned char ReadPtr;
unsigned char WritePtr;
unsigned char ReadLength;
unsigned char ReadTimeout;
unsigned char WriteLength;
unsigned char Reading;
unsigned char Writing;
unsigned char *p_ReadBuffer;
unsigned char *p_WriteBuffer;
} mof_fix_length_uart_port_t;


void uart_fixed_length_tx_in_isr(void);

void uart_fixed_length_rx_in_isr(void);

#endif
