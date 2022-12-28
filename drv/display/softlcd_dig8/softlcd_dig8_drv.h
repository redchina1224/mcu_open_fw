#ifndef __SOFTLCD_DIG8_DRV_H_
#define __SOFTLCD_DIG8_DRV_H_

extern unsigned char *Lcd_WriteSegBuffer;
extern const unsigned char *Lcd_WriteComBuffer;

void zd_softlcd_run(void);	
void zd_softlcd_init(void);

#endif