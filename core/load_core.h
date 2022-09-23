#ifndef __CORECONFIG_LOAD_H_
#define __CORECONFIG_LOAD_H_

//��оƬ�����Ӧͷ�ļ� �������׼���ӿ�
#if ((McuType==McuType_CmsSemicon_CMS79F738)||(McuType==McuType_CmsSemicon_CMS79F726))

	//����ʱ������
	#define FocsClk 8000000

	#if ((McuType==McuType_CmsSemicon_CMS79F738))
	//IO�����׼��	
	#include "cms\cms_core.h"

	//������궨��
	//#include "cms\touch_79ft73x\CMS_CheckTouch_PT_79FT73xx_V1.08.h"

	#elif (McuType==McuType_CmsSemicon_CMS79F726)

	//IO�����׼��	
	#include "cms\cms79f726_core.h"

	//������궨��
	//#include "cms\touch_79ft72x\CMS_CheckTouch_PT_79F72x_V1.01.h"

	#endif
	
	//ϵͳʱ��
	#if (ZD_FSYS_CLKSET_DEFAULT==ZD_FSYS_CLKSET_FOSC_DIV1)
		#define FsysClk FocsClk/1
	#elif (ZD_FSYS_CLKSET_DEFAULT==ZD_FSYS_CLKSET_FOSC_DIV2)
		#define FsysClk FocsClk/2
	#elif (ZD_FSYS_CLKSET_DEFAULT==ZD_FSYS_CLKSET_FOSC_DIV4)
		#define FsysClk FocsClk/4
	#elif (ZD_FSYS_CLKSET_DEFAULT==ZD_FSYS_CLKSET_FOSC_DIV8)
		#define FsysClk FocsClk/8
	#elif (ZD_FSYS_CLKSET_DEFAULT==ZD_FSYS_CLKSET_FOSC_DIV16)
		#define FsysClk FocsClk/16
	#elif (ZD_FSYS_CLKSET_DEFAULT==ZD_FSYS_CLKSET_FOSC_DIV32)
		#define FsysClk FocsClk/32
	#elif (ZD_FSYS_CLKSET_DEFAULT==ZD_FSYS_CLKSET_FOSC_DIV64)
		#define FsysClk FocsClk/64		
	#elif (ZD_FSYS_CLKSET_DEFAULT==ZD_FSYS_CLKSET_LFINTOSC_32KHZ)
		#define FsysClk 32000
	#endif

	
	//��ʱ��0ʱ������
	#if (ZD_TIMER0_CLKSET_DEFAULT==ZD_TIMER0_CLKSET_FSYS_DIV4)
	
		#if (ZD_TIMER0_CLKPSASET_DEFAULT==ZD_TIMER0_CLKPSASET_NONE)
			#define Ft0Clk FsysClk/4
		#elif (ZD_TIMER0_CLKPSASET_DEFAULT==ZD_TIMER0_CLKPSASET_DIV2)
			#define Ft0Clk FsysClk/4/2
		#elif (ZD_TIMER0_CLKPSASET_DEFAULT==ZD_TIMER0_CLKPSASET_DIV4)
			#define Ft0Clk FsysClk/4/4
		#elif (ZD_TIMER0_CLKPSASET_DEFAULT==ZD_TIMER0_CLKPSASET_DIV8)
			#define Ft0Clk FsysClk/4/8
		#elif (ZD_TIMER0_CLKPSASET_DEFAULT==ZD_TIMER0_CLKPSASET_DIV16)
			#define Ft0Clk FsysClk/4/16
		#elif (ZD_TIMER0_CLKPSASET_DEFAULT==ZD_TIMER0_CLKPSASET_DIV32)
			#define Ft0Clk FsysClk/4/32
		#elif (ZD_TIMER0_CLKPSASET_DEFAULT==ZD_TIMER0_CLKPSASET_DIV64)
			#define Ft0Clk FsysClk/4/64
		#elif (ZD_TIMER0_CLKPSASET_DEFAULT==ZD_TIMER0_CLKPSASET_DIV128)
			#define Ft0Clk FsysClk/4/128
		#elif (ZD_TIMER0_CLKPSASET_DEFAULT==ZD_TIMER0_CLKPSASET_DIV256)
			#define Ft0Clk FsysClk/4/256
		#endif
		
	#endif	


	//��ʱ��2ʱ������
	#if ((ZD_TIMER2_CLKSET_DEFAULT&(BIT0|BIT1))==ZD_TIMER2_CLKSET_FSYS_DIV4_DIV1)
		#define Ft2Clk FsysClk/4/1
	#elif ((ZD_TIMER2_CLKSET_DEFAULT&(BIT0|BIT1))==ZD_TIMER2_CLKSET_FSYS_DIV4_DIV4)
		#define Ft2Clk FsysClk/4/4
	#elif ((ZD_TIMER2_CLKSET_DEFAULT&(BIT0|BIT1))==ZD_TIMER2_CLKSET_FSYS_DIV4_DIV16)
		#define Ft2Clk FsysClk/4/16
	#endif	



