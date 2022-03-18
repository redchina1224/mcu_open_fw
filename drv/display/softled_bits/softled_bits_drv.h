#ifndef __SOFTLEDBITS_DRV_H_
#define __SOFTLEDBITS_DRV_H_

//#ifdef DisplayType
//#if ((DisplayType&DisplayType_SoftLed_Bits)==DisplayType_SoftLed_Bits) 


#define LEDBITS_MODE_STOP 0x00
#define LEDBITS_MODE_STEP 0x40
#define LEDBITS_MODE_LOOP 0x80


#define LEDBITS_MOVE_FIX 0x01
#define LEDBITS_MOVE_MASK 0x02


#define LEDBITS_MODE_LOOP_FIX (LEDBITS_MODE_LOOP|LEDBITS_MOVE_FIX)
#define LEDBITS_MODE_STEP_FIX (LEDBITS_MODE_STEP|LEDBITS_MOVE_FIX)
#define LEDBITS_MODE_STEP_MASK (LEDBITS_MODE_STEP|LEDBITS_MOVE_MASK)



#define LEDBITS_DIR_FORWARD 1 //LEDBITS_DIR_FORWARD 1
#define LEDBITS_DIR_REVERSE 2 //LEDBITS_DIR_REVERSE 2
#define LEDBITS_DIR_F LEDBITS_DIR_FORWARD
#define LEDBITS_DIR_R LEDBITS_DIR_REVERSE




struct  zd_ledbits_t {
unsigned char WorkEn;
unsigned char MoveBit_Max;
unsigned char MoveBit_Min;
unsigned char MoveBit_cnt;
unsigned char MaskBit_Set;
unsigned long MaskValue;
unsigned long MoveValue;
unsigned long Value;
unsigned char WorkDir;
union {  
unsigned long WorkStep_cnt;
unsigned long WorkLoop_cnt;
};  
unsigned char WorkSpeed_x50ms_cnt;
unsigned char WorkSpeed_repeat;

};



/***********************************************************************************************
*函数名 		: unsigned char zd_ledBits_isbusy(void)
*函数功能描述 	: LED位驱动忙标志位
*函数参数 		: 无，
*函数返回值 	: 无
***********************************************************************************************/
// unsigned char zd_ledBits_isbusy(void);

/***********************************************************************************************
*函数名 		: zd_ledBits_shift(void)
*函数功能描述 	: 循环移位函数
*函数参数 		: 无
*函数返回值 	: unsigned char : 返回loop状态,当通过最高位或最低位产生循环时返回1，否则返回0
***********************************************************************************************/
unsigned char zd_ledBits_shift(struct zd_ledbits_t *ledBits);

/***********************************************************************************************
*函数名 		: zd_ledBits_StepWork(unsigned char dir,unsigned long stepCount,unsigned char speed)
*函数功能描述 	: 步进电机工作任务设置，设置后自动开始工作
*函数参数 		: dir=工作方向，0=锁定当前位置，1=正转，2=反转
				  stepCount=要工作的脉冲步数 ,
				  speed=脉冲间隔时间,转速 (x50ms)
*函数返回值 	: 无
***********************************************************************************************/
//void zd_ledBits_StepWork(struct zd_ledbits_t *ledBits,unsigned char dir,unsigned long stepCount,unsigned char speed);

/***********************************************************************************************
*函数名 		: zd_ledBits_LoopWork(unsigned char dir,unsigned long loopCount,unsigned char speed)
*函数功能描述 	: 步进电机工作任务设置，设置后自动开始工作
*函数参数 		: dir=工作方向，0=锁定当前位置，1=正转，2=反转
				  stepCount=要工作的脉冲步数 ,
				  speed=脉冲间隔时间,转速 (x50ms)
*函数返回值 	: 无
***********************************************************************************************/
//void zd_ledBits_LoopWork(struct zd_ledbits_t *ledBits,unsigned char dir,unsigned long loopCount,unsigned char speed);

/***********************************************************************************************
*函数名 		: zd_ledBits_LoopWork(unsigned char dir,unsigned long loopCount,unsigned char speed)
*函数功能描述 	: 步进电机工作任务设置，设置后自动开始工作
*函数参数 		: dir=工作方向，0=锁定当前位置，1=正转，2=反转
				  stepCount=要工作的脉冲步数 ,
				  speed=脉冲间隔时间,转速 (x50ms)
*函数返回值 	: 无
***********************************************************************************************/
void zd_ledBits_Work(struct zd_ledbits_t *ledBits,unsigned char mode,unsigned char dir,unsigned long loopCount,unsigned char speed);

/***********************************************************************************************
*函数名 			: void zd_ledBitsLoop_run(void)
*函数功能描述 		: LED位驱动自动控制(速度，循环次数),需每50ms调用一次
*函数参数 			: 无
*函数返回值 		: 无
***********************************************************************************************/
//void zd_ledBitsLoop_run(struct zd_ledbits_t *ledBits);

/***********************************************************************************************
*函数名 			: void zd_ledBitsStep_run(void)
*函数功能描述 		: LED位驱动自动控制(速度，移动位数),需每50ms调用一次
*函数参数 			: 无
*函数返回值 		: 无
***********************************************************************************************/
//void zd_ledBitsStep_run(struct zd_ledbits_t *ledBits);

/***********************************************************************************************
*函数名 			: void zd_ledBits_run(void)
*函数功能描述 		: LED位驱动自动控制(通用),需每50ms调用一次
*函数参数 			: 无
*函数返回值 		: 无
***********************************************************************************************/
void zd_ledBits_run(struct zd_ledbits_t *ledBits);

/***********************************************************************************************
*函数功能描述 		: LED位驱动赋值
*函数参数 			: 无
*函数返回值 		: 无
***********************************************************************************************/
void zd_ledBits_SetMaskBit(struct zd_ledbits_t *ledBits,unsigned char mskbit);

/***********************************************************************************************
*函数功能描述 		: LED位驱动初始化
*函数参数 			: 无
*函数返回值 		: 无
***********************************************************************************************/
void zd_ledBits_init(struct zd_ledbits_t *ledBits,unsigned long movebit,unsigned char minmove,unsigned char maxmove);


/***********************************************************************************************
*函数功能描述 		: LED位驱动初始化
*函数参数 			: 无
*函数返回值 		: 无
***********************************************************************************************/
void zd_ledBits_stop(struct zd_ledbits_t *ledBits);

//#endif //#if ((DisplayType&DisplayType_SoftLed_Bits)==DisplayType_SoftLed_Bits) 
//#endif //#ifdef DisplayType
#endif //#ifndef __SOFTLEDBITS_DRV_H_