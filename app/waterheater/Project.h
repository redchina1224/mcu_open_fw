#ifndef __PROJECT_H__
#define __PROJECT_H__

#define NK 	0x000000
#define K0 	0x000001
#define K1 	0x000002
#define K2 	0x000004
#define K3 	0x000008
#define K4 	0x000010
#define K5 	0x000020
#define K6 	0x000040
#define K7 	0x000080
#define K8 	0x000100
#define K9 	0x000200
#define K10 0x000400
#define K11 0x000800
#define K12 0x001000
#define K13 0x002000
#define K14 0x004000
#define K15	0x008000
#define K16	0x010000
#define K17	0x020000
#define K18	0x040000

/***************************IO口设置映射*****************************/

/**********************PA口**********************/


#define SET_PA0_IO_IN TRISA |= 0x01
#define SET_PA1_IO_IN TRISA |= 0x02

#define SET_PA0_IO_OUT TRISA &= ~0x01
#define SET_PA1_IO_OUT TRISA &= ~0x02

#define SET_PA0_L PA0 = 0
#define SET_PA1_L PA1 = 0

#define SET_PA0_H PA0 = 1
#define SET_PA1_H PA1 = 1

#define SET_PA0_PU_ON PU_PA |= 0x01
#define SET_PA1_PU_ON PU_PA |= 0x02

#define SET_PA0_PU_OFF PU_PA &= ~0x01
#define SET_PA1_PU_OFF PU_PA &= ~0x02

#define SET_PA0_OD_ON ODRAIN_EN |= 0x01
#define SET_PA1_OD_ON ODRAIN_EN |= 0x02

#define SET_PA0_OD_OFF ODRAIN_EN &= ~0x01
#define SET_PA1_OD_OFF ODRAIN_EN &= ~0x02

#define GET_PA0 (DATAA&0x01)
#define GET_PA1 (DATAA&0x02)


/**********************PA口**********************/

/**********************PB口**********************/

#define SET_PB0_IO_IN TRISB |= 0x01
#define SET_PB1_IO_IN TRISB |= 0x02
#define SET_PB2_IO_IN TRISB |= 0x04
#define SET_PB3_IO_IN TRISB |= 0x08
#define SET_PB4_IO_IN TRISB |= 0x10
#define SET_PB5_IO_IN TRISB |= 0x20
#define SET_PB6_IO_IN TRISB |= 0x40
#define SET_PB7_IO_IN TRISB |= 0x80

#define SET_PB0_IO_OUT TRISB &= ~0x01
#define SET_PB1_IO_OUT TRISB &= ~0x02
#define SET_PB2_IO_OUT TRISB &= ~0x04
#define SET_PB3_IO_OUT TRISB &= ~0x08
#define SET_PB4_IO_OUT TRISB &= ~0x10
#define SET_PB5_IO_OUT TRISB &= ~0x20
#define SET_PB6_IO_OUT TRISB &= ~0x40
#define SET_PB7_IO_OUT TRISB &= ~0x80


#define SET_PB0_L PB0 = 0
#define SET_PB1_L PB1 = 0
#define SET_PB2_L PB2 = 0
#define SET_PB3_L PB3 = 0
#define SET_PB4_L PB4	= 0
#define SET_PB5_L PB5 = 0
#define SET_PB6_L PB6 = 0
#define SET_PB7_L PB7	= 0

#define SET_PB0_H PB0 = 1
#define SET_PB1_H PB1 = 1
#define SET_PB2_H PB2 = 1
#define SET_PB3_H PB3 = 1
#define SET_PB4_H PB4	= 1
#define SET_PB5_H PB5 = 1
#define SET_PB6_H PB6 = 1
#define SET_PB7_H PB7	= 1


#define SET_PB0_PU_ON PU_PB |= 0x01
#define SET_PB1_PU_ON PU_PB |= 0x02
#define SET_PB2_PU_ON PU_PB |= 0x04
#define SET_PB3_PU_ON PU_PB |= 0x08
#define SET_PB4_PU_ON PU_PB |= 0x10
#define SET_PB5_PU_ON PU_PB |= 0x20
#define SET_PB6_PU_ON PU_PB |= 0x40
#define SET_PB7_PU_ON PU_PB |= 0x80

