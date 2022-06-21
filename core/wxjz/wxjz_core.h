#ifndef __ZDWXJZCORE_H_
#define __ZDWXJZCORE_H_

	#include "JZ8P2600/JZ8P2600_core.h"


#define EI()  __asm__(" ei ")
#define DI()  __asm__(" di ")
#define NOP() __asm__(" nop ")
#define CONTW(VAL)			__asm__("mov a,@"#VAL"\n ctw")			//CTW = VAL：CONT寄存器赋值
#define IOCP_W(REG,VAL)		__asm__("mov a,@"#VAL"\n iw "#REG)		//REG = VAL：IOC页寄存器赋值
#define IOCP_WV(REG,VAL)	__asm__("mov a,"#VAL"\n iw "#REG)		//REG = VAL：IOC页寄存器赋值
#define IOCP_R(RAM,REG)		__asm__("ir "#REG"\n mov "#RAM",a")		//RAM = REG：IOC页寄存器读值
#define PUSH(A_REG,R3_REG)	__asm__("mov "#A_REG",a\n swap "#A_REG"\n swapa STATUS\n mov "#R3_REG",a")	//中断入栈保护	
#define POP(A_REG,R3_REG)	__asm__("swapa "#R3_REG"\n mov STATUS,a\n swapa "#A_REG)					//中断出栈保护恢复



	#define ZD_CLRWDT __asm__("cwdt")
	#define ZD_NOP __asm__(" nop ")

	#define ZD_GIE_ENABLE_SET __asm__(" ei ")
	#define ZD_GIE_DISABLE_SET __asm__(" di ")

	#define ZD_GIE_ENABLE 1
	#define ZD_GIE_DISABLE 0
	#define ZD_GIE(x) { if(x==ZD_GIE_ENABLE) { ZD_GIE_ENABLE_SET; } else { ZD_GIE_DISABLE_SET; } }


	#define ZD_T0IE_ENABLE 1
	#define ZD_T0IE_DISABLE 0
	
	
	#define ZD_T0IE(x) ZD_NOP
	
	
	#define ZD_T0IF_CLEAN TCIF=0
	#define ZD_T0IF_GRIGGER (TCIF==1)

	#define ZD_T0_ENABLE ZD_NOP//TR0=1;
	#define ZD_T0_DISABLE ZD_NOP//TR0=0;
	

	//#ifdef PORTA
	#define ZD_PORTF PORT6
	#define ZD_PORT6 PORT6
	#define ZD_PORTF_DIR P6CR
	#define ZD_PORT6_DIR P6CR

	#define ZD_PORT6_7 PORT6_7
	#define ZD_PORT6_6 PORT6_6
	#define ZD_PORT6_5 PORT6_5
	#define ZD_PORT6_4 PORT6_4
	#define ZD_PORT6_3 PORT6_3
	#define ZD_PORT6_2 PORT6_2
	#define ZD_PORT6_1 PORT6_1
	#define ZD_PORT6_0 PORT6_0

	#define ZD_PORTF_DIR P6CR
	#define ZD_PORT6_DIR P6CR	
	
	#define ZD_PORTF_PHRES PHCR
	#define ZD_PORT6_PHRES PHCR
	#define ZD_PORTF_PDRES PHDCR
	#define ZD_PORT6_PDRES PHDCR

	
	//#endif
	
	#define ZD_PORT_OUTPUT_SET(gpdir,iobit) IOCP_R(_JZMCU_IOCP_DATABUFF,gpdir);JZMCU_IOCP_DATABUFF&=(~(iobit));IOCP_WV(gpdir,_JZMCU_IOCP_DATABUFF);
	#define ZD_PORT_INPUT_SET(gpdir,iobit) IOCP_R(_JZMCU_IOCP_DATABUFF,gpdir);JZMCU_IOCP_DATABUFF|=(iobit);IOCP_WV(gpdir,_JZMCU_IOCP_DATABUFF);
	#define ZD_PORT_PHRES_SET(gpph,iobit) IOCP_R(_JZMCU_IOCP_DATABUFF,gpdir);JZMCU_IOCP_DATABUFF|=(iobit);IOCP_WV(gpdir,_JZMCU_IOCP_DATABUFF);
	#define ZD_PORT_PDRES_SET(gppd,iobit) IOCP_R(_JZMCU_IOCP_DATABUFF,gpdir);JZMCU_IOCP_DATABUFF|=(iobit);IOCP_WV(gpdir,_JZMCU_IOCP_DATABUFF);



	//#define ZD_TIMER_CLKSET(x) 

	


	#define ZD_FSYS_CLKSET_FOSC_DIV1  0x71
	#define ZD_FSYS_CLKSET_FOSC_DIV2  0x61
	#define ZD_FSYS_CLKSET_FOSC_DIV4  0x51
	#define ZD_FSYS_CLKSET_FOSC_DIV8  0x41
	#define ZD_FSYS_CLKSET_FOSC_DIV16 0x31
	#define ZD_FSYS_CLKSET_FOSC_DIV32 0x21
	#define ZD_FSYS_CLKSET_FOSC_DIV64 0x11
	#define ZD_FSYS_CLKSET_LFINTOSC_32KHZ 0x00
	
	#define ZD_FSYS_CLKSET_DEFAULT ZD_FSYS_CLKSET_FOSC_DIV1
	
	#define ZD_FSYS_CLKSET(clkset) OSCCON&=(~(BIT6|BIT5|BIT4)),OSCCON|=(clkset)


	//////////////////////////////////////////////////////
	#define ZD_ADC_CLKSET_FSYS_DIV8 0B00000000
	#define ZD_ADC_CLKSET_FSYS_DIV16 0B01000000
	#define ZD_ADC_CLKSET_FSYS_DIV32 0B10000000
	#define ZD_ADC_CLKSET_FRC 0B11000000
	
	#define ZD_ADC_CLKSET_DEFAULT ZD_ADC_CLKSET_FSYS_DIV8
	
	#define ZD_ADC_CLKSET(clkset) ADCON0&=(~(BIT7|BIT6)),ADCON0|=((clkset))
	
	
	//右对齐10位
	//#define ZD_ADC_INIT ADCON1|=(BIT7),ADCON0|=(BIT0)
	//左对齐12位
	#define ZD_ADC_INIT ADCON1&=(~BIT7),ADCON0|=(BIT0)
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
	
	
	//CMS79F738
	#define ZD_ADC_CH0_ENABLE ZD_PORTA_DIR|=BIT0,ANSEL0|=BIT0
	#define ZD_ADC_CH1_ENABLE ZD_PORTA_DIR|=BIT1,ANSEL0|=BIT1
	#define ZD_ADC_CH2_ENABLE ZD_PORTA_DIR|=BIT2,ANSEL0|=BIT2
	#define ZD_ADC_CH3_ENABLE ZD_PORTA_DIR|=BIT3,ANSEL0|=BIT3
	#define ZD_ADC_CH4_ENABLE ZD_PORTA_DIR|=BIT4,ANSEL0|=BIT4
	#define ZD_ADC_CH5_ENABLE ZD_PORTA_DIR|=BIT5,ANSEL0|=BIT5
	#define ZD_ADC_CH6_ENABLE ZD_PORTA_DIR|=BIT6,ANSEL0|=BIT6
	#define ZD_ADC_CH7_ENABLE ZD_PORTA_DIR|=BIT7,ANSEL0|=BIT7
	#define ZD_ADC_CH8_ENABLE ZD_PORTB_DIR|=BIT0,ANSEL1|=BIT0
	#define ZD_ADC_CH9_ENABLE ZD_PORTB_DIR|=BIT1,ANSEL1|=BIT1
	#define ZD_ADC_CH10_ENABLE ZD_PORTB_DIR|=BIT2,ANSEL1|=BIT2
	#define ZD_ADC_CH11_ENABLE ZD_PORTB_DIR|=BIT3,ANSEL1|=BIT3
	#define ZD_ADC_CH12_ENABLE ZD_PORTB_DIR|=BIT4,ANSEL1|=BIT4
	#define ZD_ADC_CH13_ENABLE ZD_PORTB_DIR|=BIT5,ANSEL1|=BIT5
	#define ZD_ADC_CH14_ENABLE ZD_PORTB_DIR|=BIT6,ANSEL1|=BIT6

	#define ZD_ADC_CH15_ENABLE ZD_PORTD_DIR|=BIT2,ANSEL1|=BIT7
	#define ZD_ADC_CH16_ENABLE ZD_PORTC_DIR|=BIT7,ANSEL2|=BIT0
	#define ZD_ADC_CH17_ENABLE ZD_PORTC_DIR|=BIT6,ANSEL2|=BIT1
	#define ZD_ADC_CH18_ENABLE ZD_PORTC_DIR|=BIT5,ANSEL2|=BIT2
	#define ZD_ADC_CH19_ENABLE ZD_PORTC_DIR|=BIT4,ANSEL2|=BIT3
	#define ZD_ADC_CH20_ENABLE ZD_PORTC_DIR|=BIT3,ANSEL2|=BIT4
	#define ZD_ADC_CH21_ENABLE ZD_PORTC_DIR|=BIT2,ANSEL2|=BIT5
	#define ZD_ADC_CH22_ENABLE ZD_PORTC_DIR|=BIT1,ANSEL2|=BIT6
	#define ZD_ADC_CH23_ENABLE ZD_PORTC_DIR|=BIT0,ANSEL2|=BIT7
	
	#define ZD_ADC_CH24_ENABLE ZD_PORTD_DIR|=BIT1
	#define ZD_ADC_CH25_ENABLE ZD_PORTD_DIR|=BIT0
	
	
	
	 
	#define ZD_ADC_CH_SELECT(adch) ( ADCON0&=(~(BIT2|BIT3|BIT4|BIT5)),ADCON1&=(~(BIT6)),ADCON0|=(((adch)<<2)&(BIT2|BIT3|BIT4|BIT5)),ADCON1 |= (((adch)<<2)&BIT6) )

	//右对齐10位
	//#define ZD_ADC_GETVAL ((unsigned int)(ADRESH<<8|ADRESL))
	//左对齐12位
	#define ZD_ADC_GETVAL ((unsigned int)((ADRESH<<4)|(ADRESL>>4)))
	
	#define ZD_ADC_START ADCON0|=(BIT1);    
	#define ZD_ADC_ISBUSY (0!=(ADCON0&BIT1))     
	#define ZD_ADC_ISNOTBUSY (0==(ADCON0&BIT1))
	
	///////////////////////////////////////////////////////////////
	

	#define ZD_TIMER0_LOAD TCC
	
	
	#define ZD_TIMER0_INIT CONTW(0x00);IOCP_W(IMR,0x01);
	
	
	////////////////////////////////////////////////////////////////
	#define ZD_IAP_WRITEDATA_SET(x) 	EEDAT = (x)
	#define ZD_IAP_WRITEADDR_SET(x) 	EEADR = (x)

	#define ZD_IAP_READADDR_SET(x) 	EEADR = (x)
		
	#define ZD_IAP_DATAAREA_SET(x) 	EEPGD = (x)
	#define ZD_IAP_DATAAREA_EEPROM 	ZD_IAP_DATAAREA_SET(0)
	
	#define ZD_IAP_READ_START 		RD=1
	#define ZD_IAP_WRITE_START 		EECON1|=0x30,WREN=1,EECON2=0x55,EECON2=0xaa,WR=1
	
	#define ZD_IAP_DATAREAD(x) 		ZD_IAP_READADDR_SET(x),ZD_IAP_READ_START
	#define ZD_IAP_DATA EEDAT
	#define ZD_IAP_END WREN=0

	
	#define ZD_TOUCH_KEY_CH(x) C_KCHS##x
	
	#define ZD_UART1_TXBUF TXREG
	#define ZD_UART1_RXBUF RCREG

#endif