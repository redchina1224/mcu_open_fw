#include "..\com_include_drv.h"


unsigned int UserKeyRepeatDelay=0;
//unsigned char UserKeyExRepeatDelay=0;
unsigned char KeyQuickPressCount=0;
unsigned int KeyLongPressCount=0;

//unsigned char KeyExQuickPressCount=0;

//unsigned long KeyVal_NotPress=0;
unsigned long KeyVal=0;
unsigned long KeyValQuick_Ago=0;
unsigned long KeyVal_Ago=0;
unsigned long UserKeyVal=0;

bit UserKeyPressed=0;
bit UserKeyLongPressed=0;
bit UserKeyPressed_down=0;
bit UserKeyPressed_up=0;

//bit UserKeyExPressed=0;




//unsigned int KeyCheckCnt=0;
unsigned int UserKeyCnt=0;
//unsigned int UserKeyExCnt=0;


void zd_key_init(void)
{

		#if (KeyType==KeyType_Gpio)
			KEYS_IO_INPUT; //所有按键设置为输入
			KEYS_IO_WPUA; //打开IO口上拉
		#elif (KeyType==KeyType_McuTouch)
			zd_touchkeyInit();
		#elif (KeyType==KeyType_IR)
		
		#endif

}


void zd_key_clear(void)
{
	UserKeyPressed=0;
	UserKeyPressed_down=0;
  UserKeyPressed_up=0;
  UserKeyLongPressed=0;
}



//10ms调用一次
void zd_keyRun(void)
{
		#if (KeyType==KeyType_Gpio)
	
			KeyVal=KEYS_IO_VALUE; //获取按键值
	
		#elif (KeyType==KeyType_McuTouch)
	
			zd_touchkeyRead(&KeyVal);
	
		#elif (KeyType==KeyType_RF)

			zd_rfkeyRead(&KeyVal);

		#endif
	

	
	if(KEYS_IO_NOTPRESS!=KeyVal)
	{

		if(KeyVal_Ago==KeyVal)
		{
			UserKeyPressed=1;
			if(KeyLongPressCount<1000) KeyLongPressCount++;
			if(KeyLongPressCount==200) UserKeyLongPressed=1;			
		}
		else
		{
			if(KeyValQuick_Ago==KeyVal)
			{
				KeyQuickPressCount++;
				UserKeyRepeatDelay=75;
			}
			else
			{
				KeyQuickPressCount=1;
				UserKeyRepeatDelay=75;
			}
			KeyVal_Ago=KeyVal;
			UserKeyVal=KeyVal;

				
			KeyValQuick_Ago=KeyVal;
			UserKeyPressed_down=1;
			KeyLongPressCount=0;

		}	
	}
	else
	{
		UserKeyPressed=0;
		if(KeyVal_Ago!=KeyVal)
		{
			KeyVal_Ago=KeyVal;
			if(KeyLongPressCount<200) UserKeyPressed_up=1;
		}
		
		KeyLongPressCount=0;
		
	}
	
	if(UserKeyRepeatDelay>0)
	{
		 UserKeyRepeatDelay--; 
		 if(UserKeyRepeatDelay==0)
		 {
			KeyValQuick_Ago=KEYS_IO_NOTPRESS;
		 }
	}
	else {KeyQuickPressCount=0;}
	
}



