
#ifndef _CHIP_DEVICE_H_
#define _CHIP_DEVICE_H_
//
// Special function register definitions
//


// Register: INDF
volatile unsigned char           INDF                @ 0x000;
// bit and bitfield definitions

// Register: TMR0
volatile unsigned char           TMR0                @ 0x001;
// bit and bitfield definitions

// Register: PCL
volatile unsigned char           PCL                 @ 0x002;
// bit and bitfield definitions

// Register: STATUS
volatile unsigned char           STATUS              @ 0x003;
// bit and bitfield definitions
volatile bit CARRY               @ ((unsigned)&STATUS*8)+0;
volatile bit DC                  @ ((unsigned)&STATUS*8)+1;
volatile bit ZERO                @ ((unsigned)&STATUS*8)+2;
volatile bit nPD                 @ ((unsigned)&STATUS*8)+3;
volatile bit nTO                 @ ((unsigned)&STATUS*8)+4;
volatile bit RP0                 @ ((unsigned)&STATUS*8)+5;
volatile bit RP1                 @ ((unsigned)&STATUS*8)+6;
volatile bit FSRB8               @ ((unsigned)&STATUS*8)+7;

volatile bit C                   @ ((unsigned)&STATUS*8)+0;
volatile bit HC                  @ ((unsigned)&STATUS*8)+1;
volatile bit Z                   @ ((unsigned)&STATUS*8)+2;
volatile bit nPF                 @ ((unsigned)&STATUS*8)+3;
volatile bit nTF                 @ ((unsigned)&STATUS*8)+4;
volatile bit PAGE0               @ ((unsigned)&STATUS*8)+5;
volatile bit PAGE1               @ ((unsigned)&STATUS*8)+6;

#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	CARRY               : 1;
        unsigned	DC                  : 1;
        unsigned	ZERO                : 1;
        unsigned	nPD                 : 1;
        unsigned	nTO                 : 1;
        unsigned	RP                  : 2;
        unsigned	FSRB8              : 1;
    };
    struct {
        unsigned	                    : 5;
        unsigned	RP0                 : 1;
        unsigned	RP1                 : 1;
    };
    struct {
        unsigned	C                   : 1;
        unsigned	HC                  : 1;
        unsigned	Z                   : 1;
        unsigned	nPF                 : 1;
        unsigned	nTF                 : 1;
        unsigned	PAGE                : 2;
    };
    struct {
        unsigned	                    : 5;
        unsigned	PAGE0               : 1;
        unsigned	PAGE1               : 1;
    };
} STATUSbits @ 0x003;
#endif

// Register: FSR
volatile unsigned char           FSR                 @ 0x004;
// bit and bitfield definitions

// Register: PORTA
volatile unsigned char           PORTA               @ 0x005;
// bit and bitfield definitions
volatile bit RA0                 @ ((unsigned)&PORTA*8)+0;
volatile bit RA1                 @ ((unsigned)&PORTA*8)+1;
volatile bit RA2                 @ ((unsigned)&PORTA*8)+2;
volatile bit RA3                 @ ((unsigned)&PORTA*8)+3;
volatile bit RA4                 @ ((unsigned)&PORTA*8)+4;
volatile bit RA5                 @ ((unsigned)&PORTA*8)+5;
volatile bit RA6                 @ ((unsigned)&PORTA*8)+6;
volatile bit RA7                 @ ((unsigned)&PORTA*8)+7;

volatile bit PA0                 @ ((unsigned)&PORTA*8)+0;
volatile bit PA1                 @ ((unsigned)&PORTA*8)+1;
volatile bit PA2                 @ ((unsigned)&PORTA*8)+2;
volatile bit PA3                 @ ((unsigned)&PORTA*8)+3;
volatile bit PA4                 @ ((unsigned)&PORTA*8)+4;
volatile bit PA5                 @ ((unsigned)&PORTA*8)+5;
volatile bit PA6                 @ ((unsigned)&PORTA*8)+6;
volatile bit PA7                 @ ((unsigned)&PORTA*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	RA0                 : 1;
        unsigned	RA1                 : 1;
        unsigned	RA2                 : 1;
        unsigned	RA3                 : 1;
        unsigned	RA4                 : 1;
        unsigned	RA5                 : 1;
        unsigned	RA6                 : 1;
        unsigned	RA7                 : 1;
    };
	struct {
        unsigned	PA0                 : 1;
        unsigned	PA1                 : 1;
        unsigned	PA2                 : 1;
        unsigned	PA3                 : 1;
        unsigned	PA4                 : 1;
        unsigned	PA5                 : 1;
        unsigned	PA6                 : 1;
        unsigned	PA7                 : 1;
    };
    struct {
        unsigned	RA                  : 8;
    };
    struct {
        unsigned	PA                  : 8;
    };
} PORTAbits @ 0x005;
#endif

// Register: PORTB
volatile unsigned char           PORTB               @ 0x006;
// bit and bitfield definitions
volatile bit RB0                 @ ((unsigned)&PORTB*8)+0;
volatile bit RB1                 @ ((unsigned)&PORTB*8)+1;
volatile bit RB2                 @ ((unsigned)&PORTB*8)+2;
volatile bit RB3                 @ ((unsigned)&PORTB*8)+3;
volatile bit RB4                 @ ((unsigned)&PORTB*8)+4;
volatile bit RB5                 @ ((unsigned)&PORTB*8)+5;
volatile bit RB6                 @ ((unsigned)&PORTB*8)+6;
volatile bit RB7                 @ ((unsigned)&PORTB*8)+7;

volatile bit PB0                 @ ((unsigned)&PORTB*8)+0;
volatile bit PB1                 @ ((unsigned)&PORTB*8)+1;
volatile bit PB2                 @ ((unsigned)&PORTB*8)+2;
volatile bit PB3                 @ ((unsigned)&PORTB*8)+3;
volatile bit PB4                 @ ((unsigned)&PORTB*8)+4;
volatile bit PB5                 @ ((unsigned)&PORTB*8)+5;
volatile bit PB6                 @ ((unsigned)&PORTB*8)+6;
volatile bit PB7                 @ ((unsigned)&PORTB*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	RB0                 : 1;
        unsigned	RB1                 : 1;
        unsigned	RB2                 : 1;
        unsigned	RB3                 : 1;
        unsigned	RB4                 : 1;
        unsigned	RB5                 : 1;
        unsigned	RB6                 : 1;
        unsigned	RB7                 : 1;
    };
	struct {
        unsigned	PB0                 : 1;
        unsigned	PB1                 : 1;
        unsigned	PB2                 : 1;
        unsigned	PB3                 : 1;
        unsigned	PB4                 : 1;
        unsigned	PB5                 : 1;
        unsigned	PB6                 : 1;
        unsigned	PB7                 : 1;
    };
    struct {
        unsigned	RB                  : 8;
    };
    struct {
        unsigned	PB                  : 8;
    };
} PORTBbits @ 0x006;
#endif
// Register: PORTC
volatile unsigned char           PORTC               @ 0x007;
// bit and bitfield definitions
volatile bit RC0                 @ ((unsigned)&PORTC*8)+0;
volatile bit RC1                 @ ((unsigned)&PORTC*8)+1;

volatile bit PC0                 @ ((unsigned)&PORTC*8)+0;
volatile bit PC1                 @ ((unsigned)&PORTC*8)+1;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	RC0                 : 1;
        unsigned	RC1                 : 1;
    };
    struct {
        unsigned	RC                  : 2;
    };
	
	struct {
        unsigned	PC0                 : 1;
        unsigned	PC1                 : 1;
    };
    struct {
        unsigned	PC                  : 2;
    };
} PORTCbits @ 0x007;
#endif

// Register: P1DDTL
volatile unsigned char           P1DDTL              @ 0x008;
// Register: P1DDTL
volatile unsigned char           P1DDTH              @ 0x009;
// bit and bitfield definitions
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	P1DDTH0                    : 1;
        unsigned	P1DDTH1                    : 1;
        unsigned	P1DDTH2                    : 1;
        unsigned	P1DDTH3                    : 1;
        unsigned	P1DDTH4                    : 1;
        unsigned	P1DDTH5                    : 1;
        unsigned	P1DDTH6                    : 1;
        unsigned	P1DDTH7                    : 1;
    };
    struct {
        unsigned	P1DDTH                    : 8;
    };
} P1DDTHbits @ 0x009;
#endif
// Register: PCLATH
volatile unsigned char           PCLATH              @ 0x00A;
// bit and bitfield definitions
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	PCLATH0                    : 1;
        unsigned	PCLATH1                    : 1;
        unsigned	PCLATH2                    : 1;
        unsigned	PCLATH3                    : 1;
        unsigned	PCLATH4                    : 1;
    };
    struct {
        unsigned	PCLATH                    : 5;
    };
} PCLATHbits @ 0x00A;
#endif

