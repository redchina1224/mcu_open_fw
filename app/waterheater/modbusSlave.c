
#include "..\bsp\bsp.h"

unsigned int GetCRC16(unsigned char* database, unsigned char length);

unsigned long SyncTimeUtcSec;



bit ModbusBusy(void)
{
	return S1_Busy;
}

void ModbusSlaveInit(void)
{
	Rs485nit();
}

void MODS_ReadInputValue(void (*Rs485Send) (unsigned char),unsigned char * Rs485ReadBuffer,unsigned char * Rs485WriteBuffer)
{
	unsigned int CRC_Value;
	unsigned char mask=0xFF;
	if(0x00==Rs485ReadBuffer[2]&&0x00==Rs485ReadBuffer[3])
	{
		Rs485WriteBuffer[0]=Rs485ReadBuffer[0]; //Addr
		Rs485WriteBuffer[1]=2; //Fun
		Rs485WriteBuffer[2]=1; //Byte count 
		
		
		CRC_Value=GetCRC16(Rs485WriteBuffer,4);
		Rs485WriteBuffer[4]=CRC_Value%256;
		Rs485WriteBuffer[5]=CRC_Value/256;
		Rs485Send(6);
	}
}



void MODS_ReadCoilValue(void (*Rs485Send) (unsigned char),unsigned char * Rs485ReadBuffer,unsigned char * Rs485WriteBuffer)
{
	unsigned int CRC_Value;

	if(0x00==Rs485ReadBuffer[2]&&0x00==Rs485ReadBuffer[3])
	{
		Rs485WriteBuffer[0]=Rs485ReadBuffer[0]; //Addr
		Rs485WriteBuffer[1]=1; //Fun
		Rs485WriteBuffer[2]=1; //Byte count 
		


		CRC_Value=GetCRC16(Rs485WriteBuffer,4);
		Rs485WriteBuffer[4]=CRC_Value%256;
		Rs485WriteBuffer[5]=CRC_Value/256;
		Rs485Send(6);
	}
}


void MODS_WriteCoilValue(void (*Rs485Send) (unsigned char),unsigned char * Rs485ReadBuffer,unsigned char * Rs485WriteBuffer)
{
	unsigned int CRC_Value;
	
	if(0x00==Rs485ReadBuffer[2]&&0x00==Rs485ReadBuffer[3])
	{
		
		Rs485WriteBuffer[0]=Rs485ReadBuffer[0]; //Addr
		Rs485WriteBuffer[1]=5; //Fun

		
		CRC_Value=GetCRC16(Rs485WriteBuffer,6);
		Rs485WriteBuffer[6]=CRC_Value%256;
		Rs485WriteBuffer[7]=CRC_Value/256;
		Rs485Send(8);		
	}
	else if(0x69==Rs485ReadBuffer[2]&&0x01==Rs485ReadBuffer[3])
	{


		Rs485WriteBuffer[0]=Rs485ReadBuffer[0]; //Addr
		Rs485WriteBuffer[1]=5; //Fun
		
		Rs485WriteBuffer[2]=0x69; //startAddr
		Rs485WriteBuffer[3]=0x01; //startAddr
		

		
		CRC_Value=GetCRC16(Rs485WriteBuffer,6);
		Rs485WriteBuffer[6]=CRC_Value%256;
		Rs485WriteBuffer[7]=CRC_Value/256;
		Rs485Send(8);		
	}	
	else if(0x69==Rs485ReadBuffer[2]&&0x02==Rs485ReadBuffer[3])
	{


		Rs485WriteBuffer[0]=Rs485ReadBuffer[0]; //Addr
		Rs485WriteBuffer[1]=5; //Fun
		
		Rs485WriteBuffer[2]=0x69; //startAddr
		Rs485WriteBuffer[3]=0x02; //startAddr
		
		
		CRC_Value=GetCRC16(Rs485WriteBuffer,6);
		Rs485WriteBuffer[6]=CRC_Value%256;
		Rs485WriteBuffer[7]=CRC_Value/256;
		Rs485Send(8);		
	}	
}



void MODS_ReadRegValue(void (*Rs485Send) (unsigned char),unsigned char * Rs485ReadBuffer,unsigned char * Rs485WriteBuffer)
{
	unsigned int reg_value=0;
		unsigned int CRC_Value;
	unsigned long temp=0;
	reg_value=Rs485ReadBuffer[2];
	reg_value=reg_value<<8;
	reg_value+=Rs485ReadBuffer[3];
	
	
	Rs485WriteBuffer[0]=Rs485ReadBuffer[0]; //Addr
	Rs485WriteBuffer[1]=3; //Fun
	

	switch (reg_value)
	{	
		case 0x000: //产品版本信息 <---01 03 00 00 00 04 44 09 , 01 03 08 AA BB CC DD 00 03 00 04 18 C7 -->
								if(0x00==Rs485ReadBuffer[4]&&0x04==Rs485ReadBuffer[5])
								{
									Rs485WriteBuffer[2]=8; //byte length
									


									CRC_Value=GetCRC16(Rs485WriteBuffer,11);
									Rs485WriteBuffer[11]=CRC_Value%256;
									Rs485WriteBuffer[12]=CRC_Value/256;
									Rs485Send(13);	
							
									
								}

                break;	
		case 0x004: //产品序列号
								if(0x00==Rs485ReadBuffer[4]&&0x04==Rs485ReadBuffer[5])
								{
									Rs485WriteBuffer[2]=8; //byte length
									


									Rs485WriteBuffer[10]=0; ///cdata
									
									CRC_Value=GetCRC16(Rs485WriteBuffer,11);
									Rs485WriteBuffer[11]=CRC_Value%256;
									Rs485WriteBuffer[12]=CRC_Value/256;
									Rs485Send(13);	
								
									
								}
                break;	
					
								
		default:

                break;
	}

}

