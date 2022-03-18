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
*������ 		: unsigned char zd_ledBits_isbusy(void)
*������������ 	: LEDλ����æ��־λ
*�������� 		: �ޣ�
*��������ֵ 	: ��
***********************************************************************************************/
// unsigned char zd_ledBits_isbusy(void);

// unsigned char zd_ledBits_isbusy(void)
// {
// 	return ledBitsWorkEn;
// }


/***********************************************************************************************
*������ 		: zd_ledBits_shift(void)
*������������ 	: ѭ����λ����
*�������� 		: ��
*��������ֵ 	: unsigned char : ����loop״̬,��ͨ�����λ�����λ����ѭ��ʱ����1�����򷵻�0
***********************************************************************************************/
//unsigned char zd_ledBits_shift(struct zd_ledbits_t *ledBits);
unsigned char zd_ledBits_shift(struct zd_ledbits_t *ledBits)
{
    unsigned char MoveMode=(ledBits->WorkEn&0x3f);
    
	if(ledBits->WorkDir==LEDBITS_DIR_FORWARD)
	{
		if((ledBits->Value&ledBits->MaxBit)==0)
        {
			ledBits->Value<<=1;
            if(MoveMode==1) ledBits->Value|=ledBits->MinBit;
            if(ledBits->Value&ledBits->MaxBit) return 1;
        }
		else
		{
			ledBits->Value=ledBits->MinBit;
		}
	}
	else if(ledBits->WorkDir==LEDBITS_DIR_REVERSE)
	{
		if((ledBits->Value&ledBits->MinBit)==0)
        {
			ledBits->Value>>=1;
            if(MoveMode==1) ledBits->Value|=ledBits->MaxBit;
            if(ledBits->Value&ledBits->MinBit) return 1;
        }
		else
		{
			ledBits->Value=ledBits->MaxBit;
		}
	}

	return 0;
	
}
/***********************************************************************************************
*������ 		: zd_ledBits_StepWork(unsigned char dir,unsigned long stepCount,unsigned char speed)
*������������ 	: ������������������ã����ú��Զ���ʼ����
*�������� 		: dir=��������0=������ǰλ�ã�1=��ת��2=��ת
				  stepCount=Ҫ���������岽�� ,
				  speed=������ʱ��,ת�� (x50ms)
*��������ֵ 	: ��
***********************************************************************************************/
//void zd_ledBits_StepWork(struct zd_ledbits_t *ledBits,unsigned char dir,unsigned long stepCount,unsigned char speed);
void zd_ledBits_StepWork(struct zd_ledbits_t *ledBits,unsigned char mode,unsigned char dir,unsigned long stepCount,unsigned char speed)
{
	ledBits->WorkEn=LEDBITS_MODE_STEP+(mode&0x3f);
	ledBits->WorkDir=dir;
	ledBits->WorkStep_cnt=stepCount;
	ledBits->WorkSpeed_repeat=speed;
	ledBits->WorkSpeed_x50ms_cnt=0;
    if(ledBits->Value==0)
    {
        if(dir==1)
			ledBits->Value=ledBits->MinBit;
        else
			ledBits->Value=ledBits->MaxBit;
    }
}



/***********************************************************************************************
*������ 		: zd_ledBits_LoopWork(unsigned char dir,unsigned long loopCount,unsigned char speed)
*������������ 	: ������������������ã����ú��Զ���ʼ����
*�������� 		: dir=��������0=������ǰλ�ã�1=��ת��2=��ת
				  stepCount=Ҫ���������岽�� ,
				  speed=������ʱ��,ת�� (x50ms)
*��������ֵ 	: ��
***********************************************************************************************/
//void zd_ledBits_LoopWork(struct zd_ledbits_t *ledBits,unsigned char dir,unsigned long loopCount,unsigned char speed);
void zd_ledBits_LoopWork(struct zd_ledbits_t *ledBits,unsigned char mode,unsigned char dir,unsigned long loopCount,unsigned char speed)
{
	ledBits->WorkEn=LEDBITS_MODE_LOOP+(mode&0x3f);
	ledBits->WorkDir=dir;
	ledBits->WorkLoop_cnt=loopCount;
	ledBits->WorkSpeed_repeat=speed;
	ledBits->WorkSpeed_x50ms_cnt=0;
    if(ledBits->Value==0)
    {
        if(dir==1)
			ledBits->Value=ledBits->MinBit;
        else
			ledBits->Value=ledBits->MaxBit;
    }
}

