#ifndef __ZDBYDCORE_H_
#define __ZDBYDCORE_H_

	#include "BF7512DMXX_XXXX.H"

	#include "absacc.h"
	#include "intrins.h"
	#include "stdlib.h"

	#define ZD_CLRWDT WDT_CTRL = 7;
	#define ZD_NOP _nop_()

	#define ZD_GIE EA
	#define ZD_GIE_ENABLE EA=1
	#define ZD_GIE_DISABLE EA=0


	#define ZD_T0IE_ENABLE IEN0|=0x02 //开Timer0中断使能 
	#define ZD_T0IE_DISABLE IEN0&=~0x02 //关Timer0中断使能
		
	#define ZD_T0IF_CLEAN TCON&=~0x20//清除Timer0中断标志
	#define ZD_T0IF_GRIGGER ((TCON&0x20)==0x20)

	#define ZD_T0_ENABLE TCON|=0X10 // 1为开启Timer0
	#define ZD_T0_DISABLE TCON&=~0X10 //0为停止Timer0
	
	#define ZD_INTERRUPT_INIT ZD_NOP//临时解决方案,需替换为关所有中断功能
	#define ZD_PORT_INIT 		PU_PA = 0x00;PU_PB = 0x00;PU_PC = 0x00;PU_PD = 0x00;PD_PB = 0x00;DATAA = 0x00;DATAB = 0x00;DATAC = 0x00;DATAD = 0x00;TRISA = 0x00;TRISB = 0x00;TRISC = 0x00;TRISD = 0x00;
								//临时解决方案,需替换为初始化所有IO的功能


	//#ifdef PORTA
	#define ZD_PORTA DATAA

	#define ZD_PORTA_DIR TRISA

	#define ZD_PORTA_7 PA7
	#define ZD_PORTA_6 PA6
	#define ZD_PORTA_5 PA5
	#define ZD_PORTA_4 PA4
	#define ZD_PORTA_3 PA3
	#define ZD_PORTA_2 PA2
	#define ZD_PORTA_1 PA1
	#define ZD_PORTA_0 PA0
	
	#define ZD_PORTA_PHRES PU_PA

	
	//#endif
	
	//#ifdef PORTB
	#define ZD_PORTB DATAB
	#define ZD_PORTB_DIR TRISB

	#define ZD_PORTB_7 PB7
	#define ZD_PORTB_6 PB6
	#define ZD_PORTB_5 PB5
	#define ZD_PORTB_4 PB4
	#define ZD_PORTB_3 PB3
	#define ZD_PORTB_2 PB2
	#define ZD_PORTB_1 PB1
	#define ZD_PORTB_0 PB0

	#define ZD_PORTB_PHRES PU_PB
	#define ZD_PORTB_PDRES PD_PB
	//#endif
	
	//#ifdef PORTC
	#define ZD_PORTC DATAC

	#define ZD_PORTC_DIR TRISC

	#define ZD_PORTC_7 PC7
	#define ZD_PORTC_6 PC6
	#define ZD_PORTC_5 PC5
	#define ZD_PORTC_4 PC4
	#define ZD_PORTC_3 PC3
	#define ZD_PORTC_2 PC2
	#define ZD_PORTC_1 PC1
	#define ZD_PORTC_0 PC0

	#define ZD_PORTC_PHRES PU_PC

	//#endif
	
	//#ifdef PORTD
	#define ZD_PORTD DATAD

	#define ZD_PORTD_DIR TRISD	

	#define ZD_PORTD_7 PD7
	#define ZD_PORTD_6 PD6
	#define ZD_PORTD_5 PD5
	#define ZD_PORTD_4 PD4
	#define ZD_PORTD_3 PD3
	#define ZD_PORTD_2 PD2
	#define ZD_PORTD_1 PD1
	#define ZD_PORTD_0 PD0

	#define ZD_PORTD_PHRES PU_PD


	//#endif


	#define ZD_PORT_OUTPUT_SET(gpdir,iobit) gpdir&=(~iobit)
	#define ZD_PORT_INPUT_SET(gpdir,iobit) gpdir|=iobit
	#define ZD_PORT_PHRES_SET(gpph,iobit) gpph|=(iobit)
	#define ZD_PORT_PDRES_SET(gppd,iobit) gppd|=(iobit)



	//#define ZD_TIMER_CLKSET(x) 

	
	#define BOR_ON {PD_ANA &= ~(0x08);}				   							//开掉电复位
	#define BOR_OFF {PD_ANA |= (0x08);}			   							  //关掉电复位
	#define V_BOR_SET(x) {BOR_LVDT_VTH &= ~(0x38);BOR_LVDT_VTH |= (0x38&(x<<3));}//设置掉电复位点:(0/1-保留）-(2-2.8V)-(3-3.3V)-(4-3.7V)-(5/6/7-4.2V)，默认为 2.1V
	#define BOR_DELAY_SET(x) {REG_ADDR = 0x2E;REG_DATA &= ~(0x04);REG_DATA |= (0x04&(x<<2));}//0延时1，1延时2;(延时参数见规格书)




	#define ZD_FSYS_CLKSET_FOSC_DIV2_DIV2  0x00
	#define ZD_FSYS_CLKSET_FOSC_DIV2_DIV4  0x01
	#define ZD_FSYS_CLKSET_FOSC_DIV2_DIV6  0x02
	#define ZD_FSYS_CLKSET_FOSC_DIV2_DIV24 0x03
	
	#define ZD_FSYS_CLKSET_DEFAULT ZD_FSYS_CLKSET_FOSC_DIV2_DIV2
	
	#define ZD_FSYS_CLKSET(clkset) SYS_CLK_CFG&=~(0x03);SYS_CLK_CFG|=(0x03&(clkset));


	//////////////////////////////////////////////////////
	#define ZD_ADC_CLKSET_FOSC_DIV16 0
	#define ZD_ADC_CLKSET_FOSC_DIV24 1
	#define ZD_ADC_CLKSET_FOSC_DIV32 2
	#define ZD_ADC_CLKSET_FOSC_DIV48 3
	
	#define ZD_ADC_CLKSET_DEFAULT ZD_ADC_CLKSET_FOSC_DIV32
	
	#define ZD_ADC_CLKSET(clkset) ADCCKC&=~(0x03);ADCCKC|=(0x03&(clkset));
	
	#define ZD_ADC_VREF_VOL_SEL_VCC 0x00
	#define ZD_ADC_VREF_VOL_SEL_ADC_REF_2V 0x01
	#define ZD_ADC_VREF_VOL_SEL_ADC_REF_4V 0x03

	#define ZD_ADC_VREF_VOL_SEL_DEFAULT ZD_ADC_VREF_VOL_SEL_VCC

	#define ADC_VREF_VOL_SEL(x)  {REG_ADDR = 0x2D;REG_DATA=(x);}	////参考电压选择：0：2V;1:4V

	
