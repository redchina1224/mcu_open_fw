//******************************************************************************
//Copyright(C) 2020-2021 zhejiang zhida dianzikeji Co., Ltd
//�㽭�Ǵ���ӿƼ����޹�˾
//File name:      variable.h
//Author:         zzg
//Version:        Ver0.1
//Date:           2021-4-25
//Description:    ȫ��ͷ�ļ�����/ȫ�ֺ궨������/ȫ�ֱ�������
//History:
//******************************************************************************
#ifndef __TM1628_DRV_H__
#define __TM1628_DRV_H__

extern unsigned char *Tm1628_WriteBuffer;


void tm1628_Init(void);
void tm1628_SendDataRun(void);
void tm1628_BrightSet(unsigned char flag);

#endif
//******************************************************************************

