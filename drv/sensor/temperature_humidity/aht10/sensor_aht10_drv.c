#include "..\..\..\com_include_drv.h"

//#define Aht_addr_write 0x38
//#define Aht_addr_read (Aht_addr_write|0x01)
//#define Aht_cmd_init 0xBE

#define Aht_cmd_measure 0xAC
//#define Aht_cmd_reset 0xBA


#define Aht_delayms core_DelayUs

mof_sensor_aht10_t xdata sensor_aht10;
void mof_sensor_aht10_Send_Measuer(void);

//void Aht_Send_Reset(void);
//void Aht_Send_Init(void);
unsigned char mof_sensor_aht10_Read_Status(void);
//bit Aht_Read_Cal_Enable(void);



void mof_sensor_aht10_Send_Measuer(void) //向AHT10发送AC命令
{
 I2C_Start();
 I2C_SendByte(0x70);
 I2C_WaitToAck();
 I2C_SendByte(Aht_cmd_measure);
 I2C_WaitToAck();
 I2C_SendByte(0x33);
 I2C_WaitToAck();
 I2C_SendByte(0x00);
 I2C_WaitToAck();
 I2C_Stop();
}



void mof_sensor_aht10_Reset_REG(unsigned char addr)
{
	
	unsigned char Byte_first,Byte_second,Byte_third;//,Byte_fourth;
	
	
	I2C_Start();
	I2C_SendByte(0x70);
	I2C_WaitToAck();
	I2C_SendByte(addr);//写系统配置寄存器
	I2C_WaitToAck();
	I2C_SendByte(0x00);
	I2C_WaitToAck();
	I2C_SendByte(0x00);
	I2C_WaitToAck();
	I2C_Stop();
	

	Aht_delayms(25);


	I2C_Start();
	I2C_SendByte(0x71);//0x70+1   0x70为设备地址 1为方向位
	I2C_WaitToAck();
	Byte_first = I2C_ReadByte();
	I2C_Ack();
	Byte_second = I2C_ReadByte();
	I2C_Ack();
	Byte_third = I2C_ReadByte();
	I2C_NoAck();
	I2C_Stop();

	Aht_delayms(25);
	

	I2C_Start();
	I2C_SendByte(0x70);
	I2C_WaitToAck();
	I2C_SendByte(0xB0|addr);//写系统配置寄存器
	I2C_WaitToAck();
	I2C_SendByte(Byte_second);
	I2C_WaitToAck();
	I2C_SendByte(Byte_third);
	I2C_WaitToAck();
	I2C_Stop();

}



unsigned char mof_sensor_aht10_Read_CTdata(void) //读取AHT10的温度和湿度数据
{
	static unsigned char xdata read_case=0;
	static unsigned char xdata read_delay=0;
	unsigned char Byte_1th=0;
	unsigned char Byte_2th=0;
	unsigned char Byte_3th=0;
	unsigned char Byte_4th=0;
	unsigned char Byte_5th=0;
	unsigned char Byte_6th=0;
	unsigned long RetuData = 0;
	
	unsigned char readok = 0;

	switch(read_case)
	{
		case 0:
			if((mof_sensor_aht10_Read_Status()&0x18)!=0x18)
			{
				//重新初始化寄存器
				mof_sensor_aht10_Reset_REG(0x1b);
				mof_sensor_aht10_Reset_REG(0x1c);
				mof_sensor_aht10_Reset_REG(0x1e);
			}
			else
			{
				read_case++;
			}
		break;
		case 1:
			mof_sensor_aht10_Send_Measuer();//向AHT10发送AC命令
			read_delay=0;
			read_case++;
		break;
		case 2:
			if(((mof_sensor_aht10_Read_Status()&0x80)==0x80))
			{
				if(++read_delay>10) read_case=0;
			}
			else read_case++;
		break;
		case 3:
			I2C_Start();
			I2C_SendByte(0x71);//0x70+1   0x70为设备地址 1为方向位
			I2C_WaitToAck();
			Byte_1th = I2C_ReadByte();//状态字
			I2C_Ack();
			Byte_2th = I2C_ReadByte();//湿度字节
			I2C_Ack();
			Byte_3th = I2C_ReadByte();//湿度字节
			I2C_Ack();
			Byte_4th = I2C_ReadByte();//高4位为湿度  低4位为温度
			I2C_Ack();
			Byte_5th = I2C_ReadByte();//温度字节
			I2C_Ack();
			Byte_6th = I2C_ReadByte();//温度字节
			I2C_NoAck();
			I2C_Stop();


			RetuData = (RetuData|Byte_2th)<<8;
			RetuData = (RetuData|Byte_3th)<<8;
			RetuData = (RetuData|Byte_4th);
			RetuData =RetuData >>4;

			sensor_aht10.humidity=RetuData*1000/1024/1024;  //计算得到湿度值（放大了10倍,如果c1=523，表示现在湿度为52.3%）
			
			RetuData = 0;
			RetuData = (RetuData|Byte_4th)<<8;
			RetuData = (RetuData|Byte_5th)<<8;
			RetuData = (RetuData|Byte_6th);
			RetuData = RetuData&0xfffff;

			if(RetuData>262144)
			{
				sensor_aht10.temperature=RetuData*200*10/1024/1024-500;//计算得到温度值（放大了10倍，如果t1=245，表示现在温度为24.5℃）
			}
			else
			{
				sensor_aht10.temperature=0;
			}
			
			readok=1;
			
			read_delay=0;
			read_case++;
		break;
		case 0xe0:

		break;
		default:
			read_case=0;
		break;
		
	}
	
	return readok;

}

//void Aht_Send_Reset(void)//向AHT10发送BA命令
//{
// I2C_Start();
// I2C_SendByte(Aht_addr_write);//Aht_addr_write);
// I2C_WaitToAck();
// I2C_SendByte(Aht_cmd_reset);
// I2C_WaitToAck();
// I2C_Stop();
//}

//void Aht_Send_Init(void)//向AHT10发送E1命令
//{
//	I2C_Start();
//	I2C_SendByte(Aht_addr_write);//Aht_addr_write);
//	I2C_WaitToAck();
//	I2C_SendByte(Aht_cmd_init);//写系统配置寄存器
//	I2C_WaitToAck();
//	I2C_SendByte(0x08);
//	I2C_WaitToAck();
//	I2C_SendByte(0x00);
//	I2C_WaitToAck();
//	I2C_Stop();
//}


unsigned char mof_sensor_aht10_Read_Status(void)//读取AHT10的状态寄存器
{
	unsigned char Byte_first;	
	I2C_Start();
	I2C_SendByte(0x71);//(Aht_addr_read);
	I2C_WaitToAck();
	Byte_first = I2C_ReadByte();
	I2C_NoAck();
	I2C_Stop();

	return Byte_first;
}




//bit Aht_Read_Cal_Enable(void)  //查询cal enable位有没有使能？
//{
//	unsigned char val = 0;//ret = 0,
// 
//  val = Aht_Read_Status();
//  if((val & 0x18)==0x18)  //判断NOR模式和校准输出是否有效
//  return 1;
//  else  return 0;
// }


 
void mof_sensor_aht10_Init(void)
{
	I2C_Init();
		
	if((mof_sensor_aht10_Read_Status()&0x18)!=0x18)
	{
		//重新初始化寄存器
		mof_sensor_aht10_Reset_REG(0x1b);
		mof_sensor_aht10_Reset_REG(0x1c);
		mof_sensor_aht10_Reset_REG(0x1e);
	}	
	
	sensor_aht10.temperature=0;
	sensor_aht10.humidity=0;
	
}