#define ADC_SAMPT						255	//ADC采样时间配置选择，   		bit[7:0],(0~255)采样时间为(ADC_SPT+1)*4*ADC_CLK
#define ADC_WNUM						8		//采样完毕距离转换时间选择2~31，(x+3)*ADC_CLK
#define ADC_SAMBG						1		//采样时序与比较时序间隔选择，0为间隔0，1为间隔1(ADC_CLK)
#define ADC_SAMDEL					3		//采样延时选择，0为间隔0(ADC_CLK)，1为2(ADC_CLK)，2为4(ADC_CLK)，3为8(ADC_CLK)
#define ADC_FILTER					0		//输入信号滤波选择，0为不加RC滤波，1为加RC滤波
#define ADC26_VIN						1		//ADC26内部输入电压选择，0:为1.362V,1为2.253V，2为3.111V,3为4.082V,使用需要读取ADC校准值,Vin = (ADC_Data/ADC30_Data)*V_ADC30,其中V_ADC30需要从芯片读校准电压值
#define ADC_OFFSETI					3		//ADC偏置电流大小选择，ADC_OFFSETI[1：0]；ADC_OFFSETI[0]比较器偏置电流大小:0为1uA，1为2uA；ADC_OFFSETI[1]运放偏置电流大小:0为1uA，1为2uA；
#define ADC_CTRL						0		//ADC比较器失调消除选择，0为先采样再失调消除，1为所有开关一起断开,默认为1

#define ADC_DCLK					2		//ADC分频选择，					bit[1:0],(0~3)-(3MHz,2MHz,1.5MHz,1MHz)
#define ADC_VREF					0		//参考源电压选择：0：VCC;1:ADC_VREF
#define ADC_VREF_VOL			1		//参考电压选择ADC_VREF：0：2V;1:4V
	
	
	
	
	#define ADC_IE_SET IEN1 |= 0x10																	//开ADC中断使能