/***********************************************************************************************
*������ 		: zd_ledBits_LoopWork(unsigned char dir,unsigned long loopCount,unsigned char speed)
*������������ 	: ������������������ã����ú��Զ���ʼ����
*�������� 		: dir=��������0=������ǰλ�ã�1=��ת��2=��ת
				  stepCount=Ҫ���������岽�� ,
				  speed=������ʱ��,ת�� (x50ms)
*��������ֵ 	: ��
***********************************************************************************************/
//void zd_ledBits_LoopWork(struct zd_ledbits_t *ledBits,unsigned char dir,unsigned long loopCount,unsigned char speed);
void zd_ledBits_Work(struct zd_ledbits_t *ledBits,unsigned char mode,unsigned char dir,unsigned long loopCount,unsigned char speed)
{
	ledBits->WorkEn=mode;
	ledBits->WorkDir=dir;
	ledBits->WorkLoop_cnt=loopCount;
	ledBits->WorkSpeed_repeat=speed;
	ledBits->WorkSpeed_x50ms_cnt=0;
    if(ledBits->Value==0)
    {
        if(dir==LEDBITS_DIR_FORWARD)
			ledBits->Value=ledBits->MinBit;
        else
			ledBits->Value=ledBits->MaxBit;
    }
}

/***********************************************************************************************
*������ 			: void zd_ledBitsLoop_run(void)
*������������ 		: LEDλ�����Զ�����(�ٶȣ�ѭ������),��ÿ50ms����һ��
*�������� 			: ��
*��������ֵ 		: ��
***********************************************************************************************/
//void zd_ledBitsLoop_run(struct zd_ledbits_t *ledBits);
void zd_ledBitsLoop_run(struct zd_ledbits_t *ledBits)//
{
	if(ledBits->WorkLoop_cnt>0)
	{
		ledBits->WorkEn=1;
		if(++ledBits->WorkSpeed_x50ms_cnt>=ledBits->WorkSpeed_repeat)
		{
			ledBits->WorkSpeed_x50ms_cnt=0;
			if(zd_ledBits_shift(ledBits))
				ledBits->WorkLoop_cnt--;
		}
	}
	else
	{
		ledBits->WorkEn=0;
	}
}



/***********************************************************************************************
*������ 			: void zd_ledBitsStep_run(void)
*������������ 		: LEDλ�����Զ�����(�ٶȣ��ƶ�λ��),��ÿ50ms����һ��
*�������� 			: ��
*��������ֵ 		: ��
***********************************************************************************************/
// void zd_ledBitsStep_run(struct zd_ledbits_t *ledBits);
void zd_ledBitsStep_run(struct zd_ledbits_t *ledBits)//
{
	if(ledBits->WorkStep_cnt>0)
	{
		ledBits->WorkEn=1;
		if(++ledBits->WorkSpeed_x50ms_cnt>=ledBits->WorkSpeed_repeat)
		{
			ledBits->WorkSpeed_x50ms_cnt=0;
			
			zd_ledBits_shift(ledBits);
			ledBits->WorkStep_cnt--;
		}
	}
	else
	{
		ledBits->WorkEn=0;
	}
}

/***********************************************************************************************
*������ 			: void zd_ledBitsStep_run(void)
*������������ 		: LEDλ�����Զ�����(ͨ��),��ÿ50ms����һ��
*�������� 			: ��
*��������ֵ 		: ��
***********************************************************************************************/
// void zd_ledBitsStep_run(struct zd_ledbits_t *ledBits);
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
// void zd_ledBits_Set(unsigned long setval);
// void zd_ledBits_Set(unsigned long setval)
// {
// 	ledBitsValue=startval;
// }

/***********************************************************************************************
*������������ 		: LEDλ������ʼ��
*�������� 			: ��
*��������ֵ 		: ��
***********************************************************************************************/
void zd_ledBits_stop(struct zd_ledbits_t *ledBits)
{
    ledBits->WorkEn=0;
	ledBits->Value=0;
	ledBits->WorkStep_cnt=0;
	ledBits->WorkLoop_cnt=0;
}

/***********************************************************************************************
*������������ 		: LEDλ������ʼ��
*�������� 			: ��
*��������ֵ 		: ��
***********************************************************************************************/
void zd_ledBits_init(struct zd_ledbits_t *ledBits,unsigned long minbit,unsigned long maxbit)
{
	zd_ledBits_stop(ledBits);
    ledBits->MinBit=minbit;
	ledBits->MaxBit=maxbit;
    
    ledBits->MoveBit_Max=4;
	ledBits->MoveBit_Min=0;

}



#endif
#endif
