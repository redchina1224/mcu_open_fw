#ifndef __SIGNAL_FILTERING_APP_H_
#define __SIGNAL_FILTERING_APP_H_

struct  zd_signal_filtering_t {
 unsigned char TriggerFilterCnt;
 unsigned char TriggerFilterValue;
 unsigned char TriggerStatus;
};

void zd_signalCheck(struct zd_signal_filtering_t* sig,unsigned char chkmax,unsigned char chkmin);

#endif

