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

	//系统时钟初始化
	#define MOF_FSYS_CLKPLL_MULTIPLE_DEFAULT 6
	#define MOF_FSYS_CLKPLL_SET(x) PLLCON=(BIT7|((x-2)<<3)) //设置倍频倍数并使能PLL
	#define MOF_FSYS_CLKPLL_WAITE while((PLLCON & BIT0)) //等待PLL时钟稳定
		
	//切换系统时钟
	#define MOF_FSYS_CLK_SWITCH_TO_IRCH		0	
	#define MOF_FSYS_CLK_SWITCH_TO_IRCL		1
	#define MOF_FSYS_CLK_SWITCH_TO_XOSCL		3
	#define MOF_FSYS_CLK_SWITCH_TO_PLL			4
	#define MOF_FSYS_CLK_SWITCH_TO_TFRC		5
	
	#define MOF_FSYS_CLK_SWITCH_TO(x) CKSEL=((CKSEL&0xF8)|x) //切换系统时钟到PLL
	
	#define MOF_FSYS_INIT	{ MOF_FSYS_CLKPLL_SET(MOF_FSYS_CLKPLL_MULTIPLE_DEFAULT);	MOF_FSYS_CLKPLL_WAITE; MOF_FSYS_CLK_SWITCH_TO(MOF_FSYS_CLK_SWITCH_TO_PLL); }	
	
	//端口定义
	#define MOF_PORT(p) P##p
	#define MOF_PORT_BIT(p,b) P##p##b
	
	//端口输入输出配置
	#define MOF_PORT_BIT_CONFIG(p,b,s) P##p##b##s
	
	#define MOF_PORT_BIT_OUTPUT(p,b) MOF_PORT_BIT_CONFIG(p,b,F)=2
	#define MOF_PORT_BIT_INPUT(p,b) MOF_PORT_BIT_CONFIG(p,b,F)=1
	#define MOF_PORT_BIT_AIN(p,b) MOF_PORT_BIT_CONFIG(p,b,F)=5
	#define MOF_PORT_BIT_TK(p,b) MOF_PORT_BIT_CONFIG(p,b,F)=4
	#define MOF_PORT_BIT_UART(p,b) MOF_PORT_BIT_CONFIG(p,b,F)=3
	
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
	#define MOF_ADC_INIT ADCON&=(~0xff),ADCON|=(BIT0) //参考电压为外部VDD
	
	#define MOF_ADC_CLKSET_DEFAULT 0 //0默认不分频,1为2分频，2为4分频，，，，，7为14分频
	
	#define MOF_ADC_CLKSET(x) ADCFGL|=((x<<5)&(BIT7|BIT6|BIT5))
	
	#define MOF_ADC_GETVAL ((unsigned int)((ADCDH<<4)|(ADCDL>>4))) //左对齐12位
	
	#define MOF_ADC_START ADCON|=(BIT7);    
	#define MOF_ADC_ISBUSY (0!=(ADCON&BIT7))     
	#define MOF_ADC_ISNOTBUSY (0==(ADCON&BIT7))
	#define MOF_ADC_CH_SELECT(adch) ADCFGL&=(~(BIT0|BIT1|BIT2|BIT3));ADCFGL|=((((adch)+1))&(BIT0|BIT1|BIT2|BIT3))

	//SOP28,TSSOP28
	#define MOF_ADC_CH0_ENABLE MOF_PORT_BIT_AIN(1,0)
	#define MOF_ADC_CH1_ENABLE MOF_PORT_BIT_AIN(1,1)
	#define MOF_ADC_CH2_ENABLE MOF_PORT_BIT_AIN(1,2)
	#define MOF_ADC_CH3_ENABLE MOF_PORT_BIT_AIN(1,3)
	#define MOF_ADC_CH4_ENABLE MOF_PORT_BIT_AIN(1,4)
	#define MOF_ADC_CH5_ENABLE MOF_PORT_BIT_AIN(1,5)
	#define MOF_ADC_CH6_ENABLE MOF_PORT_BIT_AIN(1,6)
	#define MOF_ADC_CH7_ENABLE MOF_PORT_BIT_AIN(1,7)

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

	#define MOF_UART1_BAUDRATE(x) { S1RELH = (unsigned char)((MOF_CA51F_S1REL_FROM_BAUDRATE(x))>>8); S1RELL = (unsigned char)(MOF_CA51F_S1REL_FROM_BAUDRATE(x));}

	//配置串口通道
	#define MOF_UART1_CH0_ENABLE { MOF_PORT_BIT_UART(1,1);MOF_PORT_BIT_UART(1,2); }

	//使能串口
	#define MOF_UART1_ENABLE {S1CON=0xD0;ES1=1;}
	
	#define MOF_UART1_RXIF_GRIGGER (S1CON & BIT0)
	#define MOF_UART1_RXIF_CLEAN {S1CON=(S1CON&~(BIT0|BIT1))|BIT0;}

	#define MOF_UART1_TXIF_GRIGGER (S1CON & BIT1)
	#define MOF_UART1_TXIF_CLEAN {S1CON=(S1CON&~(BIT0|BIT1))|BIT1;}
	



#endif