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
#ifndef __TM1640_DRV_H__
#define __TM1640_DRV_H__

extern unsigned char *tm1640_WriteBuffer;


void tm1640_Init(void);
void tm1640_SendDataRun(void);
void tm1640_BrightSet(unsigned char flag);

#endif
//******************************************************************************

