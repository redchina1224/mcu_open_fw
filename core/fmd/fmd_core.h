#ifndef __ZDFMDCORE_H_
#define __ZDFMDCORE_H_

#if (McuType==McuType_FremontMicroDevices_FT61F13)
	#include <syscfg.h>
#elif (McuType==McuType_FremontMicroDevices_FT62F13)
	#include "FT62F13X\syscfg.h"
#endif	

	#define ZD_CLRWDT  asm("clrwdt")
	#define ZD_NOP  __nop()
	#define ZD_SLEEP  asm("sleep")


	#define ZD_GIE_ENABLE GIE=1
	#define ZD_GIE_DISABLE GIE=0
	//#define ZD_GIE(x) GIE=(x)


	#define ZD_T0IE_ENABLE T0IE=1
	#define ZD_T0IE_DISABLE T0IE=0
	
	
	//#define ZD_T0IE(x) T0IE=(x)

	#define ZD_T0IF_CLEAN T0IF=0
	#define ZD_T0IF_GRIGGER (T0IE && T0IF)

	#define ZD_T0_ENABLE T0ON=1;
	#define ZD_T0_DISABLE T0ON=0;



	//#ifdef P0
	#define ZD_PORTA PORTA
	#define ZD_PORT0 PORTA
	#define ZD_PORTA_DIR TRISA
	#define ZD_PORT0_DIR TRISA

	#define ZD_PORTA_PHRES WPUA
	#define ZD_PORT0_PHRES WPUA
	#define ZD_PORTA_PDRES WPDA
	#define ZD_PORT0_PDRES WPDA

	#define ZD_PORTA_0 PA0
	#define ZD_PORTA_1 PA1
	#define ZD_PORTA_2 PA2
	#define ZD_PORTA_3 PA3
	#define ZD_PORTA_4 PA4
	#define ZD_PORTA_5 PA5
	#define ZD_PORTA_6 PA6
	#define ZD_PORTA_7 PA7

	#define ZD_PORT0_0 PA0
	#define ZD_PORT0_1 PA1
	#define ZD_PORT0_2 PA2
	#define ZD_PORT0_3 PA3
	#define ZD_PORT0_4 PA4
	#define ZD_PORT0_5 PA5
	#define ZD_PORT0_6 PA6
	#define ZD_PORT0_7 PA7

	//#endif
	
	//#ifdef P1
	#define ZD_PORTB PORTB
	#define ZD_PORT1 PORTB	
	#define ZD_PORTB_DIR TRISB
	#define ZD_PORT1_DIR TRISB

	#define ZD_PORTB_PHRES WPUB
	#define ZD_PORT1_PHRES WPUB
	#define ZD_PORTB_PDRES WPDB
	#define ZD_PORT1_PDRES WPDB



	#define ZD_PORT1_0 PB0
	#define ZD_PORT1_1 PB1
	#define ZD_PORT1_2 PB2
	#define ZD_PORT1_3 PB3
	#define ZD_PORT1_4 PB4
	#define ZD_PORT1_5 PB5
	#define ZD_PORT1_6 PB6
	#define ZD_PORT1_7 PB7

	#define ZD_PORTB_0 PB0
	#define ZD_PORTB_1 PB1
	#define ZD_PORTB_2 PB2
	#define ZD_PORTB_3 PB3
	#define ZD_PORTB_4 PB4
	#define ZD_PORTB_5 PB5
	#define ZD_PORTB_6 PB6
	#define ZD_PORTB_7 PB7

	//#endif
	
	//#ifdef P2
	#define ZD_PORTC PORTC
	#define ZD_PORT2 PORTC	
	#define ZD_PORTC_DIR TRISC
	#define ZD_PORT2_DIR TRISC

	#define ZD_PORTC_PHRES WPUC
	#define ZD_PORT2_PHRES WPUC
	#define ZD_PORTC_PDRES WPDC
	#define ZD_PORT2_PDRES WPDC


	#define ZD_PORT2_0 PC0
	#define ZD_PORT2_1 PC1


	#define ZD_PORTC_0 PC0
	#define ZD_PORTC_1 PC1


	//#endif




	#define ZD_PORT_OUTPUT_SET(gpdir,iobit) gpdir&=(~iobit)
	#define ZD_PORT_INPUT_SET(gpdir,iobit) gpdir|=(iobit)

	#define ZD_PORT_PHRES_SET(gpph,iobit) gpph|=(iobit)
	#define ZD_PORT_PDRES_SET(gppd,iobit) gppd|=(iobit)