// Register: INTCON
volatile unsigned char           INTCON              @ 0x00B;
// bit and bitfield definitions
volatile bit PAIF                @ ((unsigned)&INTCON*8)+0;
volatile bit INTF                @ ((unsigned)&INTCON*8)+1;
volatile bit T0IF                @ ((unsigned)&INTCON*8)+2;
volatile bit PAIE                @ ((unsigned)&INTCON*8)+3;
volatile bit INTE                @ ((unsigned)&INTCON*8)+4;
volatile bit T0IE                @ ((unsigned)&INTCON*8)+5;
volatile bit PEIE                @ ((unsigned)&INTCON*8)+6;
volatile bit GIE                 @ ((unsigned)&INTCON*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	PAIF                : 1;
        unsigned	INTF                : 1;
        unsigned	T0IF                : 1;
        unsigned	PAIE                : 1;
        unsigned	INTE                : 1;
        unsigned	T0IE                : 1;
        unsigned	PEIE                : 1;
        unsigned	GIE                 : 1;
    };
} INTCONbits @ 0x00B;
#endif

// Register: PIR1
volatile unsigned char           PIR1                @ 0x00C;
// bit and bitfield definitions
volatile bit ADCIF                @ ((unsigned)&PIR1*8)+0;
volatile bit TMR2IF               @ ((unsigned)&PIR1*8)+1;
volatile bit OSFIF                @ ((unsigned)&PIR1*8)+2;
volatile bit TMR1IF               @ ((unsigned)&PIR1*8)+3;
volatile bit ACMPIF               @ ((unsigned)&PIR1*8)+4;
volatile bit LVDIF                @ ((unsigned)&PIR1*8)+5;
volatile bit CKMIF                @ ((unsigned)&PIR1*8)+6;
volatile bit EEIF                 @ ((unsigned)&PIR1*8)+7;

#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	ADCIF        			  : 1;
        unsigned	TMR2IF              : 1;
        unsigned	OSFIF         			: 1;
        unsigned	TMR1IF          		: 1;
        unsigned	ACMPIF          		: 1;
        unsigned	LVDIF               : 1;
        unsigned	CKMIF               : 1;
        unsigned	EEIF                : 1;
    };
} PIR1bits @ 0x00C;
#endif

// Register: FOSCCAL
volatile unsigned char           FOSCCAL             @ 0x00D;
// Register: P1ADTL
volatile unsigned char           P1ADTL              @ 0x00E;
// bit and bitfield definitions

// Register: P1BDTL
volatile unsigned char           P1BDTL              @ 0x00F;
// bit and bitfield definitions

// Register: P1CDTL
volatile unsigned char           P1CDTL              @ 0x0010;

// Register: TMR2L
volatile unsigned char           TMR2L               @ 0x011;
// bit and bitfield definitions

// Register: T2CON
volatile unsigned char           T2CON0               @ 0x012;
// bit and bitfield definitions
volatile bit T2CKPS0             @ ((unsigned)&T2CON0*8)+0;
volatile bit T2CKPS1             @ ((unsigned)&T2CON0*8)+1;
volatile bit TMR2ON              @ ((unsigned)&T2CON0*8)+2;
volatile bit TOUTPS0             @ ((unsigned)&T2CON0*8)+3;
volatile bit TOUTPS1             @ ((unsigned)&T2CON0*8)+4;
volatile bit TOUTPS2             @ ((unsigned)&T2CON0*8)+5;
volatile bit TOUTPS3             @ ((unsigned)&T2CON0*8)+6;
volatile bit PR2U                @ ((unsigned)&T2CON0*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	T2CKPS              : 2;
        unsigned	                    : 1;
        unsigned	TOUTPS              : 4;
    };
    struct {
        unsigned	T2CKPS0             : 1;
        unsigned	T2CKPS1             : 1;
        unsigned	TMR2ON              : 1;
        unsigned	TOUTPS0             : 1;
        unsigned	TOUTPS1             : 1;
        unsigned	TOUTPS2             : 1;
        unsigned	TOUTPS3             : 1;
        unsigned	PR2U                : 1;
    };
} T2CON0bits @ 0x012;
#endif
// bit and bitfield definitions

// Register: TMR2H
volatile unsigned char           TMR2H                 @ 0x013;
// bit and bitfield definitions

// Register: P1ADTH
volatile unsigned char           P1ADTH                @ 0x014;
// bit and bitfield definitions

// Register: P1BDTH
volatile unsigned char           P1BDTH                @ 0x015;
// bit and bitfield definitions

// Register: P1CON
volatile unsigned char           P1CON               @ 0x016;
// bit and bitfield definitions
volatile bit P1DC0                 @ ((unsigned)&P1CON*8)+0;
volatile bit P1DC1                 @ ((unsigned)&P1CON*8)+1;
volatile bit P1DC2                 @ ((unsigned)&P1CON*8)+2;
volatile bit P1DC3                 @ ((unsigned)&P1CON*8)+3;
volatile bit P1DC4                 @ ((unsigned)&P1CON*8)+4;
volatile bit P1DC5                 @ ((unsigned)&P1CON*8)+5;
volatile bit P1DC6                 @ ((unsigned)&P1CON*8)+6;
volatile bit P1AUE                @ ((unsigned)&P1CON*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	P1DC                 : 7;
    };
    struct {
        unsigned	P1DC0                : 1;
        unsigned	P1DC1                : 1;
        unsigned	P1DC2                : 1;
        unsigned	P1DC3                : 1;
        unsigned	P1DC4                : 1;
        unsigned	P1DC5                : 1;
        unsigned	P1DC6                : 1;
        unsigned	P1AUE               : 1;
    };
} P1CONbits @ 0x016;
#endif
// bit and bitfield definitions

// Register: P1BR0
volatile unsigned char           P1BR0               @ 0x017;
// bit and bitfield definitions
volatile bit P1ASS0                 @ ((unsigned)&P1BR0*8)+0;
volatile bit P1ASS1                 @ ((unsigned)&P1BR0*8)+1;
volatile bit P1BSS0                 @ ((unsigned)&P1BR0*8)+2;
volatile bit P1BSS1                 @ ((unsigned)&P1BR0*8)+3;
volatile bit P1BKS0                 @ ((unsigned)&P1BR0*8)+4;
volatile bit P1BKS1                 @ ((unsigned)&P1BR0*8)+5;
volatile bit P1BKS2                 @ ((unsigned)&P1BR0*8)+6;
volatile bit P1BEVT                 @ ((unsigned)&P1BR0*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	P1ASS               : 2;
        unsigned	P1BSS               : 2;
        unsigned	P1BKS               : 3;
        unsigned	P1BEVT              : 1;
    };
    struct {
        unsigned	P1ASS0              : 1;
        unsigned	P1ASS1              : 1;
        unsigned	P1BSS0              : 1;
        unsigned	P1BSS1              : 1;
        unsigned	P1BKS0              : 1;
        unsigned	P1BKS1              : 1;
        unsigned	P1BKS2              : 1;
    };
} P1BR0bits @ 0x017;
#endif
// bit and bitfield definitions
// Register: WDTCON
volatile unsigned char           WDTCON             @ 0x018;
// bit and bitfield definitions
volatile bit SWDTEN                @ ((unsigned)&WDTCON*8)+0;
volatile bit WDTPS0                @ ((unsigned)&WDTCON*8)+1;
volatile bit WDTPS1                @ ((unsigned)&WDTCON*8)+2;
volatile bit WDTPS2                @ ((unsigned)&WDTCON*8)+3;
volatile bit WDTPS3                @ ((unsigned)&WDTCON*8)+4;
volatile bit WCKSRC0               @ ((unsigned)&WDTCON*8)+5;
volatile bit WCKSRC1               @ ((unsigned)&WDTCON*8)+6;

#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	                    : 1;
        unsigned	WDTPS               : 4;
        unsigned	WCKSRC              : 2;
    };
    struct {
        unsigned	SWDTEN             : 1;
        unsigned	WDTPS0             : 1;
        unsigned	WDTPS1             : 1;
        unsigned	WDTPS2             : 1;
        unsigned	WDTPS3             : 1;
        unsigned	WCKSRC0            : 1;
        unsigned	WCKSRC1            : 1;
    };
} WDTCONbits @ 0x018;
#endif

