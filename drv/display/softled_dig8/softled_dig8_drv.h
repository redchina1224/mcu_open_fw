#ifndef __SOFTLED_DIG8_DRV_H_
#define __SOFTLED_DIG8_DRV_H_

extern unsigned char *Led_WriteSegBuffer;
extern unsigned char *Led_WriteComBuffer;

void zd_softled_run(void);	
void zd_softled_init(void);
void zd_softled_set_bright(unsigned char bright);

#endif