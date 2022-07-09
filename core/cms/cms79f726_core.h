#ifndef __ZDCMSCORE_H_
#define __ZDCMSCORE_H_

	#include <cms.h>

	#include "touch_79ft72x\TouchKeyConst.h"

	#define ZD_CLRWDT asm("clrwdt");
	#define ZD_NOP asm("nop");


	#define ZD_GIE_ENABLE GIE=1
	#define ZD_GIE_DISABLE GIE=0
	//#define ZD_GIE(x) GIE=(x)


	#define ZD_T0IE_ENABLE T0IE=1
	#define ZD_T0IE_DISABLE T0IE=0
	
	
	#define ZD_T0IE(x) T0IE=(x)
	
	
	#define ZD_T0IF_CLEAN T0IF=0
	#define ZD_T0IF_GRIGGER (T0IF==1)

	#define ZD_LVDIF_CLEAN LVDIF=0
	#define ZD_LVDIF_GRIGGER (LVDIF==1)

	#define ZD_T0_ENABLE TR0=1;
	#define ZD_T0_DISABLE TR0=0;
	
	#define ZD_INTERRUPT_INIT ZD_NOP//临时解决方案,需替换为关所有中断功能
	#define ZD_PORT_INIT RBPU=0;ZD_NOP;//临时解决方案,需替换为初始化所有IO的功能

	//#ifdef PORTA
	#define ZD_PORTA PORTA
	#define ZD_PORT0 PORTA
	#define ZD_PORTA_DIR TRISA
	#define ZD_PORT0_DIR TRISA

	#define ZD_PORTA_7 RA7
	#define ZD_PORTA_6 RA6
	#define ZD_PORTA_5 RA5
	#define ZD_PORTA_4 RA4
	#define ZD_PORTA_3 RA3
	#define ZD_PORTA_2 RA2
	#define ZD_PORTA_1 RA1
	#define ZD_PORTA_0 RA0
	
	
	#define ZD_PORTA_PHRES WPUA
	#define ZD_PORT0_PHRES WPUA
	
	//#endif
	
	//#ifdef PORTB
	#define ZD_PORTB PORTB
	#define ZD_PORT1 PORTB	
	#define ZD_PORTB_DIR TRISB
	#define ZD_PORT1_DIR TRISB

	#define ZD_PORTB_7 RB7
	#define ZD_PORTB_6 RB6
	#define ZD_PORTB_5 RB5
	#define ZD_PORTB_4 RB4
	#define ZD_PORTB_3 RB3
	#define ZD_PORTB_2 RB2
	#define ZD_PORTB_1 RB1
	#define ZD_PORTB_0 RB0

	#define ZD_PORTB_PHRES WPUB
	#define ZD_PORT1_PHRES WPUB
	//#endif
	
	//#ifdef PORTC
	#define ZD_PORTC PORTC
	#define ZD_PORT2 PORTC
	#define ZD_PORTC_DIR TRISC
	#define ZD_PORT2_DIR TRISC	

	#define ZD_PORTC_7 RC7
	#define ZD_PORTC_6 RC6
	#define ZD_PORTC_5 RC5
	#define ZD_PORTC_4 RC4
	#define ZD_PORTC_3 RC3
	#define ZD_PORTC_2 RC2
	#define ZD_PORTC_1 RC1
	#define ZD_PORTC_0 RC0

	#define ZD_PORTC_PHRES WPUC
	#define ZD_PORT2_PHRES WPUC
	//#endif
	


	#define ZD_PORT_OUTPUT_SET(gpdir,iobit) gpdir&=(~iobit)
	#define ZD_PORT_INPUT_SET(gpdir,iobit) gpdir|=iobit
	#define ZD_PORT_PHRES_SET(gpph,iobit) gpph|=(iobit)
	#define ZD_PORT_PDRES_SET(gppd,iobit) gppd|=(iobit)



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
	
	
	//CMS79F726
	#define ZD_ADC_CH0_ENABLE ZD_PORTA_DIR|=BIT0,ANSEL0|=BIT0
	#define ZD_ADC_CH1_ENABLE ZD_PORTA_DIR|=BIT1,ANSEL0|=BIT1
	#define ZD_ADC_CH2_ENABLE ZD_PORTA_DIR|=BIT2,ANSEL0|=BIT2
	#define ZD_ADC_CH3_ENABLE ZD_PORTA_DIR|=BIT3,ANSEL0|=BIT3
	#define ZD_ADC_CH4_ENABLE ZD_PORTA_DIR|=BIT4,ANSEL0|=BIT4
	#define ZD_ADC_CH5_ENABLE ZD_PORTA_DIR|=BIT5,ANSEL0|=BIT5
	#define ZD_ADC_CH6_ENABLE ZD_PORTA_DIR|=BIT6,ANSEL0|=BIT6
	#define ZD_ADC_CH7_ENABLE ZD_PORTA_DIR|=BIT7,ANSEL0|=BIT7
	#define ZD_ADC_CH8_ENABLE ZD_PORTB_DIR|=BIT7,ANSEL1|=BIT0
	#define ZD_ADC_CH9_ENABLE ZD_PORTB_DIR|=BIT6,ANSEL1|=BIT1
	#define ZD_ADC_CH10_ENABLE ZD_PORTB_DIR|=BIT5,ANSEL1|=BIT2
	#define ZD_ADC_CH11_ENABLE ZD_PORTB_DIR|=BIT4,ANSEL1|=BIT3
	#define ZD_ADC_CH12_ENABLE ZD_PORTB_DIR|=BIT3,ANSEL1|=BIT4
	#define ZD_ADC_CH13_ENABLE ZD_PORTB_DIR|=BIT2,ANSEL1|=BIT5
	#define ZD_ADC_CH14_ENABLE ZD_PORTB_DIR|=BIT1,ANSEL1|=BIT6

	#define ZD_ADC_CH15_ENABLE ZD_PORTB_DIR|=BIT0,ANSEL1|=BIT7
	#define ZD_ADC_CH16_ENABLE ZD_PORTC_DIR|=BIT1,ANSEL2|=BIT0
	#define ZD_ADC_CH17_ENABLE ZD_PORTC_DIR|=BIT0,ANSEL2|=BIT1

	
	
	
	 
	#define ZD_ADC_CH_SELECT(adch) ( ADCON0&=(~(BIT2|BIT3|BIT4|BIT5)),ADCON1&=(~(BIT6)),ADCON0|=(((adch)<<2)&(BIT2|BIT3|BIT4|BIT5)),ADCON1 |= (((adch)<<2)&BIT6) )

	//右对齐10位
	//#define ZD_ADC_GETVAL ((unsigned int)(ADRESH<<8|ADRESL))
	//左对齐12位
	#define ZD_ADC_GETVAL ((unsigned int)((ADRESH<<4)|(ADRESL>>4)))
	
	#define ZD_ADC_START ADCON0|=(BIT1);    
	#define ZD_ADC_ISBUSY (0!=(ADCON0&BIT1))     
	#define ZD_ADC_ISNOTBUSY (0==(ADCON0&BIT1))
	
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
	
	#define ZD_IAP_DATAREAD(x) 		ZD_IAP_READADDR_SET(x),ZD_IAP_READ_START
	#define ZD_IAP_DATA EEDAT
	#define ZD_IAP_END WREN=0

	
	#define ZD_TOUCH_KEY_CH(x) C_KCHS##x
	
	#define ZD_UART1_TXBUF TXREG
	#define ZD_UART1_RXBUF RCREG




#endif