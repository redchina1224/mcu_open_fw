#include "..\com_include_drv.h"


//#if ((KeyType&KeyType_MultiChannel)==KeyType_MultiChannel)

	#if ((KeyType&KeyType_Gpio)==KeyType_Gpio||(KeyType&KeyType_SoftLedWithGpio)==KeyType_SoftLedWithGpio)
struct mof_userkey_t gpioKeys;
	#endif
	
	#if ((KeyType&KeyType_McuTouch)==KeyType_McuTouch)
struct mof_userkey_t mcuTouchKeys;
	#endif
	
	#if ((KeyType&KeyType_IR)==KeyType_IR)
struct mof_userkey_t irKeys;
	#endif
	
	#if ((KeyType&KeyType_RF)==KeyType_RF)
struct mof_userkey_t rfKeys;	
	#endif


	#if ((KeyType&KeyType_USER)==KeyType_USER)
struct mof_userkey_t userKeys;	
	#endif


//#endif

void mof_key_init(void)
{


	#if ((KeyType&KeyType_Gpio)==KeyType_Gpio)
		KEYS_IO_INIT; //���а�������Ϊ����//��IO������
	#endif
	
	#if ((KeyType&KeyType_McuTouch)==KeyType_McuTouch)
		mof_touchkeyInit();
	#endif
	
	#if ((KeyType&KeyType_IR)==KeyType_IR)
	
	#endif
	
	#if ((KeyType&KeyType_RF)==KeyType_RF)
		mof_rfkeyInit();
	#endif
	



}

void mof_key_clear(struct mof_userkey_t* ukey)
{
	ukey->UserKeyPressed=0;
	ukey->UserKeyPressed_down=0;
	ukey->UserKeyPressed_up=0;
	ukey->UserKeyLongPressed=0;
}


void mof_keyCheck(struct mof_userkey_t* ukey,unsigned long keysnotpress)
{
	if(keysnotpress!=ukey->KeyVal)
	{

		if(ukey->KeyVal_Ago==ukey->KeyVal)
		{
			ukey->UserKeyPressed=1;
			if(ukey->KeyLongPressCount<1000) ukey->KeyLongPressCount++;
			if(ukey->KeyLongPressCount==5) ukey->UserKeyPressed_down=1;
			if(ukey->KeyLongPressCount==50) ukey->UserKeyLongPressed=1;			
		}
		else
		{
			if(ukey->KeyValQuick_Ago==ukey->KeyVal)
			{
				ukey->KeyQuickPressCount++;
			}
			else
			{
				ukey->KeyQuickPressCount=1;
				ukey->UserKeyRepeatDelay=100;
			}
			ukey->KeyVal_Ago=ukey->KeyVal;
			ukey->UserKeyVal=ukey->KeyVal;
			ukey->UserKeyDat=ukey->KeyDat;

				
			ukey->KeyValQuick_Ago=ukey->KeyVal;
			
			//�˴������㣨ukey->KeyLongPressCount=10��,��ʹ��סһ�����������ٰ������������ͷ�ʱ���ᴥ����ס���ŵ��Ǹ���������,��ʹ�������ʱ����100ms��һ����ʱ��������
			if(ukey->KeyLongPressCount>10) {ukey->KeyLongPressCount=10; ukey->UserKeyLongPressed=0;}

		}	
	}
	else
	{
		ukey->UserKeyPressed=0;
		if(ukey->KeyVal_Ago!=ukey->KeyVal)
		{
			ukey->KeyVal_Ago=ukey->KeyVal;
			if(ukey->KeyLongPressCount>5&&ukey->KeyLongPressCount<200) ukey->UserKeyPressed_up=1;
		}
		
		ukey->KeyLongPressCount=0;

	}
	
	if(ukey->UserKeyRepeatDelay>0)
	{
		 ukey->UserKeyRepeatDelay--; 
		 if(ukey->UserKeyRepeatDelay==0)
			ukey->KeyValQuick_Ago=keysnotpress;
	}
	else {ukey->KeyQuickPressCount=0;}	
}

void mof_keyRun(void)
{
#if ((KeyType&KeyType_Gpio)==KeyType_Gpio)
		gpioKeys.KeyVal=KEYS_IO_VALUE; //��ȡ����ֵ
		mof_keyCheck(&gpioKeys,KEYS_IO_NOTPRESS);
#endif	

#if ((KeyType&KeyType_SoftLedWithGpio)==KeyType_SoftLedWithGpio)
	#ifdef DisplayType
	#if ((DisplayType&DisplayType_SoftLed)==DisplayType_SoftLed) 
	#ifdef DisplayTypeSoftLedModel
		#if (DisplayTypeSoftLedModel==DisplayType_SoftLed_Dig8WithKeys) 
			gpioKeys.KeyVal=softledkey;
            mof_keyCheck(&gpioKeys,KEYS_IO_NOTPRESS);
		#endif
    #endif
    #endif
    #endif    
#endif	


#if ((KeyType&KeyType_McuTouch)==KeyType_McuTouch)

	mof_touchkeyRead(&(mcuTouchKeys.KeyVal));
	mof_keyCheck(&mcuTouchKeys,KEYS_IO_NOTPRESS);
#endif	
#if ((KeyType&KeyType_IR)==KeyType_IR)
	
	mof_keyCheck(&irKeys,KEYS_IO_NOTPRESS);
#endif	
#if ((KeyType&KeyType_RF)==KeyType_RF)
	mof_rfkeyRead(&(rfKeys.KeyVal));
	mof_keyCheck(&rfKeys,KEYS_IO_NOTPRESS);	
			
#endif
	

	

	
}