/////////////////////////////////////////////////////////////////
	#define ZD_PORT_OUTPUT(port,bits) TRIS##port|=bits
	#define ZD_PORT_INPUT(port,bits) TRIS##port&=(~bits)
	#define ZD_PORT_PHRES(port,bits) WPU##port|=(bits)
	#define ZD_PORT_PDRES(port,bits) WPD##port|=(bits)
/////////////////////////////////////////////////////////////////

	#define ZD_FSYS_CLKSET_FOSC_DIV1    0x71//0B01110001
	#define ZD_FSYS_CLKSET_FOSC_DIV2    0x61//0B01100001
	#define ZD_FSYS_CLKSET_FOSC_DIV4    0x51//0B01010001
	#define ZD_FSYS_CLKSET_FOSC_DIV8    0x41//0B01000001
	#define ZD_FSYS_CLKSET_FOSC_DIV16   0x31//0B00110001
	#define ZD_FSYS_CLKSET_FOSC_DIV32   0x21//0B00100001
	#define ZD_FSYS_CLKSET_FOSC_DIV64   0x11//0B00010001
	
	#define ZD_FSYS_CLKSET_DEFAULT ZD_FSYS_CLKSET_FOSC_DIV1


	#define ZD_FSYS_CLKSET(clkset) OSCCON=clkset;
	
	//#define ZD_FSYS_CLKSET(clkset) ZD_NOP //该配置在烧录时用选项写入，用空指令代替

	#define ZD_TIMER0_LOAD_RELOAD TMR0
	#define ZD_TIMER0_LOAD TMR0
			

	#define ZD_TIMER0_CLKSET_FSYS 0x00
	#define ZD_TIMER0_CLKSET_T0CKI BIT5
	#define ZD_TIMER0_CLKSET_DEFAULT ZD_TIMER0_CLKSET_FSYS
	
	#define ZD_TIMER0_CLKSET(clkset) OPTION&=(~(BIT5)),OPTION|=(clkset)


	#define ZD_TIMER0_CLKPSASET_DIV1 BIT3
	#define ZD_TIMER0_CLKPSASET_DIV2 0x00
	#define ZD_TIMER0_CLKPSASET_DIV4 0x01
	#define ZD_TIMER0_CLKPSASET_DIV8 0x02
	#define ZD_TIMER0_CLKPSASET_DIV16 0x03
	#define ZD_TIMER0_CLKPSASET_DIV32 0x04
	#define ZD_TIMER0_CLKPSASET_DIV64 0x05
	#define ZD_TIMER0_CLKPSASET_DIV128 0x06
	#define ZD_TIMER0_CLKPSASET_DIV256 0x07

	
	#define ZD_TIMER0_CLKPSASET_DEFAULT ZD_TIMER0_CLKPSASET_DIV8
	
	#define ZD_TIMER0_CLKPSASET(clkset) OPTION&=(~(BIT0|BIT1|BIT2|BIT3)),OPTION|=(clkset)



	#define ZD_TIMER0_INIT ZD_TIMER0_CLKSET(ZD_TIMER0_CLKSET_DEFAULT),ZD_TIMER0_CLKPSASET(ZD_TIMER0_CLKPSASET_DEFAULT),ZD_T0_ENABLE





	//////////////////////////////////////////////////////
	#define ZD_ADC_CLKSET_FOSC_DIV3 7
	#define ZD_ADC_CLKSET_FOSC_DIV4 6
	#define ZD_ADC_CLKSET_FOSC_DIV6 5
	#define ZD_ADC_CLKSET_FOSC_DIV8 4
	#define ZD_ADC_CLKSET_FOSC_DIV12 3
	#define ZD_ADC_CLKSET_FOSC_DIV16 2
	#define ZD_ADC_CLKSET_FOSC_DIV24 1
	#define ZD_ADC_CLKSET_FOSC_DIV32 0
	
	#define ZD_ADC_CLKSET_DEFAULT ZD_ADC_CLKSET_FOSC_DIV32
	
	#define ZD_ADC_CLKSET(clkset) ADCCFG2&=(~(BIT0|BIT1|BIT2)),ADCCFG2|=((clkset))
	
	#define ZD_ADC_INIT ADCCON|=(BIT7),ADCCON&=(~BIT5)

	
	
	//SOC SC92F8463B SOP20
	#define ZD_ADC_CH0_ENABLE  ( ZD_PORT_INPUT_SET(ZD_PORT2_DIR,BIT2),ADCCFG0|=BIT0  )
	#define ZD_ADC_CH1_ENABLE  ( ZD_PORT_INPUT_SET(ZD_PORT2_DIR,BIT3),ADCCFG0|=BIT1  )
	#define ZD_ADC_CH2_ENABLE  ( ZD_PORT_INPUT_SET(ZD_PORT2_DIR,BIT4),ADCCFG0|=BIT2  )
	#define ZD_ADC_CH3_ENABLE  ( ZD_PORT_INPUT_SET(ZD_PORT2_DIR,BIT5),ADCCFG0|=BIT3  )
	#define ZD_ADC_CH4_ENABLE  ( ZD_PORT_INPUT_SET(ZD_PORT2_DIR,BIT6),ADCCFG0|=BIT4  )
	#define ZD_ADC_CH5_ENABLE  ( ZD_PORT_INPUT_SET(ZD_PORT2_DIR,BIT7),ADCCFG0|=BIT5  )
	#define ZD_ADC_CH6_ENABLE  ( ZD_PORT_INPUT_SET(ZD_PORT1_DIR,BIT7),ADCCFG0|=BIT6  )
	#define ZD_ADC_CH7_ENABLE  ( ZD_PORT_INPUT_SET(ZD_PORT1_DIR,BIT6),ADCCFG0|=BIT7  )
	#define ZD_ADC_CH8_ENABLE  ( ZD_PORT_INPUT_SET(ZD_PORT1_DIR,BIT5),ADCCFG1|=BIT0  )
	#define ZD_ADC_CH9_ENABLE  ( ZD_PORT_INPUT_SET(ZD_PORT1_DIR,BIT4),ADCCFG1|=BIT1  )

	 
	#define ZD_ADC_CH_SELECT(adch) ( ADCCON&=(~(BIT0|BIT1|BIT2|BIT3|BIT4)),ADCCON|=(((adch))&(BIT0|BIT1|BIT2|BIT3|BIT4)) )

	#define ZD_ADC_GETVAL ((unsigned int)((ADCVH<<4)|(ADCVL>>4)))
	
	#define ZD_ADC_START 		ADCCON&=(~BIT5),ADCCON|=(BIT6) 
	#define ZD_ADC_ISBUSY (BIT5!=(ADCCON&(BIT5)))
	#define ZD_ADC_ISNOTBUSY (BIT5==(ADCCON&(BIT5)))
	
	//#define ZD_ADC_INIT(x) ADCON1|=(BIT7),ANSEL=(x),ADCON0|=(BIT0)
	//#define ZD_ADC_CHSELECT(adch) (	ADCON0&=(~(BIT2|BIT3|BIT4|BIT5)),ADCON0|=((adch)<<2)	)
	//#define ZD_ADC_CHSELECT(x) ADCON0|=((x)<<2);

	//#define ZD_ADC_GETVAL ((ADRESH<<8|ADRESL))
	//#define ZD_ADC_START ADCON0|=(BIT1);    
	//#define ZD_ADC_ISBUSY (ADCON0&BIT1)     
	

	
	//#define ZD_UART1_TXBUF TXREG
	//#define ZD_UART1_RXBUF RCREG


	#define ZD_IAP_WRITEDATA_SET(x) 	IAPDAT = (x);
	#define ZD_IAP_WRITEADDR_SET(x) 	IAPADH = (((x)>>8)&0X7F),IAPADL = (x)
	#define ZD_IAP_DATAAREA_SET(x) 	IAPADE = (x)
	#define ZD_IAP_DATAAREA_EEPROM 	ZD_IAP_DATAAREA_SET(0x02)
	
	#define ZD_IAP_WRITE_START 		IAPKEY = 240,IAPCTL = 0x06
	
	#define ZD_IAP_DATAREAD(x) 		(*(0+x))
	
	#define ZD_IAP_END IAPADE = 0x00
	


	#define ZD_TOUCH_KEY_CH(x) BIT##x


	#define ZD_INTERRUPT_INIT INTCON=0

	#define ZD_PORT_INIT PORTA=0,PORTC=0,PORTB=0,TRISA=0,TRISB=0,TRISC=0,WPUA=0,WPUB=0,WPDA=0,WPDB=0,ANSEL0=0
	

#endif