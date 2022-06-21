#include "..\..\com_include_app.h"


void zd_signalCheck(struct zd_signal_filtering_t* sig,unsigned char chkmax,unsigned char chkmin)
{
	unsigned char TriggerFilterValueHalf;
	TriggerFilterValueHalf=(sig->TriggerFilterValue>>1);
	if(chkmax)
	{
		if(sig->TriggerFilterCnt<sig->TriggerFilterValue) sig->TriggerFilterCnt++;
		else	sig->TriggerStatus=2;
			
	}
	else if(chkmin)
	{
		if(sig->TriggerFilterCnt>0) sig->TriggerFilterCnt--;
		else	sig->TriggerStatus=1;
	}
	else
	{
		if(sig->TriggerFilterCnt==TriggerFilterValueHalf) sig->TriggerStatus=0;
		else if(sig->TriggerFilterCnt>TriggerFilterValueHalf) sig->TriggerFilterCnt--;
		else if(sig->TriggerFilterCnt<TriggerFilterValueHalf) sig->TriggerFilterCnt++;
		
	}

}