#elif (McuType==McuType_CmsSemicon_CMS89F2265B)
	//����ʱ������

	#ifndef FocsClk
		#define FocsClk 8000000
	#endif
	
	//IO�����׼��	
	#include "cms\cms89f2265b_core.h"
	
	//ϵͳʱ��
	#if (ZD_FSYS_CLKSET_DEFAULT==ZD_FSYS_CLKSET_FOSC_DIV1||ZD_FSYS_CLKSET_DEFAULT==ZD_FSYS_CLKSET_XT_DIV1)
		#define FsysClk FocsClk/1
	#elif (ZD_FSYS_CLKSET_DEFAULT==ZD_FSYS_CLKSET_FOSC_DIV2)
		#define FsysClk FocsClk/2
	#elif (ZD_FSYS_CLKSET_DEFAULT==ZD_FSYS_CLKSET_FOSC_DIV4)
		#define FsysClk FocsClk/4
	#elif (ZD_FSYS_CLKSET_DEFAULT==ZD_FSYS_CLKSET_FOSC_DIV8)
		#define FsysClk FocsClk/8
	#elif (ZD_FSYS_CLKSET_DEFAULT==ZD_FSYS_CLKSET_FOSC_DIV16)
		#define FsysClk FocsClk/16
	#elif (ZD_FSYS_CLKSET_DEFAULT==ZD_FSYS_CLKSET_FOSC_DIV32)
		#define FsysClk FocsClk/32
	#elif (ZD_FSYS_CLKSET_DEFAULT==ZD_FSYS_CLKSET_FOSC_DIV64)
		#define FsysClk FocsClk/64		
	#elif (ZD_FSYS_CLKSET_DEFAULT==ZD_FSYS_CLKSET_LFINTOSC_32KHZ)
		#define FsysClk 32000
	#endif

	
	//��ʱ��ʱ������
	#if (ZD_TIMER0_CLKSET_DEFAULT==ZD_TIMER0_CLKSET_FSYS_DIV4)
	
		#if (ZD_TIMER0_CLKPSASET_DEFAULT==ZD_TIMER0_CLKPSASET_NONE)
			#define Ft0Clk FsysClk/4
		#elif (ZD_TIMER0_CLKPSASET_DEFAULT==ZD_TIMER0_CLKPSASET_DIV2)
			#define Ft0Clk FsysClk/4/2
		#elif (ZD_TIMER0_CLKPSASET_DEFAULT==ZD_TIMER0_CLKPSASET_DIV4)
			#define Ft0Clk FsysClk/4/4
		#elif (ZD_TIMER0_CLKPSASET_DEFAULT==ZD_TIMER0_CLKPSASET_DIV8)
			#define Ft0Clk FsysClk/4/8
		#elif (ZD_TIMER0_CLKPSASET_DEFAULT==ZD_TIMER0_CLKPSASET_DIV16)
			#define Ft0Clk FsysClk/4/16
		#elif (ZD_TIMER0_CLKPSASET_DEFAULT==ZD_TIMER0_CLKPSASET_DIV32)
			#define Ft0Clk FsysClk/4/32
		#elif (ZD_TIMER0_CLKPSASET_DEFAULT==ZD_TIMER0_CLKPSASET_DIV64)
			#define Ft0Clk FsysClk/4/64
		#elif (ZD_TIMER0_CLKPSASET_DEFAULT==ZD_TIMER0_CLKPSASET_DIV128)
			#define Ft0Clk FsysClk/4/128
		#elif (ZD_TIMER0_CLKPSASET_DEFAULT==ZD_TIMER0_CLKPSASET_DIV256)
			#define Ft0Clk FsysClk/4/256
		#endif
		
	#endif	