#define ADC_IE_CLR IEN1 &= ~0x10																//关ADC中断使能
#define ADC_IP_SET IPL1 |= 0x10																	//设置ADC中断优先级为高
#define ADC_IP_CLR IPL1 &= ~0x10																//设置ADC中断优先级为低
#define ADC_INT_FLAG_CLR IRCON1 &= ~0x10												// 清除ADC中断标志位
	
	
	#define ADC_SAMP_SET(x) 	ADC_SPT = x	//ADC采样时间配置选择，     bit[7:0]，(0~255)采样时间为(ADC_SPT+1)*4*ADC_CLK
	#define ADC_WNUM_SET(x) 	{ADC_CFG1 &= ~(0xF8);ADC_CFG1 |= (0xF8&(x<<3));}		//采样完毕距离转换时间选择2~31，bit[7:3],(x+3)*ADC_CLK 
	#define ADC_SAMPBG_SET(x) {ADC_CFG1 &= ~(0x04);ADC_CFG1 |= (0x04&(x<<2));}		//采样时序与比较时序间隔选择，0为间隔0，1为间隔1(ADC_CLK)
	#define ADC_SAMPDEL_SET(x){ADC_CFG1 &= ~(0x03);ADC_CFG1 |= (0x03&(x<<0));}		//采样延时选择，0为间隔0(ADC_CLK)，1为2(ADC_CLK)，2为4(ADC_CLK)，3为8(ADC_CLK)
	#define ADC_FILTER_SET(x) {ADC_CFG2 &= ~(0x40);ADC_CFG2 |= (0x40&(x<<6));}		//输入信号滤波选择，0为不加滤波，1为加10k电阻滤波
	#define ADC26_VIN_SET(x)  {ADC_CFG2 &= ~(0x30);ADC_CFG2 |= (0x30&(x<<4));}		//ADC26内部输入电压选择，0:为1.362V,1为2.253V，2为3.111V,3为4.082V,使用需要读取ADC校准值
	#define ADC_I_SET(x) 			{ADC_CFG2 &= ~(0x0C);ADC_CFG2 |= (0x0C&(x<<2));}		//ADC偏置电流大小选择，ADC_CFG2[3;2]；ADC_CFG2[2]比较器偏置电流大小:0为1uA，1为2uA；ADC_CFG2[3]运放偏置电流大小:0为1uA，1为2uA；
	#define ADC_CTRL_SET(x)   {ADC_CFG2 &= ~(0x02);ADC_CFG2 |= (0x02&(x<<1));}		//ADC比较器失调消除选择，ADC比较器失调消除选择，0为先采样再失调消除，1为所有开关一起断开,默认为1
	#define ADC_PD(x) 				{PD_ANA &= ~(0x01);PD_ANA |= (0x01&(x<<0));}					//ADC模块开启0为开启，1为关闭


