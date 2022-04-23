#ifndef __ZDCMSCORE_H_
#define __ZDCMSCORE_H_

	#include <cms80f252x.h>

	#include "touch_79ft73x\TouchKeyConst.h"

	#define ZD_CLRWDT 	TA=0xAA,TA=0x55,WDCON|=BIT0;
	#define ZD_NOP _nop_();


	#define ZD_GIE_ENABLE EA=1
	#define ZD_GIE_DISABLE EA=0
	//#define ZD_GIE(x) GIE=(x)


	#define ZD_T0IE_ENABLE T0IE=1
	#define ZD_T0IE_DISABLE T0IE=0
	
	
	#define ZD_T0IE(x) ET0=(x)
	
	
	#define ZD_T0IF_CLEAN T0IF=0
	#define ZD_T0IF_GRIGGER (T0IF==1)

	#define ZD_T0_ENABLE TR0=1;
	#define ZD_T0_DISABLE TR0=0;
	
	#define ZD_INTERRUPT_INIT ZD_NOP//临时解决方案,需替换为关所有中断功能
	#define ZD_PORT_INIT ZD_NOP//临时解决方案,需替换为初始化所有IO的功能

	//#ifdef PORTA
	#define ZD_PORTA PO
	#define ZD_PORTA_DIR POTRIS

	#define ZD_PORTA_7 P07
	#define ZD_PORTA_6 P06
	#define ZD_PORTA_5 P05
	#define ZD_PORTA_4 P04
	#define ZD_PORTA_3 P03
	#define ZD_PORTA_2 P02
	#define ZD_PORTA_1 P01
	#define ZD_PORTA_0 P00
	
	#define ZD_PORTA_PHRES P0UP
	#define ZD_PORTA_PDRES P0RD

	#define ZD_PORT0 ZD_PORTA
	#define ZD_PORT0_DIR ZD_PORTA_DIR
	#define ZD_PORT0_7 ZD_PORTA_7
	#define ZD_PORT0_6 ZD_PORTA_6
	#define ZD_PORT0_5 ZD_PORTA_5
	#define ZD_PORT0_4 ZD_PORTA_4
	#define ZD_PORT0_3 ZD_PORTA_3
	#define ZD_PORT0_2 ZD_PORTA_2
	#define ZD_PORT0_1 ZD_PORTA_1
	#define ZD_PORT0_0 ZD_PORTA_0
	#define ZD_PORT0_PHRES ZD_PORTA_PHRES
	#define ZD_PORT0_PDRES ZD_PORTA_PDRES
	
	//#endif
	
	//#ifdef PORTB
	#define ZD_PORTB P1
	#define ZD_PORTB_DIR P1TRIS
	#define ZD_PORTB_7 P17
	#define ZD_PORTB_6 P16
	#define ZD_PORTB_5 P15
	#define ZD_PORTB_4 P14
	#define ZD_PORTB_3 P13
	#define ZD_PORTB_2 P12
	#define ZD_PORTB_1 P11
	#define ZD_PORTB_0 P10
	#define ZD_PORTB_PHRES P1UP
	#define ZD_PORTB_PDRES P1RD

	#define ZD_PORT1 ZD_PORTB
	#define ZD_PORT1_DIR ZD_PORTB_DIR
	#define ZD_PORT1_7 ZD_PORTB_7
	#define ZD_PORT1_6 ZD_PORTB_6
	#define ZD_PORT1_5 ZD_PORTB_5
	#define ZD_PORT1_4 ZD_PORTB_4
	#define ZD_PORT1_3 ZD_PORTB_3
	#define ZD_PORT1_2 ZD_PORTB_2
	#define ZD_PORT1_1 ZD_PORTB_1
	#define ZD_PORT1_0 ZD_PORTB_0
	#define ZD_PORT1_PHRES ZD_PORTB_PHRES
	#define ZD_PORT1_PDRES ZD_PORTB_PDRES
	//#endif
	
	//#ifdef PORTC
	#define ZD_PORTC P2
	#define ZD_PORTC_DIR P2TRIS
	#define ZD_PORTC_7 P27
	#define ZD_PORTC_6 P26
	#define ZD_PORTC_5 P25
	#define ZD_PORTC_4 P24
	#define ZD_PORTC_3 P23
	#define ZD_PORTC_2 P22
	#define ZD_PORTC_1 P21
	#define ZD_PORTC_0 P20
	#define ZD_PORTC_PHRES P2UP
	#define ZD_PORTC_PDRES P2RD

	#define ZD_PORT2 ZD_PORTC
	#define ZD_PORT2_DIR ZD_PORTC_DIR
	#define ZD_PORT2_7 ZD_PORTC_7
	#define ZD_PORT2_6 ZD_PORTC_6
	#define ZD_PORT2_5 ZD_PORTC_5
	#define ZD_PORT2_4 ZD_PORTC_4
	#define ZD_PORT2_3 ZD_PORTC_3
	#define ZD_PORT2_2 ZD_PORTC_2
	#define ZD_PORT2_1 ZD_PORTC_1
	#define ZD_PORT2_0 ZD_PORTC_0
	#define ZD_PORT2_PHRES ZD_PORTC_PHRES
	#define ZD_PORT2_PDRES ZD_PORTC_PDRES
	//#endif
	
	//#ifdef PORTD
	#define ZD_PORTD P3
	#define ZD_PORTD_DIR P3TRIS
	#define ZD_PORTD_7 P37
	#define ZD_PORTD_6 P36
	#define ZD_PORTD_5 P35
	#define ZD_PORTD_4 P34
	#define ZD_PORTD_3 P33
	#define ZD_PORTD_2 P32
	#define ZD_PORTD_1 P31
	#define ZD_PORTD_0 P30
	#define ZD_PORTD_PHRES P3UP
	#define ZD_PORTD_PDRES P3RD

	#define ZD_PORT3 ZD_PORTD
	#define ZD_PORT3_DIR ZD_PORTD_DIR
	#define ZD_PORT3_7 ZD_PORTD_7
	#define ZD_PORT3_6 ZD_PORTD_6
	#define ZD_PORT3_5 ZD_PORTD_5
	#define ZD_PORT3_4 ZD_PORTD_4
	#define ZD_PORT3_3 ZD_PORTD_3
	#define ZD_PORT3_2 ZD_PORTD_2
	#define ZD_PORT3_1 ZD_PORTD_1
	#define ZD_PORT3_0 ZD_PORTD_0
	#define ZD_PORT3_PHRES ZD_PORTD_PHRES
	#define ZD_PORT3_PDRES ZD_PORTD_PDRES

	//#endif

	//#ifdef PORTD
	#define ZD_PORTE P4
	#define ZD_PORTE_DIR P4TRIS
	#define ZD_PORTE_7 P47
	#define ZD_PORTE_6 P46
	#define ZD_PORTE_5 P45
	#define ZD_PORTE_4 P44
	#define ZD_PORTE_3 P43
	#define ZD_PORTE_2 P42
	#define ZD_PORTE_1 P41
	#define ZD_PORTE_0 P40
	#define ZD_PORTE_PHRES P4UP
	#define ZD_PORTE_PDRES P4RD

	#define ZD_PORT4 ZD_PORTE
	#define ZD_PORT4_DIR ZD_PORTE_DIR
	#define ZD_PORT4_7 ZD_PORTE_7
	#define ZD_PORT4_6 ZD_PORTE_6
	#define ZD_PORT4_5 ZD_PORTE_5
	#define ZD_PORT4_4 ZD_PORTE_4
	#define ZD_PORT4_3 ZD_PORTE_3
	#define ZD_PORT4_2 ZD_PORTE_2
	#define ZD_PORT4_1 ZD_PORTE_1
	#define ZD_PORT4_0 ZD_PORTE_0
	#define ZD_PORT4_PHRES ZD_PORTE_PHRES
	#define ZD_PORT4_PDRES ZD_PORTE_PDRES

	//#endif


	#define ZD_PORT_OUTPUT_SET(gpdir,iobit) gpdir|=(iobit)
	#define ZD_PORT_INPUT_SET(gpdir,iobit) gpdir&=(~iobit)
	#define ZD_PORT_PHRES_SET(gpph,iobit) gpph|=(iobit)
	#define ZD_PORT_PDRES_SET(gppd,iobit) gppd|=(iobit)



	//#define ZD_TIMER_CLKSET(x) 

	


	#define ZD_FSYS_CLKSET_FOSC_DIV1  0
	#define ZD_FSYS_CLKSET_FOSC_DIV2  1
	#define ZD_FSYS_CLKSET_FOSC_DIV4  2
	#define ZD_FSYS_CLKSET_FOSC_DIV8  3
	#define ZD_FSYS_CLKSET_FOSC_DIV16 4
	#define ZD_FSYS_CLKSET_FOSC_DIV32 5
	#define ZD_FSYS_CLKSET_FOSC_DIV64 6
	
	#define ZD_FSYS_CLKSET_DEFAULT ZD_FSYS_CLKSET_FOSC_DIV1
	
	#define ZD_FSYS_CLKSET(clkset) TA=0xAA,TA=0x55,CLKDIV==(clkset)


	//////////////////////////////////////////////////////
	#define ZD_ADC_CLKSET_FSYS_DIV2 (0<<4)
	#define ZD_ADC_CLKSET_FSYS_DIV4 (1<<4)
	#define ZD_ADC_CLKSET_FSYS_DIV8 (2<<4)
	#define ZD_ADC_CLKSET_FSYS_DIV16 (3<<4)
	#define ZD_ADC_CLKSET_FSYS_DIV32 (4<<4)
	#define ZD_ADC_CLKSET_FSYS_DIV64 (5<<4)
	#define ZD_ADC_CLKSET_FSYS_DIV128 (6<<4)
	#define ZD_ADC_CLKSET_FSYS_DIV256 (7<<4)

	#define ZD_ADC_CLKSET_DEFAULT ZD_ADC_CLKSET_FSYS_DIV64
	
	#define ZD_ADC_CLKSET(clkset) ADCON1&=(~(BIT6|BIT5|BIT4)),ADCON1|=((clkset))
	
	
	//右对齐10位
	#define ZD_ADC_INIT ADCON0|=(BIT6),ADCON1|=(BIT7)
	//左对齐12位
	//#define ZD_ADC_INIT ADCON0&=(~BIT6),ADCON1|=(BIT7)
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
	
	
	//CMS80F252X
	#define ZD_ADC_CH0_ENABLE P14CFG=0x01
	#define ZD_ADC_CH1_ENABLE P15CFG=0x01
	#define ZD_ADC_CH2_ENABLE P16CFG=0x01
	#define ZD_ADC_CH3_ENABLE P17CFG=0x01

	#define ZD_ADC_CH4_ENABLE P20CFG=0x01
	#define ZD_ADC_CH5_ENABLE P21CFG=0x01
	#define ZD_ADC_CH6_ENABLE P22CFG=0x01
	#define ZD_ADC_CH7_ENABLE P23CFG=0x01

	#define ZD_ADC_CH8_ENABLE  P34CFG=0x01
	#define ZD_ADC_CH9_ENABLE  P35CFG=0x01
	#define ZD_ADC_CH10_ENABLE P36CFG=0x01
	#define ZD_ADC_CH11_ENABLE P37CFG=0x01

	#define ZD_ADC_CH12_ENABLE P40CFG=0x01
	#define ZD_ADC_CH13_ENABLE P41CFG=0x01
	#define ZD_ADC_CH14_ENABLE P42CFG=0x01
	#define ZD_ADC_CH15_ENABLE P43CFG=0x01
	#define ZD_ADC_CH16_ENABLE P44CFG=0x01

	#define ZD_ADC_CH17_ENABLE P12CFG=0x01
	#define ZD_ADC_CH18_ENABLE P13CFG=0x01

	#define ZD_ADC_CH19_ENABLE P24CFG=0x01
	#define ZD_ADC_CH20_ENABLE P25CFG=0x01
	#define ZD_ADC_CH21_ENABLE P26CFG=0x01
	#define ZD_ADC_CH22_ENABLE P27CFG=0x01

	

	
	 
	#define ZD_ADC_CH_SELECT(adch) ( ADCON1&=(~(BIT2|BIT3|BIT0|BIT1)),ADCON0&=(~(BIT7)),ADCON1|=(((adch))&(BIT2|BIT3|BIT0|BIT1)),ADCON0 |= (((adch)<<3)&BIT7) )

	//右对齐12位
	#define ZD_ADC_GETVAL ((unsigned int)(ADRESH<<8|ADRESL))
	//左对齐12位
	//#define ZD_ADC_GETVAL ((unsigned int)((ADRESH<<4)|(ADRESL>>4)))
	
	#define ZD_ADC_START ADCON0|=(BIT1);    
	#define ZD_ADC_ISBUSY (0!=(ADCON0&BIT1))     
	#define ZD_ADC_ISNOTBUSY (0==(ADCON0&BIT1))
	
	///////////////////////////////////////////////////////////////
	

	#define ZD_TIMER0_LOAD TL0
	#define ZD_TIMER0_RELOAD TH0
	
	
	
	
	#define ZD_TIMER0_CLKSET_FSYS_DIV4 0x04
	#define ZD_TIMER0_CLKSET_FSYS_DIV12 0x00

	#define ZD_TIMER0_CLKSET_DEFAULT ZD_TIMER0_CLKSET_FSYS_DIV12
	
	#define ZD_TIMER0_CLKSET(clkset) CKCON&=(~(BIT3)),CKCON|=(clkset)

	///////////////////////////////////////////////////////////////

	
	#define ZD_TIMER0_INIT ZD_TIMER0_CLKSET(ZD_TIMER0_CLKSET_DEFAULT)
	
	
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