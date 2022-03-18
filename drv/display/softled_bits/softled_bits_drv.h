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



#define LEDBITS_DIR_FORWARD 1 //LEDBITS_DIR_FORWARD 1
#define LEDBITS_DIR_REVERSE 2 //LEDBITS_DIR_REVERSE 2
#define LEDBITS_DIR_F LEDBITS_DIR_FORWARD
#define LEDBITS_DIR_R LEDBITS_DIR_REVERSE




struct  zd_ledbits_t {
unsigned char WorkEn;
unsigned long MinBit;
unsigned long MaxBit;
unsigned char MoveBit_Max;
unsigned char MoveBit_Min;
unsigned char MoveBit_cnt;
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
*������ 		: unsigned char zd_ledBits_isbusy(void)
*������������ 	: LEDλ����æ��־λ
*�������� 		: �ޣ�
*��������ֵ 	: ��
***********************************************************************************************/
// unsigned char zd_ledBits_isbusy(void);

/***********************************************************************************************
*������ 		: zd_ledBits_shift(void)
*������������ 	: ѭ����λ����
*�������� 		: ��
*��������ֵ 	: unsigned char : ����loop״̬,��ͨ�����λ�����λ����ѭ��ʱ����1�����򷵻�0
***********************************************************************************************/
unsigned char zd_ledBits_shift(struct zd_ledbits_t *ledBits);

/***********************************************************************************************
*������ 		: zd_ledBits_StepWork(unsigned char dir,unsigned long stepCount,unsigned char speed)
*������������ 	: ������������������ã����ú��Զ���ʼ����
*�������� 		: dir=��������0=������ǰλ�ã�1=��ת��2=��ת
				  stepCount=Ҫ���������岽�� ,
				  speed=������ʱ��,ת�� (x50ms)
*��������ֵ 	: ��
***********************************************************************************************/
//void zd_ledBits_StepWork(struct zd_ledbits_t *ledBits,unsigned char dir,unsigned long stepCount,unsigned char speed);

/***********************************************************************************************
*������ 		: zd_ledBits_LoopWork(unsigned char dir,unsigned long loopCount,unsigned char speed)
*������������ 	: ������������������ã����ú��Զ���ʼ����
*�������� 		: dir=��������0=������ǰλ�ã�1=��ת��2=��ת
				  stepCount=Ҫ���������岽�� ,
				  speed=������ʱ��,ת�� (x50ms)
*��������ֵ 	: ��
***********************************************************************************************/
//void zd_ledBits_LoopWork(struct zd_ledbits_t *ledBits,unsigned char dir,unsigned long loopCount,unsigned char speed);

/***********************************************************************************************
*������ 		: zd_ledBits_LoopWork(unsigned char dir,unsigned long loopCount,unsigned char speed)
*������������ 	: ������������������ã����ú��Զ���ʼ����
*�������� 		: dir=��������0=������ǰλ�ã�1=��ת��2=��ת
				  stepCount=Ҫ���������岽�� ,
				  speed=������ʱ��,ת�� (x50ms)
*��������ֵ 	: ��
***********************************************************************************************/
void zd_ledBits_Work(struct zd_ledbits_t *ledBits,unsigned char mode,unsigned char dir,unsigned long loopCount,unsigned char speed);

/***********************************************************************************************
*������ 			: void zd_ledBitsLoop_run(void)
*������������ 		: LEDλ�����Զ�����(�ٶȣ�ѭ������),��ÿ50ms����һ��
*�������� 			: ��
*��������ֵ 		: ��
***********************************************************************************************/
//void zd_ledBitsLoop_run(struct zd_ledbits_t *ledBits);

/***********************************************************************************************
*������ 			: void zd_ledBitsStep_run(void)
*������������ 		: LEDλ�����Զ�����(�ٶȣ��ƶ�λ��),��ÿ50ms����һ��
*�������� 			: ��
*��������ֵ 		: ��
***********************************************************************************************/
//void zd_ledBitsStep_run(struct zd_ledbits_t *ledBits);

/***********************************************************************************************
*������ 			: void zd_ledBits_run(void)
*������������ 		: LEDλ�����Զ�����(ͨ��),��ÿ50ms����һ��
*�������� 			: ��
*��������ֵ 		: ��
***********************************************************************************************/
void zd_ledBits_run(struct zd_ledbits_t *ledBits);

/***********************************************************************************************
*������������ 		: LEDλ������ֵ
*�������� 			: ��
*��������ֵ 		: ��
***********************************************************************************************/
// void zd_ledBits_Set(unsigned long setval);

/***********************************************************************************************
*������������ 		: LEDλ������ʼ��
*�������� 			: ��
*��������ֵ 		: ��
***********************************************************************************************/
void zd_ledBits_init(struct zd_ledbits_t *ledBits,unsigned long minbit,unsigned long maxbit);


/***********************************************************************************************
*������������ 		: LEDλ������ʼ��
*�������� 			: ��
*��������ֵ 		: ��
***********************************************************************************************/
void zd_ledBits_stop(struct zd_ledbits_t *ledBits);

//#endif //#if ((DisplayType&DisplayType_SoftLed_Bits)==DisplayType_SoftLed_Bits) 
//#endif //#ifdef DisplayType
#endif //#ifndef __SOFTLEDBITS_DRV_H_