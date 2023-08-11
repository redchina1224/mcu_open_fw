#ifndef __SIGNAL_FILTERING_APP_H_
#define __SIGNAL_FILTERING_APP_H_

typedef struct {
 unsigned char TriggerFilterCnt;
 unsigned char TriggerFilterValue;
 unsigned char TriggerStatus;
}mof_signal_filtering_t;

void mof_signalCheck(mof_signal_filtering_t* sig,unsigned char chkmax,unsigned char chkmin);

#endif

