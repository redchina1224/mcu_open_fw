#ifndef	__CMS_CHECKTOUCH_PT_79FT73XX_H_
#define	__CMS_CHECKTOUCH_PT_79FT73XX_H_


//#include "TouchKeyConst.h"

//�ӿں�������
extern void __CMS_CheckTouchKey(void);		//����ɨ�������̺���,������2.5ms~5ms�ڵ���
extern void __CMS_GetTouchKeyValue(void);//�˺��������жϣ������ж�ɨ��ʱ��125us
extern volatile bit _CMS_b_kerr;				//��λ������־
//ÿ��������Ӧ�ڼĴ�����1��λ,�ɸ�����һһ��Ӧ
//_CMS_KeyFlag[0]��Ӧ��Key8,...,Key2,Key1
//_CMS_KeyFlag[1]��Ӧ��Key16,...,Key10,Key9
//_CMS_KeyFlag[2]��Ӧ��Key20,Key19,Key18,Key17
//������Чʱ��ӦλΪ1,��ЧʱΪ0
extern volatile unsigned char _CMS_KeyFlag[3];
//-------------------------------------------------------

//-------------------------------------------------------
//-------------------------------------------------------
//-------------------------------------------------------
/*
���津��Ч����������
*/
//����ⰴ������,����
#define		C_KEY_TOTAL		TOUCH_KEYS_TOTAL_NUMBER	//���֧��16ͨ��

//����������������C_KEY_SHAKE
#define		C_KEY_SHAKE		2	//2~8

//�����ſ���������C_KEY_SHAKE
#define		C_KEY_OFFSHAKE		2	//2~8

//������ֵ
#define		VOL_VALUE		25	//�޸����µ����������ֵ*2,��Χ10~127

//����ֵ
#define		SLU_VALUE		12	//��ָ���ºͷſ��л�������ֵ,��ֵ��С�ڵ���VOL_VALUE

//������׼ֵ������������
#define		CM_BASE			10			//����ʱ��ԼΪ(���������ʱ��4ms*2 + ��������*1.5) * CM_BASE

//ͬʱ���������Ч������,������ֵ����Ϊ�Ǹ���
#define		C_VALID_KEY		2	

//�������������Чʱ��,��ɨ��ʱ�䣨����5ms��Ϊ��׼����,Ϊ0ʱ������
#define		C_VALID_TIME	(1000/5)*20//20S

//�����ȵ�λ
#define 	LMDVALUE		1//0~1,Խ��Լ����,Ϊ1ʱע������ֵ�Լ�������׼ֵ

//�ڲ�������
#define		KEY_EN1KRES		0//0~1



/*-------------------------------------------------------
��������ͨ������²����޸�
-------------------------------------------------------*/
//�쳣�ж�ʹ�ܣ���TKֵ�쳣���½�������Ӧ
#define		UNNOL_CHECK		1//0~1
//�쳣�ж��Իָ��������������ٽ����Իָ�
#define		UNNOL_TIMES		100//1~100

//����ѹ
#define 	KEY_LDOSEL		4//0~7


#endif