// Register: P1BR1
volatile unsigned char           P1BR1             @ 0x019;
// bit and bitfield definitions
volatile bit P1CSS0                @ ((unsigned)&P1BR1*8)+0;
volatile bit P1CSS1                @ ((unsigned)&P1BR1*8)+1;
volatile bit P1C2SS0               @ ((unsigned)&P1BR1*8)+2;
volatile bit P1C2SS1               @ ((unsigned)&P1BR1*8)+3;
volatile bit P1DSS0                @ ((unsigned)&P1BR1*8)+4;
volatile bit P1DSS1                @ ((unsigned)&P1BR1*8)+5;
volatile bit P1D2SS0               @ ((unsigned)&P1BR1*8)+6;
volatile bit P1D2SS1               @ ((unsigned)&P1BR1*8)+7;

#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	P1CSS                 : 2;
        unsigned	P1C2SS					      : 2;
        unsigned	P1DSS                 : 2;
        unsigned	P1D2SS                : 2;
    };
    struct {
        unsigned	P1CSS0                : 1;
        unsigned	P1CSS1                : 1;
        unsigned	P1C2SS0               : 1;
        unsigned	P1C2SS1               : 1;
        unsigned	P1DSS0                : 1;
        unsigned	P1DSS1                : 1;
        unsigned	P1D2SS0               : 1;
        unsigned	P1D2SS1               : 1;
    };
} P1BR1bits @ 0x019;
#endif

// Register: P1CDTH
volatile unsigned char           P1CDTH             @ 0x01A;

// Register: MSCON0
volatile unsigned char           MSCON0         @ 0x01B;
// bit and bitfield definitions
volatile bit T2CKRUN                  @ ((unsigned)&MSCON0*8)+0;
volatile bit CKCNTI                   @ ((unsigned)&MSCON0*8)+1;
volatile bit CKMAVG                   @ ((unsigned)&MSCON0*8)+2;
volatile bit SLVREN                   @ ((unsigned)&MSCON0*8)+3;
volatile bit CLKOS                    @ ((unsigned)&MSCON0*8)+4;
volatile bit ROMLPE                   @ ((unsigned)&MSCON0*8)+5;
volatile bit LVROE                    @ ((unsigned)&MSCON0*8)+6;
volatile bit BGRBOE                   @ ((unsigned)&MSCON0*8)+7;

#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	T2CKRUN               : 1;
        unsigned	CKCNTI                : 1;
        unsigned	CKMAVG                : 1;
        unsigned	SLVREN                : 1;
        unsigned	CLKOS                 : 1;
        unsigned	ROMLPE						    : 1;
        unsigned	LVROE                 : 1;
        unsigned	BGRBOE                : 1;
    };
} MSCON0bits @ 0x01B;
#endif

// Register: SOSCPRL
volatile unsigned char           SOSCPRL             @ 0x01C;
// bit and bitfield definitions

// Register: SOSCPRH
volatile unsigned char           SOSCPRH              @ 0x01D;
// bit and bitfield definitions

// Register: P1AUX
volatile unsigned char           P1AUX               @ 0x01E;
// bit and bitfield definitions
volatile bit P1DF2                    @ ((unsigned)&P1AUX*8)+0;
volatile bit P1DF2E                   @ ((unsigned)&P1AUX*8)+1;
volatile bit P1CF2                    @ ((unsigned)&P1AUX*8)+2;
volatile bit P1CF2E                   @ ((unsigned)&P1AUX*8)+3;
volatile bit P1B2SS0                  @ ((unsigned)&P1AUX*8)+4;
volatile bit P1B2SS1                  @ ((unsigned)&P1AUX*8)+5;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	P1DF2               : 1;
        unsigned	P1DF2E              : 1;
        unsigned	P1CF2               : 1;
        unsigned	P1CF2E              : 1;
        unsigned	P1B2SS0             : 1;
        unsigned	P1B2SS1             : 1;
    };
} P1AUXbits @ 0x01E;
#endif

//
// Register: T0CON0
volatile unsigned char           T0CON0             @ 0x01F;
// bit and bitfield definitions
volatile bit T0CKSRC0                  @ ((unsigned)&T0CON0*8)+0;
volatile bit T0CKSRC1                  @ ((unsigned)&T0CON0*8)+1;
volatile bit T0CKRUN                   @ ((unsigned)&T0CON0*8)+2;
volatile bit T0ON                      @ ((unsigned)&T0CON0*8)+3;

#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	T0CKSRC0             : 1;
        unsigned	T0CKSRC1             : 1;
        unsigned	T0CKRUN              : 1;
        unsigned	T0ON                 : 1;
    };
} T0CON0bits @ 0x01F;
#endif
// Special function register definitions: Bank 1
//


// Register: OPTION_REG
volatile unsigned char           OPTION          @ 0x081;
// bit and bitfield definitions
volatile bit PS0                 @ ((unsigned)&OPTION*8)+0;
volatile bit PS1                 @ ((unsigned)&OPTION*8)+1;
volatile bit PS2                 @ ((unsigned)&OPTION*8)+2;
volatile bit PSA                 @ ((unsigned)&OPTION*8)+3;
volatile bit T0SE                @ ((unsigned)&OPTION*8)+4;
volatile bit T0CS                @ ((unsigned)&OPTION*8)+5;
volatile bit INTEDG              @ ((unsigned)&OPTION*8)+6;
volatile bit nPAPU               @ ((unsigned)&OPTION*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	PS                  : 3;
        unsigned	PSA                 : 1;
        unsigned	T0SE                : 1;
        unsigned	T0CS                : 1;
        unsigned	INTEDG              : 1;
        unsigned	nPAPU               : 1;
    };
    struct {
        unsigned	PS0                 : 1;
        unsigned	PS1                 : 1;
        unsigned	PS2                 : 1;
    };
} OPTIONbits @ 0x081;
#endif

// Register: TRISA
volatile unsigned char           TRISA               @ 0x085;
// bit and bitfield definitions
volatile bit TRISA0              @ ((unsigned)&TRISA*8)+0;
volatile bit TRISA1              @ ((unsigned)&TRISA*8)+1;
volatile bit TRISA2              @ ((unsigned)&TRISA*8)+2;
volatile bit TRISA3              @ ((unsigned)&TRISA*8)+3;
volatile bit TRISA4              @ ((unsigned)&TRISA*8)+4;
volatile bit TRISA5              @ ((unsigned)&TRISA*8)+5;
volatile bit TRISA6              @ ((unsigned)&TRISA*8)+6;
volatile bit TRISA7              @ ((unsigned)&TRISA*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	TRISA0              : 1;
        unsigned	TRISA1              : 1;
        unsigned	TRISA2              : 1;
        unsigned	TRISA3              : 1;
        unsigned	TRISA4              : 1;
        unsigned	TRISA5              : 1;
        unsigned	TRISA6              : 1;
        unsigned	TRISA7              : 1;
    };
    struct {
        unsigned	TRISA               : 8;
    };
} TRISAbits @ 0x085;
#endif

// Register: TRISB
volatile unsigned char           TRISB               @ 0x086;
// bit and bitfield definitions
volatile bit TRISB0              @ ((unsigned)&TRISB*8)+0;
volatile bit TRISB1              @ ((unsigned)&TRISB*8)+1;
volatile bit TRISB2              @ ((unsigned)&TRISB*8)+2;
volatile bit TRISB3              @ ((unsigned)&TRISB*8)+3;
volatile bit TRISB4              @ ((unsigned)&TRISB*8)+4;
volatile bit TRISB5              @ ((unsigned)&TRISB*8)+5;
volatile bit TRISB6              @ ((unsigned)&TRISB*8)+6;
volatile bit TRISB7              @ ((unsigned)&TRISB*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	TRISB0              : 1;
        unsigned	TRISB1              : 1;
        unsigned	TRISB2              : 1;
        unsigned	TRISB3              : 1;
        unsigned	TRISB4              : 1;
        unsigned	TRISB5              : 1;
        unsigned	TRISB6              : 1;
        unsigned	TRISB7              : 1;
    };
    struct {
        unsigned	TRISB               : 8;
    };
} TRISBbits @ 0x086;
#endif

// Register: TRISC
volatile unsigned char           TRISC               @ 0x087;
// bit and bitfield definitions
volatile bit TRISC0              @ ((unsigned)&TRISC*8)+0;
volatile bit TRISC1              @ ((unsigned)&TRISC*8)+1;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	TRISC               : 2;
    };
    struct {
        unsigned	TRISC0              : 1;
        unsigned	TRISC1              : 1;
    };
} TRISCbits @ 0x087;
#endif

// Register: PSRCB1
volatile unsigned char           PSRCB1               @ 0x088;
// bit and bitfield definitions