#elif (McuType==McuType_CmsSemicon_CMS79F113)
	
	//����ʱ������
	#define FocsClk 16000000
	
	//IO�����׼��	
	#include "cms\cms79f133_core.h"
	
	//ϵͳʱ��
	#if (ZD_FSYS_CLKSET_DEFAULT==ZD_FSYS_CLKSET_FOSC_DIV1)
		#define FsysClk FocsClk/1
	#elif (ZD_FSYS_CLKSET_DEFAULT==ZD_FSYS_CLKSET_FOSC_DIV2)
		#define FsysClk FocsClk/2
	#elif (ZD_FSYS_CLKSET_DEFAULT==ZD_FSYS_CLKSET_FOSC_DIV4)
		#define FsysClk FocsClk/4
	#elif (ZD_FSYS_CLKSET_DEFAULT==ZD_FSYS_CLKSET_FOSC_DIV8)
		#define FsysClk FocsClk/8
	#elif (ZD_FSYS_CLKSET_DEFAULT==ZD_FSYS_CLKSET_FOSC_DIV16)
		#define FsysClk FocsClk/16
	#elif (ZD_FSYS_CLKSET_DEFAULT==ZD_FSYS_CLKSET_FOSC_DIV32)
		#define FsysClk FocsClk/32
	#elif (ZD_FSYS_CLKSET_DEFAULT==ZD_FSYS_CLKSET_FOSC_DIV64)
		#define FsysClk FocsClk/64		
	#elif (ZD_FSYS_CLKSET_DEFAULT==ZD_FSYS_CLKSET_LFINTOSC_32KHZ)
		#define FsysClk 32000
	#endif

	
	//��ʱ��ʱ������
	#if (ZD_TIMER0_CLKSET_DEFAULT==ZD_TIMER0_CLKSET_FSYS_DIV4)
	
		#if (ZD_TIMER0_CLKPSASET_DEFAULT==ZD_TIMER0_CLKPSASET_NONE)
			#define Ft0Clk FsysClk/4
		#elif (ZD_TIMER0_CLKPSASET_DEFAULT==ZD_TIMER0_CLKPSASET_DIV2)
			#define Ft0Clk FsysClk/4/2
		#elif (ZD_TIMER0_CLKPSASET_DEFAULT==ZD_TIMER0_CLKPSASET_DIV4)
			#define Ft0Clk FsysClk/4/4
		#elif (ZD_TIMER0_CLKPSASET_DEFAULT==ZD_TIMER0_CLKPSASET_DIV8)
			#define Ft0Clk FsysClk/4/8
		#elif (ZD_TIMER0_CLKPSASET_DEFAULT==ZD_TIMER0_CLKPSASET_DIV16)
			#define Ft0Clk FsysClk/4/16
		#elif (ZD_TIMER0_CLKPSASET_DEFAULT==ZD_TIMER0_CLKPSASET_DIV32)
			#define Ft0Clk FsysClk/4/32
		#elif (ZD_TIMER0_CLKPSASET_DEFAULT==ZD_TIMER0_CLKPSASET_DIV64)
			#define Ft0Clk FsysClk/4/64
		#elif (ZD_TIMER0_CLKPSASET_DEFAULT==ZD_TIMER0_CLKPSASET_DIV128)
			#define Ft0Clk FsysClk/4/128
		#elif (ZD_TIMER0_CLKPSASET_DEFAULT==ZD_TIMER0_CLKPSASET_DIV256)
			#define Ft0Clk FsysClk/4/256
		#endif
		
	#endif	


