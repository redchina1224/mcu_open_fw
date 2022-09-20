#ifndef __CMSTOUCHCORECONFIG_LOAD_H_
#define __CMSTOUCHCORECONFIG_LOAD_H_

#if ((McuType==McuType_CmsSemicon_CMS79F738))
	//´¥Ãþ¿â
	#include "touch_79ft73x\CMS_CheckTouch_PT_79FT73xx_V1.08.h"
#elif (McuType==McuType_CmsSemicon_CMS79F726)
	#include "touch_79ft72x\CMS_CheckTouch_PT_79F72x_V1.02.h"
	
#elif (McuType==McuType_CmsSemicon_CMS80F7518)
	#include "Device\CMS80fx51x\Touch\CheckTouchKey_80F75xx.h"
#endif


#endif