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
*函数名 		: unsigned char zd_ledBits_isbusy(void)
*函数功能描述 	: LED位驱动忙标志位
*函数参数 		: 无，
*函数返回值 	: 无
***********************************************************************************************/
// unsigned char zd_ledBits_isbusy(void);

// unsigned char zd_ledBits_isbusy(void)
// {
// 	return ledBitsWorkEn;
// }


/***********************************************************************************************
*函数名 		: zd_ledBits_shift(void)
*函数功能描述 	: 循环移位函数
*函数参数 		: 无
*函数返回值 	: unsigned char : 返回loop状态,当通过最高位或最低位产生循环时返回1，否则返回0
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
*函数名 		: zd_ledBits_StepWork(unsigned char dir,unsigned long stepCount,unsigned char speed)
*函数功能描述 	: 步进电机工作任务设置，设置后自动开始工作
*函数参数 		: dir=工作方向，0=锁定当前位置，1=正转，2=反转
				  stepCount=要工作的脉冲步数 ,
				  speed=脉冲间隔时间,转速 (x50ms)
*函数返回值 	: 无
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
*函数名 		: zd_ledBits_LoopWork(unsigned char dir,unsigned long loopCount,unsigned char speed)
*函数功能描述 	: 步进电机工作任务设置，设置后自动开始工作
*函数参数 		: dir=工作方向，0=锁定当前位置，1=正转，2=反转
				  stepCount=要工作的脉冲步数 ,
				  speed=脉冲间隔时间,转速 (x50ms)
*函数返回值 	: 无
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
*函数名 		: zd_ledBits_LoopWork(unsigned char dir,unsigned long loopCount,unsigned char speed)
*函数功能描述 	: 步进电机工作任务设置，设置后自动开始工作
*函数参数 		: dir=工作方向，0=锁定当前位置，1=正转，2=反转
				  stepCount=要工作的脉冲步数 ,
				  speed=脉冲间隔时间,转速 (x50ms)
*函数返回值 	: 无
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
*函数名 			: void zd_ledBitsLoop_run(void)
*函数功能描述 		: LED位驱动自动控制(速度，循环次数),需每50ms调用一次
*函数参数 			: 无
*函数返回值 		: 无
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
*函数名 			: void zd_ledBitsStep_run(void)
*函数功能描述 		: LED位驱动自动控制(速度，移动位数),需每50ms调用一次
*函数参数 			: 无
*函数返回值 		: 无
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
*函数名 			: void zd_ledBitsStep_run(void)
*函数功能描述 		: LED位驱动自动控制(通用),需每50ms调用一次
*函数参数 			: 无
*函数返回值 		: 无
***********************************************************************************************/
// void zd_ledBitsStep_run(struct zd_ledbits_t *ledBits);
void zd_ledBits_run(struct zd_ledbits_t *ledBits)//
{
    if(ledBits->WorkEn!=0)
    {
        if(++ledBits->WorkSpeed_x50ms_cnt>=ledBits->WorkSpeed_repeat)
		{
			if(ledBits->WorkStep_cnt>0)//step与loop是联合,使用同一个变量
			{
				ledBits->WorkSpeed_x50ms_cnt=0;
				if(zd_ledBits_shift(ledBits)||(ledBits->WorkEn&LEDBITS_MODE_STEP))
                {
					ledBits->WorkStep_cnt--;//step与loop是联合,使用同一个变量
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
*函数功能描述 		: LED位驱动赋值
*函数参数 			: 无
*函数返回值 		: 无
***********************************************************************************************/
// void zd_ledBits_Set(unsigned long setval);
// void zd_ledBits_Set(unsigned long setval)
// {
// 	ledBitsValue=startval;
// }

/***********************************************************************************************
*函数功能描述 		: LED位驱动初始化
*函数参数 			: 无
*函数返回值 		: 无
***********************************************************************************************/
void zd_ledBits_stop(struct zd_ledbits_t *ledBits)
{
    ledBits->WorkEn=0;
	ledBits->Value=0;
	ledBits->WorkStep_cnt=0;
	ledBits->WorkLoop_cnt=0;
}

/***********************************************************************************************
*函数功能描述 		: LED位驱动初始化
*函数参数 			: 无
*函数返回值 		: 无
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
