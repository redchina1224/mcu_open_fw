#ifndef __DEFINESTD_CORE_H_
#define __DEFINESTD_CORE_H_


//通用定义-变量类型
typedef unsigned long u32;
typedef unsigned int  u16;
typedef unsigned char u8;

typedef signed long s32;
typedef signed int  s16;
typedef signed char s8;

typedef unsigned long uint32;
typedef unsigned int  uint16;
typedef unsigned char uint8;

typedef signed long int32;
typedef signed int  int16;
typedef signed char int8;

typedef unsigned long uint32_t;
typedef unsigned int  uint16_t;
typedef unsigned char uint8_t;

typedef signed long int32_t;
typedef signed int  int16_t;
typedef signed char int8_t;



typedef float f24;
typedef double d24;


typedef unsigned char BYTE;
typedef unsigned int WORD;


typedef bit 			    BOOL; 		// 布尔变量（位变量）
typedef unsigned char		CHAR;		// 字符变量
typedef unsigned char 		INT8U; 		// 无符号8位整型变量  
typedef signed char 		INT8S; 		// 有符号8位整型变量  
typedef unsigned int 		INT16U; 	// 无符号16位整型变量 
typedef signed int 		    INT16S; 	// 有符号16位整型变量
typedef unsigned long 		INT32U; 	// 无符号32位整型变量
typedef signed long 		INT32S; 	// 有符号32位整型变量 
typedef float 			    FP32; 		// 单精度浮点数(32位长度) 
typedef double 			    FP64; 		// 双精度浮点数(64位长度)

#define	uchar	unsigned	char
#define	uint	unsigned	int
#define	uint32	unsigned	double	int



//			第一位: g表示全局变量 l表示局部变量
//			第二位: u表示unsigned s表示signed
//			第三位: i表示int 	c表示char	b表示bit	l表示long
//			第四位: v表示变量  c表示静态变量





typedef union {
unsigned char Value;
	struct {
		unsigned char bit0:1;
		unsigned char bit1:1;
		unsigned char bit2:1;
		unsigned char bit3:1;	
		unsigned char bit4:1;
		unsigned char bit5:1;
		unsigned char bit6:1;
		unsigned char bit7:1;		
	};
} zd_charbits_t;

typedef union {
unsigned int Value;
	struct {
		unsigned char bit0:1;
		unsigned char bit1:1;
		unsigned char bit2:1;
		unsigned char bit3:1;	
		unsigned char bit4:1;
		unsigned char bit5:1;
		unsigned char bit6:1;
		unsigned char bit7:1;
		unsigned char bit8:1;
		unsigned char bit9:1;
		unsigned char bit10:1;
		unsigned char bit11:1;	
		unsigned char bit12:1;
		unsigned char bit13:1;
		unsigned char bit14:1;
		unsigned char bit15:1;
	};
} zd_intbits_t;



typedef union {
unsigned long Value;
	struct {
		unsigned char bit0:1;
		unsigned char bit1:1;
		unsigned char bit2:1;
		unsigned char bit3:1;	
		unsigned char bit4:1;
		unsigned char bit5:1;
		unsigned char bit6:1;
		unsigned char bit7:1;
		unsigned char bit8:1;
		unsigned char bit9:1;
		unsigned char bit10:1;
		unsigned char bit11:1;
		unsigned char bit12:1;
		unsigned char bit13:1;
		unsigned char bit14:1;
		unsigned char bit15:1;
		unsigned char bit16:1;
		unsigned char bit17:1;
		unsigned char bit18:1;
		unsigned char bit19:1;
		unsigned char bit20:1;
		unsigned char bit21:1;
		unsigned char bit22:1;
		unsigned char bit23:1;
		unsigned char bit24:1;
		unsigned char bit25:1;
		unsigned char bit26:1;
		unsigned char bit27:1;
		unsigned char bit28:1;
		unsigned char bit29:1;
		unsigned char bit30:1;
		unsigned char bit31:1;

	};
} zd_longbits_t;



//常量定义


//#ifdef code
//	#define ZD_CONST code 
//#el
//	typedef const ZD_CONST
//#endif





//#define UIV (unsigned int)
//#define UCV (unsigned char)
//#define ULV (unsigned long)
//	
//#define SIV (signed int)
//#define SCV (signed char)
//#define SLV (signed long)



//#ifdef code
//#define UIC (code unsigned int)
//#define UCC (code unsigned char)
//#define ULC (code unsigned long)
//	
//#define SIC (code signed int)
//#define SCC (code signed char)
//#define SLC (code signed long)
//	

//#el

//#define UIC (const unsigned int)
//#define UCC (const unsigned char)
//#define ULC (const unsigned long)
//	
//#define SIC (const signed int)
//#define SCC (const signed char)
//#define SLC (const signed long)
//#endif



//通用定义--位定义
#define BIT0  (1<<0)
#define BIT1  (1<<1)
#define BIT2  (1<<2)
#define BIT3  (1<<3)
#define BIT4  (1<<4)
#define BIT5  (1<<5)
#define BIT6  (1<<6)
#define BIT7  (1<<7)
#define BIT8  (1<<8)
#define BIT9  (1<<9)
#define BIT10  (1<<10)
#define BIT11  (1<<11)
#define BIT12  (1<<12)
#define BIT13  (1<<13)
#define BIT14  (1<<14)
#define BIT15  (1<<15)
#define BIT16  (1<<16)
#define BIT17  (1<<17)
#define BIT18  (1<<18)
#define BIT19  (1<<19)
#define BIT20  (1<<20)
#define BIT21  (1<<21)
#define BIT22  (1<<22)
#define BIT23  (1<<23)
#define BIT24  (1<<24)
#define BIT25  (1<<25)
#define BIT26  (1<<26)
#define BIT27  (1<<27)
#define BIT28  (1<<28)
#define BIT29  (1<<29)
#define BIT30  (1<<30)
#define BIT31  (1<<31)


//通用定义--真/假
#define 	TRUE  1
#define 	FALSE  0

#define 	True		1
#define 	False		0

#define 	true		1
#define 	false		0

#define 	ENABLE		1
#define 	DISABLE		0

#define 	Enable		1
#define 	Disable		0

#define 	enable		1
#define 	disable		0

#define NULL 0
#define Null 0
#define null 0


//通用定义-功能块

#define		BS(SFR,NUM)		(SFR|=(1<<NUM))
#define		BC(SFR,NUM)		(SFR&=~(1<<NUM))
#define		BitSet(SFR,NUM)		(SFR|=(1<<NUM))
#define		BitReset(SFR,NUM)		(SFR&=~(1<<NUM))

#define 	bit_is_set(var,bit)  	(var&(0x01<<bit))
#define 	bit_is_clear(var,bit)  	((~var)&(0x01<<bit))

#define   set_bit(var,bit)  		var|=(0x01<<bit)     //位置1 
#define   clear_bit(var,bit)  	var&=(~(0x01<<bit))  //位清零


#endif