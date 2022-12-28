//******************************************************************************
//Copyright(C) 2020-2021 zhejiang zhida dianzikeji Co., Ltd
//�㽭�Ǵ���ӿƼ����޹�˾
//File name:      function.h
//Author:         zzg
//Version:        Ver0.1
//Date:           2021-4-25
//Description:    ����
//History:
//******************************************************************************
#ifndef __APPSTDLIB_LIMIT_VALUE_CHECK_APP_H__
#define __APPSTDLIB_LIMIT_VALUE_CHECK_APP_H__
//******************************************************************

unsigned char ucharLimitValueCheck(unsigned char *setval,unsigned char min,unsigned char max);
unsigned int uintLimitValueCheck(unsigned int *setval,unsigned int min,unsigned int max);
signed char charLimitValueCheck(signed char *setval,signed char min,signed char max);
signed int intLimitValueCheck(signed int *setval,signed int min,signed int max);


//ʹ��ʾ��
/*

#define CheckSetBoilingTemp(x) ucharLimitValueCheck((x),SET_BOILINGTEMP_MIN,SET_BOILINGTEMP_MAX)
#define CheckSetTemp(x)  ucharLimitValueCheck((x),SET_TEMP_MIN,(gucv_set_boilingtemp))
#define CheckSetWarmTime(x) ucharLimitValueCheck((x),SET_WARMTIME_MIN,SET_WARMTIME_MAX)
#define CheckSetWaterTime(x) ucharLimitValueCheck((x),SET_WATERTIME_MIN,SET_WATERTIME_MAX)


*/


#endif 


/************************ (C) COPYRIGHT zhejiang zhida *****END OF FILE****/