#elif (McuType==McuType_CmsSemicon_CMS80F252X)

	//����ʱ������
	#define FocsClk 48000000
	
	//IO�����׼��	
	#include "cms\cms80f_core.h"

	//ϵͳʱ��
	#if (ZD_FSYS_CLKSET_DEFAULT==ZD_FSYS_CLKSET_FOSC_DIV1)
		#define FsysClk FocsClk/1
	#elif (ZD_FSYS_CLKSET_DEFAULT==ZD_FSYS_CLKSET_FOSC_DIV2)
		#define FsysClk FocsClk/2
	#elif (ZD_FSYS_CLKSET_DEFAULT==ZD_FSYS_CLKSET_FOSC_DIV4)
		#define FsysClk FocsClk/4
	#elif (ZD_FSYS_CLKSET_DEFAULT==ZD_FSYS_CLKSET_FOSC_DIV8)
		#define FsysClk FocsClk/8
	#endif
	
	
	//��ʱ��ʱ������
	#if (ZD_TIMER0_CLKSET_DEFAULT==ZD_TIMER0_CLKSET_FSYS)
		#if (ZD_TIMER0_CLKPSASET_DEFAULT==ZD_TIMER0_CLKPSASET_DIV4)
			#define Ft0Clk FsysClk/4
		#elif (ZD_TIMER0_CLKPSASET_DEFAULT==ZD_TIMER0_CLKPSASET_DIV12)
			#define Ft0Clk FsysClk/12
		#endif
	#endif	
#elif (McuType==McuType_CmsSemicon_CMS80F7518)

	//����ʱ������
	#define FocsClk 48000000
	
	//IO�����׼��	
	#include "cms\cms80f7518_core.h"

	//ϵͳʱ��

	
	
	//��ʱ��ʱ������


#elif (McuType==McuType_SinOneChip_SC92F8463B)

	//����ʱ������
	#define FocsClk 24000000
	
	//�ײ����
	#include <intrins.h>
	
	
	//IO�����׼��	
	#include "soc\touch_92f8x6xb\SC92F846XB_C.H"

	//IO�����׼��	
	#include "soc\soc_core.h"

	//ϵͳʱ��
	#if (ZD_FSYS_CLKSET_DEFAULT==ZD_FSYS_CLKSET_FOSC_DIV1)
		#define FsysClk FocsClk/1
	#elif (ZD_FSYS_CLKSET_DEFAULT==ZD_FSYS_CLKSET_FOSC_DIV2)
		#define FsysClk FocsClk/2
	#elif (ZD_FSYS_CLKSET_DEFAULT==ZD_FSYS_CLKSET_FOSC_DIV4)
		#define FsysClk FocsClk/4
	#elif (ZD_FSYS_CLKSET_DEFAULT==ZD_FSYS_CLKSET_FOSC_DIV12)
		#define FsysClk FocsClk/12
	#endif
	
	
	//��ʱ��ʱ������
	#if (ZD_TIMER0_CLKSET_DEFAULT==ZD_TIMER0_CLKSET_FSYS)
		#if (ZD_TIMER0_CLKPSASET_DEFAULT==ZD_TIMER0_CLKPSASET_DIV1)
			#define Ft0Clk FsysClk/1
		#elif (ZD_TIMER0_CLKPSASET_DEFAULT==ZD_TIMER0_CLKPSASET_DIV12)
			#define Ft0Clk FsysClk/12
		#endif
	#endif	
	
