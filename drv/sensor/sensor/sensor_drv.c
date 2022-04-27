#include "..\..\com_include_drv.h"

#ifdef SensorType

void zd_sensorCheck(struct zd_sensor_t* sen,unsigned char chkmax,unsigned char chkmin)
{

	if(chkmax)
	{
		if(sen->TriggerFilterCnt<sen->TriggerFilterValue) sen->TriggerFilterCnt++;
		else	sen->TriggerStatus=2;
			
	}
	else if(chkmin)
	{
		if(sen->TriggerFilterCnt>0) sen->TriggerFilterCnt--;
		else	sen->TriggerStatus=1;
	}
	else
	{
		sen->TriggerFilterCnt=50;
		sen->TriggerStatus=0;
	}

}


#endif