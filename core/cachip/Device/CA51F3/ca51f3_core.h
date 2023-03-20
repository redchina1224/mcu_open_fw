#ifndef __MOF_CACHIP_CORE_H_
#define __MOF_CACHIP_CORE_H_

	#include "include/ca51f3sfr.h"
	#include "include/ca51f3xsfr.h"
	#include <intrins.h>

	//清看门狗定义
	#define MOF_CLRWDT WDFLG=0xA5;

	//空指令定义
	#define MOF_NOP _nop_();

	//全局中断定义
	#define MOF_GIE EA
	#define MOF_GIE_ENABLE EA=1
	#define MOF_GIE_DISABLE EA=0
	
	//初始化配置相关
	#define MOF_INTERRUPT_INIT MOF_NOP//临时解决方案,需替换为关所有中断功能
	#define MOF_PORT_INIT MOF_NOP;//临时解决方案,需替换为初始化所有IO的功能

	//端口定义
	#define MOF_PORT(p) P##p
	#define MOF_PORT_BIT(p,b) P##p##b
	
	//端口输入输出配置
	#define MOF_PORT_BIT_CONFIG(p,b,s) P##p##b##s
	
	#define MOF_PORT_BIT_OUTPUT(p,b) MOF_PORT_BIT_CONFIG(p,b,F)=2
	#define MOF_PORT_BIT_INPUT(p,b) MOF_PORT_BIT_CONFIG(p,b,F)=1
	#define MOF_PORT_BIT_AIN(p,b) MOF_PORT_BIT_CONFIG(p,b,F)=3
	
	
	//ADC配置
	#define MOF_ADC_INIT ADCON&=(~0xff),ADCON|=(BIT0) //参考电压为外部VDD
	
	#define MOF_ADC_CLKSET_DEFAULT 0 //0默认不分频,1为2分频，2为4分频，，，，，7为14分频
	
	#define MOF_ADC_CLKSET(x) ADCFGL|=((x<<5)&(BIT7|BIT6|BIT5))
	
	#define MOF_ADC_GETVAL ((unsigned int)((ADCDH<<4)|(ADCDL>>4))) //左对齐12位
	
	#define MOF_ADC_START ADCON|=(BIT7);    
	#define MOF_ADC_ISBUSY (0!=(ADCON&BIT7))     
	#define MOF_ADC_ISNOTBUSY (0==(ADCON&BIT7))
	#define MOF_ADC_CH_SELECT(adch) ADCFGL&=(~(BIT0|BIT1|BIT2|BIT3));ADCFGL|=((((adch)+1))&(BIT0|BIT1|BIT2|BIT3))

	//SOP20,TSSOP20
	#define MOF_ADC_CH0_ENABLE MOF_PORT_BIT_AIN(1,2)
	#define MOF_ADC_CH1_ENABLE MOF_PORT_BIT_AIN(1,1)
	#define MOF_ADC_CH2_ENABLE MOF_PORT_BIT_AIN(0,1)
	#define MOF_ADC_CH3_ENABLE MOF_PORT_BIT_AIN(0,3)
	#define MOF_ADC_CH4_ENABLE MOF_PORT_BIT_AIN(0,4)
	#define MOF_ADC_CH5_ENABLE MOF_PORT_BIT_AIN(0,5)
	#define MOF_ADC_CH6_ENABLE MOF_PORT_BIT_AIN(0,6)
	#define MOF_ADC_CH7_ENABLE MOF_PORT_BIT_AIN(0,7)
	#define MOF_ADC_CH8_ENABLE MOF_PORT_BIT_AIN(3,0)
	#define MOF_ADC_CH9_ENABLE MOF_PORT_BIT_AIN(1,7)
	#define MOF_ADC_CH10_ENABLE MOF_PORT_BIT_AIN(1,6)
	#define MOF_ADC_CH11_ENABLE MOF_PORT_BIT_AIN(1,5)

	



#endif