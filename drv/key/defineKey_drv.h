#ifndef __DEFINEKEY_BSP_H_
#define __DEFINEKEY_BSP_H_

	//�����ѡ�������嵥
	#define KeyType_Unkonw 0
	#define KeyType_Gpio BIT0 //ֱ��IO
	#define KeyType_McuTouch BIT1 //��������
	#define KeyType_Touch BIT2 //��������
	#define KeyType_IR BIT3 //�������
	#define KeyType_RF BIT4 //�������
	#define KeyType_SoftLedWithGpio BIT5 //�����LED�������õ�ֱ��IO

	#define KeyType_USER BIT24

	#define KeyType_MultiChannel BIT31 //��ͨ��ʹ��

#endif