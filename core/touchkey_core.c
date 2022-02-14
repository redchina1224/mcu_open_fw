//******************************************************************************
//Copyright(C) 2020-2021 zhejiang zhida dianzikeji Co., Ltd
//浙江智达电子科技有限公司
//File name:      touchkey_core.c
//Author:         zzg
//Version:        Ver0.1
//Date:           2021-4-25
//Description:    触摸按键标准接口
//History:
//******************************************************************************
//头文件************************************************************************
#include "com_include_core.h"


#ifdef KeyType
#if (KeyType==KeyType_McuTouch)




#if (McuType==McuType_CmsSemicon_CMS79F738)
	#include "cms\touch_79ft73x\Touch_Kscan_Library.c"
#endif





/***********************************************************************************************
*函数名 		: void zd_touchkeyInit(void)
*函数功能描述 	: 初始化触摸按键
*函数参数 		: 无
*函数返回值 	: 无
***********************************************************************************************/
void zd_touchkeyInit(void)
{

	#if (McuType==McuType_SinOneChip_SC92F8463B)
			//赛元微触控按键初始化
			TouchKeyInit();	
	#endif

}


/***********************************************************************************************
*函数名 		: unsigned long zd_touchkeyRead(void)
*函数功能描述 	: 初始化触摸按键
*函数参数 		: unsigned long *keyval ：按键值地址指针
*函数返回值 	: unsigned char  按键值状态  1：键值有更新  0：键值无更新
***********************************************************************************************/
unsigned char zd_touchkeyRead(unsigned long *keyval)
{

		#if (McuType==McuType_SinOneChip_SC92F8463B)
		//赛元微触控取值
		if(SOCAPI_TouchKeyStatus&0x80)	    //重要步骤2:  触摸键扫描一轮标志，是否调用TouchKeyScan()一定要根据此标志位置起后
		 {	   																	
			SOCAPI_TouchKeyStatus &= 0x7f;	//重要步骤3: 清除标志位， 需要外部清除。													    
			(*keyval) = TouchKeyScan();//按键数据处理函数   
			
			TouchKeyRestart();				//启动下一轮转换		
			return 1;
		}
		#elif (McuType==McuType_CmsSemicon_CMS79F738)

		/*
		(*keyval)=_CMS_KeyFlag[2];
		(*keyval)<<=8;
		(*keyval)|=_CMS_KeyFlag[1];
		(*keyval)<<=8;
		(*keyval)|=_CMS_KeyFlag[0];
		*/
		(*keyval)=(unsigned long)(_CMS_KeyFlag[0]);
		return 1;
		#endif
		
return 0;
}



#endif
#endif

/************************ (C) COPYRIGHT zhejiang zhida *****END OF FILE****/