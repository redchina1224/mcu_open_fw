#ifndef __ZDSOCCORE_H_
#define __ZDSOCCORE_H_


	#define ZD_CLRWDT  WDTCON  = 0x10;	
	#define ZD_NOP  _nop_()


	#define ZD_GIE_ENABLE EA=1
	#define ZD_GIE_DISABLE EA=0
	//#define ZD_GIE(x) EA=(x)


	#define ZD_T0IE_ENABLE 1
	#define ZD_T0IE_DISABLE 0
	
	
	#define ZD_T0IE(x) ET0=(x)
	#define ZD_T0IF_CLEAN TF0=0;

	#define ZD_T0_ENABLE TR0=1;
	#define ZD_T0_DISABLE TR0=0;



	//#ifdef P0
	#define ZD_PORTA P0
	#define ZD_PORT0 P0
	#define ZD_PORTA_DIR P0CON
	#define ZD_PORT0_DIR P0CON

	#define ZD_PORTA_0 P00
	#define ZD_PORTA_1 P01
	#define ZD_PORTA_2 P02
	#define ZD_PORTA_3 P03
	#define ZD_PORTA_4 P04
	#define ZD_PORTA_5 P05
	#define ZD_PORTA_6 P06
	#define ZD_PORTA_7 P07

	#define ZD_PORT0_0 P00
	#define ZD_PORT0_1 P01
	#define ZD_PORT0_2 P02
	#define ZD_PORT0_3 P03
	#define ZD_PORT0_4 P04
	#define ZD_PORT0_5 P05
	#define ZD_PORT0_6 P06
	#define ZD_PORT0_7 P07

	//#endif
	
	//#ifdef P1
	#define ZD_PORTB P1
	#define ZD_PORT1 P1	
	#define ZD_PORTB_DIR P1CON
	#define ZD_PORT1_DIR P1CON

	#define ZD_PORTB_PHRES P1PH
	#define ZD_PORT1_PHRES P1PH




	#define ZD_PORT1_0 P10
	#define ZD_PORT1_1 P11
	#define ZD_PORT1_2 P12
	#define ZD_PORT1_3 P13
	#define ZD_PORT1_4 P14
	#define ZD_PORT1_5 P15
	#define ZD_PORT1_6 P16
	#define ZD_PORT1_7 P17

	#define ZD_PORTB_0 P10
	#define ZD_PORTB_1 P11
	#define ZD_PORTB_2 P12
	#define ZD_PORTB_3 P13
	#define ZD_PORTB_4 P14
	#define ZD_PORTB_5 P15
	#define ZD_PORTB_6 P16
	#define ZD_PORTB_7 P17

	//#endif
	
	//#ifdef P2
	#define ZD_PORTC P2
	#define ZD_PORT2 P2
	#define ZD_PORTC_DIR P2CON
	#define ZD_PORT2_DIR P2CON	

	#define ZD_PORT2_0 P20
	#define ZD_PORT2_1 P21
	#define ZD_PORT2_2 P22
	#define ZD_PORT2_3 P23
	#define ZD_PORT2_4 P24
	#define ZD_PORT2_5 P25
	#define ZD_PORT2_6 P26
	#define ZD_PORT2_7 P27

	#define ZD_PORTC_0 P20
	#define ZD_PORTC_1 P21
	#define ZD_PORTC_2 P22
	#define ZD_PORTC_3 P23
	#define ZD_PORTC_4 P24
	#define ZD_PORTC_5 P25
	#define ZD_PORTC_6 P26
	#define ZD_PORTC_7 P27

	//#endif
	
	//#ifdef P3
	#define ZD_PORTD P3
	#define ZD_PORT3 P3
	#define ZD_PORTD_DIR P3CON
	#define ZD_PORT3_DIR P3CON	

	#define ZD_PORT3_0 P30
	#define ZD_PORT3_1 P31
	#define ZD_PORT3_2 P32
	#define ZD_PORT3_3 P33
	#define ZD_PORT3_4 P34
	#define ZD_PORT3_5 P35
	#define ZD_PORT3_6 P36
	#define ZD_PORT3_7 P37

	#define ZD_PORTD_0 P30
	#define ZD_PORTD_1 P31
	#define ZD_PORTD_2 P32
	#define ZD_PORTD_3 P33
	#define ZD_PORTD_4 P34
	#define ZD_PORTD_5 P35
	#define ZD_PORTD_6 P36
	#define ZD_PORTD_7 P37


	//#endif


	//#ifdef P4
	#define ZD_PORTE P4
	#define ZD_PORT4 P4
	#define ZD_PORTE_DIR P4CON
	#define ZD_PORT4_DIR P4CON	

	#define ZD_PORT4_0 P40
	#define ZD_PORT4_1 P41
	#define ZD_PORT4_2 P42
	#define ZD_PORT4_3 P43
	#define ZD_PORT4_4 P44
	#define ZD_PORT4_5 P45
	#define ZD_PORT4_6 P46
	#define ZD_PORT4_7 P47

	#define ZD_PORTE_0 P40
	#define ZD_PORTE_1 P41
	#define ZD_PORTE_2 P42
	#define ZD_PORTE_3 P43
	#define ZD_PORTE_4 P44
	#define ZD_PORTE_5 P45
	#define ZD_PORTE_6 P46
	#define ZD_PORTE_7 P47


	//#endif




	//#ifdef P5
	#define ZD_PORTF P5
	#define ZD_PORT5 P5
	#define ZD_PORTF_DIR P5CON
	#define ZD_PORT5_DIR P5CON	

	#define ZD_PORT5_0 P50
	#define ZD_PORT5_1 P51
	#define ZD_PORT5_2 P52
	#define ZD_PORT5_3 P53
	#define ZD_PORT5_4 P54
	#define ZD_PORT5_5 P55
	#define ZD_PORT5_6 P56
	#define ZD_PORT5_7 P57

	#define ZD_PORTF_0 P50
	#define ZD_PORTF_1 P51
	#define ZD_PORTF_2 P52
	#define ZD_PORTF_3 P53
	#define ZD_PORTF_4 P54
	#define ZD_PORTF_5 P55
	#define ZD_PORTF_6 P56
	#define ZD_PORTF_7 P57


	//#endif














	#define ZD_PORT_OUTPUT_SET(gpdir,iobit) gpdir|=iobit
	#define ZD_PORT_INPUT_SET(gpdir,iobit) gpdir&=(~iobit)

	#define ZD_PORT_PHRES_SET(gpph,iobit) gpph|=(iobit)


	#define ZD_FSYS_CLKSET_FOSC_DIV1  (0x00<<4)
	#define ZD_FSYS_CLKSET_FOSC_DIV2  (0x01<<4)
	#define ZD_FSYS_CLKSET_FOSC_DIV4   (0x02<<4)
	#define ZD_FSYS_CLKSET_FOSC_DIV12   (0x03<<4)
	
	#define ZD_FSYS_CLKSET_DEFAULT ZD_FSYS_CLKSET_FOSC_DIV2
	
	//#define ZD_FSYS_CLKSET(clkset) OPINX=0xC1,if(  ((BIT5|BIT4)&OPREG )!= (clkset)  ){ OPREG&=(~(BIT5|BIT4));OPREG|=(clkset) } //该配置是写入FLASH的不建议在每次上电时写入
		#define ZD_FSYS_CLKSET(clkset) \
			OPINX=0xC1;\
			if(  ((BIT5|BIT4)&OPREG )!= (clkset)  ){\
			 OPREG&=(~(BIT5|BIT4));\
			OPREG|=(clkset);\
			};



	//#define ZD_FSYS_CLKSET(clkset) ZD_NOP //该配置在烧录时用选项写入，用空指令代替

	#define ZD_TIMER0_LOAD_H TH0
	#define ZD_TIMER0_LOAD_L TL0
	#define ZD_TIMER0_LOAD_RELOAD TH0
	#define ZD_TIMER0_LOAD TL0
			

	#define ZD_TIMER0_CLKSET_FSYS 0x00
	#define ZD_TIMER0_CLKSET_T0CKI 0x02
	#define ZD_TIMER0_CLKSET_DEFAULT ZD_TIMER0_CLKSET_FSYS
	
	#define ZD_TIMER0_CLKSET(clkset) TMOD&=(~(BIT2)),TMOD|=(clkset)


	#define ZD_TIMER0_CLKPSASET_DIV1 0x01
	#define ZD_TIMER0_CLKPSASET_DIV12 0x00
	
	#define ZD_TIMER0_CLKPSASET_DEFAULT ZD_TIMER0_CLKPSASET_DIV12
	
	#define ZD_TIMER0_CLKPSASET(clkset) TMCON&=(~(BIT0)),TMCON|=(clkset)



	#define ZD_TIMER0_MODESET_MODE0 0x00
	#define ZD_TIMER0_MODESET_MODE1 0x01
	#define ZD_TIMER0_MODESET_MODE2 0x02
	#define ZD_TIMER0_MODESET_STOP 0x3

	
	#define ZD_TIMER0_MODESET_DEFAULT ZD_TIMER0_MODESET_MODE2 
	
	#define ZD_TIMER0_MODESET(modeset) TMOD&=(~(BIT0|BIT1)),TMOD|=(modeset)

	#define ZD_TIMER0_INIT ZD_TIMER0_CLKSET(ZD_TIMER0_CLKSET_DEFAULT),ZD_TIMER0_CLKPSASET(ZD_TIMER0_CLKPSASET_DEFAULT),ZD_TIMER0_MODESET(ZD_TIMER0_MODESET_DEFAULT),ZD_T0_ENABLE





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
	
	

#endif