#ifndef _TK_API_C_
#define _TK_API_C_

/*********************************************************************************************************************/
#include "ca51f_config.h"
#include "includes\CA51F005SFR.h"
#include "includes\CA51F005XSFR.h"
#include "includes\gpiodef.h"

#include "Library\Includes\tmc.h"		
#include "Library\Includes\system_clock.h"		
#include "Library\includes\uart.h"
#include "includes\system.h"
#include "Library\includes\delay.h"
#include <intrins.h>
/*********************************************************************************************************************/
#include "TS_Lib\Includes\ts_configuration.h"
#include "TS_Lib\Includes\ts_def.h"
#include "TS_Lib\Includes\ts_api.h"
#include "TS_Lib\Includes\ts_service.h"		   
/*********************************************************************************************************************/
void Debug_init(void);
void Debug_ParamLoad(void);

#if SUPPORT_KEY
code unsigned int TS_KEY_CH_INFO_SEQ[][2]=
{
	KEY_SEQ
};
#endif

code unsigned char WHEEL_SLIDER0_MAX_MIN_TAB[1]={0};


#if SUPPORT_KEY	
code TYPE_SN MASK_TAB[]=
{
	0x000001,
#if (KEY_CH_COUNT > 1)
	0x000002,
#endif
#if (KEY_CH_COUNT > 2)
	0x000004,
#endif
#if (KEY_CH_COUNT > 3)
	0x000008,
#endif
#if (KEY_CH_COUNT > 4)
	0x000010,
#endif
#if (KEY_CH_COUNT > 5)
	0x000020,
#endif
#if (KEY_CH_COUNT > 6)
	0x000040,
#endif
#if (KEY_CH_COUNT > 7)
	0x000080,
#endif
#if (KEY_CH_COUNT > 8)
	0x000100,
#endif
#if (KEY_CH_COUNT > 9)
	0x000200,
#endif
#if (KEY_CH_COUNT > 10)
	0x000400,
#endif
#if (KEY_CH_COUNT > 11)
	0x000800,
#endif
#if (KEY_CH_COUNT > 12)
	0x001000,
#endif
#if (KEY_CH_COUNT > 13)
	0x002000,
#endif
#if (KEY_CH_COUNT > 14)
	0x004000,
#endif
#if (KEY_CH_COUNT > 15)
	0x008000,
#endif

};
code unsigned char AREA_CONFIRM_TIME_TAB[]=
{
	FINGER_TOUCH_CONFIRM_TIME,
	AREA_PNOISE_PLUS_CONFIRM_TIME,
	AREA_PNOISE_CONFIRM_TIME,
	AREA_NNOISE_CONFIRM_TIME,
	AREA_OVERLOW_CONFIRM_TIME,
};
#else
code unsigned char AREA_CONFIRM_TIME_TAB[1]={0};
code unsigned long int MASK_TAB[1]={0};
#endif
void TS_MS_ISR (void)
{
	static unsigned char xdata ms_cnt = 0;
	unsigned char i;

	ms_cnt++;
	if(ms_cnt >= 4)
	{
		ms_cnt = 0;
		for(i = 0; i < TS_Cnt; i++)
		{
			if(TS_AreaConfirmTimer[i])
			{
				TS_AreaConfirmTimer[i]--;
			}
		}

#if SUPPORT_KEY
#if SUPPORT_COVER_PANAL_AFTER_POWERON
		if(PanalCoverJudgeTimer) PanalCoverJudgeTimer--;
#endif
#endif
#if SUPPORT_KEY
#if ANTI_SPEAKER_EN
		if(RefChDataTimer) RefChDataTimer--;
#endif
#endif
	}	
}
void TS_HS_ISR (void)
{
#if SUPPORT_KEY
#if (FINGER_LONG_TOUCH_TIME_LIMIT > 0)
	unsigned char i;
#endif
#endif

	TS_HalfSecCnt++;
	
#if SUPPORT_KEY
#if (FINGER_LONG_TOUCH_TIME_LIMIT > 0)
	for(i = 0; i < KEY_CH_COUNT; i++)
	{
		if(TSKey_LongTouchLimitTimer[i])
		{
			TSKey_LongTouchLimitTimer[i]--;
		}
	}		
#endif
#endif

	if(TS_RefCHBaseLineAdjuTimer)
	{
		TS_RefCHBaseLineAdjuTimer--;
	}	
	if(EnterStopScanTimer)
	{
		EnterStopScanTimer--;
	}	
}
void TS_ISR (void)
{	
	unsigned char i;
	WORD_UNION TS_Data[6];

	if(TKIF & TKIF0)
	{
		TKIF = TKIF0; 
		TS_Data[0].bVal[0] = TK0MSH;
		TS_Data[0].bVal[1] = TK0MSL;
	}
	if(TKIF & TKIF1)
	{
		TKIF = TKIF1; 	
		TS_Data[1].bVal[0] = TK1MSH;
		TS_Data[1].bVal[1] = TK1MSL;	
	}
	if(TKIF & TKIF2)
	{
		TKIF = TKIF2; 	
		TS_Data[2].bVal[0] = TK2MSH;
		TS_Data[2].bVal[1] = TK2MSL;
	}
	if(TKIF & TKIF3)
	{
		TKIF = TKIF3; 	
		TS_Data[3].bVal[0] = TK3MSH;
		TS_Data[3].bVal[1] = TK3MSL;	
	}
	if(TKIF & TKIF4)
	{
		TKIF = TKIF4; 	
		TS_Data[4].bVal[0] = TK4MSH;
		TS_Data[4].bVal[1] = TK4MSL;
	}
	if(TKIF & TKIF5)
	{
		TKIF = TKIF5; 	
		TS_Data[5].bVal[0] = TK5MSH;
		TS_Data[5].bVal[1] = TK5MSL;
	}
	
	for(i = 0; i < 6; i++)
	{
#if (TS_ACQ_TIMES == 1)
		TS_RawData[TS_Index+i] = TS_Data[i].wVal;
#else
		TS_DataSum[TS_Index+i] += TS_Data[i].wVal;	
#endif		

		if(TS_Index+i == TS_Cnt)
		{			
			break;
		}	

	}

	if(TS_Index+6 > TS_Cnt)
	{
#if (TS_ACQ_TIMES == 1)
		TS_CycleScanDoneFlag = 1;	
#else
		TS_Acq_Counter++;
		if(TS_Acq_Counter >= TS_ACQ_TIMES)
		{
			for(i = 0; i < TS_Cnt+1; i++)
			{
				TS_RawData[i] = TS_DataSum[i];
				TS_DataSum[i] = 0;
			}
			TS_CycleScanDoneFlag = 1;		
			TS_Acq_Counter = 0;
		}	
#endif		
		TS_Index = 0;
	}
	else 
	{
		TS_Index += 6;
	}
	if(!TS_CycleScanDoneFlag)
	{
		TS_ScanStart();	
	}
	if(TS_HalfSecCnt) TS_HalfSecCnt--;
	if(MainLoopCnt1 != MainLoopCnt2)
	{
		MainLoopCnt2 = MainLoopCnt1;
		WDFLG = 0xA5;
	}
}
void TS_DataFiltering(void)
{
	unsigned char i;
#if (FILTER_COUNT > 1)
	unsigned char j;
	unsigned int DataSum,DataMax,DataMin;
#endif
	for(i = 0; i < TS_Cnt+1; i++)
	{
#if (FILTER_COUNT == 1)
		TS_PostData[i] = TS_RawData[i];
#else
		TS_FilterPosIdx[i]++;
		if(TS_FilterPosIdx[i] >= FILTER_COUNT) 
		{
			TS_FilterPosIdx[i] = 0;
		}
		INT3EN = 0;
		TS_FilterBuf[i][TS_FilterPosIdx[i]] = TS_RawData[i];
		INT3EN = 1; 
		
		DataSum = 0;
		DataMax = 0;
		DataMin = 0xFFFF;
	 	for(j = 0; j < FILTER_COUNT; j++)
		{
			DataSum += TS_FilterBuf[i][j];
#if (FILTER_COUNT > 2)
			if(TS_FilterBuf[i][j] > DataMax)
			{
				DataMax = TS_FilterBuf[i][j];
			}
			if(TS_FilterBuf[i][j] < DataMin)
			{
				DataMin = TS_FilterBuf[i][j];
			}
#endif
		}
#if (FILTER_COUNT == 2)
		TS_PostData[i] = (DataSum)/(FILTER_COUNT);	
#else
		TS_PostData[i] = (DataSum - DataMax - DataMin)/(FILTER_COUNT-2);	
#endif
#endif		
 	}		
}
#if SUPPORT_KEY
#if ANTI_SPEAKER_EN
bit TS_RefChAbnormalJudge(void)
{
	unsigned int ref_value,crt_value,delta;
	
	if(RefChDataBufIdx == (REF_CH_DATA_BUF_SIZE-1)) 
	{
		ref_value = RefChDataBuf[0];
	}
	else
	{
		ref_value = RefChDataBuf[RefChDataBufIdx + 1];
	}
	crt_value = TS_PostData[OPENED_TS_COUNT];
	if(ref_value > crt_value)
	{
		delta = ref_value - crt_value;
	}
	else
	{
		delta = crt_value - ref_value;
	}
	if(delta >= REF_CH_ABNORMAL_THD)			
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
void TS_RefChCheck(void)
{
	if(!RefChDataTimer)
	{
		RefChDataTimer = 3;
		RefChDataBufIdx++;
		if(RefChDataBufIdx >= REF_CH_DATA_BUF_SIZE)
		{
			RefChDataBufIdx = 0;
		}
		RefChDataBuf[RefChDataBufIdx] = TS_PostData[OPENED_TS_COUNT];
	}	
}
#endif
#if TOUCH_SENSITIVITY_AUTO_BALANCE_EN
unsigned char GetSensAutoTrimRefCH(unsigned int *baseLine)
{
	unsigned char i,idx;
	unsigned int min = 0xffff;
	for(i = 0; i < TS_Cnt; i++)
	{
		if(baseLine[i] < min)
		{
			min = baseLine[i];
			idx = i;
		}
	}
	return idx;
}
#endif
#endif
void TS_RunInit(void)
{
	unsigned char i,j;
	static unsigned char TS_ScanTimes=0;
#if (POWER_ON_WAIT_TK_STABLE_EN)
	static unsigned char TS_Init_Step_Sub;
#endif
	if(TS_Init_Step == 0)
	{
#if (TS_ACQ_TIMES > 1)
		for(i = 0; i < TS_Cnt; i++)
		{	
			TS_DataSum[i] = 0;
		}
		TS_Acq_Counter = 0;
#endif
		TS_CycleScanDoneFlag = 0;
		TS_HalfSecCnt = 0;
		TS_Index = 0;
		TS_ScanStart();	
#if POWER_ON_WAIT_TK_STABLE_EN
		TS_Init_Step = 1;		
		TS_Init_Step_Sub = 0;
		TS_ScanTimes = 5;
#else
		TS_Init_Step = 2;
		TS_ScanTimes = 50;			
#endif
	}
#if POWER_ON_WAIT_TK_STABLE_EN
	else if(TS_Init_Step == 1)
	{
		if(TS_CycleScanDoneFlag)
		{
			TS_CycleScanDoneFlag = 0;
			if(TS_Init_Step_Sub == 0)
			{
				if(--TS_ScanTimes)
				{				
					TS_Index = 0;
					TS_ScanStart();		
					return;
				}
				for(i = 0; i < TS_Cnt+1; i++)
				{
					TS_PostData[i] = TS_RawData[i];
				}
				TS_Init_Step_Sub = 1;
				TS_AreaConfirmTimer[0] = 40;
			}			
			else if(TS_Init_Step_Sub == 1)
			{
				if(!TS_AreaConfirmTimer[0])
				{
					int delta;
					for(i = 0; i < TS_Cnt+1; i++)
					{
						delta = (int)TS_PostData[i] - (int)TS_RawData[i];
						if((delta > NOISE_THRESHOLD) || (delta < -NOISE_THRESHOLD))
						{
							TS_Init_Step_Sub = 0;
							return;
						}
					}			
					TS_Init_Step = 2;
					TS_ScanTimes = 10;	
				}
			}
			TS_Index = 0;
			TS_ScanStart();	
		}
	}
#endif
	else if(TS_Init_Step == 2)
	{
		if(TS_CycleScanDoneFlag)
		{
			TS_CycleScanDoneFlag = 0;
			if(--TS_ScanTimes)
			{				
				TS_Index = 0;
				TS_ScanStart();		
				return;
			}
			TS_RefCHBaseLineAdjuTimer = 0;
			for(i = 0; i < TS_Cnt+1; i++)
			{	
				for(j = 0; j < FILTER_COUNT; j++)
				{
					TS_FilterBuf[i][j] = TS_RawData[i];
				}
				TS_FilterPosIdx[i] = 0;
				
				if(i == TS_Cnt) break;
				TS_BaseLineData[i] = TS_RawData[i];			
				TS_FirstAreaData[i] = TS_RawData[i]; 
#if SUPPORT_KEY
#if TOUCH_SENSITIVITY_AUTO_BALANCE_EN
				TS_PostData2[i] = TS_RawData[i];
#endif				
#if TK_BASE_TRIM_WHILE_KEY_PRESSED
				RefChDataBak[i] = TS_RawData[OPENED_TS_COUNT];
				TS_BaseLineDataBak[i] = TS_BaseLineData[i];
#endif	
#endif				
#if SUPPORT_KEY
				TSKey_FingerThd[i] = TS_KEY_CH_INFO_SEQ[i][1];
				TS_AreaConfirmTimerSet(i,AREA_PNOISE);				
#endif
			}	
#if SUPPORT_KEY
#if TOUCH_SENSITIVITY_AUTO_BALANCE_EN
			SensAutoTrimRefCH = GetSensAutoTrimRefCH(TS_BaseLineData);
#endif
#if ANTI_SPEAKER_EN
			for(i = 0; i < REF_CH_DATA_BUF_SIZE; i++)
			{
				RefChDataBuf[i] = TS_PostData[OPENED_TS_COUNT];
			}
			RefChDataBufIdx = 0;
#endif		
#endif			
			TS_Index = 0;
			TS_ScanStart();	
			TS_State = TS_DEAL;	
		}
	}
}

#if SUPPORT_ANTI_WATER_FUNCTION
unsigned char AntiWaterModeGetMaxDeltaCh(void)
{
	unsigned char i;
	unsigned long int CalcTemp1;
	unsigned int CalcTemp2,CalcTemp3;
	int Delta;
	int max_delta;
	char max_index;
	max_delta = 0;
	for(i = 0; i < KEY_CH_COUNT; i++)
	{
		if(i == 0)
		{
			Delta = (int)TS_BaseLineData[i] - (int)TS_PostData[i];
		}
		else
		{
			CalcTemp1 = 	(unsigned long int)TS_PostData[i] * (unsigned long int)TS_BaseLineData[0];
			CalcTemp2 =  	(unsigned int)(CalcTemp1/TS_BaseLineData[i]);
			CalcTemp3 = 	TS_PostData[i] + TS_BaseLineData[0] - CalcTemp2;
			CalcTemp2 = 	(unsigned int)(CalcTemp1/CalcTemp3);	
			Delta 		= 	(int)TS_BaseLineData[0] - (int)CalcTemp2;						
		}
		if(max_delta < Delta)
		{
			max_delta = Delta;
			max_index = i;
		}
	}
	return max_index;
}
#endif
#endif
#if SUPPORT_KEY
#if TOUCH_SENSITIVITY_AUTO_BALANCE_EN
int GetTouchDiffer(unsigned int touchData,unsigned int touchBase,unsigned int baseRef)
{
	unsigned long int CalcTemp1;
	unsigned int CalcTemp2,CalcTemp3;
	int Delta;

	CalcTemp1 = 	(unsigned long int)touchData * (unsigned long int)baseRef;
	CalcTemp2 =  	(unsigned int)(CalcTemp1/touchBase);
	CalcTemp3 = 	touchData + baseRef - CalcTemp2;
	CalcTemp2 = 	(unsigned int)(CalcTemp1/CalcTemp3);	
	Delta 		= 	(int)baseRef - (int)CalcTemp2;						

	return Delta;
}
#endif
void TSKey_DataDeal(void)
{
	unsigned char i;
	unsigned char  TouchArea,NowArea;		

#if SUPPORT_COVER_PANAL_AFTER_POWERON
	unsigned char PanalToggleCount = 0;
#endif
	for(i = 0; i < KEY_CH_COUNT; i++)
	{	
#if SUPPORT_ANTI_WATER_FUNCTION
		if(KeyPressedFlag)
		{
			if(PressedKeyIndex != i)
			{
				TS_FirstAreaData[i] = TS_BaseLineData[i];
				TS_AreaConfirmTimerSet(i,AREA_PNOISE);		
				continue;		
			}
		}
#endif
#if TOUCH_SENSITIVITY_AUTO_BALANCE_EN
		if(SensAutoTrimRefCH == i)
		{
			TS_PostData2[i] = TS_PostData[i];
		}
		else
		{
			TS_PostData2[i] = (int)TS_BaseLineData[i] - GetTouchDiffer(TS_PostData[i],TS_BaseLineData[i],TS_BaseLineData[SensAutoTrimRefCH]);
		}
#endif
		TouchArea = TS_GetDataArea(i,TS_FirstAreaData[i],NOISE_THRESHOLD,(bit)(PreKeysFlagSN & MASK_TAB[i]));
#if TOUCH_SENSITIVITY_AUTO_BALANCE_EN
		NowArea   = TS_GetDataArea(i,TS_PostData2[i],NOISE_THRESHOLD,(bit)(PreKeysFlagSN & MASK_TAB[i]));
#else
		NowArea   = TS_GetDataArea(i,TS_PostData[i],NOISE_THRESHOLD,(bit)(PreKeysFlagSN & MASK_TAB[i]));
#endif
		
		if((NowArea != AREA_PNOISE)&&(NowArea != AREA_NNOISE))
		{
			TS_StableFlag = 0;		
		}
#if SUPPORT_COVER_PANAL_AFTER_POWERON
		if((NowArea == AREA_PNOISE_PLUS) || (NowArea == AREA_FINGER_TOUCH))
		{
			PanalToggleCount++;
		}
#endif
		if(TouchArea == AREA_FINGER_TOUCH)
		{
			if(NowArea == AREA_FINGER_TOUCH)
			{
				if(!(PreKeysFlagSN & MASK_TAB[i]))
				{
					if(!TS_AreaConfirmTimer[i])
					{		
						PreKeysFlagSN |= MASK_TAB[i];		
#if (FINGER_LONG_TOUCH_TIME_LIMIT > 0)
						TSKey_LongTouchLimitTimer[i] = FINGER_LONG_TOUCH_TIME_LIMIT;
#endif
						TS_AreaConfirmTimer[i] = FINGER_TOUCH_RELEASE_CONFIRM_TIME;	
					}
				}
				else
				{	
#if SUPPORT_ANTI_WATER_FUNCTION		
					if(i != AntiWaterModeGetMaxDeltaCh())
					{
						goto ANTI_WATER_MODE_KEY_RELEASE;
					}
#endif
					
#if TK_BASE_TRIM_WHILE_KEY_PRESSED					
					TS_BaseLineData[i] = ((unsigned long int)TS_BaseLineDataBak[i]*TS_PostData[OPENED_TS_COUNT])/RefChDataBak[i];
#endif		
					
					TS_AreaConfirmTimer[i] = FINGER_TOUCH_RELEASE_CONFIRM_TIME;
#if (FINGER_LONG_TOUCH_TIME_LIMIT > 0)
					if(!TSKey_LongTouchLimitTimer[i])
					{
						PreKeysFlagSN &= ~MASK_TAB[i];
						TS_FirstAreaData[i] = TS_PostData[i];
						TS_BaseLineData[i] 	= TS_PostData[i];

						TS_AreaConfirmTimerSet(i,AREA_PNOISE);		
#if SUPPORT_ANTI_WATER_FUNCTION
						KeyPressedFlag = 0;
						break;
#endif						
					}							
#endif					
				}				
			}
			else
			{
				if(PreKeysFlagSN & MASK_TAB[i]) 
				{
					if(!TS_AreaConfirmTimer[i])
					{
#if SUPPORT_ANTI_WATER_FUNCTION
ANTI_WATER_MODE_KEY_RELEASE:						
						KeyPressedFlag = 0;
#endif
						PreKeysFlagSN &= ~MASK_TAB[i];

						TS_FirstAreaData[i] = TS_BaseLineData[i];
						TS_AreaConfirmTimerSet(i,AREA_PNOISE);
#if SUPPORT_ANTI_WATER_FUNCTION
						break;
#endif
					}					
				}			
				else
				{
#if TOUCH_SENSITIVITY_AUTO_BALANCE_EN
					TS_FirstAreaData[i] = TS_PostData2[i];
#else
					TS_FirstAreaData[i] = TS_PostData[i];
#endif
					TS_AreaConfirmTimerSet(i,NowArea);
				}	
			}	
			continue;						
		}	
		else
		{
			if(NowArea == AREA_FINGER_TOUCH)
			{
#if TOUCH_SENSITIVITY_AUTO_BALANCE_EN
				TS_FirstAreaData[i] = TS_PostData2[i];
#else
				TS_FirstAreaData[i] = TS_PostData[i];
#endif
				TS_AreaConfirmTimerSet(i,AREA_FINGER_TOUCH);
				continue;		
			}	
		}
		if(PreKeysFlagSN != 0) 
		{
			TS_FirstAreaData[i] = TS_BaseLineData[i];
			TS_AreaConfirmTimerSet(i,AREA_PNOISE);		
			continue;			
		}
#if TOUCH_SENSITIVITY_AUTO_BALANCE_EN
		if(TS_AreaDeviateDetection(TS_FirstAreaData[i],TS_PostData2[i],NOISE_THRESHOLD))	   //ÅÐ¶ÏÆ«²îÊÇ·ñÔÚÔÊÐí·¶Î§ÄÚ
#else
		if(TS_AreaDeviateDetection(TS_FirstAreaData[i],TS_PostData[i],NOISE_THRESHOLD))	   //ÅÐ¶ÏÆ«²îÊÇ·ñÔÚÔÊÐí·¶Î§ÄÚ
#endif
		{	
			if(!TS_AreaConfirmTimer[i])
			{
				TS_FirstAreaData[i] = TS_PostData[i];
				TS_BaseLineData[i] 	= TS_PostData[i];
				
#if TK_BASE_TRIM_WHILE_KEY_PRESSED
				RefChDataBak[i] = TS_PostData[OPENED_TS_COUNT];
				TS_BaseLineDataBak[i] = TS_BaseLineData[i];
#endif				
				TS_AreaConfirmTimerSet(i,AREA_PNOISE);	
			}	
		}
		else
		{
#if TOUCH_SENSITIVITY_AUTO_BALANCE_EN
			TS_FirstAreaData[i] = TS_PostData2[i];	
#else
			TS_FirstAreaData[i] = TS_PostData[i];	
#endif
			TS_AreaConfirmTimerSet(i,NowArea);		
		}
	}	 	
#if SUPPORT_ANTI_WATER_FUNCTION
	if(KeysFlagSN == 0)
	{
		if(PreKeysFlagSN != 0)
		{
			PressedKeyIndex = AntiWaterModeGetMaxDeltaCh();
			PreKeysFlagSN = MASK_TAB[PressedKeyIndex];
#if (FINGER_LONG_TOUCH_TIME_LIMIT > 0)
			TSKey_LongTouchLimitTimer[PressedKeyIndex] = FINGER_LONG_TOUCH_TIME_LIMIT;
#endif
			TS_AreaConfirmTimer[PressedKeyIndex] = FINGER_TOUCH_RELEASE_CONFIRM_TIME;	
			KeyPressedFlag = 1;
		}
	}
#endif
#if SUPPORT_COVER_PANAL_AFTER_POWERON
	if(!PanalCoverJudgeFlag)
	{
		if(PreKeysFlagSN != 0)
		{
			if(KeysFlagSN == 0)
			{
				PanalCoverJudgeFlag = 1;
				PanalCoverJudgeTimer = PANAL_COVER_JUDGE_TIME; 		
			}
			else
			{
				if((PanalToggleCount >= JUDGE_TK_NUM)||(TS_RefChAbnormalJudge()))
				{
					PreKeysFlagSN = 0;
					PanalCoverJudgeFlag = 0;
					TS_BaseLineForceUpdate();
				}
				KeysFlagSN  = PreKeysFlagSN;
			}
		}
		else
		{
			KeysFlagSN  = PreKeysFlagSN;
		}
	}
	else
	{
		if(!PanalCoverJudgeTimer)
		{
			PanalCoverJudgeFlag = 0;
			KeysFlagSN = PreKeysFlagSN;
		}
		else
		{
			if((PanalToggleCount >= JUDGE_TK_NUM)||(TS_RefChAbnormalJudge()))
			{
				PreKeysFlagSN = 0;
				PanalCoverJudgeFlag = 0;
				TS_BaseLineForceUpdate();
			}			
		}
	}
#else
#if ANTI_SPEAKER_EN
	if((PreKeysFlagSN != 0)&&(KeysFlagSN == 0))
	{
		if(TS_RefChAbnormalJudge())
		{
			PreKeysFlagSN = 0;
			
#if SUPPORT_ANTI_WATER_FUNCTION
			KeyPressedFlag = 0;
#endif
			TS_BaseLineForceUpdate();		
		}
	}
#endif
	KeysFlagSN  = PreKeysFlagSN;

#endif
	if(KeysFlagSN != 0) 
	{
		ActiveTouchType = 1;
	}
	else
	{
		ActiveTouchType = 0;
	}
}
#endif

void TS_init(void)
{
	unsigned char i,ch_idx;

	TS_Cnt 		= OPENED_TS_COUNT;
	ch_idx = 0;
	for(i = 0;i < OPENED_TS_COUNT; i++)
	{
#if SUPPORT_KEY
		TS_CH[ch_idx++] = TS_KEY_CH_INFO_SEQ[i][0];
#endif
	}
	
	CKCON |= ILCKE;


	TMCON = TME(1);
	TMSNU = 0;	
	
	
	
	INT8EN = 1;			
	
	TS_IO_init();
	
	
	TKCFG = TKDIV(TKDIV_VAL)|TKTMS(TKTMS_VAL);		
#if (TK_CHARGE_REF_SELECT == SOURCE_VDD)
	TKCON = TKST(0)|TKIE(1)|TMEN(0)|FAEN(FAEN_V)|VRS(VRS_VAL);
	TKPWC = TKPC(TK_PC_VAL)|VDS(0)|VIRS(0)|TKPWS(0)|TKCVS(0);		
#elif (TK_CHARGE_REF_SELECT == SOURCE_INNER) 
	TKCON = TKST(0)|TKIE(1)|TMEN(0)|FAEN(FAEN_V)|VRS(0);
	TKPWC = TKPC(TK_PC_VAL)|VDS(VDS_VAL)|VIRS(VIRS_VAL)|TKPWS(1)|TKCVS(1);		
#endif
 	
	INT3EN = 1; 
	
	TS_CycleScanDoneFlag = 0;
#if SUPPORT_KEY
	KeysFlagSN = 0;
	PreKeysFlagSN = 0;
#endif	
	ActiveTouchType = 0;
#if SUPPORT_KEY
#if SUPPORT_COVER_PANAL_AFTER_POWERON
	PanalCoverJudgeFlag = 0;
#endif
#endif

	TS_State = TS_INIT;
	TS_Init_Step = 0;
#if SUPPORT_KEY
#if ANTI_SPEAKER_EN	
	RefChDataTimer = 0;
#endif
#endif
	MainLoopCnt1 = MainLoopCnt2 = 0;

}

void TS_Action(void)
{	
	switch(TS_State)
	{
		case TS_INIT:
			TS_RunInit();			
			break;
		case TS_DEAL:		
			if(TS_CycleScanDoneFlag)
			{			
				TS_CycleScanDoneFlag = 0;		
				MainLoopCnt1 = MainLoopCnt2 + 1;
#if SUPPORT_KEY
#if ANTI_SPEAKER_EN
				TS_RefChCheck();
#endif
#endif
				TS_DataFiltering();
			
				TS_Index = 0;
				TS_ScanStart();	
				TS_StableFlag = 1;
#if SUPPORT_KEY	
				if(ActiveTouchType != 2)
				{
					TSKey_DataDeal();	
				}
#endif
									
			}
			if(TS_HalfSecCnt >= 5)
			{
				TKCON = 0;
				TKIF = 0x3F;
				TS_init();
			}
			break;
		default:
			break;
	}


}

/*********************************************************************************************************************/

/*********************************************************************************************************************/

/*********************************************************************************************************************/
