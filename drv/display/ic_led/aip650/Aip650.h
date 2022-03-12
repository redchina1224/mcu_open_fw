#ifndef __SOFTLED_H_
#define __SOFTLED_H_



//extern unsigned char bufferLength;
//extern  unsigned char *Aip650_Brightness;
//extern unsigned char *Aip650_ReadBuffer;
extern  unsigned char *Aip650_WriteBuffer;


extern void Aip650_Init(void);
extern void Aip650_SendDisBuffer(void);
//extern void Aip650_SendDisBufferTest(void);
#endif