// Register: WPDA
volatile unsigned char           WPDA               @ 0x089;
// bit and bitfield definitions
volatile bit WPDA0              @ ((unsigned)&WPDA*8)+0;
volatile bit WPDA1              @ ((unsigned)&WPDA*8)+1;
volatile bit WPDA2              @ ((unsigned)&WPDA*8)+2;
volatile bit WPDA3              @ ((unsigned)&WPDA*8)+3;
volatile bit WPDA4              @ ((unsigned)&WPDA*8)+4;
volatile bit WPDA5              @ ((unsigned)&WPDA*8)+5;
volatile bit WPDA6              @ ((unsigned)&WPDA*8)+6;
volatile bit WPDA7              @ ((unsigned)&WPDA*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	WPDA0              : 1;
        unsigned	WPDA1              : 1;
        unsigned	WPDA2              : 1;
        unsigned	WPDA3              : 1;
        unsigned	WPDA4              : 1;
        unsigned	WPDA5              : 1;
        unsigned	WPDA6              : 1;
        unsigned	WPDA7              : 1;
    };
} WPDAbits @ 0x089;
#endif

// Register: PIE1
volatile unsigned char           PIE1                @ 0x08C;
// bit and bitfield definitions
volatile bit ADCIE               @ ((unsigned)&PIE1*8)+0;
volatile bit TMR2IE              @ ((unsigned)&PIE1*8)+1;
volatile bit OSFIE               @ ((unsigned)&PIE1*8)+2;
volatile bit TMR1IE              @ ((unsigned)&PIE1*8)+3;
volatile bit ACMPIE              @ ((unsigned)&PIE1*8)+4;
volatile bit LVDIE               @ ((unsigned)&PIE1*8)+5;
volatile bit CKMIE               @ ((unsigned)&PIE1*8)+6;
volatile bit EEIE                @ ((unsigned)&PIE1*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	ADCIE               : 1;
        unsigned	TMR2IE              : 1;
        unsigned	OSFIE               : 1;
        unsigned	TMR1IE              : 1;
        unsigned	ACMPIE              : 1;
        unsigned	LVDIE               : 1;
        unsigned	CKMIE               : 1;
        unsigned	EEIE                : 1;
    };
} PIE1bits @ 0x08C;
#endif

// Register: WPDC
volatile unsigned char           WPDC                @ 0x08D;
// bit and bitfield definitions
volatile bit WPDC0              @ ((unsigned)&WPDC*8)+0;
volatile bit WPDC1              @ ((unsigned)&WPDC*8)+1;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	WPDC0               : 1;
        unsigned	WPDC1               : 1;
        unsigned	                    : 6;
    };
} WPDCbits @ 0x08D;
#endif

// Register: PCON
volatile unsigned char           PCON                @ 0x08E;
// bit and bitfield definitions
volatile bit nBOR                @ ((unsigned)&PCON*8)+0;
volatile bit nPOR                @ ((unsigned)&PCON*8)+1;
volatile bit LVDW                @ ((unsigned)&PCON*8)+2;
volatile bit LVDEN               @ ((unsigned)&PCON*8)+3;
volatile bit LVDL0               @ ((unsigned)&PCON*8)+4;
volatile bit LVDL1               @ ((unsigned)&PCON*8)+5;
volatile bit LVDL2               @ ((unsigned)&PCON*8)+6;
volatile bit LVDL3               @ ((unsigned)&PCON*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	                    : 4;
        unsigned	LVDL                : 4;
        	
    };
    struct {
        unsigned	nBOR                : 1;
        unsigned	nPOR                : 1;
        unsigned	LVDW                : 1;
        unsigned	LVDEN               : 1;
        unsigned	LVDL0               : 1;
        unsigned	LVDL1               : 1;
        unsigned	LVDL2               : 1;
        unsigned	LVDL3               : 1;
    };
} PCONbits @ 0x08E;
#endif

// Register: OSCCON
volatile unsigned char           OSCCON              @ 0x08F;
// bit and bitfield definitions
volatile bit SCS                    @ ((unsigned)&OSCCON*8)+0;
volatile bit LTS                    @ ((unsigned)&OSCCON*8)+1;
volatile bit HTS                    @ ((unsigned)&OSCCON*8)+2;
volatile bit OSTS                   @ ((unsigned)&OSCCON*8)+3;
volatile bit IRCF0                  @ ((unsigned)&OSCCON*8)+4;
volatile bit IRCF1                  @ ((unsigned)&OSCCON*8)+5;
volatile bit IRCF2                  @ ((unsigned)&OSCCON*8)+6;
volatile bit LFMOD                  @ ((unsigned)&OSCCON*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	                       : 4;
        unsigned	IRCF                	 : 3;
    };
    struct {
        unsigned	SCS                    : 1;
        unsigned	LTS                    : 1;
        unsigned	HTS                    : 1;
        unsigned	OSTS                   : 1;
        unsigned	IRCF0                  : 1;
        unsigned	IRCF1                  : 1;
        unsigned	IRCF2                  : 1;
        unsigned	LFMOD                  : 1;
    };
} OSCCONbits @ 0x08F;
#endif

// Register: P1OE
volatile unsigned char           P1OE              @ 0x090;
// bit and bitfield definitions
volatile bit P1A0OE                   @ ((unsigned)&P1OE*8)+0;
volatile bit P1A0NOE                  @ ((unsigned)&P1OE*8)+1;
volatile bit P1A1OE                   @ ((unsigned)&P1OE*8)+2;
volatile bit P1A1NOE                  @ ((unsigned)&P1OE*8)+3;
volatile bit P1A2OE                   @ ((unsigned)&P1OE*8)+4;
volatile bit P1A2NOE                  @ ((unsigned)&P1OE*8)+5;
volatile bit P1B0OE                   @ ((unsigned)&P1OE*8)+6;
volatile bit P1C0OE                   @ ((unsigned)&P1OE*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	P1A0OE                     : 1;
        unsigned	P1A0NOE                    : 1;
        unsigned	P1A1OE                     : 1;
        unsigned	P1A1NOE                    : 1;
        unsigned	P1A2OE                	   : 1;
        unsigned	P1A2NOE                    : 1;
        unsigned	P1B0OE                	   : 1;
        unsigned	P1C0OE                     : 1;
    };
} P1OEbits @ 0x090;
#endif

// Register: PR2L
volatile unsigned char           PR2L                @ 0x091;
// bit and bitfield definitions

// Register: PR2H
volatile unsigned char           PR2H                @ 0x092;
// bit and bitfield definitions

// Register: WPUC
volatile unsigned char           WPUC                @ 0x093;
// bit and bitfield definitions
volatile bit WPUC0               @ ((unsigned)&WPUC*8)+0;
volatile bit WPUC1               @ ((unsigned)&WPUC*8)+1;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	WPUC0               : 1;
        unsigned	WPUC1               : 1;
    };
    struct {
        unsigned	WPUC                : 2;
    };
} WPUCbits @ 0x093;
#endif

// Register: PSRCC
volatile unsigned char           PSRCC                @ 0x094;
// bit and bitfield definitions
volatile bit PSRCC0               @ ((unsigned)&PSRCC*8)+0;
volatile bit PSRCC1               @ ((unsigned)&PSRCC*8)+1;
volatile bit PSRCC2               @ ((unsigned)&PSRCC*8)+2;
volatile bit PSRCC3               @ ((unsigned)&PSRCC*8)+3;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	PSRCC0               : 1;
        unsigned	PSRCC1               : 1;
        unsigned	PSRCC2               : 1;
        unsigned	PSRCC3               : 1;
    };
    struct {
        unsigned	PSRCC                : 4;
    };
} PSRCCbits @ 0x094;
#endif

