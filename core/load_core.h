#ifndef __CORECONFIG_LOAD_H_
#define __CORECONFIG_LOAD_H_

//��оƬ�����Ӧͷ�ļ� �������׼���ӿ�
#if((McuType&McuType_FacMask)==McuType_CaChip)

	//����ʱ������
	#define FocsClk 32000000

	//IO�����׼��	
	#include "cachip\load_cachip_core.h"

	//������궨��
	//#include "cms\touch_79ft72x\CMS_CheckTouch_PT_79F72x_V1.01.h"


	
	//ϵͳʱ��
	#define FsysClk (FocsClk/2)
	
	//��ʱ��0ʱ������
	//#define Ft0Clk FsysClk/12
	//��ʱ��1ʱ������
	//#define Ft1Clk FsysClk/12

	//��ʱ��2ʱ������
	#define Ft2Clk (FsysClk/1)

#elif (McuType==McuType_Unkonw)

#endif



#endif

