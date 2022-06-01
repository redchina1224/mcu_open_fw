
#include "..\com_include_drv.h"

	#ifdef NtcType
		#include "ntc_table_drv.c" //载入NTC参数温度表


TableValueType GetTempAdcVal(unsigned char temp)
{
	if(temp<=(TEMPTABLE_BUFFER_LENGTH-1))
	return cucv_temp_Tab[temp];
	else return 0;
}


unsigned char TmpC_to_TmpF(unsigned char tmpc)
{
    return (unsigned char)(((((unsigned int)tmpc)*18)/10)+32);
}

unsigned char CalcTmpC(unsigned char adcval,unsigned char TempC_realtime)
{
	unsigned char tablepos;
	
	if(TempC_realtime<TEMPTABLE_BUFFER_START) TempC_realtime=TEMPTABLE_BUFFER_START;
	tablepos=TempC_realtime-TEMPTABLE_BUFFER_START;
	
	#ifdef NtcOnBoardResPullType
			if(adcval>cucv_temp_Tab[tablepos])
			{
				#if ((NtcOnBoardResPullType==NtcOnBoardResPullUp))
					if(TempC_realtime>TEMPTABLE_BUFFER_START) TempC_realtime--;
				#elif (NtcOnBoardResPullType==NtcOnBoardResPullDown)
					if(TempC_realtime<TEMPTABLE_BUFFER_END) TempC_realtime++;
				#endif
				
				//gucv_real_tempC=gucv_real_temp/1.8;

			}
			else if(adcval<cucv_temp_Tab[tablepos])
			{
				#if ((NtcOnBoardResPullType==NtcOnBoardResPullUp))
					if(TempC_realtime<TEMPTABLE_BUFFER_END) TempC_realtime++;
				#elif (NtcOnBoardResPullType==NtcOnBoardResPullDown)
					if(TempC_realtime>TEMPTABLE_BUFFER_START) TempC_realtime--;
				#endif
			}
	#endif
	return TempC_realtime;
}



	#endif