// Register: WPUA
volatile unsigned char           WPUA                @ 0x095;
// bit and bitfield definitions
volatile bit WPUA0               @ ((unsigned)&WPUA*8)+0;
volatile bit WPUA1               @ ((unsigned)&WPUA*8)+1;
volatile bit WPUA2               @ ((unsigned)&WPUA*8)+2;
volatile bit WPUA3               @ ((unsigned)&WPUA*8)+3;
volatile bit WPUA4               @ ((unsigned)&WPUA*8)+4;
volatile bit WPUA5               @ ((unsigned)&WPUA*8)+5;
volatile bit WPUA6               @ ((unsigned)&WPUA*8)+6;
volatile bit WPUA7               @ ((unsigned)&WPUA*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	WPUA0               : 1;
        unsigned	WPUA1               : 1;
        unsigned	WPUA2               : 1;
        unsigned	WPUA3               : 1;
        unsigned	WPUA4               : 1;
        unsigned	WPUA5               : 1;
        unsigned	WPUA6               : 1;
        unsigned	WPUA7               : 1;
    };
    struct {
        unsigned	WPUA                : 8;
    };
} WPUAbits @ 0x095;
#endif
// Register: IOCA
volatile unsigned char           IOCA                @ 0x096;
volatile unsigned char           IOC                 @ 0x096;
// bit and bitfield definitions
volatile bit IOCA0               @ ((unsigned)&IOCA*8)+0;
volatile bit IOCA1               @ ((unsigned)&IOCA*8)+1;
volatile bit IOCA2               @ ((unsigned)&IOCA*8)+2;
volatile bit IOCA3               @ ((unsigned)&IOCA*8)+3;
volatile bit IOCA4               @ ((unsigned)&IOCA*8)+4;
volatile bit IOCA5               @ ((unsigned)&IOCA*8)+5;
volatile bit IOCA6               @ ((unsigned)&IOCA*8)+6;
volatile bit IOCA7               @ ((unsigned)&IOCA*8)+7;

volatile bit IOC0                @ ((unsigned)&IOCA*8)+0;
volatile bit IOC1                @ ((unsigned)&IOCA*8)+1;
volatile bit IOC2                @ ((unsigned)&IOCA*8)+2;
volatile bit IOC3                @ ((unsigned)&IOCA*8)+3;
volatile bit IOC4                @ ((unsigned)&IOCA*8)+4;
volatile bit IOC5                @ ((unsigned)&IOCA*8)+5;
volatile bit IOC6                @ ((unsigned)&IOCA*8)+6;
volatile bit IOC7                @ ((unsigned)&IOCA*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	IOCA               : 8;
    };
    struct {
        unsigned	IOC                : 8;
    };
} IOCAbits @ 0x096;
#endif

// Register: VRP5VCAL
volatile unsigned char           VRP5VCAL           @ 0x097;
// bit and bitfield definitions

// Register: P1POL
volatile unsigned char           P1POL              @ 0x099;
// bit and bitfield definitions
volatile bit P1A0P              @ ((unsigned)&P1POL*8)+0;
volatile bit P1A0NP             @ ((unsigned)&P1POL*8)+1;
volatile bit P1A1P              @ ((unsigned)&P1POL*8)+2;
volatile bit P1A1NP             @ ((unsigned)&P1POL*8)+3;
volatile bit P1A2P              @ ((unsigned)&P1POL*8)+4;
volatile bit P1A2NP             @ ((unsigned)&P1POL*8)+5;
volatile bit P1BOP              @ ((unsigned)&P1POL*8)+6;
volatile bit P1C0P              @ ((unsigned)&P1POL*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	P1A0P                 : 1;
        unsigned	P1A0NP                : 1;
        unsigned	P1A1P                 : 1;
        unsigned	P1A1NP                : 1;
        unsigned	P1A2P                 : 1;
        unsigned	P1A2NP                : 1;
        unsigned	P1BOP                 : 1;
        unsigned	P1C0P                 : 1;
    };
} P1POLbits @ 0x099;
#endif

// Register: EEDAT
volatile unsigned char           EEDAT              @ 0x09A;
volatile unsigned char           EEDATA             @ 0x09A;
// bit and bitfield definitions

// Register: EEADR
volatile unsigned char           EEADR              @ 0x09B;
// bit and bitfield definitions


// Register: EECON1
volatile unsigned char           EECON1              @ 0x09C;
// bit and bitfield definitions
volatile bit RD                  @ ((unsigned)&EECON1*8)+0;
volatile bit PONLY               @ ((unsigned)&EECON1*8)+1;
volatile bit WREN1               @ ((unsigned)&EECON1*8)+2;
volatile bit WRERR               @ ((unsigned)&EECON1*8)+3;
volatile bit WREN2               @ ((unsigned)&EECON1*8)+4;
volatile bit WREN3               @ ((unsigned)&EECON1*8)+5;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	RD                  : 1;
        unsigned	PONLY               : 1;
        unsigned	WREN1               : 1;
        unsigned	WRERR               : 1;
        unsigned	WREN2               : 1;
        unsigned	WREN3               : 1;
    };
} EECON1bits @ 0x09C;
#endif

// Register: EECON2
volatile unsigned char           EECON2             @ 0x09D;
// bit and bitfield definitions
volatile bit WR                  @ ((unsigned)&EECON2*8)+0;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	WR                  : 1;
    };
} EECON2bits @ 0x09d;
#endif

// Register: T2CON1
volatile unsigned char           T2CON1             @ 0x09E;
// bit and bitfield definitions
volatile bit T2CKSRC0                @ ((unsigned)&T2CON1*8)+0;
volatile bit T2CKSRC1                @ ((unsigned)&T2CON1*8)+1;
volatile bit T2CKSRC2                @ ((unsigned)&T2CON1*8)+2;
volatile bit P1BZM                   @ ((unsigned)&T2CON1*8)+3;
volatile bit P1OS                    @ ((unsigned)&T2CON1*8)+4;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	T2CKSRC0           : 1;
        unsigned	T2CKSRC1           : 1;
        unsigned	T2CKSRC2           : 1;
        unsigned	P1BZM              : 1;
        unsigned	P1OS               : 1;
    };
    struct {
        unsigned	T2CKSRC            : 3;
    };
} T2CON1bits @ 0x09E;
#endif

// Register: PSINKC
volatile unsigned char           PSINKC             @ 0x09F;
// bit and bitfield definitions
volatile bit PSINKC0                  @ ((unsigned)&PSINKC*8)+0;
volatile bit PSINKC1                  @ ((unsigned)&PSINKC*8)+1;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	PSINKC0                 : 1;
        unsigned	PSINKC1                 : 1;
    };
    struct {
        unsigned	PSINKC                  : 2;
    };
} PSINKCbits @ 0x09F;
#endif

// Special function register definitions: Bank 2
//
// Register: RXRSM
volatile unsigned char           RXRSM          @ 0x0101;
// bit and bitfield definitions
volatile bit RSDATA             @ ((unsigned)&RXRSM*8)+0;
volatile bit REB                @ ((unsigned)&RXRSM*8)+1;
volatile bit RSBST              @ ((unsigned)&RXRSM*8)+2;
volatile bit RSAST              @ ((unsigned)&RXRSM*8)+3;
volatile bit RSVH1X             @ ((unsigned)&RXRSM*8)+4;
volatile bit RSVH1              @ ((unsigned)&RXRSM*8)+5;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	RSDATA             : 1;
        unsigned	REB                : 1;
        unsigned	RSBST              : 1;
        unsigned	RSAST              : 1;
        unsigned	RSVH1X             : 1;
        unsigned	RSVH1              : 1;
    };
} RXRSMbits @ 0x0101;
#endif

// Register: ODCONA
volatile unsigned char           ODCONA          @ 0x0105;
// bit and bitfield definitions

// Register: ODCONA
volatile unsigned char           ODCONB          @ 0x0106;
// bit and bitfield definitions

// Register: ODCONA
volatile unsigned char           ODCONC          @ 0x0107;
// bit and bitfield definitions
volatile bit ODCONC0             @ ((unsigned)&ODCONC*8)+0;
volatile bit ODCONC1             @ ((unsigned)&ODCONC*8)+1;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	ODCONC0             : 1;
        unsigned	ODCONC1             : 1;
    };
    struct {
        unsigned	ODCONC              : 2;
    };
} ODCONCbits @ 0x0107;
#endif

// Register: VR2VCAL
volatile unsigned char           VR2VCAL          @ 0x0108;
// bit and bitfield definitions

// Register: P1POL2
volatile unsigned char           P1POL2          @ 0x0109;
// bit and bitfield definitions
volatile bit P1B1P             @ ((unsigned)&P1POL2*8)+1;
volatile bit P1C1P             @ ((unsigned)&P1POL2*8)+2;
volatile bit P1D0P             @ ((unsigned)&P1POL2*8)+5;
volatile bit P1D1P             @ ((unsigned)&P1POL2*8)+6;
volatile bit P1D2P             @ ((unsigned)&P1POL2*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	                  : 1;
        unsigned	P1B1P             : 1;
        unsigned	P1C1P             : 1;
        unsigned	                  : 2;
        unsigned	P1D0P             : 1;
        unsigned	P1D1P             : 1;
        unsigned	P1D2P             : 1;
    };
} P1POL2bits @ 0x0109;
#endif

