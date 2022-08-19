//**********************************************************************************   
//********************   BYD Semiconductor copyright(c) 2021,company   **************************   
//************************    All rights reserved    *******************************   
//*****************************  ---  --  ---  ************************************   
//**********************************************************************************                                              
//========================================================================= 
//  Project Name : MCU04D                                                                                                                     
//  File    Name : BF7512DMXX_XXXX.h 
//  Date         : 2021.07-17                                                             
//  By           : xs                                                                 
//  Version      : V1.0                                 
//=========================================================================  

#ifndef __BF7512DMXX_XXXX_H__
#define __BF7512DMXX_XXXX_H__
/*  ----------------BYTE Register------------------  */
sfr	DATAB				= 0x80;
sfr	SP					= 0x81;
sfr	DPL					= 0x82;
sfr	DPH					= 0x83;
sfr	SYS_CLK_CFG			= 0x84;
sfr	INT_PE_STAT			= 0x85;
sfr	INT_POBO_STAT		= 0x86;
sfr	PCON				= 0x87;
sfr	TCON				= 0x88;
sfr	TMOD				= 0x89;
sfr	TL0					= 0x8A;
sfr	TL1					= 0x8B;
sfr	TH0					= 0x8C;
sfr	TH1					= 0x8D;
sfr	SOFT_RST			= 0x8E;
sfr	DATAC				= 0x90;
sfr	WDT_CTRL			= 0x91;
sfr	WDT_EN				= 0x92;	
sfr	TIMER2_CFG			= 0x93;				   
sfr	TIMER2_SET_H		= 0x94;
sfr	TIMER2_SET_L		= 0x95;
sfr	REG_ADDR			= 0x96;
sfr	REG_DATA			= 0x97;
sfr	DATAD				= 0x98;
sfr	PWM1_L_L			= 0x99;
sfr	PWM1_L_H			= 0x9A;
sfr	PWM1_H_L			= 0x9B;
sfr	PWM1_H_H			= 0x9C;
sfr	PWM2_L_L			= 0x9D;
sfr	PWM2_L_H			= 0x9E;
sfr	PWM2_H_L			= 0x9F;
sfr	P2_XH				= 0xA0;
sfr	PWM2_H_H			= 0xA1;
sfr	PWM_EN				= 0xA2;
sfr	PWM0_CH_CTRL		= 0xA3;
sfr	PWM0_CH0_CNT_L		= 0xA4;
sfr	PWM0_CH0_CNT_H		= 0xA5;
sfr	PWM0_CH1_CNT_L		= 0xA6;
sfr	PWM0_CH1_CNT_H		= 0xA7;
sfr	IEN0				= 0xA8;
sfr	PWM0_CH2_CNT_L		= 0xA9;
sfr	PWM0_CH2_CNT_H		= 0xAA;
sfr	PWM0_CH3_CNT_L		= 0xAB;
sfr	PWM0_CH3_CNT_H		= 0xAC;
sfr	PWM0_MOD_L			= 0xAD;
sfr	PWM0_MOD_H			= 0xAE;
sfr	SCAN_START			= 0xAF;
sfr	DP_CON				= 0xB0;
sfr	SCAN_WIDTH			= 0xB1;
sfr	LED2_WIDTH			= 0xB2;
sfr	LED_DRIVE			= 0xB3;
sfr	ADC_SPT				= 0xB4;
sfr	ADC_SCAN_CFG		= 0xB5;
sfr	ADCCKC				= 0xB6;
sfr	IPL0				= 0xB8;
sfr	ADC_RDATAH			= 0xB9;
sfr	ADC_RDATAL			= 0xBA;
sfr	ADC_CFG1			= 0xBB;
sfr	ADC_CFG2			= 0xBC;
sfr	UART0_BDL			= 0xBD;
sfr	UART0_CON1			= 0xBE;
sfr	UART0_CON2			= 0xBF;
sfr	UART0_STATE			= 0xC0;
sfr	UART0_BUF			= 0xC1;
sfr	UART_IO_CTRL 		= 0xC2;
sfr	UART_IO_CTRL1 		= 0xC3;
sfr	LED_IO_START 		= 0xC4;
sfr	UART1_BDL			= 0xC5;
sfr	UART1_CON1		 	= 0xC6;
sfr	UART1_CON2		 	= 0xC7;
sfr	UART1_STATE		 	= 0xC8;
sfr	UART1_BUF			= 0xC9;
sfr	PSW					= 0xD0;

