#ifndef __LOAD_CACHIP_CORE_H_
#define __LOAD_CACHIP_CORE_H_

//��оƬ�����Ӧͷ�ļ� �������׼���ӿ�
#if (McuType==McuType_CaChip_CA51F003)

	//����ʱ������
	#define FocsClk 32000000

	//IO�����׼��	
	#include "Device\CA51F003\ca51f003_core.h"

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

#elif (McuType==McuType_CaChip_CA51F005)
	//����ʱ������
	#define FocsClk 24000000

	//IO�����׼��	
	#include "Device\CA51F005\ca51f005_core.h"

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
#elif (McuType==McuType_CaChip_CA51F3)
	//����ʱ������
	#define FocsClk (3686400)

	//IO�����׼��	
	#include "Device\CA51F3\ca51f3_core.h"

	//������궨��
	//#include "cms\touch_79ft72x\CMS_CheckTouch_PT_79F72x_V1.01.h"

	//ϵͳʱ��
	#define FsysClk (FocsClk*MOF_FSYS_CLKPLL_MULTIPLE_DEFAULT)
	
	//��ʱ��0ʱ������
	//#define Ft0Clk FsysClk/12
	//��ʱ��1ʱ������
	//#define Ft1Clk FsysClk/12

	//��ʱ��2ʱ������
	#define Ft2Clk (FsysClk/1)


#elif (McuType==McuType_Unkonw)

#endif



#endif