// Register: PSRCB2
volatile unsigned char           PSRCB2          @ 0x010C;
// bit and bitfield definitions
volatile bit PSRCB20             @ ((unsigned)&PSRCB2*8)+0;
volatile bit PSRCB21             @ ((unsigned)&PSRCB2*8)+1;
volatile bit PSRCB22             @ ((unsigned)&PSRCB2*8)+2;
volatile bit PSRCB23             @ ((unsigned)&PSRCB2*8)+3;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	PSRCB20           : 1;
        unsigned	PSRCB21           : 1;
        unsigned	PSRCB22           : 1;
        unsigned	PSRCB23           : 1;
    };
    struct {
        unsigned	PSRCB2            : 4;
    };
} PSRCB2bits @ 0x010C;
#endif

// Register: WPUB
volatile unsigned char           WPUB          @ 0x010D;
// bit and bitfield definitions
volatile bit WPUB0              @ ((unsigned)&WPUB*8)+0;
volatile bit WPUB1              @ ((unsigned)&WPUB*8)+1;
volatile bit WPUB2              @ ((unsigned)&WPUB*8)+2;
volatile bit WPUB3              @ ((unsigned)&WPUB*8)+3;
volatile bit WPUB4              @ ((unsigned)&WPUB*8)+4;
volatile bit WPUB5              @ ((unsigned)&WPUB*8)+5;
volatile bit WPUB6              @ ((unsigned)&WPUB*8)+6;
volatile bit WPUB7              @ ((unsigned)&WPUB*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	WPUB              : 8;
    };
    struct {
        unsigned	WPUB0             : 1;
        unsigned	WPUB1             : 1;
        unsigned	WPUB2             : 1;
        unsigned	WPUB3             : 1;
        unsigned	WPUB4             : 1;
        unsigned	WPUB5             : 1;
        unsigned	WPUB6             : 1;
        unsigned	WPUB7             : 1;
    };
} WPUBbits @ 0x010D;
#endif

// Register: WPDB
volatile unsigned char           WPDB          @ 0x010E;
// bit and bitfield definitions
volatile bit WPDB0              @ ((unsigned)&WPDB*8)+0;
volatile bit WPDB1              @ ((unsigned)&WPDB*8)+1;
volatile bit WPDB2              @ ((unsigned)&WPDB*8)+2;
volatile bit WPDB3              @ ((unsigned)&WPDB*8)+3;
volatile bit WPDB4              @ ((unsigned)&WPDB*8)+4;
volatile bit WPDB5              @ ((unsigned)&WPDB*8)+5;
volatile bit WPDB6              @ ((unsigned)&WPDB*8)+6;
volatile bit WPDB7              @ ((unsigned)&WPDB*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	WPDB              : 8;
    };
    struct {
        unsigned	WPDB0             : 1;
        unsigned	WPDB1             : 1;
        unsigned	WPDB2             : 1;
        unsigned	WPDB3             : 1;
        unsigned	WPDB4             : 1;
        unsigned	WPDB5             : 1;
        unsigned	WPDB6             : 1;
        unsigned	WPDB7             : 1;
    };
} WPDBbits @ 0x010E;
#endif

// Register: PSINKB
volatile unsigned char           PSINKB       @ 0x010F;
// bit and bitfield definitions
volatile bit PSINKB2             @ ((unsigned)&PSINKB*8)+2;
volatile bit PSINKB3             @ ((unsigned)&PSINKB*8)+3;
volatile bit PSINKB4             @ ((unsigned)&PSINKB*8)+4;
volatile bit PSINKB5             @ ((unsigned)&PSINKB*8)+5;
volatile bit PSINKB6             @ ((unsigned)&PSINKB*8)+6;
volatile bit PSINKB7             @ ((unsigned)&PSINKB*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	                   : 2;
        unsigned	PSINKB2            : 1;
        unsigned	PSINKB3            : 1;
        unsigned	PSINKB4            : 1;
        unsigned	PSINKB5            : 1;
        unsigned	PSINKB6            : 1;
        unsigned	PSINKB7            : 1;
    };
} PSINKBbits @ 0x010F;
#endif

// Register: LVDCON
volatile unsigned char           LVDCON       @ 0x0110;
// bit and bitfield definitions
volatile bit LVDM0              @ ((unsigned)&LVDCON*8)+0;
volatile bit LVDM1              @ ((unsigned)&LVDCON*8)+1;
volatile bit LVDM2              @ ((unsigned)&LVDCON*8)+2;
volatile bit LVDDEB             @ ((unsigned)&LVDCON*8)+3;
volatile bit LVDP               @ ((unsigned)&LVDCON*8)+4;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	LVDM0             : 1;
        unsigned	LVDM1             : 1;
        unsigned	LVDM2             : 1;
        unsigned	LVDDEB            : 1;
        unsigned	LVDP              : 1;
    };
    struct {
        unsigned	LVDM              : 3;
    };
} LVDCONbits @ 0x0110;
#endif

// Register: ADRESL
volatile unsigned char           ADRESL         @ 0x0111;
// bit and bitfield definitions


// Register: ADRESH
volatile unsigned char           ADRESH         @ 0x0112;
// bit and bitfield definitions

// Register: ADCON0
volatile unsigned char           ADCON0          @ 0x0113;
// bit and bitfield definitions
volatile bit ADON               @ ((unsigned)&ADCON0*8)+0;
volatile bit GO_DONE            @ ((unsigned)&ADCON0*8)+1;
volatile bit ADEX               @ ((unsigned)&ADCON0*8)+2;
volatile bit CHS0               @ ((unsigned)&ADCON0*8)+3;
volatile bit CHS1               @ ((unsigned)&ADCON0*8)+4;
volatile bit CHS2               @ ((unsigned)&ADCON0*8)+5;
volatile bit CHS3               @ ((unsigned)&ADCON0*8)+6;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	                    : 3;
        unsigned	CHS                 : 4;
    };
    struct {
        unsigned	ADON              : 1;
        unsigned	GO_DONE           : 1;
        unsigned	ADEX              : 1;
        unsigned	CHS0              : 1;
        unsigned	CHS1              : 1;
        unsigned	CHS2              : 1;
        unsigned	CHS3              : 1;
    };
} ADCON0bits @ 0x0113;
#endif

// Register: ADCON1
volatile unsigned char           ADCON1          @ 0x0114;
// bit and bitfield definitions
volatile bit ADPREF0              @ ((unsigned)&ADCON1*8)+0;
volatile bit ADPREF1              @ ((unsigned)&ADCON1*8)+1;
volatile bit ADNREF0              @ ((unsigned)&ADCON1*8)+2;
volatile bit ADNREF1              @ ((unsigned)&ADCON1*8)+3;
volatile bit ADCS0                @ ((unsigned)&ADCON1*8)+4;
volatile bit ADCS1                @ ((unsigned)&ADCON1*8)+5;
volatile bit ADCS2                @ ((unsigned)&ADCON1*8)+6;
volatile bit ADFM                 @ ((unsigned)&ADCON1*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	ADPREF              : 2;
        unsigned	ADNREF              : 2;
        unsigned	ADCS                : 3;
    };
    struct {
        unsigned	ADPREF0              : 1;
        unsigned	ADPREF1              : 1;
        unsigned	ADNREF0              : 1;
        unsigned	ADNREF1              : 1;
        unsigned	ADCS0                : 1;
        unsigned	ADCS1                : 1;
        unsigned	ADCS2                : 1;
        unsigned	ADFM                 : 1;
    };
} ADCON1bits @ 0x0114;
#endif

// Register: ADCON2
volatile unsigned char           ADCON2       @ 0x0115;
// bit and bitfield definitions
volatile bit ETGSEL0               @ ((unsigned)&ADCON2*8)+0;
volatile bit ETGSEL1               @ ((unsigned)&ADCON2*8)+1;
volatile bit ETGSEL2               @ ((unsigned)&ADCON2*8)+2;
volatile bit ADDLY8                @ ((unsigned)&ADCON2*8)+3;
volatile bit ETGTYP0               @ ((unsigned)&ADCON2*8)+4;
volatile bit ETGTYP1               @ ((unsigned)&ADCON2*8)+5;
volatile bit ADINTREF0             @ ((unsigned)&ADCON2*8)+6;
volatile bit ADINTREF1             @ ((unsigned)&ADCON2*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	ETGSEL             : 3;
        unsigned	                   : 1;
        unsigned	ETGTYP             : 2;
        unsigned	ADINTREF           : 2;
    };
    struct {
        unsigned	ETGSEL0           : 1;
        unsigned	ETGSEL1           : 1;
        unsigned	ETGSEL2           : 1;
        unsigned	ADDLY8            : 1;
        unsigned	ETGTYP0           : 1;
        unsigned	ETGTYP1           : 1;
        unsigned	ADINTREF0         : 1;
        unsigned	ADINTREF1         : 1;
    };
} ADCON2bits @ 0x0115;
#endif

