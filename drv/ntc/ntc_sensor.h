#ifndef __NTC_SENSOR_H_
#define __NTC_SENSOR_H_

unsigned char GetTempAdcVal(unsigned char temp);

unsigned char TmpC_to_TmpF(unsigned char tmpc);

unsigned char CalcTmpC(unsigned char adc_agval,unsigned char TempC_realtime);


#endif

