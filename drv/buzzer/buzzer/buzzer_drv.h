//******************************************************************************
//Copyright(C) 2020-2021 zhejiang zhida dianzikeji Co., Ltd
//�㽭�Ǵ���ӿƼ����޹�˾
//File name:      buzz.h
//Author:         zzg
//Version:        Ver0.1
//Date:           2021-4-25
//Description:    ������
//History:
//******************************************************************************
#ifndef __BUZZER_DRV_H__
#define __BUZZER_DRV_H__

/*
typedef struct {
unsigned char beepCnt;
unsigned char beepton_x50ms;
unsigned char beeptoff_x50ms;
} zd_buzzer_t;
*/



/***********************************************************************************************
*������ 		: void zd_buzzer_beep(unsigned char beepCnt,unsigned char beepton_x50ms,unsigned char beeptoff_x50ms)
*������������ 	: ���������칤��
*�������� 		: beepCnt=����������
				  beepton=�����ʱ�� (x50ms) ,
				  beeptoff=�м�ֹͣ�����ʱ�� (x50ms)
*��������ֵ 	: ��
***********************************************************************************************/
void zd_buzzer_beep(unsigned char beepCnt,unsigned char beepton_x50ms,unsigned char beeptoff_x50ms);



/***********************************************************************************************
*������ 			: void zd_buzzerRun(void)
*������������ 		: �����������Զ�����(����ʱ�䣬����),��ÿ50ms����һ��
*�������� 			: ��
*��������ֵ 		: ��
***********************************************************************************************/
void zd_buzzerRun(void);

/***********************************************************************************************
*������ 			: void zd_buzzer_init(void)
*������������ 		: ������ʼ��
*�������� 			: ��
*��������ֵ 		: ��
***********************************************************************************************/
void zd_buzzer_init(void);


#endif 


/************************ (C) COPYRIGHT zhejiang zhida *****END OF FILE****/