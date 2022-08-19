
#include "..\..\com_include_drv.h"
#ifdef DisplayType
#if ((DisplayType&DisplayType_SoftLed)==DisplayType_SoftLed) 
#ifdef DisplayTypeSoftLedModel
#if (DisplayTypeSoftLedModel==DisplayType_SoftLed_Dig8WithKeys) 
#ifndef DisplaySoftLedBrightMax
	#define	DisplaySoftLedBrightMax 40
#endif 

unsigned char LedDrvCaseSelect;
unsigned char *Led_WriteSegBuffer;
const unsigned char *Led_WriteComBuffer;
unsigned char LedBrightSet_Rel=20;
unsigned char LedBrightSet=20;
unsigned char LedBrightCnt;
//unsigned char LedBlinkSegTempVal;
unsigned long softledkey;

#ifdef SoftLed_Dig8WithKeysFilterEnhanced
unsigned char key_filter_cnt=0;
unsigned char key_filter_value=0;
unsigned char key_filter_value_ago=0;
#endif

//在bsp_run中调用，或在中断中调用
void zd_softled_run(void)	
{
	LedBrightCnt++;
	if(LedBrightCnt==LedBrightSet_Rel||LedBrightSet==0)
	{
        	KEYS_IO_INIT;
	}
#ifdef SoftLed_Dig8WithKeysFilterEnhanced
	else if(LedBrightCnt>LedBrightSet_Rel&&LedBrightCnt<=DisplaySoftLedBrightMax)
	{
		if(LedBrightCnt==DisplaySoftLedBrightMax)
		{
		Led_IO_SEG_OUTPUT;
		Led_IO_SEG_CTRL_OFF;
		Led_IO_COM_OUTPUT;
		Led_IO_COM_CTRL_OFF;
		}
		else
		{
					key_filter_value=((unsigned char)(KEYS_IO_VALUE)); //获取按键值
					if(key_filter_value==key_filter_value_ago) 
					{
						if(key_filter_cnt<(SoftLed_Dig8WithKeysFilterEnhanced)) key_filter_cnt++; 
						else
						{
							softledkey=key_filter_value;
						}
					}
					else
					{
						key_filter_value_ago=key_filter_value;
						key_filter_cnt=0;
					}
		}
	}
#else
	else if(LedBrightCnt==DisplaySoftLedBrightMax)
	{
			softledkey=((unsigned long)(KEYS_IO_VALUE));	
		
			Led_IO_SEG_OUTPUT;
			Led_IO_SEG_CTRL_OFF;
			Led_IO_COM_OUTPUT;
			Led_IO_COM_CTRL_OFF;

	}
#endif	
	else if(LedBrightCnt>DisplaySoftLedBrightMax)
	{
		LedBrightCnt=0;
		LedBrightSet_Rel=LedBrightSet;

		if(++LedDrvCaseSelect>=DisplaySoftLedBufferLength) LedDrvCaseSelect=0;
		
		Led_IO_SEG_CTRL(Led_WriteSegBuffer[LedDrvCaseSelect]);
		Led_IO_COM_CTRL(Led_WriteComBuffer[LedDrvCaseSelect]);
	}
}


void zd_softled_init(void)
{ 
	Led_IO_COM_OUTPUT;
	Led_IO_COM_CTRL_OFF;
	Led_IO_SEG_OUTPUT;
	Led_IO_SEG_CTRL_OFF;
	LedDrvCaseSelect=0;
}



void zd_softled_set_bright(unsigned char bright)	
{
#ifdef SoftLed_Dig8WithKeysFilterEnhanced
	if(bright>(DisplaySoftLedBrightMax-SoftLed_Dig8WithKeysFilterEnhanced)) bright=(DisplaySoftLedBrightMax-SoftLed_Dig8WithKeysFilterEnhanced);
#else
	if(bright>(DisplaySoftLedBrightMax)) bright=(DisplaySoftLedBrightMax);
#endif

	//if(bright<1) bright=1;
	
	LedBrightSet=bright;
}

#endif
#endif
#endif
#endif