#define ADC_SCAN_EN	 	 	 {ADC_SCAN_CFG &= ~0x01;ADC_SCAN_CFG |= 0x01;}					//ADC模块开启从低0到1
#define ADC_SCAN_CLR	 	  ADC_SCAN_CFG &= ~0x01																	//ADC扫描关闭，bit[0],0为关闭，硬件清零 


	#define ZD_ADC_INIT ADC_IE_CLR;ADC_SCAN_CLR;ADC_VREF_VOL_SEL(ZD_ADC_VREF_VOL_SEL_DEFAULT);ADC_SAMP_SET(255);ADC_WNUM_SET(8);ADC_SAMPBG_SET(1);ADC_SAMPDEL_SET(3);ADC_FILTER_SET(0);ADC26_VIN_SET(1);ADC_I_SET(3);ADC_CTRL_SET(0);ADC_PD(0);
	
	/*
	#define ZD_ADC_CH1_ENABLE ZD_PORTA_DIR|=BIT1
	#define ZD_ADC_CH2_ENABLE ZD_PORTA_DIR|=BIT2
	#define ZD_ADC_CH3_ENABLE ZD_PORTA_DIR|=BIT3
	#define ZD_ADC_CH4_ENABLE ZD_PORTA_DIR|=BIT4
	#define ZD_ADC_CH5_ENABLE ZD_PORTA_DIR|=BIT5
	#define ZD_ADC_CH6_ENABLE ZD_PORTA_DIR|=BIT6
	#define ZD_ADC_CH7_ENABLE ZD_PORTA_DIR|=BIT7
	#define ZD_ADC_CH8_ENABLE ZD_PORTB_DIR|=BIT5
	#define ZD_ADC_CH9_ENABLE ZD_PORTB_DIR|=BIT4
	#define ZD_ADC_CH10_ENABLE ZD_PORTB_DIR|=BIT3
	#define ZD_ADC_CH11_ENABLE ZD_PORTB_DIR|=BIT2
	#define ZD_ADC_CH12_ENABLE ZD_PORTB_DIR|=BIT1
	#define ZD_ADC_CH13_ENABLE ZD_PORTB_DIR|=BIT0
	*/
	
	
	//BF7512DM
	#define ZD_ADC_CH0_ENABLE ZD_PORTB_DIR|=BIT0;ADC_IO_SEL1|=BIT0;
	#define ZD_ADC_CH1_ENABLE ZD_PORTB_DIR|=BIT1;ADC_IO_SEL1|=BIT1;
	#define ZD_ADC_CH2_ENABLE ZD_PORTB_DIR|=BIT2;ADC_IO_SEL1|=BIT2;
	#define ZD_ADC_CH3_ENABLE ZD_PORTB_DIR|=BIT3;ADC_IO_SEL1|=BIT3;
	#define ZD_ADC_CH4_ENABLE ZD_PORTB_DIR|=BIT4;ADC_IO_SEL1|=BIT4;
	#define ZD_ADC_CH5_ENABLE ZD_PORTB_DIR|=BIT5;ADC_IO_SEL1|=BIT5;
	#define ZD_ADC_CH6_ENABLE ZD_PORTB_DIR|=BIT6;ADC_IO_SEL1|=BIT6;
	#define ZD_ADC_CH7_ENABLE ZD_PORTB_DIR|=BIT7;ADC_IO_SEL1|=BIT7;
	
	#define ZD_ADC_CH8_ENABLE ZD_PORTC_DIR|=BIT0;ADC_IO_SEL2|=BIT0;
	#define ZD_ADC_CH9_ENABLE ZD_PORTC_DIR|=BIT1;ADC_IO_SEL2|=BIT1;
	#define ZD_ADC_CH10_ENABLE ZD_PORTC_DIR|=BIT2;ADC_IO_SEL2|=BIT2;
	#define ZD_ADC_CH11_ENABLE ZD_PORTC_DIR|=BIT3;ADC_IO_SEL2|=BIT3;
	#define ZD_ADC_CH12_ENABLE ZD_PORTC_DIR|=BIT4;ADC_IO_SEL2|=BIT4;
	#define ZD_ADC_CH13_ENABLE ZD_PORTC_DIR|=BIT5;ADC_IO_SEL2|=BIT5;
	#define ZD_ADC_CH14_ENABLE ZD_PORTC_DIR|=BIT6;ADC_IO_SEL2|=BIT6;
	#define ZD_ADC_CH15_ENABLE ZD_PORTC_DIR|=BIT7;ADC_IO_SEL2|=BIT7;
	
	#define ZD_ADC_CH16_ENABLE ZD_PORTD_DIR|=BIT0;ADC_IO_SEL3|=BIT0;
	#define ZD_ADC_CH17_ENABLE ZD_PORTD_DIR|=BIT1;ADC_IO_SEL3|=BIT1;
	#define ZD_ADC_CH18_ENABLE ZD_PORTD_DIR|=BIT2;ADC_IO_SEL3|=BIT2;
	#define ZD_ADC_CH19_ENABLE ZD_PORTD_DIR|=BIT3;ADC_IO_SEL3|=BIT3;
	#define ZD_ADC_CH20_ENABLE ZD_PORTD_DIR|=BIT4;ADC_IO_SEL3|=BIT4;
	#define ZD_ADC_CH21_ENABLE ZD_PORTD_DIR|=BIT5;ADC_IO_SEL3|=BIT5;
	#define ZD_ADC_CH22_ENABLE ZD_PORTD_DIR|=BIT6;ADC_IO_SEL3|=BIT6;
	#define ZD_ADC_CH23_ENABLE ZD_PORTD_DIR|=BIT7;ADC_IO_SEL3|=BIT7;
	
	#define ZD_ADC_CH24_ENABLE ZD_PORTA_DIR|=BIT0;ADC_IO_SEL4|=BIT0;
	#define ZD_ADC_CH25_ENABLE ZD_PORTA_DIR|=BIT1;ADC_IO_SEL4|=BIT1;
	
	
	
	 
	#define ZD_ADC_CH_SELECT(adch) { ADC_SCAN_CFG&=(~(BIT1|BIT2|BIT3|BIT4|BIT5));ADC_SCAN_CFG|=(((adch)<<1)&(BIT1|BIT2|BIT3|BIT4|BIT5)); }

	//右对齐
	#define ZD_ADC_GETVAL ((unsigned int)(ADC_RDATAH<<8|ADC_RDATAL))
	//左对齐12位
	//#define ZD_ADC_GETVAL ((unsigned int)((ADRESH<<4)|(ADRESL>>4)))
	
	#define ZD_ADC_START ADC_SCAN_CFG|=1;    
	#define ZD_ADC_ISBUSY (BIT0==(ADC_SCAN_CFG&BIT0))
	#define ZD_ADC_ISNOTBUSY (0==(ADC_SCAN_CFG&BIT0))
	
	///////////////////////////////////////////////////////////////
	

	#define ZD_TIMER0_LOAD TMR0
	
	
	
	
	#define ZD_TIMER0_CLKSET_FSYS_DIV4 0x00
	#define ZD_TIMER0_CLKSET_T0CKI 0x20
	#define ZD_TIMER0_CLKSET_DEFAULT ZD_TIMER0_CLKSET_FSYS_DIV4
	
	#define ZD_TIMER0_CLKSET(clkset) OPTION_REG&=(~(BIT5)),OPTION_REG|=(clkset)

	///////////////////////////////////////////////////////////////
	#define ZD_TIMER0_CLKPSASET_NONE BIT3	
	#define ZD_TIMER0_CLKPSASET_DIV2 0
	#define ZD_TIMER0_CLKPSASET_DIV4 1
	#define ZD_TIMER0_CLKPSASET_DIV8 2
	#define ZD_TIMER0_CLKPSASET_DIV16 3
	#define ZD_TIMER0_CLKPSASET_DIV32 4
	#define ZD_TIMER0_CLKPSASET_DIV64 5
	#define ZD_TIMER0_CLKPSASET_DIV128 6
	#define ZD_TIMER0_CLKPSASET_DIV256 7
	
	#if(FocsClk>8000000)
	#define ZD_TIMER0_CLKPSASET_DEFAULT ZD_TIMER0_CLKPSASET_DIV2
	#else
	#define ZD_TIMER0_CLKPSASET_DEFAULT ZD_TIMER0_CLKPSASET_NONE
	#endif

	#define ZD_TIMER0_CLKPSASET(clkset) OPTION_REG&=(~(BIT0|BIT1|BIT2|BIT3)),OPTION_REG|=(clkset)
	
	#define ZD_TIMER0_INIT ZD_TIMER0_CLKSET(ZD_TIMER0_CLKSET_DEFAULT),ZD_TIMER0_CLKPSASET(ZD_TIMER0_CLKPSASET_DEFAULT)
	
	
	////////////////////////////////////////////////////////////////
	#define ZD_IAP_WRITEDATA_SET(x) 	EEDAT = (x)
	#define ZD_IAP_WRITEADDR_SET(x) 	EEADR = (x)

	#define ZD_IAP_READADDR_SET(x) 	EEADR = (x)
		
	#define ZD_IAP_DATAAREA_SET(x) 	EEPGD = (x)
	#define ZD_IAP_DATAAREA_EEPROM 	ZD_IAP_DATAAREA_SET(0)
	
	#define ZD_IAP_READ_START 		RD=1
	#define ZD_IAP_WRITE_START 		EECON1|=0x30,WREN=1,EECON2=0x55,EECON2=0xaa,WR=1
	#define ZD_IAP_WRITE_NOT_OVER 		(WR==1)
	


	#define ZD_IAP_DATAREAD(x) 		ZD_IAP_READADDR_SET(x),ZD_IAP_READ_START
	#define ZD_IAP_DATA EEDAT
	#define ZD_IAP_END WREN=0

	
	#define ZD_TOUCH_KEY_CH(x) C_KCHS##x
	
	#define ZD_UART1_TXBUF TXREG
	#define ZD_UART1_RXBUF RCREG




#endif