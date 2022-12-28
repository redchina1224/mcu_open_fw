//******************************************************************************
//Copyright(C) 2020-2021 zhejiang zhida dianzikeji Co., Ltd
//浙江智达电子科技有限公司
//File name:      limmit_value_check_app.c
//Author:         zzg
//Version:        Ver0.1
//Date:           2021-4-25
//Description:    一般用于设置值从EEPROM取出或者用户设置完成时，进行数值合归限值检查。
//History:
//******************************************************************************
//头文件************************************************************************
#include "..\..\com_include_app.h"

unsigned char ucharLimitValueCheck(unsigned char *setval,unsigned char min,unsigned char max)
{
	if((*setval)>max)
	{
		(*setval)=max;
		return min;
	}
	else if((*setval)<min)
	{
		(*setval)=min;
		return max;
	}
	else
	{
		return (*setval);
	}
}

unsigned int uintLimitValueCheck(unsigned int *setval,unsigned int min,unsigned int max)
{
	if((*setval)>max)
	{
		(*setval)=max;
		return min;
	}
	else if((*setval)<min)
	{
		(*setval)=min;
		return max;
	}
	else
	{
		return (*setval);
	}
}

signed char charLimitValueCheck(signed char *setval,signed char min,signed char max)
{
	if((*setval)>max)
	{
		(*setval)=max;
		return min;
	}
	else if((*setval)<min)
	{
		(*setval)=min;
		return max;
	}
	else
	{
		return (*setval);
	}
}

signed int intLimitValueCheck(signed int *setval,signed int min,signed int max)
{
	if((*setval)>max)
	{
		(*setval)=max;
		return min;
	}
	else if((*setval)<min)
	{
		(*setval)=min;
		return max;
	}
	else
	{
		return (*setval);
	}
}