#define SET_PB0_PU_OFF PU_PB &= ~0x01
#define SET_PB1_PU_OFF PU_PB &= ~0x02
#define SET_PB2_PU_OFF PU_PB &= ~0x04
#define SET_PB3_PU_OFF PU_PB &= ~0x08
#define SET_PB4_PU_OFF PU_PB &= ~0x10
#define SET_PB5_PU_OFF PU_PB &= ~0x20
#define SET_PB6_PU_OFF PU_PB &= ~0x40
#define SET_PB7_PU_OFF PU_PB &= ~0x80

#define GET_PB0 (DATAB&0x01)
#define GET_PB1 (DATAB&0x02)
#define GET_PB2 (DATAB&0x04)
#define GET_PB3 (DATAB&0x08)
#define GET_PB4 (DATAB&0x10)
#define GET_PB5 (DATAB&0x20)
#define GET_PB6 (DATAB&0x40)
#define GET_PB7 (DATAB&0x80)


/**********************PB口**********************/

/**********************PC口**********************/

#define SET_PC0_IO_IN TRISC |= 0x01
#define SET_PC1_IO_IN TRISC |= 0x02
#define SET_PC2_IO_IN TRISC |= 0x04
#define SET_PC3_IO_IN TRISC |= 0x08
#define SET_PC4_IO_IN TRISC |= 0x10
#define SET_PC5_IO_IN TRISC |= 0x20
#define SET_PC6_IO_IN TRISC |= 0x40
#define SET_PC7_IO_IN TRISC |= 0x80

#define SET_PC0_IO_OUT TRISC &= ~0x01
#define SET_PC1_IO_OUT TRISC &= ~0x02
#define SET_PC2_IO_OUT TRISC &= ~0x04
#define SET_PC3_IO_OUT TRISC &= ~0x08
#define SET_PC4_IO_OUT TRISC &= ~0x10
#define SET_PC5_IO_OUT TRISC &= ~0x20
#define SET_PC6_IO_OUT TRISC &= ~0x40
#define SET_PC7_IO_OUT TRISC &= ~0x80



#define SET_PC0_L PC0 = 0
#define SET_PC1_L PC1 = 0
#define SET_PC2_L PC2 = 0
#define SET_PC3_L PC3 = 0
#define SET_PC4_L PC4	= 0
#define SET_PC5_L PC5 = 0
#define SET_PC6_L PC6 = 0
#define SET_PC7_L PC7	= 0

#define SET_PC0_H PC0 = 1
#define SET_PC1_H PC1 = 1
#define SET_PC2_H PC2 = 1
#define SET_PC3_H PC3 = 1
#define SET_PC4_H PC4	= 1
#define SET_PC5_H PC5 = 1
#define SET_PC6_H PC6 = 1
#define SET_PC7_H PC7	= 1


#define SET_PC0_PU_ON PU_PC |= 0x01
#define SET_PC1_PU_ON PU_PC |= 0x02
#define SET_PC2_PU_ON PU_PC |= 0x04
#define SET_PC3_PU_ON PU_PC |= 0x08
#define SET_PC4_PU_ON PU_PC |= 0x10
#define SET_PC5_PU_ON PU_PC |= 0x20
#define SET_PC6_PU_ON PU_PC |= 0x40
#define SET_PC7_PU_ON PU_PC |= 0x80

#define SET_PC0_PU_OFF PU_PC &= ~0x01
#define SET_PC1_PU_OFF PU_PC &= ~0x02
#define SET_PC2_PU_OFF PU_PC &= ~0x04
#define SET_PC3_PU_OFF PU_PC &= ~0x08
#define SET_PC4_PU_OFF PU_PC &= ~0x10
#define SET_PC5_PU_OFF PU_PC &= ~0x20
#define SET_PC6_PU_OFF PU_PC &= ~0x40
#define SET_PC7_PU_OFF PU_PC &= ~0x80

#define GET_PC0 (DATAC&0x01)
#define GET_PC1 (DATAC&0x02)
#define GET_PC2 (DATAC&0x04)
#define GET_PC3 (DATAC&0x08)
#define GET_PC4 (DATAC&0x10)
#define GET_PC5 (DATAC&0x20)
#define GET_PC6 (DATAC&0x40)
#define GET_PC7 (DATAC&0x80)

/**********************PC口**********************/

/**********************PD口*********************/

#define SET_PD0_IO_IN TRISD |= 0x01
#define SET_PD1_IO_IN TRISD |= 0x02
#define SET_PD2_IO_IN TRISD |= 0x04
#define SET_PD3_IO_IN TRISD |= 0x08
#define SET_PD4_IO_IN TRISD |= 0x10
#define SET_PD5_IO_IN TRISD |= 0x20
#define SET_PD6_IO_IN TRISD |= 0x40
#define SET_PD7_IO_IN TRISD |= 0x80

