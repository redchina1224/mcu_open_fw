#ifndef	__FMDTOUCH_LIB__
#define	__FMDTOUCH_LIB__

#include "syscfg.h"


#define   TouchCount                         TOUCH_KEYS_TOTAL_NUMBER               	  //按键数

//#define   IO_TOUCH_ATTR	                     0x00D0	     //定义所使用的按键Bit 0~7对应key1~key8，0不使用，1使用

#if(TouchCount>15)
#define	IO_TOUCH_ATTR	(Touch_Key1_Channel|Touch_Key2_Channel|Touch_Key3_Channel|Touch_Key4_Channel|Touch_Key5_Channel|Touch_Key6_Channel|Touch_Key7_Channel|Touch_Key8_Channel|Touch_Key9_Channel|Touch_Key10_Channel|Touch_Key11_Channel|Touch_Key12_Channel|Touch_Key13_Channel|Touch_Key14_Channel|Touch_Key15_Channel|Touch_Key16_Channel)
#elif(TouchCount>14)
#define	IO_TOUCH_ATTR	(Touch_Key1_Channel|Touch_Key2_Channel|Touch_Key3_Channel|Touch_Key4_Channel|Touch_Key5_Channel|Touch_Key6_Channel|Touch_Key7_Channel|Touch_Key8_Channel|Touch_Key9_Channel|Touch_Key10_Channel|Touch_Key11_Channel|Touch_Key12_Channel|Touch_Key13_Channel|Touch_Key14_Channel|Touch_Key15_Channel)
#elif(TouchCount>13)
#define	IO_TOUCH_ATTR	(Touch_Key1_Channel|Touch_Key2_Channel|Touch_Key3_Channel|Touch_Key4_Channel|Touch_Key5_Channel|Touch_Key6_Channel|Touch_Key7_Channel|Touch_Key8_Channel|Touch_Key9_Channel|Touch_Key10_Channel|Touch_Key11_Channel|Touch_Key12_Channel|Touch_Key13_Channel|Touch_Key14_Channel)
#elif(TouchCount>12)
#define	IO_TOUCH_ATTR	(Touch_Key1_Channel|Touch_Key2_Channel|Touch_Key3_Channel|Touch_Key4_Channel|Touch_Key5_Channel|Touch_Key6_Channel|Touch_Key7_Channel|Touch_Key8_Channel|Touch_Key9_Channel|Touch_Key10_Channel|Touch_Key11_Channel|Touch_Key12_Channel|Touch_Key13_Channel)
#elif(TouchCount>11)
#define	IO_TOUCH_ATTR	(Touch_Key1_Channel|Touch_Key2_Channel|Touch_Key3_Channel|Touch_Key4_Channel|Touch_Key5_Channel|Touch_Key6_Channel|Touch_Key7_Channel|Touch_Key8_Channel|Touch_Key9_Channel|Touch_Key10_Channel|Touch_Key11_Channel|Touch_Key12_Channel)
#elif(TouchCount>10)
#define	IO_TOUCH_ATTR	(Touch_Key1_Channel|Touch_Key2_Channel|Touch_Key3_Channel|Touch_Key4_Channel|Touch_Key5_Channel|Touch_Key6_Channel|Touch_Key7_Channel|Touch_Key8_Channel|Touch_Key9_Channel|Touch_Key10_Channel|Touch_Key11_Channel)
#elif(TouchCount>9)
#define	IO_TOUCH_ATTR	(Touch_Key1_Channel|Touch_Key2_Channel|Touch_Key3_Channel|Touch_Key4_Channel|Touch_Key5_Channel|Touch_Key6_Channel|Touch_Key7_Channel|Touch_Key8_Channel|Touch_Key9_Channel|Touch_Key10_Channel)
#elif(TouchCount>8)
#define	IO_TOUCH_ATTR	(Touch_Key1_Channel|Touch_Key2_Channel|Touch_Key3_Channel|Touch_Key4_Channel|Touch_Key5_Channel|Touch_Key6_Channel|Touch_Key7_Channel|Touch_Key8_Channel|Touch_Key9_Channel)
#elif(TouchCount>7)
#define	IO_TOUCH_ATTR	(Touch_Key1_Channel|Touch_Key2_Channel|Touch_Key3_Channel|Touch_Key4_Channel|Touch_Key5_Channel|Touch_Key6_Channel|Touch_Key7_Channel|Touch_Key8_Channel)
#elif(TouchCount>6)
#define	IO_TOUCH_ATTR	(Touch_Key1_Channel|Touch_Key2_Channel|Touch_Key3_Channel|Touch_Key4_Channel|Touch_Key5_Channel|Touch_Key6_Channel|Touch_Key7_Channel)
#elif(TouchCount>5)
#define	IO_TOUCH_ATTR	(Touch_Key1_Channel|Touch_Key2_Channel|Touch_Key3_Channel|Touch_Key4_Channel|Touch_Key5_Channel|Touch_Key6_Channel)
#elif(TouchCount>4)
#define	IO_TOUCH_ATTR	(Touch_Key1_Channel|Touch_Key2_Channel|Touch_Key3_Channel|Touch_Key4_Channel|Touch_Key5_Channel)
#elif(TouchCount>3)
#define	IO_TOUCH_ATTR	(Touch_Key1_Channel|Touch_Key2_Channel|Touch_Key3_Channel|Touch_Key4_Channel)
#elif(TouchCount>2)
#define	IO_TOUCH_ATTR	(Touch_Key1_Channel|Touch_Key2_Channel|Touch_Key3_Channel)
#elif(TouchCount>1)
#define	IO_TOUCH_ATTR	(Touch_Key1_Channel|Touch_Key2_Channel)
#elif(TouchCount>0)
#define	IO_TOUCH_ATTR	(Touch_Key1_Channel)
#endif




#define   LONGKEYPROTECT                       30               	  //(秒)，长按保护设置, 0 不使用
#define   ANTISHAKETIMES 				         1               	  //防抖次数
#define   SCANNINGTIME					         20                //按键扫描频率

//多按键设置
#define   MAXIMUMNUMBEROFKEYS1          0                  //多按键数
#define   PRIMARYKEY1				                  0               	  //主按键
#define   FORBIDDENKEY1                           0x0000        //禁止按键

#define   WAKEUPFREQUENCY                     8                  //唤醒频率  次/秒
#define   WHEELADDSILER							  0x00         	//0B 0000 10 01 (bit1bit0,第一组滑条滚轮选择，00不用，01滚轮，10滑条。bit3bit2,选择第二组滑条滚轮选择





unsigned char TouchKeyScan();
void ReadCap();
void Scan_AllKey();
void Touch_init();
extern void DelayUs();

#endif	
