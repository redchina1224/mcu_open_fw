#ifndef __SOFTLED_DIG8_DRV_H_
#define __SOFTLED_DIG8_DRV_H_

extern unsigned char *Led_WriteSegBuffer;
extern const unsigned char *Led_WriteComBuffer;

#ifdef DisplaySoftLedBrightBreath
extern unsigned char *Led_WriteSegBreathMask;
extern unsigned char LedBreathBrightSet;
#endif 

void mof_softled_run(void);	
void mof_softled_init(void);
void mof_softled_set_bright(unsigned char bright);

#ifdef DisplaySoftLedBrightBreath
void zd_softled_set_breathbright(unsigned char bright);
#endif 

#endif