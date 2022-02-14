#ifndef	__CMS_CHECKTOUCH_PT_79FT73XX_H_
#define	__CMS_CHECKTOUCH_PT_79FT73XX_H_


//#include "TouchKeyConst.h"

//接口函数声明
extern void __CMS_CheckTouchKey(void);		//按键扫描主过程函数,建议在2.5ms~5ms内调用
extern void __CMS_GetTouchKeyValue(void);//此函数放在中断，建议中断扫描时间125us
extern volatile bit _CMS_b_kerr;				//复位按键标志
//每个按键对应于寄存器的1个位,由高至低一一对应
//_CMS_KeyFlag[0]对应于Key8,...,Key2,Key1
//_CMS_KeyFlag[1]对应于Key16,...,Key10,Key9
//_CMS_KeyFlag[2]对应于Key20,Key19,Key18,Key17
//按键有效时相应位为1,无效时为0
extern volatile unsigned char _CMS_KeyFlag[3];
//-------------------------------------------------------

//-------------------------------------------------------
//-------------------------------------------------------
//-------------------------------------------------------
/*
常规触摸效果参数设置
*/
//待检测按键总数,常量
#define		C_KEY_TOTAL		TOUCH_KEYS_TOTAL_NUMBER	//最多支持16通道

//按键按下消抖次数C_KEY_SHAKE
#define		C_KEY_SHAKE		2	//2~8

//按键放开消抖次数C_KEY_SHAKE
#define		C_KEY_OFFSHAKE		2	//2~8

//噪声阈值
#define		VOL_VALUE		25	//无干扰下的最大触摸波动值*2,范围10~127

//迟滞值
#define		SLU_VALUE		12	//手指按下和放开切换的消抖值,此值需小于等于VOL_VALUE

//触摸基准值更新消抖次数
#define		CM_BASE			10			//消抖时间约为(主程序调用时间4ms*2 + 按键个数*1.5) * CM_BASE

//同时最大允许有效按键数,超过该值将认为是干扰
#define		C_VALID_KEY		2	

//按键最大允许生效时间,以扫描时间（例如5ms）为基准换算,为0时将忽略
#define		C_VALID_TIME	(1000/5)*20//20S

//灵敏度档位
#define 	LMDVALUE		1//0~1,越大约灵敏,为1时注意噪声值以及触摸基准值

//内部串电阻
#define		KEY_EN1KRES		0//0~1



/*-------------------------------------------------------
以下数据通常情况下不用修改
-------------------------------------------------------*/
//异常判断使能，当TK值异常重新进行自适应
#define		UNNOL_CHECK		1//0~1
//异常判断自恢复次数，超过则不再进行自恢复
#define		UNNOL_TIMES		100//1~100

//检测电压
#define 	KEY_LDOSEL		4//0~7


#endif