#elif (McuType==McuType_FremontMicroDevices_FT62F13||McuType==McuType_FremontMicroDevices_FT61F13)
	//����ʱ������
	#define FocsClk 16000000
	
	//IO�����׼��	
	#include "fmd\fmd_core.h"

	//ϵͳʱ��

	#if (ZD_FSYS_CLKSET_DEFAULT==ZD_FSYS_CLKSET_FOSC_DIV1)
		#define FsysClk FocsClk/1
	#elif (ZD_FSYS_CLKSET_DEFAULT==ZD_FSYS_CLKSET_FOSC_DIV2)
		#define FsysClk FocsClk/2
	#elif (ZD_FSYS_CLKSET_DEFAULT==ZD_FSYS_CLKSET_FOSC_DIV4)
		#define FsysClk FocsClk/4
	#elif (ZD_FSYS_CLKSET_DEFAULT==ZD_FSYS_CLKSET_FOSC_DIV8)
		#define FsysClk FocsClk/8
	#elif (ZD_FSYS_CLKSET_DEFAULT==ZD_FSYS_CLKSET_FOSC_DIV16)
		#define FsysClk FocsClk/16
	#elif (ZD_FSYS_CLKSET_DEFAULT==ZD_FSYS_CLKSET_FOSC_DIV32)
		#define FsysClk FocsClk/32
	#elif (ZD_FSYS_CLKSET_DEFAULT==ZD_FSYS_CLKSET_FOSC_DIV64)
		#define FsysClk FocsClk/64
	#endif

	//��ʱ��ʱ������,ʱ��ԴΪָ��ʱ��,ʱ������Ϊ2T
	#if (ZD_TIMER0_CLKSET_DEFAULT==ZD_TIMER0_CLKSET_FSYS)
		#if (ZD_TIMER0_CLKPSASET_DEFAULT==ZD_TIMER0_CLKPSASET_DIV1)
			#define Ft0Clk FsysClk/2/1
		#elif (ZD_TIMER0_CLKPSASET_DEFAULT==ZD_TIMER0_CLKPSASET_DIV2)
			#define Ft0Clk FsysClk/2/2
		#elif (ZD_TIMER0_CLKPSASET_DEFAULT==ZD_TIMER0_CLKPSASET_DIV4)
			#define Ft0Clk FsysClk/2/4
		#elif (ZD_TIMER0_CLKPSASET_DEFAULT==ZD_TIMER0_CLKPSASET_DIV8)
			#define Ft0Clk FsysClk/2/8
		#elif (ZD_TIMER0_CLKPSASET_DEFAULT==ZD_TIMER0_CLKPSASET_DIV16)
			#define Ft0Clk FsysClk/2/16
		#elif (ZD_TIMER0_CLKPSASET_DEFAULT==ZD_TIMER0_CLKPSASET_DIV32)
			#define Ft0Clk FsysClk/2/32
		#elif (ZD_TIMER0_CLKPSASET_DEFAULT==ZD_TIMER0_CLKPSASET_DIV64)
			#define Ft0Clk FsysClk/2/64
		#elif (ZD_TIMER0_CLKPSASET_DEFAULT==ZD_TIMER0_CLKPSASET_DIV128)
			#define Ft0Clk FsysClk/2/128
		#elif (ZD_TIMER0_CLKPSASET_DEFAULT==ZD_TIMER0_CLKPSASET_DIV256)
			#define Ft0Clk FsysClk/2/256
		#endif

	#endif	



