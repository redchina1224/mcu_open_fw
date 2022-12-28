
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

unsigned char LedBrightSet=0;
unsigned char LedBrightCnt;
//unsigned char LedBlinkSegTempVal;
unsigned long softledkey;

#ifdef DisplaySoftLedBrightBreath
unsigned char *Led_WriteSegBreathMask;
unsigned char LedBreathBrightSet;
unsigned char LedBreathBrightSet_Rel=0;
#endif 

#ifdef SoftLed_Dig8WithKeysFilterEnhanced
unsigned char key_filter_cnt=0;
unsigned char key_filter_value=0;
unsigned char key_filter_value_ago=0;
#endif


//��bsp_run�е��ã������ж��е���
void zd_softled_run(void)	
{
	
	if(++LedBrightCnt>DisplaySoftLedBrightMax)
	{
		LedBrightCnt=0;
#ifdef DisplaySoftLedBrightBreath
		LedBreathBrightSet_Rel=LedBreathBrightSet;
#endif
		Led_IO_COM_CTRL_OFF;
		Led_IO_SEG_OUTPUT;
		Led_IO_SEG_CTRL_OFF;

		if(++LedDrvCaseSelect>=DisplaySoftLedBufferLength) LedDrvCaseSelect=0;
		
		Led_IO_SEG_CTRL(Led_WriteSegBuffer[LedDrvCaseSelect]);

		#ifdef DisplaySoftLedBrightBreath
		if(LedBrightCnt==LedBreathBrightSet_Rel)
		{
			Led_IO_SEG_CLR(Led_WriteSegBreathMask[LedDrvCaseSelect]);
		}
		#endif 
	
		Led_IO_COM_CTRL(Led_WriteComBuffer[LedDrvCaseSelect]);
	}
	else if(LedBrightCnt>=LedBrightSet)
	{
		if(LedBrightCnt==LedBrightSet)
		{
			Led_IO_COM_CTRL_OFF;
			KEYS_IO_FORCE_PULL;
			KEYS_IO_INIT;
		}
		else
		{
#ifdef SoftLed_Dig8WithKeysFilterEnhanced
			//���ȡֵȥ��--������LedBrightSetʱ����Ϊ����,��LedBrightSet+1����������DisplaySoftLedBrightMaxʱ���ж�����ֵ��С��SoftLed_Dig8WithKeysFilterEnhancedʱȡֵ,��ʾ��DisplaySoftLedBrightMax+1ʱ������
			key_filter_value=((unsigned char)(KEYS_IO_VALUE)); //��ȡ����ֵ
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
#else
			//ֻȡһ��ֵ--������LedBrightSetʱ����Ϊ����,��DisplaySoftLedBrightMaxʱ��ȡֵ,��ʾ��DisplaySoftLedBrightMax+1ʱ������
			if(LedBrightCnt==DisplaySoftLedBrightMax)
			{
					softledkey=((unsigned long)(KEYS_IO_VALUE));	
			}
#endif
		}

	}
#ifdef DisplaySoftLedBrightBreath
	else if(LedBrightCnt==LedBreathBrightSet_Rel)
	{
		Led_IO_SEG_CLR(Led_WriteSegBreathMask[LedDrvCaseSelect]);
	}
#endif 	


}


void zd_softled_init(void)
{ 
	Led_IO_COM_OUTPUT;
	Led_IO_COM_CTRL_OFF;
	Led_IO_SEG_OUTPUT;
	Led_IO_SEG_CTRL_OFF;
	LedDrvCaseSelect=0;
}

#ifdef DisplaySoftLedBrightBreath
void zd_softled_set_breathbright(unsigned char bright)	
{
	if(bright>(LedBrightSet)) bright=(LedBrightSet);
	
	LedBreathBrightSet=bright;
}
#endif 



void zd_softled_set_bright(unsigned char bright)	
{
#ifdef SoftLed_Dig8WithKeysFilterEnhanced
	if(bright>(DisplaySoftLedBrightMax-SoftLed_Dig8WithKeysFilterEnhanced-1)) bright=(DisplaySoftLedBrightMax-SoftLed_Dig8WithKeysFilterEnhanced-1); //LedBrightSet ���ֵΪDisplaySoftLedBrightMax-1,������LedBrightSetʱ����Ϊ����,��LedBrightSet+1����������DisplaySoftLedBrightMaxʱ���ж�ȡֵ,��ʾ��DisplaySoftLedBrightMax+1ʱ������
#else
	if(bright>(DisplaySoftLedBrightMax-1)) bright=(DisplaySoftLedBrightMax-1); //LedBrightSet ���ֵΪDisplaySoftLedBrightMax-1,������LedBrightSetʱ����Ϊ����,��DisplaySoftLedBrightMaxʱ��ȡֵ,��ʾ��DisplaySoftLedBrightMax+1ʱ������
#endif	
	if(bright<1) LedBrightSet=1; else LedBrightSet=bright; //LedBrightSet ��СֵΪ1

#ifdef DisplaySoftLedBrightBreath //���º�������ֵ,��ֵ���ܴ���LedBrightSet
	zd_softled_set_breathbright(LedBreathBrightSet);
#endif 
}

#endif
#endif
#endif
#endif
