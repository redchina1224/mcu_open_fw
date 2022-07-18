
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


//在bsp_run中调用，或在中断中调用
void zd_softled_run(void)	
{
	LedBrightCnt++;
	if(LedBrightCnt==LedBrightSet_Rel||LedBrightSet==0)
	{
        	KEYS_IO_INIT;
	}
	else if(LedBrightCnt>DisplaySoftLedBrightMax)
	{
		LedBrightCnt=0;
		LedBrightSet_Rel=LedBrightSet;
		
		softledkey=((unsigned long)(KEYS_IO_VALUE));
        
		Led_IO_SEG_OUTPUT;
		Led_IO_SEG_CTRL_OFF;
		Led_IO_COM_OUTPUT;
		Led_IO_COM_CTRL_OFF;


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
	if(bright>DisplaySoftLedBrightMax) bright=DisplaySoftLedBrightMax;
	//if(bright<1) bright=1;
	
	LedBrightSet=bright;
}

#endif
#endif
#endif
#endif
