
#ifndef __IAP_CORE_H_
#define __IAP_CORE_H_

//

#define IapROM  0x00	  //0x00：选择ROM区操作  0x02：选择EEPROM区操作
#define IapEPPROM  0x02	  //0x00：选择ROM区操作  0x02：选择EEPROM区操作



BYTE IapReadByte(WORD addr);
void IapProgramByte(WORD addr, BYTE dat);



#endif