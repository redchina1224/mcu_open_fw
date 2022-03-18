//******************************************************************************
//Copyright(C) 2020-2021 zhejiang zhida dianzikeji Co., Ltd
//????????????????
//File name:      buzz.c
//Author:         zzg
//Version:        Ver0.1
//Date:           2021-4-25
//Description:    ??????????
//History:
//******************************************************************************
//????************************************************************************
#include "..\..\com_include_drv.h"
//????????***********************************************************************


#ifdef DisplayType
#if ((DisplayType&DisplayType_SoftLed_Bits)==DisplayType_SoftLed_Bits) 


/***********************************************************************************************
*������ 		: zd_ledBits_shift(void)
*������������ 	: ѭ����λ����
*�������� 		: ��
*��������ֵ 	: unsigned char : ����loop״̬,��ͨ�����λ�����λ����ѭ��ʱ����1�����򷵻�0
***********************************************************************************************/
unsigned char zd_ledBits_shift(struct zd_ledbits_t *ledBits)
{
    unsigned char MoveMode=(ledBits->WorkEn&0x3f);
    unsigned long MoveValueTemp;
    
	if(ledBits->WorkDir==LEDBITS_DIR_FORWARD)
	{
        if(MoveMode==LEDBITS_MOVE_MASK)
		{
			if(ledBits->MoveBit_cnt<=ledBits->MaskBit_Set)
            {
                 ledBits->MaskValue|=ledBits->Value;
            }
		}
            
		if(ledBits->MoveBit_cnt<ledBits->MoveBit_Max)
        {
            ledBits->MoveBit_cnt++;
            MoveValueTemp=(ledBits->Value<<1);
            
            if(MoveMode==LEDBITS_MOVE_FIX) ledBits->Value|=MoveValueTemp;
            else ledBits->Value=MoveValueTemp;
            
            if(ledBits->MoveBit_cnt==ledBits->MoveBit_Max) return 1;
        }
		else
		{
            ledBits->MoveBit_cnt=ledBits->MoveBit_Min;
			ledBits->Value=ledBits->MoveValue<<ledBits->MoveBit_Min;
		}
        
		
	}
	else if(ledBits->WorkDir==LEDBITS_DIR_REVERSE)
	{
		if(MoveMode==LEDBITS_MOVE_MASK)
		{
			if(ledBits->MoveBit_cnt>=ledBits->MaskBit_Set)
            {
                 ledBits->MaskValue|=ledBits->Value;
            }
		}

		if(ledBits->MoveBit_cnt>ledBits->MoveBit_Min)
        {
            ledBits->MoveBit_cnt--;
            MoveValueTemp=(ledBits->Value>>1);
            
            if(MoveMode==LEDBITS_MOVE_FIX) ledBits->Value|=MoveValueTemp;
            else ledBits->Value=MoveValueTemp;

           if(ledBits->MoveBit_cnt==ledBits->MoveBit_Min) return 1;
        }
		else
		{
            ledBits->MoveBit_cnt=ledBits->MoveBit_Max;
			ledBits->Value=ledBits->MoveValue<<ledBits->MoveBit_Max;
		}
	}

	return 0;
	
}

/***********************************************************************************************
*������ 		: zd_ledBits_LoopWork(unsigned char dir,unsigned long loopCount,unsigned char speed)
*������������ 	: ������������������ã����ú��Զ���ʼ����
*�������� 		: dir=��������0=������ǰλ�ã�1=��ת��2=��ת
				  stepCount=Ҫ���������岽�� ,
				  speed=������ʱ��,ת�� (x50ms)
*��������ֵ 	: ��
***********************************************************************************************/
void zd_ledBits_Work(struct zd_ledbits_t *ledBits,unsigned char mode,unsigned char dir,unsigned long loopCount,unsigned char speed)
{
	ledBits->WorkEn=mode;
	ledBits->WorkDir=dir;
	ledBits->WorkLoop_cnt=loopCount;
	ledBits->WorkSpeed_repeat=speed;
	ledBits->WorkSpeed_x50ms_cnt=0;
    ledBits->MaskValue=0;
    if(ledBits->Value==0)
    {
        if(dir==LEDBITS_DIR_FORWARD)
        {
            ledBits->MaskBit_Set=0;
            ledBits->MoveBit_cnt=ledBits->MoveBit_Min;
			ledBits->Value=ledBits->MoveValue<<ledBits->MoveBit_Min;
        }
        else
        {
            ledBits->MaskBit_Set=31;
            ledBits->MoveBit_cnt=ledBits->MoveBit_Max;
			ledBits->Value=ledBits->MoveValue<<ledBits->MoveBit_Max;
        }
    }
}

/***********************************************************************************************
*������ 			: void zd_ledBitsStep_run(void)
*������������ 		: LEDλ�����Զ�����(ͨ��),��ÿ50ms����һ��
*�������� 			: ��
*��������ֵ 		: ��
***********************************************************************************************/
void zd_ledBits_run(struct zd_ledbits_t *ledBits)//
{
    if(ledBits->WorkEn!=0)
    {
        if(++ledBits->WorkSpeed_x50ms_cnt>=ledBits->WorkSpeed_repeat)
		{
			if(ledBits->WorkStep_cnt>0)//step��loop������,ʹ��ͬһ������
			{
				ledBits->WorkSpeed_x50ms_cnt=0;
				if(zd_ledBits_shift(ledBits)||(ledBits->WorkEn&LEDBITS_MODE_STEP))
                {
					ledBits->WorkStep_cnt--;//step��loop������,ʹ��ͬһ������
                }
			}
			else
			{
				ledBits->WorkEn=0;
			}
        }
    }
}


/***********************************************************************************************
*������������ 		: LEDλ������ֵ
*�������� 			: ��
*��������ֵ 		: ��
***********************************************************************************************/
void zd_ledBits_SetMaskBit(struct zd_ledbits_t *ledBits,unsigned char mskbit)
{
    ledBits->MaskBit_Set=mskbit;
    if(ledBits->WorkDir==LEDBITS_DIR_FORWARD)
    {
       ledBits->MoveBit_Min=ledBits->MaskBit_Set+1;
    }
    else if(ledBits->WorkDir==LEDBITS_DIR_REVERSE)
    {
		ledBits->MoveBit_Max=ledBits->MaskBit_Set-1;
    }
}

/***********************************************************************************************
*������������ 		: LEDλ������ʼ��
*�������� 			: ��
*��������ֵ 		: ��
***********************************************************************************************/
void zd_ledBits_stop(struct zd_ledbits_t *ledBits)
{
    ledBits->WorkEn=0;
	ledBits->Value=0;
    ledBits->MaskValue=0;
	ledBits->WorkStep_cnt=0;
	ledBits->WorkLoop_cnt=0;
}

/***********************************************************************************************
*������������ 		: LEDλ������ʼ��
*�������� 			: ��
*��������ֵ 		: ��
***********************************************************************************************/
void zd_ledBits_init(struct zd_ledbits_t *ledBits,unsigned long movebit,unsigned char minmove,unsigned char maxmove)
{
	zd_ledBits_stop(ledBits);

    ledBits->MoveValue=movebit;
    
    ledBits->MoveBit_Max=maxmove;
	ledBits->MoveBit_Min=minmove;

}



#endif
#endif
