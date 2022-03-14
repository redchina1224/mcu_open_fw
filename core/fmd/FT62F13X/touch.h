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


//KEY ON 百分比
#define   KEY0_ON					65
#define   KEY1_ON					65
#define   KEY2_ON					55
#define   KEY3_ON					65
#define   KEY4_ON					55
#define   KEY5_ON					65
#define   KEY6_ON					55
#define   KEY7_ON					65
#define   KEY8_ON					65
//KEY OFF 百分比
#define   KEY0_OFF					40
#define   KEY1_OFF					40
#define   KEY2_OFF					40
#define   KEY3_OFF					40
#define   KEY4_OFF					40
#define   KEY5_OFF					40
#define   KEY6_OFF					40
#define   KEY7_OFF					40
#define   KEY8_OFF					40
//----------------------------------------------------------

//触摸阈值	1
#define  KEY0_ACTIVE_SENSOR_DELTA1		0
#define  KEY1_ACTIVE_SENSOR_DELTA1		0
#define  KEY2_ACTIVE_SENSOR_DELTA1		69*KEY2_ON/100
#define  KEY3_ACTIVE_SENSOR_DELTA1		0
#define  KEY4_ACTIVE_SENSOR_DELTA1		67*KEY4_ON/100
#define  KEY5_ACTIVE_SENSOR_DELTA1		0
#define  KEY6_ACTIVE_SENSOR_DELTA1		49*KEY6_ON/100
#define  KEY7_ACTIVE_SENSOR_DELTA1		0
#define  KEY8_ACTIVE_SENSOR_DELTA1		19*KEY8_ON/100
//----------------------------------------------------------

//非触摸阈值	1
#define  KEY0_INACTIVE_SENSOR_DELTA1		0
#define  KEY1_INACTIVE_SENSOR_DELTA1		0
#define  KEY2_INACTIVE_SENSOR_DELTA1		69*KEY2_OFF/100
#define  KEY3_INACTIVE_SENSOR_DELTA1		0
#define  KEY4_INACTIVE_SENSOR_DELTA1		67*KEY4_OFF/100
#define  KEY5_INACTIVE_SENSOR_DELTA1		0
#define  KEY6_INACTIVE_SENSOR_DELTA1		49*KEY6_OFF/100
#define  KEY7_INACTIVE_SENSOR_DELTA1		0
#define  KEY8_INACTIVE_SENSOR_DELTA1		19*KEY8_OFF/100
//----------------------------------------------------------


unsigned char TouchKeyScan();
void ReadCap();
void Scan_AllKey();
void Touch_init();
extern void DelayUs();

#endif	
