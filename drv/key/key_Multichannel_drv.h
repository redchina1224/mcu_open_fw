//******************************************************************************
//Copyright(C) 2020-2021 zhejiang zhida dianzikeji Co., Ltd
//浙江智达电子科技有限公司
//File name:      key.h
//Author:         zzg
//Version:        Ver0.1
//Date:           2021-4-25
//Description:    按键
//History:
//******************************************************************************
#ifndef __KEY_MULTICHANNEL_DRV_H__
#define __KEY_MULTICHANNEL_DRV_H__




struct  mof_userkey_t {
unsigned int UserKeyRepeatDelay;
unsigned char KeyQuickPressCount;
unsigned int KeyLongPressCount;
unsigned char KeySource;
unsigned long KeyVal;
unsigned long KeyDat;
unsigned long KeyValQuick_Ago;
unsigned long KeyVal_Ago;
	
unsigned char UserKeySource;
unsigned long UserKeyVal;
unsigned long UserKeyDat;
unsigned int UserKeyCnt;

unsigned char UserKeyPressed;
unsigned char UserKeyLongPressed;
unsigned char UserKeyPressed_down;
unsigned char UserKeyPressed_up;


};



//#if ((KeyType&KeyType_MultiChannel)==KeyType_MultiChannel)

	#if ((KeyType&KeyType_Gpio)==KeyType_Gpio||(KeyType&KeyType_SoftLedWithGpio)==KeyType_SoftLedWithGpio)
extern struct mof_userkey_t gpioKeys;
	#endif
	
	#if ((KeyType&KeyType_McuTouch)==KeyType_McuTouch)
extern struct mof_userkey_t mcuTouchKeys;
	#endif
	
	#if ((KeyType&KeyType_IR)==KeyType_IR)
extern struct mof_userkey_t irKeys;
	#endif
	
	#if ((KeyType&KeyType_RF)==KeyType_RF)
extern struct mof_userkey_t rfKeys;	
	#endif

	#if ((KeyType&KeyType_USER)==KeyType_USER)
extern struct mof_userkey_t userKeys;	
	#endif
	
//#endif



//声明外部函数******************************************************************
void mof_key_init(void);
void mof_key_clear(struct mof_userkey_t *ukey);
void mof_keyRun(void);

void mof_keyCheck(struct mof_userkey_t* ukey,unsigned long keysnotpress);


#endif 


/************************ (C) COPYRIGHT zhejiang zhida *****END OF FILE****/