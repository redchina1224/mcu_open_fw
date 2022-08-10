#ifndef __SCR_CROSSZERO_CTRL_DRV_H_
#define __SCR_CROSSZERO_CTRL_DRV_H_

extern unsigned char cucv_Scr_Ctrl_Delay_Tab[101];
#define GetScrCtrlDelayValByPercent(x) cucv_Scr_Ctrl_Delay_Tab[unsigned char(x)]

#endif