#elif (McuType==McuType_HD_HD68651)

	//����ʱ������
	#define FocsClk 16000000
	
	//IO�����׼��	
	#include "hd\hd_core.h"

	//ϵͳʱ��

	#if (ZD_FSYS_CLKSET_DEFAULT==ZD_FSYS_CLKSET_FOSC_DIV1)
		#define FsysClk FocsClk/1
	#elif (ZD_FSYS_CLKSET_DEFAULT==ZD_FSYS_CLKSET_FOSC_DIV2)
		#define FsysClk FocsClk/2
	#elif (ZD_FSYS_CLKSET_DEFAULT==ZD_FSYS_CLKSET_FOSC_DIV4)
		#define FsysClk FocsClk/4
	#elif (ZD_FSYS_CLKSET_DEFAULT==ZD_FSYS_CLKSET_FOSC_DIV8)
		#define FsysClk FocsClk/8
	#elif (ZD_FSYS_CLKSET_DEFAULT==ZD_FSYS_CLKSET_FOSC_DIV16)
		#define FsysClk FocsClk/16
	#elif (ZD_FSYS_CLKSET_DEFAULT==ZD_FSYS_CLKSET_FOSC_DIV32)
		#define FsysClk FocsClk/32
	#elif (ZD_FSYS_CLKSET_DEFAULT==ZD_FSYS_CLKSET_FOSC_DIV64)
		#define FsysClk FocsClk/64
	#endif

	//��ʱ��ʱ������,ʱ��ԴΪָ��ʱ��,ʱ������Ϊ2T
	#if (ZD_TIMER0_CLKSET_DEFAULT==ZD_TIMER0_CLKSET_FSYS)
		#if (ZD_TIMER0_CLKPSASET_DEFAULT==ZD_TIMER0_CLKPSASET_DIV1)
			#define Ft0Clk FsysClk/2/1
		#elif (ZD_TIMER0_CLKPSASET_DEFAULT==ZD_TIMER0_CLKPSASET_DIV2)
			#define Ft0Clk FsysClk/2/2
		#elif (ZD_TIMER0_CLKPSASET_DEFAULT==ZD_TIMER0_CLKPSASET_DIV4)
			#define Ft0Clk FsysClk/2/4
		#elif (ZD_TIMER0_CLKPSASET_DEFAULT==ZD_TIMER0_CLKPSASET_DIV8)
			#define Ft0Clk FsysClk/2/8
		#elif (ZD_TIMER0_CLKPSASET_DEFAULT==ZD_TIMER0_CLKPSASET_DIV16)
			#define Ft0Clk FsysClk/2/16
		#elif (ZD_TIMER0_CLKPSASET_DEFAULT==ZD_TIMER0_CLKPSASET_DIV32)
			#define Ft0Clk FsysClk/2/32
		#elif (ZD_TIMER0_CLKPSASET_DEFAULT==ZD_TIMER0_CLKPSASET_DIV64)
			#define Ft0Clk FsysClk/2/64
		#elif (ZD_TIMER0_CLKPSASET_DEFAULT==ZD_TIMER0_CLKPSASET_DIV128)
			#define Ft0Clk FsysClk/2/128
		#elif (ZD_TIMER0_CLKPSASET_DEFAULT==ZD_TIMER0_CLKPSASET_DIV256)
			#define Ft0Clk FsysClk/2/256
		#endif

	#endif	

#elif (McuType==McuType_BydMicro_BF7512)

	//����ʱ������
	#define FocsClk 48000000
	
	//IO�����׼��	
	#include "byd\byd_core.h"

	//ϵͳʱ��
	#if (ZD_FSYS_CLKSET_DEFAULT==ZD_FSYS_CLKSET_FOSC_DIV2_DIV2)
		#define FsysClk FocsClk/4
	#elif (ZD_FSYS_CLKSET_DEFAULT==ZD_FSYS_CLKSET_FOSC_DIV2_DIV4)
		#define FsysClk FocsClk/8
	#elif (ZD_FSYS_CLKSET_DEFAULT==ZD_FSYS_CLKSET_FOSC_DIV2_DIV6)
		#define FsysClk FocsClk/12
	#elif (ZD_FSYS_CLKSET_DEFAULT==ZD_FSYS_CLKSET_FOSC_DIV2_DIV24)
		#define FsysClk FocsClk/48
	#endif


#elif (McuType==McuType_Unkonw)

#endif










#endif