// Register: PR1L
volatile unsigned char           PR1L           @ 0x0116;
// bit and bitfield definitions

// Register: PR1H
volatile unsigned char           PR1H           @ 0x0117;
// bit and bitfield definitions

// Register: TMR1L
volatile unsigned char           TMR1L          @ 0x0118;
// bit and bitfield definitions

// Register: TMR1H
volatile unsigned char           TMR1H          @ 0x0119;
// bit and bitfield definitions
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	TMR1H                : 4;
    };
} TMR1Hbits @ 0x0119;
#endif

// Register: T1CON0
volatile unsigned char           T1CON0       @ 0x011A;
// bit and bitfield definitions
volatile bit T1CKSRC0              @ ((unsigned)&T1CON0*8)+0;
volatile bit T1CKSRC1              @ ((unsigned)&T1CON0*8)+1;
volatile bit T1ON                  @ ((unsigned)&T1CON0*8)+2;
volatile bit T1CKRUN               @ ((unsigned)&T1CON0*8)+3;
volatile bit T1CKPSA               @ ((unsigned)&T1CON0*8)+4;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	T1CKSRC           : 2;
    };
    struct {
        unsigned	T1CKSRC0          : 1;
        unsigned	T1CKSRC1          : 1;
        unsigned	T1ON              : 1;
        unsigned	T1CKRUN           : 1;
        unsigned	T1CKPSA           : 1;
    };
} T1CON0bits @ 0x011A;
#endif

// Register: P1OE2
volatile unsigned char           P1OE2       @ 0x011B;
// bit and bitfield definitions
volatile bit P1B1OE               @ ((unsigned)&P1OE2*8)+1;
volatile bit P1C1OE               @ ((unsigned)&P1OE2*8)+2;
volatile bit P1D0OE               @ ((unsigned)&P1OE2*8)+5;
volatile bit P1D1OE               @ ((unsigned)&P1OE2*8)+6;
volatile bit P1D2OE               @ ((unsigned)&P1OE2*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	                  : 1;
        unsigned	P1B1OE            : 1;
        unsigned	P1C1OE            : 1;
        unsigned	                  : 2;
        unsigned	P1D0OE            : 1;
        unsigned	P1D1OE            : 1;
        unsigned	P1D2OE            : 1;
    };
} P1OE2bits @ 0x011B;
#endif

// Register: TKCON0
volatile unsigned char           TKCON0       @ 0x011C;
// bit and bitfield definitions
volatile bit TKCAPEN              @ ((unsigned)&TKCON0*8)+0;
volatile bit TKEN                 @ ((unsigned)&TKCON0*8)+0;
volatile bit TKCHGS0              @ ((unsigned)&TKCON0*8)+1;
volatile bit TKCHGS1              @ ((unsigned)&TKCON0*8)+2;
volatile bit TKMODE               @ ((unsigned)&TKCON0*8)+3;
volatile bit TKCAPM               @ ((unsigned)&TKCON0*8)+4;
volatile bit VREFM                @ ((unsigned)&TKCON0*8)+5;
volatile bit TKRSEL0              @ ((unsigned)&TKCON0*8)+6;
volatile bit TKRSEL1              @ ((unsigned)&TKCON0*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	TKCAPEN              : 1;
        unsigned	TKCHGS0              : 1;
        unsigned	TKCHGS1              : 1;
        unsigned	TKMODE               : 1;
        unsigned	TKCAPM               : 1;
        unsigned	VREFM                : 1;
        unsigned	TKRSEL0              : 1;
        unsigned	TKRSEL1              : 1;
    };
    struct {
        unsigned	TKEN              : 1;
        unsigned	TKCHGS            : 2;
        unsigned	                  : 3;
        unsigned	TKRSEL            : 2;
    };
} TKCON0bits @ 0x011C;
#endif

// Register: TKCON1
volatile unsigned char           TKCON1       @ 0x011D;
// bit and bitfield definitions
volatile bit TKCHE0                @ ((unsigned)&TKCON1*8)+0;
volatile bit TKCHE1                @ ((unsigned)&TKCON1*8)+1;
volatile bit TKCHE2                @ ((unsigned)&TKCON1*8)+2;
volatile bit TKCHE3                @ ((unsigned)&TKCON1*8)+3;
volatile bit TKCHE4                @ ((unsigned)&TKCON1*8)+4;
volatile bit TKCHE5                @ ((unsigned)&TKCON1*8)+5;
volatile bit TKCHE6                @ ((unsigned)&TKCON1*8)+6;
volatile bit TKCHE7                @ ((unsigned)&TKCON1*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	TKCHE0              : 1;
        unsigned	TKCHE1              : 1;
        unsigned	TKCHE2              : 1;
        unsigned	TKCHE3              : 1;
        unsigned	TKCHE4              : 1;
        unsigned	TKCHE5              : 1;
        unsigned	TKCHE6              : 1;
        unsigned	TKCHE7              : 1;
    };
    struct {
        unsigned	TKCHE            : 8;
    };
} TKCON1bits @ 0x011D;
#endif

// Register: ANSEL0
volatile unsigned char           ANSEL0       @ 0x011E;
// bit and bitfield definitions

// Register: VR3VCAL
volatile unsigned char           VR3VCAL      @ 0x011F;
// bit and bitfield definitions

// Register: CRYPEN
volatile unsigned char           CRYPEN       @ 0x0181;
// bit and bitfield definitions

// Register: LEBCON
volatile unsigned char           LEBCON       @ 0x0185;
// bit and bitfield definitions
volatile bit EDGS                  @ ((unsigned)&LEBCON*8)+3;
volatile bit LEBCH0                @ ((unsigned)&LEBCON*8)+5;
volatile bit LEBCH1                @ ((unsigned)&LEBCON*8)+6;
volatile bit LEBEN                 @ ((unsigned)&LEBCON*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	                    : 3;
        unsigned	EDGS                : 1;
        unsigned	                    : 1;
        unsigned	LEBCH0              : 1;
        unsigned	LEBCH1              : 1;
        unsigned	LEBEN               : 1;
    };
    struct {
        unsigned	                    : 5;
        unsigned	LEBCH               : 2;
    };
} LEBCONbits @ 0x0185;
#endif


// Register: ADCON3
volatile unsigned char           ADCON3       @ 0x0186;
// bit and bitfield definitions
volatile bit LEBADT                @ ((unsigned)&ADCON3*8)+3;
volatile bit ADCMPEN               @ ((unsigned)&ADCON3*8)+5;
volatile bit ADCMPOP               @ ((unsigned)&ADCON3*8)+6;
volatile bit ADFBEN                @ ((unsigned)&ADCON3*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	                    : 3;
        unsigned	LEBADT              : 1;
        unsigned	                    : 1;
        unsigned	ADCMPEN             : 1;
        unsigned	ADCMPOP             : 1;
        unsigned	ADFBEN              : 1;
    };
} ADCON3bits @ 0x0186;
#endif

// Register: ADCMPH
volatile unsigned char           ADCMPH       @ 0x0187;
// bit and bitfield definitions

// Register: ADDLY
volatile unsigned char           ADDLY        @ 0x0188;
// bit and bitfield definitions
volatile bit ADDLY0                 @ ((unsigned)&ADDLY*8)+0;
volatile bit ADDLY1                 @ ((unsigned)&ADDLY*8)+1;
volatile bit ADDLY2                 @ ((unsigned)&ADDLY*8)+2;
volatile bit ADDLY3                 @ ((unsigned)&ADDLY*8)+3;
volatile bit ADDLY4                 @ ((unsigned)&ADDLY*8)+4;
volatile bit ADDLY5                 @ ((unsigned)&ADDLY*8)+5;
volatile bit ADDLY6                 @ ((unsigned)&ADDLY*8)+6;
volatile bit ADDLY7                 @ ((unsigned)&ADDLY*8)+7;


