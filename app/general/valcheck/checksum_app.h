//******************************************************************************
//Copyright(C) 2020-2021 zhejiang zhida dianzikeji Co., Ltd
//浙江智达电子科技有限公司
//File name:      function.h
//Author:         zzg
//Version:        Ver0.1
//Date:           2021-4-25
//Description:    功能
//History:
//******************************************************************************
#ifndef __APPSTDLIB_CHECKSUM_APP_H__
#define __APPSTDLIB_CHECKSUM_APP_H__
//******************************************************************

unsigned int GetCheckSum16(unsigned char* database, unsigned char length,unsigned int checksum);

unsigned char GetCheckSum8(unsigned char* database, unsigned char length,unsigned char checksum);

void data_char_fix(unsigned char* database,unsigned char length,unsigned char dat);

//使用示例
/*


*/


#endif 


/************************ (C) COPYRIGHT zhejiang zhida *****END OF FILE****/