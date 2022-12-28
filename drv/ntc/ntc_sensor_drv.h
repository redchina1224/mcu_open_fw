#ifndef __NTC_SENSOR_H_
#define __NTC_SENSOR_H_

TableValueType GetTempAdcVal(unsigned char temp);

unsigned char TmpC_to_TmpF(unsigned char tmpc);

unsigned char CalcTmpC(TableValueType adc_agval,unsigned char TempC_realtime);


#endif

