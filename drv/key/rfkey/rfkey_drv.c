#include "..\..\com_include_drv.h"



unsigned long __ZD_RfKeyValue=0;

unsigned long gulv_Read_Data;
	
unsigned char ioL_timeout=0;		//IO低电平超时
unsigned char ioH_timeout=0;//IO高电平超时
unsigned char io_data_ago=0;		//IO电平历史值

unsigned char bit_ioH_checktime=0;		//接收位判定高电平时间值
unsigned char bit_read_count=0;		//接收位计数值
//unsigned char test_bit_read_count=0;		//接收位判定高电平时间值


/***********************************************************************************************
*函数名 		: void zd_touchkeyInit(void)
*函数功能描述 	: 初始化RF遥控按键
*函数参数 		: 无
*函数返回值 	: 无
***********************************************************************************************/
void zd_rfkeyInit(void)
{
	#if (RfKeyType==RfKeyType_IoWidthCode)
		RFKEY_POWER_IO_Output;
		RFKEY_DATA_IO_Input;
		RFKEY_POWER_IO_Ctrl(RFKEY_POWER_IO_ON);
	#endif


}


/***********************************************************************************************
*函数名 		: unsigned long zd_touchkeyRead(void)
*函数功能描述 	: 获取RF遥控按键值
*函数参数 		: unsigned long *keyval ：按键值地址指针
*函数返回值 	: unsigned char  按键值状态  1：键值有更新  0：键值无更新
***********************************************************************************************/
unsigned char zd_rfkeyRead(unsigned long *keyval)
{
	if((*keyval)==__ZD_RfKeyValue)
	{
		return 0;
	}
	else
	{
		(*keyval)=__ZD_RfKeyValue;
		return 1;
	}
}

/***********************************************************************************************
*函数名 		: void __ZD_GetRfKeyValue(void)
*函数功能描述 	: 中断采集RF遥控信号
*函数参数 		: 无
*函数返回值 	: 无
***********************************************************************************************/
void __ZD_GetRfKeyValue(void)
{

	if(RFKEY_DATA_IO_Channel==0)//低电平
	{
		//低电平超时
		if(ioL_timeout<32)
		{
			ioL_timeout++;
			
			if(ioL_timeout>=32)
			{
				if(bit_read_count==25)
				{
					__ZD_RfKeyValue=gulv_Read_Data;
				}
				else
					__ZD_RfKeyValue=0;
				
				gulv_Read_Data=0;
				bit_read_count=0;
			}
		}
		else
		{
			return;
		}
		
		//高电平超时清零
		ioH_timeout=0;
		
		//低电平接收
		if(io_data_ago==1)
		{
			io_data_ago=0;
			if(bit_ioH_checktime>=8)//位为1
			{
				gulv_Read_Data|=BIT0;
			}
			
			if(bit_read_count<32)
			{
				bit_read_count++;
			}
		}
	}
	else//高电平
	{

		//高电平超时
		if(ioH_timeout<32)
		{
			ioH_timeout++;
			if(ioH_timeout>=32)
			{
				gulv_Read_Data=0;
				__ZD_RfKeyValue=0;
				bit_read_count=0;
			}
		}
		else
		{
			return;
		}
				
		//低电平超时清零
		ioL_timeout=0;
		
		
		//高电平接收
		if(io_data_ago==0)
		{
			io_data_ago=1;
			bit_ioH_checktime=0;//上升沿开始作为数据位1和0时间判定的起始点
			gulv_Read_Data<<=1;
		}
		else
			bit_ioH_checktime++;
	}
	
}

