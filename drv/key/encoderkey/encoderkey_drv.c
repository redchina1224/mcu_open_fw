//******************************************************************************
//Copyright(C) 2020-2021 zhejiang zhida dianzikeji Co., Ltd
//浙江智达电子科技有限公司
//File name:      TM1628.c
//Author:         zzg
//Version:        Ver0.1
//Date:           2021-4-25
//Description:    TM1628驱动
//History:
//******************************************************************************
//头文件************************************************************************
#include "..\..\com_include_drv.h"
//******************************************************************************
#ifdef ENCODER_KEY_TOTAL_NUM
#if(ENCODER_KEY_TOTAL_NUM>0)

mof_encoder_key_t xdata encoder_key[ONEWIRE_DENG_TOTAL_NUM];
unsigned char xdata encoder_key_object_select=0;


/***********************************************************************************************
*函数名 		: void onewrite_fixed_length_in_isr(void)
*函数功能描述 	: 单线通讯邓氏接收服务程序(用于数据连续接收和发送)
*函数参数 		: unsigned char *RxReg：串口硬件接收缓存地址指针
*函数返回值 	: 无
***********************************************************************************************/
void mof_encoder_key_read(void)
{
	if(encoder_key[0].key_cw_data!=0&&encoder_key[0].key_cw_clr_flag==0&&encoder_key[0].key_cw_user_data==0)
	{
		encoder_key[0].key_cw_user_data=encoder_key[0].key_cw_data;
	}
	
	if(encoder_key[0].key_ccw_data!=0&&encoder_key[0].key_ccw_clr_flag==0&&encoder_key[0].key_ccw_user_data==0)
	{
		encoder_key[0].key_ccw_user_data=encoder_key[0].key_ccw_data;
	}
}

/***********************************************************************************************
*函数名 		: void onewrite_fixed_length_in_isr(void)
*函数功能描述 	: 单线通讯邓氏接收服务程序(用于数据连续接收和发送)
*函数参数 		: unsigned char *RxReg：串口硬件接收缓存地址指针
*函数返回值 	: 无
***********************************************************************************************/
void mof_encoder_key_clear(void)
{
	if(encoder_key[0].key_cw_user_data&&encoder_key[0].key_cw_clr_flag==0)
	{
		encoder_key[0].key_cw_clr_flag=encoder_key[0].key_cw_user_data;
		encoder_key[0].key_cw_user_data=0;
	}

	if(encoder_key[0].key_ccw_user_data&&encoder_key[0].key_ccw_clr_flag==0)
	{
		encoder_key[0].key_ccw_clr_flag=encoder_key[0].key_ccw_user_data;
		encoder_key[0].key_ccw_user_data=0;
	}

}

/***********************************************************************************************
*函数名 		: void onewrite_fixed_length_in_isr(void)
*函数功能描述 	: 单线通讯邓氏接收服务程序(用于数据连续接收和发送)
*函数参数 		: unsigned char *RxReg：串口硬件接收缓存地址指针
*函数返回值 	: 无
***********************************************************************************************/
void mof_encoder_key_init(void)
{

		encoder_key[0].key_cw_clr_flag=0;
		encoder_key[0].key_ccw_clr_flag=0;
		encoder_key[0].key_cw_user_data=0;
		encoder_key[0].key_ccw_user_data=0;

		encoder_key[0].key_cw_data=0;
		encoder_key[0].key_ccw_data=0;
		encoder_key[0].code_value=3;
		encoder_key[0].code_value_ago=3;
		encoder_key[0].code_value_serial=0;

	
//							if(i==0)
//							{
							#ifdef EncoderKey_Phase_A_IO_Channel
								EncoderKey_Phase_A_IO_Input;
							#endif
							#ifdef EncoderKey_Phase_B_IO_Channel
								EncoderKey_Phase_B_IO_Input;
							#endif
//							}
//		#if (ENCODER_KEY_TOTAL_NUM>1)
//							else if(i==1)
//							{
//							#ifdef EncoderKey2_Phase_A_IO_Channel
//								EncoderKey2_Phase_A_IO_Input;
//							#endif
//							#ifdef EncoderKey2_Phase_B_IO_Channel
//								EncoderKey2_Phase_B_IO_Input;
//							#endif
//							}	
//		#endif
//		#if (ENCODER_KEY_TOTAL_NUM>2)
//							else if(i==2)
//							{
//							#ifdef EncoderKey3_Phase_A_IO_Channel
//								EncoderKey3_Phase_A_IO_Input;
//							#endif
//							#ifdef EncoderKey3_Phase_B_IO_Channel
//								EncoderKey3_Phase_B_IO_Input;
//							#endif
//							}	
//		#endif	
	
}



/***********************************************************************************************
*函数名 		: void onewrite_fixed_length_in_isr(void)
*函数功能描述 	: 单线通讯邓氏接收服务程序(用于数据连续接收和发送)
*函数参数 		: unsigned char *RxReg：串口硬件接收缓存地址指针
*函数返回值 	: 无
***********************************************************************************************/
void mof_encoder_key_in_isr(void)
{

#if(ENCODER_KEY_TOTAL_NUM>1)
	for(encoder_key_object_select=0;encoder_key_object_select<(ENCODER_KEY_TOTAL_NUM);encoder_key_object_select++)
	{
#else
	{
		encoder_key_object_select=0;
#endif
		encoder_key[encoder_key_object_select].code_value=(EncoderKey_Phase_A_IO_Channel);
		if(EncoderKey_Phase_B_IO_Channel) encoder_key[encoder_key_object_select].code_value|=0x02;
		
		if(encoder_key[encoder_key_object_select].code_value_ago!=encoder_key[encoder_key_object_select].code_value) //编码值有变化
		{
			encoder_key[encoder_key_object_select].code_value_ago=encoder_key[0].code_value;
			
			encoder_key[encoder_key_object_select].code_value_serial<<=2;
			encoder_key[encoder_key_object_select].code_value_serial|=encoder_key[encoder_key_object_select].code_value;
			
			if(encoder_key[encoder_key_object_select].code_value==3) //停止旋转
			{
				if(encoder_key[encoder_key_object_select].code_value_serial==0x4B) //1023顺时针
				{
					encoder_key[encoder_key_object_select].key_cw_data++;
				}
				else if(encoder_key[encoder_key_object_select].code_value_serial==0x87) //2013逆时针
				{
					encoder_key[encoder_key_object_select].key_ccw_data++;
				}
			}			
		}
		else if(encoder_key[encoder_key_object_select].code_value==3) //停止旋转
		{
			if(encoder_key[encoder_key_object_select].key_cw_clr_flag!=0)
			{
				if(encoder_key[encoder_key_object_select].key_cw_data>=encoder_key[encoder_key_object_select].key_cw_clr_flag) encoder_key[encoder_key_object_select].key_cw_data-=encoder_key[encoder_key_object_select].key_cw_clr_flag;
				encoder_key[encoder_key_object_select].key_cw_clr_flag=0;
			}
			if(encoder_key[encoder_key_object_select].key_ccw_clr_flag!=0)
			{
				if(encoder_key[encoder_key_object_select].key_ccw_data>=encoder_key[encoder_key_object_select].key_ccw_clr_flag) encoder_key[encoder_key_object_select].key_ccw_data-=encoder_key[encoder_key_object_select].key_ccw_clr_flag;
				encoder_key[encoder_key_object_select].key_ccw_clr_flag=0;
			}
		}
		
	}
}
#endif
#endif