#define SET_PD0_IO_OUT TRISD &= ~0x01
#define SET_PD1_IO_OUT TRISD &= ~0x02
#define SET_PD2_IO_OUT TRISD &= ~0x04
#define SET_PD3_IO_OUT TRISD &= ~0x08
#define SET_PD4_IO_OUT TRISD &= ~0x10
#define SET_PD5_IO_OUT TRISD &= ~0x20
#define SET_PD6_IO_OUT TRISD &= ~0x40
#define SET_PD7_IO_OUT TRISD &= ~0x80


#define SET_PD0_L PD0 = 0
#define SET_PD1_L PD1 = 0
#define SET_PD2_L PD2 = 0
#define SET_PD3_L PD3 = 0
#define SET_PD4_L PD4	= 0
#define SET_PD5_L PD5 = 0
#define SET_PD6_L PD6 = 0
#define SET_PD7_L PD7	= 0

#define SET_PD0_H PD0 = 1
#define SET_PD1_H PD1 = 1
#define SET_PD2_H PD2 = 1
#define SET_PD3_H PD3 = 1
#define SET_PD4_H PD4	= 1
#define SET_PD5_H PD5 = 1
#define SET_PD6_H PD6 = 1
#define SET_PD7_H PD7	= 1

#define SET_PD0_PU_ON PU_PD |= 0x01
#define SET_PD1_PU_ON PU_PD |= 0x02
#define SET_PD2_PU_ON PU_PD |= 0x04
#define SET_PD3_PU_ON PU_PD |= 0x08
#define SET_PD4_PU_ON PU_PD |= 0x10
#define SET_PD5_PU_ON PU_PD |= 0x20
#define SET_PD6_PU_ON PU_PD |= 0x40
#define SET_PD7_PU_ON PU_PD |= 0x80

#define SET_PD0_PU_OFF PU_PD &= ~0x01
#define SET_PD1_PU_OFF PU_PD &= ~0x02
#define SET_PD2_PU_OFF PU_PD &= ~0x04
#define SET_PD3_PU_OFF PU_PD &= ~0x08
#define SET_PD4_PU_OFF PU_PD &= ~0x10
#define SET_PD5_PU_OFF PU_PD &= ~0x20
#define SET_PD6_PU_OFF PU_PD &= ~0x40
#define SET_PD7_PU_OFF PU_PD &= ~0x80

#define GET_PD0 (DATAD&0x01)
#define GET_PD1 (DATAD&0x02)
#define GET_PD2 (DATAD&0x04)
#define GET_PD3 (DATAD&0x08)
#define GET_PD4 (DATAD&0x10)
#define GET_PD5 (DATAD&0x20)
#define GET_PD6 (DATAD&0x40)
#define GET_PD7 (DATAD&0x80)

/**********************PD口**********************/

/***************************IO口设置映射*****************************/


//IO口翻转
#define TRUN_PA0 PA0 = ~PA0
#define TRUN_PA1 PA1 = ~PA1

#define TRUN_PB0 PB0 = ~PB0
#define TRUN_PB1 PB1 = ~PB1
#define TRUN_PB2 PB2 = ~PB2
#define TRUN_PB3 PB3 = ~PB3
#define TRUN_PB4 PB4 = ~PB4
#define TRUN_PB5 PB5 = ~PB5
#define TRUN_PB6 PB6 = ~PB6
#define TRUN_PB7 PB7 = ~PB7

#define TRUN_PC0 PC0 = ~PC0
#define TRUN_PC1 PC1 = ~PC1
#define TRUN_PC2 PC2 = ~PC2
#define TRUN_PC3 PC3 = ~PC3
#define TRUN_PC4 PC4 = ~PC4
#define TRUN_PC5 PC5 = ~PC5
#define TRUN_PC6 PC6 = ~PC6
#define TRUN_PC7 PC7 = ~PC7

#define TRUN_PD0 PD0 = ~PD0
#define TRUN_PD1 PD1 = ~PD1
#define TRUN_PD2 PD2 = ~PD2
#define TRUN_PD3 PD3 = ~PD3
#define TRUN_PD4 PD4 = ~PD4
#define TRUN_PD5 PD5 = ~PD5
#define TRUN_PD6 PD6 = ~PD6
#define TRUN_PD7 PD7 = ~PD7

//公共头文件********************************************************************

//外部函数定义********************************************************************
extern void Project(void);



//公共宏定义********************************************************************


//申明外部变量********************************************************************


#endif