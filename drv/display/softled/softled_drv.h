#ifndef __SOFTLED_DRV_H_
#define __SOFTLED_DRV_H_

extern unsigned char LedBlinkSet;
extern unsigned char *Led_WriteSegBuffer;
extern unsigned char *Led_WriteComBuffer;

void zd_softled_run(void);	
void zd_softled_init(void);


#endif