sfr	RST_STAT			= 0xD7;
sfr	PD_PB				= 0xD8;
sfr	ADC_IO_SEL1			= 0xD9;
sfr	ADC_IO_SEL2			= 0xDA;
sfr	ADC_IO_SEL3			= 0xDB;
sfr	ADC_IO_SEL4			= 0xDC;
sfr	PU_PA				= 0xDD;
sfr	PU_PB				= 0xDE;
sfr	PU_PC				= 0xDF;
sfr	ACC					= 0xE0;
sfr	IRCON2				= 0xE1;
sfr	PU_PD				= 0xE2;
sfr	IICADD				= 0xE3;
sfr	IICBUF				= 0xE4;
sfr	IICCON				= 0xE5;
sfr	IEN1				= 0xE6;
sfr	IEN2				= 0xE7;
sfr	IICSTAT				= 0xE8;
sfr	IICBUFFER			= 0xE9;
sfr	TRISA				= 0xEA;
sfr	TRISB				= 0xEB;
sfr	TRISC				= 0xEC;
sfr	TRISD				= 0xED;
sfr	COM_IO_SEL			= 0xEE;
sfr	ODRAIN_EN			= 0xEF;
sfr	B					= 0xF0;
sfr	IRCON1				= 0xF1;
sfr	PERIPH_IO_SEL		= 0xF2;
sfr	IPL2				= 0xF4;
sfr	IPL1				= 0xF6;
sfr	EXT_INT_CON			= 0xF7;
sfr	DATAA				= 0xF8;
sfr	SPROG_ADDR_H		= 0xF9;
sfr	SPROG_ADDR_L		= 0xFA;
sfr	SPROG_DATA		  	= 0xFB;
sfr	SPROG_CMD			= 0xFC;
sfr	SPROG_TIM			= 0xFD;
sfr	PD_ANA				= 0xFE;
sfr	BOR_LVDT_VTH	    = 0xFF;

/*  ----------------Bit Register------------------  */

/*  DATAA  */
sbit PA0  = DATAA^0;
sbit PA1  = DATAA^1;


/*  DATAB  */
sbit PB0  = DATAB^0;
sbit PB1  = DATAB^1;
sbit PB2  = DATAB^2;
sbit PB3  = DATAB^3;
sbit PB4  = DATAB^4;
sbit PB5  = DATAB^5;
sbit PB6  = DATAB^6;
sbit PB7  = DATAB^7;

/*  TCON  */
sbit IE0  = TCON^1;
sbit IE1  = TCON^3;
sbit TR0  = TCON^4;
sbit TF0  = TCON^5;
sbit TR1  = TCON^6;
sbit TF1  = TCON^7;


/*  DATAC  */
sbit PC0  = DATAC^0;
sbit PC1  = DATAC^1;
sbit PC2  = DATAC^2;
sbit PC3  = DATAC^3;
sbit PC4  = DATAC^4;
sbit PC5  = DATAC^5;
sbit PC6  = DATAC^6;
sbit PC7  = DATAC^7;


/*  DATAD  */
sbit PD0  = DATAD^0;
sbit PD1  = DATAD^1;
sbit PD2  = DATAD^2;
sbit PD3  = DATAD^3;
sbit PD4  = DATAD^4;
sbit PD5  = DATAD^5;
sbit PD6  = DATAD^6;
sbit PD7  = DATAD^7;


/*  IEN0  */
sbit EX0  = IEN0^0;
sbit ET0  = IEN0^1;
sbit EX1  = IEN0^2;
sbit ET1  = IEN0^3;
sbit EA   = IEN0^7;



/*  IPL0  */
sbit PX0  = IPL0^0;
sbit PT0  = IPL0^1;
sbit PX1  = IPL0^2;
sbit PT1  = IPL0^3;



/*  PSW  */
sbit P   = PSW^0;
sbit F1  = PSW^1;
sbit OV  = PSW^2;
sbit RS0 = PSW^3;
sbit RS1 = PSW^4;
sbit F0  = PSW^5;
sbit AC  = PSW^6;
sbit CY  = PSW^7;


/*  IICSTAT  */
sbit IIC_RECOV  = IICSTAT^0;
sbit IIC_WCOL  	= IICSTAT^1;
sbit IIC_ACK 	= IICSTAT^2;
sbit IIC_BF  	= IICSTAT^3;
sbit IIC_AD  	= IICSTAT^4;
sbit IIC_RW  	= IICSTAT^5;
sbit IIC_STOP  	= IICSTAT^6;
sbit IIC_START  = IICSTAT^7;

/*  UART0_STATE  */
sbit UART0_P  	= UART0_STATE^0;
sbit UART0_F  	= UART0_STATE^1;
sbit UART0_RO 	= UART0_STATE^2;
sbit RI0  		= UART0_STATE^3;
sbit TI0  		= UART0_STATE^4;
sbit UART0_T8  	= UART0_STATE^5;
sbit UART0_R8  	= UART0_STATE^6;


/*  UART1_STATE  */
sbit UART1_P  	= UART1_STATE^0;
sbit UART1_F  	= UART1_STATE^1;
sbit UART1_RO 	= UART1_STATE^2;
sbit RI1  		= UART1_STATE^3;
sbit TI1  		= UART1_STATE^4;
sbit UART1_T8  	= UART1_STATE^5;
sbit UART1_R8  	= UART1_STATE^6;

/*  ----------------Bit Register------------------  */

#endif