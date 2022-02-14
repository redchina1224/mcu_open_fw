//******************************************************************************
//Copyright(C) 2020-2021 zhejiang zhida dianzikeji Co., Ltd
//浙江智达电子科技有限公司
//File name:      user_time.h
//Author:         zzg
//Version:        Ver0.1
//Date:           2021-4-25
//Description:    TIME时间处理
//History:
//******************************************************************************
#ifndef __USER_UART_H__
#define __USER_UART_H__

/*
struct struct_uartdata
{
unsigned char S1ReadStartChar;
unsigned char S1ReadPtr;
unsigned char S1WritePtr;
unsigned char S1ReadLength;
unsigned char S1ReadTimeout;
unsigned char S1WriteLength;
unsigned char S1Reading;
unsigned char *S1ReadBuffer;
unsigned char *S1WriteBuffer;
};
*/

extern bit S1_Busy;
extern unsigned char S1ReadStartChar;
extern unsigned char S1ReadPtr;
extern unsigned char S1WritePtr;
extern unsigned char S1ReadLength;
extern unsigned char S1ReadTimeout;
extern unsigned char S1WriteLength;
extern unsigned char S1Reading;
extern unsigned char *S1ReadBuffer;
extern unsigned char *S1WriteBuffer;



//声明外部函数******************************************************************
void Uart1Init(void);
void Uart1Send(unsigned char writelength);
void UART1_TxIsr(unsigned char *TxReg);
void UART1_RxIsr(unsigned char *RxReg);


#endif 


/************************ (C) COPYRIGHT zhejiang zhida *****END OF FILE****/