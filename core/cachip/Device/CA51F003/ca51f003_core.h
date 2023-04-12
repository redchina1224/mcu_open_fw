#ifndef __MOF_CACHIP_CORE_H_
#define __MOF_CACHIP_CORE_H_

	#include "include/ca51f003sfr.h"
	#include "include/ca51f003xsfr.h"
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

	//系统时钟初始化
	
	#define MOF_FSYS_INIT	MOF_NOP;//临时解决方案,需替换为初始化系统时钟
	
	//端口定义
	#define MOF_PORT(p) P##p
	#define MOF_PORT_BIT(p,b) P##p##b
	
	//端口输入输出配置
	#define MOF_PORT_BIT_CONFIG(p,b,s) P##p##b##s
	
	#define MOF_PORT_BIT_OUTPUT(p,b) MOF_PORT_BIT_CONFIG(p,b,F)=2
	#define MOF_PORT_BIT_INPUT(p,b) MOF_PORT_BIT_CONFIG(p,b,F)=1
	#define MOF_PORT_BIT_AIN(p,b) MOF_PORT_BIT_CONFIG(p,b,F)=3
	#define MOF_PORT_BIT_UART(p,b) MOF_PORT_BIT_CONFIG(p,b,F)=4
	#define MOF_PORT_BIT_PWM(p,b) MOF_PORT_BIT_CONFIG(p,b,F)=5
	
	//TIMER配置


	#define MOF_T2IE_ENABLE ET2=1
	#define MOF_T2IE_DISABLE ET2=0
	
	
	#define MOF_T2IF_CLEAN {T2MOD=(T2MOD&0x1F)|BIT7;}
	#define MOF_T2IF_GRIGGER (T2MOD & BIT7)

	#define MOF_T2_ENABLE T2CON|=BIT6
	#define MOF_T2_DISABLE T2CON&=~BIT6

	#define MOF_TIMER2_LOAD_SET(x)  { TH2=((x)>>8); TL2=((x)); }
	#define MOF_TIMER2_LOAD_RELOAD(x) { T2CH=((x)>>8); T2CL=((x)); }
	//#define MOF_TIMER2_CLKSET_DEFAULT 
	//#define MOF_TIMER2_INIT { T2CON=0; T2MOD=0;} //设置为比较模式
	#define MOF_TIMER2_INIT {T2CON=(BIT5|BIT3); T2MOD=0;} ////设置定时器为重载模式0		
	
	//ADC配置
	#define MOF_ADC_INIT ADCON&=(~0xff);ADCON|=(BIT0|((7)<<2)) //参考电压为外部VDD,时间为2的HTME次方的时钟周期
	
	#define MOF_ADC_CLKSET_DEFAULT 7 //0默认不分频,1为2分频，2为4分频，，，，，7为14分频
	
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

	
	//配置UART时钟
	#define MOF_UART1_TXBUF S1BUF
	#define MOF_UART1_RXBUF S1BUF
	
	#define MOF_UART_CLKSET_DEFAULT 0
	#define MOF_UART1_CLKSET(clk)  MOF_NOP//临时解决方案,需替换为串口时钟源及分频比设置功能

	//配置UART波特率
	/*
	//注意： 以下波特率参数对应主时钟为16M，如选择另外的主时钟频率，参数须重新计算。
code unsigned long int BR_TAB[]=
{
	1200,
	2400,
	4800,
	9600,
	19200,
	38400,
	57600,
	115200,
};
//注意下表中的第一个值是被1024减之前的值,实际写入SxREL的值应为减好后的值
code unsigned int BR_SET_TAB[][2]=
{
	{416,31},
	{208,31},
	{104,31},
	{52,31},
	{26,31},
	{13,31},
	{10,27},
	{5,27},//16000000÷115200÷5=27.78。取分频数为 28，那么波特率为 114285，和 115200 相比，误差率约为 0.8%
};
	*/
	#define MOF_CA51F_DNUM 31
	#define MOF_CA51F_S1REL_FROM_BAUDRATE(baudrate) (1024-((FsysClk)/((baudrate)*32)))
	
	#define MOF_UART1_BAUDRATE(x) {UDCKS1=(0X80|MOF_CA51F_DNUM);	S1RELH = (unsigned char)((MOF_CA51F_S1REL_FROM_BAUDRATE(x))>>8); S1RELL = (unsigned char)(MOF_CA51F_S1REL_FROM_BAUDRATE(x));}

	//配置串口通道
	#define MOF_UART1_CH0_ENABLE { MOF_PORT_BIT_UART(0,7);MOF_PORT_BIT_UART(0,6); }

	//使能串口
	#define MOF_UART1_ENABLE {S1CON=0xD0;ES1=1;}
	
	#define MOF_UART1_RXIF_GRIGGER (S1CON & BIT0)
	#define MOF_UART1_RXIF_CLEAN {S1CON=(S1CON&~(BIT0|BIT1))|BIT0;}

	#define MOF_UART1_TXIF_GRIGGER (S1CON & BIT1)
	#define MOF_UART1_TXIF_CLEAN {S1CON=(S1CON&~(BIT0|BIT1))|BIT1;}

	//串口通用接收发送接口
	#define UART_BUF_CH(n,t) MOF_UART##n##t
	#define UART_TXBUF_CH(n) UART_BUF_CH(n,_TXBUF)
	#define UART_RXBUF_CH(n) UART_BUF_CH(n,_RXBUF)


//PWMPS

