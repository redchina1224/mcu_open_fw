#ifndef __CORECONFIG_LOAD_H_
#define __CORECONFIG_LOAD_H_

//��оƬ�����Ӧͷ�ļ� �������׼���ӿ�
#if((McuType&McuType_FacMask)==McuType_CaChip)

	//IO�����׼��	
	#include "cachip\load_cachip_core.h"

#elif (McuType==McuType_Unkonw)

#endif



#endif