volatile bit LEBPRL0                 @ ((unsigned)&ADDLY*8)+0;
volatile bit LEBPRL1                 @ ((unsigned)&ADDLY*8)+1;
volatile bit LEBPRL2                 @ ((unsigned)&ADDLY*8)+2;
volatile bit LEBPRL3                 @ ((unsigned)&ADDLY*8)+3;
volatile bit LEBPRL4                 @ ((unsigned)&ADDLY*8)+4;
volatile bit LEBPRL5                 @ ((unsigned)&ADDLY*8)+5;
volatile bit LEBPRL6                 @ ((unsigned)&ADDLY*8)+6;
volatile bit LEBPRL7                 @ ((unsigned)&ADDLY*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	ADDLY0                : 1;
        unsigned	ADDLY1                : 1;
        unsigned	ADDLY2                : 1;
        unsigned	ADDLY3                : 1;
        unsigned	ADDLY4                : 1;
        unsigned	ADDLY5                : 1;
        unsigned	ADDLY6                : 1;
        unsigned	ADDLY7                : 1;
    };
    struct {
        unsigned	LEBPRL0                : 1;
        unsigned	LEBPRL1                : 1;
        unsigned	LEBPRL2                : 1;
        unsigned	LEBPRL3                : 1;
        unsigned	LEBPRL4                : 1;
        unsigned	LEBPRL5                : 1;
        unsigned	LEBPRL6                : 1;
        unsigned	LEBPRL7                : 1;
    };
    struct {
        unsigned	ADDLY                  : 8;
    };
    struct {
        unsigned	LEBPRL                 : 8;
    };
} ADDLYbits @ 0x0188;
#endif
// Register: T0DUTY
volatile unsigned char           T0DUTY       @ 0x018C;
// bit and bitfield definitions
// Register: PR0
volatile unsigned char           PR0         @ 0x018D;
// bit and bitfield definitions
// Register: MSCON1
volatile unsigned char           MSCON1       @ 0x018E;
// bit and bitfield definitions
volatile bit HIRCM                @ ((unsigned)&MSCON1*8)+0;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	HIRCM              : 1;
    };
} MSCON1bits @ 0x018E;
#endif
// Register: LVDTRIM
volatile unsigned char           LVDTRIM       @ 0x019F;
// bit and bitfield definitions
volatile bit LVRADJ0                @ ((unsigned)&LVDTRIM*8)+0;
volatile bit LVRADJ1                @ ((unsigned)&LVDTRIM*8)+1;
volatile bit LVRADJ2                @ ((unsigned)&LVDTRIM*8)+2;
volatile bit LVDADJ0                @ ((unsigned)&LVDTRIM*8)+3;
volatile bit LVDADJ1                @ ((unsigned)&LVDTRIM*8)+4;
volatile bit LVDADJ2                @ ((unsigned)&LVDTRIM*8)+5;
volatile bit LVDADJ3                @ ((unsigned)&LVDTRIM*8)+6;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	LVRADJ0              : 1;
        unsigned	LVRADJ1              : 1;
        unsigned	LVRADJ2              : 1;
        unsigned	LVDADJ0              : 1;
        unsigned	LVDADJ1              : 1;
        unsigned	LVDADJ2              : 1;
        unsigned	LVDADJ3              : 1;
    };
    struct {
        unsigned	LVRADJ              : 3;
        unsigned	LVDADJ              :4;
    };
} LVDTRIMbits @ 0x019F;
#endif
//--------------------------------------------------------------------------by yangxu
volatile unsigned char           SFR00             @0x000;
volatile unsigned char           SFR01             @0x001;
volatile unsigned char           SFR02             @0x002;
volatile unsigned char           SFR03             @0x003;
volatile unsigned char           SFR04             @0x004;
volatile unsigned char           SFR05             @0x005;
volatile unsigned char           SFR06             @0x006;
volatile unsigned char           SFR07             @0x007;
volatile unsigned char           SFR08             @0x008;
volatile unsigned char           SFR09             @0x009;
volatile unsigned char           SFR0A             @0x00A;
volatile unsigned char           SFR0B             @0x00B;
volatile unsigned char           SFR0C             @0x00C;
volatile unsigned char           SFR0D             @0x00D;
volatile unsigned char           SFR0E             @0x00E;
volatile unsigned char           SFR0F             @0x00F;

volatile unsigned char           SFR10             @0x010;
volatile unsigned char           SFR11             @0x011;
volatile unsigned char           SFR12             @0x012;
volatile unsigned char           SFR13             @0x013;
volatile unsigned char           SFR14             @0x014;
volatile unsigned char           SFR15             @0x015;
volatile unsigned char           SFR16             @0x016;
volatile unsigned char           SFR17             @0x017;
volatile unsigned char           SFR18             @0x018;
volatile unsigned char           SFR19             @0x019;
volatile unsigned char           SFR1A             @0x01A;
volatile unsigned char           SFR1B             @0x01B;
volatile unsigned char           SFR1C             @0x01C;
volatile unsigned char           SFR1D             @0x01D;
volatile unsigned char           SFR1E             @0x01E;
volatile unsigned char           SFR1F             @0x01F;


volatile unsigned char           SFR80             @0x080;
volatile unsigned char           SFR81             @0x081;
volatile unsigned char           SFR82             @0x082;
volatile unsigned char           SFR83             @0x083;
volatile unsigned char           SFR84             @0x084;
volatile unsigned char           SFR85             @0x085;
volatile unsigned char           SFR86             @0x086;
volatile unsigned char           SFR87             @0x087;
volatile unsigned char           SFR88             @0x088;
volatile unsigned char           SFR89             @0x089;
volatile unsigned char           SFR8A             @0x08A;
volatile unsigned char           SFR8B             @0x08B;
volatile unsigned char           SFR8C             @0x08C;
volatile unsigned char           SFR8D             @0x08D;
volatile unsigned char           SFR8E             @0x08E;
volatile unsigned char           SFR8F             @0x08F;

volatile unsigned char           SFR90             @0x090;
volatile unsigned char           SFR91             @0x091;
volatile unsigned char           SFR92             @0x092;
volatile unsigned char           SFR93             @0x093;
volatile unsigned char           SFR94             @0x094;
volatile unsigned char           SFR95             @0x095;
volatile unsigned char           SFR96             @0x096;
volatile unsigned char           SFR97             @0x097;
volatile unsigned char           SFR98             @0x098;
volatile unsigned char           SFR99             @0x099;
volatile unsigned char           SFR9A             @0x09A;
volatile unsigned char           SFR9B             @0x09B;
volatile unsigned char           SFR9C             @0x09C;
volatile unsigned char           SFR9D             @0x09D;
volatile unsigned char           SFR9E             @0x09E;
volatile unsigned char           SFR9F             @0x09F;

volatile unsigned char           SFR100             @0x100;
volatile unsigned char           SFR101             @0x101;
volatile unsigned char           SFR102             @0x102;
volatile unsigned char           SFR103             @0x103;
volatile unsigned char           SFR104             @0x104;
volatile unsigned char           SFR105             @0x105;
volatile unsigned char           SFR106             @0x106;
volatile unsigned char           SFR107             @0x107;
volatile unsigned char           SFR108             @0x108;
volatile unsigned char           SFR109             @0x109;
volatile unsigned char           SFR10A             @0x10A;
volatile unsigned char           SFR10B             @0x10B;
volatile unsigned char           SFR10C             @0x10C;
volatile unsigned char           SFR10D             @0x10D;
volatile unsigned char           SFR10E             @0x10E;
volatile unsigned char           SFR10F             @0x10F;

volatile unsigned char           SFR110             @0x110;
volatile unsigned char           SFR111             @0x111;
volatile unsigned char           SFR112             @0x112;
volatile unsigned char           SFR113             @0x113;
volatile unsigned char           SFR114             @0x114;
volatile unsigned char           SFR115             @0x115;
volatile unsigned char           SFR116             @0x116;
volatile unsigned char           SFR117             @0x117;
volatile unsigned char           SFR118             @0x118;
volatile unsigned char           SFR119             @0x119;
volatile unsigned char           SFR11A             @0x11A;
volatile unsigned char           SFR11B             @0x11B;
volatile unsigned char           SFR11C             @0x11C;
volatile unsigned char           SFR11D             @0x11D;
volatile unsigned char           SFR11E             @0x11E;
volatile unsigned char           SFR11F             @0x11F;

volatile unsigned char           SFR180             @0x180;
volatile unsigned char           SFR181             @0x181;
volatile unsigned char           SFR182             @0x182;
volatile unsigned char           SFR183             @0x183;
volatile unsigned char           SFR184             @0x184;
volatile unsigned char           SFR185             @0x185;
volatile unsigned char           SFR186             @0x186;
volatile unsigned char           SFR187             @0x187;
volatile unsigned char           SFR188             @0x188;
volatile unsigned char           SFR189             @0x189;
volatile unsigned char           SFR18A             @0x18A;
volatile unsigned char           SFR18B             @0x18B;
volatile unsigned char           SFR18C             @0x18C;
volatile unsigned char           SFR18D             @0x18D;
volatile unsigned char           SFR18E             @0x18E;
volatile unsigned char           SFR18F             @0x18F;

volatile unsigned char           SFR19F             @0x19F;
//---------------------------------------------------------------------------
#endif