#define PWM_P00_INDEX   0 
#define PWM_P01_INDEX   1 
#define PWM_P02_INDEX   2 
#define PWM_P03_INDEX   3 
#define PWM_P04_INDEX   4 
#define PWM_P05_INDEX   5 
#define PWM_P06_INDEX   6 
#define PWM_P07_INDEX   7 
#define PWM_P10_INDEX   8
#define PWM_P11_INDEX   9
#define PWM_P12_INDEX   10
#define PWM_P13_INDEX   11
#define PWM_P14_INDEX   12
#define PWM_P15_INDEX   13
#define PWM_P16_INDEX   14
#define PWM_P17_INDEX   15
#define PWM_P20_INDEX   16
#define PWM_P30_INDEX   17

	#define MOF_PWM_SELECT(md) INDEX=(md);
	#define MOF_PWM_CH0_ENABLE PWMPS=PWM_P00_INDEX;MOF_PORT_BIT_PWM(0,0)
	#define MOF_PWM_CH1_ENABLE PWMPS=PWM_P01_INDEX;MOF_PORT_BIT_PWM(0,1)
	#define MOF_PWM_CH2_ENABLE PWMPS=PWM_P02_INDEX;MOF_PORT_BIT_PWM(0,2)
	#define MOF_PWM_CH3_ENABLE PWMPS=PWM_P03_INDEX;MOF_PORT_BIT_PWM(0,3)
	#define MOF_PWM_CH4_ENABLE PWMPS=PWM_P04_INDEX;MOF_PORT_BIT_PWM(0,4)
	#define MOF_PWM_CH5_ENABLE PWMPS=PWM_P05_INDEX;MOF_PORT_BIT_PWM(0,5)
	#define MOF_PWM_CH6_ENABLE PWMPS=PWM_P06_INDEX;MOF_PORT_BIT_PWM(0,6)
	#define MOF_PWM_CH7_ENABLE PWMPS=PWM_P07_INDEX;MOF_PORT_BIT_PWM(0,7)
	#define MOF_PWM_CH8_ENABLE PWMPS=PWM_P10_INDEX;MOF_PORT_BIT_PWM(1,0)
	#define MOF_PWM_CH9_ENABLE PWMPS=PWM_P11_INDEX;MOF_PORT_BIT_PWM(1,1)
	#define MOF_PWM_CH10_ENABLE PWMPS=PWM_P12_INDEX;MOF_PORT_BIT_PWM(1,2)
	#define MOF_PWM_CH11_ENABLE PWMPS=PWM_P13_INDEX;MOF_PORT_BIT_PWM(1,3)
	#define MOF_PWM_CH12_ENABLE PWMPS=PWM_P14_INDEX;MOF_PORT_BIT_PWM(1,4)
	#define MOF_PWM_CH13_ENABLE PWMPS=PWM_P15_INDEX;MOF_PORT_BIT_PWM(1,5)
	#define MOF_PWM_CH14_ENABLE PWMPS=PWM_P16_INDEX;MOF_PORT_BIT_PWM(1,6)
	#define MOF_PWM_CH15_ENABLE PWMPS=PWM_P17_INDEX;MOF_PORT_BIT_PWM(1,7)
	#define MOF_PWM_CH16_ENABLE PWMPS=PWM_P20_INDEX;MOF_PORT_BIT_PWM(2,0)
	#define MOF_PWM_CH17_ENABLE PWMPS=PWM_P30_INDEX;MOF_PORT_BIT_PWM(3,0)
	
	
#define MOF_PWM_CLKSET_CKS_SYS		(0<<0)
#define MOF_PWM_CLKSET_CKS_IH			(1<<0)
#define MOF_PWM_CLKSET_CKS_IL			(2<<0)
#define MOF_PWM_CLKSET_CKS_XH			(3<<0)
	
	#define MOF_PWM_CLKSET_DEFAULT MOF_PWM_CLKSET_CKS_IH //0内部高速振荡器
	
	#define MOF_PWM_CLKSET(md,x) INDEX=((md)&0xfe);PWMCON=((PWMCON&(BIT0|BIT1|BIT2))|MOF_PWM_CLKSET_CKS_IH);INDEX=((md));PWMCFG=31; //内部32M,32分频
	
			//设置时钟周期
	#define MOF_PWM_CYCLE(md,x) 	INDEX=(md);PWMDIVH	= (unsigned char)((x)>>8);PWMDIVL	= (unsigned char)(x);	
			//初始化占空比
	#define MOF_PWM_DUTY(md,x) 	INDEX=(md);PWMDUTH	= (unsigned char)((x)>>8);PWMDUTL	= (unsigned char)(x);PWMUPD=(1<<(md));while(PWMUPD);	
	#define MOF_PWM_RGB_DUTY(Ridx,Gidx,Bidx,Rval,Gval,Bval) 	INDEX=(Ridx);PWMDUTH	= (unsigned char)((Rval)>>8);PWMDUTL	= (unsigned char)(Rval);INDEX=(Gidx);PWMDUTH	= (unsigned char)((Gval)>>8);PWMDUTL	= (unsigned char)(Gval);INDEX=(Bidx);PWMDUTH	= (unsigned char)((Bval)>>8);PWMDUTL	= (unsigned char)(Bval);PWMUPD=((1<<(Ridx))|(1<<(Gidx))|(1<<(Bidx)));while(PWMUPD);	
	
			//配置PWM开启
	#define MOF_PWM_INIT(md)  while(PWMUPD);PWMEN |= (1<<(md));
			
			
	
#endif