void MODS_WriteRegValue(void (*Rs485Send) (unsigned char),unsigned char * Rs485ReadBuffer,unsigned char * Rs485WriteBuffer)
{
	unsigned int reg_value=0;
		unsigned int CRC_Value;
	unsigned long temp;
	reg_value=Rs485ReadBuffer[2];
	reg_value=reg_value<<8;
	reg_value+=Rs485ReadBuffer[3];
	
	
	Rs485WriteBuffer[0]=Rs485ReadBuffer[0]; //Addr
	Rs485WriteBuffer[1]=0x10; //Fun
	

	switch (reg_value)
	{	
		
		
		case 0x004: //设置stcid
								if(0x00==Rs485ReadBuffer[4]&&0x04==Rs485ReadBuffer[5]&&0x08==Rs485ReadBuffer[6])
								{

									
									Rs485WriteBuffer[2]=0x00; //reg_value
									Rs485WriteBuffer[3]=0x04; //reg_value
									
									Rs485WriteBuffer[4]=0x00; ///write length
									Rs485WriteBuffer[5]=0x04; ///write length
																		
									CRC_Value=GetCRC16(Rs485WriteBuffer,6);
									Rs485WriteBuffer[6]=CRC_Value%256;
									Rs485WriteBuffer[7]=CRC_Value/256;
									Rs485Send(8);	
								}
                break;	

								default:break;
	}

}



unsigned int GetCRC16(unsigned char* database, unsigned char length) 
{ 
	int j; 
	unsigned int reg_crc=0Xffff; 
	while(length--) 
	{ 
		reg_crc ^= *database++; 
		for (j=0;j<8;j++) 
		{ 
			if (reg_crc & 0x01) reg_crc=(reg_crc>>1) ^ 0Xa001; /* LSB(b0)=1 */ 
			else reg_crc=reg_crc >>1; 
		} 
	} 
	return reg_crc;
} 

//bit ModbusCrcCheck(unsigned char length)
//{
//	unsigned int CRC_Value=0;  //
//	unsigned int CRC_Recv=0;  //
//	
////	CRC_Value=GetCRC16(Rs485ReadBuffer,length);
////	CRC_Recv=(Rs485ReadBuffer[length+1]*256)+Rs485ReadBuffer[length];
////	
////	if(CRC_Value==CRC_Recv) return 1;
//	
//	if(0==GetCRC16(Rs485ReadBuffer,length)) return 1;
//	return 0;
//		
//}

bit ModbusSlaveTask(void)
{

	if(Uart1_Rs485ReadOverCheck()&&0==GetCRC16(Uart1_Rs485ReadBuffer,Uart1_Rs485RecvLength))
	{

		switch (Uart1_Rs485ReadBuffer[1])	
		{	
			
			case 0x01: //读取输出端口bit
							MODS_ReadCoilValue(Uart1_Rs485Send,Uart1_Rs485ReadBuffer,Uart1_Rs485WriteBuffer);
							break;	
			case 0x02: //读取输入端口bit
							MODS_ReadInputValue(Uart1_Rs485Send,Uart1_Rs485ReadBuffer,Uart1_Rs485WriteBuffer);
							break;					
			case 0x03: //读取保持寄存器
							MODS_ReadRegValue(Uart1_Rs485Send,Uart1_Rs485ReadBuffer,Uart1_Rs485WriteBuffer);
							break;		
			case 0x05: //强置单线圈bit
							MODS_WriteCoilValue(Uart1_Rs485Send,Uart1_Rs485ReadBuffer,Uart1_Rs485WriteBuffer);
							break;		
			case 0x06: //预置单寄存器
//							Wifi_Rs485WriteBuffer[0]=0x06;
//							Wifi_Rs485WriteBuffer[1]=0x06;
							break;	
			case 0x10: //预置多寄存器
							MODS_WriteRegValue(Uart1_Rs485Send,Uart1_Rs485ReadBuffer,Uart1_Rs485WriteBuffer);
							break;	
			default:

							break;
		}		

		
		return 1;
	}
		return 0;
}



void ModbusMasterSend(unsigned char reg) //非标准自定义用户协议，用于主动上报数据
{
	
	unsigned int CRC_Value;
	unsigned char indextemp;
	unsigned long sendutcsec;
	
	//sendutcsec=GetUtcSec();
	
	Uart1_Rs485WriteBuffer[0]=0x01; //Addr
	Uart1_Rs485WriteBuffer[1]=0x47; //Fun
	
	Uart1_Rs485WriteBuffer[2]=reg; //regAddr


	switch (reg)
	{	
		case 0x21: //用户上报
									Uart1_Rs485WriteBuffer[3]=6; //byte length
									
									Uart1_Rs485WriteBuffer[4]=0; //cdata
									Uart1_Rs485WriteBuffer[5]=1; ///cdata
						
									Uart1_Rs485WriteBuffer[6]=sendutcsec>>24; ///cdata
									Uart1_Rs485WriteBuffer[7]=sendutcsec>>16; ///cdata
									Uart1_Rs485WriteBuffer[8]=sendutcsec>>8; ///cdata
									Uart1_Rs485WriteBuffer[9]=sendutcsec; ///cdata
									
									CRC_Value=GetCRC16(Uart1_Rs485WriteBuffer,10);
									Uart1_Rs485WriteBuffer[10]=CRC_Value%256;
									Uart1_Rs485WriteBuffer[11]=CRC_Value/256;
									Uart1_Rs485Send(12);	

                break;	


		default:	//每分钟上报,运行时钟
			

                break;
	}	
	
	
	
	
	
}



