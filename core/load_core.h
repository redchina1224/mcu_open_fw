#ifndef __CORECONFIG_LOAD_H_
#define __CORECONFIG_LOAD_H_

//��оƬ�����Ӧͷ�ļ� �������׼���ӿ�
#if((McuType&McuType_FacMask)==McuType_CaChip)

	//����ʱ������
	//#define FocsClk 16000000

	//IO�����׼��	
	#include "cachip\load_cachip_core.h"

	//������궨��
	//#include "cms\touch_79ft72x\CMS_CheckTouch_PT_79F72x_V1.01.h"


	
	//ϵͳʱ��
	
	//��ʱ��0ʱ������

	//��ʱ��1ʱ������
	//#define Ft1Clk FsysClk/4/1

	//��ʱ��2ʱ������


#elif (McuType==McuType_Unkonw)

#endif



#endif

