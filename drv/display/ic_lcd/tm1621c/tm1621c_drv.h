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
#ifndef __TM1621C_DRV_H__
#define __TM1621C_DRV_H__

extern unsigned char *Tm1621c_WriteBuffer;


void TM1621C_Init(void);
void TM1621C_SendDataRun(void);

#endif
//******************************************************************************

