
#ifndef __IAP_CORE_H_
#define __IAP_CORE_H_

//

#define IapROM  0x00	  //0x00��ѡ��ROM������  0x02��ѡ��EEPROM������
#define IapEPPROM  0x02	  //0x00��ѡ��ROM������  0x02��ѡ��EEPROM������



BYTE IapReadByte(WORD addr);
void IapProgramByte(WORD addr, BYTE dat);



#endif