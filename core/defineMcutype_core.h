#ifndef __DEFINEMCUTYPE_CORE_H_
#define __DEFINEMCUTYPE_CORE_H_

//����MCU�ͺ��嵥
#define McuType_Unkonw 0
#define McuType_FacMask 0xff0000
#define McuType_Mask 0xffff00

//��΢MCU�嵥
////////////////////////////////////////////////////////////////////////////////
#define McuType_CmsSemicon 0x010000
#include "cms\cms_mcutype_core.h"

//��Ԫ΢MCU�嵥
////////////////////////////////////////////////////////////////////////////////
#define McuType_SinOneChip 0x020000
#define McuType_SinOneChip_SC92F 0x020100
#define McuType_SinOneChip_SC92F8463B (McuType_SinOneChip_SC92F+0x01)

//��â΢MCU�嵥
/////////////////////////////////////////////////////////////////////////////////
#define McuType_FremontMicroDevices 0x030000
#define McuType_FremontMicroDevices_FT62F 0x030100
#define McuType_FremontMicroDevices_FT62F13 (McuType_FremontMicroDevices_FT62F+0x01)

#define McuType_FremontMicroDevices_FT61F 0x030200
#define McuType_FremontMicroDevices_FT61F13 (McuType_FremontMicroDevices_FT61F+0x01)

//����MCU�嵥
////////////////////////////////////////////////////////////////////////////////////
#define McuType_HD 0x040000
#define McuType_HD_HD68651 0x040101

//���ǵ�MCU�嵥
////////////////////////////////////////////////////////////////////////////////////
#define McuType_BydMicro 0x050000
#define McuType_BydMicro_BF7512 0x050101

////////////////////////////////////////////////////////////////////////////////////

#endif