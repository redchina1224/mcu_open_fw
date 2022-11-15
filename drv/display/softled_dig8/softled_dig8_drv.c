
#include "..\..\com_include_drv.h"

#ifdef DisplayType
#if ((DisplayType&DisplayType_SoftLed)==DisplayType_SoftLed) 
#ifdef DisplayTypeSoftLedModel

#ifndef DisplaySoftLedBrightMax
	#define	DisplaySoftLedBrightMax 40
#endif 

unsigned char LedDrvCaseSelect;
unsigned char *Led_WriteSegBuffer;
const unsigned char *Led_WriteComBuffer;
unsigned char LedBrightSet=0;
unsigned char LedBrightCnt;
//unsigned char LedBlinkSegTempVal;

#ifdef DisplaySoftLedBrightBreath
unsigned char *Led_WriteSegBreathMask;
unsigned char LedBreathBrightSet=0;
#endif 


//在bsp_run中调用，或在中断中调用
void zd_softled_run(void)	
{
	
	if(++LedBrightCnt>DisplaySoftLedBrightMax)
	{
		LedBrightCnt=0;
		
		Led_IO_COM_CTRL_OFF;
		Led_IO_SEG_CTRL_OFF;

		if(++LedDrvCaseSelect>=DisplaySoftLedBufferLength) LedDrvCaseSelect=0;
		
		Led_IO_SEG_CTRL(Led_WriteSegBuffer[LedDrvCaseSelect]);
		Led_IO_COM_CTRL(Led_WriteComBuffer[LedDrvCaseSelect]);
	}
	else if(LedBrightCnt==LedBrightSet)
	{
		Led_IO_COM_CTRL_OFF;
		Led_IO_SEG_CTRL_OFF;
	}
#ifdef DisplaySoftLedBrightBreath
	else if(LedBrightCnt==LedBreathBrightSet)
	{
		Led_IO_SEG_CTRL((Led_WriteSegBuffer[LedDrvCaseSelect]&Led_WriteSegBreathMask[LedDrvCaseSelect]));
	}
#endif 	


/*
COM0_PIN=0;
COM1_PIN=0;


SEG_D_PIN=1;
SEG_E_PIN=1;
SEG_A_PIN=1;
SEG_B_PIN=1;
SEG_C_PIN=1;
SEG_G_PIN=1;
SEG_F_PIN=1;
*/
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
	if(bright<1) bright=1;
	
	LedBrightSet=bright;
}



#ifdef DisplaySoftLedBrightBreath
void zd_softled_set_breathbright(unsigned char bright)	
{
	if(bright>DisplaySoftLedBrightMax) bright=DisplaySoftLedBrightMax;
	if(bright<1) bright=1;
	
	LedBreathBrightSet=bright;
}
#endif 



#endif
#endif
#endif
