
#include "..\..\com_include_drv.h"

#ifdef DisplayType
#if ((DisplayType&DisplayType_SoftLed)==DisplayType_SoftLed) 
#ifdef DisplayTypeSoftLedModel

unsigned char LedDrvCaseSelect;
unsigned char *Led_WriteSegBuffer;
const unsigned char *Led_WriteComBuffer;

unsigned char LedBrightSet=0;
unsigned char LedBrightCnt;
//unsigned char LedBlinkSegTempVal;


//在bsp_run中调用，或在中断中调用
void zd_softled_run(void)	
{
	

	//显示扫描
	LedDrvCaseSelect++;
	
	//显示移位
	if( LedDrvCaseSelect>18 )
		LedDrvCaseSelect = 1;
		
	//更新显示字节
	LED_CHANEL_OUTPUT;

	switch(LedDrvCaseSelect)
	{
		case 1:
		//B1
			if((Led_WriteSegBuffer[0]&Ex)) {SET_PIN_COM5_OUT_H;}
		//C1
			if((Led_WriteSegBuffer[0]&Fx)) {SET_PIN_COM6_OUT_H;}
		//G1
			if((Led_WriteSegBuffer[0]&Gx)) {SET_PIN_COM7_OUT_H;}
		//H2
			if((Led_WriteSegBuffer[0]&Hx)) {SET_PIN_CC_OUT_H;}
		SET_PIN_BB_OUT_L;
		break;
		case 3:
			//A1
					if((Led_WriteSegBuffer[0]&Dx)) {SET_PIN_COM5_OUT_H;}
			//F1
					if((Led_WriteSegBuffer[0]&Cx)) {SET_PIN_COM6_OUT_H;}
			//E1
					if((Led_WriteSegBuffer[0]&Bx)) {SET_PIN_COM7_OUT_H;}
			//H2
					if((Led_WriteSegBuffer[1]&Hx)) {SET_PIN_AA_OUT_H;}
			//D1
					if((Led_WriteSegBuffer[0]&Ax)) {SET_PIN_BB_OUT_H;}
			SET_PIN_CC_OUT_L;
		break;
		case 5:
			//F2
				if((Led_WriteSegBuffer[1]&Cx)) {SET_PIN_COM5_OUT_H;}
			//A2
				if((Led_WriteSegBuffer[1]&Dx)) {SET_PIN_COM6_OUT_H;}
			//G2
				if((Led_WriteSegBuffer[1]&Gx)) {SET_PIN_AA_OUT_H;}
			//C2
				if((Led_WriteSegBuffer[1]&Fx)) {SET_PIN_BB_OUT_H;}
			//B2
				if((Led_WriteSegBuffer[1]&Ex)) {SET_PIN_CC_OUT_H;}
			SET_PIN_COM7_OUT_L;
		break;
		case 7:
			//E2
						if((Led_WriteSegBuffer[1]&Bx)) {SET_PIN_COM5_OUT_H;}
			//D2
						if((Led_WriteSegBuffer[1]&Ax)) {SET_PIN_COM7_OUT_H;}
			//C3
						if((Led_WriteSegBuffer[2]&Fx)) {SET_PIN_AA_OUT_H;}
			//G3
						if((Led_WriteSegBuffer[2]&Gx)) {SET_PIN_BB_OUT_H;}
			//H3
						if((Led_WriteSegBuffer[2]&Hx)) {SET_PIN_CC_OUT_H;}
			SET_PIN_COM6_OUT_L;
		break;
		case 9:
			//D3
						if((Led_WriteSegBuffer[2]&Ax)) {SET_PIN_COM6_OUT_H;}
		//E3
						if((Led_WriteSegBuffer[2]&Bx)) {SET_PIN_COM7_OUT_H;}
		//B3
						if((Led_WriteSegBuffer[2]&Ex)) {SET_PIN_AA_OUT_H;}			
		//A3
						if((Led_WriteSegBuffer[2]&Dx)) {SET_PIN_BB_OUT_H;}
		//F3
						if((Led_WriteSegBuffer[2]&Cx)) {SET_PIN_CC_OUT_H;}
			SET_PIN_COM5_OUT_L;
		break;
		case 11:
		if((Led_WriteSegBuffer[4]&Dx)) {SET_PIN_COM2_OUT_H;}//LED8
		if((Led_WriteSegBuffer[3]&Fx)) {SET_PIN_COM3_OUT_H;}//LED10
		if((Led_WriteSegBuffer[4]&Fx)) {SET_PIN_COM4_OUT_H;}//LED12
		
		SET_PIN_COM1_OUT_L;
		break;
		case 13:
		if((Led_WriteSegBuffer[3]&Dx)) {SET_PIN_COM1_OUT_H; }//LED7
		if((Led_WriteSegBuffer[4]&Ex)) {SET_PIN_COM3_OUT_H; }//LED9
		if((Led_WriteSegBuffer[3]&Ex)) {SET_PIN_COM4_OUT_H; }//LED11
		
		SET_PIN_COM2_OUT_L;
		break;
		case 15:
		if((Led_WriteSegBuffer[3]&Bx)) {SET_PIN_COM2_OUT_H;}//LED4
		if((Led_WriteSegBuffer[4]&Ax)) {SET_PIN_COM1_OUT_H;}//LED2
		if((Led_WriteSegBuffer[3]&Cx)) {SET_PIN_COM4_OUT_H;}//LED6
		
		SET_PIN_COM3_OUT_L;
		break;
		case 17:
		if((Led_WriteSegBuffer[4]&Cx)) {SET_PIN_COM2_OUT_H; }//LED3
		if((Led_WriteSegBuffer[4]&Bx)) {SET_PIN_COM3_OUT_H; }//LED5
		if((Led_WriteSegBuffer[3]&Ax)) {SET_PIN_COM1_OUT_H; }//LED1
		
		SET_PIN_COM4_OUT_L;
		break;
		
		default:

			LED_CHANEL_OUTPUT;
		break;
		
		
	}
	
	







}


void zd_softled_init(void)
{ 
	LED_CHANEL_OUTPUT
	LedDrvCaseSelect=0;
	
}



void zd_softled_set_bright(unsigned char bright)	
{
	if(bright>10) bright=10;
	if(bright<1) bright=1;
	
	LedBrightSet=bright;
}

#endif
#endif
#endif
