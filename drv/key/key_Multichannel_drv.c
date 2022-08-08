#include "..\com_include_drv.h"


//#if ((KeyType&KeyType_MultiChannel)==KeyType_MultiChannel)

	#if ((KeyType&KeyType_Gpio)==KeyType_Gpio||(KeyType&KeyType_SoftLedWithGpio)==KeyType_SoftLedWithGpio)
struct zd_userkey_t gpioKeys;
	#endif
	
	#if ((KeyType&KeyType_McuTouch)==KeyType_McuTouch)
struct zd_userkey_t mcuTouchKeys;
	#endif
	
	#if ((KeyType&KeyType_IR)==KeyType_IR)
struct zd_userkey_t irKeys;
	#endif
	
	#if ((KeyType&KeyType_RF)==KeyType_RF)
struct zd_userkey_t rfKeys;	
	#endif
	
//#endif

void zd_key_init(void)
{


	#if ((KeyType&KeyType_Gpio)==KeyType_Gpio)
		KEYS_IO_INPUT; //所有按键设置为输入
		KEYS_IO_WPUA; //打开IO口上拉
	#endif
	
	#if ((KeyType&KeyType_McuTouch)==KeyType_McuTouch)
		zd_touchkeyInit();
	#endif
	
	#if ((KeyType&KeyType_IR)==KeyType_IR)
	
	#endif
	
	#if ((KeyType&KeyType_RF)==KeyType_RF)
		zd_rfkeyInit();
	#endif
	



}

void zd_key_clear(struct zd_userkey_t* ukey)
{
	ukey->UserKeyPressed=0;
	ukey->UserKeyPressed_down=0;
	ukey->UserKeyPressed_up=0;
	ukey->UserKeyLongPressed=0;
}


void zd_keyCheck(struct zd_userkey_t* ukey,unsigned long keysnotpress)
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

				
			ukey->KeyValQuick_Ago=ukey->KeyVal;
			ukey->KeyLongPressCount=0;

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

void zd_keyRun(void)
{
#if (KeyType&KeyType_Gpio)==KeyType_Gpio)
		gpioKeys.KeyVal=KEYS_IO_VALUE; //获取按键值
		zd_keyCheck(&gpioKeys,KEYS_IO_NOTPRESS);
#endif	

#if (KeyType&KeyType_SoftLedWithGpio)==KeyType_SoftLedWithGpio)
	#ifdef DisplayType
	#if ((DisplayType&DisplayType_SoftLed)==DisplayType_SoftLed) 
	#ifdef DisplayTypeSoftLedModel
		#if (DisplayTypeSoftLedModel==DisplayType_SoftLed_Dig8WithKeys) 
			gpioKeys.KeyVal=softledkey;
            zd_keyCheck(&gpioKeys,KEYS_IO_NOTPRESS);
		#endif
    #endif
    #endif
    #endif    
#endif	


#if (KeyType&KeyType_McuTouch)==KeyType_McuTouch)

	zd_touchkeyRead(&(mcuTouchKeys.KeyVal));
	zd_keyCheck(&mcuTouchKeys,KEYS_IO_NOTPRESS);
#endif	
#if (KeyType&KeyType_IR)==KeyType_IR)
	
	zd_keyCheck(&irKeys,KEYS_IO_NOTPRESS);
#endif	
#if (KeyType&KeyType_RF)==KeyType_RF)
	zd_rfkeyRead(&(rfKeys.KeyVal));
	zd_keyCheck(&rfKeys,KEYS_IO_NOTPRESS);	
			
#endif
	

	

	
}



