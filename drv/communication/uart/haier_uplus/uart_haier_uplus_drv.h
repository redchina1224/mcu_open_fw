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
#ifndef __UART_HAIER_UPLUS_PROTOCOL_DRV_H__
#define __UART_HAIER_UPLUS_PROTOCOL_DRV_H__


typedef struct
{
unsigned char S_Busy;
unsigned char S_ReadCharWindows[2];
unsigned char S_ReadPtr;
unsigned char S_WritePtr;
unsigned char S_ReadLength;
unsigned char S_ReadTimeout;
unsigned char S_WriteLength;
unsigned char S_WriteAppendbytes;
unsigned char S_Reading;
unsigned char S_Writing;
unsigned char *S_ReadBuffer;
unsigned char *S_WriteBuffer;
unsigned char S_ReadChecksumAdj;
unsigned char S_WriteChecksumAdj;
} mof_haier_uplus_uart_port_t;

void uart_haier_uplus_tx_in_isr(void);

void uart_haier_uplus_rx_in_isr(void);

#endif
